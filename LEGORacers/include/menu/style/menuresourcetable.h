#ifndef MENURESOURCETABLE_H
#define MENURESOURCETABLE_H

#include "compat.h"
#include "decomp.h"
#include "golfileparser.h"
#include "golnametable.h"
#include "types.h"

class GolD3DRenderDevice;

// VTABLE: LEGORACERS 0x004b2210
// SIZE 0x20
class MenuResourceTable : public GolNameTable {
public:
	MenuResourceTable();
	~MenuResourceTable() override;                      // vtable+0x00
	void Clear() override;                              // vtable+0x08
	virtual void Reset();                               // vtable+0x0c
	virtual void CreateParser(undefined4 p_binary) = 0; // vtable+0x10
	virtual void ParseSection(undefined4 p_token) = 0;  // vtable+0x14
	void* ResolveEntryByName(const LegoChar* p_name);

	// SYNTHETIC: LEGORACERS 0x0046b070
	// MenuResourceTable::`scalar deleting destructor'

protected:
	LegoBool32 BeginLoad();
	LegoS32 ReadHeader();
	LegoS32 ReadSectionCount();
	void ReadRect(LegoS32* p_ints);
	void ReadVisualState(LegoS8* p_ints);
	void ParseSections();

	LegoBool m_loaded;              // 0x0c
	GolFileParser* m_parser;        // 0x10
	GolD3DRenderDevice* m_renderer; // 0x14
	LegoU32 m_entryCount;           // 0x18
	undefined4 m_entryCapacity;     // 0x1c
};

#endif // MENURESOURCETABLE_H
