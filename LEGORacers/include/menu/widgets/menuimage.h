#ifndef OBSCUREANCHOR0X5C
#define OBSCUREANCHOR0X5C

#include "compat.h"
#include "decomp.h"
#include "menu/widgets/menustaticwidget.h"

class UtopianPan0xa4;

// VTABLE: LEGORACERS 0x004b26bc
// SIZE 0x5c
class MenuImage : public MenuStaticWidget {
public:
	// SIZE 0x3c
	class CreateParams : public MenuWidget::CreateParams {
	public:
		UtopianPan0xa4* m_unk0x38; // 0x38
	};

	MenuImage();

	void Reset() override;                         // vtable+0x00
	~MenuImage() override;                         // vtable+0x04
	MenuWidget* VTable0x38(Rect*, Rect*) override; // vtable+0x38
	LegoBool32 FUN_0046f150(CreateParams* p_createParams);
	void SetUnk0x58(UtopianPan0xa4* p_unk0x58) { m_unk0x58 = p_unk0x58; }

	// SYNTHETIC: LEGORACERS 0x0046f0d0
	// MenuImage::`scalar deleting destructor'

protected:
	UtopianPan0xa4* m_unk0x58; // 0x58
};

#endif // OBSCUREANCHOR0X5C
