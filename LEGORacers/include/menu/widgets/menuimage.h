#ifndef OBSCUREANCHOR0X5C
#define OBSCUREANCHOR0X5C

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
	void SetUnk0x58(GolImage* p_unk0x58) { m_unk0x58 = p_unk0x58; }

	// SYNTHETIC: LEGORACERS 0x0046f0d0
	// MenuImage::`scalar deleting destructor'

protected:
	GolImage* m_unk0x58; // 0x58
};

#endif // OBSCUREANCHOR0X5C
