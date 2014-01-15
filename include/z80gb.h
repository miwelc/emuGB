#ifndef _Z80GB_H_
#define _Z80GB_H_

class Z80gb;

#include <fstream>
#include <stdio.h>
#include "tipos.h"
#include "MMU.h"


const double CPU_CLOCK = 4194304; //Hz

enum MascarasFlag {
	flagZF = 0x80,
	noflagZF = 0x70,
	flagN = 0x40,
	noflagN = 0xB0,
	flagH = 0x20, /////
	noflagH = 0xD0,
	flagCY = 0x10,
	noflagCY = 0xE0
};

class Z80gb {
	public:
		bool IME;
		bool halt;
		bool stop;
		Z80gb();
		void reset();
		void conectarConMMU(MMU *mmuRef);
		void step(int &ciclos);
		
		//Interrupciones
		void ISR_40H();
		void ISR_48H();
		void ISR_50H();
		void ISR_58H();
		void ISR_60H();
		
	private:
		//MAPEO DEL INSTRUCTION SET
		typedef void (Z80gb:: *Funcion)();
		struct Instruccion {
			Funcion f; //Puntero a la función
			int ciclos; //Número de ciclos de la instrucción
		};
		static Instruccion instructions[0x100];
		static Instruccion CBinstructions[0x100];
		
		/// MEMORY MANAGEMENT UNIT
		MMU *mmu;
		
		/// REGISTROS 8BITS
		byte rF, rF2;
		byte rA, rA2;
		byte rB, rB2;
		byte rC, rC2;
		byte rD, rD2;
		byte rE, rE2;
		byte rH, rH2;
		byte rL, rL2;
		
		/// REGISTROS DE 16BITS
		word SP;
		
	word rAF() { return (rA << 8); }
	void rAF(word AF) { /*rF = (AF & 0xFF);*/ rA = (AF >> 8); }
		
		word rBC() { return rC | (rB << 8); }
		void rBC(word BC) { rC = (BC & 0xFF); rB = (BC >> 8); }
		
		word rDE() { return rE | (rD << 8); }
		void rDE(word DE) { rE = (DE & 0xFF); rD = (DE >> 8); }
		
		word rHL() { return (rL | (rH << 8)); }
		void rHL(word HL) { rL = (HL & 0xFF); rH = (HL >> 8); }
		
		/// FLAGS
		//c = a + b;
		//if (c < a) carry = 1;
		//c = a - b;
		//if (c > a) carry = 1;
		void setFlags(short z, short n, short h, short c);
		
		bool ZF() const { return rF == (rF | flagZF); }
		void setZF() { rF |= flagZF; }
		void unsetZF() { rF &= noflagZF; }
		
		bool N() const { return rF == (rF | flagN); }
		void setN() { rF |= flagN; }
		void unsetN() { rF &= noflagN; }
		
		short chkH(byte a, byte b) const;
		short chkHres(byte a, byte b) const;
		short chkH(byte n) const;
		short chkH(word n) const;
		bool H() const { return rF == (rF | flagH); }
		void setH() { rF |= flagH; }
		void unsetH() { rF &= noflagH; }
		
		short chkCY(word n, signoB sus) const; //Suma o resta
		short chkCY(byte n, byte m) const; //Suma
		short chkCY(word n, word m) const; //Suma
		short chkCYres(byte n, byte m) const; //Resta
		bool CY() const { return rF == (rF | flagCY); }
		void setCY() { rF |= flagCY; }
		void unsetCY() { rF &= noflagCY; }
		
		void saveRegs();
		void loadRegs();
		/// INSTRUCCIONES MÁQUINA
		void noImplementado();
/////////////////////
///  8-Bit Loads  ///
/////////////////////
/// LD
		void LD_A_n8(); //0x3E
		void LD_B_n8(); //0x06
		void LD_C_n8(); //0x0E
		void LD_D_n8(); //0x16
		void LD_E_n8(); //0x1E
		void LD_H_n8(); //0x26
		void LD_L_n8(); //0x2E
		void LD_mHL_n8(); //0x36

