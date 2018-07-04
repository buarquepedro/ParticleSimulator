/*
 * Screen.cpp
 *
 *  Created on: Mar 16, 2017
 *      Author: PedroBuarque
 */

#include "Screen.h"

namespace particleSDL {

const int Screen::SCREEN_WIDTH = 800;
const int Screen::SCREEN_HEIGHT = 600;

Screen::Screen() : m_window(nullptr), m_renderer(nullptr), m_texture(nullptr),
				   m_mainBuffer(nullptr), m_auxBuffer(nullptr) {}

bool Screen::init(void) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	m_window = SDL_CreateWindow("Particle Fire Simulator",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			Screen::SCREEN_WIDTH, Screen::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (m_window == nullptr) {
		std::cout << SDL_GetError() << std::endl;
		SDL_Quit();
		return false;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET, Screen::SCREEN_WIDTH,
			Screen::SCREEN_HEIGHT);

	if (m_renderer == nullptr) {
		std::cout << SDL_GetError() << std::endl;
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	if (m_texture == nullptr) {
		std::cout << SDL_GetError() << std::endl;
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	m_mainBuffer = new Uint32[Screen::SCREEN_WIDTH * Screen::SCREEN_HEIGHT];
	m_auxBuffer = new Uint32[Screen::SCREEN_WIDTH * Screen::SCREEN_HEIGHT];
	memset(m_mainBuffer, 0x00000000, Screen::SCREEN_WIDTH * Screen::SCREEN_HEIGHT * sizeof(Uint32));
	memset(m_auxBuffer, 0x00000000, Screen::SCREEN_WIDTH * Screen::SCREEN_HEIGHT * sizeof(Uint32));
	return true;
}

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {
	if (x < 0 || x >= Screen::SCREEN_WIDTH || y < 0 || y >= Screen::SCREEN_HEIGHT) {
		return;
	}

	Uint32 color = 0;
	color += red;
	color <<= 8;
	color += green;
	color <<= 8;
	color += blue;
	color <<= 8;
	color += (Uint8) 0xFF;

	m_mainBuffer[(Screen::SCREEN_WIDTH * y) + x] = color;
	return;
}

bool Screen::processEvents(void) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			return false;
		}
	}
	return true;
}

void Screen::update(void) {
	SDL_UpdateTexture(m_texture, nullptr, m_mainBuffer, SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_texture, nullptr, nullptr);
	SDL_RenderPresent(m_renderer);
}

void Screen::boxBlur(void) {
	Uint32 *helper = m_mainBuffer;
	m_mainBuffer = m_auxBuffer;
	m_auxBuffer = helper;

	for (int x = 0; x < Screen::SCREEN_WIDTH; ++x) {
		for  (int y = 0; y < Screen::SCREEN_HEIGHT; ++y) {

			int totalRed = 0;
			int totalGreen = 0;
			int totalBlue = 0;


			for (int row = -1; row <= 1; ++row) {
				for (int col = -1; col <= 1; ++col) {
					int currentX = x + col;
					int currentY = y + row;

					if (currentX >= 0 && currentX < Screen::SCREEN_WIDTH &&
						currentY >= 0 && currentY < Screen::SCREEN_HEIGHT) {

						Uint32 color = m_auxBuffer[(Screen::SCREEN_WIDTH * currentY) + currentX];
						Uint8 red = color >> 24;
						Uint8 green = color >> 16;
						Uint8 blue = color >> 8;

						totalRed += red;
						totalGreen += green;
						totalBlue += blue;
					}
				}
			}

			Uint8 red = totalRed/9;
			Uint8 green = totalGreen/9;
			Uint8 blue = totalBlue/9;
			setPixel(x, y, red, green, blue);

		}
	}
}

void Screen::clear(void) {
	memset(m_mainBuffer, 0x00000000, Screen::SCREEN_WIDTH * Screen::SCREEN_HEIGHT * sizeof(Uint32));
	memset(m_auxBuffer, 0x00000000, Screen::SCREEN_WIDTH * Screen::SCREEN_HEIGHT * sizeof(Uint32));
}

void Screen::close(void) {
	delete[] m_mainBuffer;
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyTexture(m_texture);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

}
