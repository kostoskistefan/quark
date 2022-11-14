#ifndef WINDOW_H
#define WINDOW_H

#include <vector>
#include <functional>
#include <SDL2/SDL.h>
#include "taskbar.h"

class QuarkWindow 
{
    public:
        QuarkWindow();
        ~QuarkWindow();

        SDL_Renderer *get_renderer();

        void render();
        void registerRenderCallback(std::function<void(void)> callback);

    private:
        Taskbar *taskbar;
        SDL_Window *window;
        SDL_Renderer *renderer;
        std::vector<std::function<void(void)>> registeredRenderCallbacks;
};

#endif // WINDOW_H
