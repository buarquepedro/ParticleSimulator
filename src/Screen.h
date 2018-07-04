/*
 * Screen.h
 *
 *  Created on: Mar 16, 2017
 *      Author: PedroBuarque
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include <iostream>
#include <SDL.h>

namespace particleSDL {

class Screen {
public:
	const static int SCREEN_WIDTH;
	const static int SCREEN_HEIGHT;

	Screen();
	bool init(void);
	void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
	bool processEvents(void);
	void update(void);
	void boxBlur(void);
	void clear(void);
	void close(void);

private:
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Texture *m_texture;
	Uint32 *m_mainBuffer;
	Uint32 *m_auxBuffer;
};

}

#endif /* SCREEN_H_ */
