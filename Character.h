#ifndef CHARACTER_H
#define CHARACTER_H

#include "BaseObject.h"

class Character : public BaseObject {
public:
    Charracter(){;}
    ~Character(){;}
};

class moveCharacter {
    moveCharacter();
    ~moveCharacter();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void jog();
};

#endif //CHARACTER_H
