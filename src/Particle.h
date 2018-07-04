/*
 * Particle.h
 *
 *  Created on: Mar 17, 2017
 *      Author: PedroBuarque
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <cstdlib>
#include <cmath>

namespace particleSDL {

class Particle {
public:
	Particle();
	void update(int elapsed);

	double m_x;
	double m_y;

private:
	void init(void);

	double m_speed;
	double m_direction;

};

}

#endif /* PARTICLE_H_ */
