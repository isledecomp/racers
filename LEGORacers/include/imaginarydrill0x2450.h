#ifndef IMAGINARYDRILL0x2450
#define IMAGINARYDRILL0x2450

#include "compat.h"
#include "decomp.h"
#include "imaginarydrillfieldat0x22dc.h"
#include "imaginarydrillfieldat0x420.h"
#include "imaginarydrillfieldat0x498.h"
#include "imaginarytool0x368.h"
#include "obscureanchor0x5c.h"
#include "obscuresigil0xdc.h"

// VTABLE: LEGORACERS 0x004b36d8
// SIZE 0x2450
class ImaginaryDrill0x2450 : public ImaginaryTool0x368 {
public:
	ImaginaryDrill0x2450();

	undefined4 VTable0x18(
		ObscureVantage0x58*,
		OnyxCircularBuffer0x1c::Item*,
		undefined4,
		undefined4
	) override; // vtable+0x18
	undefined4 VTable0x1c(
		ObscureVantage0x58*,
		OnyxCircularBuffer0x1c::Item*,
		undefined4,
		undefined4
	) override;                                                                        // vtable+0x1c
	void VTable0x38(ObscureVantage0x58*) override;                                     // vtable+0x38
	void VTable0x4c() override;                                                        // vtable+0x4c
	void Reset() override;                                                             // vtable+0x54
	~ImaginaryDrill0x2450() override;                                                  // vtable+0x68
	LegoBool32 Destroy() override;                                                     // vtable+0x74
	LegoBool32 VTable0x78(undefined4) override;                                        // vtable+0x78
	void VTable0x84() override;                                                        // vtable+0x84
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00480cb0
	//  ImaginaryDrill0x2450::`scalar deleting destructor'

protected:
	void FUN_0047ff50(MenuToolContext0x4bc8* p_context, undefined4 p_unk0x08);
	void FUN_00480210(MenuToolContext0x4bc8* p_context, undefined4 p_unk0x08);
	void FUN_00480310();
	void FUN_004803a0();
	void FUN_00480e40();

	ObscureAnchor0x5c m_unk0x368;            // 0x0368
	ObscureAnchor0x5c m_unk0x3c4;            // 0x03c4
	ImaginaryDrillFieldAt0x420 m_unk0x420;   // 0x0420
	ImaginaryDrillFieldAt0x498 m_unk0x498;   // 0x0498
	ImaginaryDrillFieldAt0x498 m_unk0x788;   // 0x0788
	ImaginaryDrillFieldAt0x498 m_unk0xa78;   // 0x0a78
	ImaginaryDrillFieldAt0x498 m_unk0xd68;   // 0x0d68
	ImaginaryDrillFieldAt0x498 m_unk0x1058;  // 0x1058
	ImaginaryDrillFieldAt0x498 m_unk0x1348;  // 0x1348
	ImaginaryDrillFieldAt0x498 m_unk0x1638;  // 0x1638
	ImaginaryDrillFieldAt0x498 m_unk0x1928;  // 0x1928
	ImaginaryDrillFieldAt0x498 m_unk0x1c18;  // 0x1c18
	ImaginaryDrillFieldAt0x498 m_unk0x1f08;  // 0x1f08
	ObscureSigil0xdc m_unk0x21f8;            // 0x21f8
	undefined m_unk0x22d4[0x22dc - 0x22d4];  // 0x22d4
	ImaginaryDrillFieldAt0x22dc m_unk0x22dc; // 0x22dc
	OpalHaven0xf4* m_unk0x2438;              // 0x2438
	undefined4 m_unk0x243c;                  // 0x243c
	undefined4 m_unk0x2440;                  // 0x2440
	LegoU32 m_unk0x2444;                     // 0x2444
	LegoU32 m_unk0x2448;                     // 0x2448
	LegoU8 m_unk0x244c;                      // 0x244c
	undefined m_unk0x244d[0x2450 - 0x244d];  // 0x244d
};

#endif // IMAGINARYDRILL0x2450
