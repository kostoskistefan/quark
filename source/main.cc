#include <SDL2/SDL.h>
#include "quark_window.h"

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    QuarkWindow quarkWindow;

    bool keepRunning = true;

    while(keepRunning)
    {
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

        quarkWindow.render();
    }

    SDL_Quit();

    return EXIT_SUCCESS;
}
