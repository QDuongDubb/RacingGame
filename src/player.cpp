#include "Player.hpp"

int Player::getScore() {
    return m_PlayerScore;
}

int Player::getLives() {
    return m_Lives;
}

void Player::setScore(int score) {
    m_PlayerScore = score;
}

void Player::setLives(int lives) {
    m_Lives = lives;
}

SDL_Texture* Player::getTexture() {
    return m_PlayerTexture;
}

void Player::setTexture(SDL_Renderer* renderer, const char* filePath) {
    SDL_Surface* tempSurface = IMG_Load(filePath);
    if (tempSurface == nullptr) {
        // Handle error
        return;
    }
    m_PlayerTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
}

void Player::setTexture(SDL_Texture* texture) {
    m_PlayerTexture = texture;
}

void Player::setCarState(CarState state) {
    m_CarState = state;
}

Player::CarState Player::getCarState() {
    return m_CarState;
}

SDL_Rect Player::getPlayerPosition() {
    return m_PlayerRect;
}

void Player::setPlayerPosition(int x, int y) {
    m_PlayerRect.x = x;
    m_PlayerRect.y = y;
}
