#ifndef BALL_H 
#define BALL_H 

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Ball : public sf::Drawable
{
public:
    Ball(const sf::Vector2f &size, 
            const sf::Vector2f &velo,
            const sf::Texture &texture);
    const sf::Vector2f &getPos();
    void setPos(const sf::Vector2f &pos);
    void move();
    void handlePlayerCollision(const sf::Rect<float> &bounds); 
private:
    sf::Vector2f _BALL_MID_POS;
    sf::RectangleShape _ball;
    sf::Vector2f _velocity;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif // BALL_H