		void LD_mBC_A(); //0x02
		void LD_mDE_A(); //0x12

		void LD_mHL_B(); //0x70
		void LD_mHL_C(); //0x71
		void LD_mHL_D(); //0x72
		void LD_mHL_E(); //0x73
		void LD_mHL_H(); //0x74
		void LD_mHL_L(); //0x75
		void LD_mHL_A(); //0x77

		void LD_A_mBC(); //0x0A
		void LD_A_mDE(); //0x1A
		void LD_A_B(); //0x78
		void LD_A_C(); //0x79
		void LD_A_D(); //0x7A
		void LD_A_E(); //0x7B
		void LD_A_H(); //0x7C
		void LD_A_L(); //0x7D
		void LD_A_mHL(); //0x7E
		void LD_A_A(); //0x7F
		void LD_A_mCo(); //0xF2
		void LD_A_mn16(); //0xFA

		void LD_B_B(); //0x40
		void LD_B_C(); //0x41
		void LD_B_D(); //0x42
		void LD_B_E(); //0x43
		void LD_B_H(); //0x44
		void LD_B_L(); //0x45
		void LD_B_mHL(); //0x46
		void LD_B_A(); //0x47

		void LD_C_B(); //0x48
		void LD_C_C(); //0x49
		void LD_C_D(); //0x4A
		void LD_C_E(); //0x4B
		void LD_C_H(); //0x4C
		void LD_C_L(); //0x4D
		void LD_C_mHL(); //0x4E
		void LD_C_A(); //0x4F

		void LD_D_B(); //0x50
		void LD_D_C(); //0x51
		void LD_D_D(); //0x52
		void LD_D_E(); //0x53
		void LD_D_H(); //0x54
		void LD_D_L(); //0x55
		void LD_D_mHL(); //0x56
		void LD_D_A(); //0x57

		void LD_E_B(); //0x58
		void LD_E_C(); //0x59
		void LD_E_D(); //0x5A
		void LD_E_E(); //0x5B
		void LD_E_H(); //0x5C
		void LD_E_L(); //0x5D
		void LD_E_mHL(); //0x5E
		void LD_E_A(); //0x5F

		void LD_H_B(); //0x60
		void LD_H_C(); //0x61
		void LD_H_D(); //0x62
		void LD_H_E(); //0x63
		void LD_H_H(); //0x64
		void LD_H_L(); //0x65
		void LD_H_mHL(); //0x66
		void LD_H_A(); //0x67

		void LD_L_B(); //0x68
		void LD_L_C(); //0x69
		void LD_L_D(); //0x6A
		void LD_L_E(); //0x6B
		void LD_L_H(); //0x6C
		void LD_L_L(); //0x6D
		void LD_L_mHL(); //0x6E
		void LD_L_A(); //0x6F

		void LD_mCo_A(); //0xE2
		void LD_mn16_A(); //0xEA

/// LDI 
		void LDI_mHL_A(); //0x22
		void LDI_A_mHL(); //0x2A
/// LDD 
		void LDD_mHL_A(); //0x32
		void LDD_A_mHL(); //0x3A
/// LDH
		void LDH_mn8o_A(); //0xE0
		void LDH_A_mn8o(); //0xF0


//////////////////////
///  16-Bit Loads  ///
//////////////////////
/// LD
		void LD_mn16_SP(); //0x08

		void LD_BC_n16(); //0x01
		void LD_DE_n16(); //0x11
		void LD_HL_n16(); //0x21
		void LD_SP_n16(); //0x31

