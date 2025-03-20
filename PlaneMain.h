#ifndef PLANEMAIN_H
#define PLANEMAIN_H

#include <vector>
#include "BaseObject.h"
#include "Bullet.h"
#include "MapGame.h"

class PlaneMain : public BaseObject {
public:
    PlaneMain();
    ~PlaneMain();
    bool loadImg(std::string path, SDL_Renderer* screen);
    void MovePlane(SDL_Event events , SDL_Renderer* screen);
    void ShowPlane(SDL_Renderer* screen);
    void Move();
    void MoveLeft();
    void MoveRight();
    void MoveUp();
    void MoveDown();
    void StopMoveX();  // Thêm hàm dừng di chuyển theo trục X
    void StopMoveY();  // Thêm hàm dừng di chuyển theo trục Y

    void set_bullet_list(std::vector<Bullet*> bullets) {
        bullet_list = bullets;
    }
    std::vector<Bullet*> get_bullet_list() const {return bullet_list;}
    void HandleBullet(SDL_Renderer* des);

    // Thêm hàm mới để bắn đạn
    void Shoot(SDL_Renderer* screen);

    // Thêm hàm xử lý việc bắn đạn liên tục
    void HandleShooting(SDL_Renderer* screen);

    // check va chạm
    void CheckBulletCollision(Bullet* bullet);

    SetMap* map_; // Thêm một con trỏ đến đối tượng map

    void setMap(SetMap* map) { map_ = map; }

    void increaseScore(int val);    // tính điểm
    int getScore() const { return score; }    // lấy điểm

    void CheckPlaneCollision();   // check va chạm máy bay và tiles
    void CheckCollisionPoint(int x, int y, int map_x_start, int map_y_start);  // check va chạm điểm
    void decreaseLives(int amount);
    void increaseLives(int amount);
    void activateDoubleShot();
    void updatePowerUps();
    int getLives() const;
    bool isGameOver() const;

private:
    std::vector<Bullet*> bullet_list;

    int x_pos, y_pos;
    int stepX, stepY;

    // Thêm các biến cho chức năng bắn liên tục
    Uint32 last_shooting_time;  // Thời điểm bắn đạn gần nhất
    Uint32 shooting_delay;      // Độ trễ giữa các lần bắn (milliseconds)
    bool is_shooting;           // Biến kiểm tra trạng thái đang bắn

    int score;

    int lives;       // số sinh mạng
    bool double_shot; // trạng thái bắn 2 đạn
    Uint32 double_shot_start_time;  // thời gian bắt đầu bắn đạn đôi
    Uint32 double_shot_duration;    // thời gian duy trì đạn đôi
};

#endif //PLANEMAIN_H
