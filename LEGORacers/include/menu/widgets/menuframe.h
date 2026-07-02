#ifndef MENUFRAME_H
#define MENUFRAME_H

#include "compat.h"
#include "decomp.h"
#include "menu/widgets/menuimage.h"
#include "menu/widgets/menustaticwidget.h"
#include "menu/widgets/menutriangle.h"
#include "render/rectangle.h"

class GolImage;

// VTABLE: LEGORACERS 0x004b267c
// SIZE 0x3fc
class MenuFrame : public MenuStaticWidget {
public:
	// SIZE 0x60
	class CreateParams : public MenuWidget::CreateParams {
	public:
		GolImage* m_images[8];        // 0x38
		VisualStateColor m_fillColor; // 0x58
		LegoBool32 m_hasFillColor;    // 0x5c
	};

	MenuFrame();
	~MenuFrame() override;        // vtable+0x04
	void SetRect(Rect*) override; // vtable+0x10

	// SYNTHETIC: LEGORACERS 0x0046ec30
	// MenuFrame::`scalar deleting destructor'

	LegoBool32 Create(CreateParams* p_createParams);
	void SetBorderColors(VisualStateColor* p_visualState);
	MenuTriangle* GetFill() { return &m_fill; }

	// SIZE 0x38
	class CreateParamsPrefix : public MenuWidget::CreateParams {
	public:
	};

private:
	LegoBool32 CreateFill(CreateParams* p_createParams);
	LegoBool32 CreateBorder(CreateParams* p_createParams);

protected:
	MenuTriangle m_fill;         // 0x058
	MenuImage m_borderImages[8]; // 0x0fc
	GolImage* m_images[8];       // 0x3dc
};

#endif // MENUFRAME_H
