#ifndef IMAGINARYLEVER0X1D7C
#define IMAGINARYLEVER0X1D7C

#include "compat.h"
#include "decomp.h"
#include "imaginarydrillfieldat0x420.h"
#include "imaginarydrillfieldat0x498.h"
#include "imaginarytool0x368.h"
#include "obscureanchor0x5c.h"

class CitrineGrove0x1f4c;

// VTABLE: LEGORACERS 0x004b3d1c
// SIZE 0x1d7c
class ImaginaryLever0x1d7c : public ImaginaryTool0x368 {
public:
	ImaginaryLever0x1d7c();

	void VTable0x38(ObscureVantage0x58*) override;                                     // vtable+0x38
	void VTable0x4c() override;                                                        // vtable+0x4c
	~ImaginaryLever0x1d7c() override;                                                  // vtable+0x68
	LegoBool32 Destroy() override;                                                     // vtable+0x74
	LegoBool32 VTable0x78(undefined4) override;                                        // vtable+0x78
	void VTable0x84() override;                                                        // vtable+0x84
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00486c80
	// ImaginaryLever0x1d7c::`scalar deleting destructor'

protected:
	void FUN_00486e40(CitrineGrove0x1f4c* p_unk0x04);

	LegoS32 m_unk0x368;                     // 0x0368
	LegoU32 m_unk0x36c;                     // 0x036c
	LegoS32 m_unk0x370;                     // 0x0370
	LegoBool32 m_unk0x374;                  // 0x0374
	LegoBool32 m_unk0x378;                  // 0x0378
	ObscureAnchor0x5c m_unk0x37c;           // 0x037c
	ObscureAnchor0x5c m_unk0x3d8;           // 0x03d8
	ObscureAnchor0x5c m_unk0x434;           // 0x0434
	ImaginaryDrillFieldAt0x420 m_unk0x490;  // 0x0490
	ImaginaryDrillFieldAt0x420 m_unk0x508;  // 0x0508
	ImaginaryDrillFieldAt0x420 m_unk0x580;  // 0x0580
	ImaginaryDrillFieldAt0x498 m_unk0x5f8;  // 0x05f8
	ImaginaryDrillFieldAt0x498 m_unk0x8e8;  // 0x08e8
	ImaginaryDrillFieldAt0x498 m_unk0xbd8;  // 0x0bd8
	ImaginaryDrillFieldAt0x498 m_unk0xec8;  // 0x0ec8
	ImaginaryDrillFieldAt0x498 m_unk0x11b8; // 0x11b8
	ImaginaryDrillFieldAt0x498 m_unk0x14a8; // 0x14a8
	ImaginaryDrillFieldAt0x498 m_unk0x1798; // 0x1798
	ImaginaryDrillFieldAt0x498 m_unk0x1a88; // 0x1a88
	undefined4 m_unk0x1d78;                 // 0x1d78
};

#endif // IMAGINARYLEVER0X1D7C