		void LD_SP_HL(); //0xF9

/// LDHL
		void LDHL_SP_s8(); //0xF8
			
/// PUSH
		void PUSH_AF(); //0xF5
		void PUSH_BC(); //0xC5
		void PUSH_DE(); //0xD5
		void PUSH_HL(); //0xE5

/// POP
		void POP_AF(); //0xF1
		void POP_BC(); //0xC1
		void POP_DE(); //0xD1
		void POP_HL(); //0xE1


//////////////////////
///   8-Bit ALU    ///
//////////////////////

/// ADD
		void ADD_A_A(); //0x87
		void ADD_A_B(); //0x80
		void ADD_A_C(); //0x81
		void ADD_A_D(); //0x82
		void ADD_A_E(); //0x83
		void ADD_A_H(); //0x84
		void ADD_A_L(); //0x85
		void ADD_A_mHL(); //0x86
		void ADD_A_n8(); //0xC6

/// ADC
		void ADC_A_A(); //0x8F
		void ADC_A_B(); //0x88
		void ADC_A_C(); //0x89
		void ADC_A_D(); //0x8A
		void ADC_A_E(); //0x8B
		void ADC_A_H(); //0x8C
		void ADC_A_L(); //0x8D
		void ADC_A_mHL(); //0x8E
		void ADC_A_n8(); //0xCE

/// SUB
		void SUB_A_A(); //0x97
		void SUB_A_B(); //0x90
		void SUB_A_C(); //0x91
		void SUB_A_D(); //0x92
		void SUB_A_E(); //0x93
		void SUB_A_H(); //0x94
		void SUB_A_L(); //0x95
		void SUB_A_mHL(); //0x96
		void SUB_A_n8(); //0xD6
			
/// SBC
		void SBC_A_A(); //0x9F
		void SBC_A_B(); //0x98
		void SBC_A_C(); //0x99
		void SBC_A_D(); //0x9A
		void SBC_A_E(); //0x9B
		void SBC_A_H(); //0x9C
		void SBC_A_L(); //0x9D
		void SBC_A_mHL(); //0x9E
		void SBC_A_n8(); //0xDE
			
/// AND
		void AND_A(); //0xA7
		void AND_B(); //0xA0
		void AND_C(); //0xA1
		void AND_D(); //0xA2
		void AND_E(); //0xA3
		void AND_H(); //0xA4
		void AND_L(); //0xA5
		void AND_mHL(); //0xA6
		void AND_n8(); //0xE6

/// OR
		void OR_A(); //0xB7
		void OR_B(); //0xB0
		void OR_C(); //0xB1
		void OR_D(); //0xB2
		void OR_E(); //0xB3
		void OR_H(); //0xB4
		void OR_L(); //0xB5
		void OR_mHL(); //0xB6
		void OR_n8(); //0xF6

/// XOR
		void XOR_A(); //0xAF
		void XOR_B(); //0xA8
		void XOR_C(); //0xA9
		void XOR_D(); //0xAA
		void XOR_E(); //0xAB
		void XOR_H(); //0xAC
		void XOR_L(); //0xAD
		void XOR_mHL(); //0xAE
		void XOR_n8(); //0xEE

/// CP
		void CP_A(); //0xBF
		void CP_B(); //0xB8
		void CP_C(); //0xB9
		void CP_D(); //0xBA
		void CP_E(); //0xBB
		void CP_H(); //0xBC
		void CP_L(); //0xBD
		void CP_mHL(); //0xBE
		void CP_n8(); //0xFE
			
/// INC
		void INC_A(); //0x3C
		void INC_B(); //0x04
		void INC_C(); //0x0C
		void INC_D(); //0x14
		void INC_E(); //0x1C
		void INC_H(); //0x24
		void INC_L(); //0x2C
		void INC_mHL(); //0x34
			
/// DEC
		void DEC_A(); //0x3D
		void DEC_B(); //0x05
		void DEC_C(); //0x0D
		void DEC_D(); //0x15
		void DEC_E(); //0x1D
		void DEC_H(); //0x25
		void DEC_L(); //0x2D
		void DEC_mHL(); //0x35
		
		
//////////////////////
///   16-Bit ALU   ///
//////////////////////

/// ADD
		void ADD_HL_BC(); //0x09
		void ADD_HL_DE(); //0x19
		void ADD_HL_HL(); //0x29
		void ADD_HL_SP(); //0x39
			
