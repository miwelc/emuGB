#include "GameBoy.h"

GameBoy::GameBoy() {
	printf("Emulador de Game Boy Cl%csica           |\n", 0xA0);
	printf("Desarrollado por: Miguel Cant%cn Cort%cs |\n", 0xA2, 0x82);
	printf("%c 2011                                 |\n", 169);
	printf("_______________________________________/\n\n");
	
	//printf("Aumentando prioridad del proceso.../\n\n");
	//SDL_SetThreadPriority(SDL_THREAD_PRIORITY_HIGH);
	
	z80.conectarConMMU(&mmu);
	gpu.conectarConMMU(&mmu);
	timer.conectarConMMU(&mmu);
	keypad.conectarConMMU(&mmu);
	mmu.mapearCartSlot(&cartucho);
	mmu.mapearGPU(&gpu);
	mmu.mapearKeyPad(&keypad);
	estado = OFF;
}

void GameBoy::reset() {
	keypad.reset();
	z80.reset();
	mmu.reset();
	gpu.reset();
}

void GameBoy::cargarROM(const char *dir) {
	reset();
	cartucho.cargarROM(dir);
}

void GameBoy::run() {
	int nCiclosInstruccion;
	bool finFrame;
	std::ofstream salida("./e.txt");
	
	estado = ON;
	printf("GameBoy: Emulaci%cn iniciada\n\n",0xA2);
	//mmu.testMemoria(salida);
	
	for(;;) {
		//Ejecuta siguiente instrucción
		z80.step(nCiclosInstruccion, salida);
		
		//Cede control a la GPU
		finFrame = gpu.step(nCiclosInstruccion);
		
		//Actualizamos timer
		timer.step(nCiclosInstruccion);
		
		//Se comprueba el teclado
		keypad.comprobarPulsadas();
		keypad.comprobarSoltadas();

		if(finFrame) {
			SDL_PumpEvents(); //Actualizamos eventos
			Uint8 *keystate = SDL_GetKeyState(NULL);
			//Salir
			if(keystate[SDLK_q])
				break;
			//Escala
			else if(keystate[SDLK_1])
				gpu.cambiarEscalado(1);
			else if(keystate[SDLK_2])
				gpu.cambiarEscalado(2);
			else if(keystate[SDLK_3])
				gpu.cambiarEscalado(3);
			else if(keystate[SDLK_4])
				gpu.cambiarEscalado(4);
			//Limitador de frames
			else if(keystate[SDLK_l])
				gpu.switchLimiteFPS();
			//Filtro CRT
			else if(keystate[SDLK_f])
				gpu.switchFiltroCRT();
		}
	}
}
