#ifndef _MMU_H_
#define _MMU_H_

class MMU;
class KeyPad;

#include <fstream>
#include <stdio.h>
#include <assert.h>
#include "tipos.h"
#include "CartSlot.h"
#include "gpu.h"
#include "keypad.h"

enum MapaMemoria {
	BANK0 = 0x0000,
		ENDBIOS = 0x0100,
	BANKX = 0x4000,
	GRAPHICSRAM = 0x8000,
	EXTERNALRAM = 0xA000,
	WORKINGRAM = 0xC000,
	SHADOWRAM = 0xE000,
	OAM = 0xFE00,
		ENDOAM = 0xFEA0,
	MAPPED_IO = 0xFF00,
		KEYPAD_REG = 0xFF00,
		DIVIDER = 0xFF04,
		CONTROL = 0xFF07,
	INTERRUPT_FLAG = 0xFF0F,
	DMA = 0xFF46,
	ZEROPAGERAM = 0xFF80,
	INTERRUPT_ENABLER = 0xFFFF
};

class MMU {
	private:
		static const byte bios[256]; //256B
		CartSlot *cartucho;
		GPU *gpu;
		KeyPad *keypad;
		byte workingRAM[8192]; //8kB
		byte *shadowRAM;
		byte IO[0x80]; //128B
		byte ZRAM[127]; //127B
		byte IE; //Interrupt Enabler Register

	public:
		bool biosEnMemoria;
		MMU();
		void reset();
		bool BIOScargada() const { return biosEnMemoria; }
		void mapearCartSlot(CartSlot *cartRef);
		void mapearGPU(GPU *gpuRef);
		void mapearKeyPad(KeyPad *keyRef);
		void dumpearMemoria(word ini, word fin);

		byte rb(word address);
		void rb(word address, byte &valor);
		word rw(word address);
		void rw(word address, word &valor);

		void wb(word address, byte valor);
		void ww(word address, word valor);
};

#endif
