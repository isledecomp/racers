#ifndef IMAGINARYDRILLFIELDAT0X498_H
#define IMAGINARYDRILLFIELDAT0X498_H

#include "compat.h"
#include "decomp.h"
#include "imaginarydrillfieldat0x420.h"
#include "obscureanchor0x5c.h"
#include "obscureicon0x1a8.h"

class GolFont0xa0;
class GolStringTable;
class UtopianPan0xa4;

// VTABLE: LEGORACERS 0x004b38b0
// SIZE 0x2f0
class ImaginaryDrillFieldAt0x498 : public ObscureIcon0x1a8 {
public:
	// SIZE 0xe0
	class CreateParams0xe0 : public ObscureIcon0x1a8::CreateParams0x84 {
	public:
		GolFont0xa0* m_unk0x84[6];    // 0x84
		UtopianPan0xa4* m_unk0x9c[6]; // 0x9c
		VisualState0x4 m_unk0xb4[6];  // 0xb4
		GolStringTable* m_unk0xcc;    // 0xcc
		undefined4 m_unk0xd0;         // 0xd0
		undefined2 m_unk0xd4;         // 0xd4
		undefined2 m_unk0xd6;         // 0xd6
		undefined4 m_unk0xd8;         // 0xd8
		undefined4 m_unk0xdc;         // 0xdc
	};

	ImaginaryDrillFieldAt0x498();
	void Reset() override;                                                                 // vtable+0x00
	~ImaginaryDrillFieldAt0x498() override;                                                // vtable+0x04
	undefined4 VTable0x08() override;                                                      // vtable+0x08
	void VTable0x10(Rect*) override;                                                       // vtable+0x10
	undefined4 VTable0x34(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4) override; // vtable+0x34
	undefined4 VTable0x38(Rect*, Rect*) override;                                          // vtable+0x38
	void VTable0x40(ImaginaryInterface*) override;                                         // vtable+0x40
	undefined4 FUN_004826c0(CreateParams0xe0* p_createParams, undefined4* p_unk0x08);

	// SYNTHETIC: LEGORACERS 0x00482400
	// ImaginaryDrillFieldAt0x498::`scalar deleting destructor'

private:
	undefined4 m_unk0x1a8;                 // 0x1a8
	undefined m_unk0x1ac[0x1c0 - 0x1ac];   // 0x1ac
	GolFont0xa0* m_unk0x1c0[6];            // 0x1c0
	UtopianPan0xa4* m_unk0x1d8[6];         // 0x1d8
	VisualState0x4 m_unk0x1f0[6];          // 0x1f0
	ObscureAnchor0x5c m_unk0x208;          // 0x208
	ImaginaryDrillFieldAt0x420 m_unk0x264; // 0x264
	undefined4 m_unk0x2dc;                 // 0x2dc
	undefined4 m_unk0x2e0[4];              // 0x2e0
};

#endif // IMAGINARYDRILLFIELDAT0X498_H
