#ifndef MAROONATOLL0X170_H
#define MAROONATOLL0X170_H

#include "compat.h"
#include "decomp.h"
#include "menu/widgets/violetshoal0xc0.h"
#include "scene/golbillboard.h"
#include "util/tealcrucible0x50.h"

class MenuToolContext0x4bc8;
class SaveSystem;
class LavenderVault0x764;

// VTABLE: LEGORACERS 0x004b39d4
// SIZE 0x170
class MaroonAtoll0x170 : public VioletShoal0xc0 {
public:
	// SIZE 0x80
	class CreateParams0x80 : public VioletShoal0xc0::CreateParams0x74 {
	public:
		MenuToolContext0x4bc8* m_context; // 0x74
		TealCrucible0x50* m_unk0x78;      // 0x78
		LegoU32 m_unk0x7c;                // 0x7c
	};

	MaroonAtoll0x170();

	void Reset() override;                // vtable+0x00
	~MaroonAtoll0x170() override;         // vtable+0x04
	LegoBool32 VTable0x08() override;     // vtable+0x08
	void VTable0x50(undefined4) override; // vtable+0x50
	LegoS32 VTable0x54() override;        // vtable+0x54
	LegoS32 VTable0x58() override;        // vtable+0x58
	void VTable0x60(LegoS32) override;    // vtable+0x60

	LegoBool32 FUN_00483a60(CreateParams0x80* p_createParams, CeruleanEmperor0x4c::Entry0x18* p_styleEntry);
	void FUN_00484170(LegoS32 p_index);
	LegoS32 GetSelectedValue() const { return m_unk0xd0[m_unk0x6c]; }
	LegoS32 GetItemCount() const { return m_unk0x68; }

	// SYNTHETIC: LEGORACERS 0x004839c0
	// MaroonAtoll0x170::`scalar deleting destructor'

protected:
	void CopyModelMaterialTable(GolModelBase* p_model, GolBillboard::Field0x2c* p_materialTable);
	void FUN_00483b60(LegoS32 p_unk0x04);
	void FUN_00483c60(LavenderVault0x764* p_config, SaveSystem* p_saveSystem, LegoU32 p_unlockFlags);
	void FUN_00483d00(LavenderVault0x764* p_config, SaveSystem* p_saveSystem, LegoU32 p_unlockFlags);
	void FUN_00483da0(LavenderVault0x764* p_config, SaveSystem* p_saveSystem, LegoU32 p_unlockFlags);
	void FUN_00483e40(LavenderVault0x764* p_config, SaveSystem* p_saveSystem, LegoU32 p_unlockFlags);
	void FUN_00483ee0();

	GolBillboard::Field0x2c* m_materialTables; // 0xc0
	TealCrucible0x50* m_unk0xc4;               // 0xc4
	MenuToolContext0x4bc8* m_unk0xc8;          // 0xc8
	LegoU32 m_unk0xcc;                         // 0xcc
	LegoS32 m_unk0xd0[(0x170 - 0xd0) / 4];     // 0xd0
};

#endif // MAROONATOLL0X170_H
