#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "player.hpp"

using namespace std;

enum GameState { START, RUNNING, PAUSED, OVER };

Uint32 previousTime = SDL_GetTicks();
Uint32 currentTime = 0;
float deltaTime = 0.0f;

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
    SDL_Texture* textureTree = window.loadTexture("res/tree.png");
    
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
    SDL_Rect spriteRoad = {0, 0, 1086, 679};

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
    player.setTexture(playerTexture);
    player.setPlayerPosition(575, 500); 
    player.setCarState(Player::CarState::STOPPED);

    //NPC car
    SDL_Rect spriteNPC;
    int textureChoice = rand() % 15;
    spriteNPC = {(rand() % 345) + 344, (rand() % 1) - 2000, 50, 100};

    //HUD
    SDL_Rect spriteSpeedometerRect = { 840, 520, 150, 150 };

    GameState gameState = GameState::START;
    bool gameRunning = true;
    SDL_Event event;
    float gameSpeed = 0.0f;
    const float MaxSpeed = 1100.0f;

    while (gameRunning)
    {
        currentTime = SDL_GetTicks();
        deltaTime = (currentTime - previousTime) / 1000.0f; 
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
                            gameSpeed == 0.0f;
                            player.setScore(0);
                            gameState = GameState::START;
                        }
                        break;
                    case SDLK_ESCAPE:
                        gameRunning = false;
                        break;
                    case SDLK_SPACE:
                        if (gameState == GameState::RUNNING)
                        {
                            player.setCarState(Player::CarState::ACCELERATE);
                            if (gameSpeed < MaxSpeed)
                            {
                                gameSpeed += 0.55f;
                            }
                        }
                        break;
                    case SDLK_RIGHT:
                        if (player.getPlayerPosition().x < 615)
                        {
                        player.setPlayerPosition(player.getPlayerPosition().x + 5, player.getPlayerPosition().y);
                        }
                        break;
                    case SDLK_LEFT:
                        if (player.getPlayerPosition().x > 350)
                        {
                            player.setPlayerPosition(player.getPlayerPosition().x - 5, player.getPlayerPosition().y);
                        }
                        break;

                }
            }
        }

        const Uint8* state = SDL_GetKeyboardState(NULL);

        if (gameState == GameState::RUNNING)
        {
            int testValue = 10 + 5; // Simple addition
            std::cout << "The game is running. Test calculation: 10 + 5 = " << testValue << std::endl;
            if(player.getCarState() == Player::CarState::ACCELERATE)
            {
            // Move the NPC car down the screen
                spriteNPC.y += static_cast<int>(gameSpeed * deltaTime);
            }
            else if(player.getCarState() == Player::CarState::DECELERATE)
            {
                if(spriteNPC.y > -1000)
                {
                    spriteNPC.y -= static_cast<int>(800 * deltaTime);
                }
            }

            // Reset NPC car position and change texture if it moves off the screen
            if(spriteNPC.y > 800)
            {
                spriteNPC.x = (rand() % 345) + 344;
                spriteNPC.y = (rand() % 1) - 2000;

                // Set a new texture for the NPC car
                int textureChoice = rand() % 15;
                // Increment player score
                player.setScore(player.getScore() + 1);
            }
            //Update positions of road stripes
            for (int i = 0; i < 5; i++)
            {
                spriteRoadStripe[i].y += static_cast<int>(gameSpeed * 0.016);
                if (spriteRoadStripe[i].y > 679)
                {
                    spriteRoadStripe[i].y = -70;
                }
            }

            //Update positions of rock and trees
            for (int i = 0; i < NumberOfRocks; i++) 
            {
                spriteRock[i].y += static_cast<int>(gameSpeed * 0.016);  
                if (spriteRock[i].y > 679) {
                    if (i == 0) 
                    {
                        spriteRock[i].x = rand() % 280;
                        spriteRock[i].y = -1000;
                    } else 
                    {
                        spriteRock[i].x = (rand() % 810) + 780;
                        spriteRock[i].y = -500;
                    }
                }
            }

            for (int i = 0; i < NumberOfTrees; i++) 
            {
                spriteTree[i].y += static_cast<int>(gameSpeed * 0.016);
                if (spriteTree[i].y > 679) {
                    if (i % 2 == 0) 
                    {
                        spriteTree[i].x = rand() % 230;
                        spriteTree[i].y = -500;
                    } else 
                    {
                        spriteTree[i].x = (rand() % 810) + 780;
                        spriteTree[i].y = -500;
                    }
                }
            }
            //Move the NPC car and check fpr collisions
            spriteNPC.y += static_cast<int>(gameSpeed * 0.016);
            if (spriteNPC.y > 800)
            {
                spriteNPC.x = (rand() % 345) + 344;
                spriteNPC.y = (rand() % 1) - 2000;
                textureChoice = rand() % 15;
                player.setScore(player.getScore() + 1);
            }
            SDL_Rect PlayerBounds = player.getPlayerPosition();
            SDL_Rect npcBounds = {344, -2000, 50, 100}; 
            if (SDL_HasIntersection(&PlayerBounds, &npcBounds))
            {
                gameState = GameState::OVER;
            }

        }

        window.clear();
        window.render(backgroundTexture);
        
        //Render road stripes
        for (int i = 0; i < 5; i++)
        {
            window.renderWithScale(textureRoadStripe, spriteRoadStripe[i].x, spriteRoadStripe[i].y, spriteRoadStripe[i].w, spriteRoadStripe[i].h);
        }
        //Render rocks and trees
        for (int i = 0; i < NumberOfRocks; i++) 
        {
            window.renderWithScale(textureRock, spriteRock[i].x, spriteRock[i].y, spriteRock[i].w, spriteRock[i].h);
        }
        for (int i = 0; i < NumberOfTrees; i++) 
        {
            window.renderWithScale(textureTree, spriteTree[i].x, spriteTree[i].y, spriteTree[i].w, spriteTree[i].h);
        }

        //Render player car
        SDL_Rect PlayerPos = player.getPlayerPosition();
        window.renderWithScale(player.getTexture(), PlayerPos.x, PlayerPos.y, 100, 100);
        
        //Render NPC car
        window.renderWithScale(textureCars[textureChoice], spriteNPC.x, spriteNPC.y, spriteNPC.w, spriteNPC.h);    
            
        window.display();
    }

    window.cleanUp();
    SDL_Quit();

    return 0;
}
    