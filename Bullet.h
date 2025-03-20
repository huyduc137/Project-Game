
#ifndef BULLET_H
#define BULLET_H

#include <vector>
#include "BaseObject.h"

class Bullet : public BaseObject {
public:
    Bullet();
    ~Bullet();

    void set_x_val(const int &Val){x_val_ = Val;}
    void set_y_val(const int &Val){y_val_ = Val;}
    int get_x_val() const{return x_val_;}
    int get_y_val() const{return y_val_;}

    void set_is_move(const bool &isMove){is_move_ = isMove;}
    bool get_is_move() const{return is_move_;}

    void HandleMove(const int &x_border , const int &y_border);

    // check va chạm
    //bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);

private:
    int x_val_;
    int y_val_;
    bool is_move_;
    int bullet_speed_;
};

#endif //BULLET_H
