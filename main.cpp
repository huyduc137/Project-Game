#include "CommonFunc.h"
#include "BaseObject.h"
#include "PlaneMain.h"
#include "MapGame.h"
#include "TextObject.h"
#include "Menu.h"

BaseObject backGround;

bool initData() {
    bool success;
    success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    if (ret < 0) {
        return false;
    }
    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        success = false;
    }
    //SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    window = SDL_CreateWindow("Save The World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        success = false;
    }
    else {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == nullptr) {
            success = false;
        }
        else {
            SDL_SetRenderDrawColor(renderer, 225, 225, 225, 225);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags)) {
                success = false;
            }
            if (TTF_Init() == -1) {
                success = false;
            }
        }
    }
    return success;
}

bool loadSoundEffects() {
    bool success = true;

    // Load bullet sound effect
    g_sound_bullet = Mix_LoadWAV("sound/PlaneHit1.wav");
    if (g_sound_bullet == nullptr) {
        return false;
        success = false;
    }

    // Load explosion sound effect
    g_sound_explosion = Mix_LoadWAV("sound/PlaneCollsition.wav");
    if (g_sound_explosion == nullptr) {
        return false;
        success = false;
    }
    g_sound_click = Mix_LoadWAV("sound/click.wav");
    if (g_sound_click == nullptr) {
        return false;
        success = false;
    }

    return success;
}

bool loadBackGround() {
    return backGround.loadImg("img/background.jpg", renderer);
}

void close() {
    // Free sound effects
    if (g_sound_bullet != nullptr) {
        Mix_FreeChunk(g_sound_bullet);
        g_sound_bullet = nullptr;
    }

    if (g_sound_explosion != nullptr) {
        Mix_FreeChunk(g_sound_explosion);
        g_sound_explosion = nullptr;
    }
    backGround.Free();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = nullptr;
    window = nullptr;
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
}

