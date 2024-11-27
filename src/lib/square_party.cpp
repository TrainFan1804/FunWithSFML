#include "square_party.h"
#include "vector_helper.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Window/Event.hpp>

const int VERT_ARRAY_SIZE = 4;
const int WINDOW_WIDHT = 1000;
const int WINDOW_HEIGHT = 800;

void squareParty()
{
    std::srand(std::time(0));

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDHT, WINDOW_HEIGHT),
                            "Square Party",
                            sf::Style::Titlebar); // need this to make the winow
                                                // floating on my system
    window.setFramerateLimit(60);

    std::vector<sf::VertexArray> all_vec_arr;

    for (int i = 0; i < 100; i++)
    {
        sf::VertexArray quad(sf::Quads, VERT_ARRAY_SIZE);

        int pos_off_x = (std::rand() % WINDOW_WIDHT) - 100;
        int pos_off_y = (std::rand() % WINDOW_HEIGHT) - 100;

        // define the position of the quad's points
        quad[0].position = sf::Vector2f(10.f + pos_off_x, 10.f + pos_off_y);	// upper left
        quad[1].position = sf::Vector2f(100.f + pos_off_x, 10.f + pos_off_y);	// upper right
        quad[2].position = sf::Vector2f(100.f + pos_off_x, 100.f + pos_off_y);	// botttom left
        quad[3].position = sf::Vector2f(10.f + pos_off_x, 100.f + pos_off_y);	// bottom right

        // define the color of the quad's points
        for (int vert_index = 0; vert_index < quad.getVertexCount(); vert_index++)
        {
            int red_code = std::rand() % 256;
            int green_code = std::rand() % 256;
            int blue_code = std::rand() % 256;

            quad[vert_index].color = sf::Color(red_code, green_code, blue_code);
        }

        all_vec_arr.push_back(quad);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for (auto &tri :all_vec_arr)
        {
            int ev = std::rand() % 3;
            switch (ev)
            {
            case 0:
            {
                int dir_x = (std::rand() % 11) - 5;
                int dir_y = (std::rand() % 11) - 5;
                moveVertex(tri, dir_x, dir_y);
                break;
            }
            case 3:
            // dead code because rectangle will scale too much!
            {
                int scl_fac_x;
                int scl_fac_y;
                do
                {
                    scl_fac_x = (std::rand() % 5) - 2;
                    scl_fac_y = (std::rand() % 5) - 2;
                }
                while (scl_fac_x == 0 || scl_fac_y == 0);

                scaleVertex(tri, scl_fac_x, scl_fac_y);
                break;
            }
            case 2:
            {
                int phi = std::rand() % 2;
                rotateVertex(tri, phi);
                break;
            }
            }
        }

        window.clear();
        for (auto &tri : all_vec_arr)
        {
            window.draw(tri);
        }

        window.display();
    }

}