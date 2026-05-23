#ifndef SIENNACIRCUIT0X154_H
#define SIENNACIRCUIT0X154_H

#include "ceruleanemperor0x4c.h"
#include "decomp.h"
#include "obscurevantage0x58.h"
#include "types.h"

class LegoPieceLibrary;
class ObscureIcon0x1a8;
class SapphireReef0x2030;
class TopazBurst0x14;
class VerdantTide0x38;

// SIZE 0x154
class SiennaCircuit0x154 {
public:
	// SIZE 0x84
	class CreateParams0x84 : public ObscureVantage0x58::CreateParams0x30 {
	public:
		undefined m_unk0x30[0x38 - 0x30]; // 0x30
		LegoBool m_unk0x38;               // 0x38
		undefined m_unk0x39[0x3c - 0x39]; // 0x39
		undefined4 m_unk0x3c;             // 0x3c
		undefined2 m_unk0x40;             // 0x40
		undefined m_unk0x42[0x44 - 0x42]; // 0x42
		ObscureIcon0x1a8* m_parent;       // 0x44
		undefined2 m_unk0x48;             // 0x48
		LegoU8 m_unk0x4a;                 // 0x4a
		undefined m_unk0x4b[0x6c - 0x4b]; // 0x4b
		LegoU32 m_unk0x6c;                // 0x6c
		LegoFloat m_unk0x70;              // 0x70
		TopazBurst0x14* m_unk0x74;        // 0x74
		LegoPieceLibrary* m_pieceLibrary; // 0x78
		SapphireReef0x2030* m_unk0x7c;    // 0x7c
		VerdantTide0x38* m_unk0x80;       // 0x80
	};

	LegoBool32 FUN_00485300(CreateParams0x84* p_createParams, CeruleanEmperor0x4c::Entry0x150* p_styleEntry);

private:
	undefined m_unk0x00[0x154]; // 0x00
};

#endif // SIENNACIRCUIT0X154_H
