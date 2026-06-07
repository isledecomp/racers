#ifndef MENUFRAME_H
#define MENUFRAME_H

#include "compat.h"
#include "decomp.h"
#include "menu/widgets/menuimage.h"
#include "menu/widgets/menustaticwidget.h"
#include "menu/widgets/menutriangle.h"
#include "render/rectangle.h"

class UtopianPan0xa4;

// VTABLE: LEGORACERS 0x004b267c
// SIZE 0x3fc
class MenuFrame : public MenuStaticWidget {
public:
	// SIZE 0x60
	class CreateParams : public MenuWidget::CreateParams {
	public:
		UtopianPan0xa4* m_images[8]; // 0x38
		VisualStateColor m_unk0x58;  // 0x58
		LegoBool32 m_unk0x5c;        // 0x5c
	};

	MenuFrame();
	~MenuFrame() override;           // vtable+0x04
	void VTable0x10(Rect*) override; // vtable+0x10

	// SYNTHETIC: LEGORACERS 0x0046ec30
	// MenuFrame::`scalar deleting destructor'

	LegoBool32 FUN_0046ecd0(CreateParams* p_createParams);
	void FUN_0046f050(VisualStateColor* p_visualState);
	MenuTriangle* GetUnk0x58() { return &m_unk0x58; }

	// SIZE 0x38
	class CreateParamsPrefix : public MenuWidget::CreateParams {
	public:
	};

private:
	LegoBool32 FUN_0046ed30(CreateParams* p_createParams);
	LegoBool32 FUN_0046edf0(CreateParams* p_createParams);

protected:
	MenuTriangle m_unk0x58;      // 0x058
	MenuImage m_unk0xfc[8];      // 0x0fc
	UtopianPan0xa4* m_images[8]; // 0x3dc
};

#endif // MENUFRAME_H
