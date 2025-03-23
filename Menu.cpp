#include "Menu.h"

Menu::Menu() {
}

Menu::~Menu() {
    startButton.Free();
    guideButton.Free();
    menuBackground.Free();
}

bool Menu::loadMenu(SDL_Renderer* screen) {
    // Tải hình nền menu
    bool ret = menuBackground.loadImg("img/menu_bg.jpg", screen);
    if (!ret) return false;

    // Tải nút Start
    ret = startButton.loadImg("img/play_button.png", screen);
    if (!ret) return false;
    startButton.setPosition(SCREEN_WIDTH/2 - startButton.getRect().w/2, SCREEN_HEIGHT/2 - 200);

    // Tải nút Guide
    ret = guideButton.loadImg("img/guide_button.png", screen);
    if (!ret) return false;
    guideButton.setPosition(SCREEN_WIDTH/2 - guideButton.getRect().w/2, SCREEN_HEIGHT/2 - 50);

    // Tải nút Quit
    ret = quitButton.loadImg("img/qquit.png" , screen);
    if (!ret) return false;
    quitButton.setPosition(SCREEN_WIDTH/2 - quitButton.getRect().w/2 , SCREEN_HEIGHT/2 + 100);

    // Khởi tạo các text hướng dẫn
    for (int i = 0; i < 5; i++) {
        TextObject text;
        text.setColor(TextObject::WHITE);
        guideTexts.push_back(text);
    }

    return true;
}

void Menu::render(SDL_Renderer* screen) {
    // Vẽ nền menu
    menuBackground.render(screen);

    // Vẽ các nút
    startButton.render(screen);
    guideButton.render(screen);
    quitButton.render(screen);
}

// void Menu::handleEvents(SDL_Event& event, MenuState& currentState) {
//     if (event.type == SDL_MOUSEBUTTONDOWN) {
//         if (event.button.button == SDL_BUTTON_LEFT) {
//             int x = event.button.x;
//             int y = event.button.y;
//
//             // Kiểm tra xem người dùng nhấn vào nút nào
//             if (startButton.isClicked(x, y)) {
//                 if (g_sound_click != nullptr) {
//                     Mix_PlayChannel(-1, g_sound_click, 0);
//                 }
//                 currentState = MENU_STATE_PLAY;
//             }
//             else if (guideButton.isClicked(x, y)) {
//                 if (g_sound_click != nullptr) {
//                     Mix_PlayChannel(-1, g_sound_click, 0);
//                 }
//                 currentState = MENU_STATE_GUIDE;
//             }
//         }
//     }
//     else if (event.type == SDL_KEYDOWN && currentState == MENU_STATE_GUIDE) {
//         // Nhấn phím bất kỳ để quay lại menu chính từ màn hình hướng dẫn
//         if (event.key.keysym.sym == SDLK_ESCAPE) {
//             currentState = MENU_STATE_MAIN;
//         }
//     }
// }
void Menu::handleEventsGuide(SDL_Event &event, MenuState &currentState) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            int x = event.button.x;
            int y = event.button.y;
            if (guideButton.isClicked(x , y)) {
                if (g_sound_click != nullptr) {
                    Mix_PlayChannel(-1, g_sound_click, 0);
                }
                currentState = MENU_STATE_GUIDE;
            }
        }
    }
}
void Menu::handleEventsPlay(SDL_Event &event, MenuState &currentState) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            int x = event.button.x;
            int y = event.button.y;
            if (startButton.isClicked(x, y)) {
                if (g_sound_click != nullptr) {
                    Mix_PlayChannel(-1, g_sound_click, 0);
                }
                currentState = MENU_STATE_PLAY;
            }
        }
    }
}
void Menu :: handleEventsQuit(SDL_Event &event , MenuState &currentState) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            int x = event.button.x;
            int y = event.button.y;
            if (quitButton.isClicked(x, y)) {
                if (g_sound_click != nullptr) {
                    Mix_PlayChannel(-1, g_sound_click, 0);
                }
                currentState = MENU_STATE_QUIT;
            }
        }
    }
}
void Menu::renderGuide(SDL_Renderer* screen, TTF_Font* font) {
    // Vẽ nền menu
    menuBackground.render(screen);

    // Thiết lập nội dung cho các dòng hướng dẫn
    guideTexts[0].setText("HƯỚNG DẪN CHƠI");
    guideTexts[1].setText("Sử dụng các phím mũi tên để di chuyển máy bay");
    guideTexts[2].setText("Nhấn SPACE để bắn");
    guideTexts[3].setText("Bắn trúng các chướng ngại vật để ghi điểm");
    guideTexts[4].setText("Nhấn ESC để quay lại menu chính");

    // Vẽ các dòng hướng dẫn
    int y_pos = 150;
    for (int i = 0; i < guideTexts.size(); i++) {
        guideTexts[i].loadFromRenderText(font, screen);
        int x_pos = SCREEN_WIDTH/2 - guideTexts[i].getRect().w/2;
        guideTexts[i].render(screen, x_pos, y_pos);
        y_pos += 80;  // Khoảng cách giữa các dòng
    }
}
