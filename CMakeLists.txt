cmake_minimum_required(VERSION 3.30)
project(project_game)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)
set(SDL2_PATH "D:/SDLsetup/SDL2-devel-2.30.10-mingw/SDL2-2.30.10/x86_64-w64-mingw32")
set(SDL2_IMAGE_PATH "D:/SDL_ImageSetup/SDL2_image-devel-2.8.4-mingw/SDL2_image-2.8.4/x86_64-w64-mingw32")
set(SDL2_TTF_PATH "D:/SDL_ttfSetup/SDL2_ttf-devel-2.22.0-mingw/SDL2_ttf-2.22.0/x86_64-w64-mingw32")
set(SDL2_MIXER_PATH "D:/SDL_mixerSetup/SDL2_mixer-devel-2.8.1-mingw/SDL2_mixer-2.8.1/x86_64-w64-mingw32")
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR})

add_executable(project_game main.cpp
        CommonFunc.h
        BaseObject.h
        CommonFunc.cpp
        BaseObject.cpp
        mapGame.h
        mapGame.cpp
        Character.h
        Character.cpp)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES})
