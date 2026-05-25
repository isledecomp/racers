#ifndef TOPAZBURST0X14_H
#define TOPAZBURST0X14_H

#include "decomp.h"
#include "types.h"

class LegoPieceLibrary;
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
		void SetIndex(LegoS32 p_index) { m_index = p_index; }
		void Load(
			const LegoChar* p_filename,
			LegoPieceLibrary* p_pieceLibrary,
			VerdantTide0x38* p_verdantTide,
			undefined4 p_binary
		);

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

	void SetUnk0x00(VerdantTide0x38* p_verdantTide) { m_verdantTide = p_verdantTide; }
	void FUN_0049ce80(
		const LegoChar* p_filename,
		LegoPieceLibrary* p_pieceLibrary,
		VerdantTide0x38* p_unk0x0c,
		undefined4 p_binary
	);

private:
	void FUN_0049ce40();

	VerdantTide0x38* m_verdantTide;   // 0x00
	LegoPieceLibrary* m_pieceLibrary; // 0x04
	LegoS32 m_entryCount;             // 0x08
	Entry* m_entries;                 // 0x0c
	undefined4 m_unk0x10;             // 0x10
};

#endif // TOPAZBURST0X14_H
