#include "PlaneMain.h"

PlaneMain::PlaneMain() {
    rect_.x = SCREEN_WIDTH / 2 - 55;
    rect_.y = SCREEN_HEIGHT/2 + 200;
    x_pos = rect_.x;
    y_pos = rect_.y;
    stepX = 0;
    stepY = 0;

    map_ = nullptr;

    // Khởi tạo các biến cho chức năng bắn liên tục
    last_shooting_time = 0;
    shooting_delay = 150;  // 150ms giữa các lần bắn
    is_shooting = false;

    score = 0;

    lives = 5;
    double_shot = false;
    double_shot_start_time = 0;
    double_shot_duration = 5000;  // thời gian bắn đạn đôi

    is_invulnerable = false;
    invulnerable_start_time = 0;
    invulnerable_duration = 2000; // 2000ms invulnerability after hit

}

PlaneMain::~PlaneMain() {
    Free();
}

bool PlaneMain::loadImg(std::string path, SDL_Renderer *screen) {
    bool ret = BaseObject::loadImg(path, screen);
    return ret;
}

void PlaneMain::ShowPlane(SDL_Renderer *screen) {
    rect_.x = x_pos;
    rect_.y = y_pos;
    SDL_Rect renderQuad = {rect_.x, rect_.y, rect_.w, rect_.h};
    SDL_RenderCopy(screen, p_object, NULL, &renderQuad);
}

void PlaneMain::Move() {
    x_pos += stepX;
    y_pos += stepY;

    if (x_pos < 0) {
        x_pos = 0;
    }
    else if (x_pos + rect_.w > SCREEN_WIDTH) {
        x_pos = SCREEN_WIDTH - rect_.w;
    }

    if (y_pos < 0) {
        y_pos = 0;
    }
    else if (y_pos + rect_.h > SCREEN_HEIGHT) {
        y_pos = SCREEN_HEIGHT - rect_.h;
    }
}

void PlaneMain::MoveRight() {
    stepX = SPEED_PLANE;
}

void PlaneMain::MoveLeft() {
    stepX = -SPEED_PLANE;
}

void PlaneMain::MoveUp() {
    stepY = -SPEED_PLANE;
}

void PlaneMain::MoveDown() {
    stepY = SPEED_PLANE;
}

void PlaneMain::StopMoveX() {
    stepX = 0;
}

void PlaneMain::StopMoveY() {
    stepY = 0;
}

void PlaneMain::MovePlane(SDL_Event events, SDL_Renderer *screen) {
    if (events.type == SDL_KEYDOWN) {
        switch (events.key.keysym.sym) {
            case SDLK_UP:
                if (events.key.repeat == 0) MoveUp();
                break;
            case SDLK_DOWN:
                if (events.key.repeat == 0) MoveDown();
                break;
            case SDLK_LEFT:
                if (events.key.repeat == 0) MoveLeft();
                break;
            case SDLK_RIGHT:
                if (events.key.repeat == 0) MoveRight();
                break;
            case SDLK_SPACE:
                is_shooting = true;
                break;
            default: break;
        }
    }
    else if (events.type == SDL_KEYUP) {
        switch (events.key.keysym.sym) {
            case SDLK_UP:
            case SDLK_DOWN:
                if (events.key.repeat == 0) StopMoveY();
                break;
            case SDLK_LEFT:
            case SDLK_RIGHT:
                if (events.key.repeat == 0) StopMoveX();
                break;
            case SDLK_SPACE:
                is_shooting = false;
                break;
            default: break;
        }
    }
}

