/*
	Name: emuGB
	Copyright: Miguel Cantón Cortés
	Date: 29/02/12 04:15
	Description: GameBoy Classic emulator
*/

#ifndef _INSTRUCTIONSET_H_
#define _INSTRUCTIONSET_H_

#include "z80gb.h"


void Z80gb::saveRegs() {
	rF2 = rF;
	rA2 = rA;
	rB2 = rB;
	rC2 = rC;
	rD2 = rD;
	rE2 = rE;
	rH2 = rH;
	rL2 = rL;
}

void Z80gb::loadRegs() {
	rF = rF2;
	rA = rA2;
	rB = rB2;
	rC = rC2;
	rD = rD2;
	rE = rE2;
	rH = rH2;
	rL = rL2;
}

/////////////////////
///  8-Bit Loads  ///
/////////////////////

/// LD
void Z80gb::LD_A_n8() { mmu->rb(PC, rA); PC++; } //0x3E
void Z80gb::LD_B_n8() { mmu->rb(PC, rB);  PC++; } //0x06
void Z80gb::LD_C_n8() { mmu->rb(PC, rC);  PC++; } //0x0E
void Z80gb::LD_D_n8() { mmu->rb(PC, rD);  PC++; } //0x16
void Z80gb::LD_E_n8() { mmu->rb(PC, rE);  PC++; } //0x1E
void Z80gb::LD_H_n8() { mmu->rb(PC, rH);  PC++; } //0x26
void Z80gb::LD_L_n8() { mmu->rb(PC, rL);  PC++; } //0x2E
void Z80gb::LD_mHL_n8() { mmu->wb( rHL(), mmu->rb(PC) );  PC++; } //0x36

void Z80gb::LD_mBC_A() { mmu->wb(rBC(), rA); } //0x02
void Z80gb::LD_mDE_A() { mmu->wb(rDE(), rA); } //0x12

void Z80gb::LD_mHL_B() { mmu->wb(rHL(), rB); } //0x70
void Z80gb::LD_mHL_C() { mmu->wb(rHL(), rC); } //0x71
void Z80gb::LD_mHL_D() { mmu->wb(rHL(), rD); } //0x72
void Z80gb::LD_mHL_E() { mmu->wb(rHL(), rE); } //0x73
void Z80gb::LD_mHL_H() { mmu->wb(rHL(), rH); } //0x74
void Z80gb::LD_mHL_L() { mmu->wb(rHL(), rL); } //0x75
void Z80gb::LD_mHL_A() { mmu->wb(rHL(), rA); } //0x77

void Z80gb::LD_A_mBC() { rA = mmu->rb(rBC()); } //0x0A
void Z80gb::LD_A_mDE() { rA = mmu->rb(rDE()); } //0x1A
void Z80gb::LD_A_B() { rA = rB; } //0x78
void Z80gb::LD_A_C() { rA = rC; } //0x79
void Z80gb::LD_A_D() { rA = rD; } //0x7A
void Z80gb::LD_A_E() { rA = rE; } //0x7B
void Z80gb::LD_A_H() { rA = rH; } //0x7C
void Z80gb::LD_A_L() { rA = rL; } //0x7D
void Z80gb::LD_A_mHL() { rA = mmu->rb(rHL()); } //0x7E
void Z80gb::LD_A_A() { rA = rA; } //0x7F
void Z80gb::LD_A_mCo() { rA = mmu->rb(0xFF00+rC); } //0xF2
void Z80gb::LD_A_mn16() { rA = mmu->rb( mmu->rw(PC) ); PC+=2; } //0xFA

void Z80gb::LD_B_B() { rB = rB; } //0x40
void Z80gb::LD_B_C() { rB = rC; } //0x41
void Z80gb::LD_B_D() { rB = rD; } //0x42
void Z80gb::LD_B_E() { rB = rE; } //0x43
void Z80gb::LD_B_H() { rB = rH; } //0x44
void Z80gb::LD_B_L() { rB = rL; } //0x45
void Z80gb::LD_B_mHL() { rB = mmu->rb(rHL()); } //0x46
void Z80gb::LD_B_A() { rB = rA; } //0x47

void Z80gb::LD_C_B() { rC = rB; } //0x48
void Z80gb::LD_C_C() { rC = rC; } //0x49
void Z80gb::LD_C_D() { rC = rD; } //0x4A
void Z80gb::LD_C_E() { rC = rE; } //0x4B
void Z80gb::LD_C_H() { rC = rH; } //0x4C
void Z80gb::LD_C_L() { rC = rL; } //0x4D
void Z80gb::LD_C_mHL() { rC = mmu->rb(rHL()); } //0x4E
void Z80gb::LD_C_A() { rC = rA; } //0x4F

void Z80gb::LD_D_B() { rD = rB; } //0x50
void Z80gb::LD_D_C() { rD = rC; } //0x51
void Z80gb::LD_D_D() { rD = rD; } //0x52
void Z80gb::LD_D_E() { rD = rE; } //0x53
void Z80gb::LD_D_H() { rD = rH; } //0x54
void Z80gb::LD_D_L() { rD = rL; } //0x55
void Z80gb::LD_D_mHL() { rD = mmu->rb(rHL()); } //0x56
void Z80gb::LD_D_A() { rD = rA; } //0x57

void Z80gb::LD_E_B() { rE = rB; } //0x58
void Z80gb::LD_E_C() { rE = rC; } //0x59
void Z80gb::LD_E_D() { rE = rD; } //0x5A
void Z80gb::LD_E_E() { rE = rE; } //0x5B
void Z80gb::LD_E_H() { rE = rH; } //0x5C
void Z80gb::LD_E_L() { rE = rL; } //0x5D
void Z80gb::LD_E_mHL() { rE = mmu->rb(rHL()); } //0x5E
void Z80gb::LD_E_A() { rE = rA; } //0x5F

void Z80gb::LD_H_B() { rH = rB; } //0x60
void Z80gb::LD_H_C() { rH = rC; } //0x61
void Z80gb::LD_H_D() { rH = rD; } //0x62
void Z80gb::LD_H_E() { rH = rE; } //0x63
void Z80gb::LD_H_H() { rH = rH; } //0x64
void Z80gb::LD_H_L() { rH = rL; } //0x65
void Z80gb::LD_H_mHL() { rH = mmu->rb(rHL()); } //0x66
void Z80gb::LD_H_A() { rH = rA; } //0x67

void Z80gb::LD_L_B() { rL = rB; } //0x68
void Z80gb::LD_L_C() { rL = rC; } //0x69
void Z80gb::LD_L_D() { rL = rD; } //0x6A
void Z80gb::LD_L_E() { rL = rE; } //0x6B
void Z80gb::LD_L_H() { rL = rH; } //0x6C
void Z80gb::LD_L_L() { rL = rL; } //0x6D
void Z80gb::LD_L_mHL() { rL = mmu->rb(rHL()); } //0x6E
void Z80gb::LD_L_A() { rL = rA; } //0x6F

void Z80gb::LD_mCo_A() { mmu->wb(0xFF00+rC, rA); } //0xE2
void Z80gb::LD_mn16_A() { mmu->wb( mmu->rw(PC), rA ); PC+=2;} //0xEA

/// LDI 
void Z80gb::LDI_mHL_A() { LD_mHL_A(); rHL( rHL()+1 ); } //0x22
void Z80gb::LDI_A_mHL() { LD_A_mHL(); rHL( rHL()+1 ); } //0x2A
/// LDD 
void Z80gb::LDD_mHL_A() { LD_mHL_A(); rHL( rHL()-1 ); } //0x32
void Z80gb::LDD_A_mHL() { LD_A_mHL(); rHL( rHL()-1 ); } //0x3A
/// LDH
void Z80gb::LDH_mn8o_A() { mmu->wb( 0xFF00+mmu->rb(PC++), rA); } //0xE0
void Z80gb::LDH_A_mn8o() { mmu->rb( 0xFF00+mmu->rb(PC++), rA); } //0xF0

//////////////////////
///  16-Bit Loads  ///
//////////////////////

/// LD
void Z80gb::LD_mn16_SP() { mmu->ww(mmu->rw(PC), SP); PC+=2; } //0x08

void Z80gb::LD_BC_n16() { rBC(mmu->rw(PC)); PC+=2; } //0x01
void Z80gb::LD_DE_n16() { rDE(mmu->rw(PC)); PC+=2; } //0x11
void Z80gb::LD_HL_n16() { rHL(mmu->rw(PC)); PC+=2; } //0x21
void Z80gb::LD_SP_n16() { SP = mmu->rw(PC); PC+=2; } //0x31

void Z80gb::LD_SP_HL() { SP = rHL(); } //0xF9

/// LDHL
void Z80gb::LDHL_SP_s8() { signoB s8 = mmu->rb(PC++); rHL( SP+s8 );
			setFlags(0,0,chkH(rHL()),chkCY(SP,s8)); } //0xF8
			
/// PUSH
void Z80gb::PUSH_AF() { SP-=2; mmu->ww(SP, rAF()); } //0xF5
void Z80gb::PUSH_BC() { SP-=2; mmu->ww(SP, rBC()); } //0xC5
void Z80gb::PUSH_DE() { SP-=2; mmu->ww(SP, rDE()); } //0xD5
void Z80gb::PUSH_HL() { SP-=2; mmu->ww(SP, rHL()); } //0xE5

/// POP
void Z80gb::POP_AF() { rAF( mmu->rw(SP) ); SP+=2; } //0xF1
void Z80gb::POP_BC() { rBC( mmu->rw(SP) ); SP+=2; } //0xC1
void Z80gb::POP_DE() { rDE( mmu->rw(SP) ); SP+=2; } //0xD1
void Z80gb::POP_HL() { rHL( mmu->rw(SP) ); SP+=2; } //0xE1

//////////////////////
///   8-Bit ALU    ///
//////////////////////

/// ADD
void Z80gb::ADD_A_A() { int acarr = chkCY(rA,rA); int hacarr = chkH(rA,rA); rA += rA; setFlags(rA==0,0,hacarr,acarr); } //0x87
void Z80gb::ADD_A_B() { int acarr = chkCY(rA,rB); int hacarr = chkH(rA,rB); rA += rB; setFlags(rA==0,0,hacarr,acarr); } //0x80
void Z80gb::ADD_A_C() { int acarr = chkCY(rA,rC); int hacarr = chkH(rA,rC); rA += rC; setFlags(rA==0,0,hacarr,acarr); } //0x81
void Z80gb::ADD_A_D() { int acarr = chkCY(rA,rD); int hacarr = chkH(rA,rD); rA += rD; setFlags(rA==0,0,hacarr,acarr); } //0x82
void Z80gb::ADD_A_E() { int acarr = chkCY(rA,rE); int hacarr = chkH(rA,rE); rA += rE; setFlags(rA==0,0,hacarr,acarr); } //0x83
void Z80gb::ADD_A_H() { int acarr = chkCY(rA,rH); int hacarr = chkH(rA,rH); rA += rH; setFlags(rA==0,0,hacarr,acarr); } //0x84
void Z80gb::ADD_A_L() { int acarr = chkCY(rA,rL); int hacarr = chkH(rA,rL); rA += rL; setFlags(rA==0,0,hacarr,acarr); } //0x85
void Z80gb::ADD_A_mHL() { byte b = mmu->rb(rHL()); int acarr = chkCY(rA,b); int hacarr = chkH(rA,b); rA += b;
			setFlags(rA==0,0,hacarr,acarr); } //0x86
void Z80gb::ADD_A_n8() { byte n8 = mmu->rb(PC++); int acarr = chkCY(rA,n8); int hacarr = chkH(rA,n8); rA += n8;
			setFlags(rA==0,0,hacarr,acarr); } //0xC6

/// ADC
void Z80gb::ADC_A_A() { byte sum = CY() + rA; int acarr = chkCY(rA,sum); int hacarr = chkH(rA,sum); rA += sum;
			setFlags(rA==0,0,hacarr,acarr); } //0x8F
void Z80gb::ADC_A_B() { byte sum = CY() + rB; int acarr = chkCY(rA,sum); int hacarr = chkH(rA,sum); rA += sum;
			setFlags(rA==0,0,hacarr,acarr); } //0x88
void Z80gb::ADC_A_C() { byte sum = CY() + rC; int acarr = chkCY(rA,sum); int hacarr = chkH(rA,sum); rA += sum;
			setFlags(rA==0,0,hacarr,acarr); } //0x89
void Z80gb::ADC_A_D() { byte sum = CY() + rD; int acarr = chkCY(rA,sum); int hacarr = chkH(rA,sum); rA += sum;
			setFlags(rA==0,0,hacarr,acarr); } //0x8A
