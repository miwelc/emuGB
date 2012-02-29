#ifndef _CARTSLOT_H_
#define _CARTSLOT_H_

class CartSlot;

#include <stdio.h>
#include <fstream>
#include <assert.h>
#include "tipos.h"

enum CabeceraCartucho {
	ENTRYPOINT = 0x0100,	//4 Bytes
	LOGO = 0x0104,			//48 Bytes
	TITLE = 0x0134,			//16 Bytes
	MANFCODE = 0x013F,		//4 Bytes
	CGBFLAG = 0x0143,		//1 Byte
		GBANDCGB = 0x80,
		CGBONLY = 0xC0,
	NEWLICENSE = 0x0144,	//2 Bytes
	SGBFLAG = 0x0146,		//1 Byte
		NOSGB = 0x00,
		SGBREADY = 0x03,
	CARTTYPE = 0x0147,		//1 Byte
		ROMONLY = 0x00,
	ROMSIZE = 0x0148,		//1 Byte
		ROM32KB = 0x00,
		ROM64KB = 0x01,
	RAMSIZE = 0x0149,		//1 Byte
		NORAM = 0x00,
		RAM2KB = 0x01,
		RAM8KB = 0x02,
		RAM32KB = 0x03,
	DESTCODE = 0x014A,		//1 Byte
		JAPANESE = 0x00,
		NONJAPANESE = 0x01,
	OLDLICENSE = 0x014B,	//1 Byte
		NEWLICENSEUSED = 0x33,
	GAMEVERSION = 0x014C,	//1 Byte
	HEADERCHECKSUM = 0x014D,//1 Byte
	GLOBALCHECKSUM = 0x014E,//2 Byte
	ENDHEADER = 0x0150
};

class CartSlot {
	private:
		unsigned int BytesROM;
		byte *ROMdata;
		bool ROMCargada;
		unsigned int BytesERAM;
		byte *externalRAM;

	public:
		CartSlot();
		~CartSlot();
		void cargarROM(const char* dir);

		byte rb(word address);
		void rb(word address, byte &valor);
		word rw(word address);
		void rw(word address, word &valor);
		void wb(word address, byte valor);
		void ww(word address, word valor);
		
		byte rbERAM(word address);
		void rbERAM(word address, byte &valor);
		word rwERAM(word address);
		void rwERAM(word address, word &valor);
		void wbERAM(word address, byte valor);
		void wwERAM(word address, word valor);
};

#endif
