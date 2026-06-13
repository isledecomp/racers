#ifndef RACENAMEENTRY_H
#define RACENAMEENTRY_H

#include "golname.h"
#include "golstringtable.h"
#include "race/data/circuitdefinitionlist.h"
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
		CircuitDefinitionList* p_raceList,
		const LegoChar* p_name,
		GolStringTable* p_stringTable
	);
	void Reset();
	LegoChar* GetName() { return m_name; }
	LegoChar* GetFolderName() { return m_folderName; }
	LegoChar* GetThemeName() { return m_themeName; }
	LegoChar* GetMascotName() { return m_mascotName; }
	LegoBool32 GetMirror() const { return m_mirror; }
	GolStringTable* GetStringTable() const { return m_stringTable; }
	LegoU16 GetDisplayStringIndex() const { return m_displayStringIndex; }
	void CopyDisplayString(GolString* p_string) const
	{
		m_stringTable->CopyStringByIndex(p_string, m_displayStringIndex);
	}

private:
	enum {
		c_tokenPositionInCircuit = 0x28,
		c_tokenFolderName = 0x29,
		c_tokenCircuit = 0x2a,
		c_tokenDisplayStringIndex = 0x2b,
		c_tokenMirror = 0x2c,
		c_tokenThemeName = 0x2d,
		c_tokenMascotName = 0x2e
	};

	LegoBool32 m_loaded;                                 // 0x00
	GolName m_name;                                      // 0x04
	GolName m_folderName;                                // 0x0c
	GolName m_themeName;                                 // 0x14
	GolName m_mascotName;                                // 0x1c
	CircuitDefinitionList::CircuitDefinition* m_circuit; // 0x24
	LegoU32 m_positionInCircuit;                         // 0x28
	LegoBool32 m_mirror;                                 // 0x2c
	GolStringTable* m_stringTable;                       // 0x30
	LegoU16 m_displayStringIndex;                        // 0x34
	undefined2 m_unk0x36;                                // 0x36
};

#endif // RACENAMEENTRY_H
