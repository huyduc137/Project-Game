#include "MenuItem.h"

MenuItem::MenuItem() {
    pos_x = 0;
    pos_y = 0;
}

MenuItem::~MenuItem() {
    Free();
}

void MenuItem::setPosition(int x, int y) {
    pos_x = x;
    pos_y = y;
    rect_.x = x;
    rect_.y = y;
}

bool MenuItem::isClicked(int x, int y) const {
    // Kiểm tra xem điểm (x, y) có nằm trong phạm vi của button không
    if (x >= pos_x && x <= pos_x + rect_.w &&
        y >= pos_y && y <= pos_y + rect_.h) {
        return true;
        }
    return false;
}

bool MenuItem::loadImg(std::string path, SDL_Renderer* screen) {
    bool ret = BaseObject::loadImg(path, screen);
    return ret;
}

void MenuItem::render(SDL_Renderer* des, const SDL_Rect* clip) {
    SDL_Rect renderQuad = {pos_x, pos_y, rect_.w, rect_.h};
    SDL_RenderCopy(des, p_object, clip, &renderQuad);
}
