#ifndef VECTOR_HELPER_H
#define VECTOR_HELPER_H

#include <SFML/Graphics/VertexArray.hpp>

void rotateVertex(sf::VertexArray &vertex_arr, double phi);

void moveVertex(sf::VertexArray &vertex_arr, double x_dir, double y_dir);

void scaleVertex(sf::VertexArray &vertex_arr, double x_scl, double y_scl);

#endif // VECTOR_HELPER_H