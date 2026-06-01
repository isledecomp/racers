#ifndef VIOLETSHOAL0XC0_H
#define VIOLETSHOAL0XC0_H

#include "compat.h"
#include "decomp.h"
#include "golmodelentity.h"
#include "menu/widgets/obscurecarousel0x78.h"
#include "render/golrenderdevice.h"

class GolCamera;
class GolModelBase;

// VTABLE: LEGORACERS 0x004b2450
// SIZE 0xc0
class VioletShoal0xc0 : public ObscureCarousel0x78 {
public:
	// SIZE 0x74
	class CreateParams0x74 : public ObscureCarousel0x78::CreateParams0x38 {
	public:
		LegoS32 m_unk0x38;      // 0x38
		Rect* m_unk0x3c;        // 0x3c
		LegoFloat m_unk0x40;    // 0x40
		LegoS32 m_unk0x44;      // 0x44
		LegoFloat m_unk0x48[9]; // 0x48
		LegoU32 m_unk0x6c;      // 0x6c
		LegoFloat m_unk0x70;    // 0x70
	};

	// SIZE 0xd0
	class Item0xd0 {
	public:
		LegoFloat m_unk0x00;      // 0x00
		LegoFloat m_unk0x04;      // 0x04
		LegoFloat m_unk0x08;      // 0x08
		LegoFloat m_unk0x0c;      // 0x0c
		Rect m_rect;              // 0x10
		LegoFloat m_unk0x20;      // 0x20
		LegoFloat m_unk0x24;      // 0x24
		LegoFloat m_unk0x28;      // 0x28
		GolModelBase* m_model;    // 0x2c
		LegoFloat m_modelRadius;  // 0x30
		GolModelEntity m_entity;  // 0x34
		undefined4 m_unk0xc4;     // 0xc4
		VisualState0x4 m_unk0xc8; // 0xc8
		VisualState0x4 m_unk0xcc; // 0xcc
	};

	VioletShoal0xc0();

	void Reset() override;                                                                    // vtable+0x00
	~VioletShoal0xc0() override;                                                              // vtable+0x04
	LegoBool32 VTable0x08() override;                                                         // vtable+0x08
	void SetParent(ObscureVantage0x58*) override;                                             // vtable+0x0c
	ObscureVantage0x58* VTable0x30(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x30
	ObscureVantage0x58* VTable0x38(Rect*, Rect*) override;                                    // vtable+0x38
	undefined4 VTable0x3c(undefined4) override;                                               // vtable+0x3c
	void VTable0x40() override;                                                               // vtable+0x40
	void VTable0x44(undefined4) override;                                                     // vtable+0x44
	void VTable0x48(VisualState0x4*, VisualState0x4*) override;                               // vtable+0x48
	void VTable0x4c(VisualState0x4*, VisualState0x4*) override;                               // vtable+0x4c
	LegoS32 VTable0x54() override;                                                            // vtable+0x54
	LegoS32 VTable0x58() override;                                                            // vtable+0x58
	virtual void VTable0x5c(undefined4, GolModelEntity*);                                     // vtable+0x5c
	virtual void VTable0x60(LegoS32);                                                         // vtable+0x60

	// SYNTHETIC: LEGORACERS 0x0046ca60
	// VioletShoal0xc0::`scalar deleting destructor'

protected:
	LegoBool32 FUN_0046cb10(CreateParams0x74* p_createParams, CeruleanEmperor0x4c::Entry0x18* p_styleEntry);
	void FUN_0046cc10(CreateParams0x74* p_createParams);
	void FUN_0046d010(Item0xd0* p_item);
	void FUN_0046cd30();
	void FUN_0046cdc0();
	void FUN_0046cdf0();
	void FUN_0046ce10(CreateParams0x74* p_createParams);
	void FUN_0046cf20();
	void FUN_0046d040(Item0xd0* p_item, GolVec3* p_position);
	GolModelEntity* GetItemEntity(LegoS32 p_index);
	GolModelBase* GetItemModel(LegoS32 p_index);

	undefined4 m_unk0x78;                     // 0x78
	Item0xd0* m_unk0x7c;                      // 0x7c
	GolCamera* m_unk0x80;                     // 0x80
	GolCamera* m_unk0x84;                     // 0x84
	GolRenderDevice::MaterialColor m_unk0x88; // 0x88
	GolRenderDevice::Light m_unk0x8c;         // 0x8c
	undefined4 m_unk0x9c;                     // 0x9c
	undefined4 m_unk0xa0;                     // 0xa0
	LegoFloat m_unk0xa4;                      // 0xa4
	undefined m_unk0xa8[0xb4 - 0xa8];         // 0xa8
	LegoFloat m_unk0xb4;                      // 0xb4
	undefined4 m_unk0xb8;                     // 0xb8
	LegoFloat m_unk0xbc;                      // 0xbc
};

#endif // VIOLETSHOAL0XC0_H
