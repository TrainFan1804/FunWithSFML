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
    _ball.setOutlineThickness(10.f);
    _ball.setOutlineColor(sf::Color::Red);
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
    // 140 because offset of left slider is 75 and size is also 75 also total of 150. 140 for some buffer
    if (_ball.getPosition().x <= 140)
    {
        _ball.setPosition(_BALL_MID_POS);
        _velocity.x = -_velocity.x;
        score_data::score_changed = true;
        score_data::player_two++; 
    } 
    // 140 because offset of left slider is 75 and size is also 75 also total of 150. 140 for some buffer
    if (_ball.getPosition().x + _WIDHT >= window_data::WINDOW_WIDHT - 140)
    {
        _ball.setPosition(_BALL_MID_POS);
        _velocity.x = -_velocity.x;
        score_data::score_changed = true;
        score_data::player_one++;
    }
}

void Ball::handleCollision(const sf::Rect<float> &bounds)
{
    const sf::Rect<float> ball_bounds = _ball.getGlobalBounds();

    if(ball_bounds.intersects(bounds))
    {
        float offset = bounds.width * 0.1f;
        if (_velocity.x >= 0)
            offset = -offset - bounds.width;

        _velocity.x = -_velocity.x;
    }
}

void Ball::draw(sf::RenderTarget &target, sf::RenderStates states) const 
{
    target.draw(_ball, states);  // Zeichne das Rechteck
}
