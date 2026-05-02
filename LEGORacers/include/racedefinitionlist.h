#ifndef RACEDEFINITIONLIST_H
#define RACEDEFINITIONLIST_H

#include "decomp.h"
#include "golnametable.h"
#include "goltxtparser.h"
#include "types.h"

class GolStringTable;
class RaceNameEntry;

// VTABLE: LEGORACERS 0x004affd4
// SIZE 0x14
class RaceDefinitionList : public GolNameTable {
public:
	// VTABLE: LEGORACERS 0x004affe0
	// SIZE 0x1fc
	class CrbTxtParser : public GolTxtParser {};

	// SIZE 0x64
	class RaceDefinition {
	public:
		RaceDefinition();
		~RaceDefinition();

		void Clear();
		void Reset();
		void Load(GolFileParser& p_parser, const LegoChar* p_name, GolStringTable* p_stringTable);
		void SetRaceNameEntry(LegoU32 p_index, RaceNameEntry* p_raceNameEntry)
		{
			m_raceNameEntries[p_index] = p_raceNameEntry;
		}

	private:
		enum {
			c_tokenCourseList = 0x28,
			c_tokenCircuit = 0x29,
			c_tokenStringIndex = 0x2a,
			c_tokenMenuName = 0x2b
		};

		LegoBool32 m_loaded;                 // 0x00
		LegoChar m_name[8];                  // 0x04
		LegoChar m_menuName[8];              // 0x0c
		LegoU32 m_courseCount;               // 0x14
		LegoChar m_courseNames[6][8];        // 0x18
		RaceNameEntry* m_raceNameEntries[4]; // 0x48
		LegoS32 m_stringIndex;               // 0x58
		GolStringTable* m_stringTable;       // 0x5c
		LegoU16 m_circuit;                   // 0x60
		undefined2 m_unk0x62;                // 0x62
	};

	RaceDefinitionList();
	~RaceDefinitionList() override; // vtable+0x00
	void Clear() override;          // vtable+0x08

	// SYNTHETIC: LEGORACERS 0x0041f160
	// RaceDefinitionList::`scalar deleting destructor'

	void Load(GolStringTable* p_stringTable, const LegoChar* p_fileName, undefined4 p_binary);

private:
	enum {
		c_tokenRaceDefinition = 0x27
	};

	RaceDefinition* m_entries; // 0x0c
	LegoU32 m_entryCount;      // 0x10
};

#endif // RACEDEFINITIONLIST_H
