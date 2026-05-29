#ifndef OBSCURERUNE0X4D8
#define OBSCURERUNE0X4D8

#include "compat.h"
#include "decomp.h"
#include "menu/widgets/obscuresigil0xdc.h"
#include "menu/widgets/obscuretome0x3fc.h"

// VTABLE: LEGORACERS 0x004b1e40
// SIZE 0x4d8
class ObscureRune0x4d8 : public ObscureSigil0xdc {
public:
	// SIZE 0x88
	class CreateParams0x88 : public ObscureSigil0xdc::CreateParams0x84 {
	public:
		ObscureTome0x3fc::CreateParams0x60* m_unk0x84; // 0x84
	};

	ObscureRune0x4d8();
	~ObscureRune0x4d8() override; // vtable+0x04

	LegoBool32 FUN_004661f0(CreateParams0x88* p_createParams, undefined4 p_unk0x08);

	// SYNTHETIC: LEGORACERS 0x00466100
	// ObscureRune0x4d8::`scalar deleting destructor'

protected:
	LegoBool32 FUN_00466180(CreateParams0x88* p_createParams);

	ObscureTome0x3fc m_unk0xdc; // 0x0dc
};

#endif // OBSCURERUNE0X4D8
