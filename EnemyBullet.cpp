#include "EnemyBullet.h"

EnemyBullet::EnemyBullet() {
    is_move_ = false;
    x_val_ = 0;
    y_val_ = 0;
}

EnemyBullet::~EnemyBullet() {
    // Destructor
}

void EnemyBullet::HandleMove(const int &x_border, const int &y_border) {
    rect_.y += y_val_;
    if (rect_.y > y_border) {
        is_move_ = false;
    }
}
