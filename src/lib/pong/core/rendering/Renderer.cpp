#include "Renderer.h"

void Renderer::add(sf::Drawable &render)
{
    _render_vec.push_back(std::ref(render));
}

void Renderer::render(sf::RenderWindow &window)
{
    for (const auto &draw_obj : _render_vec)
    {
        window.draw(draw_obj);
    }
}

void Renderer::flush()
{
    _render_vec.clear();
}
