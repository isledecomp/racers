#ifndef OBSCUREGLYPH0X21C_H
#define OBSCUREGLYPH0X21C_H

#include "compat.h"
#include "decomp.h"
#include "obscureanchor0x5c.h"
#include "obscureicon0x1a8.h"

// VTABLE: LEGORACERS 0x004b1e80
// SIZE 0x21c
class ObscureGlyph0x21c : public ObscureIcon0x1a8 {
public:
	ObscureGlyph0x21c();
	void Reset() override;                        // vtable+0x00
	~ObscureGlyph0x21c() override;                // vtable+0x04
	LegoBool32 VTable0x08() override;             // vtable+0x08
	undefined4 VTable0x38(Rect*, Rect*) override; // vtable+0x38

	// SYNTHETIC: LEGORACERS 0x004662c0
	// ObscureGlyph0x21c::`scalar deleting destructor'

protected:
	undefined4 m_unk0x1a8[6];     // 0x1a8
	ObscureAnchor0x5c m_unk0x1c0; // 0x1c0
};

#endif // OBSCUREGLYPH0X21C_H
