#ifndef EMBERVAULT0X330_H
#define EMBERVAULT0X330_H

#include "compat.h"
#include "decomp.h"
#include "menu/widgets/ivorytalon0x23c.h"
#include "menu/widgets/sablecrest0xc0.h"

// VTABLE: LEGORACERS 0x004b28d0
// SIZE 0x330
class EmberVault0x330 : public IvoryTalon0x23c {
public:
	EmberVault0x330();

	~EmberVault0x330() override;                                                                 // vtable+0x04
	ObscureVantage0x58* VTable0x30(InputEventQueue::Event*, undefined4, undefined4) override;    // vtable+0x30
	ObscureVantage0x58* VTable0x38(Rect*, Rect*) override;                                       // vtable+0x38
	LegoBool32 VTable0x70(CreateParams0xa0*, const ObscureIcon0x1a8::CreateState0x90*) override; // vtable+0x70

	// SYNTHETIC: LEGORACERS 0x004718b0
	// EmberVault0x330::`scalar deleting destructor'

protected:
	void FUN_00471930(CreateParams0xa0* p_createParams);
	void FUN_00471a30();
	LegoBool32 FUN_00471aa0(CreateParams0xa0* p_createParams);

	SableCrest0xc0 m_unk0x23c;           // 0x23c
	undefined m_unk0x2fc[0x330 - 0x2fc]; // 0x2fc
};

#endif // EMBERVAULT0X330_H
