#ifndef RACENAMELIST_H
#define RACENAMELIST_H

#include "compat.h"
#include "decomp.h"
#include "golnametable.h"
#include "goltxtparser.h"
#include "racedefinitionlist.h"
#include "racenameentry.h"
#include "types.h"

class GolStringTable;

// VTABLE: LEGORACERS 0x004b08c4
// SIZE 0x14
class RaceNameList : public GolNameTable {
public:
	// VTABLE: LEGORACERS 0x004b08d0
	// SIZE 0x1fc
	class RcbTxtParser : public GolTxtParser {};

	RaceNameList();
	~RaceNameList() override; // vtable+0x00
	void Clear() override;    // vtable+0x08

	// SYNTHETIC: LEGORACERS 0x00436680
	// RaceNameList::`scalar deleting destructor'

	LegoU32 GetEntryIndexByName(LegoChar* p_name);
	void Load(
		GolStringTable* p_stringTable,
		RaceDefinitionList* p_raceList,
		const LegoChar* p_fileName,
		undefined4 p_binary
	);

private:
	enum {
		c_tokenRaceName = 0x27
	};

	RaceNameEntry* m_entries; // 0x0c
	LegoU32 m_entryCount;     // 0x10
};

#endif // RACENAMELIST_H
