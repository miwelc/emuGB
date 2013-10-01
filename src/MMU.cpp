/*
	Name: emuGB
	Copyright: Miguel Cantón Cortés
	Date: 29/02/12 04:15
	Description: GameBoy Classic emulator
*/

#include "MMU.h"

extern word PC, pcAnt;

MMU::MMU() {
	cartucho = 0;
	for(int i = 0; i < 8192; i++)
		workingRAM[i] = 0;
	for(int i = 0; i < 127; i++)
		ZRAM[i] = 0;
	for(int i = 0; i < 128; i++)
		IO[i] = 0;
	biosEnMemoria = true;
	shadowRAM = workingRAM;
	IE = 0;
}

void MMU::reset() {
	printf("MMU: Reinicianco MMU...\n");
	
	biosEnMemoria = true;
	shadowRAM = workingRAM;
	IE = 0;
}

void MMU::mapearCartSlot(CartSlot *cartRef) {
	printf("MMU: Mapeando CartSlot...\n");
	cartucho = cartRef;
}

void MMU::mapearGPU(GPU *gpuRef) {
	printf("MMU: Mapeando memoria de video...\n");
	gpu = gpuRef;
}

void MMU::mapearKeyPad(KeyPad *keyRef) {
	printf("MMU: Mapeando keypad...\n");
	keypad = keyRef;
}

/////////////////////////////
////  Funciones Lectura   ///
/////////////////////////////

byte MMU::rb(word address) {
	switch(address & 0xF000) {
		case BANK0:
			if(biosEnMemoria && address <= ENDBIOS) {
				if(address == ENDBIOS) {
					printf("MMU: Bios finalizada, descargada de la memoria\n");
					biosEnMemoria = false;
					dumpearMemoria(0xFF05, 0xFF85);
					cartucho->rb(address);
				} else
					return bios[address];
			} else
				return cartucho->rb(address);
			break;
			
		case 0x1000:
		case 0x2000:
		case 0x3000:
			return cartucho->rb(address);
			break;
			
		case BANKX:
		case 0x5000:
		case 0x6000:
		case 0x7000:
			return cartucho->rb(address);
			break;
			
		case GRAPHICSRAM:
		case 0x9000:
			return gpu->rbVRAM(address-GRAPHICSRAM);
			break;
			
		case EXTERNALRAM:
		case 0xB000:
			return cartucho->rbERAM(address-EXTERNALRAM);
			break;
			
		case WORKINGRAM:
		case 0xD000:
			assert(address-WORKINGRAM < 8192);
			return workingRAM[address-WORKINGRAM];
			break;

		case SHADOWRAM:
			assert(address-SHADOWRAM < 8192);
			return shadowRAM[address-SHADOWRAM];
			break;

		case 0xF000:
			switch(address & 0xFF00) {
				/// CONTINUA LA SHADOWRAM
				case 0xF000: case 0xF100: case 0xF200: case 0xF300: case 0xF400: case 0xF500:
				case 0xF600: case 0xF700: case 0xF800: case 0xF900: case 0xFA00: case 0xFB00:
				case 0xFC00: case 0xFD00:
					assert(address-SHADOWRAM < 8192);
					return shadowRAM[address-SHADOWRAM];
					break;
					
				case OAM:
					return address-OAM < 0xA0 ? gpu->rbOAM(address-OAM) : 0;
					break;
					
				case MAPPED_IO:
					if(address < ZEROPAGERAM) {
						if(address == KEYPAD_REG) {
							return keypad->rb();
						} else {
							//switch(address&0x00F0) {case 0x10: case 0x20: case 0x30: return 0;} //audio
							assert(address-MAPPED_IO < 128);
							return IO[address-MAPPED_IO];
						}
					} else {/// ZERO PAGE RAM
						if(address == INTERRUPT_ENABLER)
							return IE;
						else
							return ZRAM[address-ZEROPAGERAM];
					}
					break;
			}
			break;
			
		default:
			return 0;
			break;
	}
}

void MMU::rb(word address, byte &valor) {
	valor = rb(address);
}

word MMU::rw(word address) {
	return rb(address) | (rb(address+1) << 8);
}

void MMU::rw(word address, word &valor) {
	valor = rb(address) | (rb(address+1) << 8);
}



/////////////////////////////
//// Funciones Escritura  ///
/////////////////////////////

