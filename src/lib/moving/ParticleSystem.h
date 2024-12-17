#ifndef PARTICLESYSTEM_H 
#define PARTICLESYSTEM_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:
    ParticleSystem(unsigned int count);
    void setEmitter(sf::Vector2f position);
    void update(sf::Time elapsed);
private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    struct Particle
    {
        sf::Vector2f velocity;
        sf::Time lifetime;
    };
    void resetParticle(std::size_t index);
    std::vector<Particle> m_particles;
    sf::VertexArray m_vertices;
    sf::Time m_lifetime;
    sf::Vector2f m_emitter;
};

#endif // MOVING_H
