#ifndef RACENAMEENTRY_H
#define RACENAMEENTRY_H

#include "racedefinitionlist.h"
#include "types.h"

class GolFileParser;
class GolStringTable;

// SIZE 0x38
class RaceNameEntry {
public:
	RaceNameEntry();
	~RaceNameEntry();

	void Clear();
	void Load(
		GolFileParser& p_parser,
		RaceDefinitionList* p_raceList,
		const LegoChar* p_name,
		GolStringTable* p_stringTable
	);
	void Reset();

private:
	enum {
		c_tokenRaceDefinitionIndex = 0x28,
		c_tokenUnk0x0cName = 0x29,
		c_tokenCircuit = 0x2a,
		c_tokenUnk0x34 = 0x2b,
		c_tokenFlag0x2c = 0x2c,
		c_tokenUnk0x14Name = 0x2d,
		c_tokenUnk0x1cName = 0x2e
	};

	LegoBool32 m_loaded;                           // 0x00
	LegoChar m_name[8];                            // 0x04
	LegoChar m_unk0x0c[8];                         // 0x0c
	LegoChar m_unk0x14[8];                         // 0x14
	LegoChar m_unk0x1c[8];                         // 0x1c
	RaceDefinitionList::RaceDefinition* m_circuit; // 0x24
	LegoU32 m_raceDefinitionIndex;                 // 0x28
	LegoBool32 m_unk0x2c;                          // 0x2c
	GolStringTable* m_stringTable;                 // 0x30
	LegoU16 m_unk0x34;                             // 0x34
	undefined2 m_unk0x36;                          // 0x36
};

#endif // RACENAMEENTRY_H
