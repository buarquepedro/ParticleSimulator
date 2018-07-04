//============================================================================
// Name        : ParticleSimulator.cpp
// Author      : 
// Version     :
// Copyright   : Copyright Notice
// Description : Particle Simulator in C++
//============================================================================

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Screen.h"
#include "Particle.h"
#include "Swarm.h"

using namespace std;
using namespace particleSDL;

int main() {

	Screen screen;
	if (!screen.init()) {
		cout << "ERROR: " << SDL_GetError() << endl;
	}

	Swarm swarm;
	while (true) {
		int elapsed = SDL_GetTicks();
		swarm.update(elapsed);

		unsigned char red = (1 + sin(elapsed * 0.0001)) * 128;
		unsigned char green = (1 + sin(elapsed * 0.0002)) * 128;
		unsigned char blue = (1 + sin(elapsed * 0.0003)) * 128;

		const Particle * const pParticles = swarm.getParticles();
		for (unsigned i = 0; i < Swarm::N_PARTICLES; ++i) {
			Particle particle = pParticles[i];
			int x = (particle.m_x + 1) * (Screen::SCREEN_WIDTH / 2);
			int y = particle.m_y * (Screen::SCREEN_WIDTH / 2)
					+ Screen::SCREEN_HEIGHT / 2;
			screen.setPixel(x, y, red, green, blue);
		}

		screen.boxBlur();
		screen.update();

		if (!screen.processEvents()) {
			break;
		}
	}

	screen.close();
	return 0;
}
