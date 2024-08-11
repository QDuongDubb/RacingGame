#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "RenderWindow.hpp"
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
    if (TTF_Init() < 0) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return 1;
    }

    RenderWindow window("Game v1.0", 1086, 679);
    SDL_Texture* backgroundTexture = window.loadTexture("res/background.png");
    SDL_Texture* menuTexture = window.loadTexture("res/image.png");
    SDL_Renderer* renderer =window.getRenderer();

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
    SDL_Texture* textureTree = window.loadTexture("res/tree.png");

    SDL_Texture* textureSpeedometer = window.loadTexture("res/speedometer.png");
    
    //Rock
    const int NumberOfRocks = 30;
    SDL_Rect spriteRock[NumberOfRocks];
    for (int i = 0; i < NumberOfRocks; i++)
    {
        spriteRock[i].w = 100;
        spriteRock[i].h = 70;
        if (i == 0) 
        {
            spriteRock[i].x = rand() % 280;
            spriteRock[i].y = (rand() % 900) - 1500;
        } else
        {
            spriteRock[i].x = (rand() % 770) + 710;
            spriteRock[i].y = (rand() % 900) - 900;
        }
    }

    //Tree
    const int NumberOfTrees = 20;
    SDL_Rect spriteTree[NumberOfTrees];
    for (int i = 0; i < NumberOfTrees; i++)
    {
        spriteTree[i].w = 90;  
        spriteTree[i].h = 60;
        if (i % 2 == 0) {
            spriteTree[i].x = rand() % 230;
            spriteTree[i].y = (rand() % 1000) - 500;
        } else {
            spriteTree[i].x = (rand() % 810) + 780;
            spriteTree[i].y = (rand() % 1000) - 500;
        }
    }

    //Road Stripes
    SDL_Rect spriteRoadStripe[5];
    for (int i = 0; i < 5; i++)
    {
        spriteRoadStripe[i].w = 10;
        spriteRoadStripe[i].h = 50;
        spriteRoadStripe[i].x = 538;
        spriteRoadStripe[i].y = i * 150;
    }

    //Player car
    SDL_Texture* playerTexture = window.loadTexture("res/carOne.png");
    Player player;
    SDL_Rect PlayerPos;
    player.setTexture(playerTexture);
    player.setPlayerPosition(575, 500); 
    player.setCarState(Player::CarState::STOPPED);

    //NPC car
    SDL_Rect spriteNPC;
    int textureChoice = rand() % 15;
    spriteNPC = {(rand() % 345) + 344, (rand() % 1) - 2000, 50, 100};

    //Speedometer
    SDL_Rect spriteSpeedometerRect = { 840, 520, 150, 150 };
    //Speedometer needle
    SDL_Point needelePoints[4] = 
    {
        {915, 603},
        {920, 673},
        {910, 673},
        {915, 603}
    };

    //Load Fonts
    TTF_Font* font = TTF_OpenFont("fonts/Bungee-Regular.ttf", 28);
    if (!font) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return 1;
    }
    string scoreText;
    SDL_Color White = {255, 255, 255};
    SDL_Surface* HighScore;
    SDL_Texture* HighScoreTexture;
    SDL_Rect HighScoreRect;

    GameState gameState = GameState::START;
    bool gameRunning = true;
    SDL_Event event;
    float gameSpeed = 0.15f;
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
                        if (gameState == GameState::START || gameState ==  GameState::PAUSED)
                        {
                            printf("Transitioning to RUNNING state...\n");  // Debug
                            gameState = GameState::RUNNING;
                        }
                        else if (gameState == GameState::RUNNING)
                        {
                            gameState = GameState::PAUSED;
                        }
                        else if (gameState == GameState::OVER)
                        {
                            player.setPlayerPosition(575, 500);
                            spriteNPC.x = (rand() % 345) + 344;
                            spriteNPC.y = (rand() % 1) - 2000;
                            gameSpeed == 0.00f;
                            player.setScore(0);
                            gameState = GameState::START;
                        }
                        break;
                    case SDLK_ESCAPE:
                        gameRunning = false;
                        break;
                    case SDLK_UP:
                        if (gameState == GameState::RUNNING)
                        {
                            player.setCarState(Player::CarState::ACCELERATE);
                            if (gameSpeed < MaxSpeed)
                            {
                                gameSpeed += 0.55f;
                            }
                        }
                        break;
                    case SDLK_DOWN:
                        if (gameState == GameState::RUNNING)
                        {
                            player.setCarState(Player::CarState::DECELERATE);
                            if (gameSpeed > 0.00f)
                            {
                                gameSpeed -= 0.55f;
                            }
                        }
                        break;
                    case SDLK_RIGHT:
                        if (gameState == GameState::RUNNING)
                        {
                            if (player.getPlayerPosition().x < 630)
                            {
                            player.setPlayerPosition(player.getPlayerPosition().x + 5, player.getPlayerPosition().y);
                            }
                            break;
                        }
                    case SDLK_LEFT:
                        if (gameState == GameState::RUNNING)
                        {
                            if (player.getPlayerPosition().x > 350)
                            {
                                player.setPlayerPosition(player.getPlayerPosition().x - 5, player.getPlayerPosition().y);
                            }
                        break;
                        }
                }
            }
        }

        if (gameState == GameState::RUNNING)
        {
            
            spriteNPC.y += static_cast<int>(gameSpeed + 1);
            if(player.getCarState() == Player::CarState::ACCELERATE)
            {
            // Move the NPC car down the screen
                spriteNPC.y += static_cast<int>(gameSpeed + 0.3);
            }
            else if(player.getCarState() == Player::CarState::DECELERATE)
            {
                if(spriteNPC.y > -1000)
                {
                    spriteNPC.y -= static_cast<int>(gameSpeed - 0.3);
                }
            }

            // Reset NPC car position and change texture if it moves off the screen
            if(spriteNPC.y > 700)
            {
                spriteNPC.x = (rand() % 345) + 344;
                spriteNPC.y = (rand() % 1) - 2000;
                textureChoice = rand() % 15;
                player.setScore(player.getScore() + 1);
            }

            //Update positions of road stripes
            for(int i = 0; i < 5; i++)
            {
                //spriteRoadStripe[i].y += static_cast<int>(gameSpeed * deltaTime);
                spriteRoadStripe[i].y += 2;
                if(spriteRoadStripe[i].y > 679)
                {
                    spriteRoadStripe[i].y = -70;
                }
            }


            //Update positions of rock and trees
            for(int i = 0; i < NumberOfRocks; i++)
            {
                //spriteRock[i].y += static_cast<int>((gameSpeed / 1.5) * deltaTime);
                spriteRock[i].y += 2.5;
                if(spriteRock[i].y > 679)
                {
                    if(i == 0)
                    {
                        spriteRock[i].x = rand() % 280;
                        spriteRock[i].y = -1000;
                    }
                    else
                    {
                        spriteRock[i].x = (rand() % 810) + 780;
                        spriteRock[i].y = -500; 
                    }
                }
            }

            for(int i = 0; i < NumberOfTrees; i++)
            {
                spriteTree[i].y += 2.5;
                if(spriteTree[i].y > 800)
                {
                    if(i == 0)
                    {
                        spriteTree[i].x = rand() % 280;
                        spriteTree[i].y = -200; 
                    }
                    else
                    {
                        spriteTree[i].x = (rand() % 770) + 750;
                        spriteTree[i].y = -200; 
                    }
                }
            }

            //Move the NPC car and check fpr collisions
            // Get the player's bounding box
            SDL_Rect playerBounds = player.getPlayerPosition();
            SDL_Rect playerModBounds = {
                playerBounds.x + 10,
                playerBounds.y + 10,
                40,
                90
            };

            // Get the NPC's bounding box
            SDL_Rect npcBounds = spriteNPC; 
            // Check for collision
            if (SDL_HasIntersection(&npcBounds, &playerModBounds))
            {
                gameState = GameState::OVER;
            }


        }
        if(gameState == GameState::START)
        {
            window.clear();
            window.render(menuTexture);
            window.display();
        }
        

        if(gameState == GameState::RUNNING)
        {
            printf("Game is in RUNNING state...\n");  // Debug
            window.clear();
            //Render background
            window.render(backgroundTexture); 
            //Render road stripes
            for (int i = 0; i < 5; i++)
            {
                window.renderWithScale(textureRoadStripe, spriteRoadStripe[i].x, spriteRoadStripe[i].y, spriteRoadStripe[i].w, spriteRoadStripe[i].h);
            }

            // //Render rocks and trees
            for (int i = 0; i < NumberOfRocks; i++) 
            {
                window.renderWithScale(textureRock, spriteRock[i].x, spriteRock[i].y, spriteRock[i].w, spriteRock[i].h);
            }
            for (int i = 0; i < NumberOfTrees; i++) 
            {
                window.renderWithScale(textureTree, spriteTree[i].x, spriteTree[i].y, spriteTree[i].w, spriteTree[i].h);
            }

            // //Render player car
            PlayerPos = player.getPlayerPosition();
            window.renderWithScale(player.getTexture(), PlayerPos.x, PlayerPos.y, 50, 100);
            
            // //Render NPC car
            window.renderWithScale(textureCars[textureChoice], spriteNPC.x, spriteNPC.y, 50, 100); 

            // //Render Speedometer
            window.renderWithScale(textureSpeedometer, spriteSpeedometerRect.x, spriteSpeedometerRect.y, spriteSpeedometerRect.w, spriteSpeedometerRect.h);
            
            // //Render HUD
            scoreText = "Score: " + to_string(player.getScore());
            White = {255, 255, 255};
            
            // SDL_FreeSurface(HighScore);
            // SDL_DestroyTexture(HighScoreTexture);

            HighScore = TTF_RenderText_Solid(font, scoreText.c_str(), White);
            HighScoreTexture = SDL_CreateTextureFromSurface(renderer, HighScore);

            HighScoreRect = {10, 10, HighScore->w, HighScore->h};
            SDL_RenderCopy(renderer, HighScoreTexture, NULL, &HighScoreRect);

            window.display();
        }
    }

    window.cleanUp();
    SDL_Quit();

    return 0;
}
    