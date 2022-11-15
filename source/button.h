#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <functional>
#include <SDL2/SDL.h>
#include "mouse.h"
#include "button_state.h"

class Button
{
    public:
        Button(SDL_Renderer *renderer, int width, int height, int padding, std::string iconPath);
        ~Button();

        void move(int x, int y);

        ButtonState::State get_state();

        void set_state(ButtonState::State state);
        void set_callback(std::function<bool()> callback);

        void update(Mouse *mouse);
        void render();

    private:
        SDL_Renderer * const renderer;
        SDL_Rect globalPosition;
        SDL_Rect relativePosition;
        const int padding;
        const std::string iconPath;
        ButtonState buttonState;
        SDL_Texture *texture;
        bool callbackIsHandled;

        std::function<bool()> callback;

        void on_leave();
        void on_hover();
        void on_click();
};

#endif // BUTTON_H
