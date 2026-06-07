#ifndef IMAGINARYSHAPE0X2B20
#define IMAGINARYSHAPE0X2B20

#include "compat.h"
#include "decomp.h"
#include "golmath.h"
#include "golmodelentity.h"
#include "menu/screens/awardcinematicscreen.h"
#include "menu/screens/carbuildscreenbase.h"
#include "menu/widgets/menucarousel.h"
#include "menu/widgets/menuframedsceneview.h"
#include "menu/widgets/menuimage.h"
#include "menu/widgets/menusceneelement.h"
#include "menu/widgets/menuselector.h"
#include "menu/widgets/menutextbutton.h"
#include "model/carbuildmodel.h"
#include "racer/siennacircuit0x154.h"
#include "render/golrenderdevice.h"
#include "util/opalhaven0xf4.h"

class MenuGameContext;
class MenuScreenCreateParams;
class SoundGroupBinding;
class CmbModelPart0x34;
class GolModelBase;
class GolSceneNode;
class GolWorldEntity;

// VTABLE: LEGORACERS 0x004b2cf8
// SIZE 0x2b20
class CarModelScreenBase : public CarBuildScreenBase {
public:
	enum {
		c_carBuildSaveBufferSize = 0x202,
		c_partCategoryCount = 12,
		c_alwaysAvailablePartCategoryCount = 4,
		c_saveUnlockedPartCategoryCount = c_partCategoryCount - c_alwaysAvailablePartCategoryCount
	};

	// VTABLE: LEGORACERS 0x004b2edc
	// SIZE 0x2d0
	class CarPartPlacement : public MenuSceneElement {
	public:
		enum {
			c_flagRotatingAroundCar = 1 << 0,
			c_flagPitchChanging = 1 << 1,
			c_flagCommittingPart = 1 << 2,
			c_flagResettingView = 1 << 3,
			c_placementFeedbackLowering = 1 << 0,
			c_placementFeedbackHold = 1 << 1,
			c_placementFeedbackRaising = 1 << 2,
			c_placementFeedbackMask =
				c_placementFeedbackLowering | c_placementFeedbackHold | c_placementFeedbackRaising,
		};

		// SIZE 0x30
		struct CreateParams : public MenuSceneElement::CreateParams {
			undefined4 m_unk0x0c;                   // 0x0c
			SoundGroupBinding* m_soundGroupBinding; // 0x10
			MenuGameContext* m_context;             // 0x14
			CarModelScreenBase* m_screen;           // 0x18
			GolVec3 m_unk0x1c;                      // 0x1c
			LegoFloat m_unk0x28;                    // 0x28
			undefined4 m_unk0x2c;                   // 0x2c
		};

		CarPartPlacement();
		void Reset() override;                      // vtable+0x00
		~CarPartPlacement() override;               // vtable+0x04
		LegoBool32 VTable0x08() override;           // vtable+0x08
		LegoBool32 VTable0x0c() override;           // vtable+0x0c
		LegoBool32 VTable0x10(undefined4) override; // vtable+0x10
		LegoBool32 FUN_00477ae0(CreateParams* p_createParams);
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
		GolWorldEntity* GetUnk0x58() { return &m_unk0x58; }
		GolWorldEntity* GetUnk0x1a4() { return &m_unk0x1a4; }
		LegoS32 GetUnk0x294() const { return m_unk0x294; }
		LegoS8 GetUnk0x298() const { return m_unk0x298; }

		// SYNTHETIC: LEGORACERS 0x004779b0
		// CarModelScreenBase::CarPartPlacement::`scalar deleting destructor'

	private:
		void FUN_00477bf0();
		void FUN_00477c50();
		void FUN_00477cc0(undefined4 p_unk0x04);
		void FUN_00477dc0();
		void FUN_00477f00(LegoS32 p_unk0x04);
		void FUN_00477f30(LegoFloat p_unk0x04);
		void FUN_00478c70(LegoS32 p_elapsed);
		void FUN_00478e90(LegoS32 p_elapsed);
		void FUN_00478ec0(LegoS32 p_elapsed);
		void FUN_00478ef0(LegoS32 p_elapsed);
		void FUN_00478fd0(LegoS32 p_elapsed);
		void FUN_004790f0(LegoS32 p_elapsed);
		void FUN_00479250(LegoS32 p_elapsed);
		void FUN_00479330(GolVec3* p_dest, LegoS32 p_index);

