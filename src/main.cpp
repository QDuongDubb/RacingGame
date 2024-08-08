#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <cstdlib>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "player.hpp"

using namespace std;

enum GameState { START, RUNNING, PAUSED, OVER };

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    if (IMG_Init(IMG_INIT_PNG) < 0) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return 1;
    }


    RenderWindow window("Game v1.0", 1086, 679);
    SDL_Texture* backgroundTexture = window.loadTexture("res/background.png");

    SDL_Texture* textureCars[15];
    textureCars[0] = window.loadTexture("res/carOne.png");
    textureCars[1] = window.loadTexture("res/carTwo.png");
    textureCars[2] = window.loadTexture("res/carThree.png");
    textureCars[3] = window.loadTexture("res/carFour.png");
    textureCars[4] = window.loadTexture("res/carFive.png");
    textureCars[5] = window.loadTexture("res/carSix.png");
    textureCars[6] = window.loadTexture("res/carSeven.png");
    textureCars[7] = window.loadTexture("res/carEight.png");
    textureCars[8] = window.loadTexture("res/carNine.png");
    textureCars[9] = window.loadTexture("res/carTen.png");
    textureCars[10] = window.loadTexture("res/carEleven.png");
    textureCars[11] = window.loadTexture("res/carTwelve.png");
    textureCars[12] = window.loadTexture("res/carThirteen.png");
    textureCars[13] = window.loadTexture("res/carFourteen.png");
    textureCars[14] = window.loadTexture("res/carFifteen.png");
    textureCars[15] = window.loadTexture("res/carSixteen.png");

    SDL_Texture* textureRoadStripe = window.loadTexture("res/roadStripe.png");
    SDL_Texture* textureRock = window.loadTexture("res/rock.png");
    
    Player player;
    player.setTexture(textureCars[0]);
    player.setPlayerPosition(575, 500); 
    player.setCarState(Player::CarState::STOPPED);

    int textureChoice = rand() % 16;

    GameState gameState = GameState::START;
    bool gameRunning = true;
    SDL_Event event;
    float gameSpeed = 0.0f;
    const float MaxSpeed = 1100.0f;

    while (gameRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                gameRunning = false;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_RETURN:
                        if (gameState == START || gameState ==  PAUSED)
                        {
                            gameState = RUNNING;
                        }
                        else if (gameState == RUNNING)
                        {
                            gameState = PAUSED;
                        }
                        else if (gameState == OVER)
                        {
                            player.setPlayerPosition(575, 500);
                            gameSpeed == 0.0f;
                            player.setScore(0);
                            gameState = START;
                        }
                        break;
                    case SDLK_ESCAPE:
                        gameRunning = false;
                        break;
                    case SDLK_SPACE:
                        if (gameState == RUNNING)
                        {
                            player.setCarState(Player::CarState::ACCELERATE);
                            if (gameSpeed < MaxSpeed)
                            {
                                gameSpeed += 0.55f;
                            }
                        }
                        break;
                }
            }
            if (gameState == RUNNING)
            {
                SDL_Rect PlayerBounds = player.getPlayerPosition();
                SDL_Rect npcBounds = {344, -2000, 50, 100};
                if (SDL_HasIntersection(&PlayerBounds, &npcBounds))
                {
                    gameState = OVER;
                }

            }

            window.clear();
            window.render(backgroundTexture);
            
            window.renderWithScale(textureCars[0], 575, 500, 100, 100);
            
            
            window.display();
        }
    }

    window.cleanUp();
    SDL_Quit();

    return 0;
}
    