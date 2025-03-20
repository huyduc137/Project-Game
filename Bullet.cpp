#include "Bullet.h"

#include "PlaneMain.h"

Bullet::Bullet() {
    is_move_ = false;
    x_val_ = 0;
    y_val_ = 0;
}

Bullet::~Bullet() {

}

void Bullet::HandleMove(const int &x_border, const int &y_border) {
    rect_.y -= y_val_;
    if (rect_.y < 0) {
        is_move_ = false;
    }
}

// bool Bullet::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2) {
//     bool collision = false;
//     int left_a = object1.x;
//     int right_a = object1.x + object1.w;
//     int top_a = object1.y;
//     int bottom_a = object1.y + object1.h;
//
//     int left_b = object2.x;
//     int right_b = object2.x + object2.w;
//     int top_b = object2.y;
//     int bottom_b = object2.y + object2.h;
//
//     if (left_a < right_b && right_a > left_b && top_a < bottom_b && bottom_a > top_b) {
//         collision = true;
//     }
//     return collision;
// }