		void ADD_SP_s8(); //0xE8
			
/// INC
		void INC_BC(); //0x03
		void INC_DE(); //0x13
		void INC_HL(); //0x23
		void INC_SP(); //0x33

/// DEC
		void DEC_BC(); //0x0B
		void DEC_DE(); //0x1B
		void DEC_HL(); //0x2B
		void DEC_SP(); //0x3B
		
//////////////////////
///     Jumps      ///
//////////////////////
/// JP
		void JP_n16(); //0xC3
		void JP_NZ_n16(); //0xC2
		void JP_Z_n16(); //0xCA
		void JP_NC_n16(); //0xD2
		void JP_C_n16(); //0xDA

		void JP_mHL(); //0xE9

/// JR
		void JR_s8o(); //0x18
		void JR_NZ_s8o(); //0x20
		void JR_Z_s8o(); //0x28
		void JR_NC_s8o(); //0x30
		void JR_C_s8o(); //0x38

//////////////////////
///     Calls      ///
//////////////////////
/// CALL
		void CALL_n16(); //0xCD

		void CALL_NZ_n16(); //0xC4
		void CALL_Z_n16(); //0xCC
		void CALL_NC_n16(); //0xD4
		void CALL_C_n16(); //0xDC

//////////////////////
///    Restarts    ///
//////////////////////
/// RST
		void RST_00H(); //0xC7
		void RST_08H(); //0xCF
		void RST_10H(); //0xD7
		void RST_18H(); //0xDF
		void RST_20H(); //0xE7
		void RST_28H(); //0xEF
		void RST_30H(); //0xF7
		void RST_38H(); //0xFF
	

//////////////////////
///    Returns     ///
//////////////////////
/// RET
		void RET(); //0xC9

		void RET_NZ(); //0xC0
		void RET_Z(); //0xC8
		void RET_NC(); //0xD0
		void RET_C(); //0xD8

/// RETI
		void RETI(); //0xD9
		
//////////////////////
///     Extra      ///
//////////////////////
		void DAA(); //0x27
		void CPL(); //0x2F
		void CCF(); //0x3F
		void SCF(); //0x37
		void NOP(); //0x00
		void HALT(); //0x76
		void STOP(); //0x10 0xXX
		void DI(); //0xF3
		void EI(); //0xFB
		
///////////////////////////
/// Rotaciones y shifts ///
///////////////////////////
		void RLCA(); //0x07
		void RLA(); //0x17
		void RRCA(); //0x0F
		void RRA(); //0x1F
		
		void RLC_A(); //0xCB 0x07
		void RLC_B(); //0xCB 0x00
		void RLC_C(); //0xCB 0x01
		void RLC_D(); //0xCB 0x02
		void RLC_E(); //0xCB 0x03
		void RLC_H(); //0xCB 0x04
		void RLC_L(); //0xCB 0x05
		void RLC_mHL(); //0xCB 0x06

		void RL_A(); //0xCB 0x17
		void RL_B(); //0xCB 0x10
		void RL_C(); //0xCB 0x11
		void RL_D(); //0xCB 0x12
		void RL_E(); //0xCB 0x13
		void RL_H(); //0xCB 0x14
		void RL_L(); //0xCB 0x15
		void RL_mHL(); //0xCB 0x06

		void RRC_A(); //0xCB 0x0F
		void RRC_B(); //0xCB 0x08
		void RRC_C(); //0xCB 0x09
		void RRC_D(); //0xCB 0x0A
		void RRC_E(); //0xCB 0x0B
		void RRC_H(); //0xCB 0x0C
		void RRC_L(); //0xCB 0x0D
		void RRC_mHL(); //0xCB 0x0E
			
		void RR_A(); //0xCB 0x1F
		void RR_B(); //0xCB 0x18
		void RR_C(); //0xCB 0x19
		void RR_D(); //0xCB 0x1A
		void RR_E(); //0xCB 0x1B
		void RR_H(); //0xCB 0x1C
		void RR_L(); //0xCB 0x1D
		void RR_mHL(); //0xCB 0x0E
			
