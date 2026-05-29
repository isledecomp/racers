#ifndef OBSCUREGLYPH0X21C_H
#define OBSCUREGLYPH0X21C_H

#include "compat.h"
#include "decomp.h"
#include "menu/widgets/obscureanchor0x5c.h"
#include "menu/widgets/obscureicon0x1a8.h"

// VTABLE: LEGORACERS 0x004b1e80
// SIZE 0x21c
class ObscureGlyph0x21c : public ObscureIcon0x1a8 {
public:
	// SIZE 0x9c
	class CreateParams0x9c : public ObscureIcon0x1a8::CreateParams0x84 {
	public:
		UtopianPan0xa4* m_images[6]; // 0x84
	};

	ObscureGlyph0x21c();
	void Reset() override;                                 // vtable+0x00
	~ObscureGlyph0x21c() override;                         // vtable+0x04
	LegoBool32 VTable0x08() override;                      // vtable+0x08
	ObscureVantage0x58* VTable0x38(Rect*, Rect*) override; // vtable+0x38

	LegoBool32 FUN_004663d0(CreateParams0x9c* p_createParams, const ObscureIcon0x1a8::CreateState0x90* p_createState);

	// SYNTHETIC: LEGORACERS 0x004662c0
	// ObscureGlyph0x21c::`scalar deleting destructor'

protected:
	LegoBool32 FUN_00466370(ObscureAnchor0x5c* p_unk0x04, CreateParams0x9c* p_createParams);

	UtopianPan0xa4* m_unk0x1a8[6]; // 0x1a8
	ObscureAnchor0x5c m_unk0x1c0;  // 0x1c0
};

#endif // OBSCUREGLYPH0X21C_H
