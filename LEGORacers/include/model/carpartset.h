#ifndef CARPARTSET_H
#define CARPARTSET_H

#include "decomp.h"
#include "types.h"

class LegoPieceLibrary;
class CarBuildModel;
class LegoColorTable;

// SIZE 0x14
class CarPartSet {
public:
	enum {
		e_pieceType = 0x2e,
		e_parts = 0x2f,
		e_choices = 0x30,
		e_name = 0x31,
	};

	// SIZE 0x04
	struct PartChoice {
		LegoU16 m_pieceType;       // 0x00
		LegoU8 m_colorRecordIndex; // 0x02
	};

	// SIZE 0x18
	class Entry {
	public:
		Entry();
		~Entry();
		void FUN_004513d0(CarBuildModel* p_buildModel);
		void SetIndex(LegoS32 p_index) { m_index = p_index; }
		LegoS32 GetPieceType() const { return m_pieceType; }
		LegoS32 GetIndex() const { return m_index; }
		void Load(
			const LegoChar* p_filename,
			LegoPieceLibrary* p_pieceLibrary,
			LegoColorTable* p_colorTable,
			undefined4 p_binary
		);
		void FillChoiceIndices(LegoS32* p_dest, LegoS32 p_startIndex, LegoS32 p_count);
		LegoS32 NormalizeChoiceIndex(LegoS32 p_index);
		void GetChoice(LegoS32 p_index, LegoS32* p_pieceType, LegoS32* p_colorRecordIndex);
		LegoS32 FindChoiceIndex(LegoS32 p_pieceType, LegoS32 p_colorRecordIndex);
		const LegoChar* GetName() const { return m_name; }

	private:
		void Clear();

		LegoChar m_name[8];    // 0x00
		LegoS32 m_pieceType;   // 0x08
		LegoS32 m_index;       // 0x0c
		LegoS32 m_choiceCount; // 0x10
		PartChoice* m_choices; // 0x14
	};

	CarPartSet();
	~CarPartSet();

	void Clear();
	void SetColorTable(LegoColorTable* p_colorTable) { m_colorTable = p_colorTable; }
	void Load(
		const LegoChar* p_filename,
		LegoPieceLibrary* p_pieceLibrary,
		LegoColorTable* p_colorTable,
		undefined4 p_binary
	);
	Entry* FindEntry(LegoS32 p_index);
	LegoS32 FindEntryIndex(LegoS32 p_index);
	Entry* GetEntries() const { return m_entries; }
	Entry* GetSelectedEntry() const { return m_selectedEntry; }
	void SetSelectedEntry(Entry* p_selectedEntry) { m_selectedEntry = p_selectedEntry; }

private:
	LegoColorTable* m_colorTable;     // 0x00
	LegoPieceLibrary* m_pieceLibrary; // 0x04
	LegoS32 m_entryCount;             // 0x08
	Entry* m_entries;                 // 0x0c
	Entry* m_selectedEntry;           // 0x10
};

#endif // CARPARTSET_H
