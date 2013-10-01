#ifndef _GPU_H
#define _GPU_H

class GPU;

#include <stdio.h>
#include <SDL/SDL.h>
#include <assert.h>
#include "tipos.h"
#include "MMU.h"

#define VENTANA_WIDTH 160
#define VENTANA_HEIGHT 144
#define REFRESCOS_SEGUNDO 59.727
#define MILISEGUNDOS_REFRESCO 16.7427
#define DEFAULT_DELAY 6

enum RegistrosGPU {
	LCDC = 0xFF40, //Registro de control
	STAT = 0xFF41, //Registro de estado
	SCY = 0xFF42, //Scroll del BG
	SCX = 0xFF43,
	LY = 0xFF44, //Número de línea
	LYC = 0xFF45, //Si es igual a LY en STAT se activa la flag de coincidencia
	BGP = 0xFF47, //Paleta de colores del BG y window
	OBP0 = 0xFF48, //Paleta de colores 0 de sprites
	OBP1 = 0xFF49, //Paleta de colores 1 de sprites
	WY = 0xFF4A, //Posición de la window
	WX = 0xFF4B
};

enum VRAM_MEM {
	TILE_SET_1 = 0x8000,
	TILE_SET_2 = 0x9000,
	TILE_MAP_0 = 0x9800,
	TILE_MAP_1 = 0x9C00
};
const int TAM_TILE = 16;

const int OAM_MEM = 0xFE00;
const int END_OAM_MEM = 0xFEA0;
enum ModoSprites {
	MODO_8x8 = 8,
	MODO_8x16 = 16
};
const int TAM_SPRITE_ATTRIBUTE = 4;

enum Color {
	WHITE = 255,
	LIGHT_GREY = 192,
	DARK_GREY = 96,
	BLACK = 0
};

class GPU {
	private:
		enum Estado {
			SCANLINE_VRAM,
			SCANLINE_OAM,
			H_BLANK,
			V_BLANK
		};
		MMU *mmu;
		Estado estado;
		int contadorCiclos;
		int linea;
		SDL_Surface* pantalla;
		byte VRAM[8192]; //8kB
		byte OAM[160]; //160B
		bool filtro;
		bool fullScreen;
		int multiplicador;
		double ticks;
		int framesSegundo;
		int framesSegundoViejos;
		bool limitarFrames;
		float delay;
		void ajustarTiming();
		void setPixel(int x, int y, Color color);
		Color getPixel(int x, int y);
		void dibujarLinea();
		void dibujarLineaDeBackground();
		void printLineOfTile(VRAM_MEM tileSet, byte nTile, int nfilaTile, int xTile, int xPantalla);
		word getLineOfTile(VRAM_MEM tileSet, byte nTile, int nfilaTile);
		void dibujarLineaDeSprites();
		void printLineOfSprite(byte nSprite, int nfilaSprite, ModoSprites modoSprites, int xSprite, RegistrosGPU paleta, bool prioridad, bool flip = false);
		word getLineOfSprite(byte nSprite, int nfilaSprite, ModoSprites modoSprites);
		Color getColor(byte codColor, RegistrosGPU paleta = BGP);
		void actualizarPantalla();
		void vaciarPantalla();
		void filtroCRT();
	public:
		GPU();
		~GPU();
		void conectarConMMU(MMU *mmuRef);
		bool step(int ciclos);
		void iniciar();
		void reset();
		void cambiarEscalado(int Multiplicador);
		void switchLimiteFPS() { limitarFrames = !limitarFrames; delay = DEFAULT_DELAY; }
		void switchFiltroCRT() { filtro = !filtro; }
		
		byte rbVRAM(word address);
		void rbVRAM(word address, byte &valor);
		word rwVRAM(word address);
		void rwVRAM(word address, word &valor);
		void wbVRAM(word address, byte valor);
		void wwVRAM(word address, word valor);
		
		byte rbOAM(word address);
		void rbOAM(word address, byte &valor);
		word rwOAM(word address);
		void rwOAM(word address, word &valor);
		void wbOAM(word address, byte valor);
		void wwOAM(word address, word valor);
};

#endif
