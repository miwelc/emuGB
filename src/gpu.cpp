/*
	Name: emuGB
	Copyright: Miguel Cantón Cortés
	Date: 29/02/12 04:15
	Description: GameBoy Classic emulator
*/

#include "gpu.h"

GPU::GPU() {
	mmu = 0;
	estado = SCANLINE_VRAM;
	contadorCiclos = 0;
	linea = 0;
	pantalla = 0;
	multiplicador = 2;
	ticks = 0;
	framesSegundo = 0;
	framesSegundoViejos = 0;
	delay = DEFAULT_DELAY;
	limitarFrames = true;
	filtro = false;
	fullScreen = false;
}

GPU::~GPU() {
	SDL_FreeSurface(pantalla);
	SDL_Quit();
}

void GPU::conectarConMMU(MMU *mmuRef) {
	printf("GPU: Conectando a la MMU...\n");
	mmu = mmuRef;
}

bool GPU::step(int ciclos) {
	bool finFrame = false;
	
	byte lcdc = mmu->rb(LCDC);
	if((lcdc&0x80) == 0) return false;
	
	contadorCiclos += ciclos;
	
	if(mmu->rb(LYC) == mmu->rb(LY)) { //LYC = LY
		mmu->wb(STAT, (mmu->rb(STAT)|0x04)); //Coincidence flag
		if(mmu->rb(STAT)&0x40) //Interrupción LYC = LY elegida?
			mmu->wb(INTERRUPT_FLAG, (mmu->rb(INTERRUPT_FLAG)|0x02));
	} else mmu->wb(STAT, (mmu->rb(STAT)&0xFB)); //LYC != LY

	switch(estado) {
		case SCANLINE_VRAM:
			if(contadorCiclos >= 172) {
				contadorCiclos -= 172;
				//Cambiamos a modo OAM-RAM
				mmu->wb(STAT, ((mmu->rb(STAT)|0x02)&0xFE));
				if(mmu->rb(STAT)&0x20) //Interrupción OAM elegida?
					mmu->wb(INTERRUPT_FLAG, (mmu->rb(INTERRUPT_FLAG)|0x02));
				estado = SCANLINE_OAM;
			}
			break;
			
		case SCANLINE_OAM:
			if(contadorCiclos >= 80) {
				contadorCiclos -= 80;
				//Cambiamos a modo H-Blank
				mmu->wb(STAT, (mmu->rb(STAT)&0xFC));
				if(mmu->rb(STAT)&0x08) //Interrupción H-Blank elegida?
					mmu->wb(INTERRUPT_FLAG, (mmu->rb(INTERRUPT_FLAG)|0x02));
				estado = H_BLANK;
			}
			break;
			
		case H_BLANK:
			if(contadorCiclos >= 204) {
				contadorCiclos -= 204;
				dibujarLinea();
				//actualizarPantalla();
				mmu->wb(LY, linea++);
				if(linea == VENTANA_HEIGHT) {
					//Interrupción V-Blank
					mmu->wb(INTERRUPT_FLAG, (mmu->rb(INTERRUPT_FLAG)|0x01));
					//Cambiamos a modo V-Blank
					mmu->wb(STAT, ((mmu->rb(STAT)|0x01)&0xFD));
					if(mmu->rb(STAT)&0x10) //Interrupción V-Blank (STAT)
						mmu->wb(INTERRUPT_FLAG, (mmu->rb(INTERRUPT_FLAG)|0x02));
					estado = V_BLANK;
				} else {//Volvemos al estado inicial para la siguiente linea ///Quitar este bloque hace ganar muchos frames
					estado = SCANLINE_VRAM;
					//Cambiamos a modo transferir datos al LCD Driver
					mmu->wb(STAT, (mmu->rb(STAT)|0x03));
				}
			}
			break;
			
		case V_BLANK:
			if(contadorCiclos >= 456) {
				contadorCiclos -= 456;
				mmu->wb(LY, linea++);
				if(linea > 153) {
					//Cambiamos a modo transferir datos al LCD Driver
					mmu->wb(STAT, (mmu->rb(STAT)|0x03));
					actualizarPantalla();
					ajustarTiming();
					linea = 0;
					estado = SCANLINE_VRAM;
					finFrame = true;
				}
			}
			break;
	}
	return finFrame;
}

