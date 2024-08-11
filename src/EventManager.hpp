#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include <SDL.h>
#include "player.hpp"

enum class GameState { START, RUNNING, PAUSED, OVER, FOULED, };

class EventManager {
public:
    EventManager();
    void handleEvents(bool& gameRunning, GameState& gameState, Player& player, SDL_Rect& spriteNPC, float& gameSpeed, const float MaxSpeed);
};

#endif
