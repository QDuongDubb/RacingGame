#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

#include "RenderWindow.hpp"

using namespace std;

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
    :window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        cout << "Window failed to init. Error: " << SDL_GetError() << endl;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);
    if (texture == NULL)
    {
        cout << "Failed to load texture. Error: " << SDL_GetError() << endl;
    }
    return texture;
}


void RenderWindow::cleanUp()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Renderer* RenderWindow::getRenderer() const
{
    return renderer;
}

void RenderWindow::clear() 
{
    SDL_RenderClear(renderer);
}

void RenderWindow::render(SDL_Texture* p_tex)
{
    SDL_RenderCopy(renderer, p_tex, NULL, NULL);
}

void RenderWindow::renderWithScale(SDL_Texture* p_tex, int x, int y, int width, int height)
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = width;
    dest.h = height;
    SDL_RenderCopy(renderer, p_tex, NULL, &dest);
}
void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}