void Z80gb::ADC_A_E() { byte sum = CY() + rE; int acarr = chkCY(rA,sum); int hacarr = chkH(rA,sum); rA += sum;
			setFlags(rA==0,0,hacarr,acarr); } //0x8B
void Z80gb::ADC_A_H() { byte sum = CY() + rH; int acarr = chkCY(rA,sum); int hacarr = chkH(rA,sum); rA += sum;
			setFlags(rA==0,0,hacarr,acarr); } //0x8C
void Z80gb::ADC_A_L() { byte sum = CY() + rL; int acarr = chkCY(rA,sum); int hacarr = chkH(rA,sum); rA += sum;
			setFlags(rA==0,0,hacarr,acarr); } //0x8D
void Z80gb::ADC_A_mHL() { byte sum = CY() + mmu->rb(rHL()); int acarr = chkCY(rA,sum); int hacarr = chkH(rA,sum); rA += sum;
			setFlags(rA==0,0,hacarr,acarr); } //0x8E
void Z80gb::ADC_A_n8() { byte sum = CY() + mmu->rb(PC++); int acarr = chkCY(rA,sum); int hacarr = chkH(rA,sum); rA += sum;
			setFlags(rA==0,0,hacarr,acarr); } //0xCE

/// SUB
void Z80gb::SUB_A_A() { int acarr = chkCYres(rA,rA); int hacarr = chkHres(rA,rA); rA -= rA;
			setFlags(rA==0,1,hacarr,acarr); } //0x97
void Z80gb::SUB_A_B() { int acarr = chkCYres(rA,rB); int hacarr = chkHres(rA,rB); rA -= rB;
			setFlags(rA==0,1,hacarr,acarr); } //0x90
void Z80gb::SUB_A_C() { int acarr = chkCYres(rA,rC); int hacarr = chkHres(rA,rC); rA -= rC;
			setFlags(rA==0,1,hacarr,acarr); } //0x91
void Z80gb::SUB_A_D() { int acarr = chkCYres(rA,rD); int hacarr = chkHres(rA,rD); rA -= rD;
			setFlags(rA==0,1,hacarr,acarr); } //0x92
void Z80gb::SUB_A_E() { int acarr = chkCYres(rA,rE); int hacarr = chkHres(rA,rE); rA -= rE;
			setFlags(rA==0,1,hacarr,acarr); } //0x93
void Z80gb::SUB_A_H() { int acarr = chkCYres(rA,rH); int hacarr = chkHres(rA,rH); rA -= rH;
			setFlags(rA==0,1,hacarr,acarr); } //0x94
void Z80gb::SUB_A_L() { int acarr = chkCYres(rA,rL); int hacarr = chkHres(rA,rL); rA -= rL;
			setFlags(rA==0,1,hacarr,acarr); } //0x95
void Z80gb::SUB_A_mHL() { byte n8 = mmu->rb(rHL()); int acarr = chkCYres(rA,n8); int hacarr = chkHres(rA,n8); rA -= n8;
			setFlags(rA==0,1,hacarr,acarr); } //0x96
void Z80gb::SUB_A_n8() { byte n8 = mmu->rb(PC++); int acarr = chkCYres(rA,n8); int hacarr = chkHres(rA,n8); rA -= n8;
			setFlags(rA==0,1,hacarr,acarr); } //0xD6
			
/// SBC
void Z80gb::SBC_A_A() { byte res = CY() + rA; int acarr = chkCYres(rA,res); int hacarr = chkHres(rA,res); rA -= res;
			setFlags(rA==0,1,hacarr,acarr); } //0x9F
void Z80gb::SBC_A_B() { byte res = CY() + rB; int acarr = chkCYres(rA,res); int hacarr = chkHres(rA,res); rA -= res;
			setFlags(rA==0,1,hacarr,acarr); } //0x98
void Z80gb::SBC_A_C() { byte res = CY() + rC; int acarr = chkCYres(rA,res); int hacarr = chkHres(rA,res); rA -= res;
			setFlags(rA==0,1,hacarr,acarr); } //0x99
void Z80gb::SBC_A_D() { byte res = CY() + rD; int acarr = chkCYres(rA,res); int hacarr = chkHres(rA,res); rA -= res;
			setFlags(rA==0,1,hacarr,acarr); } //0x9A
void Z80gb::SBC_A_E() { byte res = CY() + rE; int acarr = chkCYres(rA,res); int hacarr = chkHres(rA,res); rA -= res;
			setFlags(rA==0,1,hacarr,acarr); } //0x9B
void Z80gb::SBC_A_H() { byte res = CY() + rH; int acarr = chkCYres(rA,res); int hacarr = chkHres(rA,res); rA -= res;
			setFlags(rA==0,1,hacarr,acarr); } //0x9C
void Z80gb::SBC_A_L() { byte res = CY() + rL; int acarr = chkCYres(rA,res); int hacarr = chkHres(rA,res); rA -= res;
			setFlags(rA==0,1,hacarr,acarr); } //0x9D
void Z80gb::SBC_A_mHL() { byte res = CY() + mmu->rb(rHL()); int acarr = chkCYres(rA,res); int hacarr = chkHres(rA,res); rA -= res;
			setFlags(rA==0,1,hacarr,acarr); } //0x9E
void Z80gb::SBC_A_n8() { byte res = CY() + mmu->rb(PC++); int acarr = chkCYres(rA,res); int hacarr = chkHres(rA,res); rA -= res;
			setFlags(rA==0,1,hacarr,acarr); } //0xDE
			
/// AND
void Z80gb::AND_A() { rA &= rA; setFlags(rA==0,0,1,0); } //0xA7
void Z80gb::AND_B() { rA &= rB; setFlags(rA==0,0,1,0); } //0xA0
void Z80gb::AND_C() { rA &= rC; setFlags(rA==0,0,1,0); } //0xA1
void Z80gb::AND_D() { rA &= rD; setFlags(rA==0,0,1,0); } //0xA2
void Z80gb::AND_E() { rA &= rE; setFlags(rA==0,0,1,0); } //0xA3
void Z80gb::AND_H() { rA &= rH; setFlags(rA==0,0,1,0); } //0xA4
void Z80gb::AND_L() { rA &= rL; setFlags(rA==0,0,1,0); } //0xA5
void Z80gb::AND_mHL() { rA &= mmu->rb(rHL()); setFlags(rA==0,0,1,0); } //0xA6
void Z80gb::AND_n8() { rA &= mmu->rb(PC++); setFlags(rA==0,0,1,0); } //0xE6

/// OR
void Z80gb::OR_A() { rA |= rA; setFlags(rA==0,0,0,0); } //0xB7
void Z80gb::OR_B() { rA |= rB; setFlags(rA==0,0,0,0); } //0xB0
void Z80gb::OR_C() { rA |= rC; setFlags(rA==0,0,0,0); } //0xB1
void Z80gb::OR_D() { rA |= rD; setFlags(rA==0,0,0,0); } //0xB2
void Z80gb::OR_E() { rA |= rE; setFlags(rA==0,0,0,0); } //0xB3
void Z80gb::OR_H() { rA |= rH; setFlags(rA==0,0,0,0); } //0xB4
void Z80gb::OR_L() { rA |= rL; setFlags(rA==0,0,0,0); } //0xB5
void Z80gb::OR_mHL() { rA |= mmu->rb(rHL()); setFlags(rA==0,0,0,0); } //0xB6
void Z80gb::OR_n8() { rA |= mmu->rb(PC++); setFlags(rA==0,0,0,0); } //0xF6

/// XOR
void Z80gb::XOR_A() { rA ^= rA; setFlags(rA==0,0,0,0); } //0xAF
void Z80gb::XOR_B() { rA ^= rB; setFlags(rA==0,0,0,0); } //0xA8
void Z80gb::XOR_C() { rA ^= rC; setFlags(rA==0,0,0,0); } //0xA9
void Z80gb::XOR_D() { rA ^= rD; setFlags(rA==0,0,0,0); } //0xAA
void Z80gb::XOR_E() { rA ^= rE; setFlags(rA==0,0,0,0); } //0xAB
void Z80gb::XOR_H() { rA ^= rH; setFlags(rA==0,0,0,0); } //0xAC
void Z80gb::XOR_L() { rA ^= rL; setFlags(rA==0,0,0,0); } //0xAD
void Z80gb::XOR_mHL() { rA ^= mmu->rb(rHL()); setFlags(rA==0,0,0,0); } //0xAE
void Z80gb::XOR_n8() { rA ^= mmu->rb(PC++); setFlags(rA==0,0,0,0); } //0xEE

/// CP
void Z80gb::CP_A() { int acarr = chkCYres(rA,rA); int hacarr = chkHres(rA,rA); byte res = rA - rA;
			setFlags(res==0,1,hacarr,acarr); } //0xBF
void Z80gb::CP_B() { int acarr = chkCYres(rA,rB); int hacarr = chkHres(rA,rB); byte res = rA - rB;
			setFlags(res==0,1,hacarr,acarr); } //0xB8
void Z80gb::CP_C() { int acarr = chkCYres(rA,rC); int hacarr = chkHres(rA,rC); byte res = rA - rC;
			setFlags(res==0,1,hacarr,acarr); } //0xB9
void Z80gb::CP_D() { int acarr = chkCYres(rA,rD); int hacarr = chkHres(rA,rD); byte res = rA - rD;
			setFlags(res==0,1,hacarr,acarr); } //0xBA
void Z80gb::CP_E() { int acarr = chkCYres(rA,rE); int hacarr = chkHres(rA,rE); byte res = rA - rE;
			setFlags(res==0,1,hacarr,acarr); } //0xBB
void Z80gb::CP_H() { int acarr = chkCYres(rA,rH); int hacarr = chkHres(rA,rH); byte res = rA - rH;
			setFlags(res==0,1,hacarr,acarr); } //0xBC
void Z80gb::CP_L() { int acarr = chkCYres(rA,rL); int hacarr = chkHres(rA,rL); byte res = rA - rL;
			setFlags(res==0,1,hacarr,acarr); } //0xBD
void Z80gb::CP_mHL() { byte n8 = mmu->rb(rHL()); int acarr = chkCYres(rA,n8); int hacarr = chkHres(rA,n8); byte res = rA - n8;
			setFlags(res==0,1,hacarr,acarr); } //0xBE
void Z80gb::CP_n8() { byte n8 = mmu->rb(PC++); int acarr = chkCYres(rA,n8); int hacarr = chkHres(rA,n8); byte res = rA - n8;
			setFlags(res==0,1,hacarr,acarr); } //0xFE
			
/// INC
void Z80gb::INC_A() { int hacarr = chkH(rA,1); rA++; setFlags(rA==0,0,hacarr,-1); } //0x3C
void Z80gb::INC_B() { int hacarr = chkH(rB,1); rB++; setFlags(rB==0,0,hacarr,-1); } //0x04
void Z80gb::INC_C() { int hacarr = chkH(rC,1); rC++; setFlags(rC==0,0,hacarr,-1); } //0x0C
void Z80gb::INC_D() { int hacarr = chkH(rD,1); rD++; setFlags(rD==0,0,hacarr,-1); } //0x14
void Z80gb::INC_E() { int hacarr = chkH(rE,1); rE++; setFlags(rE==0,0,hacarr,-1); } //0x1C
void Z80gb::INC_H() { int hacarr = chkH(rH,1); rH++; setFlags(rH==0,0,hacarr,-1); } //0x24
void Z80gb::INC_L() { int hacarr = chkH(rL,1); rL++; setFlags(rL==0,0,hacarr,-1); } //0x2C
void Z80gb::INC_mHL() { byte n8 = mmu->rb(rHL()); int hacarr = chkH(n8,1); n8++; mmu->wb(rHL(), n8);
			setFlags(n8==0,0,hacarr,-1); } //0x34
			
/// DEC
void Z80gb::DEC_A() { int hacarr = chkHres(rA,1); rA--; setFlags(rA==0,1,hacarr,-1); } //0x3D
void Z80gb::DEC_B() { int hacarr = chkHres(rB,1); rB--; setFlags(rB==0,1,hacarr,-1); } //0x05
void Z80gb::DEC_C() { int hacarr = chkHres(rC,1); rC--; setFlags(rC==0,1,hacarr,-1); } //0x0D
void Z80gb::DEC_D() { int hacarr = chkHres(rD,1); rD--; setFlags(rD==0,1,hacarr,-1); } //0x15
void Z80gb::DEC_E() { int hacarr = chkHres(rE,1); rE--; setFlags(rE==0,1,hacarr,-1); } //0x1D
void Z80gb::DEC_H() { int hacarr = chkHres(rH,1); rH--; setFlags(rH==0,1,hacarr,-1); } //0x25
void Z80gb::DEC_L() { int hacarr = chkHres(rL,1); rL--; setFlags(rL==0,1,hacarr,-1); } //0x2D
void Z80gb::DEC_mHL() { byte n8 = mmu->rb(rHL()); int hacarr = chkHres(n8,1); n8--; mmu->wb(rHL(), n8);
			setFlags(n8==0,0,hacarr,-1); } //0x35

