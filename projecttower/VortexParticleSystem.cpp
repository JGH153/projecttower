#include "VortexParticleSystem.h"


VortexParticleSystem::VortexParticleSystem(unsigned int count) :
	m_particles(count),
	m_vertices(sf::Points, count),
	m_lifetime(sf::seconds(3)),
	m_emitter(0, 0){

	for (std::size_t i = 0; i < m_particles.size(); ++i){
		resetParticle(i);
		m_vertices[i].position = sf::Vector2f(-1000.f, -1000.f);
		float percent = (float)i / (float)m_particles.size();
		//std::cout << percent << std::endl;
		m_particles[i].lifetime = sf::milliseconds(((std::rand() % 2000) + 1000) * percent);
	}
}

void VortexParticleSystem::setEmitter(sf::Vector2f position){
	m_emitter = position;
}

void VortexParticleSystem::update(sf::Time elapsed){

	for (std::size_t i = 0; i < m_particles.size(); ++i){

		// update the particle lifetime
		Particle& p = m_particles[i];
		p.lifetime -= elapsed;

		// if the particle is dead, respawn it
		if (p.lifetime <= sf::Time::Zero)
			resetParticle(i);

		// update the position of the corresponding vertex
		m_vertices[i].position += p.velocity * elapsed.asSeconds();

		// update the alpha (transparency) of the particle according to its lifetime
		float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
		m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);

	}
}

void VortexParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	// apply the transform
	states.transform *= getTransform();

	// our particles don't use a texture
	states.texture = NULL;

	// draw the vertex array
	target.draw(m_vertices, states);
}

void VortexParticleSystem::resetParticle(std::size_t index){
	// give a random velocity and lifetime to the particle
	float angle = (std::rand() % 360) * 3.1415926f / 180.f;
	float speed = (std::rand() % 50) + 50.f;
	m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
	m_particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);

	// reset the position of the corresponding vertex
	m_vertices[index].position = m_emitter;
	//m_vertices[index].position = sf::Vector2f(std::rand() % 800, std::rand() % 600);

	/*m_vertices[index].color.r = 255;
	m_vertices[index].color.g = 0;
	m_vertices[index].color.b = 0;*/
}