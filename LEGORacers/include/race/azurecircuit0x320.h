#ifndef AZURECIRCUIT0X320_H
#define AZURECIRCUIT0X320_H

#include "app/legoracers.h"
#include "decomp.h"
#include "types.h"

// SIZE 0x320
class AzureCircuit0x320 {
public:
	// SIZE 0xdbc
	class Field0x318 {
	public:
		undefined m_unk0x000[0xdb8 - 0x000]; // 0x000
		undefined4 m_unk0xdb8;               // 0xdb8
	};

	// SIZE 0xe34
	class Entry0xe34 {
	public:
		undefined m_unk0x000[0xce4 - 0x000]; // 0x000
		LegoU32 m_unk0xce4;                  // 0xce4
		undefined m_unk0xce8[0xcec - 0xce8]; // 0xce8
		LegoU32 m_unk0xcec[0x148 / 4];       // 0xcec
	};

	void FUN_0043beb0(LegoRacers::Context* p_context);
	Field0x318* GetUnk0x318() { return m_unk0x318; }

private:
	enum {
		c_invalidScore = 0xffffffff,
	};

	undefined m_unk0x000[0x140 - 0x000]; // 0x000
	Entry0xe34* m_unk0x140;              // 0x140
	LegoU32 m_unk0x144;                  // 0x144
	undefined m_unk0x148[0x29c - 0x148]; // 0x148
	LegoU8 m_unk0x29c;                   // 0x29c
	undefined m_unk0x29d[0x318 - 0x29d]; // 0x29d
	Field0x318* m_unk0x318;              // 0x318
	undefined m_unk0x31c[0x320 - 0x31c]; // 0x31c
};

#endif // AZURECIRCUIT0X320_H
