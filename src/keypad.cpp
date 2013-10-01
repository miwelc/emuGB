/*
	Name: emuGB
	Copyright: Miguel Cantón Cortés
	Date: 29/02/12 04:15
	Description: GameBoy Classic emulator
*/

#include "keypad.h"

KeyPad::KeyPad() {
	botones = NINGUNO;
	columna = NINGUNA;
	mmu = 0;
}

void KeyPad::reset() {
	printf("KeyPad: Reiniciando keypad...\n");
	
	botones = NINGUNO;
	columna = NINGUNA;
}

void KeyPad::conectarConMMU(MMU *mmuRef) {
	printf("KeyPad: Conectando a la MMU...\n");
	mmu = mmuRef;
}

void KeyPad::botonPulsado(byte bots) {
	botones &= bots;
	//Interrupción
	mmu->wb(INTERRUPT_FLAG, (mmu->rb(INTERRUPT_FLAG)|0x10));
}

void KeyPad::botonSoltado(byte bots) {
	botones |= (bots^0xFF);
}

byte KeyPad::rb() {
	if(columna == P14)
		return (botones&0x0F);
	else if(columna == P15)
		return ((botones&0xF0)>>4);
	else
		return 0xF;
}

void KeyPad::rb(byte &valor) {
	valor = rb();
}

void KeyPad::wb(byte valor) {
	columna = (valor&0x30);
}

void KeyPad::comprobarPulsadas() {
	Uint8 *keystate = SDL_GetKeyState(NULL);
	
	if(keystate[MAP_START])
		botonPulsado(START);
	if(keystate[MAP_SELECT])
		botonPulsado(SELECT);
	if(keystate[MAP_B])
		botonPulsado(B);
	if(keystate[MAP_A])
		botonPulsado(A);
		
	if(keystate[MAP_DOWN])
		botonPulsado(DOWN);
	if(keystate[MAP_UP])
		botonPulsado(UP);
	if(keystate[MAP_LEFT])
		botonPulsado(LEFT);
	if(keystate[MAP_RIGHT])
		botonPulsado(RIGHT);
}

void KeyPad::comprobarSoltadas() {
	Uint8 *keystate = SDL_GetKeyState(NULL);
	
	if(!keystate[SDLK_RETURN])
		botonSoltado(START);
	if(!keystate[MAP_SELECT])
		botonSoltado(SELECT);
	if(!keystate[MAP_B])
		botonSoltado(B);
	if(!keystate[MAP_A])
		botonSoltado(A);
		
	if(!keystate[MAP_DOWN])
		botonSoltado(DOWN);
	if(!keystate[MAP_UP])
		botonSoltado(UP);
	if(!keystate[MAP_LEFT])
		botonSoltado(LEFT);
	if(!keystate[MAP_RIGHT])
		botonSoltado(RIGHT);
}
