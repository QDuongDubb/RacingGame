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
#include "RenderText.hpp"
#include "EventManager.hpp"
#include "AudioManager.hpp"

using namespace std;



int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
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
    
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        return 1;
    }
    

    RenderWindow window("Mad Racer", 1086, 679);
    SDL_Texture* backgroundTexture = window.loadTexture("res/background.png");
    SDL_Texture* gameStartTexture = window.loadTexture("res/START.png");
    SDL_Texture* gameOverTexture = window.loadTexture("res/OVER.png");
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

    SDL_Texture* texturePlus10 = window.loadTexture("res/plus10.png");
    
    SDL_Texture* playerTexture = window.loadTexture("res/carOne.png");
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
    
    Player player;
    SDL_Rect PlayerPos;
    player.setTexture(playerTexture);
    player.setPlayerPosition(575, 500); 
    player.setCarState(Player::CarState::STOPPED);

    //NPC car
    SDL_Rect spriteNPC;
    int textureChoice = rand() % 15;
    spriteNPC = {(rand() % 345) + 344, (rand() % 1) - 2000, 50, 100};
        

    //GetPoint
    SDL_Rect spriteGetPoint;
    spriteGetPoint = {(rand() % 345) + 344, (rand() % 1) - 2000, 50, 100};

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
    TextRenderer textRenderer(renderer);
    if (!textRenderer.loadFont("fonts/Bungee-Regular.ttf", 28)) 
    {
        return 1;
    }
    string scoreText;
    string liveText;
    SDL_Color White = {255, 255, 255};
    SDL_Color Pink = {255, 0, 255};
    SDL_Color Cyan = {0, 255, 255};

    GameState gameState = GameState::START;

    bool gameRunning = true;
    float gameSpeed = 0.15f;
    float npcSpeed = 1;
    const float MaxSpeed = 1100.0f;
    int lives = 3;
    string lastScoreString;
    string LiveLost;
    bool IsMusicPlaying = false;

    //Audio Manager
    AudioManager audioManager;
    if (!audioManager.init()) {
        return 1;
    }

    while (gameRunning)
    {
        EventManager eventManager;
        eventManager.handleEvents(gameRunning, gameState, player, gameSpeed, MaxSpeed);

        if (gameState == GameState::RUNNING)
        {
            spriteNPC.y += static_cast<int>(npcSpeed);
            spriteGetPoint.y += static_cast<int>(gameSpeed + 1);

            if(player.getCarState() == Player::CarState::ACCELERATE)
            {
                // Move the NPC car down the screen
                spriteNPC.y += static_cast<int>(npcSpeed * (gameSpeed + 0.1));
                spriteGetPoint.y += static_cast<int>(gameSpeed + 0.3);
            }
            else if(player.getCarState() == Player::CarState::DECELERATE)
            {
                if(spriteNPC.y > -1000)
                {
                    spriteNPC.y -= static_cast<int>(npcSpeed * (gameSpeed - 0.1));
                    spriteGetPoint.y -= static_cast<int>(gameSpeed - 0.3);
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
            

            // Reset GetPoint position and change texture if it moves off the screen
            if(spriteGetPoint.y > 700)
            {
                spriteGetPoint.x = (rand() % 345) + 344;
                spriteGetPoint.y = (rand() % 1) - 2000;
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
            if (SDL_HasIntersection(&npcBounds, &playerModBounds))
            {
                lives--;
                if(lives <=0)
                {
                    gameState = GameState::OVER;
                }
                else
                {
                    gameState = GameState::FOULED;
                }
            }
            
            SDL_Rect Point10Bounds = spriteGetPoint; 
            if (SDL_HasIntersection(&Point10Bounds, &playerModBounds))
            {
                player.setScore(player.getScore() + 10);
                spriteGetPoint.x = (rand() % 345) + 344;
                spriteGetPoint.y = (rand() % 1) - 2000;
            }

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

            // //Render GetPoint
            window.renderWithScale(texturePlus10, spriteGetPoint.x, spriteGetPoint.y, 100, 100);

            // //Render Speedometer
            window.renderWithScale(textureSpeedometer, spriteSpeedometerRect.x, spriteSpeedometerRect.y, spriteSpeedometerRect.w, spriteSpeedometerRect.h);

            scoreText = "Score: " + to_string(player.getScore());
            liveText = "Lives: " + to_string(lives);
            textRenderer.renderText(scoreText, 10, 10, White);
            textRenderer.renderText(liveText, 10, 40, White);

            window.display();
        }

        if(gameState == GameState::START)
        {
            window.clear();
            window.render(gameStartTexture);
            window.display();

            if(!IsMusicPlaying)
            {
                audioManager.loadMusic("intro","audio/Intro.wav");
                audioManager.playMusic("intro", -1);
                IsMusicPlaying = true;
            }
        }  
        else if (IsMusicPlaying)  
        {
            audioManager.stopMusic();  
            IsMusicPlaying = false;    
        }
        if (gameState == GameState::FOULED)
        {
            player.setPlayerPosition(575, 500);
            spriteNPC.x = (rand() % 345) + 344;
            spriteNPC.y = (rand() % 1) - 2000;
            LiveLost = "You lose a live !!";
            int LiveLostWidth, LiveLostHeight;

            TTF_SizeText(textRenderer.getFont(), LiveLost.c_str(), &LiveLostWidth, &LiveLostHeight);

            int centerLiveLostX = (1086 / 2) - (LiveLostWidth / 2);
            int centerLiveLostY = (679 / 2) - (LiveLostHeight / 2);
            textRenderer.renderText(LiveLost, centerLiveLostX, centerLiveLostY, Pink);
            textRenderer.renderText(LiveLost, centerLiveLostX + 2, centerLiveLostY + 2, Cyan);
            window.display();
            gameSpeed = 0.00f;
            cout << lives << endl;
        }
        if(gameState == GameState::OVER)
        {
            lastScoreString = "Your Score: " + to_string(player.getScore());
            int textWidthOver, textHeightOver;
            
            TTF_SizeText(textRenderer.getFont(), lastScoreString.c_str(), &textWidthOver, &textHeightOver);

            // Calculate the position to center the text
            int centerX = (1086 / 2) - (textWidthOver / 2); 
            int centerY = (679 / 2) - (textHeightOver / 2); 

            window.clear();
            window.render(gameOverTexture);
            textRenderer.renderText(lastScoreString, centerX, centerY, Pink);
            textRenderer.renderText(lastScoreString, centerX + 2, centerY + 2, Cyan);
            window.display();
            player.setPlayerPosition(575, 500);
            
            
            spriteNPC.x = (rand() % 345) + 344;
            spriteNPC.y = (rand() % 1) - 2000;
            
            gameSpeed = 0.00f;
            lives = 3;
        }
    }

    audioManager.cleanUp();
    window.cleanUp();
    SDL_Quit();

    return 0;
}
    