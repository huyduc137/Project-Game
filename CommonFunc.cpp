#include "CommonFunc.h"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Event event;

Mix_Chunk* g_sound_bullet = nullptr;
Mix_Chunk* g_sound_explosion = nullptr;
Mix_Chunk* g_sound_click = nullptr;