		void SLA_A(); //0xCB 0x27
		void SLA_B(); //0xCB 0x20
		void SLA_C(); //0xCB 0x21
		void SLA_D(); //0xCB 0x22
		void SLA_E(); //0xCB 0x23
		void SLA_H(); //0xCB 0x24
		void SLA_L(); //0xCB 0x25
		void SLA_mHL(); //0xCB 0x26
			
		void SRA_A(); //0xCB 0x2F
		void SRA_B(); //0xCB 0x28
		void SRA_C(); //0xCB 0x29
		void SRA_D(); //0xCB 0x2A
		void SRA_E(); //0xCB 0x2B
		void SRA_H(); //0xCB 0x2C
		void SRA_L(); //0xCB 0x2D
		void SRA_mHL(); //0xCB 0x2E
			
		void SRL_A(); //0xCB 0x3F
		void SRL_B(); //0xCB 0x38
		void SRL_C(); //0xCB 0x39
		void SRL_D(); //0xCB 0x3A
		void SRL_E(); //0xCB 0x3B
		void SRL_H(); //0xCB 0x3C
		void SRL_L(); //0xCB 0x3D
		void SRL_mHL(); //0xCB 0x3E


//////////////////////
///    0xCB ops    ///
//////////////////////
		void CBops();

/// SWAP
		void SWAP_A(); //0xCB 0x37
		void SWAP_B(); //0xCB 0x30
		void SWAP_C(); //0xCB 0x31
		void SWAP_D(); //0xCB 0x32
		void SWAP_E(); //0xCB 0x33
		void SWAP_H(); //0xCB 0x34
		void SWAP_L(); //0xCB 0x35
		void SWAP_mHL(); //0xCB 0x36

/// BIT
		void BIT_0_A(); //0xCB 0x47
		void BIT_0_B(); //0xCB 0x40
		void BIT_0_C(); //0xCB 0x41
		void BIT_0_D(); //0xCB 0x42
		void BIT_0_E(); //0xCB 0x43
		void BIT_0_H(); //0xCB 0x44
		void BIT_0_L(); //0xCB 0x45
		void BIT_0_mHL(); //0xCB 0x46
			
		void BIT_1_A(); //0xCB 0x4F
		void BIT_1_B(); //0xCB 0x48
		void BIT_1_C(); //0xCB 0x49
		void BIT_1_D(); //0xCB 0x4A
		void BIT_1_E(); //0xCB 0x4B
		void BIT_1_H(); //0xCB 0x4C
		void BIT_1_L(); //0xCB 0x4D
		void BIT_1_mHL(); //0xCB 0x4E
			
		void BIT_2_A(); //0xCB 0x57
		void BIT_2_B(); //0xCB 0x50
		void BIT_2_C(); //0xCB 0x51
		void BIT_2_D(); //0xCB 0x52
		void BIT_2_E(); //0xCB 0x53
		void BIT_2_H(); //0xCB 0x54
		void BIT_2_L(); //0xCB 0x55
		void BIT_2_mHL(); //0xCB 0x56
			
		void BIT_3_A(); //0xCB 0x5F
		void BIT_3_B(); //0xCB 0x58
		void BIT_3_C(); //0xCB 0x59
		void BIT_3_D(); //0xCB 0x5A
		void BIT_3_E(); //0xCB 0x5B
		void BIT_3_H(); //0xCB 0x5C
		void BIT_3_L(); //0xCB 0x5D
		void BIT_3_mHL(); //0xCB 0x5E
			
		void BIT_4_A(); //0xCB 0x67
		void BIT_4_B(); //0xCB 0x60
		void BIT_4_C(); //0xCB 0x61
		void BIT_4_D(); //0xCB 0x62
		void BIT_4_E(); //0xCB 0x63
		void BIT_4_H(); //0xCB 0x64
		void BIT_4_L(); //0xCB 0x65
		void BIT_4_mHL(); //0xCB 0x66
			
