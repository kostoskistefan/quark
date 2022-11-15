#include "taskbar.h"
#include "screen_utilities.h"

Taskbar::Taskbar(int height, int padding, int buttonWidth, int buttonSpacing) : 
    height(height), 
    padding(padding),
    buttonWidth(buttonWidth), 
    buttonSpacing(buttonSpacing)
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
                this->height, 
                SDL_WINDOW_BORDERLESS | SDL_WINDOW_SKIP_TASKBAR | SDL_WINDOW_ALWAYS_ON_TOP, 
                &window, 
                &renderer);

    if (windowCreatedSuccessfully)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create window and renderer: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_SetWindowPosition(window, 0, ScreenUtilities::get_screen_height() - this->height);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    Button *button = new Button(this->renderer, this->buttonWidth, this->height, 5, "/usr/share/icons/hicolor/32x32/apps/google-chrome.png");

    this->buttons.push_back(button);

    for (uint32_t i = 0; i < this->buttons.size(); i++)
        this->buttons[i]->move(this->padding + (this->buttonWidth + this->buttonSpacing) * i, 0);
}

Taskbar::~Taskbar()
{
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
}

void Taskbar::update()
{
    mouse.update();

    for (Button *button : buttons)
        button->update(&mouse);
}

void Taskbar::render()
{
    SDL_SetRenderDrawColor(renderer, 20, 45, 66, 255);
    SDL_RenderClear(renderer);

    for (Button *button : buttons)
        button->render();

    SDL_RenderPresent(renderer);
}
