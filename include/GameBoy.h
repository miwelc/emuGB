#ifndef _GAMEBOY_H_
#define _GAMEBOY_H_

#include <stdio.h>
#include <SDL/SDL.h>
#include "CartSlot.h"
#include "z80gb.h"
#include "MMU.h"
#include "gpu.h"
#include "keypad.h"
#include "timer.h"

enum EstadoEmulador {
	ON,
	PAUSE,
	OFF
};

class GameBoy {
	private:
		CartSlot cartucho;
		KeyPad keypad;
		Z80gb z80;
		MMU mmu;
		GPU gpu;
		Timer timer;
		EstadoEmulador estado;
		
	public:
		GameBoy();
		void run();
		void reset();
		void cargarROM(const char* dir);
};

#endif
