#include "triangle_classic.h"

#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Window/Event.hpp>

const int WINDOW_WIDHT = 1000;
const int WINDOW_HEIGHT = 800;

void triangleClassic()
{
    std::srand(std::time(0));

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDHT, WINDOW_HEIGHT),
                            "Triangle Classic",
                            sf::Style::Titlebar); // need this to make the winow
                                                // floating on my system
    window.setFramerateLimit(60);

    sf::VertexArray triangle(sf::Triangles, 3);

    triangle[0].position = sf::Vector2f(10, WINDOW_HEIGHT / 2.f);
    triangle[1].position = sf::Vector2f(WINDOW_WIDHT - 10, WINDOW_HEIGHT/ 2.f);
    triangle[2].position = sf::Vector2f(WINDOW_WIDHT/ 2.f, 10);

    triangle[0].color = sf::Color::Red;
    triangle[1].color = sf::Color::Blue;
    triangle[2].color = sf::Color::Green;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(triangle);
        window.display();
    }

}