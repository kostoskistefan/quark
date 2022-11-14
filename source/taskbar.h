#ifndef TASKBAR_H
#define TASKBAR_H

#include <vector>
#include "button.h"
#include <SDL2/SDL.h>

class Taskbar 
{
    public:
        Taskbar(SDL_Renderer *renderer, int offset, int height = 30, int iconSpacing = 5);

        void set_height(int height);
        void set_offset(int offset);
        void set_icon_spacing(int spacing);

        int get_height();
        int get_offset();
        int get_icon_spacing();

        void render();

    private:
        int height;
        int offset;
        int iconSpacing;
        SDL_Renderer *renderer;
        std::vector<Button*> buttons;
};

#endif // TASKBAR_H
