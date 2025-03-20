#include "BaseObject.h"

BaseObject::BaseObject() {
    p_object = nullptr;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}

BaseObject::~BaseObject() {
    Free();
}

bool BaseObject::loadImg(std::string path, SDL_Renderer* screen) {
    Free(); // Giải phóng texture cũ trước khi tải ảnh mới
    SDL_Surface* loadSurface = IMG_Load(path.c_str());
    if (loadSurface != nullptr) {
        SDL_SetColorKey(loadSurface, SDL_TRUE, SDL_MapRGB(loadSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        p_object = SDL_CreateTextureFromSurface(screen, loadSurface);
        if (p_object != nullptr) {
            rect_.w = loadSurface->w;  // lấy luôn chiều rộng thực sự của ảnh gán vào rect.w
            rect_.h = loadSurface->h;  // lấy luôn chiều cao thực sự của ảnh gán vào ract.h
        }
        SDL_FreeSurface(loadSurface);
    }
    return p_object != nullptr;
}

void BaseObject::render(SDL_Renderer* des, const SDL_Rect* clip) {
    if (p_object != nullptr) {
        SDL_Rect renderQuad = { rect_.x, rect_.y, rect_.w, rect_.h }; // Hiển thị full màn hình
        SDL_RenderCopy(des, p_object, clip, &renderQuad);
    }
}


void BaseObject::Free() {
    if (p_object != nullptr) {
        SDL_DestroyTexture(p_object);
        p_object = nullptr;
        rect_.w = 0;
        rect_.h = 0;
    }
}

