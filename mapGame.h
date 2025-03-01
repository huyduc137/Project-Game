#ifndef MAPGAME_H
#define MAPGAME_H

#include "BaseObject.h"

struct infor_tile {
    int x_start , y_start;  // vị trí xét trong bản đồ khi nhân vật di chuyển
    int max_x = 0 , max_y = 0;     // chiều dài và chiều rộng của bản đồ
    int tile[MAX_MAP_Y][MAX_MAP_X];  // lưu các định dạng của Tiles
    const char* fileName; // ten cac file tiles
};

class renderTile : public BaseObject {
public:
    renderTile(){;}
    ~renderTile(){;}
};

class setMap {
public:
    setMap(){;}
    ~setMap(){;}
    void loadMap(const char* name);           // load nhan dang file txt vao matrix
    void loadTiles(SDL_Renderer* screen);   // load san image tiles vao matrix
    void drawMap(SDL_Renderer* screen);    // ve anh
private:
    infor_tile gameMap;    // luu cac thong tin cua mot o tile
    renderTile tileMat[TILE_SIZE];   // fill anh vao tileMat
};


#endif //MAPGAME_H
