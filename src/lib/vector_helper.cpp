#include "vector_helper.h"

#include <cmath>

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