//////////////////////
///   16-Bit ALU   ///
//////////////////////

/// ADD
void Z80gb::ADD_HL_BC() { int acarr = chkCY(rHL(),rBC()); rHL(rBC()+rHL());
			setFlags(-1,0,-1,acarr); } //0x09
void Z80gb::ADD_HL_DE() { int acarr = chkCY(rHL(),rDE()); rHL(rDE()+rHL());
			setFlags(-1,0,-1,acarr); } //0x19
void Z80gb::ADD_HL_HL() { int acarr = chkCY(rHL(),rHL()); rHL(rHL()+rHL());
			setFlags(-1,0,-1,acarr); } //0x29
void Z80gb::ADD_HL_SP() { int acarr = chkCY(rHL(),SP); rHL(SP+rHL());
			setFlags(-1,0,-1,acarr); } //0x39
			
void Z80gb::ADD_SP_s8() { signoB s8 = mmu->rb(PC++); int acarr = chkCY(SP,s8); SP += s8;
			setFlags(0,0,-1,acarr); } //0xE8
			
/// INC
void Z80gb::INC_BC() { rBC(rBC()+1); } //0x03
void Z80gb::INC_DE() { rDE(rDE()+1); } //0x13
void Z80gb::INC_HL() { rHL(rHL()+1); } //0x23
void Z80gb::INC_SP() { SP++; } //0x33

/// DEC
void Z80gb::DEC_BC() { rBC(rBC()-1); } //0x0B
void Z80gb::DEC_DE() { rDE(rDE()-1); } //0x1B
void Z80gb::DEC_HL() { rHL(rHL()-1); } //0x2B
void Z80gb::DEC_SP() { SP--; } //0x3B

//////////////////////
///     Jumps      ///
//////////////////////
/// JP
void Z80gb::JP_n16() { PC = mmu->rw(PC); } //0xC3
void Z80gb::JP_NZ_n16() { if(!ZF()) PC = mmu->rw(PC); else PC += 2; } //0xC2
void Z80gb::JP_Z_n16() { if(ZF()) PC = mmu->rw(PC); else PC += 2; } //0xCA
void Z80gb::JP_NC_n16() { if(!CY()) PC = mmu->rw(PC); else PC += 2; } //0xD2
void Z80gb::JP_C_n16() { if(CY()) PC = mmu->rw(PC); else PC += 2; } //0xDA

void Z80gb::JP_mHL() { PC = mmu->rw(rHL()); } //0xE9

/// JR
void Z80gb::JR_s8o() { PC += (signoB)mmu->rb(PC)+1; } //0x18
void Z80gb::JR_NZ_s8o() { if(!ZF()) PC += (signoB)mmu->rb(PC)+1; else PC++; } //0x20
void Z80gb::JR_Z_s8o() { if(ZF()) PC += (signoB)mmu->rb(PC)+1; else PC++; } //0x28
void Z80gb::JR_NC_s8o() { if(!CY()) PC += (signoB)mmu->rb(PC)+1; else PC++; } //0x30
void Z80gb::JR_C_s8o() { if(CY()) PC += (signoB)mmu->rb(PC)+1; else PC++; } //0x38

//////////////////////
///     Calls      ///
//////////////////////
/// CALL
void Z80gb::CALL_n16() { word n16 = mmu->rw(PC); PC += 2; SP-=2; mmu->ww(SP, PC); PC = n16; } //0xCD

void Z80gb::CALL_NZ_n16() { if(!ZF()) { word n16 = mmu->rw(PC); PC += 2; SP-=2; mmu->ww(SP, PC); PC = n16; } else PC += 2; } //0xC4
void Z80gb::CALL_Z_n16() { if(ZF()) { word n16 = mmu->rw(PC); PC += 2; SP-=2; mmu->ww(SP, PC); PC = n16; } else PC += 2; } //0xCC
void Z80gb::CALL_NC_n16() { if(!CY()) { word n16 = mmu->rw(PC); PC += 2; SP-=2; mmu->ww(SP, PC); PC = n16; } else PC += 2; } //0xD4
void Z80gb::CALL_C_n16() { if(CY()) { word n16 = mmu->rw(PC); PC += 2; SP-=2; mmu->ww(SP, PC); PC = n16; } else PC += 2; } //0xDC

//////////////////////
///    Restarts    ///
//////////////////////
/// RST
void Z80gb::RST_00H() { saveRegs(); SP-=2; mmu->ww(SP, PC); PC = 0x00; } //0xC7
void Z80gb::RST_08H() { saveRegs(); SP-=2; mmu->ww(SP, PC); PC = 0x08; } //0xCF
void Z80gb::RST_10H() { saveRegs(); SP-=2; mmu->ww(SP, PC); PC = 0x10; } //0xD7
void Z80gb::RST_18H() { saveRegs(); SP-=2; mmu->ww(SP, PC); PC = 0x18; } //0xDF
void Z80gb::RST_20H() { saveRegs(); SP-=2; mmu->ww(SP, PC); PC = 0x20; } //0xE7
void Z80gb::RST_28H() { saveRegs(); SP-=2; mmu->ww(SP, PC); PC = 0x28; } //0xEF
void Z80gb::RST_30H() { saveRegs(); SP-=2; mmu->ww(SP, PC); PC = 0x30; } //0xF7
void Z80gb::RST_38H() { saveRegs(); SP-=2; mmu->ww(SP, PC); PC = 0x38; } //0xFF

void Z80gb::ISR_40H() { IME = false; saveRegs(); SP-=2; mmu->ww(SP, PC); PC = 0x40; }
void Z80gb::ISR_48H() { IME = false; saveRegs(); SP-=2; mmu->ww(SP, PC); PC = 0x48; }
void Z80gb::ISR_50H() { IME = false; saveRegs(); SP-=2; mmu->ww(SP, PC); PC = 0x50; }
void Z80gb::ISR_58H() { IME = false; saveRegs(); SP-=2; mmu->ww(SP, PC); PC = 0x58; }
void Z80gb::ISR_60H() { IME = false; saveRegs(); SP-=2; mmu->ww(SP, PC); PC = 0x60; }

//////////////////////
///    Returns     ///
//////////////////////
/// RET
void Z80gb::RET() { PC = mmu->rw(SP); SP+=2; } //0xC9

void Z80gb::RET_NZ() { if(!ZF()) { PC = mmu->rw(SP); SP+=2; } } //0xC0
void Z80gb::RET_Z() { if(ZF()) { PC = mmu->rw(SP); SP+=2; } } //0xC8
void Z80gb::RET_NC() { if(!CY()) { PC = mmu->rw(SP); SP+=2; } } //0xD0
void Z80gb::RET_C() { if(CY()) { PC = mmu->rw(SP); SP+=2; } } //0xD8

/// RETI
void Z80gb::RETI() { loadRegs(); PC = mmu->rw(SP); SP+=2; IME = true; } //0xD9

//////////////////////
///     Extra      ///
//////////////////////
void Z80gb::DAA() { int acarr = 0; if((rA&0x0F)>9) { acarr = chkCY(rA, (byte)0x06); rA += 0x06; }
			if(rA>99) { acarr += chkCY(rA, (byte)0x60); rA += 0x60; }
			setFlags(rA==0,-1,0,acarr); } //0x27
void Z80gb::CPL() { rA ^= 0xFF; setFlags(-1,1,1,-1); } //0x2F
void Z80gb::CCF() { setFlags(-1,0,0,!CY()); } //0x3F
void Z80gb::SCF() { setFlags(-1,0,0,1); } //0x37
void Z80gb::NOP() { return;	} //0x00
void Z80gb::HALT() { if(IME) halt = true; else PC++; } //0x76 //Comportamiento especial de la instrucción
void Z80gb::STOP() { signoB s8 = mmu->rb(PC++); if(--rB) PC += s8; }//{ stop = true; PC++; } //0x10 0xXX //DJNZ s8
void Z80gb::DI() { IME = false; } //0xF3
void Z80gb::EI() { IME = true; } //0xFB
 
///////////////////////////
/// Rotaciones y shifts ///
///////////////////////////
void Z80gb::RLCA() { short bit = (rA>>7); rA = ((rA << 1) | bit); setFlags(0,0,0,bit); } //0x07
void Z80gb::RLA() { short bit = (rA>>7); rA = ((rA << 1) | (byte)CY()); setFlags(0,0,0,bit); } //0x17
void Z80gb::RRCA() { short bit = (rA&0x01); rA = ((rA >> 1) | (bit << 7)); setFlags(0,0,0,bit); } //0x0F
void Z80gb::RRA() { short bit = (rA&0x01); rA = ((rA >> 1) | (((byte)CY())<<7)); setFlags(0,0,0,bit); } //0x1F

void Z80gb::RLC_A() { short bit = (rA>>7); rA = ((rA << 1) | bit); setFlags(rA==0,0,0,bit); } //0xCB 0x07
void Z80gb::RLC_B() { short bit = (rB>>7); rB = ((rB << 1) | bit); setFlags(rB==0,0,0,bit); } //0xCB 0x00
void Z80gb::RLC_C() { short bit = (rC>>7); rC = ((rC << 1) | bit); setFlags(rC==0,0,0,bit); } //0xCB 0x01
void Z80gb::RLC_D() { short bit = (rD>>7); rD = ((rD << 1) | bit); setFlags(rD==0,0,0,bit); } //0xCB 0x02
void Z80gb::RLC_E() { short bit = (rE>>7); rE = ((rE << 1) | bit); setFlags(rE==0,0,0,bit); } //0xCB 0x03
void Z80gb::RLC_H() { short bit = (rH>>7); rH = ((rH << 1) | bit); setFlags(rH==0,0,0,bit); } //0xCB 0x04
void Z80gb::RLC_L() { short bit = (rL>>7); rL = ((rL << 1) | bit); setFlags(rL==0,0,0,bit); } //0xCB 0x05
void Z80gb::RLC_mHL() { short bit; byte n8 = mmu->rb(rHL()); bit = (n8>>7); n8 = ((n8 << 1) | bit); mmu->wb(rHL(), n8);
			setFlags(n8==0,0,0,bit); } //0xCB 0x06

void Z80gb::RL_A() { short bit = (rA>>7); rA = ((rA << 1) | (byte)CY()); setFlags(rA==0,0,0,bit); } //0xCB 0x17
void Z80gb::RL_B() { short bit = (rB>>7); rB = ((rB << 1) | (byte)CY()); setFlags(rB==0,0,0,bit); } //0xCB 0x10
void Z80gb::RL_C() { short bit = (rC>>7); rC = ((rC << 1) | (byte)CY()); setFlags(rC==0,0,0,bit); } //0xCB 0x11
void Z80gb::RL_D() { short bit = (rD>>7); rD = ((rD << 1) | (byte)CY()); setFlags(rD==0,0,0,bit); } //0xCB 0x12
void Z80gb::RL_E() { short bit = (rE>>7); rE = ((rE << 1) | (byte)CY()); setFlags(rE==0,0,0,bit); } //0xCB 0x13
void Z80gb::RL_H() { short bit = (rH>>7); rH = ((rH << 1) | (byte)CY()); setFlags(rH==0,0,0,bit); } //0xCB 0x14
void Z80gb::RL_L() { short bit = (rL>>7); rL = ((rL << 1) | (byte)CY()); setFlags(rL==0,0,0,bit); } //0xCB 0x15
void Z80gb::RL_mHL() { short bit; byte n8 = mmu->rb(rHL()); bit = (n8>>7); n8 = ((n8 << 1) | (byte)CY()); mmu->wb(rHL(), n8);
			setFlags(n8==0,0,0,bit); } //0xCB 0x06

