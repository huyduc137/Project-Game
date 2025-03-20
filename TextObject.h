#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H

#include "CommonFunc.h"
#include <string>
#include <SDL_ttf.h>

class TextObject {
public:
    TextObject();
    ~TextObject();

    enum TextColor {
        RED = 0,
        WHITE = 1,
        BLACK = 2
    };

    bool loadFromRenderText(TTF_Font* font, SDL_Renderer* renderer);
    void free();
    void setColor(const int& type);
    void setColor(const SDL_Color& color);
    void setRect(const int& x, const int& y) { rect_.x = x; rect_.y = y; }
    SDL_Rect getRect() const { return rect_; }
    SDL_Texture* getTexture() const { return texture_; }
    void setText(const std::string& text) { text_ = text; }
    std::string getText() const { return text_; }
    void render(SDL_Renderer* renderer, int x = -1, int y = -1);

private:
    std::string text_;
    SDL_Color text_color_;
    SDL_Texture* texture_;
    SDL_Rect rect_;
};
#endif //TEXTOBJECT_H

