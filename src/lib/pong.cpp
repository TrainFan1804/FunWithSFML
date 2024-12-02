#include "pong.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

const int VERT_ARRAY_SIZE = 4;
const int WINDOW_WIDHT = 1000;
const int WINDOW_HEIGHT = 800;

const int SLIDER_OFF_X = 75;
const int SLIDER_SIZE_X = 75;
const int SLIDER_SIZE_Y = 200;

void pong()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDHT, WINDOW_HEIGHT),
                            "Pong",
                            sf::Style::Titlebar); // need this to make the winow
                                                // floating on my system
    window.setFramerateLimit(60);

    const int SLIDER_START_OFF_Y = SLIDER_SIZE_Y / 2.f;

    sf::RectangleShape player_one(sf::Vector2f(SLIDER_SIZE_X, SLIDER_SIZE_Y));
    player_one.setPosition(sf::Vector2f(SLIDER_OFF_X, WINDOW_HEIGHT / 2.f - SLIDER_START_OFF_Y));

    sf::RectangleShape player_two(sf::Vector2f(SLIDER_SIZE_X, SLIDER_SIZE_Y));
    player_two.setPosition(sf::Vector2f(WINDOW_WIDHT - SLIDER_OFF_X - SLIDER_SIZE_X, WINDOW_HEIGHT / 2.f - SLIDER_START_OFF_Y));

    const int BALL_SIZE = SLIDER_SIZE_X;
    sf::RectangleShape ball(sf::Vector2f(BALL_SIZE, BALL_SIZE));
    ball.setPosition(sf::Vector2f(WINDOW_WIDHT / 2.f - BALL_SIZE, WINDOW_HEIGHT / 2.f - BALL_SIZE));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                player_one.setPosition(sf::Vector2f(SLIDER_OFF_X, player_one.getPosition().y - 20));
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                player_one.setPosition(sf::Vector2f(SLIDER_OFF_X, player_one.getPosition().y + 20));
        }

        window.clear();
        window.draw(player_one);
        window.draw(player_two);
        window.draw(ball);

        window.display();
    }
}
