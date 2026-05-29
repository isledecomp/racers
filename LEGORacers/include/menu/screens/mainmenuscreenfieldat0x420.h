#ifndef MAINMENUSCREENFIELDAT0X420_H
#define MAINMENUSCREENFIELDAT0X420_H

#include "compat.h"
#include "decomp.h"
#include "golstring.h"
#include "menu/style/ceruleanemperor0x4c.h"
#include "menu/widgets/obscureanthem0x58.h"

class GolFont0xa0;
class GolStringTable;

// VTABLE: LEGORACERS 0x004b273c
// SIZE 0x78
class MainMenuScreenFieldAt0x420 : public ObscureAnthem0x58 {
public:
	// SIZE 0x48
	class CreateParams0x48 : public ObscureVantage0x58::CreateParams0x38 {
	public:
		GolStringTable* m_unk0x38; // 0x38
		GolFont0xa0* m_unk0x3c;    // 0x3c
		undefined2 m_unk0x40;      // 0x40
		undefined m_unk0x42[2];    // 0x42
		undefined4 m_unk0x44;      // 0x44
	};

	MainMenuScreenFieldAt0x420();
	void Reset() override;                           // vtable+0x00
	~MainMenuScreenFieldAt0x420() override;          // vtable+0x04
	undefined4 VTable0x38(Rect*, Rect*) override;    // vtable+0x38
	virtual void VTable0x40(GolString*, undefined4); // vtable+0x40
	virtual void VTable0x44(undefined2, undefined4); // vtable+0x44
	LegoBool32 FUN_0046f520(CreateParams0x48* p_createParams, CeruleanEmperor0x4c::Entry0x14* p_unk0x08);
	void FUN_0046f6b0(LegoS32 p_rightMargin);
	void SetUnk0x60(GolFont0xa0* p_unk0x60) { m_unk0x60 = p_unk0x60; }

	// SYNTHETIC: LEGORACERS 0x0046f470
	// MainMenuScreenFieldAt0x420::`scalar deleting destructor'

protected:
	CeruleanEmperor0x4c::Entry0x14* m_unk0x58; // 0x58
	GolStringTable* m_unk0x5c;                 // 0x5c
	GolFont0xa0* m_unk0x60;                    // 0x60
	GolString m_unk0x64;                       // 0x64
	LegoS32 m_unk0x70;                         // 0x70
	LegoBool32 m_unk0x74;                      // 0x74
};

#endif // MAINMENUSCREENFIELDAT0X420_H
