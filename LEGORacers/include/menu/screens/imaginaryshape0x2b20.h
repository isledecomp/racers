#ifndef IMAGINARYSHAPE0X2B20
#define IMAGINARYSHAPE0X2B20

#include "compat.h"
#include "decomp.h"
#include "golmath.h"
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
class SoundGroupBinding;
class GolWorldEntity;

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
		// SIZE 0x30
		struct CreateParams0x30 : public ObscureLink0x1c::CreateParams0x0c {
			undefined4 m_unk0x0c;                   // 0x0c
			SoundGroupBinding* m_soundGroupBinding; // 0x10
			MenuToolContext0x4bc8* m_context;       // 0x14
			ImaginaryShape0x2b20* m_screen;         // 0x18
			GolVec3 m_unk0x1c;                      // 0x1c
			LegoFloat m_unk0x28;                    // 0x28
			undefined4 m_unk0x2c;                   // 0x2c
		};

		FieldAt0x2308();
		void Reset() override;                      // vtable+0x00
		~FieldAt0x2308() override;                  // vtable+0x04
		LegoBool32 VTable0x08() override;           // vtable+0x08
		LegoBool32 VTable0x0c() override;           // vtable+0x0c
		LegoBool32 VTable0x10(undefined4) override; // vtable+0x10
		void FUN_00477ae0(CreateParams0x30* p_createParams);
		void FUN_00477e40(LegoS32 p_unk0x04);
		LegoBool32 FUN_00477fc0(LegoFloat p_delta);
		LegoBool32 FUN_00478080(LegoS32 p_delta, LegoBool32 p_unk0x08);
		void FUN_00478120();
		LegoBool32 FUN_00478180(LegoFloat p_delta);
		LegoBool32 FUN_004782f0(LegoS32 p_delta, LegoBool32 p_unk0x08);
		void FUN_004783d0();
		LegoBool32 FUN_004784d0(LegoBool32 p_unk0x04);
		void FUN_00478560();
		LegoBool32 FUN_004785b0(LegoS32 p_delta);
		LegoBool32 FUN_00478670(LegoS32 p_delta);
		LegoBool32 FUN_00478730();
		LegoBool32 FUN_004787e0(LegoS32* p_unk0x04, LegoS32* p_unk0x08, LegoS32* p_unk0x0c);
		void FUN_004792d0();
		void FUN_00479300();
		void FUN_00479310();
		void FUN_00479320();
		GolWorldEntity* GetUnk0x58() { return reinterpret_cast<GolWorldEntity*>(&m_unk0x1c[0x58 - 0x1c]); }
		GolWorldEntity* GetUnk0x1a4() { return reinterpret_cast<GolWorldEntity*>(&m_unk0x1c[0x1a4 - 0x1c]); }
		LegoS32 GetUnk0x294() const { return m_unk0x294; }
		LegoS8 GetUnk0x298() const { return m_unk0x298; }

		// SYNTHETIC: LEGORACERS 0x004779b0
		// ImaginaryShape0x2b20::FieldAt0x2308::`scalar deleting destructor'

	private:
		undefined m_unk0x1c[0x244 - 0x1c];   // 0x1c
		undefined4 m_unk0x244;               // 0x244
		undefined4 m_unk0x248;               // 0x248
		undefined4 m_unk0x24c;               // 0x24c
		undefined m_unk0x250[0x270 - 0x250]; // 0x250
		undefined4 m_unk0x270;               // 0x270
		undefined4 m_unk0x274;               // 0x274
		undefined m_unk0x278[0x294 - 0x278]; // 0x278
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
						  MenuToolCreateParams0x30*) override;                    // vtable+0x8c
	virtual GolString* VTable0x98(undefined4) = 0;                                // vtable+0x98
	virtual GolFont0xa0* VTable0x9c(undefined4) = 0;                              // vtable+0x9c
	virtual void VTable0xa0(undefined4, undefined4, undefined4*, undefined4) = 0; // vtable+0xa0
	virtual void VTable0xa4() = 0;                                                // vtable+0xa4
	virtual void VTable0xa8() = 0;                                                // vtable+0xa8
	virtual void VTable0xac() = 0;                                                // vtable+0xac
	virtual void VTable0xb0() = 0;                                                // vtable+0xb0
	virtual void VTable0xb4() = 0;                                                // vtable+0xb4
	virtual void VTable0xb8() = 0;                                                // vtable+0xb8
	virtual void VTable0xbc() = 0;                                                // vtable+0xbc
	virtual void VTable0xc0() = 0;                                                // vtable+0xc0
	virtual void VTable0xc4();                                                    // vtable+0xc4

	// SYNTHETIC: LEGORACERS 0x00476e60
	// ImaginaryShape0x2b20::`scalar deleting destructor'

protected:
	void FUN_00477050();
	void FUN_00477130();
	void FUN_00477290();
	void FUN_004773a0();
	LegoBool32 FUN_004773e0(LegoS32 p_deltaX, LegoS32 p_deltaY, LegoU16 p_sound, LegoBool32 p_unk0x10);
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
