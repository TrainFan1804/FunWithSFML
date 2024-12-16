#include "Ball.h"
#include "pong_struct.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

Ball::Ball(const sf::Vector2f &size, 
            const sf::Vector2f &velo)
    : _WIDHT(size.x), _velocity(velo)
{
    _BALL_MID_POS = sf::Vector2f(window_data::WINDOW_WIDHT / 2.f - size.x / 2.f, 
                                window_data::WINDOW_HEIGHT / 2.f - size.x / 2.f);
    _ball.setSize(size);
    _ball.setPosition(_BALL_MID_POS);
}

const sf::Vector2f &Ball::getPos()
{
    return _ball.getPosition();
}

void Ball::setPos(sf::Vector2f &pos)
{
    _ball.setPosition(pos);
}

void Ball::move()
{
    _ball.move(_velocity);
    // if ball hit bootm / top reverse velocity
    if (_ball.getPosition().y <= 0 || _ball.getPosition().y + _WIDHT >= window_data::WINDOW_HEIGHT)
        _velocity.y = -_velocity.y;

    // if ball hit right / left reverse velocity and move ball to mid
    if (_ball.getPosition().x <= 0)
    {
        _ball.setPosition(_BALL_MID_POS);
        _velocity.x = -_velocity.x;
        score_data::player_two++; 
    } 
    if (_ball.getPosition().x + _WIDHT >= window_data::WINDOW_WIDHT)
    {
        _ball.setPosition(_BALL_MID_POS);
        _velocity.x = -_velocity.x;
        score_data::player_one++;
    }
}

void Ball::handleCollision(const sf::Rect<float> &bounds)
{
    const sf::Rect<float> ballBounds = _ball.getGlobalBounds();

    if(ballBounds.intersects(bounds))
    {
        /*
            Still not perfect but better
        */
        if (ballBounds.top + ballBounds.height <= bounds.top + 5.f) 
        {
            _velocity.y = -_velocity.y;
            _ball.setPosition(_ball.getPosition().x, bounds.top - ballBounds.height);
        }
        else if (ballBounds.top >= bounds.top + bounds.height - 5.f) 
        {
            _velocity.y = -_velocity.y;
            _ball.setPosition(_ball.getPosition().x, bounds.top + bounds.height);
        }
        else if (ballBounds.left + ballBounds.width <= bounds.left + 5.f) 
        {
            _velocity.x = -_velocity.x;
            _ball.setPosition(bounds.left - ballBounds.width, _ball.getPosition().y);
        }
        else if (ballBounds.left >= bounds.left + bounds.width - 5.f) 
        {
            _velocity.x = -_velocity.x;
            _ball.setPosition(bounds.left + bounds.width, _ball.getPosition().y);
        }
    }
}

void Ball::draw(sf::RenderTarget &target, sf::RenderStates states) const 
{
    target.draw(_ball, states);  // Zeichne das Rechteck
}
