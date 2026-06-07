#ifndef MENURACERCAROUSEL_H
#define MENURACERCAROUSEL_H

#include "compat.h"
#include "decomp.h"
#include "menu/widgets/menumodelcarousel.h"
#include "racer/driverheadbuilder.h"
#include "scene/golbillboard.h"

class MenuGameContext;
class SaveSystem;
class LavenderVault0x764;

// VTABLE: LEGORACERS 0x004b39d4
// SIZE 0x170
class MenuRacerCarousel : public MenuModelCarousel {
public:
	// SIZE 0x80
	class CreateParams : public MenuModelCarousel::CreateParams {
	public:
		MenuGameContext* m_context;   // 0x74
		DriverHeadBuilder* m_unk0x78; // 0x78
		LegoU32 m_unk0x7c;            // 0x7c
	};

	MenuRacerCarousel();

	void Reset() override;                // vtable+0x00
	~MenuRacerCarousel() override;        // vtable+0x04
	LegoBool32 VTable0x08() override;     // vtable+0x08
	void VTable0x50(undefined4) override; // vtable+0x50
	LegoS32 VTable0x54() override;        // vtable+0x54
	LegoS32 VTable0x58() override;        // vtable+0x58
	void VTable0x60(LegoS32) override;    // vtable+0x60

	LegoBool32 FUN_00483a60(CreateParams* p_createParams, MenuStyleTable::CarouselStyle* p_styleEntry);
	void FUN_00484170(LegoS32 p_index);
	LegoS32 GetSelectedValue() const { return m_unk0xd0[m_unk0x6c]; }
	LegoS32 GetItemCount() const { return m_unk0x68; }

	// SYNTHETIC: LEGORACERS 0x004839c0
	// MenuRacerCarousel::`scalar deleting destructor'

protected:
	void CopyModelMaterialTable(GolModelBase* p_model, GolBillboard::Field0x2c* p_materialTable);
	void FUN_00483b60(LegoS32 p_unk0x04);
	void FUN_00483c60(LavenderVault0x764* p_config, SaveSystem* p_saveSystem, LegoU32 p_unlockFlags);
	void FUN_00483d00(LavenderVault0x764* p_config, SaveSystem* p_saveSystem, LegoU32 p_unlockFlags);
	void FUN_00483da0(LavenderVault0x764* p_config, SaveSystem* p_saveSystem, LegoU32 p_unlockFlags);
	void FUN_00483e40(LavenderVault0x764* p_config, SaveSystem* p_saveSystem, LegoU32 p_unlockFlags);
	void FUN_00483ee0();

	GolBillboard::Field0x2c* m_materialTables; // 0xc0
	DriverHeadBuilder* m_unk0xc4;              // 0xc4
	MenuGameContext* m_unk0xc8;                // 0xc8
	LegoU32 m_unk0xcc;                         // 0xcc
	LegoS32 m_unk0xd0[(0x170 - 0xd0) / 4];     // 0xd0
};

#endif // MENURACERCAROUSEL_H
