#include <SDL.h>
#include <SDL_image.h>

#include "Entity.hpp"

Entity::Entity(double p_x, double p_y, SDL_Texture* p_tex)
{
    x = p_x;
    y = p_y;
    texture = p_tex;
}