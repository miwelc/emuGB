/*
	Name: emuGB
	Copyright: Miguel Cantón Cortés
	Date: 29/02/12 04:15
	Description: GameBoy Classic emulator
*/

#include "CartSlot.h"

using namespace std;

CartSlot::CartSlot() {
	BytesROM = 0;
	ROMdata = 0;
	BytesERAM = 0;
	externalRAM = 0;
	ROMCargada = false;
	escrituraROM = false;
	ROMBank = 1;
	RAMBank = 0;
	RAMBankEnabled = 0;
	MBCMode = 0;
}

CartSlot::~CartSlot() {
	delete [] ROMdata;
	delete [] externalRAM;
}

void CartSlot::cargarROM(const char* dir) {
	ifstream archivo;
	
	//Eliminamos la anterior
	if(ROMCargada) {
		delete [] ROMdata;
		delete [] externalRAM;
		BytesROM = 0;
		ROMdata = 0;
		BytesERAM = 0;
		externalRAM = 0;
		ROMCargada = false;
		ROMBank = 1;
		RAMBank = 0;
		RAMBankEnabled = 0;
		MBCMode = 0;
	}
	
	archivo.open(dir, ios::binary);
	if(archivo.fail()) {
		printf("Error: no se ha podido abrir el archivo '%s'", dir);
		exit(-1);
	}

	//Calculamos tamaño
	archivo.seekg(0, ios::end);
	BytesROM = archivo.tellg();
	archivo.seekg (0, ios::beg);
	
	//Almacenamos en memoria la ROM
	ROMdata = new byte[BytesROM];
	archivo.read((char*)ROMdata, BytesROM);
	
	archivo.close();
	
	MBC = ROMdata[CARTTYPE];
	
	//Creamos la External RAM
	switch(ROMdata[RAMSIZE]) {
		case NORAM:
			BytesERAM = 0;
			break;
		case RAM2KB:
			BytesERAM = 2048;
			externalRAM = new byte[2048];
			break;
		case RAM8KB:
			BytesERAM = 8192;
			externalRAM = new byte[8192];
			break;
		case RAM32KB:
			BytesERAM = 32768;
			externalRAM = new byte[32768];
			break;
	}
	
	ROMCargada = true;
	
	printf("CartSlot: ROM cargada (ROM:%iKb MBC:%i ERAM:%iKb), ", BytesROM/1024, MBC, BytesERAM/1024);
	for(int i = 0; i < 16; i++)
		printf("%c", ROMdata[TITLE+i]);
	printf("\n");
}


///////////////////
///     ROM     ///
///////////////////

byte CartSlot::rb(word address) {
	if(address >= 0x4000)
		address = (address-0x4000) + ROMBank*0x4000;
		
	assert(address < BytesROM);
	
	return ROMdata[address];
}

void CartSlot::rb(word address, byte &valor) {	
	valor = rb(address);
}

word CartSlot::rw(word address) {
	return rb(address) | (rb(address+1) << 8);
}

void CartSlot::rw(word address, word &valor) {	
	valor = rw(address);
}

void CartSlot::wb(word address, byte valor) {	
	if(escrituraROM) {
		word addressTmp = address;
		if(addressTmp >= 0x4000)
			addressTmp = (addressTmp-0x4000) + ROMBank*0x4000;
		assert(addressTmp < BytesROM);
		ROMdata[addressTmp] = valor;
	}
		
	switch(address & 0xF000) {
		case 0x0000:
		case 0x1000:
			if(MBCMode == 1) { //8Rom-4Ram
				if(valor == 0x0A)
					RAMBankEnabled = 1;
				else
					RAMBankEnabled = 0;
			}
			break;
			
		case 0x2000:	//ROM Bank Lbits
		case 0x3000:
			valor &= 0x1F; //5bits
			if(valor == 0) valor = 1;
			ROMBank = (ROMBank & 0x60) | valor;
			break;
			
		case 0x4000:	//ROM Bank Hbits / RAM Bank Lbits
		case 0x5000:
			valor &= 0x03; //2bits
			if(MBCMode == 0)
				ROMBank = (ROMBank & 0x1F) | (valor << 5);
			else {
				RAMBank = valor;
				//RAMBankEnabled = 0;
			}
			break;
			
		case 0x6000:
		case 0x7000:
			valor &= 0x01;
			MBCMode = valor;
			break;
	}
}

void CartSlot::ww(word address, word valor) {
	wb(address, valor & 0xFF);
	wb(address+1, valor >> 8);
}



///////////////////
/// ExternalRAM ///
///////////////////

		extern word PC, pcAnt;
byte CartSlot::rbERAM(word address) {
	if(RAMBankEnabled == 0) return 0;
	
	address += RAMBank*0x2000;
	
	if(address >= BytesERAM) {
		printf("%X %X\n", pcAnt, PC);
	}
	assert(address < BytesERAM);
	
	return externalRAM[address];
}

void CartSlot::rbERAM(word address, byte &valor) {
	valor = rbERAM(address);
}

word CartSlot::rwERAM(word address) {	
	return rbERAM(address) + (rbERAM(address+1) << 8);
}

void CartSlot::rwERAM(word address, word &valor) {
	valor = rwERAM(address);
}

void CartSlot::wbERAM(word address, byte valor) {
	if(RAMBankEnabled == 0) return;
	
	address += RAMBank*0x2000;
	
	if(address >= BytesERAM) {
		printf("%X %X\n", pcAnt, PC);
	}
	assert(address < BytesERAM);
	
	externalRAM[address] = valor;
}

void CartSlot::wwERAM(word address, word valor) {	
	wbERAM(address, valor & 0xFF);
	wbERAM(address+1, valor >> 8);
}
