#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>


class VortexParticleSystem : public sf::Drawable, public sf::Transformable{
public:
	VortexParticleSystem(unsigned int count);
	void setEmitter(sf::Vector2f position);
	void update(sf::Time elapsed);

private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	struct Particle{
		sf::Vector2f velocity;
		sf::Time lifetime;
	};

	void resetParticle(std::size_t index);

	std::vector<Particle> m_particles;
	sf::VertexArray m_vertices;
	sf::Time m_lifetime;
	sf::Vector2f m_emitter;

};