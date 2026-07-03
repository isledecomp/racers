#ifndef MENUIMAGE_H
#define MENUIMAGE_H

#include "compat.h"
#include "decomp.h"
#include "menu/widgets/menustaticwidget.h"

class GolImage;

// VTABLE: LEGORACERS 0x004b26bc
// SIZE 0x5c
class MenuImage : public MenuStaticWidget {
public:
	// SIZE 0x3c
	class CreateParams : public MenuWidget::CreateParams {
	public:
		GolImage* m_image; // 0x38
	};

	MenuImage();

	void Reset() override;                       // vtable+0x00
	~MenuImage() override;                       // vtable+0x04
	MenuWidget* DrawSelf(Rect*, Rect*) override; // vtable+0x38
	LegoBool32 Create(CreateParams* p_createParams);
	void SetImage(GolImage* p_image) { m_image = p_image; }

	// SYNTHETIC: LEGORACERS 0x0046f0d0
	// MenuImage::`scalar deleting destructor'

protected:
	GolImage* m_image; // 0x58
};

#endif // MENUIMAGE_H
