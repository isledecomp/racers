#ifndef CIRCUITDEFINITIONLIST_H
#define CIRCUITDEFINITIONLIST_H

#include "decomp.h"
#include "golname.h"
#include "golnametable.h"
#include "goltxtparser.h"
#include "types.h"

class GolStringTable;
class RaceNameEntry;

// VTABLE: LEGORACERS 0x004affd4
// SIZE 0x14
class CircuitDefinitionList : public GolNameTable {
public:
	// VTABLE: LEGORACERS 0x004affe0
	// SIZE 0x1fc
	class CrbTxtParser : public GolTxtParser {};

	// SIZE 0x64
	class CircuitDefinition {
	public:
		CircuitDefinition();
		~CircuitDefinition();

		void Clear();
		void Reset();
		void Load(GolFileParser& p_parser, const LegoChar* p_name, GolStringTable* p_stringTable);
		void SetRaceNameEntry(LegoU32 p_index, RaceNameEntry* p_raceNameEntry)
		{
			m_raceNameEntries[p_index] = p_raceNameEntry;
		}
		LegoChar* GetName() { return m_name; }
		const LegoChar* GetMenuName() const { return m_menuName; }
		LegoU32 GetDriverCount() const { return m_driverCount; }
		const LegoChar* GetDriverName(LegoU32 p_index) const { return m_driverNames[p_index]; }
		RaceNameEntry* GetRaceNameEntry(LegoU32 p_index) const { return m_raceNameEntries[p_index]; }
		LegoS32 GetStringIndex() const { return m_stringIndex; }

	private:
		enum {
			c_tokenDriverList = 0x28,
			c_tokenCircuitNumber = 0x29,
			c_tokenStringIndex = 0x2a,
			c_tokenMenuName = 0x2b
		};

		LegoBool32 m_loaded;                 // 0x00
		GolName m_name;                      // 0x04
		GolName m_menuName;                  // 0x0c
		LegoU32 m_driverCount;               // 0x14
		GolName m_driverNames[6];            // 0x18
		RaceNameEntry* m_raceNameEntries[4]; // 0x48
		LegoS32 m_stringIndex;               // 0x58
		GolStringTable* m_stringTable;       // 0x5c
		LegoU16 m_circuitNumber;             // 0x60
		undefined2 m_unk0x62;                // 0x62
	};

	CircuitDefinitionList();
	~CircuitDefinitionList() override; // vtable+0x00
	void Clear() override;             // vtable+0x08

	// SYNTHETIC: LEGORACERS 0x0041f160
	// CircuitDefinitionList::`scalar deleting destructor'

	void Load(GolStringTable* p_stringTable, const LegoChar* p_fileName, undefined4 p_binary);
	CircuitDefinition* GetEntry(LegoU32 p_index) const
	{
		if (p_index >= m_entryCount) {
			return NULL;
		}

		return &m_entries[p_index];
	}
	CircuitDefinition* GetEntries() const { return m_entries; }
	LegoU32 GetEntryCount() const { return m_entryCount; }
	LegoU32 GetEntryIndex(CircuitDefinition* p_entry) const;

private:
	enum {
		c_tokenCircuitDefinition = 0x27
	};

	CircuitDefinition* m_entries; // 0x0c
	LegoU32 m_entryCount;         // 0x10
};

#endif // CIRCUITDEFINITIONLIST_H
