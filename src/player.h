#pragma once

#include <SDL.h>
#include <SDL_image.h>

class Player
{
public:
    enum CarState { ACCELERATE, DECELERATE, STOPPED };

    int getScore();
    void setScore(int score);
    SDL_Texture* getTexture();
    void setTexture(SDL_Renderer* renderer, const char* filePath);
    void setCarState(CarState state);
    CarState getCarState();
    SDL_Rect getPlayerPosition();
    void setPlayerPosition(int x, int y);

private:
    int m_PlayerScore = 0;
    SDL_Texture* m_PlayerTexture = nullptr;
    CarState m_CarState;
    SDL_Rect m_PlayerRect = {0, 0, 0, 0};
};



