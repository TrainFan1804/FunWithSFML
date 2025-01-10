#ifndef PONG_STRUCT_H
#define PONG_STRUCT_H

#include <SFML/System/Vector2.hpp>

namespace window_data
{
    extern const int WINDOW_WIDHT;
    extern const int WINDOW_HEIGHT;
    extern const sf::Vector2f WINDOW_MID;
}

namespace score_data 
{
    extern bool score_changed;  // ugly AF
    extern int player_one;
    extern int player_two;
}

namespace slider_data 
{
    extern const int SLIDER_OFF_X;
    extern const int SLIDER_SIZE_X;
    extern const int SLIDER_SIZE_Y;
}

#endif // PONG_STUCT_H 
