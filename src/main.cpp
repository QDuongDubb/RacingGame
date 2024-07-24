#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "RenderWindow.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    if (IMG_Init(IMG_INIT_PNG) < 0) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return 1;
    }

    RenderWindow window("Game v1.0", 800, 600);
    SDL_Texture* backgroundTexture = window.loadTexture("res/background.png");

    bool gameRunning;
    SDL_Event event;
    while (gameRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                gameRunning = false;
            }

            window.clear();
            window.render(backgroundTexture);
            window.display();
        }
    }
    

    window.cleanUp();
    SDL_Quit();

    return 0;
}
    