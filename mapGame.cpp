#include "mapGame.h"
#include <sstream>
#include <fstream>

void setMap :: loadMap(const char* name) {
    std::ifstream file(name);
    if (!file.is_open()) {
        return;
    }
    for (int i = 0 ; i < MAX_MAP_Y ; i++) {
        for (int j = 0 ; j < MAX_MAP_X ; j++) {
            file >> gameMap.tile[i][j];
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

void setMap::loadTiles(SDL_Renderer *screen) {
    for (int i = 1 ; i <= TILE_MAX ; i++) {
        std::stringstream filename;
        filename << "map/" << i << ".png";
        std::ifstream file(filename.str());
        if (!file.is_open()) {
            continue;
        }
        tileMat[i].loadImg(filename.str().c_str() , screen);
    }
}

void setMap::drawMap(SDL_Renderer *screen) {
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
