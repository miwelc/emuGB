#include "CartSlot.h"

using namespace std;

CartSlot::CartSlot() {
	BytesROM = 0;
	ROMdata = 0;
	BytesERAM = 0;
	externalRAM = 0;
	ROMCargada = false;
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
	}
	
	archivo.open(dir, ios::binary);

	//Calculamos tamaño
	archivo.seekg(0, ios::end);
	BytesROM = archivo.tellg();
	archivo.seekg (0, ios::beg);
	
	//Almacenamos en memoria la ROM
	ROMdata = new byte[BytesROM];
	archivo.read((char*)ROMdata, BytesROM);
	
	archivo.close();
	
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
	
	printf("CartSlot: ROM cargada (ROM:%iKb ERAM:%iKb), ", BytesROM/1024, BytesERAM/1024);
	for(int i = 0; i < 16; i++)
		printf("%c", ROMdata[TITLE+i]);
	printf("\n");
}


///////////////////
///     ROM     ///
///////////////////

byte CartSlot::rb(word address) {
	assert(address < BytesROM);
	
	return ROMdata[address];
}

void CartSlot::rb(word address, byte &valor) {
	assert(address < BytesROM);
	
	valor = ROMdata[address];
}

word CartSlot::rw(word address) {
	assert(address < BytesROM);
	
	return ROMdata[address] + (ROMdata[address+1] << 8);
}

void CartSlot::rw(word address, word &valor) {
	assert(address < BytesROM);
	
	valor = ROMdata[address] + (ROMdata[address+1] << 8);
}

void CartSlot::wb(word address, byte valor) {
	assert(address < BytesROM);
	
	ROMdata[address] = valor;
}

void CartSlot::ww(word address, word valor) {
	assert(address < BytesROM);
	
	ROMdata[address] = (valor & 0xFF);
	ROMdata[address+1] = (valor >> 8);
}



///////////////////
/// ExternalRAM ///
///////////////////

byte CartSlot::rbERAM(word address) {
	assert(address < BytesERAM);
	
	return externalRAM[address];
}

void CartSlot::rbERAM(word address, byte &valor) {
	assert(address < BytesERAM);
	
	valor = externalRAM[address];
}

word CartSlot::rwERAM(word address) {
	assert(address < BytesERAM);
	
	return externalRAM[address] + (externalRAM[address+1] << 8);
}

void CartSlot::rwERAM(word address, word &valor) {
	assert(address < BytesERAM);
	
	valor = externalRAM[address] + (externalRAM[address+1] << 8);
}

void CartSlot::wbERAM(word address, byte valor) {
	assert(address < BytesERAM);
	
	externalRAM[address] = valor;
}

void CartSlot::wwERAM(word address, word valor) {
	assert(address < BytesERAM);
	
	externalRAM[address] = (valor & 0xFF);
	externalRAM[address+1] = (valor >> 8);
}
