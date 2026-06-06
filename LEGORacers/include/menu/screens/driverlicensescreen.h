#ifndef DRIVERLICENSESCREEN_H
#define DRIVERLICENSESCREEN_H

#include "compat.h"
#include "decomp.h"
#include "golstring.h"
#include "menu/screens/imaginarytool0x368.h"
#include "menu/screens/mainmenuscreenfieldat0x22dc.h"
#include "menu/screens/mainmenuscreenfieldat0x420.h"
#include "menu/screens/mainmenuscreenfieldat0x498.h"
#include "menu/widgets/embervault0x330.h"
#include "menu/widgets/obscureanchor0x5c.h"
#include "menu/widgets/obscureanchor0x7c.h"
#include "menu/widgets/obscurerune0x4d8.h"
#include "menu/widgets/obscuretome0x3fc.h"
#include "racer/turquoiseglowcolor.h"

// VTABLE: LEGORACERS 0x004b31f8
// SIZE 0x23bc
class DriverLicenseScreen : public ImaginaryTool0x368 {
public:
	DriverLicenseScreen();

	void VTable0x38(ObscureVantage0x58*) override;                                     // vtable+0x38
	void VTable0x3c(ObscureIcon0x1a8*) override;                                       // vtable+0x3c
	void VTable0x40(ObscureIcon0x1a8*) override;                                       // vtable+0x40
	void VTable0x44(ObscureVantage0x58*) override;                                     // vtable+0x44
	void VTable0x4c() override;                                                        // vtable+0x4c
	void Reset() override;                                                             // vtable+0x54
	~DriverLicenseScreen() override;                                                   // vtable+0x68
	LegoBool32 Destroy() override;                                                     // vtable+0x74
	void VTable0x84() override;                                                        // vtable+0x84
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override; // vtable+0x8c
	void VTable0x90(undefined4) override;                                              // vtable+0x90
	void VTable0x94(undefined4) override;                                              // vtable+0x94

	void ApplyCheatCode();

	// SYNTHETIC: LEGORACERS 0x0047b070
	// DriverLicenseScreen::`scalar deleting destructor'

protected:
	void FUN_0047b220();
	LegoBool32 FUN_0047b580();
	void FUN_0047b6b0();
	void FUN_0047b750();
	undefined2* GetCheatBuffer() { return m_unk0x1f1c.GetUnk0x300(); }
	TurquoiseGlowColor& GetUnk0x2244() { return *m_unk0x1f1c.GetUnk0x328(); }

	enum {
		c_nslwj = 1 << 0,
		c_flyskyhgh = 1 << 1,
		c_pgllrd = 1 << 2,
		c_pgllyll = 1 << 3,
		c_pgllgrn = 1 << 4,
		c_lnfrrrm = 1 << 5,
		c_rpcrnly = 1 << 6,
		c_mxpmx = 1 << 7,
		c_fstfrwrd = 1 << 8,
		c_nwhls = 1 << 9,
		c_nchsss = 1 << 10,
		c_ndrvr = 1 << 11,
		c_nmrchts = 1 << 12
	};

	enum {
		c_cheatBufferLength = 14,
		c_cheatBufferStorageLength = c_cheatBufferLength + 1
	};

	ObscureAnchor0x7c m_unk0x368;            // 0x0368
	ObscureAnchor0x5c m_unk0x3e4;            // 0x03e4
	ObscureAnchor0x5c m_unk0x440[8];         // 0x0440
	MainMenuScreenFieldAt0x420 m_unk0x720;   // 0x0720
	MainMenuScreenFieldAt0x498 m_unk0x798;   // 0x0798
	MainMenuScreenFieldAt0x498 m_unk0xa88;   // 0x0a88
	MainMenuScreenFieldAt0x498 m_unk0xd78;   // 0x0d78
	MainMenuScreenFieldAt0x498 m_unk0x1068;  // 0x1068
	MainMenuScreenFieldAt0x498 m_unk0x1358;  // 0x1358
	ObscureRune0x4d8 m_unk0x1648;            // 0x1648
	ObscureTome0x3fc m_unk0x1b20;            // 0x1b20
	EmberVault0x330 m_unk0x1f1c;             // 0x1f1c
	MainMenuScreenFieldAt0x22dc m_unk0x224c; // 0x224c
	GolString m_cheatString;                 // 0x23a8
	LegoBool32 m_unk0x23b4;                  // 0x23b4
	LegoBool32 m_unk0x23b8;                  // 0x23b8
};

#endif // DRIVERLICENSESCREEN_H
