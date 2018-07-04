/*
 * Swarm.h
 *
 *  Created on: Mar 17, 2017
 *      Author: PedroBuarque
 */

#ifndef SWARM_H_
#define SWARM_H_

#include "Particle.h"

namespace particleSDL {

class Swarm {
public:
	const static int N_PARTICLES;

	Swarm();
	virtual ~Swarm();
	void update(int elapsed);
	particleSDL::Particle *getParticles(void) const {return m_swarm;}

private:
	particleSDL::Particle *m_swarm;
	int lastTime;
};

}

#endif /* SWARM_H_ */
