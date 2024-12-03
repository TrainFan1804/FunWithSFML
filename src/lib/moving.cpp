#include "moving.h"
#include "vector_helper.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

const int VERT_ARRAY_SIZE = 4;
const int WINDOW_WIDHT = 1000;
const int WINDOW_HEIGHT = 800;

void moving()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDHT, WINDOW_HEIGHT),
                            "Moving",
                            sf::Style::Titlebar); // need this to make the winow
                                                // floating on my system
    window.setFramerateLimit(60);

    sf::VertexArray quad(sf::Quads, VERT_ARRAY_SIZE);

    // define the position of the quad's points
    quad[0].position = sf::Vector2f(10.f, 10.f);	// upper left
    quad[1].position = sf::Vector2f(100.f, 10.f);	// upper right
    quad[2].position = sf::Vector2f(100.f, 100.f);	// botttom left
    quad[3].position = sf::Vector2f(10.f, 100.f);	// bottom right

    quad[0].color = sf::Color::Blue; 
    quad[1].color = sf::Color::Blue;
    quad[2].color = sf::Color::Blue;
    quad[3].color = sf::Color::Blue;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            moveVertex(quad, -5, 0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            moveVertex(quad, 5, 0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            moveVertex(quad, 0, -5);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            moveVertex(quad, 0, 5);

        window.clear();
        window.draw(quad);

        window.display();
    }
}