// Hàm để bắn đạn
void PlaneMain::Shoot(SDL_Renderer *screen) {
    if (g_sound_bullet != nullptr) {
        Mix_PlayChannel(-1, g_sound_bullet, 0);
    }
    if (double_shot) {
        // Create two bullets for double shot
        Bullet* bullet1 = new Bullet();
        Bullet* bullet2 = new Bullet();

        if (bullet1->loadImg("img/bulletMain.png", screen) && bullet2->loadImg("img/bulletMain.png", screen)) {
            // Position the bullets on either side of the plane's nose
            bullet1->setRect(this->rect_.x + this->rect_.w/3 - bullet1->getRect().w/2,
                           this->rect_.y + 100);
            bullet2->setRect(this->rect_.x + 2*this->rect_.w/3 - bullet2->getRect().w/2,
                           this->rect_.y + 100);

            bullet1->set_y_val(SPEED_BULLET);
            bullet2->set_y_val(SPEED_BULLET);

            bullet1->set_is_move(true);
            bullet2->set_is_move(true);

            bullet_list.push_back(bullet1);
            bullet_list.push_back(bullet2);
        }
        else {
            delete bullet1;
            delete bullet2;
        }
    }
    else {
        // Original single bullet implementation
        Bullet* bullet = new Bullet();
        if (bullet->loadImg("img/bulletMain.png", screen)) {
            bullet->setRect(this->rect_.x + (this->rect_.w / 2) - (bullet->getRect().w / 2),
                          this->rect_.y + 150);
            bullet->set_y_val(SPEED_BULLET);
            bullet->set_is_move(true);
            bullet_list.push_back(bullet);
        }
        else {
            delete bullet;
        }
    }
}

// Hàm xử lý việc bắn đạn liên tục
void PlaneMain::HandleShooting(SDL_Renderer *screen) {
    Uint32 current_time = SDL_GetTicks();  // lấy số mili giây kể từ khi SDL được khởi tạo
    if (is_shooting && current_time - last_shooting_time > shooting_delay) {
        Shoot(screen);
        last_shooting_time = current_time;
    }
}

// Hàm bắn
void PlaneMain::HandleBullet(SDL_Renderer *des) {
    for (int i = 0; i < bullet_list.size(); i++) {
        Bullet* bullet = bullet_list.at(i);
        if (bullet != NULL) {
            if (bullet->get_is_move() == true) {
                bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                bullet->render(des, nullptr);

                // Kiểm tra va chạm với các tile
                CheckBulletCollision(bullet);
            }
            else {
                bullet_list.erase(bullet_list.begin() + i);
                if (bullet != NULL) {
                    delete bullet;
                    bullet = NULL;
                }
            }
        }
    }
}

void PlaneMain::CheckBulletCollision(Bullet* bullet) {
    if (!map_ || !bullet) return;

    // Lấy các thông số của map
    int map_x_start = map_->getXStart();
    int map_y_start = map_->getYStart();

    // Vị trí của viên đạn
    SDL_Rect bullet_rect = bullet->getRect();

    // Vị trí vật lý của viên đạn trên bản đồ
    int bullet_x = bullet_rect.x;
    int bullet_y = bullet_rect.y;

    // Chuyển đổi tọa độ pixel thành tọa độ tile
    int tile_x = (bullet_x + map_x_start) / TILE_SIZE;
    int tile_y = (bullet_y + map_y_start) / TILE_SIZE;

    // Kiểm tra xem vị trí của đạn có đúng với một tile nào đó không
    if (tile_x >= 0 && tile_x < MAX_MAP_X && tile_y >= 0 && tile_y < MAX_MAP_Y) {
        int tile_type = map_->getTileType(tile_x, tile_y);

        // Nếu tile là loại 1, 2 hoặc 3 thì xóa cả tile và đạn
        if (tile_type >= 1 && tile_type <= 3) {
            if (g_sound_explosion != nullptr) {
                Mix_PlayChannel(-1, g_sound_bullet, 0);
            }
            // Xóa tile
            map_->removeTile(bullet_x, bullet_y);

            // Đánh dấu đạn là không còn di chuyển nữa
            bullet->set_is_move(false);

            increaseScore(POINT);
        }

    }
}

void PlaneMain::increaseScore(int val) {
    score += val;
}

void PlaneMain::CheckPlaneCollision() {
    if (!map_) return;

    // Get the plane hitbox (make it slightly smaller than the actual sprite)
    SDL_Rect plane_hitbox = {
        x_pos + rect_.w/4,
        y_pos + rect_.h/4,
        rect_.w/2,
        rect_.h/2
    };

    // Map coordinates
    int map_x_start = map_->getXStart();    // đại diện cho vị trí của góc trên bên trái phần bản đồ hiển thị
    int map_y_start = map_->getYStart();    // đại diện cho vị trí của góc trên bên trái phần bản đồ hiển thị

    // Check four corners of the hitbox
    CheckCollisionPoint(plane_hitbox.x, plane_hitbox.y, map_x_start, map_y_start);
    CheckCollisionPoint(plane_hitbox.x + plane_hitbox.w, plane_hitbox.y, map_x_start, map_y_start);
    CheckCollisionPoint(plane_hitbox.x, plane_hitbox.y + plane_hitbox.h, map_x_start, map_y_start);
    CheckCollisionPoint(plane_hitbox.x + plane_hitbox.w, plane_hitbox.y + plane_hitbox.h, map_x_start, map_y_start);
}

