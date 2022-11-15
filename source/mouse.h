#ifndef MOUSE_H
#define MOUSE_H

#include <SDL2/SDL.h>

class Mouse
{
    public:
        enum State
        {
            Released,
            Pressed
        };

        Mouse();
        void update();

        SDL_Rect point;
        Mouse::State state;
};

#endif // MOUSE_H
