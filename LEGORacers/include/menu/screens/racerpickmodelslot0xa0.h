#ifndef RACERPICKMODELSLOT0XA0_H
#define RACERPICKMODELSLOT0XA0_H

#include "compat.h"
#include "decomp.h"
#include "golmath.h"
#include "menu/widgets/obscurelink0x1c.h"

class GolWorldEntity;

// VTABLE: LEGORACERS 0x004b3db4
// SIZE 0xa0
class RacerPickModelSlot0xa0 : public ObscureLink0x1c {
public:
	// SIZE 0x48
	class CreateParams0x48 : public ObscureLink0x1c::CreateParams0x0c {
	public:
		undefined4 m_unk0x0c[8]; // 0x0c
		GolVec3 m_unk0x2c;       // 0x2c
		undefined4 m_unk0x38;    // 0x38
		undefined4 m_unk0x3c;    // 0x3c
		LegoFloat m_unk0x40;     // 0x40
		LegoBool32 m_unk0x44;    // 0x44
	};

	RacerPickModelSlot0xa0();

	void Reset() override;                      // vtable+0x00
	~RacerPickModelSlot0xa0() override;         // vtable+0x04
	LegoBool32 VTable0x0c() override;           // vtable+0x0c
	LegoBool32 VTable0x10(undefined4) override; // vtable+0x10

	void FUN_00487600(GolWorldEntity* p_entity);

	// SYNTHETIC: LEGORACERS 0x00487500
	// RacerPickModelSlot0xa0::`scalar deleting destructor'

private:
	CreateParams0x48 m_unk0x1c; // 0x1c
	GolWorldEntity* m_unk0x64;  // 0x64
	GolWorldEntity* m_unk0x68;  // 0x68
	GolWorldEntity* m_unk0x6c;  // 0x6c
	undefined4 m_unk0x70;       // 0x70
	undefined4 m_unk0x74;       // 0x74
	LegoFloat m_unk0x78;        // 0x78
	undefined4 m_unk0x7c;       // 0x7c
	undefined4 m_unk0x80;       // 0x80
	undefined4 m_unk0x84;       // 0x84
	GolVec3 m_unk0x88;          // 0x88
	LegoS32 m_unk0x94;          // 0x94
	LegoS32 m_unk0x98;          // 0x98
	LegoBool32 m_unk0x9c;       // 0x9c
};

#endif // RACERPICKMODELSLOT0XA0_H
