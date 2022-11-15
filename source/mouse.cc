#include "mouse.h"
#include <SDL2/SDL_mouse.h>

Mouse::Mouse()
{
    this->point.x = 0;
    this->point.y = 0;
    this->point.w = 1;
    this->point.h = 1;

    this->state = Mouse::State::Released;
}

void Mouse::update()
{
    uint32_t state = SDL_GetGlobalMouseState(&this->point.x, &this->point.y);

    if (state & SDL_BUTTON(1))
        this->state = Mouse::State::Pressed;

    else this->state = Mouse::State::Released;
}
