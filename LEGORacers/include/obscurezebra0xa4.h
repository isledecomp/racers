#ifndef OBSCUREZEBRA0XA4
#define OBSCUREZEBRA0XA4

#include "compat.h"
#include "decomp.h"
#include "obscurevantage0x58.h"
#include "whitefalcon0x140.h"

// VTABLE: LEGORACERS 0x004b29f4
// SIZE 0xa4
class ObscureZebra0xa4 : public ObscureVantage0x58 {
public:
	ObscureZebra0xa4();
	void Reset() override;                        // vtable+0x00
	~ObscureZebra0xa4() override;                 // vtable+0x04
	void VTable0x14(VisualState0x4*) override;    // vtable+0x14
	undefined4 VTable0x38(Rect*, Rect*) override; // vtable+0x38

	LegoBool32 FUN_004735a0(CreateParams0x30* p_createParams);
	void SetAlphaOverride(LegoU32 p_alphaOverride) { m_alphaOverride = p_alphaOverride; }

	// SYNTHETIC: LEGORACERS 0x004734f0
	// ObscureZebra0xa4::`scalar deleting destructor'

protected:
	WhiteFalcon0x140::TexturedVertex m_vertices[3]; // 0x58
	LegoU32 m_alphaOverride;                        // 0xa0
};

#endif // OBSCUREZEBRA0XA4
