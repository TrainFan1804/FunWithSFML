#include "pong.h"
#include "pong_struct.h"
#include "Ball.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <cstdlib>
#include <string>

static void updateSliderPosition(sf::RectangleShape &slider, 
                          float offset_x, 
                          sf::Keyboard::Key upKey, 
                          sf::Keyboard::Key downKey)
{
    const int SLIDER_SPEED = 20;
    int dir_y = 0;

    if (sf::Keyboard::isKeyPressed(upKey))
        dir_y -= SLIDER_SPEED;
    else if (sf::Keyboard::isKeyPressed(downKey))
        dir_y += SLIDER_SPEED;

    slider.move(0, dir_y);

    float slider_top = slider.getPosition().y;
    float slider_bottom = slider_top + slider_data::SLIDER_SIZE_Y;

    if (slider_top < 0) 
        slider.setPosition(slider.getPosition().x, 0.f);
    else if (slider_bottom > window_data::WINDOW_HEIGHT) 
        slider.setPosition(slider.getPosition().x, window_data::WINDOW_HEIGHT - slider_data::SLIDER_SIZE_Y);
}

static void updateText(sf::Text &text)
{
    if (score_data::score_changed)
    {
        text.setString(std::to_string(score_data::player_one) + " : " + std::to_string(score_data::player_two));
        text.setPosition((window_data::WINDOW_WIDHT - text.getGlobalBounds().width) / 2.f, window_data::WINDOW_HEIGHT * 0.02f);
        score_data::score_changed = false;
    } 
}

static void render(sf::RenderWindow &window, 
            const sf::RectangleShape &player_one, 
            const sf::RectangleShape &player_two, 
            const Ball &ball, 
            const sf::Text &score_text) 
{
    window.clear(sf::Color::Black);
    window.draw(player_one);
    window.draw(player_two);
    window.draw(ball);
    window.draw(score_text);
    window.display();
}

void pong()
{
    sf::RenderWindow window(sf::VideoMode(window_data::WINDOW_WIDHT, window_data::WINDOW_HEIGHT),
                            "Pong",
                            sf::Style::Titlebar); // need this to make the winow
                                                // floating on my system
    window.setFramerateLimit(60);

    const int SLIDER_START_OFF_Y = slider_data::SLIDER_SIZE_Y / 2.f;

    sf::RectangleShape player_one(sf::Vector2f(slider_data::SLIDER_SIZE_X, slider_data::SLIDER_SIZE_Y));
    player_one.setPosition(sf::Vector2f(slider_data::SLIDER_OFF_X, window_data::WINDOW_HEIGHT / 2.f - SLIDER_START_OFF_Y));

    sf::RectangleShape player_two(sf::Vector2f(slider_data::SLIDER_SIZE_X, slider_data::SLIDER_SIZE_Y));
    player_two.setPosition(sf::Vector2f(window_data::WINDOW_WIDHT - slider_data::SLIDER_OFF_X - slider_data::SLIDER_SIZE_X, 
                                        window_data::WINDOW_HEIGHT / 2.f - SLIDER_START_OFF_Y));

    sf::Texture texture;
    if(!texture.loadFromFile("assets/sprites/ball.png"))
    {
        throw std::runtime_error("Failed to load ball texture");
    }
    const int BALL_SIZE = slider_data::SLIDER_SIZE_X;
    Ball ball(sf::Vector2f(BALL_SIZE, BALL_SIZE), sf::Vector2f(5.f, 5.f), texture);

    sf::Text score_text;
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/OpenSans-Medium.ttf"))
    {
        throw std::runtime_error("Failed to load font");
    }
    score_text.setFont(font);
    score_text.setCharacterSize(44);
    score_text.setStyle(sf::Text::Bold);
    score_text.setFillColor(sf::Color::White);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }

        updateSliderPosition(player_one, slider_data::SLIDER_OFF_X, sf::Keyboard::Up, sf::Keyboard::Down);
        updateSliderPosition(player_two, 
                            window_data::WINDOW_WIDHT - slider_data::SLIDER_OFF_X - slider_data::SLIDER_SIZE_X, 
                            sf::Keyboard::Left, 
                            sf::Keyboard::Right);

        ball.move();

        updateText(score_text);

        ball.handlePlayerCollision(player_one.getGlobalBounds());
        ball.handlePlayerCollision(player_two.getGlobalBounds());

        render(window, player_one, player_two, ball, score_text);
    }
}
