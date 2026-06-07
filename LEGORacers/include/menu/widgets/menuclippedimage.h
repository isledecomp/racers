#ifndef MENUCLIPPEDIMAGE_H
#define MENUCLIPPEDIMAGE_H

#include "compat.h"
#include "decomp.h"
#include "menu/widgets/menuimage.h"
#include "render/rectangle.h"

// VTABLE: LEGORACERS 0x004b26fc
// SIZE 0x7c
class MenuClippedImage : public MenuImage {
public:
	MenuClippedImage();

	~MenuClippedImage() override;                  // vtable+0x04
	MenuWidget* VTable0x38(Rect*, Rect*) override; // vtable+0x38

	// SYNTHETIC: LEGORACERS 0x0046f250
	// MenuClippedImage::`scalar deleting destructor'

protected:
	void FUN_0046f2c0(Rect* p_rect);

	Rect m_unk0x5c; // 0x5c
	Rect m_unk0x6c; // 0x6c
};

#endif // MENUCLIPPEDIMAGE_H
