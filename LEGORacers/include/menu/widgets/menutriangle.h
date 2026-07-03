#ifndef MENUTRIANGLE_H
#define MENUTRIANGLE_H

#include "compat.h"
#include "decomp.h"
#include "menu/widgets/menuwidget.h"
#include "render/golrenderdevice.h"

// VTABLE: LEGORACERS 0x004b29f4
// SIZE 0xa4
class MenuTriangle : public MenuWidget {
public:
	MenuTriangle();
	void Reset() override;                       // vtable+0x00
	~MenuTriangle() override;                    // vtable+0x04
	void SetColor(VisualStateColor*) override;   // vtable+0x14
	MenuWidget* DrawSelf(Rect*, Rect*) override; // vtable+0x38

	LegoBool32 Create(CreateParams* p_createParams);
	void SetAlphaOverride(LegoU32 p_alphaOverride) { m_alphaOverride = p_alphaOverride; }

	// SYNTHETIC: LEGORACERS 0x004734f0
	// MenuTriangle::`scalar deleting destructor'

protected:
	GolRenderDevice::TexturedVertex m_vertices[3]; // 0x58
	LegoU32 m_alphaOverride;                       // 0xa0
};

#endif // MENUTRIANGLE_H
