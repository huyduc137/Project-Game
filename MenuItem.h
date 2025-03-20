#ifndef MENUITEM_H
#define MENUITEM_H

#include "BaseObject.h"
#include <string>

class MenuItem : public BaseObject {
public:
    MenuItem();
    ~MenuItem();

    void setPosition(int x, int y);
    bool isClicked(int x, int y) const;

    bool loadImg(std::string path, SDL_Renderer* screen);
    void render(SDL_Renderer* des, const SDL_Rect* clip = nullptr);

private:
    int pos_x;
    int pos_y;
};

#endif //MENUITEM_H
