#include "taskbar.h"
#include "x_utilities.h"
#include "screen_utilities.h"

Taskbar::Taskbar(int height, int padding, int buttonWidth, int buttonSpacing) : 
    height(height), 
    padding(padding),
    buttonWidth(buttonWidth), 
    buttonSpacing(buttonSpacing)
{
    this->keepRunning = true;

    this->initialize_sdl();
    this->set_hints();
    this->create_window();

    XUtilities utils;

    std::vector<application_t> apps = utils.get_running_applications();

    /* Button *button = new Button(this->renderer, this->buttonWidth, this->height, 5, "/usr/share/icons/hicolor/32x32/apps/google-chrome.png"); */

    for (auto a : apps)
        this->buttons.push_back(new Button(this->renderer, this->buttonWidth, this->height, 5, "/usr/share/icons/hicolor/32x32/apps/google-chrome.png"));
        /* this->buttons.push_back(button); */

    for (uint32_t i = 0; i < this->buttons.size(); i++)
        this->buttons[i]->move(this->padding + (this->buttonWidth + this->buttonSpacing) * i, 0);
}

Taskbar::~Taskbar()
{
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);

    SDL_Quit();
}

void Taskbar::set_hints()
{
#ifdef X11_SESSION
    SDL_SetHint(SDL_HINT_X11_WINDOW_TYPE, "_NET_WM_WINDOW_TYPE_DOCK");
#endif

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
}

void Taskbar::initialize_sdl()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

void Taskbar::create_window()
{
    bool windowCreationFailed = 
        SDL_CreateWindowAndRenderer(
                ScreenUtilities::get_screen_width(), 
                this->height, 
                SDL_WINDOW_BORDERLESS | SDL_WINDOW_SKIP_TASKBAR | SDL_WINDOW_ALWAYS_ON_TOP, 
                &this->window, 
                &this->renderer);

    if (windowCreationFailed)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create window and renderer: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_SetWindowPosition(this->window, 0, ScreenUtilities::get_screen_height() - this->height);
    SDL_SetRenderDrawBlendMode(this->renderer, SDL_BLENDMODE_BLEND);
}

void Taskbar::update()
{
    this->mouse.update();

    for (Button *button : this->buttons)
        button->update(&this->mouse);
}

void Taskbar::render()
{
    SDL_SetRenderDrawColor(this->renderer, 20, 45, 66, 255);
    SDL_RenderClear(this->renderer);

    for (Button *button : this->buttons)
        button->render();

    SDL_RenderPresent(this->renderer);
}

void Taskbar::run()
{
    while(this->keepRunning)
    {
        this->update();

        SDL_Event event;

        while(SDL_PollEvent(&event) > 0)
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    this->keepRunning = false;
                    break;
            }
        }

        this->render();
    }
}
