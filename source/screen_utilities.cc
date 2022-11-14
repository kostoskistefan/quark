#include "screen_utilities.h"

SDL_DisplayMode get_display_mode()
{
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);

    return displayMode;
}

int ScreenUtilities::get_screen_width()
{
    return get_display_mode().w;
}

int ScreenUtilities::get_screen_height()
{
    return get_display_mode().h;
}
