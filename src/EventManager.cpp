#include "EventManager.hpp"
#include "player.hpp"

EventManager::EventManager() {}

void EventManager::handleEvents(bool& gameRunning, GameState& gameState, Player& player, float& gameSpeed, const float MaxSpeed) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            gameRunning = false;
        }
        else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_RETURN:
                    if (gameState == GameState::START || gameState == GameState::PAUSED) {
                        gameState = GameState::RUNNING;
                    }
                    else if (gameState == GameState::RUNNING) {
                        gameState = GameState::PAUSED;
                    }
                    else if (gameState == GameState::OVER) {
                        gameState = GameState::START;
                        player.setScore(0);
                    }
                    break;
                case SDLK_ESCAPE:
                    gameRunning = false;
                    break;
                case SDLK_UP:
                    if (gameState == GameState::RUNNING) {
                        player.setCarState(Player::CarState::ACCELERATE);
                        if (gameSpeed < MaxSpeed) {
                            gameSpeed += 0.55f;
                        }
                    }
                    break;
                case SDLK_DOWN:
                    if (gameState == GameState::RUNNING) {
                        player.setCarState(Player::CarState::DECELERATE);
                        if (gameSpeed > 0.00f) {
                            gameSpeed -= 0.55f;
                        }
                    }
                    break;
                case SDLK_RIGHT:
                    if (gameState == GameState::RUNNING) {
                        if (player.getPlayerPosition().x < 630) {
                            player.setPlayerPosition(player.getPlayerPosition().x + 5, player.getPlayerPosition().y);
                        }
                    }
                    break;
                case SDLK_LEFT:
                    if (gameState == GameState::RUNNING) {
                        if (player.getPlayerPosition().x > 350) {
                            player.setPlayerPosition(player.getPlayerPosition().x - 5, player.getPlayerPosition().y);
                        }
                    }
                    break;
                case SDLK_SPACE:
                    if (gameState == GameState::FOULED) {
                        gameState = GameState::RUNNING;
                    }
                    break;
            }
        }
    }
}
