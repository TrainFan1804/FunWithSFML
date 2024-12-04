#include "pong.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <string>

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
    ball.setPosition(sf::Vector2f(WINDOW_WIDHT / 2.f - BALL_SIZE / 2.f, WINDOW_HEIGHT / 2.f - BALL_SIZE / 2.f));
    sf::Vector2f ball_velo(5.f, 5.f);

    int score_player_one = 0;
    int score_player_two = 0;
    sf::Text score_text;
    sf::Font font;
    font.loadFromFile("../easyfont.otf");
    score_text.setFont(font);
    score_text.setCharacterSize(44);
    score_text.setStyle(sf::Text::Bold);
    score_text.setFillColor(sf::Color::White);
    score_text.setPosition(WINDOW_WIDHT / 2.f, 20);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // this is ugly but I don't care rn
        int dir_y = 0;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            dir_y = -20;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            dir_y = 20;

        int new_y = player_one.getPosition().y + dir_y;
        // new_y = 0 if new_y <= 0 or new_y = WINDOW_HEIGHT - SLIDER_SIZE_Y
        new_y = std::max(0, std::min(new_y, WINDOW_HEIGHT - SLIDER_SIZE_Y));
        player_one.setPosition(SLIDER_OFF_X, new_y);

        dir_y = 0;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            dir_y = -20;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            dir_y = 20;

        new_y = player_two.getPosition().y + dir_y;
        // new_y = 0 if new_y <= 0 or new_y = WINDOW_HEIGHT - SLIDER_SIZE_Y
        new_y = std::max(0, std::min(new_y, WINDOW_HEIGHT - SLIDER_SIZE_Y));
        player_two.setPosition(WINDOW_WIDHT - SLIDER_OFF_X - SLIDER_SIZE_X, new_y);

        ball.move(ball_velo);
        // if ball hit bootm / top reverse velocity
        if (ball.getPosition().y <= 0 || ball.getPosition().y + BALL_SIZE >= WINDOW_HEIGHT)
            ball_velo.y = -ball_velo.y;
        // if ball hit right / left reverse velocity (Now the ball should be removed and placed in the mid again)
        if (ball.getPosition().x <= 0)
        {
            ball_velo.x = -ball_velo.x;
            score_player_two++; 
        } 
        if (ball.getPosition().x + BALL_SIZE >= WINDOW_WIDHT)
        {
            ball_velo.x = -ball_velo.x;
            score_player_one++;
        }

        // std::cout << "Player 1: " << score_player_one << ": Player 2: " << score_player_two << std::endl;
        /*
         * why does this display score_player_one on the left and score_player_two on the opposite side of the ':'?
         * Not anymore because I switched position but see uncomment output how it should ACTUALLY look
         *
         */
        score_text.setString(std::to_string(score_player_two) + "      :     " + std::to_string(score_player_one));

        // if ball hit player_one / player_two reverse velocity as well, this bug xtrem
        if (ball.getGlobalBounds().intersects(player_one.getGlobalBounds())
                || ball.getGlobalBounds().intersects(player_two.getGlobalBounds()))
            ball_velo.x = -ball_velo.x;

        window.clear();

        window.draw(player_one);
        window.draw(player_two);
        window.draw(ball);
        window.draw(score_text);

        window.display();
    }
}
