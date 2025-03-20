// MapGame.h
#ifndef MAPGAME_H
#define MAPGAME_H

#include "BaseObject.h"

struct infor_tile {
    int x_start, y_start;   // vị trí xét trong bản đồ khi nhân vật di chuyển
    int max_x = 0, max_y = 0; // chiều dài và chiều rộng của bản đồ
    int tile[MAX_MAP_Y][MAX_MAP_X];
    const char* fileName;
};

class RenderTile: public BaseObject {
public:
    RenderTile();
    ~RenderTile();
};

class SetMap {
public:
    SetMap();
    ~SetMap();

    void loadMap(const char* name);
    void loadTiles(SDL_Renderer* screen);
    void drawMap(SDL_Renderer* screen);

    // Các hàm getter và setter hỗ trợ tự động cuộn
    int getXStart() const { return gameMap.x_start; }
    void setXStart(int x) { gameMap.x_start = x; }
    int getYStart() const { return gameMap.y_start; }
    void setYStart(int y) { gameMap.y_start = y; }
    int getMaxX() const { return gameMap.max_x; }
    int getMaxY() const { return gameMap.max_y; }

    void removeTile(int x, int y);

    int getTileType(int x, int y) const;

private:
    infor_tile gameMap;
    RenderTile tileMat[MAX_TILES];
};

#endif //MAPGAME_H