		void BIT_5_A(); //0xCB 0x6F
		void BIT_5_B(); //0xCB 0x68
		void BIT_5_C(); //0xCB 0x69
		void BIT_5_D(); //0xCB 0x6A
		void BIT_5_E(); //0xCB 0x6B
		void BIT_5_H(); //0xCB 0x6C
		void BIT_5_L(); //0xCB 0x6D
		void BIT_5_mHL(); //0xCB 0x6E
			
		void BIT_6_A(); //0xCB 0x77
		void BIT_6_B(); //0xCB 0x70
		void BIT_6_C(); //0xCB 0x71
		void BIT_6_D(); //0xCB 0x72
		void BIT_6_E(); //0xCB 0x73
		void BIT_6_H(); //0xCB 0x74
		void BIT_6_L(); //0xCB 0x75
		void BIT_6_mHL(); //0xCB 0x76
			
		void BIT_7_A(); //0xCB 0x7F
		void BIT_7_B(); //0xCB 0x78
		void BIT_7_C(); //0xCB 0x79
		void BIT_7_D(); //0xCB 0x7A
		void BIT_7_E(); //0xCB 0x7B
		void BIT_7_H(); //0xCB 0x7C
		void BIT_7_L(); //0xCB 0x7D
		void BIT_7_mHL(); //0xCB 0x7E
		
/// RES
		void RES_0_A(); //0xCB 0x87
		void RES_0_B(); //0xCB 0x80
		void RES_0_C(); //0xCB 0x81
		void RES_0_D(); //0xCB 0x82
		void RES_0_E(); //0xCB 0x83
		void RES_0_H(); //0xCB 0x84
		void RES_0_L(); //0xCB 0x85
		void RES_0_mHL(); //0xCB 0x86

		void RES_1_A(); //0xCB 0x8F
		void RES_1_B(); //0xCB 0x88
		void RES_1_C(); //0xCB 0x89
		void RES_1_D(); //0xCB 0x8A
		void RES_1_E(); //0xCB 0x8B
		void RES_1_H(); //0xCB 0x8C
		void RES_1_L(); //0xCB 0x8D
		void RES_1_mHL(); //0xCB 0x8E

		void RES_2_A(); //0xCB 0x97
		void RES_2_B(); //0xCB 0x90
		void RES_2_C(); //0xCB 0x91
		void RES_2_D(); //0xCB 0x92
		void RES_2_E(); //0xCB 0x93
		void RES_2_H(); //0xCB 0x94
		void RES_2_L(); //0xCB 0x95
		void RES_2_mHL(); //0xCB 0x96

		void RES_3_A(); //0xCB 0x9F
		void RES_3_B(); //0xCB 0x98
		void RES_3_C(); //0xCB 0x99
		void RES_3_D(); //0xCB 0x9A
		void RES_3_E(); //0xCB 0x9B
		void RES_3_H(); //0xCB 0x9C
		void RES_3_L(); //0xCB 0x9D
		void RES_3_mHL(); //0xCB 0x9E

		void RES_4_A(); //0xCB 0xA7
		void RES_4_B(); //0xCB 0xA0
		void RES_4_C(); //0xCB 0xA1
		void RES_4_D(); //0xCB 0xA2
		void RES_4_E(); //0xCB 0xA3
		void RES_4_H(); //0xCB 0xA4
		void RES_4_L(); //0xCB 0xA5
		void RES_4_mHL(); //0xCB 0xA6

		void RES_5_A(); //0xCB 0xAF
		void RES_5_B(); //0xCB 0xA8
		void RES_5_C(); //0xCB 0xA9
		void RES_5_D(); //0xCB 0xAA
		void RES_5_E(); //0xCB 0xAB
		void RES_5_H(); //0xCB 0xAC
		void RES_5_L(); //0xCB 0xAD
		void RES_5_mHL(); //0xCB 0xAE

		void RES_6_A(); //0xCB 0xB7
		void RES_6_B(); //0xCB 0xB0
		void RES_6_C(); //0xCB 0xB1
		void RES_6_D(); //0xCB 0xB2
		void RES_6_E(); //0xCB 0xB3
		void RES_6_H(); //0xCB 0xB4
		void RES_6_L(); //0xCB 0xB5
		void RES_6_mHL(); //0xCB 0xB6