void Z80gb::RRC_A() { short bit = (rA&0x01); rA = ((rA >> 1) | (bit << 7)); setFlags(rA==0,0,0,bit); } //0xCB 0x0F
void Z80gb::RRC_B() { short bit = (rB&0x01); rB = ((rB >> 1) | (bit << 7)); setFlags(rB==0,0,0,bit); } //0xCB 0x08
void Z80gb::RRC_C() { short bit = (rC&0x01); rC = ((rC >> 1) | (bit << 7)); setFlags(rC==0,0,0,bit); } //0xCB 0x09
void Z80gb::RRC_D() { short bit = (rD&0x01); rD = ((rD >> 1) | (bit << 7)); setFlags(rD==0,0,0,bit); } //0xCB 0x0A
void Z80gb::RRC_E() { short bit = (rE&0x01); rE = ((rE >> 1) | (bit << 7)); setFlags(rE==0,0,0,bit); } //0xCB 0x0B
void Z80gb::RRC_H() { short bit = (rH&0x01); rH = ((rH >> 1) | (bit << 7)); setFlags(rH==0,0,0,bit); } //0xCB 0x0C
void Z80gb::RRC_L() { short bit = (rL&0x01); rL = ((rL >> 1) | (bit << 7)); setFlags(rL==0,0,0,bit); } //0xCB 0x0D
void Z80gb::RRC_mHL() { short bit; byte n8 = mmu->rb(rHL()); bit = (n8&0x01); n8 = ((n8 >> 1) | (bit << 7));
			setFlags(n8==0,0,0,bit); } //0xCB 0x0E
			
void Z80gb::RR_A() { short bit = (rA&0x01); rA = ((rA >> 1) | (((byte)CY()) << 7)); setFlags(rA==0,0,0,bit); } //0xCB 0x1F
void Z80gb::RR_B() { short bit = (rB&0x01); rB = ((rB >> 1) | (((byte)CY()) << 7)); setFlags(rB==0,0,0,bit); } //0xCB 0x18
void Z80gb::RR_C() { short bit = (rC&0x01); rC = ((rC >> 1) | (((byte)CY()) << 7)); setFlags(rC==0,0,0,bit); } //0xCB 0x19
void Z80gb::RR_D() { short bit = (rD&0x01); rD = ((rD >> 1) | (((byte)CY()) << 7)); setFlags(rD==0,0,0,bit); } //0xCB 0x1A
void Z80gb::RR_E() { short bit = (rE&0x01); rE = ((rE >> 1) | (((byte)CY()) << 7)); setFlags(rE==0,0,0,bit); } //0xCB 0x1B
void Z80gb::RR_H() { short bit = (rH&0x01); rH = ((rH >> 1) | (((byte)CY()) << 7)); setFlags(rH==0,0,0,bit); } //0xCB 0x1C
void Z80gb::RR_L() { short bit = (rL&0x01); rL = ((rL >> 1) | (((byte)CY()) << 7)); setFlags(rL==0,0,0,bit); } //0xCB 0x1D
void Z80gb::RR_mHL() { short bit; byte n8 = mmu->rb(rHL()); bit = (n8&0x01); n8 = ((n8 >> 1) | (((byte)CY()) << 7));
			setFlags(n8==0,0,0,bit); } //0xCB 0x0E
			
void Z80gb::SLA_A() { short bit = (rA>>7); rA = (rA << 1); setFlags(rA==0,0,0,bit); } //0xCB 0x27
void Z80gb::SLA_B() { short bit = (rB>>7); rB = (rB << 1); setFlags(rB==0,0,0,bit); } //0xCB 0x20
void Z80gb::SLA_C() { short bit = (rC>>7); rC = (rC << 1); setFlags(rC==0,0,0,bit); } //0xCB 0x21
void Z80gb::SLA_D() { short bit = (rD>>7); rD = (rD << 1); setFlags(rD==0,0,0,bit); } //0xCB 0x22
void Z80gb::SLA_E() { short bit = (rE>>7); rE = (rE << 1); setFlags(rE==0,0,0,bit); } //0xCB 0x23
void Z80gb::SLA_H() { short bit = (rH>>7); rH = (rH << 1); setFlags(rH==0,0,0,bit); } //0xCB 0x24
void Z80gb::SLA_L() { short bit = (rL>>7); rL = (rL << 1); setFlags(rL==0,0,0,bit); } //0xCB 0x25
void Z80gb::SLA_mHL() { short bit; byte n8 = mmu->rb(rHL()); bit = (n8>>7); n8 = (n8 << 1); mmu->wb(rHL(), n8);
			setFlags(n8==0,0,0,bit); } //0xCB 0x26
			
void Z80gb::SRA_A() { short bit = (rA&0x01); short msb = (rA&0x80); rA = ((rA >> 1) | msb); setFlags(rA==0,0,0,bit); } //0xCB 0x2F
void Z80gb::SRA_B() { short bit = (rB&0x01); short msb = (rB&0x80); rB = ((rB >> 1) | msb); setFlags(rB==0,0,0,bit); } //0xCB 0x28
void Z80gb::SRA_C() { short bit = (rC&0x01); short msb = (rC&0x80); rC = ((rC >> 1) | msb); setFlags(rC==0,0,0,bit); } //0xCB 0x29
void Z80gb::SRA_D() { short bit = (rD&0x01); short msb = (rD&0x80); rD = ((rD >> 1) | msb); setFlags(rD==0,0,0,bit); } //0xCB 0x2A
void Z80gb::SRA_E() { short bit = (rE&0x01); short msb = (rE&0x80); rE = ((rE >> 1) | msb); setFlags(rE==0,0,0,bit); } //0xCB 0x2B
void Z80gb::SRA_H() { short bit = (rH&0x01); short msb = (rH&0x80); rH = ((rH >> 1) | msb); setFlags(rH==0,0,0,bit); } //0xCB 0x2C
void Z80gb::SRA_L() { short bit = (rL&0x01); short msb = (rL&0x80); rL = ((rL >> 1) | msb); setFlags(rL==0,0,0,bit); } //0xCB 0x2D
void Z80gb::SRA_mHL() { short bit; byte n8 = mmu->rb(rHL()); short msb = (n8&0x80); bit = (n8&0x01); n8 = ((n8 >> 1) | msb);
			setFlags(n8==0,0,0,bit); } //0xCB 0x2E
			
void Z80gb::SRL_A() { short bit = (rA&0x01); rA = (rA >> 1); setFlags(rA==0,0,0,bit); } //0xCB 0x3F
void Z80gb::SRL_B() { short bit = (rB&0x01); rB = (rB >> 1); setFlags(rB==0,0,0,bit); } //0xCB 0x38
void Z80gb::SRL_C() { short bit = (rC&0x01); rC = (rC >> 1); setFlags(rC==0,0,0,bit); } //0xCB 0x39
void Z80gb::SRL_D() { short bit = (rD&0x01); rD = (rD >> 1); setFlags(rD==0,0,0,bit); } //0xCB 0x3A
void Z80gb::SRL_E() { short bit = (rE&0x01); rE = (rE >> 1); setFlags(rE==0,0,0,bit); } //0xCB 0x3B
void Z80gb::SRL_H() { short bit = (rH&0x01); rH = (rH >> 1); setFlags(rH==0,0,0,bit); } //0xCB 0x3C
void Z80gb::SRL_L() { short bit = (rL&0x01); rL = (rL >> 1); setFlags(rL==0,0,0,bit); } //0xCB 0x3D
void Z80gb::SRL_mHL() { short bit; byte n8 = mmu->rb(rHL()); bit = (n8&0x01); n8 = (n8 >> 1);
			setFlags(n8==0,0,0,bit); } //0xCB 0x3E
			

//////////////////////
///    0xCB ops    ///
//////////////////////

void Z80gb::CBops() {
	byte opcode;
	
	//Captación
	opcode = mmu->rb(PC++);
	
	//Ejecución
	(this->*CBinstructions[opcode].f)();
	
	//No se tienen en cuenta los ciclos!!!!!
}

/// SWAP
void Z80gb::SWAP_A() { rA = ((rA << 4) | (rA >> 4)); setFlags(rA==0,0,0,0); } //0xCB 0x37
void Z80gb::SWAP_B() { rB = ((rB << 4) | (rB >> 4)); setFlags(rB==0,0,0,0); } //0xCB 0x30
void Z80gb::SWAP_C() { rC = ((rC << 4) | (rC >> 4)); setFlags(rC==0,0,0,0); } //0xCB 0x31
void Z80gb::SWAP_D() { rD = ((rD << 4) | (rD >> 4)); setFlags(rD==0,0,0,0); } //0xCB 0x32
void Z80gb::SWAP_E() { rE = ((rE << 4) | (rE >> 4)); setFlags(rE==0,0,0,0); } //0xCB 0x33
void Z80gb::SWAP_H() { rH = ((rH << 4) | (rH >> 4)); setFlags(rH==0,0,0,0); } //0xCB 0x34
void Z80gb::SWAP_L() { rL = ((rL << 4) | (rL >> 4)); setFlags(rL==0,0,0,0); } //0xCB 0x35
void Z80gb::SWAP_mHL() { byte n8 = mmu->rb(rHL()); n8 = ((n8 << 4) | (n8 >> 4)); mmu->wb(rHL(), n8);
			setFlags(n8==0,0,0,0); } //0xCB 0x36

/// BIT
void Z80gb::BIT_0_A() { short bit = (rA&0x01); setFlags(bit==0,0,1,-1); } //0xCB 0x47
void Z80gb::BIT_0_B() { short bit = (rB&0x01); setFlags(bit==0,0,1,-1); } //0xCB 0x40
void Z80gb::BIT_0_C() { short bit = (rC&0x01); setFlags(bit==0,0,1,-1); } //0xCB 0x41
void Z80gb::BIT_0_D() { short bit = (rD&0x01); setFlags(bit==0,0,1,-1); } //0xCB 0x42
void Z80gb::BIT_0_E() { short bit = (rE&0x01); setFlags(bit==0,0,1,-1); } //0xCB 0x43
void Z80gb::BIT_0_H() { short bit = (rH&0x01); setFlags(bit==0,0,1,-1); } //0xCB 0x44
void Z80gb::BIT_0_L() { short bit = (rL&0x01); setFlags(bit==0,0,1,-1); } //0xCB 0x45
void Z80gb::BIT_0_mHL() { byte n8 = mmu->rb(rHL()); short bit = (n8&0x01);
			setFlags(bit==0,0,1,-1); } //0xCB 0x46
			
void Z80gb::BIT_1_A() { short bit = (rA&0x02); setFlags(bit==0,0,1,-1); } //0xCB 0x4F
void Z80gb::BIT_1_B() { short bit = (rB&0x02); setFlags(bit==0,0,1,-1); } //0xCB 0x48
void Z80gb::BIT_1_C() { short bit = (rC&0x02); setFlags(bit==0,0,1,-1); } //0xCB 0x49
void Z80gb::BIT_1_D() { short bit = (rD&0x02); setFlags(bit==0,0,1,-1); } //0xCB 0x4A
void Z80gb::BIT_1_E() { short bit = (rE&0x02); setFlags(bit==0,0,1,-1); } //0xCB 0x4B
void Z80gb::BIT_1_H() { short bit = (rH&0x02); setFlags(bit==0,0,1,-1); } //0xCB 0x4C
void Z80gb::BIT_1_L() { short bit = (rL&0x02); setFlags(bit==0,0,1,-1); } //0xCB 0x4D
void Z80gb::BIT_1_mHL() { byte n8 = mmu->rb(rHL()); short bit = (n8&0x02);
			setFlags(bit==0,0,1,-1); } //0xCB 0x4E
			
void Z80gb::BIT_2_A() { short bit = (rA&0x04); setFlags(bit==0,0,1,-1); } //0xCB 0x57
void Z80gb::BIT_2_B() { short bit = (rB&0x04); setFlags(bit==0,0,1,-1); } //0xCB 0x50
void Z80gb::BIT_2_C() { short bit = (rC&0x04); setFlags(bit==0,0,1,-1); } //0xCB 0x51
void Z80gb::BIT_2_D() { short bit = (rD&0x04); setFlags(bit==0,0,1,-1); } //0xCB 0x52
void Z80gb::BIT_2_E() { short bit = (rE&0x04); setFlags(bit==0,0,1,-1); } //0xCB 0x53
void Z80gb::BIT_2_H() { short bit = (rH&0x04); setFlags(bit==0,0,1,-1); } //0xCB 0x54
void Z80gb::BIT_2_L() { short bit = (rL&0x04); setFlags(bit==0,0,1,-1); } //0xCB 0x55
void Z80gb::BIT_2_mHL() { byte n8 = mmu->rb(rHL()); short bit = (n8&0x04);
			setFlags(bit==0,0,1,-1); } //0xCB 0x56
			
void Z80gb::BIT_3_A() { short bit = (rA&0x08); setFlags(bit==0,0,1,-1); } //0xCB 0x5F
void Z80gb::BIT_3_B() { short bit = (rB&0x08); setFlags(bit==0,0,1,-1); } //0xCB 0x58
void Z80gb::BIT_3_C() { short bit = (rC&0x08); setFlags(bit==0,0,1,-1); } //0xCB 0x59
void Z80gb::BIT_3_D() { short bit = (rD&0x08); setFlags(bit==0,0,1,-1); } //0xCB 0x5A
void Z80gb::BIT_3_E() { short bit = (rE&0x08); setFlags(bit==0,0,1,-1); } //0xCB 0x5B
void Z80gb::BIT_3_H() { short bit = (rH&0x08); setFlags(bit==0,0,1,-1); } //0xCB 0x5C
void Z80gb::BIT_3_L() { short bit = (rL&0x08); setFlags(bit==0,0,1,-1); } //0xCB 0x5D
void Z80gb::BIT_3_mHL() { byte n8 = mmu->rb(rHL()); short bit = (n8&0x08);
			setFlags(bit==0,0,1,-1); } //0xCB 0x5E
			
