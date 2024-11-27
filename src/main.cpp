#include <SFML/Graphics.hpp>
#include <cmath>

const int VERT_ARRAY_SIZE = 4;
const int WINDOW_WIDHT = 1000;
const int WINDOW_HEIGHT = 800;

void rotateVertex(sf::VertexArray &vertex_arr, double phi);

void moveVertex(sf::VertexArray &vertex_arr, double x_dir, double y_dir);

void scaleVertex(sf::VertexArray &vertex_arr, double x_scl, double y_scl);

int main()
{
    std::srand(std::time(0));

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDHT, WINDOW_HEIGHT),
                            "Fun with vectors",
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

    return 0;
}

void rotateVertex(sf::VertexArray &vertex_arr, double phi)
{
    double rotMat[2][2] = {
        {std::cos(phi), -std::sin(phi)},
        {std::sin(phi), std::cos(phi)}
    };

    // calculate the center of the rectangle to stop rectangle from moving when
    // it's scalling
    double center_x = 0;
    double center_y = 0;
    for (int i = 0; i < vertex_arr.getVertexCount(); i++)
    {
        center_x += vertex_arr[i].position.x;
        center_y += vertex_arr[i].position.y;
    }

    center_x /= vertex_arr.getVertexCount();
    center_y /= vertex_arr.getVertexCount();

    for (int i = 0; i < vertex_arr.getVertexCount(); i++)
    {
        // could call moveVertex to handle center moving
        vertex_arr[i].position.x -= center_x;
        vertex_arr[i].position.y -= center_y;

        double coord[2]{vertex_arr[i].position.x, vertex_arr[i].position.y};

        double new_x = rotMat[0][0] * coord[0] + rotMat[0][1] * coord[1];
        double new_y = rotMat[1][0] * coord[0] + rotMat[1][1] * coord[1];

        vertex_arr[i].position.x = new_x;
        vertex_arr[i].position.y = new_y;

        vertex_arr[i].position.x += center_x;
        vertex_arr[i].position.y += center_y;
    }
}

void moveVertex(sf::VertexArray &vertex_arr, double x_dir, double y_dir)
{
    double transMat[3][3] = {
        {1, 0, x_dir},
        {0, 1, y_dir},
        {0, 0, 1}
    };

    for (int i = 0; i < vertex_arr.getVertexCount(); i++)
    {
        double coord[3]{vertex_arr[i].position.x, vertex_arr[i].position.y, 1};

        double new_x = transMat[0][0] * coord[0] + transMat[0][1] * coord[1] + transMat[0][2] * coord[2];
        double new_y = transMat[1][0] * coord[0] + transMat[1][1] * coord[1] + transMat[1][2] * coord[2];

        //if (new_x >= WINDOW_HEIGHT || new_y >= WINDOW_WIDHT) continue;

        vertex_arr[i].position.x = new_x;
        vertex_arr[i].position.y = new_y;
    }
}

void scaleVertex(sf::VertexArray &vertex_arr, double x_scl, double y_scl)
{
    double scaleMat[2][2] = {
        {x_scl, 0},
        {0, y_scl}
    };

    // calculate the center of the rectangle to stop rectangle from moving when
    // it's scalling
    double center_x = 0;
    double center_y = 0;
    for (int i = 0; i < vertex_arr.getVertexCount(); i++)
    {
        center_x += vertex_arr[i].position.x;
        center_y += vertex_arr[i].position.y;
    }

    center_x /= vertex_arr.getVertexCount();
    center_y /= vertex_arr.getVertexCount();

    for (int i = 0; i < vertex_arr.getVertexCount(); i++)
    {
        // could call moveVertex to handle center moving
        vertex_arr[i].position.x -= center_x;
        vertex_arr[i].position.y -= center_y;

        double coord[2]{vertex_arr[i].position.x, vertex_arr[i].position.y};

        double new_x = scaleMat[0][0] * coord[0] + scaleMat[0][1] * coord[1];
        double new_y = scaleMat[1][0] * coord[0] + scaleMat[1][1] * coord[1];

        vertex_arr[i].position.x = new_x;
        vertex_arr[i].position.y = new_y;

        vertex_arr[i].position.x += center_x;
        vertex_arr[i].position.y += center_y;
    }
}
