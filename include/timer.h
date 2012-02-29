#ifndef _TIMER_H
#define _TIMER_H

#include <stdio.h>
#include "mmu.h"

const int BASE_CONTADOR_INC = 4096; //Hz

class Timer {
	private:
		enum TimerMem {
			DIVIDER = 0xFF04,
			COUNTER = 0xFF05,
			MODULO = 0xFF06,
			CONTROL = 0xFF07
		};
		static const byte speed[4]; //Almacenamos el valor necesario del contadorBase para cada modo
		int contadorCiclos;
		int contadorBase; //Se incrementa cada vez que se llega a BASE_CONTADOR
		MMU *mmu;
	public:
		Timer();
		void reset();
		void conectarConMMU(MMU *mmuRef);
		void step(int ciclos);
};

#endif
