#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <SDL2/SDL.h>

class Button
{
    public:
        Button(SDL_Renderer *renderer, int size, std::string iconPath, int padding = 6);
        ~Button();

        void set_size(int size);
        void set_padding(int padding);
        void set_horizontal_offset(int offset);
        void set_background_color(int color);
        void set_icon_path(std::string iconPath);

        int get_size();
        int get_padding();
        int get_horizontal_offset();
        int get_background_color();
        std::string get_icon_path();

        void render();

    private:
        int size;
        int padding;
        int horizontalOffset;
        int backgroundColor;
        std::string iconPath;
        SDL_Texture *texture;

        SDL_Rect sizePosition;
        SDL_Renderer *renderer;

        void update_texture_from_icon_path();
};

#endif // BUTTON_H
