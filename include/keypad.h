#ifndef _KEYPAD_H_
#define _KEYPAD_H_

#include <SDL/SDL.h>
#include <stdio.h>
#include "tipos.h"
#include "MMU.h"

#define MAP_START	SDLK_RETURN
#define MAP_SELECT	SDLK_BACKSPACE
#define MAP_B		SDLK_a
#define MAP_A		SDLK_s

#define MAP_DOWN	SDLK_DOWN
#define MAP_UP		SDLK_UP
#define MAP_LEFT	SDLK_LEFT
#define MAP_RIGHT	SDLK_RIGHT

class KeyPad {
	private:
		enum Columna{
			NINGUNA = 0,
			P14 = 0x10,
			P15 = 0x20
		};
		enum Button {
			NINGUNO = 0xFF,
			START = 0xF7,
			SELECT = 0xFB,
			B = 0xFD,
			A = 0xFE,
			DOWN = 0x7F,
			UP = 0xBF,
			LEFT = 0xDF,
			RIGHT = 0xEF
		};
		byte columna;
		byte botones;
		MMU *mmu;
	public:
		KeyPad();
		void reset();
		void conectarConMMU(MMU *mmuRef);
		void botonPulsado(byte bots);
		void botonSoltado(byte bots);
		void comprobarPulsadas();
		void comprobarSoltadas();
		byte rb();
		void rb(byte &valor);
		void wb(byte valor);
};

#endif
