#ifndef COMMONFUNC_H_
#define COMMONFUNC_H_


# define TILE_SIZE 64
# define TILE_MAX 20
# define MAX_MAP_X 400
# define MAX_MAP_Y 10

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Event event;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 170;
const int COLOR_KEY_B = 180;



#endif //COMMONFUNC_H_
