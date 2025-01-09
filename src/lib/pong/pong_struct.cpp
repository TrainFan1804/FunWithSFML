#include "pong_struct.h"

namespace window_data 
{
    const int WINDOW_WIDHT = 1000;
    const int WINDOW_HEIGHT = 800;
    const sf::Vector2f WINDOW_MID = sf::Vector2f(WINDOW_WIDHT / 2.f, WINDOW_HEIGHT / 2.f);
}

namespace score_data
{
    bool score_changed = true;
    int player_one = 0;
    int player_two = 0;
}