void Z80gb::BIT_4_A() { short bit = (rA&0x10); setFlags(bit==0,0,1,-1); } //0xCB 0x67
void Z80gb::BIT_4_B() { short bit = (rB&0x10); setFlags(bit==0,0,1,-1); } //0xCB 0x60
void Z80gb::BIT_4_C() { short bit = (rC&0x10); setFlags(bit==0,0,1,-1); } //0xCB 0x61
void Z80gb::BIT_4_D() { short bit = (rD&0x10); setFlags(bit==0,0,1,-1); } //0xCB 0x62
void Z80gb::BIT_4_E() { short bit = (rE&0x10); setFlags(bit==0,0,1,-1); } //0xCB 0x63
void Z80gb::BIT_4_H() { short bit = (rH&0x10); setFlags(bit==0,0,1,-1); } //0xCB 0x64
void Z80gb::BIT_4_L() { short bit = (rL&0x10); setFlags(bit==0,0,1,-1); } //0xCB 0x65
void Z80gb::BIT_4_mHL() { byte n8 = mmu->rb(rHL()); short bit = (n8&0x10);
			setFlags(bit==0,0,1,-1); } //0xCB 0x66
			
void Z80gb::BIT_5_A() { short bit = (rA&0x20); setFlags(bit==0,0,1,-1); } //0xCB 0x6F
void Z80gb::BIT_5_B() { short bit = (rB&0x20); setFlags(bit==0,0,1,-1); } //0xCB 0x68
void Z80gb::BIT_5_C() { short bit = (rC&0x20); setFlags(bit==0,0,1,-1); } //0xCB 0x69
void Z80gb::BIT_5_D() { short bit = (rD&0x20); setFlags(bit==0,0,1,-1); } //0xCB 0x6A
void Z80gb::BIT_5_E() { short bit = (rE&0x20); setFlags(bit==0,0,1,-1); } //0xCB 0x6B
void Z80gb::BIT_5_H() { short bit = (rH&0x20); setFlags(bit==0,0,1,-1); } //0xCB 0x6C
void Z80gb::BIT_5_L() { short bit = (rL&0x20); setFlags(bit==0,0,1,-1); } //0xCB 0x6D
void Z80gb::BIT_5_mHL() { byte n8 = mmu->rb(rHL()); short bit = (n8&0x20);
			setFlags(bit==0,0,1,-1); } //0xCB 0x6E
			
void Z80gb::BIT_6_A() { short bit = (rA&0x40); setFlags(bit==0,0,1,-1); } //0xCB 0x77
void Z80gb::BIT_6_B() { short bit = (rB&0x40); setFlags(bit==0,0,1,-1); } //0xCB 0x70
void Z80gb::BIT_6_C() { short bit = (rC&0x40); setFlags(bit==0,0,1,-1); } //0xCB 0x71
void Z80gb::BIT_6_D() { short bit = (rD&0x40); setFlags(bit==0,0,1,-1); } //0xCB 0x72
void Z80gb::BIT_6_E() { short bit = (rE&0x40); setFlags(bit==0,0,1,-1); } //0xCB 0x73
void Z80gb::BIT_6_H() { short bit = (rH&0x40); setFlags(bit==0,0,1,-1); } //0xCB 0x74
void Z80gb::BIT_6_L() { short bit = (rL&0x40); setFlags(bit==0,0,1,-1); } //0xCB 0x75
void Z80gb::BIT_6_mHL() { byte n8 = mmu->rb(rHL()); short bit = (n8&0x40);
			setFlags(bit==0,0,1,-1); } //0xCB 0x76
			
void Z80gb::BIT_7_A() { short bit = (rA&0x80); setFlags(bit==0,0,1,-1); } //0xCB 0x7F
void Z80gb::BIT_7_B() { short bit = (rB&0x80); setFlags(bit==0,0,1,-1); } //0xCB 0x78
void Z80gb::BIT_7_C() { short bit = (rC&0x80); setFlags(bit==0,0,1,-1); } //0xCB 0x79
void Z80gb::BIT_7_D() { short bit = (rD&0x80); setFlags(bit==0,0,1,-1); } //0xCB 0x7A
void Z80gb::BIT_7_E() { short bit = (rE&0x80); setFlags(bit==0,0,1,-1); } //0xCB 0x7B
void Z80gb::BIT_7_H() { short bit = (rH&0x80); setFlags(bit==0,0,1,-1); } //0xCB 0x7C
void Z80gb::BIT_7_L() { short bit = (rL&0x80); setFlags(bit==0,0,1,-1); } //0xCB 0x7D
void Z80gb::BIT_7_mHL() { byte n8 = mmu->rb(rHL()); short bit = (n8&0x80);
			setFlags(bit==0,0,1,-1); } //0xCB 0x7E

/// RES
void Z80gb::RES_0_A() { rA &= 0xFE; } //0xCB 0x87
void Z80gb::RES_0_B() { rB &= 0xFE; } //0xCB 0x80
void Z80gb::RES_0_C() { rC &= 0xFE; } //0xCB 0x81
void Z80gb::RES_0_D() { rD &= 0xFE; } //0xCB 0x82
void Z80gb::RES_0_E() { rE &= 0xFE; } //0xCB 0x83
void Z80gb::RES_0_H() { rH &= 0xFE; } //0xCB 0x84
void Z80gb::RES_0_L() { rL &= 0xFE; } //0xCB 0x85
void Z80gb::RES_0_mHL() { rHL( mmu->rb(rHL())&0xFE ); } //0xCB 0x86

void Z80gb::RES_1_A() { rA &= 0xFD; } //0xCB 0x8F
void Z80gb::RES_1_B() { rB &= 0xFD; } //0xCB 0x88
void Z80gb::RES_1_C() { rC &= 0xFD; } //0xCB 0x89
void Z80gb::RES_1_D() { rD &= 0xFD; } //0xCB 0x8A
void Z80gb::RES_1_E() { rE &= 0xFD; } //0xCB 0x8B
void Z80gb::RES_1_H() { rH &= 0xFD; } //0xCB 0x8C
void Z80gb::RES_1_L() { rL &= 0xFD; } //0xCB 0x8D
void Z80gb::RES_1_mHL() { rHL( mmu->rb(rHL())&0xFD ); } //0xCB 0x8E

void Z80gb::RES_2_A() { rA &= 0xFB; } //0xCB 0x97
void Z80gb::RES_2_B() { rB &= 0xFB; } //0xCB 0x90
void Z80gb::RES_2_C() { rC &= 0xFB; } //0xCB 0x91
void Z80gb::RES_2_D() { rD &= 0xFB; } //0xCB 0x92
void Z80gb::RES_2_E() { rE &= 0xFB; } //0xCB 0x93
void Z80gb::RES_2_H() { rH &= 0xFB; } //0xCB 0x94
void Z80gb::RES_2_L() { rL &= 0xFB; } //0xCB 0x95
void Z80gb::RES_2_mHL() { rHL( mmu->rb(rHL())&0xFB ); } //0xCB 0x96

void Z80gb::RES_3_A() { rA &= 0xF7; } //0xCB 0x9F
void Z80gb::RES_3_B() { rB &= 0xF7; } //0xCB 0x98
void Z80gb::RES_3_C() { rC &= 0xF7; } //0xCB 0x99
void Z80gb::RES_3_D() { rD &= 0xF7; } //0xCB 0x9A
void Z80gb::RES_3_E() { rE &= 0xF7; } //0xCB 0x9B
void Z80gb::RES_3_H() { rH &= 0xF7; } //0xCB 0x9C
void Z80gb::RES_3_L() { rL &= 0xF7; } //0xCB 0x9D
void Z80gb::RES_3_mHL() { rHL( mmu->rb(rHL())&0xF7 ); } //0xCB 0x9E

void Z80gb::RES_4_A() { rA &= 0xEF; } //0xCB 0xA7
void Z80gb::RES_4_B() { rB &= 0xEF; } //0xCB 0xA0
void Z80gb::RES_4_C() { rC &= 0xEF; } //0xCB 0xA1
void Z80gb::RES_4_D() { rD &= 0xEF; } //0xCB 0xA2
void Z80gb::RES_4_E() { rE &= 0xEF; } //0xCB 0xA3
void Z80gb::RES_4_H() { rH &= 0xEF; } //0xCB 0xA4
void Z80gb::RES_4_L() { rL &= 0xEF; } //0xCB 0xA5
void Z80gb::RES_4_mHL() { rHL( mmu->rb(rHL())&0xEF ); } //0xCB 0xA6

void Z80gb::RES_5_A() { rA &= 0xDF; } //0xCB 0xAF
void Z80gb::RES_5_B() { rB &= 0xDF; } //0xCB 0xA8
void Z80gb::RES_5_C() { rC &= 0xDF; } //0xCB 0xA9
void Z80gb::RES_5_D() { rD &= 0xDF; } //0xCB 0xAA
void Z80gb::RES_5_E() { rE &= 0xDF; } //0xCB 0xAB
void Z80gb::RES_5_H() { rH &= 0xDF; } //0xCB 0xAC
void Z80gb::RES_5_L() { rL &= 0xDF; } //0xCB 0xAD
void Z80gb::RES_5_mHL() { rHL( mmu->rb(rHL())&0xDF ); } //0xCB 0xAE

void Z80gb::RES_6_A() { rA &= 0xBF; } //0xCB 0xB7
void Z80gb::RES_6_B() { rB &= 0xBF; } //0xCB 0xB0
void Z80gb::RES_6_C() { rC &= 0xBF; } //0xCB 0xB1
void Z80gb::RES_6_D() { rD &= 0xBF; } //0xCB 0xB2
void Z80gb::RES_6_E() { rE &= 0xBF; } //0xCB 0xB3
void Z80gb::RES_6_H() { rH &= 0xBF; } //0xCB 0xB4
void Z80gb::RES_6_L() { rL &= 0xBF; } //0xCB 0xB5
void Z80gb::RES_6_mHL() { rHL( mmu->rb(rHL())&0xBF ); } //0xCB 0xB6

void Z80gb::RES_7_A() { rA &= 0x7F; } //0xCB 0xBF
void Z80gb::RES_7_B() { rB &= 0x7F; } //0xCB 0xB8
void Z80gb::RES_7_C() { rC &= 0x7F; } //0xCB 0xB9
void Z80gb::RES_7_D() { rD &= 0x7F; } //0xCB 0xBA
void Z80gb::RES_7_E() { rE &= 0x7F; } //0xCB 0xBB
void Z80gb::RES_7_H() { rH &= 0x7F; } //0xCB 0xBC
void Z80gb::RES_7_L() { rL &= 0x7F; } //0xCB 0xBD
void Z80gb::RES_7_mHL() { rHL( mmu->rb(rHL())&0x7F ); } //0xCB 0xBE



/// SET
void Z80gb::SET_0_A() { rA |= 0x01; } //0xCB 0xC7
void Z80gb::SET_0_B() { rB |= 0x01; } //0xCB 0xC0
void Z80gb::SET_0_C() { rC |= 0x01; } //0xCB 0xC1
void Z80gb::SET_0_D() { rD |= 0x01; } //0xCB 0xC2
void Z80gb::SET_0_E() { rE |= 0x01; } //0xCB 0xC3
void Z80gb::SET_0_H() { rH |= 0x01; } //0xCB 0xC4
void Z80gb::SET_0_L() { rL |= 0x01; } //0xCB 0xC5
void Z80gb::SET_0_mHL() { rHL( mmu->rb(rHL())|0x01 ); } //0xCB 0xC6

void Z80gb::SET_1_A() { rA |= 0x02; } //0xCB 0xCF
void Z80gb::SET_1_B() { rB |= 0x02; } //0xCB 0xC8
void Z80gb::SET_1_C() { rC |= 0x02; } //0xCB 0xC9
void Z80gb::SET_1_D() { rD |= 0x02; } //0xCB 0xCA
void Z80gb::SET_1_E() { rE |= 0x02; } //0xCB 0xCB
void Z80gb::SET_1_H() { rH |= 0x02; } //0xCB 0xCC
void Z80gb::SET_1_L() { rL |= 0x02; } //0xCB 0xCD
void Z80gb::SET_1_mHL() { rHL( mmu->rb(rHL())|0x02 ); } //0xCB 0xCE

