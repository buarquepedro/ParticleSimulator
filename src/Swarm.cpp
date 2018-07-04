/*
 * Swarm.cpp
 *
 *  Created on: Mar 17, 2017
 *      Author: PedroBuarque
 */

#include "Swarm.h"

namespace particleSDL {

const int Swarm::N_PARTICLES = 7000;

Swarm::Swarm() : lastTime(0) {
	m_swarm = new particleSDL::Particle[Swarm::N_PARTICLES];
}

void Swarm::update(int elapsed) {
	int interval = elapsed - lastTime;
	for (unsigned i = 0; i < Swarm::N_PARTICLES; ++i) {
		m_swarm[i].update(interval);
	}
	lastTime = elapsed;
}

Swarm::~Swarm() {
	delete[] m_swarm;
}

}
