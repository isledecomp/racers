#ifndef IMAGINARYSHAPE0X2B20
#define IMAGINARYSHAPE0X2B20

#include "compat.h"
#include "decomp.h"
#include "menu/screens/mainmenuscreenfieldat0x498.h"
#include "menu/screens/obsidianmantle0x3b4.h"
#include "menu/widgets/obscureanchor0x5c.h"
#include "menu/widgets/obscurebanner0x5ec.h"
#include "menu/widgets/obscurecarousel0x78.h"
#include "menu/widgets/obscurelink0x1c.h"
#include "menu/widgets/obscurerune0x4d8.h"
#include "racer/siennacircuit0x154.h"

class MenuToolContext0x4bc8;
class MenuToolCreateParams0x30;

// VTABLE: LEGORACERS 0x004b2cf8
// SIZE 0x2b20
class ImaginaryShape0x2b20 : public ObsidianMantle0x3b4 {
public:
	enum {
		c_carBuildSaveBufferSize = 0x202,
		c_partCategoryCount = 12,
		c_alwaysAvailablePartCategoryCount = 4,
		c_saveUnlockedPartCategoryCount = c_partCategoryCount - c_alwaysAvailablePartCategoryCount
	};

	// VTABLE: LEGORACERS 0x004b2edc
	// SIZE 0x2d0
	class FieldAt0x2308 : public ObscureLink0x1c {
	public:
		FieldAt0x2308();
		void Reset() override;                      // vtable+0x00
		~FieldAt0x2308() override;                  // vtable+0x04
		LegoBool32 VTable0x08() override;           // vtable+0x08
		LegoBool32 VTable0x0c() override;           // vtable+0x0c
		LegoBool32 VTable0x10(undefined4) override; // vtable+0x10
		void FUN_00477e40(LegoS32 p_unk0x04);
		LegoBool32 FUN_00477fc0(LegoFloat p_delta);
		LegoBool32 FUN_00478080(LegoS32 p_delta, LegoBool32 p_unk0x08);
		void FUN_00478120();
		LegoBool32 FUN_00478180(LegoFloat p_delta);
		LegoBool32 FUN_004782f0(LegoS32 p_delta, LegoBool32 p_unk0x08);
		void FUN_004783d0();
		LegoBool32 FUN_004784d0(LegoBool32 p_unk0x04);
		void FUN_00478560();
		LegoBool32 FUN_00478730();
		LegoBool32 FUN_004787e0(LegoS32* p_unk0x04, LegoS32* p_unk0x08, LegoS32* p_unk0x0c);
		void FUN_00479300();
		void FUN_00479310();
		void FUN_00479320();
		LegoS32 GetUnk0x294() const { return m_unk0x294; }
		LegoS8 GetUnk0x298() const { return m_unk0x298; }

		// SYNTHETIC: LEGORACERS 0x004779b0
		// ImaginaryShape0x2b20::FieldAt0x2308::`scalar deleting destructor'

	private:
		undefined m_unk0x1c[0x294 - 0x1c];   // 0x1c
		LegoS32 m_unk0x294;                  // 0x294
		LegoS8 m_unk0x298;                   // 0x298
		undefined m_unk0x299[0x2d0 - 0x299]; // 0x299
	};

	ImaginaryShape0x2b20();

	void VTable0x10(ObscureVantage0x58*) override; // vtable+0x10
	void VTable0x38(ObscureVantage0x58*) override; // vtable+0x38
	void VTable0x44(ObscureVantage0x58*) override; // vtable+0x44
	void VTable0x4c() override;                    // vtable+0x4c
	void Reset() override;                         // vtable+0x54
	~ImaginaryShape0x2b20() override;              // vtable+0x68
	LegoBool32 VTable0x78(undefined4) override;    // vtable+0x78
	void VTable0x80() override;                    // vtable+0x80
	void VTable0x84() override;                    // vtable+0x84
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*,
						  MenuToolCreateParams0x30*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00476e60
	// ImaginaryShape0x2b20::`scalar deleting destructor'

protected:
	void FUN_00477050();
	void FUN_00477130();
	void FUN_00477290();
	void FUN_004773a0();
	LegoBool32 FUN_004773e0(undefined4 p_unk0x04, undefined4 p_unk0x08, undefined4 p_unk0x0c, undefined4 p_unk0x10);
	void FUN_00477770();

	ObscureAnchor0x5c m_unk0x3b4;            // 0x3b4
	ObscureCarouselNavigator0x94 m_unk0x410; // 0x410
	ObscureBanner0x9f4 m_unk0x4a4;           // 0x4a4
	SiennaCircuit0x154 m_unk0xe98;           // 0xe98
	ObscureBanner0x9f4 m_unk0xfec;           // 0xfec
	ObscureAnchor0x5c m_unk0x19e0[12];       // 0x19e0
	ObscureRune0x4d8 m_unk0x1e30;            // 0x1e30
	FieldAt0x2308 m_unk0x2308;               // 0x2308
	MainMenuScreenFieldAt0x498 m_unk0x25d8;  // 0x25d8
	undefined4 m_unk0x28c8;                  // 0x28c8
	undefined4 m_unk0x28cc;                  // 0x28cc
	undefined4 m_unk0x28d0;                  // 0x28d0
	LegoU8 m_carBuildSaveBuffer[0x202];      // 0x28d4
	undefined m_unk0x2ad6[0x2ad8 - 0x2ad6];  // 0x2ad6
	undefined4 m_unk0x2ad8;                  // 0x2ad8
	undefined4 m_unk0x2adc;                  // 0x2adc
	undefined4 m_unk0x2ae0;                  // 0x2ae0
	undefined4 m_unk0x2ae4;                  // 0x2ae4
	LegoU8 m_partCategoryUnlockFlags;        // 0x2ae8
	undefined m_unk0x2ae9[0x2aec - 0x2ae9];  // 0x2ae9
	LegoBool32 m_partCategoryAvailable[12];  // 0x2aec
	undefined4 m_unk0x2b1c;                  // 0x2b1c
};

#endif // IMAGINARYSHAPE0X2B20
