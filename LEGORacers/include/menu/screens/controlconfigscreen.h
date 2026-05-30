#ifndef CONTROLCONFIGSCREEN_H
#define CONTROLCONFIGSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/imaginarytool0x368.h"
#include "menu/screens/mainmenuscreenfieldat0x420.h"
#include "menu/screens/mainmenuscreenfieldat0x498.h"
#include "menu/widgets/obscureanchor0x5c.h"
#include "menu/widgets/obscurebanner0x5ec.h"
#include "menu/widgets/obscurecarousel0x78.h"

class InputDevice;

// VTABLE: LEGORACERS 0x004b3160
// SIZE 0x3360
class ControlConfigScreen : public ImaginaryTool0x368 {
public:
	// SIZE 0xc
	class FieldAt0x32f4 {
	public:
		FieldAt0x32f4();
		~FieldAt0x32f4();

	private:
		undefined4 m_unk0x00; // 0x00
		undefined2 m_unk0x04; // 0x04
		undefined2 m_unk0x06; // 0x06
		undefined2 m_unk0x08; // 0x08
	};

	ControlConfigScreen();

	undefined4 VTable0x18(ObscureVantage0x58*, InputEventQueue::Event*, undefined4,
						  undefined4) override; // vtable+0x18
	undefined4 VTable0x1c(ObscureVantage0x58*, InputEventQueue::Event*, undefined4,
						  undefined4) override;                                        // vtable+0x1c
	void VTable0x34(ObscureIcon0x1a8*) override;                                       // vtable+0x34
	void VTable0x38(ObscureVantage0x58*) override;                                     // vtable+0x38
	void VTable0x44(ObscureVantage0x58*) override;                                     // vtable+0x44
	void VTable0x4c() override;                                                        // vtable+0x4c
	void Reset() override;                                                             // vtable+0x54
	~ControlConfigScreen() override;                                                   // vtable+0x68
	LegoBool32 VTable0x78(undefined4) override;                                        // vtable+0x78
	void VTable0x84() override;                                                        // vtable+0x84
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x0047a690
	// ControlConfigScreen::`scalar deleting destructor'

protected:
	void FUN_0047a930();
	void FUN_0047adb0();

	InputDevice* m_unk0x368[5];                // 0x0368
	LegoS32 m_unk0x37c[5];                     // 0x037c
	undefined4 m_unk0x390;                     // 0x0390
	undefined2* m_unk0x394;                    // 0x0394
	undefined2* m_unk0x398;                    // 0x0398
	LegoU32 m_unk0x39c;                        // 0x039c
	LegoS32 m_unk0x3a0;                        // 0x03a0
	LegoU32 m_unk0x3a4;                        // 0x03a4
	ObscureAnchor0x5c m_unk0x3a8;              // 0x03a8
	MainMenuScreenFieldAt0x420 m_unk0x404;     // 0x0404
	MainMenuScreenFieldAt0x498 m_unk0x47c;     // 0x047c
	undefined4 m_unk0x76c[4];                  // 0x076c
	LegoU16 m_unk0x77c;                        // 0x077c
	undefined m_unk0x77e[0x780 - 0x77e];       // 0x077e
	ObscureCarouselNavigator0x94 m_unk0x780;   // 0x0780
	ObscureBanner0x9f4 m_unk0x814;             // 0x0814
	ObscureAnchor0x5c m_unk0x1208[5];          // 0x1208
	MainMenuScreenFieldAt0x420 m_unk0x13d4;    // 0x13d4
	MainMenuScreenFieldAt0x498 m_unk0x144c[9]; // 0x144c
	MainMenuScreenFieldAt0x420 m_unk0x2ebc[9]; // 0x2ebc
	FieldAt0x32f4 m_unk0x32f4[9];              // 0x32f4
};

#endif // CONTROLCONFIGSCREEN_H
