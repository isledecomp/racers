#ifndef RACERMODELSLOT_H
#define RACERMODELSLOT_H

#include "compat.h"
#include "decomp.h"
#include "golmath.h"
#include "menu/widgets/menusceneelement.h"

class GolWorldEntity;

// VTABLE: LEGORACERS 0x004b3db4
// SIZE 0xa0
class RacerModelSlot : public MenuSceneElement {
public:
	// SIZE 0x48
	class CreateParams : public MenuSceneElement::CreateParams {
	public:
		undefined4 m_unk0x0c[8]; // 0x0c
		GolVec3 m_unk0x2c;       // 0x2c
		undefined4 m_unk0x38;    // 0x38
		undefined4 m_unk0x3c;    // 0x3c
		LegoFloat m_unk0x40;     // 0x40
		LegoBool32 m_unk0x44;    // 0x44
	};

	RacerModelSlot();

	void Reset() override;                             // vtable+0x00
	~RacerModelSlot() override;                        // vtable+0x04
	LegoBool32 VTable0x0c() override;                  // vtable+0x0c
	LegoBool32 VTable0x10(LegoU32 p_elapsed) override; // vtable+0x10

	LegoBool32 FUN_004875d0(CreateParams* p_createParams);
	void FUN_00487600(GolWorldEntity* p_entity);
	GolWorldEntity* GetUnk0x68() const { return m_unk0x68; }

	// SYNTHETIC: LEGORACERS 0x00487500
	// RacerModelSlot::`scalar deleting destructor'

private:
	LegoBool32 FUN_00487630(LegoU32 p_elapsed);
	LegoBool32 FUN_00487690(LegoU32 p_elapsed);
	LegoBool32 FUN_004876f0(LegoS32 p_elapsed);

	CreateParams m_unk0x1c;    // 0x1c
	GolWorldEntity* m_unk0x64; // 0x64
	GolWorldEntity* m_unk0x68; // 0x68
	GolWorldEntity* m_unk0x6c; // 0x6c
	GolVec3 m_unk0x70;         // 0x70
	undefined4 m_unk0x7c;      // 0x7c
	undefined4 m_unk0x80;      // 0x80
	undefined4 m_unk0x84;      // 0x84
	GolVec3 m_unk0x88;         // 0x88
	LegoU32 m_unk0x94;         // 0x94
	LegoU32 m_unk0x98;         // 0x98
	LegoBool32 m_unk0x9c;      // 0x9c
};

#endif // RACERMODELSLOT_H
