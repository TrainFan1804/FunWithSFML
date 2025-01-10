#include "pong.h"
#include "pong_data.h"
#include "Ball.h"
#include "Player.h"

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
#include <memory>
#include <string>

namespace
{
    enum class GameState
    {
        MENU,
        COUNTDOWN,
        PLAYING
    };

    void initPlaying(std::unique_ptr<Player> &player_one, std::unique_ptr<Player> &player_two, 
                        std::unique_ptr<Ball> &ball, std::unique_ptr<sf::Texture> &ball_texture, 
                        std::unique_ptr<sf::Text> &score_text, sf::Font &font)
    {
        const int SLIDER_START_OFF_Y = slider_data::SLIDER_SIZE_Y / 2.f;

        sf::Vector2f slider_vec(slider_data::SLIDER_SIZE_X, slider_data::SLIDER_SIZE_Y);
        player_one = std::make_unique<Player>(slider_vec,
                            sf::Vector2f(slider_data::SLIDER_OFF_X, window_data::WINDOW_HEIGHT / 2.f - SLIDER_START_OFF_Y));

        player_two = std::make_unique<Player>(slider_vec,
                        sf::Vector2f(window_data::WINDOW_WIDHT - slider_data::SLIDER_OFF_X - slider_data::SLIDER_SIZE_X,
                            window_data::WINDOW_HEIGHT / 2.f - SLIDER_START_OFF_Y));

        ball_texture = std::make_unique<sf::Texture>();
        if(!ball_texture->loadFromFile("assets/sprites/ball.png"))
        {
            throw std::runtime_error("Failed to load ball texture");
        }

        const int BALL_SIZE = slider_data::SLIDER_SIZE_X;   // make sure the ball is the same size as the sliders
        ball = std::make_unique<Ball>(sf::Vector2f(BALL_SIZE, BALL_SIZE), sf::Vector2f(5.f, 5.f), *ball_texture);

        score_text = std::make_unique<sf::Text>();
        score_text->setFont(font);
        score_text->setCharacterSize(44);
        score_text->setStyle(sf::Text::Bold);
        score_text->setFillColor(sf::Color::White);
    }

    void updateScoreText(std::unique_ptr<sf::Text> &text)
    {
        if (score_data::score_changed)
        {
            text->setString(std::to_string(score_data::player_one) + " : " + std::to_string(score_data::player_two));
            text->setPosition((window_data::WINDOW_WIDHT - text->getGlobalBounds().width) / 2.f, window_data::WINDOW_HEIGHT * 0.02f);
            score_data::score_changed = false;
        } 
    }

    void playingRender(sf::RenderWindow &window,
                const Player &player_one, 
                const Player &player_two, 
                const Ball &ball, 
                const sf::Text &score_text) 
    {
        window.draw(player_one);
        window.draw(player_two);
        window.draw(ball);
        window.draw(score_text);
    }
}

void pong()
{
    sf::RenderWindow window(sf::VideoMode(window_data::WINDOW_WIDHT, window_data::WINDOW_HEIGHT),
                            "Pong",
                            sf::Style::Titlebar); // need this to make the winow
                                                // floating on my system
    window.setFramerateLimit(60);

    GameState state = GameState::MENU;

    sf::Font font;
    if (!font.loadFromFile("assets/fonts/OpenSans-Medium.ttf"))
    {
        throw std::runtime_error("Failed to load font");
    }

    sf::Text menu_text("Press ENTER to Start", font, 44);
    menu_text.setFillColor(sf::Color::White);
    menu_text.setPosition(window_data::WINDOW_MID);

    sf::Clock countdown_clock;
    float countdown_time = 3.0f;
    sf::Text countdown_text("", font, 44);
    countdown_text.setFillColor(sf::Color::Red);
    countdown_text.setPosition(window_data::WINDOW_MID);

    std::unique_ptr<Player> player_one;
    std::unique_ptr<Player> player_two;
    std::unique_ptr<Ball> ball;
    std::unique_ptr<sf::Texture> ball_texture;
    std::unique_ptr<sf::Text> score_text;

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

        window.clear(sf::Color::Black);

        switch (state) 
        {
        case GameState::MENU: 

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                initPlaying(player_one, player_two, ball, ball_texture, score_text, font);
                state = GameState::COUNTDOWN;
                countdown_clock.restart();
            }
            window.draw(menu_text);
            break;
        case GameState::COUNTDOWN: 
        {
            float remaining_time = countdown_time - countdown_clock.getElapsedTime().asSeconds();
            if (remaining_time <= 0)
            {
                state = GameState::PLAYING;
            }
            else
            {
                countdown_text.setString("Starting in: " + std::to_string(static_cast<int>(remaining_time + 1)));
            }
            window.draw(countdown_text);
            break;
        }
        case GameState::PLAYING:
            updatePlayerPosition(*player_one, slider_data::SLIDER_OFF_X, sf::Keyboard::Up, sf::Keyboard::Down);
            updatePlayerPosition(*player_two, 
                                window_data::WINDOW_WIDHT - slider_data::SLIDER_OFF_X - slider_data::SLIDER_SIZE_X, 
                                sf::Keyboard::Left, 
                                sf::Keyboard::Right);

            ball->move();

            updateScoreText(score_text);

            ball->handlePlayerCollision(player_one->getSlider().getGlobalBounds());
            ball->handlePlayerCollision(player_two->getSlider().getGlobalBounds());
            playingRender(window, *player_one, *player_two, *ball, *score_text);
            break;
        }

        window.display();
    }
}
