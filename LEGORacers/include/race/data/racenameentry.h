#ifndef RACENAMEENTRY_H
#define RACENAMEENTRY_H

#include "golname.h"
#include "golstringtable.h"
#include "race/data/racedefinitionlist.h"
#include "types.h"

class GolFileParser;
class GolString;

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
	LegoChar* GetName() { return m_name; }
	LegoChar* GetUnk0x0cName() { return m_unk0x0c; }
	LegoChar* GetUnk0x14Name() { return m_unk0x14; }
	LegoChar* GetUnk0x1cName() { return m_unk0x1c; }
	LegoBool32 GetUnk0x2c() const { return m_unk0x2c; }
	GolStringTable* GetStringTable() const { return m_stringTable; }
	LegoU16 GetUnk0x34() const { return m_unk0x34; }
	void CopyDisplayString(GolString* p_string) const { m_stringTable->CopyStringByIndex(p_string, m_unk0x34); }

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
	GolName m_name;                                // 0x04
	GolName m_unk0x0c;                             // 0x0c
	GolName m_unk0x14;                             // 0x14
	GolName m_unk0x1c;                             // 0x1c
	RaceDefinitionList::RaceDefinition* m_circuit; // 0x24
	LegoU32 m_raceDefinitionIndex;                 // 0x28
	LegoBool32 m_unk0x2c;                          // 0x2c
	GolStringTable* m_stringTable;                 // 0x30
	LegoU16 m_unk0x34;                             // 0x34
	undefined2 m_unk0x36;                          // 0x36
};

#endif // RACENAMEENTRY_H
