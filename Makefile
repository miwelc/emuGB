# Project: emuGB

CPP      = g++ -D__DEBUG__
CC       = gcc -D__DEBUG__
OBJ      = ./obj/CartSlot.o ./obj/emuGB.o ./obj/GameBoy.o ./obj/gpu.o ./obj/instructionSet.o ./obj/MMU.o ./obj/z80gb.o ./obj/keypad.o ./obj/timer.o $(RES)
LINKOBJ  = ./obj/CartSlot.o ./obj/emuGB.o ./obj/GameBoy.o ./obj/gpu.o ./obj/instructionSet.o ./obj/MMU.o ./obj/z80gb.o ./obj/keypad.o ./obj/timer.o $(RES)
LIBS     = -static-libstdc++ -static-libgcc -lSDLmain -lSDL  -g3
INCS     = -I./include
CXXINCS  = 
BIN      = bin/emuGB
CXXFLAGS = $(CXXINCS) -Iinclude -O2 -Wall -pedantic -g3 -std=c++11
CFLAGS   = $(INCS)  -O2 -Wall -pedantic -g3 -std=c++11
RM       = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o $(BIN) $(LIBS)

./obj/CartSlot.o: src/CartSlot.cpp
	$(CPP) -c src/CartSlot.cpp -o ./obj/CartSlot.o $(CXXFLAGS)

./obj/emuGB.o: src/emuGB.cpp
	$(CPP) -c src/emuGB.cpp -o ./obj/emuGB.o $(CXXFLAGS)

./obj/GameBoy.o: src/GameBoy.cpp
	$(CPP) -c src/GameBoy.cpp -o ./obj/GameBoy.o $(CXXFLAGS)

./obj/gpu.o: src/gpu.cpp
	$(CPP) -c src/gpu.cpp -o ./obj/gpu.o $(CXXFLAGS)

./obj/instructionSet.o: src/instructionSet.cpp
	$(CPP) -c src/instructionSet.cpp -o ./obj/instructionSet.o $(CXXFLAGS)

./obj/MMU.o: src/MMU.cpp
	$(CPP) -c src/MMU.cpp -o ./obj/MMU.o $(CXXFLAGS)

./obj/z80gb.o: src/z80gb.cpp
	$(CPP) -c src/z80gb.cpp -o ./obj/z80gb.o $(CXXFLAGS)

./obj/keypad.o: src/keypad.cpp
	$(CPP) -c src/keypad.cpp -o ./obj/keypad.o $(CXXFLAGS)

./obj/timer.o: src/timer.cpp
	$(CPP) -c src/timer.cpp -o ./obj/timer.o $(CXXFLAGS)
