//
// Created by navid on 13/05/2021.
//
#include "Window.h"

using namespace std;

Window::Window(const string &windowName, unsigned int sizeX, unsigned int sizeY) :
_X(sizeX),
_Y(sizeY)
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    _actualWindow = SDL_CreateWindow(windowName.c_str(),
                                     SDL_WINDOWPOS_UNDEFINED,
                                     SDL_WINDOWPOS_UNDEFINED,
                                     (int) sizeX, (int) sizeY,  0);
    if (_actualWindow == nullptr) {
        std::cout << "Window::Window() :" << SDL_GetError()
                  << std::endl;
    }
    _renderer = SDL_CreateRenderer(_actualWindow, -1, SDL_RENDERER_ACCELERATED
                                                                        | SDL_RENDERER_PRESENTVSYNC
                                                                        | SDL_RENDERER_TARGETTEXTURE);

    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1"); // check usefulness

    _defaultTexture = SDL_CreateTexture(_renderer,
                                SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_TARGET,
                                _X, _Y);
    SDL_SetTextureBlendMode(_defaultTexture, SDL_BLENDMODE_BLEND);
    _backgroundTexture = SDL_CreateTexture(_renderer,
                                SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_TARGET,
                                _X, _Y);
    SDL_SetTextureBlendMode(_backgroundTexture, SDL_BLENDMODE_BLEND);
    _auxTexture = SDL_CreateTexture(_renderer,
                                    SDL_PIXELFORMAT_RGBA8888,
                                    SDL_TEXTUREACCESS_TARGET,
                                    _X, _Y);
    SDL_SetTextureBlendMode(_backgroundTexture, SDL_BLENDMODE_BLEND);

    SDL_SetRenderTarget(_renderer, _defaultTexture);

    //SDL_SetWindowFullscreen(_actualWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
    _font = TTF_OpenFont("ressource/font/arial.ttf", 25);
}


Window::~Window() {
    SDL_DestroyTexture(_backgroundTexture);
    SDL_DestroyTexture(_defaultTexture);
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_actualWindow);

    for (auto d : _hashmap) {
        SDL_DestroyTexture(d.second);
    }

    TTF_CloseFont(_font);

    TTF_Quit();
    SDL_Quit();
}

void Window::setTitle(const std::string &windowTitle) {
    SDL_SetWindowTitle(_actualWindow, windowTitle.c_str());
}

void Window::drawIMG(int x, int y, const string &name) {
    open("ressource/" + name);
    drawIMG("ressource/" + name, x, y);
}

void Window::scaleIMG(int x, int y, int width, int height, const string &name) {
    open("ressource/" + name);
    SDL_Texture * texture = IMG_LoadTexture(_renderer, ("ressource/" + name).c_str());

    if (texture == NULL) {
        cout << "Window::drawTexture() : " << SDL_GetError() << endl;
    }

    SDL_Rect p;
    p.x = x;
    p.y = y;
    p.w = width;
    p.h = height;

    SDL_RenderCopy(_renderer, texture, NULL, &p);
}

void Window::refresh() {
    SDL_SetRenderTarget(_renderer, NULL);
    SDL_RenderCopy(_renderer, _backgroundTexture, NULL, NULL);
    SDL_RenderCopy(_renderer, _defaultTexture, NULL, NULL);

    SDL_RenderPresent(_renderer);

    SDL_SetRenderTarget(_renderer, _defaultTexture);
    SDL_RenderClear(_renderer);

    //Sleep(20);
}

void Window::clear() {
    SDL_Texture * texture = IMG_LoadTexture(_renderer, "ressource/image/clear.bmp");

    if (texture == NULL) {
        cout << "Window::drawTexture() : " << SDL_GetError() << endl;
    }

    SDL_RenderCopy(_renderer, texture, NULL, NULL);

    SDL_DestroyTexture(texture);
}

void Window::drawPartIMG(int x, int y, unsigned int a, unsigned int b, unsigned int c, unsigned int d, const string &name) {
    open("ressource/" + name);
    drawPartIMG("ressource/" + name, x, y, a, b, c, d);
}

void Window::open(string file) {
    if (_hashmap.find(file) != _hashmap.end())
        return;
    SDL_Texture* texture = IMG_LoadTexture(_renderer, file.c_str());
    if (texture != NULL) {
        _hashmap.insert({file, texture});
    } else {
        cout << "Window::open() : " << SDL_GetError() << endl;
    }
}

void Window::drawIMG(const string &name, int x, int y) {
    SDL_Texture* texture = _hashmap.at(name);

    if (texture == NULL) {
        cout << "Window::drawIMG() : " << SDL_GetError() << endl;
    }

    SDL_Rect p;
    p.x = x;
    p.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &(p.w), &(p.h));

    SDL_RenderCopy(_renderer, texture, NULL, &p);
}

void Window::drawPartIMG(const string &name, int x, int y, unsigned int a, unsigned int b, unsigned int c, unsigned int d) {
    SDL_Texture* texture = _hashmap.at(name);

    if (texture == NULL) {
        cout << "Window::drawIMG() : " << SDL_GetError() << endl;
    }

    SDL_Rect p;
    p.x = x;
    p.y = y;
    p.w = c;
    p.h = d;

    SDL_Rect r;
    r.x = a;
    r.y = b;
    r.w = c;
    r.h = d;

    SDL_RenderCopy(_renderer, texture, &r, &p);
}

void Window::changeFont(const string& name, unsigned int points) {
    TTF_CloseFont(_font);
    _font = TTF_OpenFont(("ressource/font/" + name + ".ttf").c_str(), points);
}

void Window::changeColor( Uint8 r, Uint8 v, Uint8 b) {
    _color = {r, v, b};
}

void Window::writeText(int x,int y, const string& s) {
    SDL_Surface * text = TTF_RenderText_Solid(_font,s.c_str(), _color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, text);

    SDL_Rect p;
    p.x = x;
    p.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &(p.w), &(p.h));

    SDL_RenderCopy(_renderer, texture, NULL, &p);
    SDL_FreeSurface(text);
    SDL_DestroyTexture(texture);
}



unsigned int Window::getX() const {
    return _X;
}

unsigned int Window::getY() const {
    return _Y;
}

void Window::debug() {
    cout << _hashmap.size() << endl;
}

void Window::drawOn(unsigned int layer) {
    switch(layer) {
        case BACKGROUND :
            SDL_SetRenderTarget(_renderer, _backgroundTexture);
            _currentTexture = _backgroundTexture;
            break;
        case DEFAULT :
            SDL_SetRenderTarget(_renderer, _defaultTexture);
            _currentTexture = _defaultTexture;
            break;
        default :
            break;
    }
}
/* //!\\ SDL_GetRenderTarget wrong return bug isn't patched in SDL2 */
void Window::shift(int x, int y) {
    SDL_Rect p = {x, y, static_cast<int>(_X), static_cast<int>(_Y)};
    SDL_Texture* currentTexture = SDL_GetRenderTarget(_renderer);

    SDL_SetRenderTarget(_renderer, _auxTexture);
    SDL_RenderCopy(_renderer, currentTexture, NULL, NULL);

    SDL_SetRenderTarget(_renderer, currentTexture);
    clear();
    SDL_RenderCopy(_renderer, _auxTexture, NULL, &p);
}

void Window::textSizeOf(std::string s, int& w, int& h) {
    TTF_SizeText(_font, s.c_str(), &w, &h);
}

bool Window::exists(std::string name) const {
    return !(_hashmap.find(name) == _hashmap.end());
}