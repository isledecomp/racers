#ifndef OBSCUREZEBRA0XA4
#define OBSCUREZEBRA0XA4

#include "compat.h"
#include "decomp.h"
#include "menu/widgets/menuwidget.h"
#include "render/golrenderdevice.h"

// VTABLE: LEGORACERS 0x004b29f4
// SIZE 0xa4
class MenuTriangle : public MenuWidget {
public:
	MenuTriangle();
	void Reset() override;                         // vtable+0x00
	~MenuTriangle() override;                      // vtable+0x04
	void VTable0x14(VisualStateColor*) override;   // vtable+0x14
	MenuWidget* VTable0x38(Rect*, Rect*) override; // vtable+0x38

	LegoBool32 FUN_004735a0(CreateParams* p_createParams);
	void SetAlphaOverride(LegoU32 p_alphaOverride) { m_alphaOverride = p_alphaOverride; }

	// SYNTHETIC: LEGORACERS 0x004734f0
	// MenuTriangle::`scalar deleting destructor'

protected:
	GolRenderDevice::TexturedVertex m_vertices[3]; // 0x58
	LegoU32 m_alphaOverride;                       // 0xa0
};

#endif // OBSCUREZEBRA0XA4
