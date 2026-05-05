#ifndef IMAGINARYCHISEL0X658_H
#define IMAGINARYCHISEL0X658_H

#include "compat.h"
#include "crimsonpebble0x228.h"
#include "decomp.h"
#include "golstringtable.h"
#include "imaginarytool0x368.h"
#include "obscurevantage0x58.h"
#include "types.h"

class AmberLens0x344;
class BronzeFalcon0xc8770;
class MenuToolContext0x4bc8;
class MenuToolCreateParams0x30;

// VTABLE: LEGORACERS 0x004b2f98
// SIZE 0x658
class ImaginaryChisel0x658 : public ImaginaryTool0x368 {
public:
	// VTABLE: LEGORACERS 0x004b1f60
	// SIZE 0x2d0
	class HelperAt0x368 : public ObscureVantage0x58 {
	public:
		HelperAt0x368();
		~HelperAt0x368() override; // vtable+0x04

		undefined4 VTable0x08() override;                                                      // vtable+0x08
		undefined4 VTable0x2c(void*, undefined4, undefined4) override;                         // vtable+0x2c
		undefined4 VTable0x30(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4) override; // vtable+0x30
		undefined4 VTable0x34(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4) override; // vtable+0x34
		undefined4 VTable0x38(undefined4, undefined4) override;                                // vtable+0x38
		undefined4 VTable0x3c(undefined4) override;                                            // vtable+0x3c

		// SYNTHETIC: LEGORACERS 0x00466a80
		// ImaginaryChisel0x658::HelperAt0x368::`scalar deleting destructor'

		undefined m_unk0x58[0x84 - 0x58];    // 0x058
		CrimsonPebble0x228 m_unk0x84;        // 0x084
		undefined m_unk0x2ac[0x2c8 - 0x2ac]; // 0x2ac
		undefined4 m_unk0x2c8;               // 0x2c8
		undefined4 m_unk0x2cc;               // 0x2cc
	};

	ImaginaryChisel0x658();

	~ImaginaryChisel0x658() override;           // vtable+0x68
	void VTable0x74() override;                 // vtable+0x74
	LegoBool32 VTable0x78(undefined4) override; // vtable+0x78
	void VTable0x84() override;                 // vtable+0x84
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*,
						  MenuToolCreateParams0x30*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00479710
	// ImaginaryChisel0x658::`scalar deleting destructor'

protected:
	HelperAt0x368 m_unk0x368;        // 0x368
	GolStringTable m_unk0x638;       // 0x638
	BronzeFalcon0xc8770* m_unk0x64c; // 0x64c
	AmberLens0x344* m_unk0x650;      // 0x650
	undefined4 m_unk0x654;           // 0x654
};

#endif // IMAGINARYCHISEL0X658_H
