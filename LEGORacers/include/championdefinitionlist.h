#ifndef CHAMPIONDEFINITIONLIST_H
#define CHAMPIONDEFINITIONLIST_H

#include "decomp.h"
#include "golnametable.h"
#include "goltxtparser.h"
#include "types.h"

class GolExport;
class AmberHaze0x1c;
class MagentaRibbon0x20;

// VTABLE: LEGORACERS 0x004afde8
// SIZE 0x34
class ChampionDefinitionList : public GolNameTable {
public:
	// VTABLE: LEGORACERS 0x004afdf4
	// SIZE 0x1fc
	class CcbTxtParser : public GolTxtParser {};

	// SIZE 0x30
	struct ChampionDefinition {
		LegoChar m_unk0x00[8]; // 0x00
		LegoChar m_unk0x08[8]; // 0x08
		LegoChar m_unk0x10[8]; // 0x10
		LegoChar m_unk0x18[8]; // 0x18
		LegoFloat m_unk0x20;   // 0x20
		LegoFloat m_unk0x24;   // 0x24
		LegoFloat m_unk0x28;   // 0x28
		LegoFloat m_unk0x2c;   // 0x2c
	};

	ChampionDefinitionList();
	~ChampionDefinitionList() override; // vtable+0x00

	void Clear() override; // vtable+0x08

	// SYNTHETIC: LEGORACERS 0x0041d1f0
	// ChampionDefinitionList::`scalar deleting destructor'

private:
	void Reset();
	void ClearDefinitions();

	GolExport* m_golExport;            // 0x0c
	undefined4 m_unk0x10;              // 0x10
	ChampionDefinition* m_definitions; // 0x14
	undefined4** m_unk0x18;            // 0x18
	MagentaRibbon0x20** m_unk0x1c;     // 0x1c
	AmberHaze0x1c** m_unk0x20;         // 0x20
	undefined* m_unk0x24;              // 0x24
	undefined4 m_unk0x28;              // 0x28
	LegoU32 m_entryCount;              // 0x2c
	undefined4 m_unk0x30;              // 0x30
};

#endif // CHAMPIONDEFINITIONLIST_H