void Z80gb::SET_2_A() { rA |= 0x04; } //0xCB 0xD7
void Z80gb::SET_2_B() { rB |= 0x04; } //0xCB 0xD0
void Z80gb::SET_2_C() { rC |= 0x04; } //0xCB 0xD1
void Z80gb::SET_2_D() { rD |= 0x04; } //0xCB 0xD2
void Z80gb::SET_2_E() { rE |= 0x04; } //0xCB 0xD3
void Z80gb::SET_2_H() { rH |= 0x04; } //0xCB 0xD4
void Z80gb::SET_2_L() { rL |= 0x04; } //0xCB 0xD5
void Z80gb::SET_2_mHL() { rHL( mmu->rb(rHL())|0x04 ); } //0xCB 0xD6

void Z80gb::SET_3_A() { rA |= 0x08; } //0xCB 0xDF
void Z80gb::SET_3_B() { rB |= 0x08; } //0xCB 0xD8
void Z80gb::SET_3_C() { rC |= 0x08; } //0xCB 0xD9
void Z80gb::SET_3_D() { rD |= 0x08; } //0xCB 0xDA
void Z80gb::SET_3_E() { rE |= 0x08; } //0xCB 0xDB
void Z80gb::SET_3_H() { rH |= 0x08; } //0xCB 0xDC
void Z80gb::SET_3_L() { rL |= 0x08; } //0xCB 0xDD
void Z80gb::SET_3_mHL() { rHL( mmu->rb(rHL())|0x08 ); } //0xCB 0xDE

void Z80gb::SET_4_A() { rA |= 0x10; } //0xCB 0xE7
void Z80gb::SET_4_B() { rB |= 0x10; } //0xCB 0xE0
void Z80gb::SET_4_C() { rC |= 0x10; } //0xCB 0xE1
void Z80gb::SET_4_D() { rD |= 0x10; } //0xCB 0xE2
void Z80gb::SET_4_E() { rE |= 0x10; } //0xCB 0xE3
void Z80gb::SET_4_H() { rH |= 0x10; } //0xCB 0xE4
void Z80gb::SET_4_L() { rL |= 0x10; } //0xCB 0xE5
void Z80gb::SET_4_mHL() { rHL( mmu->rb(rHL())|0x10 ); } //0xCB 0xE6

void Z80gb::SET_5_A() { rA |= 0x20; } //0xCB 0xEF
void Z80gb::SET_5_B() { rB |= 0x20; } //0xCB 0xE8
void Z80gb::SET_5_C() { rC |= 0x20; } //0xCB 0xE9
void Z80gb::SET_5_D() { rD |= 0x20; } //0xCB 0xEA
void Z80gb::SET_5_E() { rE |= 0x20; } //0xCB 0xEB
void Z80gb::SET_5_H() { rH |= 0x20; } //0xCB 0xEC
void Z80gb::SET_5_L() { rL |= 0x20; } //0xCB 0xED
void Z80gb::SET_5_mHL() { rHL( mmu->rb(rHL())|0x20 ); } //0xCB 0xEE

void Z80gb::SET_6_A() { rA |= 0x40; } //0xCB 0xF7
void Z80gb::SET_6_B() { rB |= 0x40; } //0xCB 0xF0
void Z80gb::SET_6_C() { rC |= 0x40; } //0xCB 0xF1
void Z80gb::SET_6_D() { rD |= 0x40; } //0xCB 0xF2
void Z80gb::SET_6_E() { rE |= 0x40; } //0xCB 0xF3
void Z80gb::SET_6_H() { rH |= 0x40; } //0xCB 0xF4
void Z80gb::SET_6_L() { rL |= 0x40; } //0xCB 0xF5
void Z80gb::SET_6_mHL() { rHL( mmu->rb(rHL())|0x40 ); } //0xCB 0xF6

void Z80gb::SET_7_A() { rA |= 0x80; } //0xCB 0xFF
void Z80gb::SET_7_B() { rB |= 0x80; } //0xCB 0xF8
void Z80gb::SET_7_C() { rC |= 0x80; } //0xCB 0xF9
void Z80gb::SET_7_D() { rD |= 0x80; } //0xCB 0xFA
void Z80gb::SET_7_E() { rE |= 0x80; } //0xCB 0xFB
void Z80gb::SET_7_H() { rH |= 0x80; } //0xCB 0xFC
void Z80gb::SET_7_L() { rL |= 0x80; } //0xCB 0xFD
void Z80gb::SET_7_mHL() { rHL( mmu->rb(rHL())|0x80 ); } //0xCB 0xFE

void Z80gb::noImplementado() {
	printf("Opcode %X no implementado\n", mmu->rb(PC-1));
}

