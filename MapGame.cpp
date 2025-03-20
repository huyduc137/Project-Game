#include "MapGame.h"
#include <sstream>
#include <fstream>

SetMap::SetMap() {
    gameMap.x_start = 0;
    gameMap.y_start = 0;
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

