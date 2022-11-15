#include "button.h"
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Button::Button(SDL_Renderer *renderer, int width, int height, int padding, std::string iconPath) : 
    renderer(renderer),
    padding(padding),
    iconPath(iconPath)
{
    this->relativePosition.x = 0;
    this->relativePosition.y = 0;
    this->relativePosition.w = width;
    this->relativePosition.h = height;

    SDL_GetWindowPosition(
            SDL_RenderGetWindow(renderer), 
            &this->globalPosition.x, 
            &this->globalPosition.y);

    this->globalPosition.w = width;
    this->globalPosition.h = height;

    this->buttonState.set_state(ButtonState::State::Inactive);
    this->callbackIsHandled = false;

    this->callback = nullptr;

    this->texture = IMG_LoadTexture(this->renderer, this->iconPath.c_str());

    if (!this->texture) 
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create button texture: %s", SDL_GetError());
}

Button::~Button()
{
    SDL_DestroyTexture(texture);
    IMG_Quit();
}

void Button::move(int x, int y)
{
    this->relativePosition.x = x;
    this->relativePosition.y = y;
}

ButtonState::State Button::get_state()
{
    return this->buttonState.get_state();
}

void Button::set_state(ButtonState::State state)
{
    this->buttonState.set_state(state);
}

void Button::set_callback(std::function<bool()> callback)
{
    this->callback = callback;
}

void Button::update(Mouse *mouse)
{
    if (SDL_HasIntersection(&globalPosition, &mouse->point))
    {
        if (mouse->state == Mouse::State::Pressed)
            on_click();

        else on_hover();
    } 

    else on_leave();
}

void Button::render()
{
    int backgroundColor = this->buttonState.get_color();

    int r = (backgroundColor >> 24) & 0xff;
    int g = (backgroundColor >> 16) & 0xff;
    int b = (backgroundColor >> 8) & 0xff;
    int a = backgroundColor & 0xff;

    SDL_SetRenderDrawColor(renderer, r, g, b, a);

    SDL_RenderFillRect(renderer, &this->relativePosition);

    int minSize = std::min(this->relativePosition.w, this->relativePosition.h);
    int iconSize = minSize - (this->padding * 2);

    SDL_Rect iconRect= {
        .x = (int) (this->relativePosition.x + (this->relativePosition.w / 2.0f) - (iconSize / 2.0f)),
        .y = (int) (this->relativePosition.y + (this->relativePosition.h / 2.0f) - (iconSize / 2.0f)),
        .w = iconSize,
        .h = iconSize
    };

    SDL_RenderCopy(renderer, texture, NULL, &iconRect);
}

void Button::on_leave()
{
    this->buttonState.set_state(ButtonState::State::Inactive);
}

void Button::on_hover()
{
    this->buttonState.set_state(ButtonState::State::Hover);
    this->callbackIsHandled = false;
}

void Button::on_click()
{
    this->buttonState.set_state(ButtonState::State::Clicked);

    if (this->callback && !this->callbackIsHandled)
    {
        this->callbackIsHandled = this->callback();
    }
}