Z80gb::Instruccion Z80gb::instructions[] = {
	// 0x0-
	{&Z80gb::NOP, 4}, //0x00
	{&Z80gb::LD_BC_n16, 12}, //0x01
	{&Z80gb::LD_mBC_A, 8}, //0x02
	{&Z80gb::INC_BC, 8}, //0x03
	{&Z80gb::INC_B, 4}, //0x04
	{&Z80gb::DEC_B, 4}, //0x05
	{&Z80gb::LD_B_n8, 8}, //0x06
	{&Z80gb::RLCA, 4}, //0x07
	{&Z80gb::LD_mn16_SP, 20}, //0x08
	{&Z80gb::ADD_HL_BC, 8}, //0x09
	{&Z80gb::LD_A_mBC, 8}, //0x0A
	{&Z80gb::DEC_BC, 8}, //0x0B
	{&Z80gb::INC_C, 4}, //0x0C
	{&Z80gb::DEC_C, 4}, //0x0D
	{&Z80gb::LD_C_n8, 8}, //0x0E
	{&Z80gb::RRCA, 4}, //0x0F
	
	// 0x1-
	{&Z80gb::STOP, 4}, //0x10
	{&Z80gb::LD_DE_n16, 12}, //0x11
	{&Z80gb::LD_mDE_A, 8}, //0x12
	{&Z80gb::INC_DE, 8}, //0x13
	{&Z80gb::INC_D, 4}, //0x14
	{&Z80gb::DEC_D, 4}, //0x15
	{&Z80gb::LD_D_n8, 8}, //0x16
	{&Z80gb::RLA, 4}, //0x17
	{&Z80gb::JR_s8o, 8}, //0x18
	{&Z80gb::ADD_HL_DE, 8}, //0x19
	{&Z80gb::LD_A_mDE, 8}, //0x1A
	{&Z80gb::DEC_DE, 8}, //0x1B
	{&Z80gb::INC_E, 4}, //0x1C
	{&Z80gb::DEC_E, 4}, //0x1D
	{&Z80gb::LD_E_n8, 8}, //0x1E
	{&Z80gb::RRA, 4}, //0x1F
	
	// 0x2-
	{&Z80gb::JR_NZ_s8o, 8}, //0x20
	{&Z80gb::LD_HL_n16, 12}, //0x21
	{&Z80gb::LDI_mHL_A, 8}, //0x22
	{&Z80gb::INC_HL, 8}, //0x23
	{&Z80gb::INC_H, 4}, //0x24
	{&Z80gb::DEC_H, 4}, //0x25
	{&Z80gb::LD_H_n8, 8}, //0x26
	{&Z80gb::DAA, 4}, //0x27
	{&Z80gb::JR_Z_s8o, 8}, //0x28
	{&Z80gb::ADD_HL_HL, 8}, //0x29
	{&Z80gb::LDI_A_mHL, 8}, //0x2A
	{&Z80gb::DEC_HL, 8}, //0x2B
	{&Z80gb::INC_L, 4}, //0x2C
	{&Z80gb::DEC_L, 4}, //0x2D
	{&Z80gb::LD_L_n8, 8}, //0x2E
	{&Z80gb::CPL, 4}, //0x2F
	
	// 0x3-
	{&Z80gb::JR_NC_s8o, 8}, //0x30
	{&Z80gb::LD_SP_n16, 12}, //0x31
	{&Z80gb::LDD_mHL_A, 8}, //0x32
	{&Z80gb::INC_SP, 8}, //0x33
	{&Z80gb::INC_mHL, 12}, //0x34
	{&Z80gb::DEC_mHL, 12}, //0x35
	{&Z80gb::LD_mHL_n8, 12}, //0x36
	{&Z80gb::SCF, 4}, //0x37
	{&Z80gb::JR_C_s8o, 8}, //0x38
	{&Z80gb::ADD_HL_SP, 8}, //0x39
	{&Z80gb::LDD_A_mHL, 8}, //0x3A
	{&Z80gb::DEC_SP, 8}, //0x3B
	{&Z80gb::INC_A, 4}, //0x3C
	{&Z80gb::DEC_A, 4}, //0x3D
	{&Z80gb::LD_A_n8, 8}, //0x3E
	{&Z80gb::CCF, 4}, //0x3F
	
	// 0x4-
	{&Z80gb::LD_B_B, 4}, //0x40
	{&Z80gb::LD_B_C, 4}, //0x41
	{&Z80gb::LD_B_D, 4}, //0x42
	{&Z80gb::LD_B_E, 4}, //0x43
	{&Z80gb::LD_B_H, 4}, //0x44
	{&Z80gb::LD_B_L, 4}, //0x45
	{&Z80gb::LD_B_mHL, 8}, //0x46
	{&Z80gb::LD_B_A, 4}, //0x47
	{&Z80gb::LD_C_B, 4}, //0x48
	{&Z80gb::LD_C_C, 4}, //0x49
	{&Z80gb::LD_C_D, 4}, //0x4A
	{&Z80gb::LD_C_E, 4}, //0x4B
	{&Z80gb::LD_C_H, 4}, //0x4C
	{&Z80gb::LD_C_L, 4}, //0x4D
	{&Z80gb::LD_C_mHL, 8}, //0x4E
	{&Z80gb::LD_C_A, 4}, //0x4F
	
	// 0x5-
	{&Z80gb::LD_D_B, 4}, //0x50
	{&Z80gb::LD_D_C, 4}, //0x51
	{&Z80gb::LD_D_D, 4}, //0x52
	{&Z80gb::LD_D_E, 4}, //0x53
	{&Z80gb::LD_D_H, 4}, //0x54
	{&Z80gb::LD_D_L, 4}, //0x55
	{&Z80gb::LD_D_mHL, 8}, //0x56
	{&Z80gb::LD_D_A, 4}, //0x57
	{&Z80gb::LD_E_B, 4}, //0x58
	{&Z80gb::LD_E_C, 4}, //0x59
	{&Z80gb::LD_E_D, 4}, //0x5A
	{&Z80gb::LD_E_E, 4}, //0x5B
	{&Z80gb::LD_E_H, 4}, //0x5C
	{&Z80gb::LD_E_L, 4}, //0x5D
	{&Z80gb::LD_E_mHL, 8}, //0x5E
	{&Z80gb::LD_E_A, 4}, //0x5F
	
	// 0x6-
	{&Z80gb::LD_H_B, 4}, //0x60
	{&Z80gb::LD_H_C, 4}, //0x61
	{&Z80gb::LD_H_D, 4}, //0x62
	{&Z80gb::LD_H_E, 4}, //0x63
	{&Z80gb::LD_H_H, 4}, //0x64
	{&Z80gb::LD_H_L, 4}, //0x65
	{&Z80gb::LD_H_mHL, 8}, //0x66
	{&Z80gb::LD_H_A, 4}, //0x67
	{&Z80gb::LD_L_B, 4}, //0x68
	{&Z80gb::LD_L_C, 4}, //0x69
	{&Z80gb::LD_L_D, 4}, //0x6A
	{&Z80gb::LD_L_E, 4}, //0x6B
	{&Z80gb::LD_L_H, 4}, //0x6C
	{&Z80gb::LD_L_L, 4}, //0x6D
	{&Z80gb::LD_L_mHL, 8}, //0x6E
	{&Z80gb::LD_L_A, 4}, //0x6F
	
	// 0x7-
	{&Z80gb::LD_mHL_B, 8}, //0x70
	{&Z80gb::LD_mHL_C, 8}, //0x71
	{&Z80gb::LD_mHL_D, 8}, //0x72
	{&Z80gb::LD_mHL_E, 8}, //0x73
	{&Z80gb::LD_mHL_H, 8}, //0x74
	{&Z80gb::LD_mHL_L, 8}, //0x75
	{&Z80gb::HALT, 4}, //0x76
	{&Z80gb::LD_mHL_A, 8}, //0x77
	{&Z80gb::LD_A_B, 4}, //0x78
	{&Z80gb::LD_A_C, 4}, //0x79
	{&Z80gb::LD_A_D, 4}, //0x7A
	{&Z80gb::LD_A_E, 4}, //0x7B
	{&Z80gb::LD_A_H, 4}, //0x7C
	{&Z80gb::LD_A_L, 4}, //0x7D
	{&Z80gb::LD_A_mHL, 8}, //0x7E
	{&Z80gb::LD_A_A, 4}, //0x7F
	
	// 0x8-
	{&Z80gb::ADD_A_B, 4}, //0x80
	{&Z80gb::ADD_A_C, 4}, //0x81
	{&Z80gb::ADD_A_D, 4}, //0x82
	{&Z80gb::ADD_A_E, 4}, //0x83
	{&Z80gb::ADD_A_H, 4}, //0x84
	{&Z80gb::ADD_A_L, 4}, //0x85
	{&Z80gb::ADD_A_mHL, 8}, //0x86
	{&Z80gb::ADD_A_A, 4}, //0x87
	{&Z80gb::ADC_A_B, 4}, //0x88
	{&Z80gb::ADC_A_C, 4}, //0x89
	{&Z80gb::ADC_A_D, 4}, //0x8A
	{&Z80gb::ADC_A_E, 4}, //0x8B
	{&Z80gb::ADC_A_H, 4}, //0x8C
	{&Z80gb::ADC_A_L, 4}, //0x8D
	{&Z80gb::ADC_A_mHL, 8}, //0x8E
	{&Z80gb::ADC_A_A, 4}, //0x8F
	
	// 0x9-
	{&Z80gb::SUB_A_B, 4}, //0x90
	{&Z80gb::SUB_A_C, 4}, //0x91
	{&Z80gb::SUB_A_D, 4}, //0x92
	{&Z80gb::SUB_A_E, 4}, //0x93
	{&Z80gb::SUB_A_H, 4}, //0x94
	{&Z80gb::SUB_A_L, 4}, //0x95
	{&Z80gb::SUB_A_mHL, 8}, //0x96
	{&Z80gb::SUB_A_A, 4}, //0x97
	{&Z80gb::SBC_A_B, 4}, //0x98
	{&Z80gb::SBC_A_C, 4}, //0x99
	{&Z80gb::SBC_A_D, 4}, //0x9A
	{&Z80gb::SBC_A_E, 4}, //0x9B
	{&Z80gb::SBC_A_H, 4}, //0x9C
	{&Z80gb::SBC_A_L, 4}, //0x9D
	{&Z80gb::SBC_A_mHL, 8}, //0x9E
	{&Z80gb::SBC_A_A, 4}, //0x9F
	
	// 0xA-
	{&Z80gb::AND_B, 4}, //0xA0
	{&Z80gb::AND_C, 4}, //0xA1
	{&Z80gb::AND_D, 4}, //0xA2
	{&Z80gb::AND_E, 4}, //0xA3
	{&Z80gb::AND_H, 4}, //0xA4
	{&Z80gb::AND_L, 4}, //0xA5
	{&Z80gb::AND_mHL, 8}, //0xA6
	{&Z80gb::AND_A, 4}, //0xA7
	{&Z80gb::XOR_B, 4}, //0xA8
	{&Z80gb::XOR_C, 4}, //0xA9
	{&Z80gb::XOR_D, 4}, //0xAA
	{&Z80gb::XOR_E, 4}, //0xAB
	{&Z80gb::XOR_H, 4}, //0xAC
	{&Z80gb::XOR_L, 4}, //0xAD
	{&Z80gb::XOR_mHL, 8}, //0xAE
	{&Z80gb::XOR_A, 4}, //0xAF
	
	// 0xB-
	{&Z80gb::OR_B, 4}, //0xB0
	{&Z80gb::OR_C, 4}, //0xB1
	{&Z80gb::OR_D, 4}, //0xB2
	{&Z80gb::OR_E, 4}, //0xB3
	{&Z80gb::OR_H, 4}, //0xB4
	{&Z80gb::OR_L, 4}, //0xB5
	{&Z80gb::OR_mHL, 8}, //0xB6
	{&Z80gb::OR_A, 4}, //0xB7
	{&Z80gb::CP_B, 4}, //0xB8
	{&Z80gb::CP_C, 4}, //0xB9
	{&Z80gb::CP_D, 4}, //0xBA
	{&Z80gb::CP_E, 4}, //0xBB
	{&Z80gb::CP_H, 4}, //0xBC
	{&Z80gb::CP_L, 4}, //0xBD
	{&Z80gb::CP_mHL, 8}, //0xBE
	{&Z80gb::CP_A, 4}, //0xBF
	
	// 0xC-
	{&Z80gb::RET_NZ, 8}, //0xC0
	{&Z80gb::POP_BC, 12}, //0xC1
	{&Z80gb::JP_NZ_n16, 12}, //0xC2
	{&Z80gb::JP_n16, 12}, //0xC3
	{&Z80gb::CALL_NZ_n16, 12}, //0xC4
	{&Z80gb::PUSH_BC, 16}, //0xC5
	{&Z80gb::ADD_A_n8, 8}, //0xC6
	{&Z80gb::RST_00H, 32}, //0xC7
	{&Z80gb::RET_Z, 8}, //0xC8
	{&Z80gb::RET, 8}, //0xC9
	{&Z80gb::JP_Z_n16, 12}, //0xCA
	{&Z80gb::CBops, 4}, //0xCB 0xXX		/// 4 ciclos? o 0?
	{&Z80gb::CALL_Z_n16, 12}, //0xCC
	{&Z80gb::CALL_n16, 12}, //0xCD
	{&Z80gb::ADC_A_n8, 8}, //0xCE
	{&Z80gb::RST_08H, 32}, //0xCF
	
	// 0xD-
	{&Z80gb::RET_NC, 8}, //0xD0
	{&Z80gb::POP_DE, 12}, //0xD1
	{&Z80gb::JP_NC_n16, 12}, //0xD2
	{&Z80gb::noImplementado, 0}, //0xD3
	{&Z80gb::CALL_NC_n16, 12}, //0xD4
	{&Z80gb::PUSH_DE, 16}, //0xD5
	{&Z80gb::SUB_A_n8, 8}, //0xD6
	{&Z80gb::RST_10H, 32}, //0xD7
	{&Z80gb::RET_C, 8}, //0xD8
	{&Z80gb::RETI, 8}, //0xD9
	{&Z80gb::JP_C_n16, 12}, //0xDA
	{&Z80gb::noImplementado, 0}, //0xDB
	{&Z80gb::CALL_C_n16, 12}, //0xDC
	{&Z80gb::noImplementado, 0}, //0xDD
	{&Z80gb::SBC_A_n8, 8}, //0xDE
	{&Z80gb::RST_18H, 32}, //0xDF
	
	// 0xE-
	{&Z80gb::LDH_mn8o_A, 12}, //0xE0
	{&Z80gb::POP_HL, 12}, //0xE1
	{&Z80gb::LD_mCo_A, 8}, //0xE2
	{&Z80gb::noImplementado, 0}, //0xE3
	{&Z80gb::noImplementado, 0}, //0xE4
	{&Z80gb::PUSH_HL, 16}, //0xE5
	{&Z80gb::AND_n8, 8}, //0xE6
	{&Z80gb::RST_20H, 32}, //0xE7
	{&Z80gb::ADD_SP_s8, 16}, //0xE8
	{&Z80gb::JP_mHL, 4}, //0xE9
	{&Z80gb::LD_mn16_A, 16}, //0xEA
	{&Z80gb::noImplementado, 0}, //0xEB
	{&Z80gb::noImplementado, 0}, //0xEC
	{&Z80gb::noImplementado, 0}, //0xED
	{&Z80gb::XOR_n8, 8}, //0xEE
	{&Z80gb::RST_28H, 32}, //0xEF
	
	// 0xF-
	{&Z80gb::LDH_A_mn8o, 12}, //0xF0
	{&Z80gb::POP_AF, 12}, //0xF1
	{&Z80gb::LD_A_mCo, 8}, //0xF2
	{&Z80gb::DI, 4}, //0xF3
	{&Z80gb::noImplementado, 0}, //0xF4
	{&Z80gb::PUSH_AF, 16}, //0xF5
	{&Z80gb::OR_n8, 8}, //0xF6
	{&Z80gb::RST_30H, 32}, //0xF7
	{&Z80gb::LDHL_SP_s8, 12}, //0xF8
	{&Z80gb::LD_SP_HL, 8}, //0xF9
	{&Z80gb::LD_A_mn16, 16}, //0xFA
	{&Z80gb::EI, 4}, //0xFB
	{&Z80gb::noImplementado, 0}, //0xFC
	{&Z80gb::noImplementado, 0}, //0xFD
	{&Z80gb::CP_n8, 8}, //0xFE
	{&Z80gb::RST_38H, 32} //0xFF
};