		void RES_7_A(); //0xCB 0xBF
		void RES_7_B(); //0xCB 0xB8
		void RES_7_C(); //0xCB 0xB9
		void RES_7_D(); //0xCB 0xBA
		void RES_7_E(); //0xCB 0xBB
		void RES_7_H(); //0xCB 0xBC
		void RES_7_L(); //0xCB 0xBD
		void RES_7_mHL(); //0xCB 0xBE



/// SET
		void SET_0_A(); //0xCB 0xC7
		void SET_0_B(); //0xCB 0xC0
		void SET_0_C(); //0xCB 0xC1
		void SET_0_D(); //0xCB 0xC2
		void SET_0_E(); //0xCB 0xC3
		void SET_0_H(); //0xCB 0xC4
		void SET_0_L(); //0xCB 0xC5
		void SET_0_mHL(); //0xCB 0xC6

		void SET_1_A(); //0xCB 0xCF
		void SET_1_B(); //0xCB 0xC8
		void SET_1_C(); //0xCB 0xC9
		void SET_1_D(); //0xCB 0xCA
		void SET_1_E(); //0xCB 0xCB
		void SET_1_H(); //0xCB 0xCC
		void SET_1_L(); //0xCB 0xCD
		void SET_1_mHL(); //0xCB 0xCE

		void SET_2_A(); //0xCB 0xD7
		void SET_2_B(); //0xCB 0xD0
		void SET_2_C(); //0xCB 0xD1
		void SET_2_D(); //0xCB 0xD2
		void SET_2_E(); //0xCB 0xD3
		void SET_2_H(); //0xCB 0xD4
		void SET_2_L(); //0xCB 0xD5
		void SET_2_mHL(); //0xCB 0xD6

		void SET_3_A(); //0xCB 0xDF
		void SET_3_B(); //0xCB 0xD8
		void SET_3_C(); //0xCB 0xD9
		void SET_3_D(); //0xCB 0xDA
		void SET_3_E(); //0xCB 0xDB
		void SET_3_H(); //0xCB 0xDC
		void SET_3_L(); //0xCB 0xDD
		void SET_3_mHL(); //0xCB 0xDE

		void SET_4_A(); //0xCB 0xE7
		void SET_4_B(); //0xCB 0xE0
		void SET_4_C(); //0xCB 0xE1
		void SET_4_D(); //0xCB 0xE2
		void SET_4_E(); //0xCB 0xE3
		void SET_4_H(); //0xCB 0xE4
		void SET_4_L(); //0xCB 0xE5
		void SET_4_mHL(); //0xCB 0xE6

		void SET_5_A(); //0xCB 0xEF
		void SET_5_B(); //0xCB 0xE8
		void SET_5_C(); //0xCB 0xE9
		void SET_5_D(); //0xCB 0xEA
		void SET_5_E(); //0xCB 0xEB
		void SET_5_H(); //0xCB 0xEC
		void SET_5_L(); //0xCB 0xED
		void SET_5_mHL(); //0xCB 0xEE

		void SET_6_A(); //0xCB 0xF7
		void SET_6_B(); //0xCB 0xF0
		void SET_6_C(); //0xCB 0xF1
		void SET_6_D(); //0xCB 0xF2
		void SET_6_E(); //0xCB 0xF3
		void SET_6_H(); //0xCB 0xF4
		void SET_6_L(); //0xCB 0xF5
		void SET_6_mHL(); //0xCB 0xF6

		void SET_7_A(); //0xCB 0xFF
		void SET_7_B(); //0xCB 0xF8
		void SET_7_C(); //0xCB 0xF9
		void SET_7_D(); //0xCB 0xFA
		void SET_7_E(); //0xCB 0xFB
		void SET_7_H(); //0xCB 0xFC
		void SET_7_L(); //0xCB 0xFD
		void SET_7_mHL(); //0xCB 0xFE

};

#endif
