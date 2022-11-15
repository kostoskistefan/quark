#include "button_state.h"

ButtonState::ButtonState()
{
    this->state = ButtonState::State::Inactive;

    this->colors[ButtonState::State::Inactive] = 0xFFFFFF00;
    this->colors[ButtonState::State::Hover]    = 0xFFFFFF20;
    this->colors[ButtonState::State::Clicked]  = 0xFFFFFF60;

    this->selectedColor = this->colors[ButtonState::State::Inactive];
}

void ButtonState::set_state(ButtonState::State state)
{
    this->state = state;
    this->selectedColor = this->colors[state];
}

int ButtonState::get_color()
{
    return this->selectedColor;
}

ButtonState::State ButtonState::get_state()
{
    return this->state;
}