void GPU::iniciar() {
	estado = SCANLINE_VRAM;
	contadorCiclos = 0;
	linea = 0;
	ticks = 0;
	framesSegundo = 0;
	framesSegundoViejos = 0;
	delay = DEFAULT_DELAY;
	
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
        printf("GPU: ERROR No se ha podido iniciar SDL\n");
    else
    	printf("GPU: SDL iniciado\n");
    
    //Desactivamos todos los eventos
	for(int i = 0; i < 24; i++)
		SDL_EventState(i, SDL_IGNORE);
        
    cambiarEscalado(multiplicador);
}

void GPU::reset() {
	printf("GPU: Reiniciando GPU...\n");
	
	SDL_Quit();
	iniciar();
}

void GPU::cambiarEscalado(int Multiplicador) {
	int pantallaCompletaFlag = 0;
	printf("GPU: Cambiando escalado a: x%i\n", Multiplicador);
	
	multiplicador = Multiplicador;
	if(fullScreen)
		pantallaCompletaFlag = SDL_FULLSCREEN;
	
	SDL_FreeSurface(pantalla);
	if((pantalla = SDL_SetVideoMode(VENTANA_WIDTH*multiplicador, VENTANA_HEIGHT*multiplicador, 24, pantallaCompletaFlag | SDL_ASYNCBLIT | SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
    	printf("GPU: ERROR No se ha podido iniciar la pantalla\n");
    else
    	printf("GPU: Pantalla iniciada\n");
    	
    vaciarPantalla();
}

void GPU::ajustarTiming() {
	char textoVentana[40];
	double ticksNuevos = SDL_GetTicks();
	if(ticks < ticksNuevos - 1000) { //Cada segundo
		sprintf(textoVentana, "LimitFPS: %s  FPS: %i  Escalado: x%i", limitarFrames ? "On":"Off", framesSegundo, multiplicador);
    	SDL_WM_SetCaption(textoVentana,NULL);
    	if(limitarFrames) {
	    	if(framesSegundo > REFRESCOS_SEGUNDO)
				delay += 0.5;
	    	else if(delay>0)
		    	delay -= 0.5;
		} else delay = 0;
		ticks = ticksNuevos;
		framesSegundoViejos = framesSegundo;
		framesSegundo = 0;
	} else {
		SDL_Delay((int)delay);
		framesSegundo++;
	}
}

/////////////////////////////
////  Funciones Dibujado  ///
/////////////////////////////
void GPU::setPixel(int x, int y, Color color) {
	x *= multiplicador;
	y *= multiplicador;
    Uint8 *p = (Uint8 *)pantalla->pixels + y * pantalla->pitch + x * 3;

    for(int fila = 0; fila < multiplicador; fila++) {
	    for(int columna = 0; columna < multiplicador; columna++)
			p[0+columna*3] = p[1+columna*3] = p[2+columna*3] = color;
		p += pantalla->pitch;
	}
}

Color GPU::getPixel(int x, int y) {
	x *= multiplicador;
	y *= multiplicador;
    Uint8 *p = (Uint8 *)pantalla->pixels + y * pantalla->pitch + x * 3;
    
	return (Color)*p;
}

void GPU::dibujarLinea() {
	byte lcdc = mmu->rb(LCDC);
	if(lcdc&0x01) //Background activado
		dibujarLineaDeBackground();
	if(lcdc&0x02) //Sprites activados
		dibujarLineaDeSprites();
}

void GPU::dibujarLineaDeBackground() {
	VRAM_MEM tileSet;
	VRAM_MEM tileMap;
	byte lcdc = mmu->rb(LCDC);
	byte scy = mmu->rb(SCY);
	byte scx = mmu->rb(SCX);
	word address;
	int filaTile;
	
	if(lcdc&0x10) //TileSet
		tileSet = TILE_SET_1;
	else tileSet = TILE_SET_2;
	
	if(lcdc&0x8) //TileMap
		tileMap = TILE_MAP_1;
	else tileMap = TILE_MAP_0;
	
	//Vamos a la linea correcta del tileMap
	address = tileMap + 32*(int)((scy+linea)/8);
	
	//Vamos a la columna correcta del tileMap
	address += (int)(scx/8);
	
	//Calculamos la linea del Tile
	filaTile = (scy+linea)%8;
	
	//Primer tile (por si aparece cortado)
	printLineOfTile(tileSet, mmu->rb(address++), filaTile, scx%8, 0);
	for(int x = 8-(scx%8); x < VENTANA_WIDTH; x += 8) //Resto de Tiles
		printLineOfTile(tileSet, mmu->rb(address++), filaTile, 0, x);
}

void GPU::printLineOfTile(VRAM_MEM tileSet, byte nTile, int nfilaTile, int xTile, int xPantalla) {
	word datosFila;
	byte codColor;
	
	datosFila = getLineOfTile(tileSet, nTile, nfilaTile);
	for(int x = xTile; x < 8 && x+xPantalla < VENTANA_WIDTH; x++) {
		codColor = ((datosFila >> (14-x*2))&0x03);
		setPixel(xPantalla + x, this->linea, getColor(codColor, BGP));
	}
}

word GPU::getLineOfTile(VRAM_MEM tileSet, byte nTile, int nfilaTile) {
	word address;
	word filaAux, filaRes;
	
	if(tileSet == TILE_SET_1)
		address = tileSet+(nTile*TAM_TILE); //Dirección del tile
	else //TileSet 2
		address = (word)tileSet+(signoW)((signoB)nTile*TAM_TILE); //Dirección del tile
	
	address += nfilaTile*2; //Seleccionamos fila
	
	filaAux = mmu->rw(address);
	//Agrupamos los bits de cada pixel
	filaRes = 0;
	for(int x = 0; x < 8; x++) {
		filaRes |= (((filaAux >> (15-x))&0x01) << (15-x*2)); //Bit más significativo del color
		filaRes |= (((filaAux >> (7-x))&0x01) << (14-x*2));
	}
	
	return filaRes;
}

//Incluye limitación de la GameBoy de 10 sprites por línea
void GPU::dibujarLineaDeSprites() {
	ModoSprites modoSprites;
	byte lcdc = mmu->rb(LCDC);
	RegistrosGPU paleta;
	int filaSprite;
	int xSprite;
	int ySprite;
	byte nSprite;
	byte flags;
	bool prioridad;
	bool hFlip;
	int spritesDibujados = 0;
	
	if(lcdc&0x04) //Modo Sprites
		modoSprites = MODO_8x16;
	else modoSprites = MODO_8x8;
	
	//Recorremos la lista de Sprites en OAM
	for(word i = END_OAM_MEM-TAM_SPRITE_ATTRIBUTE; i >= OAM_MEM && spritesDibujados < 10; i -= TAM_SPRITE_ATTRIBUTE) {
		ySprite = mmu->rb(i);
		xSprite = mmu->rb(i+1);
		if(ySprite > 0 && xSprite > 0) { //Si está en pantalla
			//Corregimos coordenadas
			xSprite -= 8;
			ySprite -= 16;
			
			if(ySprite <= linea && ySprite+modoSprites > linea) { //Si está en la linea a dibujar
				spritesDibujados++;
				nSprite = mmu->rb(i+2);
				
				if(modoSprites == MODO_8x16) //LSB a 0
					nSprite &= 0x7F;
				
				flags = mmu->rb(i+3);
				//Prioridad
				if(flags&0x80)
					prioridad = false;
				else
					prioridad = true;
				
				//Paletas
				if(flags&0x08)
					paleta = OBP1;
				else
					paleta = OBP0;
					
				//H.Flip
				if(flags&0x20)
					hFlip = true;
				else
					hFlip = false;
					
				//V.Flip //Calculamos la linea del sprite
				if(flags&0x40)
					filaSprite = modoSprites-1 - (linea-ySprite); //Invertido
				else
					filaSprite = linea - ySprite;

				printLineOfSprite(nSprite, filaSprite, modoSprites, xSprite, paleta, prioridad, hFlip);
			}
		}
	}
}

void GPU::printLineOfSprite(byte nSprite, int nfilaSprite, ModoSprites modoSprites, int xSprite, RegistrosGPU paleta, bool prioridad, bool flip) {
	word datosFila;
	byte codColor;
	Color color;
	int x = (xSprite < 0 ? -xSprite : 0);
	datosFila = getLineOfSprite(nSprite, nfilaSprite, modoSprites);

	if(flip) {
		for(int i = 7; i >= 0 && x+xSprite < VENTANA_WIDTH; i--) {
			codColor = ((datosFila >> (14-i*2))&0x03);
			color = getColor(codColor, paleta);
			if(color != WHITE && (prioridad || getPixel(xSprite+x, this->linea) == WHITE))
				setPixel(xSprite + x, this->linea, color);
			x++;
		}
	} else {
		for(int i = 0; i < 8 && x+xSprite < VENTANA_WIDTH; i++) {
			codColor = ((datosFila >> (14-i*2))&0x03);
			color = getColor(codColor, paleta);
			if(color != WHITE && (prioridad || getPixel(xSprite+x, this->linea) == WHITE))
				setPixel(xSprite + x, this->linea, color);
			x++;
		}
	}
}

word GPU::getLineOfSprite(byte nSprite, int nfilaSprite, ModoSprites modoSprites) {
	word address;
	word filaAux, filaRes;
	
	if(modoSprites == MODO_8x8)
		address = TILE_SET_1+(nSprite*TAM_TILE); //Dirección del sprite
	else //MODO_8x16
		address = TILE_SET_1+(nSprite*TAM_TILE*2); //Dirección del sprite
	
	address += nfilaSprite*2; //Seleccionamos fila
	
	filaAux = mmu->rw(address);
	//Agrupamos los bits de cada pixel
	filaRes = 0;
	for(int x = 0; x < 8; x++) {
		filaRes |= (((filaAux >> (15-x))&0x01) << (15-x*2)); //Bit más significativo del color
		filaRes |= (((filaAux >> (7-x))&0x01) << (14-x*2));
	}
	
	return filaRes;
}

Color GPU::getColor(byte codColor, RegistrosGPU paleta) {
	byte bgp = mmu->rb(paleta);
	
	switch((bgp>>(codColor*2))&0x03) {
		case 0:
			return WHITE;
		case 1:
			return LIGHT_GREY;
		case 2:
			return DARK_GREY;
		case 3:
		default:
			return BLACK;
	}
}

void GPU::actualizarPantalla() {
	if(filtro)
		filtroCRT();
	SDL_Flip(pantalla);
}

void GPU::vaciarPantalla() {
	for(int x = 0; x < VENTANA_WIDTH; x++)
		for(int y = 0; y < VENTANA_HEIGHT; y++)
			setPixel(x, y, WHITE);
	//actualizarPantalla();
}

void GPU::filtroCRT() {
	Uint8 *p = (Uint8 *)pantalla->pixels;
    for(int fila = 0; fila < VENTANA_HEIGHT*multiplicador; fila++) {
	    for(int columna = 0; columna < VENTANA_WIDTH*multiplicador; columna+=multiplicador+1) {
			Uint8 color = (Uint8)(DARK_GREY*0.3 + p[0+columna*3]*0.7);
			p[0+columna*3] = p[1+columna*3] = p[2+columna*3] = color;
		}
		p += pantalla->pitch;
	}
}


/////////////////////////////
////  Funciones Memoria   ///
/////////////////////////////

/// VRAM
byte GPU::rbVRAM(word address) {
	assert(address < 8192);
	
	return VRAM[address];
}

void GPU::rbVRAM(word address, byte &valor) {
	assert(address < 8192);
	
	valor = VRAM[address];
}

word GPU::rwVRAM(word address) {
	assert(address < 8192);
	
	return VRAM[address] + (VRAM[address+1] << 8);
}

void GPU::rwVRAM(word address, word &valor) {
	assert(address < 8192);
	
	valor = VRAM[address] + (VRAM[address+1] << 8);
}

void GPU::wbVRAM(word address, byte valor) {
	assert(address < 8192);
	
	VRAM[address] = valor;
}

void GPU::wwVRAM(word address, word valor) {
	assert(address < 8192);
	
	VRAM[address] = (valor & 0xFF);
	VRAM[address+1] = (valor >> 8);
}



/// OAM
byte GPU::rbOAM(word address) {
	assert(address < 160);
	
	return OAM[address];
}

void GPU::rbOAM(word address, byte &valor) {
	assert(address < 160);
	
	valor = OAM[address];
}

word GPU::rwOAM(word address) {
	assert(address < 160);
	
	return OAM[address] + (OAM[address+1] << 8);
}

void GPU::rwOAM(word address, word &valor) {
	assert(address < 160);
	
	valor = OAM[address] + (OAM[address+1] << 8);
}

void GPU::wbOAM(word address, byte valor) {
	assert(address < 160);
	
	OAM[address] = valor;
}

void GPU::wwOAM(word address, word valor) {
	assert(address < 160);
	
	OAM[address] = (valor & 0xFF);
	OAM[address+1] = (valor >> 8);
}
