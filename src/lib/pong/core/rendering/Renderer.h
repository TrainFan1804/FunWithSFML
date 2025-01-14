#ifndef RENDERER_H 
#define RENDERER_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <functional>
#include <vector>

class Renderer
{
public:
    void add(sf::Drawable &render);
    void render(sf::RenderWindow &window);
    void flush();
private:
    std::vector<std::reference_wrapper<sf::Drawable>> _render_vec;
};

#endif // RENDERER_H
