#include "taskbar.h"

Taskbar::Taskbar(SDL_Renderer *renderer, int offset, int height, int iconSpacing)
{
    this->renderer = renderer;
    this->offset = offset;
    this->height = height;
    this->iconSpacing = iconSpacing;

    buttons.push_back(new Button(this->renderer, this->height, "/usr/share/icons/hicolor/32x32/apps/google-chrome.png"));
    buttons.push_back(new Button(this->renderer, this->height, "/usr/share/icons/hicolor/32x32/apps/vlc.png"));

    for (long unsigned int i = 0; i < buttons.size(); i++)
    {
        this->buttons[i]->set_horizontal_offset(
                this->offset + (this->height + this->iconSpacing) * i);
    }
}


void Taskbar::set_height(int height)
{
    this->height = height;
}

void Taskbar::set_offset(int offset)
{
    this->offset = offset;
}

void Taskbar::set_icon_spacing(int spacing)
{
    this->iconSpacing = spacing;
}

int Taskbar::get_height()
{
    return this->height;
}

int Taskbar::get_offset()
{
    return this->offset;
}

int Taskbar::get_icon_spacing()
{
    return this->iconSpacing;
}

void Taskbar::render()
{
    for (Button *button : buttons)
        button->render();
}
