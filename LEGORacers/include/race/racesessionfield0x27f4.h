#ifndef RACESESSIONFIELD0X27F4_H
#define RACESESSIONFIELD0X27F4_H

#include "golmath.h"
#include "goltxtparser.h"
#include "types.h"

class GolFileParser;

// SIZE 0x08
class RaceSessionField0x27f4 {
public:
	// VTABLE: LEGORACERS 0x004afef4
	// SIZE 0x1fc
	class CpbTxtParser : public GolTxtParser {};

	// SIZE 0x24
	class Entry {
	public:
		// SIZE 0x04
		union Field0x20 {
			LegoU32 m_all;     // 0x00
			LegoU8 m_items[4]; // 0x00
		};

		Entry();
		~Entry();

	private:
		friend class RaceSessionField0x27f4;

		void Reset();
		void FUN_0041e630();
		void FUN_0041e640(GolFileParser* p_parser, LegoBool32 p_mirror);

	public:
		GolVec3 m_unk0x00;   // 0x00
		LegoFloat m_unk0x0c; // 0x0c
		GolVec3 m_unk0x10;   // 0x10
		LegoFloat m_unk0x1c; // 0x1c
		Field0x20 m_unk0x20; // 0x20
	};

	RaceSessionField0x27f4();
	~RaceSessionField0x27f4();

	void Reset();
	void FUN_0041e770(const LegoChar* p_name, LegoBool32 p_binary, LegoBool32 p_mirror);
	Entry* FUN_0041e940(LegoU32 p_unk0x04);
	void FUN_0041e950();
	LegoU32 FUN_0041ea60();
	LegoU32 FUN_0041ea90(LegoU32 p_unk0x04, LegoU32* p_unk0x08);
	void FUN_0041eaf0(GolVec3* p_position, LegoFloat p_distance, Entry* p_entry);

private:
	Entry* m_entries; // 0x00
	LegoU32 m_count;  // 0x04
};

#endif // RACESESSIONFIELD0X27F4_H
