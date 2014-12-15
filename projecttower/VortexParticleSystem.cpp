#include "VortexParticleSystem.h"


VortexParticleSystem::VortexParticleSystem(unsigned int count, float posX, float posY, sf::Color baseParticleColor, sf::PrimitiveType type, int generatorLifetimeMS, float spd) :
	m_particles(count),
	m_vertices(type, count),
	m_lifetime(sf::milliseconds(generatorLifetimeMS)),
	m_emitter(posX, posY) {
	stopEmitting = false;
	this->spd = spd;

	startAlpha = baseParticleColor.a;

	for (std::size_t i = 0; i < m_particles.size(); ++i){
		resetParticle(i);
		m_vertices[i].position = sf::Vector2f(posX, posY);
		float percent = (float)i / (float)m_particles.size();
		m_particles[i].lifetime = sf::milliseconds(((std::rand() % 2000) + 1000) * percent);
		// Get some slight variation in particle color
		m_vertices[i].color.r = baseParticleColor.r + ((rand() % 256) * 0.05) - ((rand() % 256) * 0.05);
		m_vertices[i].color.g = baseParticleColor.g + ((rand() % 256) * 0.05) - ((rand() % 256) * 0.05);
		m_vertices[i].color.b = baseParticleColor.b + ((rand() % 256) * 0.05) - ((rand() % 256) * 0.05);
		m_vertices[i].color.a = baseParticleColor.a + ((rand() % 256) * 0.05) - ((rand() % 256) * 0.05);
		if (m_vertices[i].color.r > 255) {
			m_vertices[i].color.r = 255;
		}
		else if (m_vertices[i].color.r < 0) {
			m_vertices[i].color.r = 0;
		}

		if (m_vertices[i].color.g > 255) {
			m_vertices[i].color.g = 255;
		}
		else if (m_vertices[i].color.g < 0) {
			m_vertices[i].color.g = 0;
		}

		if (m_vertices[i].color.b > 255) {
			m_vertices[i].color.b = 255;
		}
		else if (m_vertices[i].color.b < 0) {
			m_vertices[i].color.b = 0;
		}
	}
	timeAtStart.restart();
}

VortexParticleSystem::~VortexParticleSystem() {


}

void VortexParticleSystem::setEmitter(sf::Vector2f position){
	m_emitter = position;
}

void VortexParticleSystem::update(sf::Time elapsed){
	if (stopEmitting) {
		return;
	}
	if (timeAtStart.getElapsedTime().asMilliseconds() >= m_lifetime.asMilliseconds()) {
		stopEmitting = true;
		return;
	}

	for (std::size_t i = 0; i < m_particles.size(); ++i){

		// update the particle lifetime
		Particle& p = m_particles[i];
		p.lifetime -= elapsed;

		//// if the particle is dead, respawn it
		if (p.lifetime <= sf::Time::Zero){
			resetParticle(i);
		}
		

		// update the position of the corresponding vertex
		m_vertices[i].position += p.velocity * elapsed.asSeconds();

		// update the alpha (transparency) of the particle according to its lifetime
		float ratio = (float)p.lifetime.asMilliseconds() / (float)m_lifetime.asMilliseconds();
		m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * startAlpha);

		// Make the color become more dark the longer it lives
		if (m_vertices[i].color.r - 5 >= 0) {
			m_vertices[i].color.r -= 5;
		}
		if (m_vertices[i].color.g - 5 >= 0) {
			m_vertices[i].color.g -= 5;
		}
		if (m_vertices[i].color.b - 5 >= 0) {
			m_vertices[i].color.b -= 5;
		}

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
	float speed = (std::rand() % 50) + spd;
	m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
	m_particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);

	// reset the position of the corresponding vertex
	m_vertices[index].position = m_emitter;
	//m_vertices[index].position = sf::Vector2f(std::rand() % 800, std::rand() % 600);

	//m_vertices[index].color.r = rand() % 256;
	//m_vertices[index].color.g = rand() % 256;
	//m_vertices[index].color.b = rand() % 256;
}

void VortexParticleSystem::killYourself() {

	delete this;

}