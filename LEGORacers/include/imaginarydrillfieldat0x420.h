#ifndef IMAGINARYDRILLFIELDAT0X420_H
#define IMAGINARYDRILLFIELDAT0X420_H

#include "compat.h"
#include "decomp.h"
#include "golstring.h"
#include "obscureanthem0x58.h"

class GolFont0xa0;

// VTABLE: LEGORACERS 0x004b273c
// SIZE 0x78
class ImaginaryDrillFieldAt0x420 : public ObscureAnthem0x58 {
public:
	ImaginaryDrillFieldAt0x420();
	void Reset() override;                           // vtable+0x00
	~ImaginaryDrillFieldAt0x420() override;          // vtable+0x04
	undefined4 VTable0x38(Rect*, Rect*) override;    // vtable+0x38
	virtual void VTable0x40(undefined4, undefined4); // vtable+0x40
	virtual void VTable0x44(undefined4, undefined4); // vtable+0x44
	void SetUnk0x60(GolFont0xa0* p_unk0x60) { m_unk0x60 = p_unk0x60; }

	// SYNTHETIC: LEGORACERS 0x0046f470
	// ImaginaryDrillFieldAt0x420::`scalar deleting destructor'

private:
	undefined4 m_unk0x58;   // 0x58
	undefined4 m_unk0x5c;   // 0x5c
	GolFont0xa0* m_unk0x60; // 0x60
	GolString m_unk0x64;    // 0x64
	undefined4 m_unk0x70;   // 0x70
	undefined4 m_unk0x74;   // 0x74
};

#endif // IMAGINARYDRILLFIELDAT0X420_H
