#include "quark_window.h"
#include "screen_utilities.h"

QuarkWindow::QuarkWindow()
{
#ifdef X11_SESSION
    SDL_SetHint(SDL_HINT_X11_WINDOW_TYPE, "_NET_WM_WINDOW_TYPE_DOCK");
#endif

    int hintIsSet = SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

    if (hintIsSet == SDL_FALSE)
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    bool windowCreatedSuccessfully = 
        SDL_CreateWindowAndRenderer(
                ScreenUtilities::get_screen_width(), 
                30, 
                SDL_WINDOW_BORDERLESS | SDL_WINDOW_SKIP_TASKBAR | SDL_WINDOW_ALWAYS_ON_TOP, 
                &this->window, 
                &this->renderer);


    if (windowCreatedSuccessfully)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_SetWindowPosition(this->window, 0, ScreenUtilities::get_screen_height() - 30);
    SDL_SetRenderDrawBlendMode(this->renderer, SDL_BLENDMODE_BLEND);

    this->taskbar = new Taskbar(this->renderer, 44);

    registerRenderCallback(std::bind(&Taskbar::render, taskbar));
}

QuarkWindow::~QuarkWindow()
{
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
}

SDL_Renderer *QuarkWindow::get_renderer()
{
    return this->renderer;
}

void QuarkWindow::registerRenderCallback(std::function<void(void)> callback)
{
    this->registeredRenderCallbacks.push_back(callback);
}

void QuarkWindow::render()
{
    SDL_SetRenderDrawColor(renderer, 20, 45, 66, 255);
    SDL_RenderClear(renderer);

    for (auto callback : registeredRenderCallbacks)
        callback();

    SDL_RenderPresent(renderer);
}
