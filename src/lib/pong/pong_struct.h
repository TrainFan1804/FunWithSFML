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

#endif // PONG_STUCT_H 
