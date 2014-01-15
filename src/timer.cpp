/*
	Name: emuGB
	Copyright: Miguel Cantón Cortés
	Date: 29/02/12 04:15
	Description: GameBoy Classic emulator
*/

#include "timer.h"

const byte Timer::speed[] = { 1, 64, 16, 4 };

Timer::Timer() {
	mmu = 0;
	contadorCiclos = 0;
	contadorBase = 0;
}

void Timer::reset() {
	printf("Timer: reseteando contadores...\n");
	
	contadorCiclos = 0;
	contadorBase = 0;
	if(mmu) {
		mmu->wb(COUNTER, 0);
		mmu->wb(DIVIDER, 0);
	}
}

void Timer::conectarConMMU(MMU *mmuRef) {
	printf("Timer: Conectando a la MMU...\n");
	
	mmu = mmuRef;
}

void Timer::step(int ciclos) {
	byte contAux;
	//Obtener control
	byte control = mmu->rb(CONTROL);
	
	if(control&0x04) { //Timer activado
		//Actualizar contador de ciclos
		contadorCiclos += ciclos;
		if(contadorCiclos >= BASE_CONTADOR_INC) {
			contadorCiclos -= BASE_CONTADOR_INC;
			contadorBase++;
		}
		
		//Actualizar divider
		if(contadorBase%4 == 0)
			mmu->wb(DIVIDER, (mmu->rb(DIVIDER)+1)&0xFF);
		
		//Actualizar counter
		if((contadorBase%speed[control&0x03]) == 0) {
			contAux = mmu->rb(COUNTER);
			if(contAux == 0xFF) {
				contAux = mmu->rb(MODULO);
				//Interrupción
				mmu->wb(INTERRUPT_FLAG, (mmu->rb(INTERRUPT_FLAG)|0x04));
			} else contAux++;
			mmu->wb(COUNTER, contAux);
		}
		
		if(contadorBase == 64)
			contadorBase = 0;
	}
}
