cmake_minimum_required(VERSION 3.9)
project(ARPG_StoryBoard CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}-static-libgcc -static-libstdc++")

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wno-dev") #Affiche TOUS les warnings en mode debug
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -O3")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/SDL2/cmake") #chemin pour accéder au fichier cmake
#qui vont trouver les différents fichiers nécessaire pour utiliser SDL2


set(SDL2_IMAGE_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/SDL2/include")
set(SDL2_IMAGE_LIBRARY "${PROJECT_SOURCE_DIR}/SDL2/lib/libSDL2_image.dll.a")

set(SDL2_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/SDL2/include")
set(SDL2_LIBRARY "${PROJECT_SOURCE_DIR}/SDL2/lib/libSDL2.dll.a")
#TFF
set(SDL2_TTF_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/SDL2/include")
set(SDL2_TTF_LIBRARY "${PROJECT_SOURCE_DIR}/SDL2/lib/libSDL2_ttf.dll.a")

find_package(SDL2 REQUIRED)
find_package(SDL2_Image REQUIRED)
#TFF
find_package(SDL2_ttf REQUIRED)

file(GLOB_RECURSE SOURCES
        src/*.cpp
        src/*/*.cpp
        src/*/*/*.cpp
        src/*/*/*/*.cpp
        src/*/*/*/*/*.cpp
        )

add_executable(Dice_Game_Project ${SOURCES}
        src/online/Server.h
        src/online/Client.h)
#TFF
include_directories(${PROJECT_SOURCE_DIR}/src ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR}) #inclusion des dossier nécessaire pour le
#développement avec SDL2
#TFF
target_link_libraries(Dice_Game_Project ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY}) #inclusion des bibliothèques nécessaire pour
#le développement avec SDL2

if(WIN32)
        target_link_libraries(Dice_Game_Project wsock32 ws2_32)
elseif(UNIX)
        target_link_libraries(Dice_Game_Project pthread)
endif()