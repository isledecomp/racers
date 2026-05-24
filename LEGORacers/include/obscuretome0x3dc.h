#ifndef OBSCURETOME0X3FC_H
#define OBSCURETOME0X3FC_H

#include "compat.h"
#include "decomp.h"
#include "obscureanchor0x5c.h"
#include "obscureanthem0x58.h"
#include "obscurezebra0xa4.h"
#include "rectangle.h"

class UtopianPan0xa4;

// VTABLE: LEGORACERS 0x004b267c
// SIZE 0x3fc
class ObscureTome0x3fc : public ObscureAnthem0x58 {
public:
	// SIZE 0x60
	class CreateParams0x60 : public ObscureVantage0x58::CreateParams0x30 {
	public:
		undefined m_unk0x30[0x38 - 0x30]; // 0x30
		UtopianPan0xa4* m_images[8];      // 0x38
		VisualState0x4 m_unk0x58;         // 0x58
		LegoBool32 m_unk0x5c;             // 0x5c
	};

	ObscureTome0x3fc();
	~ObscureTome0x3fc() override;    // vtable+0x04
	void VTable0x10(Rect*) override; // vtable+0x10

	// SYNTHETIC: LEGORACERS 0x0046ec30
	// ObscureTome0x3fc::`scalar deleting destructor'

	LegoBool32 FUN_0046ecd0(CreateParams0x60* p_createParams);
	void FUN_0046f050(VisualState0x4* p_visualState);

	// SIZE 0x38
	class CreateParamsPrefix0x38 : public ObscureVantage0x58::CreateParams0x30 {
	public:
		undefined m_unk0x30[0x38 - 0x30]; // 0x30
	};

private:
	LegoBool32 FUN_0046ed30(CreateParams0x60* p_createParams);
	LegoBool32 FUN_0046edf0(CreateParams0x60* p_createParams);

protected:
	ObscureZebra0xa4 m_unk0x58;     // 0x058
	ObscureAnchor0x5c m_unk0xfc[8]; // 0x0fc
	UtopianPan0xa4* m_images[8];    // 0x3dc
};

#endif // OBSCURETOME0X3FC_H