void PlaneMain::CheckCollisionPoint(int x, int y, int map_x_start, int map_y_start) {
    // Convert pixel coordinates to tile coordinates
    int tile_x = (x + map_x_start) / TILE_SIZE;
    int tile_y = (y + map_y_start) / TILE_SIZE;

    // Check if coordinates are within map bounds
    if (tile_x >= 0 && tile_x < MAX_MAP_X && tile_y >= 0 && tile_y < MAX_MAP_Y) {
        int tile_type = map_->getTileType(tile_x, tile_y);

        // Handle collision based on tile type
        if (tile_type >= 1 && tile_type <= 3) {
            // âm thanh
            if (g_sound_explosion != nullptr) {
                Mix_PlayChannel(-1, g_sound_explosion, 0);
            }
            decreaseLives(1);  // nếu máy bay va chạm thì trừ 1 sinh mệnh
            map_->removeTile(x, y);
        }
        else if (tile_type == 4) {
            activateDoubleShot();    // chức năng double shoot
            map_->removeTile(x, y);
        }
        else if (tile_type == 5) {
            increaseLives(1);  // tăng sinh mệnh
            map_->removeTile(x, y);
        }
    }
}

void PlaneMain::decreaseLives(int amount) {
    lives -= amount;
    if (lives < 0) lives = 0;
}

void PlaneMain::increaseLives(int amount) {
    lives += amount;
    if (lives > 5) lives = 5;
}

void PlaneMain::activateDoubleShot() {
    double_shot = true;
    double_shot_start_time = SDL_GetTicks();
}

void PlaneMain::updatePowerUps() {
    // Check if double shot power-up has expired
    if (double_shot && SDL_GetTicks() - double_shot_start_time > double_shot_duration) {
        double_shot = false;
    }
    // Cập nhật trạng thái bất khả xâm phạm (invulnerability)
    if (is_invulnerable) {
        if (SDL_GetTicks() - invulnerable_start_time > invulnerable_duration) {
            is_invulnerable = false;
        }
    }
}

int PlaneMain::getLives() const {
    return lives;
}

bool PlaneMain::isGameOver() const {
    return lives <= 0;
}

SDL_Rect PlaneMain::GetHitbox() const {
    return {
        x_pos + rect_.w/4,
        y_pos + rect_.h/4,
        rect_.w/2,
        rect_.h/2
    };
}
// Hàm tiện ích kiểm tra va chạm giữa hai SDL_Rect
static bool CheckCollisionRect(const SDL_Rect& a, const SDL_Rect& b) {
    if (a.x + a.w <= b.x) return false;
    if (b.x + b.w <= a.x) return false;
    if (a.y + a.h <= b.y) return false;
    if (b.y + b.h <= a.y) return false;
    return true;
}
void PlaneMain::CheckEnemyBulletCollision() {
    // Nếu chưa liên kết map hoặc đang ở trạng thái bất khả xâm phạm, không kiểm tra
    if (!map_ || is_invulnerable) return;

    SDL_Rect plane_hitbox = GetHitbox();

    // Lấy danh sách đạn của enemy từ map
    std::vector<EnemyBullet*>& enemy_bullets = map_->getEnemyBullets();

    for (size_t i = 0; i < enemy_bullets.size(); i++) {
        EnemyBullet* bullet = enemy_bullets[i];
        if (bullet && bullet->get_is_move()) {
            SDL_Rect bullet_rect = bullet->getRect();
            // Kiểm tra va chạm giữa hitbox của máy bay và đạn enemy
            if (CheckCollisionRect(plane_hitbox, bullet_rect)) {
                // Khi va chạm, đánh dấu đạn không còn di chuyển
                bullet->set_is_move(false);
                // Giảm 1 sinh mạng
                decreaseLives(1);
                // Đặt trạng thái bất khả xâm phạm để tránh nhận sát thương liên tục (ví dụ 2000ms)
                is_invulnerable = true;
                invulnerable_start_time = SDL_GetTicks();
            }
        }
    }
}
