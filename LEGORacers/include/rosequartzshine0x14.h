#ifndef ROSEQUARTZSHINE0X14_H
#define ROSEQUARTZSHINE0X14_H

#include "compat.h"
#include "decomp.h"
#include "golnametable.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004b08c4
// SIZE 0x14
class RoseQuartzShine0x14 : public GolNameTable {
public:
	// SIZE 0x38
	class Struct0x38 {
	public:
		Struct0x38();
		~Struct0x38();

		void FUN_004364b0();
		void FUN_00436650();

	private:
		// SIZE 0x08
		class Struct0x08 {
		public:
			undefined4 m_unk0x00; // 0x00
			undefined4 m_unk0x04; // 0x04
		};

		undefined4 m_unk0x00; // 0x00
		Struct0x08 m_unk0x04; // 0x04
		Struct0x08 m_unk0x0c; // 0x0c
		Struct0x08 m_unk0x14; // 0x14
		Struct0x08 m_unk0x1c; // 0x1c
		undefined4 m_unk0x24; // 0x24
		undefined4 m_unk0x28; // 0x28
		undefined4 m_unk0x2c; // 0x2c
		undefined4 m_unk0x30; // 0x30
		undefined2 m_unk0x34; // 0x34
		undefined2 m_unk0x36; // 0x36
	};

	RoseQuartzShine0x14();
	~RoseQuartzShine0x14() override; // vtable+0x00
	void Clear() override;           // vtable+0x08

	// SYNTHETIC: LEGORACERS 0x00436680
	// RoseQuartzShine0x14::`scalar deleting destructor'

	LegoU32 GetEntryIndexByName(LegoChar* p_name);

private:
	Struct0x38* m_entries; // 0x0c
	LegoU32 m_entryCount;  // 0x10
};

#endif // ROSEQUARTZSHINE0X14_H
