#ifndef TOPAZBURST0X14_H
#define TOPAZBURST0X14_H

#include "decomp.h"
#include "types.h"

class LegoPieceLibrary;
class SapphireReef0x2030;
class VerdantTide0x38;

// SIZE 0x14
class TopazBurst0x14 {
public:
	// SIZE 0x04
	struct PartChoice0x4 {
		LegoU16 m_pieceType;       // 0x00
		LegoU8 m_colorRecordIndex; // 0x02
		undefined m_padding0x03;   // 0x03
	};

	// SIZE 0x18
	class Entry {
	public:
		Entry();
		~Entry();
		void FUN_004513d0(SapphireReef0x2030* p_unk0x04);
		void SetIndex(LegoS32 p_index) { m_index = p_index; }
		LegoS32 GetUnk0x08() const { return m_unk0x08; }
		LegoS32 GetIndex() const { return m_index; }
		void Load(
			const LegoChar* p_filename,
			LegoPieceLibrary* p_pieceLibrary,
			VerdantTide0x38* p_verdantTide,
			undefined4 p_binary
		);
		void FillChoiceIndices(LegoS32* p_dest, LegoS32 p_startIndex, LegoS32 p_count);
		LegoS32 NormalizeChoiceIndex(LegoS32 p_index);
		LegoS32* GetChoice(LegoS32 p_index, LegoS32* p_pieceType, LegoS32* p_colorRecordIndex);
		LegoS32 FindChoiceIndex(LegoS32 p_pieceType, LegoS32 p_colorRecordIndex);

	private:
		void FUN_0049cb00();

		LegoChar m_name[8];       // 0x00
		LegoS32 m_unk0x08;        // 0x08
		LegoS32 m_index;          // 0x0c
		LegoS32 m_choiceCount;    // 0x10
		PartChoice0x4* m_choices; // 0x14
	};

	TopazBurst0x14();
	~TopazBurst0x14();

	void FUN_0049ce40();
	void SetUnk0x00(VerdantTide0x38* p_verdantTide) { m_verdantTide = p_verdantTide; }
	void FUN_0049ce80(
		const LegoChar* p_filename,
		LegoPieceLibrary* p_pieceLibrary,
		VerdantTide0x38* p_unk0x0c,
		undefined4 p_binary
	);
	Entry* FindEntry(LegoS32 p_index);
	LegoS32 FindEntryIndex(LegoS32 p_index);
	Entry* GetEntries() const { return m_entries; }
	Entry* GetUnk0x10() const { return m_unk0x10; }

private:
	VerdantTide0x38* m_verdantTide;   // 0x00
	LegoPieceLibrary* m_pieceLibrary; // 0x04
	LegoS32 m_entryCount;             // 0x08
	Entry* m_entries;                 // 0x0c
	Entry* m_unk0x10;                 // 0x10
};

#endif // TOPAZBURST0X14_H
