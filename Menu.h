#ifndef MENU_H
#define MENU_H

#include "MenuItem.h"
#include "TextObject.h"
#include <vector>

enum MenuState {
    MENU_STATE_MAIN,
    MENU_STATE_PLAY,
    MENU_STATE_GUIDE
};

class Menu {
public:
    Menu();
    ~Menu();

    bool loadMenu(SDL_Renderer* screen);
    void render(SDL_Renderer* screen);
    void handleEvents(SDL_Event& event, MenuState& currentState);
    void renderGuide(SDL_Renderer* screen, TTF_Font* font);

private:
    MenuItem startButton;
    MenuItem guideButton;
    BaseObject menuBackground;

    // Text cho hướng dẫn
    std::vector<TextObject> guideTexts;
};

#endif //MENU_H

