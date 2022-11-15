#ifndef TASKBAR_H
#define TASKBAR_H

#include <vector>
#include <SDL2/SDL.h>
#include "button.h"

class Taskbar
{
    public:
        Taskbar(int height = 30, 
                int padding = 10, 
                int buttonWidth = 36, 
                int buttonSpacing = 3);
        ~Taskbar();

        void on_leave();

        void update();
        void render();

    private:
        Mouse mouse;

        SDL_Window *window;
        SDL_Renderer *renderer;

        const int height;
        const int padding;
        const int buttonWidth;
        const int buttonSpacing;

        std::vector<Button *> buttons;
};

#endif // TASKBAR_H
