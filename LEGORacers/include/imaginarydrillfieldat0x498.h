#ifndef IMAGINARYDRILLFIELDAT0X498_H
#define IMAGINARYDRILLFIELDAT0X498_H

#include "compat.h"
#include "decomp.h"
#include "imaginarydrillfieldat0x420.h"
#include "obscureanchor0x5c.h"
#include "obscureicon0x1a8.h"

// VTABLE: LEGORACERS 0x004b38b0
// SIZE 0x2f0
class ImaginaryDrillFieldAt0x498 : public ObscureIcon0x1a8 {
public:
	ImaginaryDrillFieldAt0x498();
	void Reset() override;                                                                 // vtable+0x00
	~ImaginaryDrillFieldAt0x498() override;                                                // vtable+0x04
	undefined4 VTable0x08() override;                                                      // vtable+0x08
	void VTable0x10(Rect*) override;                                                       // vtable+0x10
	undefined4 VTable0x34(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4) override; // vtable+0x34
	undefined4 VTable0x38(Rect*, Rect*) override;                                          // vtable+0x38
	void VTable0x40(ImaginaryInterface*) override;                                         // vtable+0x40

	// SYNTHETIC: LEGORACERS 0x00482400
	// ImaginaryDrillFieldAt0x498::`scalar deleting destructor'

private:
	undefined4 m_unk0x1a8;                 // 0x1a8
	undefined m_unk0x1ac[0x1c0 - 0x1ac];   // 0x1ac
	undefined4 m_unk0x1c0[0x12];           // 0x1c0
	ObscureAnchor0x5c m_unk0x208;          // 0x208
	ImaginaryDrillFieldAt0x420 m_unk0x264; // 0x264
	undefined4 m_unk0x2dc;                 // 0x2dc
	undefined4 m_unk0x2e0[4];              // 0x2e0
};

#endif // IMAGINARYDRILLFIELDAT0X498_H
