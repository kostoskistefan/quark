#ifndef BUTTON_STATE_H
#define BUTTON_STATE_H

class ButtonState
{
    public:
        enum State 
        {
            Inactive,
            Hover,
            Clicked
        };

        ButtonState();
        
        void set_state(ButtonState::State state);

        int get_color();
        ButtonState::State get_state();

    private:
        ButtonState::State state;
        int selectedColor;
        int colors[3];
};


#endif // BUTTON_STATE_H
