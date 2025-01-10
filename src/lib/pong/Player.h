#ifndef PLAYER_H 
#define PLAYER_H

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Keyboard.hpp>

class Player : public sf::Drawable
{
public:
    Player(const sf::Vector2f &size,
            const sf::Vector2f &start_pos);
    const sf::Vector2f &getPos();
    void setPos(const sf::Vector2f &pos);
    void move(int dir_y);

    sf::RectangleShape _slider;
private:
    const sf::Vector2f _PLAYER_MID_POS;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

void updatePlayerPosition(Player &player, float offset_x,
            sf::Keyboard::Key first_key, sf::Keyboard::Key second_key);

#endif // PLAYER_H
