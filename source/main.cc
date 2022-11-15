#include "taskbar.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_touch.h>

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    Taskbar taskbar;

    bool keepRunning = true;

    while(keepRunning)
    {
        taskbar.update();

        SDL_Event event;

        while(SDL_PollEvent(&event) > 0)
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    keepRunning = false;
                    break;
            }
        }

        taskbar.render();
    }

    SDL_Quit();

    return EXIT_SUCCESS;
}
