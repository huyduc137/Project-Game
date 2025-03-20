#ifndef BASEOBJECT_H
#define BASEOBJECT_H

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
    virtual bool loadImg(std::string path, SDL_Renderer* screen);    // virtual ở đây để khi sử dụng loadImg ở class khác ta có thể viết thêm chức năng
    void render(SDL_Renderer* des, const SDL_Rect* clip = nullptr);
    void Free();

protected:
    SDL_Texture* p_object;
    SDL_Rect rect_;
};

#endif //BASEOBJECT_H

