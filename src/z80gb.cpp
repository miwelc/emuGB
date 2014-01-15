/*
	Name: emuGB
	Copyright: Miguel Cantón Cortés
	Date: 29/02/12 04:15
	Description: GameBoy Classic emulator
*/

#include "z80gb.h"

		word PC;
		word pcAnt;
Z80gb::Z80gb() {
	mmu = 0;
	
	IME = true;
	halt = false;
	stop = false;

	rF = 0;
	rA = 0;
	rB = 0;
	rC = 0;
	rD = 0;
	rE = 0;
	rH = 0;
	rL = 0;
	
	SP = 0;
	PC = 0;
}

void Z80gb::reset() {
	printf("CPU: Reiniciando CPU...\n");
	
	IME = true;
	halt = false;
	stop = false;
		
	rF = 0;
	rA = 0;
	rB = 0;
	rC = 0;
	rD = 0;
	rE = 0;
	rH = 0;
	rL = 0;
	
	SP = 0;
	PC = 0;
}

void Z80gb::conectarConMMU(MMU *mmuRef) {
	printf("CPU: Conectando a la MMU...\n");
	mmu = mmuRef;
}

void Z80gb::step(int &ciclos) {
	byte interrupciones;
	byte opcode;
	
	if(!halt && !stop) {
		//Captación
		pcAnt = PC;
		opcode = mmu->rb(PC); PC++;
		
		//Ejecución
		(this->*instructions[opcode].f)();
		
		//Actualizar contador ciclos
		ciclos = instructions[opcode].ciclos;
#ifndef NDEBUG
		if(PC == 0x100) {
			printf("0xFFFF:%X A:%X F:%X BC:%X DE:%X HL:%X SP:%X\n", (Uint8)mmu->rb(INTERRUPT_ENABLER), rA, rF, rBC(), rDE(), rHL(), SP);
		}
#endif
	} else if(halt) ciclos = 4; else ciclos = 0;
	
	//Comprobación Interrupciones
	interrupciones = mmu->rb(INTERRUPT_ENABLER)&mmu->rb(INTERRUPT_FLAG);
	if(interrupciones)
		halt = false; //Aunque IME esté desactivado (comportamiento especial de la GB)
	if(IME) {
		if(interrupciones)
			stop = false;
		if(interrupciones&0x01) { //VBlank
			mmu->wb(INTERRUPT_FLAG, mmu->rb(INTERRUPT_FLAG)&0xFE);
			ISR_40H();
		}
		if(interrupciones&0x02) { //LCDC
			mmu->wb(INTERRUPT_FLAG, mmu->rb(INTERRUPT_FLAG)&0xFD);
			ISR_48H();
		}
		if(interrupciones&0x04) { //Counter
			mmu->wb(INTERRUPT_FLAG, mmu->rb(INTERRUPT_FLAG)&0xFB);
			ISR_50H();
		}
		if(interrupciones&0x08) { //Serial I/O Transfer Complete
			mmu->wb(INTERRUPT_FLAG, mmu->rb(INTERRUPT_FLAG)&0xF7);
			ISR_58H();
		}
		if(interrupciones&0x10) { //Keypad
			mmu->wb(INTERRUPT_FLAG, mmu->rb(INTERRUPT_FLAG)&0xEF);
			ISR_60H();
		}
	}
}

void Z80gb::setFlags(short z, short n, short h, short c) {
	if(z >= 0) {
		if(z)
			setZF();
		else
			unsetZF();
	}
	if(n >= 0) {
		if(n)
			setN();
		else
			unsetN();
	}
	if(h >= 0) {
		if(h)
			setH();
		else
			unsetH();
	}
	if(c >= 0) {
		if(c)
			setCY();
		else
			unsetCY();
	}
}

short Z80gb::chkH(byte a, byte b) const {
	return (((a+b)&0x0F) < (a&0x0F)) ? 1 : 0;//return (a^b^((byte)(a+b)))&0x10;
}

short Z80gb::chkHres(byte a, byte b) const {
	return (((a-b)&0x0F) > (a&0x0F)) ? 1 : 0;//return (a^b^((byte)(a-b)))&0x10;
}

short Z80gb::chkH(byte n) const {
	return ((n&0xF0) >= 0x10) ? 1 : 0;
}

short Z80gb::chkH(word n) const {
	return ((n&0x00F0) >= 0x0010) ? 1 : 0;
}

//Con signo "wordX = n + sus"
short Z80gb::chkCY(word n, signoB sus) const {
	if(sus < 0)
		return (n+(int32_t)sus < 0) ? 1 : 0;
	else
		return (n+(uint32_t)sus > 0xFFFF) ? 1 : 0;
}

short Z80gb::chkCY(byte n, byte m) const { //Suma
	return ((word)n+m > 0xFF) ? 1 : 0;
}

short Z80gb::chkCY(word n, word m) const { //Suma
	return ((uint32_t)n+m > 0xFFFF) ? 1 : 0;
}

short Z80gb::chkCYres(byte n, byte m) const { //Resta
	return ((signoW)n-m < 0) ? 1 : 0;
}

