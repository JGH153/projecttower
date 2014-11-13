#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include "RemovableObject.h"


class VortexParticleSystem : public sf::Drawable, public sf::Transformable, public RemovableObject {
public:
	VortexParticleSystem(unsigned int count, float posX, float posY, sf::Color baseParticleColor, sf::PrimitiveType type, int generatorLifetimeMS, float spd);
	~VortexParticleSystem();
	void setEmitter(sf::Vector2f position);
	void update(sf::Time elapsed);
	void killYourself();
	bool stopEmitting;

private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	struct Particle{
		sf::Vector2f velocity;
		sf::Time lifetime;
	};
	float spd;

	sf::Clock timeAtStart;

	void resetParticle(std::size_t index);

	std::vector<Particle> m_particles;
	sf::VertexArray m_vertices;
	sf::Time m_lifetime;
	sf::Vector2f m_emitter;

};