#include "TextObject.h"

TextObject::TextObject() {
    text_color_.r = 255;
    text_color_.g = 255;
    text_color_.b = 255;
    texture_ = nullptr;
    rect_ = {0, 0, 0, 0};
}

TextObject::~TextObject() {
    free();
}

bool TextObject::loadFromRenderText(TTF_Font* font, SDL_Renderer* renderer) {
    free();
    SDL_Surface* text_surface = TTF_RenderUTF8_Blended(font, text_.c_str(), text_color_);   // UTF8 viết tiếng việt
    if (text_surface != nullptr) {
        texture_ = SDL_CreateTextureFromSurface(renderer, text_surface);
        rect_.w = text_surface->w;
        rect_.h = text_surface->h;
        SDL_FreeSurface(text_surface);
    }
    return texture_ != nullptr;
}

void TextObject::free() {
    if (texture_ != nullptr) {
        SDL_DestroyTexture(texture_);
        texture_ = nullptr;
        rect_ = {0, 0, 0, 0};
    }
}

void TextObject::setColor(const int& type) {
    switch (type) {
        case RED:
            text_color_ = {255, 0, 0};
        break;
        case WHITE:
            text_color_ = {255, 255, 255};
        break;
        case BLACK:
            text_color_ = {0, 0, 0};
        break;
        default:
            text_color_ = {255, 255, 255};
        break;
    }
}

void TextObject::setColor(const SDL_Color& color) {
    text_color_ = color;
}

void TextObject::render(SDL_Renderer* renderer, int x, int y) {
    if (x >= 0) rect_.x = x;
    if (y >= 0) rect_.y = y;
    SDL_RenderCopy(renderer, texture_, nullptr, &rect_);
}
