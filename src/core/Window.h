//
// Created by navid on 13/05/2021.
//

#ifndef PROJECTTT_WINDOW_H
#define PROJECTTT_WINDOW_H

#include <iostream>
#include <unordered_map>
#include "SDL2/SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#define BACKGROUND (unsigned int)0
#define DEFAULT (unsigned int)1



typedef std::string string;
typedef std::unordered_map<string, SDL_Texture*> hashmap;

class Window {
public :
    Window(const string &windowName, unsigned int sizeX, unsigned int sizeY);
    void setTitle(const string &windowTitle);
    void drawOn(unsigned int layer);
    void drawIMG(int x, int y, const string &name);
    void scaleIMG(int x, int y, int width, int height, const string &name);
    void debug();
    void drawPartIMG(int x, int y, unsigned int a, unsigned int b, unsigned int c, unsigned int d, const string &name);
    void refresh();
    Window() = delete;
    ~Window();
    void clear();
    bool exists(std::string name) const;
    void writeText(int x,int y, const string& s);
    void changeFont(const string& name, unsigned int points);
    void changeColor( Uint8 r, Uint8 v, Uint8 b);
    unsigned int getY() const;
    unsigned int getX() const;
    void textSizeOf(std::string s, int& w, int& h);
    void shift(int x, int y);
private :
    SDL_Texture* _backgroundTexture = nullptr;
    SDL_Texture* _defaultTexture = nullptr;
    SDL_Texture* _currentTexture = nullptr;

    SDL_Texture * _auxTexture = nullptr; // auxiliary texture, no precise use

    SDL_Window *_actualWindow;
    SDL_Renderer *_renderer;

    TTF_Font * _font;
    SDL_Color _color = { 255, 255, 255 };

    hashmap _hashmap = hashmap();

    unsigned int _X = 0, _Y = 0;

    void drawIMG(const string &name, int x, int y);
    void drawPartIMG(const string &name, int x, int y, unsigned int a, unsigned int b, unsigned int c, unsigned int d);
    void open(string file);

};


#endif //PROJECTTT_WINDOW_H
