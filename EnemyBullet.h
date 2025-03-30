#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include "BaseObject.h"
class EnemyBullet : public BaseObject {
public:
    EnemyBullet();
    ~EnemyBullet();

    void set_x_val(const int &Val) { x_val_ = Val; }
    void set_y_val(const int &Val) { y_val_ = Val; }
    int get_x_val() const { return x_val_; }
    int get_y_val() const { return y_val_; }

    void set_is_move(const bool &isMove) { is_move_ = isMove; }
    bool get_is_move() const { return is_move_; }

    void HandleMove(const int &x_border, const int &y_border);

private:
    int x_val_;
    int y_val_;
    bool is_move_;
};

#endif //ENEMYBULLET_H

