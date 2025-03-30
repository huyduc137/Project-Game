#ifndef COMMONFUNC_H
#define COMMONFUNC_H

#define MAX_MAP_X 10
#define MAX_MAP_Y 197
#define MAX_TILES 20
#define TILE_SIZE 65

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

// khai báo cửa sổ
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Event event;

// hiệu ứng âm thanh#ifndef COMMONFUNC_H
#define COMMONFUNC_H

#define MAX_MAP_X 10
#define MAX_MAP_Y 197
#define MAX_TILES 20
#define TILE_SIZE 65

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

// khai báo cửa sổ
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Event event;

// hiệu ứng âm thanh
extern Mix_Chunk* g_sound_bullet;
extern Mix_Chunk* g_sound_explosion;
extern Mix_Chunk* g_sound_click;

// chiều dài rộng của cửa sổ
const int SCREEN_WIDTH = 650;
const int SCREEN_HEIGHT = 870;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 170;
const int COLOR_KEY_B = 180;

const int SPEED_PLANE = 7;
const int SPEED_BULLET = 80;
const int SIZE_PLANE_MAIN = 120;
const int POINT = 5;

#endif //COMMONFUNC_H