		CarModelScreenBase* m_unk0x1c;                    // 0x1c
		SoundGroupBinding* m_unk0x20;                     // 0x20
		MenuGameContext* m_unk0x24;                       // 0x24
		CarBuildModel::Placement m_unk0x28;               // 0x28
		AwardCinematicScreen::SceneEntityGroup m_unk0x58; // 0x58
		OpalHaven0xf4 m_unk0xa8;                          // 0xa8
		GolSceneNode* m_unk0x19c;                         // 0x19c
		CmbModelPart0x34* m_unk0x1a0;                     // 0x1a0
		GolModelEntity m_unk0x1a4;                        // 0x1a4
		GolModelBase* m_unk0x234;                         // 0x234
		GolModelBase* m_unk0x238;                         // 0x238
		GolRenderDevice::MaterialColor m_unk0x23c;        // 0x23c
		undefined4 m_unk0x240;                            // 0x240
		undefined4 m_unk0x244;                            // 0x244
		LegoU32 m_unk0x248;                               // 0x248
		LegoU32 m_unk0x24c;                               // 0x24c
		GolVec3 m_unk0x250;                               // 0x250
		undefined4 m_unk0x25c;                            // 0x25c
		undefined4 m_unk0x260;                            // 0x260
		LegoU32 m_unk0x264;                               // 0x264
		LegoU32 m_unk0x268;                               // 0x268
		LegoFloat m_unk0x26c;                             // 0x26c
		LegoFloat m_unk0x270;                             // 0x270
		LegoFloat m_unk0x274;                             // 0x274
		LegoU8 m_unk0x278;                                // 0x278
		undefined m_unk0x279[0x27c - 0x279];              // 0x279
		GolVec3 m_unk0x27c;                               // 0x27c
		LegoFloat m_unk0x288;                             // 0x288
		LegoU32 m_unk0x28c;                               // 0x28c
		LegoU8 m_unk0x290;                                // 0x290
		undefined m_unk0x291[0x294 - 0x291];              // 0x291
		LegoS32 m_unk0x294;                               // 0x294
		LegoS8 m_unk0x298;                                // 0x298
		undefined m_unk0x299[0x29c - 0x299];              // 0x299
		LegoFloat m_unk0x29c;                             // 0x29c
		LegoU32 m_unk0x2a0;                               // 0x2a0
		LegoU32 m_unk0x2a4;                               // 0x2a4
		LegoFloat m_unk0x2a8[8];                          // 0x2a8
		LegoFloat m_unk0x2c8;                             // 0x2c8
		LegoFloat m_unk0x2cc;                             // 0x2cc
	};

	CarModelScreenBase();

	void VTable0x10(MenuWidget*) override;      // vtable+0x10
	void VTable0x38(MenuWidget*) override;      // vtable+0x38
	void VTable0x44(MenuWidget*) override;      // vtable+0x44
	void VTable0x4c() override;                 // vtable+0x4c
	void Reset() override;                      // vtable+0x54
	~CarModelScreenBase() override;             // vtable+0x68
	LegoBool32 VTable0x78(undefined4) override; // vtable+0x78
	void VTable0x80() override;                 // vtable+0x80
	void VTable0x84() override;                 // vtable+0x84
	LegoBool32 VTable0x8c(MenuGameContext*,
						  MenuScreenCreateParams*) override;              // vtable+0x8c
	GolString* VTable0x98(undefined4) override = 0;                       // vtable+0x98
	GolFont0xa0* VTable0x9c(undefined4) override = 0;                     // vtable+0x9c
	void VTable0xa0(LegoS32*, LegoS32*, LegoS32*, LegoS32*) override = 0; // vtable+0xa0
	virtual void VTable0xa4() = 0;                                        // vtable+0xa4
	virtual void VTable0xa8() = 0;                                        // vtable+0xa8
	virtual void VTable0xac() = 0;                                        // vtable+0xac
	virtual void VTable0xb0() = 0;                                        // vtable+0xb0
	virtual void VTable0xb4() = 0;                                        // vtable+0xb4
	virtual void VTable0xb8() = 0;                                        // vtable+0xb8
	virtual void VTable0xbc() = 0;                                        // vtable+0xbc
	virtual void VTable0xc0() = 0;                                        // vtable+0xc0
	virtual void VTable0xc4();                                            // vtable+0xc4

	// SYNTHETIC: LEGORACERS 0x00476e60
	// CarModelScreenBase::`scalar deleting destructor'

protected:
	void FUN_00477050();
	void FUN_00477130();
	void FUN_00477290();
	void FUN_004773a0();
	LegoBool32 FUN_004773e0(LegoS32 p_deltaX, LegoS32 p_deltaY, LegoU16 p_sound, LegoBool32 p_unk0x10);
	void FUN_00477770();

	MenuImage m_unk0x3b4;                   // 0x3b4
	MenuCarouselNavigator m_unk0x410;       // 0x410
	MenuSelector m_unk0x4a4;                // 0x4a4
	SiennaCircuit0x154 m_unk0xe98;          // 0xe98
	MenuSelector m_unk0xfec;                // 0xfec
	MenuImage m_unk0x19e0[12];              // 0x19e0
	MenuFramedSceneView m_unk0x1e30;        // 0x1e30
	CarPartPlacement m_unk0x2308;           // 0x2308
	MenuTextButton m_unk0x25d8;             // 0x25d8
	undefined4 m_unk0x28c8;                 // 0x28c8
	undefined4 m_unk0x28cc;                 // 0x28cc
	undefined4 m_unk0x28d0;                 // 0x28d0
	LegoU8 m_carBuildSaveBuffer[0x202];     // 0x28d4
	undefined m_unk0x2ad6[0x2ad8 - 0x2ad6]; // 0x2ad6
	undefined4 m_unk0x2ad8;                 // 0x2ad8
	undefined4 m_unk0x2adc;                 // 0x2adc
	undefined4 m_unk0x2ae0;                 // 0x2ae0
	undefined4 m_unk0x2ae4;                 // 0x2ae4
	LegoU8 m_partCategoryUnlockFlags;       // 0x2ae8
	undefined m_unk0x2ae9[0x2aec - 0x2ae9]; // 0x2ae9
	LegoBool32 m_partCategoryAvailable[12]; // 0x2aec
	undefined4 m_unk0x2b1c;                 // 0x2b1c
};

#endif // IMAGINARYSHAPE0X2B20
