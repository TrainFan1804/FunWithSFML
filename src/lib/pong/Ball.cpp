#include "Ball.h"
#include "pong_data.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <climits>

namespace
{
    enum class WallCollision
    {
        NONE,
        LEFT,
        RIGHT,
        TOPBOTTOM
    };
    WallCollision checkWallCollision(sf::RectangleShape &ball, sf::Vector2f &velocity)
    {
        const int WIDTH = ball.getSize().x;

        if (ball.getPosition().y <= 0 || ball.getPosition().y + WIDTH >= window_data::WINDOW_HEIGHT)
        {
            velocity.y = -velocity.y;
            return WallCollision::TOPBOTTOM;
        }


        // if ball hit right / left reverse velocity and move ball to mid
        // 140 because offset of left slider is 75 and size is also 75 also total of 150. 140 for some buffer
        if (ball.getPosition().x <= 140)
            return WallCollision::LEFT;


        // 140 because offset of left slider is 75 and size is also 75 also total of 150. 140 for some buffer
        if (ball.getPosition().x + WIDTH >= window_data::WINDOW_WIDHT - 140)
            return WallCollision::RIGHT;

        return WallCollision::NONE;
    }
}

Ball::Ball(const sf::Vector2f &size, 
            const sf::Vector2f &velo,
            const sf::Texture &texture)
    : _velocity(velo)
{
    _BALL_MID_POS = sf::Vector2f(window_data::WINDOW_WIDHT / 2.f - size.x / 2.f, 
                                window_data::WINDOW_HEIGHT / 2.f - size.x / 2.f);
    _ball.setSize(size);
    _ball.setPosition(_BALL_MID_POS);
    _ball.setTexture(&texture);
}

const sf::Vector2f &Ball::getPos()
{
    return _ball.getPosition();
}

void Ball::setPos(const sf::Vector2f &pos)
{
    _ball.setPosition(pos);
}

void Ball::move()
{
    _ball.move(_velocity);

    WallCollision collsion = checkWallCollision(_ball, _velocity);

    switch (collsion) 
    {
    case WallCollision::LEFT:
        _ball.setPosition(_BALL_MID_POS);
        _velocity.x = -_velocity.x;
        score_data::score_changed = true;
        score_data::player_two++; 
        break;
    case WallCollision::RIGHT:
        _ball.setPosition(_BALL_MID_POS);
        _velocity.x = -_velocity.x;
        score_data::score_changed = true;
        score_data::player_one++;
        break;
    default:
        break;
    }
}

/**
    This should be changed because this is ugly with the combination of move method
 */
void Ball::handlePlayerCollision(const sf::Rect<float> &bounds)
{
    const sf::Rect<float> ball_bounds = _ball.getGlobalBounds();

    if(ball_bounds.intersects(bounds))
        _velocity.x = -_velocity.x;
}

void Ball::draw(sf::RenderTarget &target, sf::RenderStates states) const 
{
    target.draw(_ball, states);
}
