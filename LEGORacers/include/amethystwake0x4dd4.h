#ifndef AMETHYSTWAKE0X4DD4_H
#define AMETHYSTWAKE0X4DD4_H

#include "cactusinterface0x4.h"
#include "compat.h"
#include "decomp.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004b05a4
// SIZE 0x4dd4
class AmethystWake0x4dd4 : public CactusInterface0x4 {
public:
	AmethystWake0x4dd4();
	void VTable0x00() override;                       // vtable+0x00
	void VTable0x1c(undefined4) override;             // vtable+0x1c
	void VTable0x24(undefined4, undefined4) override; // vtable+0x24
	void VTable0x28() override;                       // vtable+0x28
	void VTable0x2c() override;                       // vtable+0x2c
	virtual ~AmethystWake0x4dd4();                    // vtable+0x30

	// SYNTHETIC: LEGORACERS 0x0042c7c0
	// AmethystWake0x4dd4::`scalar deleting destructor'

	static void FUN_0042b1e0(LegoBool32* p_unk0x00);

	void FUN_0042cb90(LegoBool32* p_unk0x00);
	LegoS32 FUN_0042ccc0();
	void FUN_0042d510();

private:
	undefined4* m_unk0x04;                  // 0x04
	undefined m_unk0x08[0x4cb4 - 0x08];     // 0x08
	undefined4 m_unk0x4cb4;                 // 0x4cb4
	undefined4 m_unk0x4cb8;                 // 0x4cb8
	undefined4 m_unk0x4cbc;                 // 0x4cbc
	undefined4 m_unk0x4cc0;                 // 0x4cc0
	LegoU8 m_unk0x4cc4;                     // 0x4cc4
	undefined m_unk0x4cc5[0x4dd0 - 0x4cc5]; // 0x4cc5
	undefined4 m_unk0x4dd0;                 // 0x4dd0
};

#endif // AMETHYSTWAKE0X4DD4_H