int main(int argc, char* argv[]) {
    if (!initData()) {
        return -1;
    }
    if (!loadBackGround()) {
        return -1;
    }
    if (!loadSoundEffects()) {
        return -1;
    }
    // Tải font
    TTF_Font* font = TTF_OpenFont("font/Times_New_Roman.ttf", 24);
    if (font == nullptr) {
        return -1;
    }

    // tạo Menu
    Menu menu;
    if (!menu.loadMenu(renderer)) {
        return -1;
    }
    MenuState gameState = MENU_STATE_MAIN;

huydeptrai:

    SetMap map;
    map.loadMap("mapgame/map_plane.txt");
    map.loadTiles(renderer);
    PlaneMain planeMain;
    planeMain.loadImg("img/main.png", renderer);
    bool running = true;

    int SPEED_SCROLL = 2;    // tốc độ cuộn màn hình

    // Sau khi khởi tạo map và planeMain
    planeMain.setMap(&map);

    TextObject scoreText;
    scoreText.setColor(TextObject::WHITE);

    TextObject livesText;
    livesText.setColor(TextObject::WHITE);

    // lives
    BaseObject heart;
    // BackGround End
    BaseObject BackGround_End;
    // Nút Back (Quay Lại)
    MenuItem back;
    // Background_WIN
    BaseObject win;

    // FPS control
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;

    while (running) {
        frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            if (gameState == MENU_STATE_MAIN) {
                // menu.handleEvents(event, gameState);
                menu.handleEventsGuide(event , gameState);
                menu.handleEventsPlay(event , gameState);
                menu.handleEventsQuit(event , gameState);
            }
            else if (gameState == MENU_STATE_GUIDE) {
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                    gameState = MENU_STATE_MAIN;
                    goto huydeptrai;
                }
            }
            else if (gameState == MENU_STATE_PLAY) {
                planeMain.MovePlane(event, renderer);

                // Thêm phím ESC để quay lại menu chính từ màn hình chơi
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                    gameState = MENU_STATE_MAIN;
                    goto huydeptrai;     // load lại map
                }
            }
        }

        // Render
        SDL_SetRenderDrawColor(renderer, 225, 225, 225, 225);
        SDL_RenderClear(renderer);

        // Render và update tùy thuộc vào trạng thái game
        if (gameState == MENU_STATE_MAIN) {
            menu.render(renderer);
        }
        else if (gameState == MENU_STATE_GUIDE) {
            menu.renderGuide(renderer, font);
        }
        else if (gameState == MENU_STATE_QUIT) {
            running = false;
        }
        else if (gameState == MENU_STATE_PLAY) {
            // Update power-ups status
            planeMain.updatePowerUps();

            // Move the plane
            planeMain.Move();

            // Check for collisions
            planeMain.CheckPlaneCollision();

            // Handle shooting
            planeMain.HandleShooting(renderer);

            // Check for game over
            if (planeMain.isGameOver()) {
                // Render game over message
                BackGround_End.loadImg("img/BackGround_End.jpg" , renderer);
                back.loadImg("img/back.png" , renderer);
                back.setPosition(SCREEN_WIDTH / 2 - back.getRect().w / 2, SCREEN_HEIGHT / 2 + 230);
                BackGround_End.render(renderer);
                back.render(renderer);
                SDL_RenderPresent(renderer);

                // Wait for ESC key to return to menu
                SDL_Event tempEvent;
                bool waitingForEsc = true;
                while (waitingForEsc) {
                    while (SDL_PollEvent(&tempEvent)) {
                        if (tempEvent.type == SDL_QUIT) {
                            waitingForEsc = false;
                            running = false;
                        }
                        if (tempEvent.type == SDL_MOUSEBUTTONDOWN) {
                            if (tempEvent.button.button == SDL_BUTTON_LEFT) {
                                int x_ = tempEvent.button.x;
                                int y_ = tempEvent.button.y;
                                if (back.isClicked(x_ , y_)) {
                                    if (g_sound_click != nullptr) {
                                        Mix_PlayChannel(-1, g_sound_click, 0);
                                    }
                                    gameState = MENU_STATE_MAIN;
                                    goto huydeptrai;
                                }
                            }
                        }
                        if (tempEvent.type == SDL_KEYDOWN && tempEvent.key.keysym.sym == SDLK_ESCAPE) {
                            waitingForEsc = false;
                            gameState = MENU_STATE_MAIN;
                            // Reset the plane
                            goto huydeptrai;
                        }
                    }
                    SDL_Delay(10);
                }
            }
            else {
                // Normal rendering and update
                backGround.render(renderer, nullptr);
                map.drawMap(renderer);

                // Update map scrolling
                int currentY = map.getYStart();
                currentY -= SPEED_SCROLL;
                if (currentY < 0) {
                    currentY = map.getMaxY() - SCREEN_HEIGHT;
                }

                if (currentY == 1)   // cuộn cuối map
                {
                    SDL_RenderClear(renderer);
                    win.loadImg("img/youwin.png" , renderer);
                    win.render(renderer);
                    SDL_RenderPresent(renderer);
                    SDL_Event tempEvent;
                    bool waitingForEsc = true;
                    while (waitingForEsc) {
                        while (SDL_PollEvent(&tempEvent)) {
                            if (tempEvent.type == SDL_QUIT) {
                                waitingForEsc = false;
                            }
                            if (tempEvent.type == SDL_KEYDOWN && tempEvent.key.keysym.sym == SDLK_ESCAPE) {
                                waitingForEsc = false;
                                gameState = MENU_STATE_MAIN;
                                // Reset the plane
                                goto huydeptrai;
                            }
                        }
                        SDL_Delay(10);
                    }
                }
                map.setYStart(currentY);

                planeMain.ShowPlane(renderer);
                planeMain.HandleBullet(renderer);

                // Display score
                std::string scoreString = "Score: " + std::to_string(planeMain.getScore());
                scoreText.setText(scoreString);
                scoreText.loadFromRenderText(font, renderer);
                scoreText.render(renderer, 10, 10);

                // Display lives
                heart.loadImg("img/heart.png", renderer);
                heart.setRect(0 , 35);
                heart.render(renderer);
                std::string textLives = " x " + std::to_string(planeMain.getLives());
                livesText.setText(textLives);
                livesText.loadFromRenderText(font, renderer);
                livesText.render(renderer, 30, 40);
            }
        }

        SDL_RenderPresent(renderer);

        // Điều chỉnh FPS
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    TTF_CloseFont(font); // giải phóng font
    close();
    return 0;
}
