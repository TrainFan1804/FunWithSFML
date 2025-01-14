#include "Player.h"
#include "pong_data.h"

Player::Player(const sf::Vector2f &size,
                const sf::Vector2f &start_pos)
    : _PLAYER_MID_POS(start_pos), _score(0)
{
    _slider.setSize(size);
    _slider.setPosition(start_pos);
}

const sf::RectangleShape &Player::getSlider()
{
    return _slider;
}

const sf::Vector2f &Player::getPos()
{
    return _slider.getPosition();
}

void Player::setPos(const sf::Vector2f &pos)
{
    _slider.setPosition(pos);
}

void Player::move(int dir_y)
{
    _slider.move(0, dir_y);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const 
{
    target.draw(_slider, states);
}

/**
    I could implement this in the player class but then I need to save the binded
    keys to each player seperatly.
 */
void updatePlayerPosition(Player &player, float offset_x, 
    sf::Keyboard::Key first_key, sf::Keyboard::Key second_key)
{
    if (!sf::Keyboard::isKeyPressed(first_key)
            && !sf::Keyboard::isKeyPressed(second_key))
        return;

    const int SLIDER_SPEED = 20;
    int dir_y = 0;

    if (sf::Keyboard::isKeyPressed(first_key))
        dir_y -= SLIDER_SPEED;
    else if (sf::Keyboard::isKeyPressed(second_key))
        dir_y += SLIDER_SPEED;

    player.move(dir_y);

    float slider_top = player.getPos().y;
    float slider_bottom = slider_top + slider_data::SLIDER_SIZE_Y;

    if (slider_top < 0) 
        player.setPos(sf::Vector2f(player.getPos().x, 0.f));
    else if (slider_bottom > window_data::WINDOW_HEIGHT) 
        player.setPos(sf::Vector2f(player.getPos().x, window_data::WINDOW_HEIGHT - slider_data::SLIDER_SIZE_Y));
}
