#include "button.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>

Button::Button(SDL_Renderer *renderer, int size, std::string iconPath, int padding)
{
    this->renderer = renderer;

    set_size(size);
    set_padding(padding);
    set_icon_path(iconPath);
    set_background_color(0xFFFFFF00);
}

Button::~Button()
{
    SDL_DestroyTexture(texture);
    IMG_Quit();
}

void Button::set_size(int size)
{
    this->size = size;
    this->sizePosition.w = size;
    this->sizePosition.h = size;
}

void Button::set_padding(int padding)
{
    this->padding = padding;
}

void Button::set_horizontal_offset(int offset)
{
    this->horizontalOffset = offset;
    this->sizePosition.x = offset;
    this->sizePosition.y = 0;
}

void Button::set_icon_path(std::string iconPath)
{
    this->iconPath = iconPath;
    update_texture_from_icon_path();
}

void Button::set_background_color(int color)
{
    this->backgroundColor = color;
}

int Button::get_size()
{
    return this->size;
}

int Button::get_padding()
{
    return this->padding;
}

int Button::get_horizontal_offset()
{
    return this->horizontalOffset;
}

std::string Button::get_icon_path()
{
    return this->iconPath;
}

int Button::get_background_color()
{
    return this->backgroundColor;
}

void Button::render()
{
    if (texture == NULL)
        return;

    SDL_SetRenderDrawColor(renderer, 
            (this->backgroundColor >> 24) & 0xff,
            (this->backgroundColor >> 16) & 0xff,
            (this->backgroundColor >> 8) & 0xff,
            this->backgroundColor & 0xff);

    SDL_RenderFillRect(renderer, &sizePosition);

    SDL_Rect paddedRect = {
        .x = sizePosition.x + this->padding,
        .y = sizePosition.y + this->padding,
        .w = sizePosition.w - (this->padding * 2),
        .h = sizePosition.h - (this->padding * 2)
    };

    SDL_RenderCopy(renderer, texture, NULL, &paddedRect);
}

void Button::update_texture_from_icon_path()
{
    SDL_Surface *surface = IMG_Load(this->iconPath.c_str());

    if (!surface) 
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s", SDL_GetError());

    texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (!texture) 
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());

    SDL_FreeSurface(surface);
}
