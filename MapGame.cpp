#include "MapGame.h"
#include <sstream>
#include <fstream>

SetMap::SetMap() {
    gameMap.x_start = 0;
    gameMap.y_start = 0;
    last_enemy_shoot_time = 0;
    enemy_shoot_delay = 400; // thời gian đạn delay để bắn đạn tiếp theo
    enemy_bullet_speed = 4;   // Enemy bullet speed

    // Seed random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}
RenderTile::RenderTile() {
}

RenderTile::~RenderTile() {
}


SetMap::~SetMap() {
}
void SetMap::loadMap(const char *name) {
    std::ifstream file(name);
    if (!file.is_open()) {
        return;
    }
    for (int i = 0 ; i < MAX_MAP_Y ; i++) {
        for (int j = 0 ; j < MAX_MAP_X ; j++) {
            file  >> gameMap.tile[i][j];
            if (gameMap.tile[i][j] != 0) {
                if (j > gameMap.max_x) {
                    gameMap.max_x = j;
                }
                if (i > gameMap.max_y) {
                    gameMap.max_y = i;
                }
            }
        }
    }
    gameMap.max_x = (gameMap.max_x + 1)*TILE_SIZE;
    gameMap.max_y = (gameMap.max_y + 1)*TILE_SIZE;
    gameMap.x_start = gameMap.y_start = 0;
    gameMap.fileName = name;
    file.close();
}

void SetMap::loadTiles(SDL_Renderer *screen) {
    for (int i = 1 ; i <= MAX_TILES ; i++) {
        std::stringstream filename;
        filename << "mapgame/plane" << i << ".png";
        std::ifstream file(filename.str());
        if (!file.is_open()) {
            continue;
        }
        tileMat[i].loadImg(filename.str().c_str() , screen);
    }
}

void SetMap::drawMap(SDL_Renderer *screen) {
    int x1 = 0 , x2 = 0;                            // x1 ,x2 là chiều dài của màn hình máy tính
    int y1 = 0, y2 = 0;                             // y1 , y2 là chiều rồng của màn hình máy tính
    int pos_x = gameMap.x_start / TILE_SIZE;        // trả về tọa độ, vị trí của ô trong bản đồ 10 * 400
    int pos_y = gameMap.y_start / TILE_SIZE;        // trả về tọa độ, vị trí của ô trong bản đồ 10 * 400

    x1 = (gameMap.x_start % TILE_SIZE)*-1;        // đưa về độ rộng của màn hình máy tính
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);
    y1 = (gameMap.y_start % TILE_SIZE)*-1;        // đưa về độ dài của màn hình máy tính
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);
    for (int i = y1 ; i < y2 ; i+=TILE_SIZE) {
        pos_x = gameMap.x_start / TILE_SIZE;
        for (int j = x1 ; j < x2 ; j+=TILE_SIZE) {
            int val = gameMap.tile[pos_y][pos_x];
            if (val > 0) {
                tileMat[val].setRect(j , i);
                tileMat[val].render(screen);
            }
            pos_x++;
        }
        pos_y++;
    }
}


void SetMap::removeTile(int x, int y) {
    // Chuyển đổi tọa độ pixel thành tọa độ tile
    int tile_x = (x + gameMap.x_start) / TILE_SIZE;
    int tile_y = (y + gameMap.y_start) / TILE_SIZE;

    // Kiểm tra xem tọa độ tile có hợp lệ không
    if (tile_x >= 0 && tile_x < MAX_MAP_X && tile_y >= 0 && tile_y < MAX_MAP_Y) {
        // Chỉ xóa tile nếu là tile 1, 2 hoặc 3
        if (gameMap.tile[tile_y][tile_x] >= 1 && gameMap.tile[tile_y][tile_x] <= 5) {
            gameMap.tile[tile_y][tile_x] = 0;
        }
    }
}

int SetMap::getTileType(int x, int y) const {
    if (x >= 0 && x < MAX_MAP_X && y >= 0 && y < MAX_MAP_Y) {
        return gameMap.tile[y][x];
    }
    return 0;
}


// Enemy bullet methods
void SetMap::InitEnemyShooting(SDL_Renderer* screen) {
    last_enemy_shoot_time = SDL_GetTicks();
}

void SetMap::TryEnemyShoot(SDL_Renderer* screen) {
    Uint32 current_time = SDL_GetTicks();

    // Check if it's time to try shooting
    if (current_time - last_enemy_shoot_time > enemy_shoot_delay) {
        last_enemy_shoot_time = current_time;

        // Find visible enemy tiles
        int x1 = 0, x2 = 0;
        int y1 = 0, y2 = 0;
        int pos_x = gameMap.x_start / TILE_SIZE;
        int pos_y = gameMap.y_start / TILE_SIZE;

        x1 = (gameMap.x_start % TILE_SIZE) * -1;
        x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);
        y1 = (gameMap.y_start % TILE_SIZE) * -1;
        y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

        std::vector<std::pair<int, int>> enemy_positions;

        for (int i = y1; i < y2; i += TILE_SIZE) {
            int map_pos_y = pos_y + (i - y1) / TILE_SIZE;
            for (int j = x1; j < x2; j += TILE_SIZE) {
                int map_pos_x = pos_x + (j - x1) / TILE_SIZE;

                // Check if this is an enemy tile (tile types 1, 2, or 3)
                if (map_pos_x >= 0 && map_pos_x < MAX_MAP_X && map_pos_y >= 0 && map_pos_y < MAX_MAP_Y) {
                    int tile_type = gameMap.tile[map_pos_y][map_pos_x];
                    if (tile_type >= 1 && tile_type <= 3) {
                        // Store enemy position (screen coordinates)
                        enemy_positions.push_back(std::make_pair(j + TILE_SIZE/2, i + TILE_SIZE));
                    }
                }
            }
        }

        // Randomly choose one enemy to shoot (if there are any)
        if (!enemy_positions.empty()) {
            // 30% chance that an enemy will shoot
            if (std::rand() % 100 < 30) {
                int random_index = std::rand() % enemy_positions.size();
                auto enemy_pos = enemy_positions[random_index];

                // Create a bullet from this enemy
                CreateEnemyBullet(enemy_pos.first, enemy_pos.second, screen);
            }
        }
    }
}

void SetMap::CreateEnemyBullet(int x, int y, SDL_Renderer* screen) {
    EnemyBullet* bullet = new EnemyBullet();
    if (bullet->loadImg("img/bulletEnemy.png", screen)) {
        bullet->setRect(x - bullet->getRect().w/2, y);
        bullet->set_y_val(enemy_bullet_speed);
        bullet->set_is_move(true);
        enemy_bullets.push_back(bullet);
    } else {
        delete bullet;
    }
}

void SetMap::HandleEnemyBullets(SDL_Renderer* screen) {
    // Try to generate new enemy bullets
    TryEnemyShoot(screen);

    // Move and render existing enemy bullets
    for (int i = 0; i < enemy_bullets.size(); i++) {
        EnemyBullet* bullet = enemy_bullets[i];
        if (bullet && bullet->get_is_move()) {
            bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
            bullet->render(screen);
        } else {
            enemy_bullets.erase(enemy_bullets.begin() + i);
            delete bullet;
            i--;
        }
    }
}

void SetMap::CleanupEnemyBullets() {
    for (auto bullet : enemy_bullets) {
        delete bullet;
    }
    enemy_bullets.clear();
}
