#include "CommonFunc.h"
#include "BaseObject.h"
#include "mapGame.h"

BaseObject backGround;

bool initData() {
    bool success;
    success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0) {
        return false;
    }
    //SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    window = SDL_CreateWindow("Keo Dep Trai", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
        }
    }
    return success;
}

bool loadBackGround() {
    return backGround.loadImg("img/background.png", renderer);
}

void close() {
    backGround.Free();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = nullptr;
    window = nullptr;
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    if (!initData()) {
        return -1;
    }
    if (!loadBackGround()) {
        return -1;
    }
    setMap map;
    map.loadMap("map/map01.dat");
    map.loadTiles(renderer);
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
        }
        SDL_SetRenderDrawColor(renderer, 225, 225, 225, 225);

        backGround.render(renderer, nullptr);
        map.drawMap(renderer);

        SDL_RenderPresent(renderer);
    }
    close();
    return 0;
}