void MMU::wb(word address, byte valor) {
	switch(address & 0xF000) {
		case BANK0:
		case 0x1000:
		case 0x2000:
		case 0x3000:
		case BANKX:
		case 0x5000:
		case 0x6000:
		case 0x7000:
			if(address >= ENDBIOS || biosEnMemoria == false)
				cartucho->wb(address, valor);
			break;
			
		case GRAPHICSRAM:
		case 0x9000:
			gpu->wbVRAM(address-GRAPHICSRAM, valor);
			break;
			
		case EXTERNALRAM:
		case 0xB000:
			cartucho->wbERAM(address-EXTERNALRAM, valor);
			break;
			
		case WORKINGRAM:
		case 0xD000:
			assert(address-WORKINGRAM < 8192);
			workingRAM[address-WORKINGRAM] = valor;
			break;
			
		case SHADOWRAM:
			assert(address-SHADOWRAM < 8192);
			shadowRAM[address-SHADOWRAM] = valor;
			break;
			
		case 0xF000:
			switch(address & 0xFF00) {
				/// CONTINUA LA SHADOWRAM
				case 0xF000: case 0xF100: case 0xF200: case 0xF300: case 0xF400: case 0xF500:
				case 0xF600: case 0xF700: case 0xF800: case 0xF900: case 0xFA00: case 0xFB00:
				case 0xFC00: case 0xFD00:
					assert(address-SHADOWRAM < 8192);
					shadowRAM[address-SHADOWRAM] = valor;
					break;
					
				case OAM:
					if(address < ENDOAM) gpu->wbOAM(address-OAM, valor);
					break;
					
				case MAPPED_IO:
					if(address < ZEROPAGERAM) {
						if(address == KEYPAD_REG) {
							keypad->wb(valor);
						} else {
							//switch(address&0x00F0) {case 0x10: case 0x20: case 0x30: return;} //audio
							assert(address-MAPPED_IO < 128);
							if(address == DMA) {
								for(word src = (valor<<8), dest = OAM; dest <= ENDOAM; src++, dest++)
									wb(dest, rb(src));
							} else if(address == DIVIDER)
								IO[address-MAPPED_IO] = 0;
							else
								IO[address-MAPPED_IO] = valor;
						}
					}
					else {/// ZERO PAGE RAM
						if(address == INTERRUPT_ENABLER)
							IE = valor;
						else {
							ZRAM[address-ZEROPAGERAM] = valor;
							if(address == 0xFF86) {
								printf("\n%X   PC-1:%X [PC-1]:%X PC:%X [PC]:%X\n", valor, pcAnt, rb(pcAnt), PC, rb(PC));
							}
						}
					}
					break;
			}
			break;
	}
}

void MMU::ww(word address, word valor) {
	wb(address, (valor & 0xFF));
	wb(address+1, (valor >> 8));
}

/////////////////////////////
////    Dumpeo Memoria    ///
/////////////////////////////
void MMU::dumpearMemoria(word ini, word fin) {
	printf("\t");
	for(word b = 0x00; b <= 0x0F; b++)
		printf("%X  ", b);
	printf("\n");
	
	for(int32_t i = ini&0xFFF0; i <= fin; i += 0x10) {
		printf("[%X]\t", i);
		for(word b = 0x00; b <= 0x0F; b++) {
			if((rb(i+b)&0xF0) == 0x00)
				printf("0");
			printf("%X ", (unsigned short)rb(i+b));

		}
		printf("\n");
	}
}

/////////////////////////////
////         BIOS         ///
/////////////////////////////
const byte MMU::bios[] = {
  0x31, 0xFE, 0xFF, 0xAF, 0x21, 0xFF, 0x9F, 0x32, 0xCB, 0x7C, 0x20, 0xFB, 0x21, 0x26, 0xFF, 0x0E,
  0x11, 0x3E, 0x80, 0x32, 0xE2, 0x0C, 0x3E, 0xF3, 0xE2, 0x32, 0x3E, 0x77, 0x77, 0x3E, 0xFC, 0xE0,
  0x47, 0x11, 0x04, 0x01, 0x21, 0x10, 0x80, 0x1A, 0xCD, 0x95, 0x00, 0xCD, 0x96, 0x00, 0x13, 0x7B,
  0xFE, 0x34, 0x20, 0xF3, 0x11, 0xD8, 0x00, 0x06, 0x08, 0x1A, 0x13, 0x22, 0x23, 0x05, 0x20, 0xF9,
  0x3E, 0x19, 0xEA, 0x10, 0x99, 0x21, 0x2F, 0x99, 0x0E, 0x0C, 0x3D, 0x28, 0x08, 0x32, 0x0D, 0x20,
  0xF9, 0x2E, 0x0F, 0x18, 0xF3, 0x67, 0x3E, 0x64, 0x57, 0xE0, 0x42, 0x3E, 0x91, 0xE0, 0x40, 0x04,
  0x1E, 0x02, 0x0E, 0x0C, 0xF0, 0x44, 0xFE, 0x90, 0x20, 0xFA, 0x0D, 0x20, 0xF7, 0x1D, 0x20, 0xF2,
  0x0E, 0x13, 0x24, 0x7C, 0x1E, 0x83, 0xFE, 0x62, 0x28, 0x06, 0x1E, 0xC1, 0xFE, 0x64, 0x20, 0x06,
  0x7B, 0xE2, 0x0C, 0x3E, 0x87, 0xF2, 0xF0, 0x42, 0x90, 0xE0, 0x42, 0x15, 0x20, 0xD2, 0x05, 0x20,
  0x4F, 0x16, 0x20, 0x18, 0xCB, 0x4F, 0x06, 0x04, 0xC5, 0xCB, 0x11, 0x17, 0xC1, 0xCB, 0x11, 0x17,
  0x05, 0x20, 0xF5, 0x22, 0x23, 0x22, 0x23, 0xC9, 0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B,
  0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E,
  0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC,
  0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E, 0x3c, 0x42, 0xB9, 0xA5, 0xB9, 0xA5, 0x42, 0x3C,
  0x21, 0x04, 0x01, 0x11, 0xA8, 0x00, 0x1A, 0x13, 0xBE, 0x20, 0xFE, 0x23, 0x7D, 0xFE, 0x34, 0x20,
  0xF5, 0x06, 0x19, 0x78, 0x86, 0x23, 0x05, 0x20, 0xFB, 0x86, 0x20, 0xFE, 0x3E, 0x01, 0xE0, 0x50
};
