#ifndef BASEOBJECT_H_
#define BASEOBJECT_H_

#include "CommonFunc.h"

class BaseObject {
public:
    BaseObject();
    ~BaseObject();
    void setRect(const int &x, const int &y) {
        rect_.x = x;
        rect_.y = y;
    }
    const SDL_Rect& getRect() const {
        return rect_;
    }
    SDL_Texture* getObject() const {
        return p_object;
    }
    bool loadImg(std::string path, SDL_Renderer* screen);
    void render(SDL_Renderer* des, const SDL_Rect* clip = nullptr);
    void Free();

protected:
    SDL_Texture* p_object;
    SDL_Rect rect_;
};


#endif //BASEOBJECT_H_
