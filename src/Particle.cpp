/*
 * Particle.cpp
 *
 *  Created on: Mar 17, 2017
 *      Author: PedroBuarque
 */

#include "Particle.h"

namespace particleSDL {

Particle::Particle() : m_x(0), m_y(0) {
	init();
}

void Particle::init(void) {
	m_x = 0;
	m_y = 0;
	m_direction = (2.0 * M_PI * rand()) / RAND_MAX;
	m_speed = (0.05 * rand()) / RAND_MAX;
	m_speed *= m_speed;
}

void Particle::update(int elapsed) {
	m_direction += elapsed * 0.0005;

	double x_speed = m_speed * cos(m_direction);
	double y_speed = m_speed * sin(m_direction);

	m_x += x_speed * elapsed;
	m_y += y_speed * elapsed;

	if (m_x < -1 || m_x > 1 || m_y < -1 || m_y > 1) {
		init();
	}

	if (rand() < RAND_MAX / 100) {
		init();
	}
}

}