Z80gb::Instruccion Z80gb::CBinstructions[] = {
	// 0x0-
	{&Z80gb::RLC_B, 8}, //0x00
	{&Z80gb::RLC_C, 8}, //0x01
	{&Z80gb::RLC_D, 8}, //0x02
	{&Z80gb::RLC_E, 8}, //0x03
	{&Z80gb::RLC_H, 8}, //0x04
	{&Z80gb::RLC_L, 8}, //0x05
	{&Z80gb::RLC_mHL, 16}, //0x06
	{&Z80gb::RLC_A, 8}, //0x07
	{&Z80gb::RRC_B, 8}, //0x08
	{&Z80gb::RRC_C, 8}, //0x09
	{&Z80gb::RRC_D, 8}, //0x0A
	{&Z80gb::RRC_E, 8}, //0x0B
	{&Z80gb::RRC_H, 8}, //0x0C
	{&Z80gb::RRC_L, 8}, //0x0D
	{&Z80gb::RRC_mHL, 16}, //0x0E
	{&Z80gb::RRC_A, 8}, //0x0F
	
	// 0x1-
	{&Z80gb::RL_B, 8}, //0x10
	{&Z80gb::RL_C, 8}, //0x11
	{&Z80gb::RL_D, 8}, //0x12
	{&Z80gb::RL_E, 8}, //0x13
	{&Z80gb::RL_H, 8}, //0x14
	{&Z80gb::RL_L, 8}, //0x15
	{&Z80gb::RL_mHL, 16}, //0x16
	{&Z80gb::RL_A, 8}, //0x17
	{&Z80gb::RR_B, 8}, //0x18
	{&Z80gb::RR_C, 8}, //0x19
	{&Z80gb::RR_D, 8}, //0x1A
	{&Z80gb::RR_E, 8}, //0x1B
	{&Z80gb::RR_H, 8}, //0x1C
	{&Z80gb::RR_L, 8}, //0x1D
	{&Z80gb::RR_mHL, 16}, //0x1E
	{&Z80gb::RR_A, 8}, //0x1F
	
	// 0x2-
	{&Z80gb::SLA_B, 8}, //0x20
	{&Z80gb::SLA_C, 8}, //0x21
	{&Z80gb::SLA_D, 8}, //0x22
	{&Z80gb::SLA_E, 8}, //0x23
	{&Z80gb::SLA_H, 8}, //0x24
	{&Z80gb::SLA_L, 8}, //0x25
	{&Z80gb::SLA_mHL, 16}, //0x26
	{&Z80gb::SLA_A, 8}, //0x27
	{&Z80gb::SRA_B, 8}, //0x28
	{&Z80gb::SRA_C, 8}, //0x29
	{&Z80gb::SRA_D, 8}, //0x2A
	{&Z80gb::SRA_E, 8}, //0x2B
	{&Z80gb::SRA_H, 8}, //0x2C
	{&Z80gb::SRA_L, 8}, //0x2D
	{&Z80gb::SRA_mHL, 16}, //0x2E
	{&Z80gb::SRA_A, 8}, //0x2F
	
	// 0x3-
	{&Z80gb::SWAP_B, 8}, //0x30
	{&Z80gb::SWAP_C, 8}, //0x31
	{&Z80gb::SWAP_D, 8}, //0x32
	{&Z80gb::SWAP_E, 8}, //0x33
	{&Z80gb::SWAP_H, 8}, //0x34
	{&Z80gb::SWAP_L, 8}, //0x35
	{&Z80gb::SWAP_mHL, 16}, //0x36
	{&Z80gb::SWAP_A, 8}, //0x37
	{&Z80gb::SRL_B, 8}, //0x38
	{&Z80gb::SRL_C, 8}, //0x39
	{&Z80gb::SRL_D, 8}, //0x3A
	{&Z80gb::SRL_E, 8}, //0x3B
	{&Z80gb::SRL_H, 8}, //0x3C
	{&Z80gb::SRL_L, 8}, //0x3D
	{&Z80gb::SRL_mHL, 16}, //0x3E
	{&Z80gb::SRL_A, 8}, //0x3F
	
	// 0x4-
	{&Z80gb::BIT_0_B, 8}, //0x40
	{&Z80gb::BIT_0_C, 8}, //0x41
	{&Z80gb::BIT_0_D, 8}, //0x42
	{&Z80gb::BIT_0_E, 8}, //0x43
	{&Z80gb::BIT_0_H, 8}, //0x44
	{&Z80gb::BIT_0_L, 8}, //0x45
	{&Z80gb::BIT_0_mHL, 16}, //0x46
	{&Z80gb::BIT_0_A, 8}, //0x47
	{&Z80gb::BIT_1_B, 8}, //0x48
	{&Z80gb::BIT_1_C, 8}, //0x49
	{&Z80gb::BIT_1_D, 8}, //0x4A
	{&Z80gb::BIT_1_E, 8}, //0x4B
	{&Z80gb::BIT_1_H, 8}, //0x4C
	{&Z80gb::BIT_1_L, 8}, //0x4D
	{&Z80gb::BIT_1_mHL, 16}, //0x4E
	{&Z80gb::BIT_1_A, 8}, //0x4F
	
	// 0x5-
	{&Z80gb::BIT_2_B, 8}, //0x50
	{&Z80gb::BIT_2_C, 8}, //0x51
	{&Z80gb::BIT_2_D, 8}, //0x52
	{&Z80gb::BIT_2_E, 8}, //0x53
	{&Z80gb::BIT_2_H, 8}, //0x54
	{&Z80gb::BIT_2_L, 8}, //0x55
	{&Z80gb::BIT_2_mHL, 16}, //0x56
	{&Z80gb::BIT_2_A, 8}, //0x57
	{&Z80gb::BIT_3_B, 8}, //0x58
	{&Z80gb::BIT_3_C, 8}, //0x59
	{&Z80gb::BIT_3_D, 8}, //0x5A
	{&Z80gb::BIT_3_E, 8}, //0x5B
	{&Z80gb::BIT_3_H, 8}, //0x5C
	{&Z80gb::BIT_3_L, 8}, //0x5D
	{&Z80gb::BIT_3_mHL, 16}, //0x5E
	{&Z80gb::BIT_3_A, 8}, //0x5F
	
	// 0x6-
	{&Z80gb::BIT_4_B, 8}, //0x60
	{&Z80gb::BIT_4_C, 8}, //0x61
	{&Z80gb::BIT_4_D, 8}, //0x62
	{&Z80gb::BIT_4_E, 8}, //0x63
	{&Z80gb::BIT_4_H, 8}, //0x64
	{&Z80gb::BIT_4_L, 8}, //0x65
	{&Z80gb::BIT_4_mHL, 16}, //0x66
	{&Z80gb::BIT_4_A, 8}, //0x67
	{&Z80gb::BIT_5_B, 8}, //0x68
	{&Z80gb::BIT_5_C, 8}, //0x69
	{&Z80gb::BIT_5_D, 8}, //0x6A
	{&Z80gb::BIT_5_E, 8}, //0x6B
	{&Z80gb::BIT_5_H, 8}, //0x6C
	{&Z80gb::BIT_5_L, 8}, //0x6D
	{&Z80gb::BIT_5_mHL, 16}, //0x6E
	{&Z80gb::BIT_5_A, 8}, //0x6F
	
	// 0x7-
	{&Z80gb::BIT_6_B, 8}, //0x70
	{&Z80gb::BIT_6_C, 8}, //0x71
	{&Z80gb::BIT_6_D, 8}, //0x72
	{&Z80gb::BIT_6_E, 8}, //0x73
	{&Z80gb::BIT_6_H, 8}, //0x74
	{&Z80gb::BIT_6_L, 8}, //0x75
	{&Z80gb::BIT_6_mHL, 16}, //0x76
	{&Z80gb::BIT_6_A, 8}, //0x77
	{&Z80gb::BIT_7_B, 8}, //0x78
	{&Z80gb::BIT_7_C, 8}, //0x79
	{&Z80gb::BIT_7_D, 8}, //0x7A
	{&Z80gb::BIT_7_E, 8}, //0x7B
	{&Z80gb::BIT_7_H, 8}, //0x7C
	{&Z80gb::BIT_7_L, 8}, //0x7D
	{&Z80gb::BIT_7_mHL, 16}, //0x7E
	{&Z80gb::BIT_7_A, 8}, //0x7F
	
	// 0x8-
		{&Z80gb::RES_0_B, 8}, //0x80
	{&Z80gb::RES_0_C, 8}, //0x81
	{&Z80gb::RES_0_D, 8}, //0x82
	{&Z80gb::RES_0_E, 8}, //0x83
	{&Z80gb::RES_0_H, 8}, //0x84
	{&Z80gb::RES_0_L, 8}, //0x85
	{&Z80gb::RES_0_mHL, 16}, //0x86
	{&Z80gb::RES_0_A, 8}, //0x87
	{&Z80gb::RES_1_B, 8}, //0x88
	{&Z80gb::RES_1_C, 8}, //0x89
	{&Z80gb::RES_1_D, 8}, //0x8A
	{&Z80gb::RES_1_E, 8}, //0x8B
	{&Z80gb::RES_1_H, 8}, //0x8C
	{&Z80gb::RES_1_L, 8}, //0x8D
	{&Z80gb::RES_1_mHL, 16}, //0x8E
	{&Z80gb::RES_1_A, 8}, //0x8F
	
	// 0x9-
	{&Z80gb::RES_2_B, 8}, //0x90
	{&Z80gb::RES_2_C, 8}, //0x91
	{&Z80gb::RES_2_D, 8}, //0x92
	{&Z80gb::RES_2_E, 8}, //0x93
	{&Z80gb::RES_2_H, 8}, //0x94
	{&Z80gb::RES_2_L, 8}, //0x95
	{&Z80gb::RES_2_mHL, 16}, //0x96
	{&Z80gb::RES_2_A, 8}, //0x97
	{&Z80gb::RES_3_B, 8}, //0x98
	{&Z80gb::RES_3_C, 8}, //0x99
	{&Z80gb::RES_3_D, 8}, //0x9A
	{&Z80gb::RES_3_E, 8}, //0x9B
	{&Z80gb::RES_3_H, 8}, //0x9C
	{&Z80gb::RES_3_L, 8}, //0x9D
	{&Z80gb::RES_3_mHL, 16}, //0x9E
	{&Z80gb::RES_3_A, 8}, //0x9F
	
	// 0xA-
	{&Z80gb::RES_4_B, 8}, //0xA0
	{&Z80gb::RES_4_C, 8}, //0xA1
	{&Z80gb::RES_4_D, 8}, //0xA2
	{&Z80gb::RES_4_E, 8}, //0xA3
	{&Z80gb::RES_4_H, 8}, //0xA4
	{&Z80gb::RES_4_L, 8}, //0xA5
	{&Z80gb::RES_4_mHL, 16}, //0xA6
	{&Z80gb::RES_4_A, 8}, //0xA7
	{&Z80gb::RES_5_B, 8}, //0xA8
	{&Z80gb::RES_5_C, 8}, //0xA9
	{&Z80gb::RES_5_D, 8}, //0xAA
	{&Z80gb::RES_5_E, 8}, //0xAB
	{&Z80gb::RES_5_H, 8}, //0xAC
	{&Z80gb::RES_5_L, 8}, //0xAD
	{&Z80gb::RES_5_mHL, 16}, //0xAE
	{&Z80gb::RES_5_A, 8}, //0xAF
	
	// 0xB-
	{&Z80gb::RES_6_B, 8}, //0xB0
	{&Z80gb::RES_6_C, 8}, //0xB1
	{&Z80gb::RES_6_D, 8}, //0xB2
	{&Z80gb::RES_6_E, 8}, //0xB3
	{&Z80gb::RES_6_H, 8}, //0xB4
	{&Z80gb::RES_6_L, 8}, //0xB5
	{&Z80gb::RES_6_mHL, 16}, //0xB6
	{&Z80gb::RES_6_A, 8}, //0xB7
	{&Z80gb::RES_7_B, 8}, //0xB8
	{&Z80gb::RES_7_C, 8}, //0xB9
	{&Z80gb::RES_7_D, 8}, //0xBA
	{&Z80gb::RES_7_E, 8}, //0xBB
	{&Z80gb::RES_7_H, 8}, //0xBC
	{&Z80gb::RES_7_L, 8}, //0xBD
	{&Z80gb::RES_7_mHL, 16}, //0xBE
	{&Z80gb::RES_7_A, 8}, //0xBF

	
	// 0xC-
	{&Z80gb::SET_0_B, 8}, //0xC0
	{&Z80gb::SET_0_C, 8}, //0xC1
	{&Z80gb::SET_0_D, 8}, //0xC2
	{&Z80gb::SET_0_E, 8}, //0xC3
	{&Z80gb::SET_0_H, 8}, //0xC4
	{&Z80gb::SET_0_L, 8}, //0xC5
	{&Z80gb::SET_0_mHL, 16}, //0xC6
	{&Z80gb::SET_0_A, 8}, //0xC7
	{&Z80gb::SET_1_B, 8}, //0xC8
	{&Z80gb::SET_1_C, 8}, //0xC9
	{&Z80gb::SET_1_D, 8}, //0xCA
	{&Z80gb::SET_1_E, 8}, //0xCB
	{&Z80gb::SET_1_H, 8}, //0xCC
	{&Z80gb::SET_1_L, 8}, //0xCD
	{&Z80gb::SET_1_mHL, 16}, //0xCE
	{&Z80gb::SET_1_A, 8}, //0xCF
	
	// 0xD-
	{&Z80gb::SET_2_B, 8}, //0xD0
	{&Z80gb::SET_2_C, 8}, //0xD1
	{&Z80gb::SET_2_D, 8}, //0xD2
	{&Z80gb::SET_2_E, 8}, //0xD3
	{&Z80gb::SET_2_H, 8}, //0xD4
	{&Z80gb::SET_2_L, 8}, //0xD5
	{&Z80gb::SET_2_mHL, 16}, //0xD6
	{&Z80gb::SET_2_A, 8}, //0xD7
	{&Z80gb::SET_3_B, 8}, //0xD8
	{&Z80gb::SET_3_C, 8}, //0xD9
	{&Z80gb::SET_3_D, 8}, //0xDA
	{&Z80gb::SET_3_E, 8}, //0xDB
	{&Z80gb::SET_3_H, 8}, //0xDC
	{&Z80gb::SET_3_L, 8}, //0xDD
	{&Z80gb::SET_3_mHL, 16}, //0xDE
	{&Z80gb::SET_3_A, 8}, //0xDF
	
	// 0xE-
	{&Z80gb::SET_4_B, 8}, //0xE0
	{&Z80gb::SET_4_C, 8}, //0xE1
	{&Z80gb::SET_4_D, 8}, //0xE2
	{&Z80gb::SET_4_E, 8}, //0xE3
	{&Z80gb::SET_4_H, 8}, //0xE4
	{&Z80gb::SET_4_L, 8}, //0xE5
	{&Z80gb::SET_4_mHL, 16}, //0xE6
	{&Z80gb::SET_4_A, 8}, //0xE7
	{&Z80gb::SET_5_B, 8}, //0xE8
	{&Z80gb::SET_5_C, 8}, //0xE9
	{&Z80gb::SET_5_D, 8}, //0xEA
	{&Z80gb::SET_5_E, 8}, //0xEB
	{&Z80gb::SET_5_H, 8}, //0xEC
	{&Z80gb::SET_5_L, 8}, //0xED
	{&Z80gb::SET_5_mHL, 16}, //0xEE
	{&Z80gb::SET_5_A, 8}, //0xEF
	
	// 0xF-
	{&Z80gb::SET_6_B, 8}, //0xF0
	{&Z80gb::SET_6_C, 8}, //0xF1
	{&Z80gb::SET_6_D, 8}, //0xF2
	{&Z80gb::SET_6_E, 8}, //0xF3
	{&Z80gb::SET_6_H, 8}, //0xF4
	{&Z80gb::SET_6_L, 8}, //0xF5
	{&Z80gb::SET_6_mHL, 16}, //0xF6
	{&Z80gb::SET_6_A, 8}, //0xF7
	{&Z80gb::SET_7_B, 8}, //0xF8
	{&Z80gb::SET_7_C, 8}, //0xF9
	{&Z80gb::SET_7_D, 8}, //0xFA
	{&Z80gb::SET_7_E, 8}, //0xFB
	{&Z80gb::SET_7_H, 8}, //0xFC
	{&Z80gb::SET_7_L, 8}, //0xFD
	{&Z80gb::SET_7_mHL, 16}, //0xFE
	{&Z80gb::SET_7_A, 8} //0xFF

};

#endif
