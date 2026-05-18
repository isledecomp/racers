#ifndef IMAGINARYDRILLFIELDAT0X22DC_H
#define IMAGINARYDRILLFIELDAT0X22DC_H

#include "cmbmodelpart0x34.h"
#include "decomp.h"
#include "obscurelink0x1c.h"
#include "opalhaven0xf4.h"
#include "turquoiseglowcolor.h"

class BronzeFalcon0xc8770;
class GolExport;
class ObscureSigil0xdc;
class TanzaniteWisp0x88;

// VTABLE: LEGORACERS 0x004b33c8
// SIZE 0x15c
class ImaginaryDrillFieldAt0x22dc : public ObscureLink0x1c {
public:
	// SIZE 0x1c
	struct CreateParams {
		GolExport* m_golExport;          // 0x00
		BronzeFalcon0xc8770* m_renderer; // 0x04
		ObscureSigil0xdc* m_unk0x08;     // 0x08
		TanzaniteWisp0x88* m_unk0x0c;    // 0x0c
		LegoFloat m_unk0x10;             // 0x10
		LegoFloat m_unk0x14;             // 0x14
		LegoFloat m_unk0x18;             // 0x18
	};

	ImaginaryDrillFieldAt0x22dc();
	void Reset() override;                   // vtable+0x00
	~ImaginaryDrillFieldAt0x22dc() override; // vtable+0x04

	OpalHaven0xf4* GetUnk0x1c() { return &m_unk0x1c; }
	CmbModelPart0x34* GetUnk0x118() { return &m_unk0x118; }
	void FUN_0047e0a0(CreateParams* p_unk0x04);
	void FUN_0047e210(TurquoiseGlowColor* p_color);

	// SYNTHETIC: LEGORACERS 0x0047dee0
	// ImaginaryDrillFieldAt0x22dc::`scalar deleting destructor'

private:
	OpalHaven0xf4 m_unk0x1c;             // 0x01c
	undefined m_unk0x110[0x118 - 0x110]; // 0x110
	CmbModelPart0x34 m_unk0x118;         // 0x118
	undefined m_unk0x14c[0x15c - 0x14c]; // 0x14c
};

#endif // IMAGINARYDRILLFIELDAT0X22DC_H
