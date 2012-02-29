#include "emuGB.h"

using namespace std;

int main(int argc, char *argv[]) {
	if(argc < 2) {
		cout << "Uso:\n" << "emuGB  'nombreROM'" << endl;
		system("pause");
		exit(1);
	}
	
	
	GameBoy gameboy;
	
	gameboy.cargarROM(argv[1]);
	gameboy.run();
	
	return 0;
}
