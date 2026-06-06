#ifndef AWARDCINEMATICSCREEN_H
#define AWARDCINEMATICSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "golnametable.h"
#include "golworldentitygroup0x38.h"
#include "menu/screens/imaginarychisel0x658.h"
#include "util/opalhaven0xf4.h"

class AquamarineSpirit0x3c;
class GolWorldEntity;
class SapphireReef0x2030;

// VTABLE: LEGORACERS 0x004b2c5c
// SIZE 0x7b0
class AwardCinematicScreen : public ImaginaryChisel0x658 {
public:
	// VTABLE: LEGORACERS 0x004b2f00
	// SIZE 0x50
	class FieldAt0x658 : public GolWorldEntityGroup0x38 {
	public:
		// SIZE 0x18
		struct CreateParams0x18 {
			AquamarineSpirit0x3c* m_unk0x00; // 0x00
			SapphireReef0x2030* m_unk0x04;   // 0x04
			GolWorldEntity* m_unk0x08;       // 0x08
			OpalHaven0xf4* m_unk0x0c;        // 0x0c
			GolName m_unk0x10;               // 0x10
		};

		// SIZE 0xd0
		struct Lookup0xd0 {
			undefined m_unk0x00[0xc4]; // 0x00
			GolVec3 m_unk0xc4;         // 0xc4
		};

		FieldAt0x658();
		~FieldAt0x658() override;

		void VTable0x08(const GolVec3& p_center) override;                         // vtable+0x08
		void VTable0x40(const GolVec3& p_direction, const GolVec3& p_up) override; // vtable+0x40
		LegoBool32 FUN_00479510(CreateParams0x18* p_createParams);
		LegoBool32 FUN_00479590();

		// SYNTHETIC: LEGORACERS 0x00479460
		// AwardCinematicScreen::FieldAt0x658::`scalar deleting destructor'

	private:
		void FUN_004794d0(OpalHaven0xf4* p_entity);

		AquamarineSpirit0x3c* m_unk0x38; // 0x38
		SapphireReef0x2030* m_unk0x3c;   // 0x3c
		GolWorldEntity* m_unk0x40;       // 0x40
		OpalHaven0xf4* m_unk0x44;        // 0x44
		GolName m_unk0x48;               // 0x48
	};

	AwardCinematicScreen();

	void VTable0x4c() override;                                                        // vtable+0x4c
	~AwardCinematicScreen() override;                                                  // vtable+0x68
	LegoBool32 Destroy() override;                                                     // vtable+0x74
	LegoBool32 VTable0x78(undefined4) override;                                        // vtable+0x78
	void VTable0x84() override;                                                        // vtable+0x84
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00475cb0
	// AwardCinematicScreen::`scalar deleting destructor'

protected:
	FieldAt0x658 m_unk0x658;  // 0x658
	OpalHaven0xf4 m_unk0x6a8; // 0x6a8
	GolModelBase* m_unk0x79c; // 0x79c
	LegoS32 m_unk0x7a0;       // 0x7a0
	undefined4 m_unk0x7a4;    // 0x7a4
	undefined4 m_unk0x7a8;    // 0x7a8
	undefined4 m_unk0x7ac;    // 0x7ac
};

#endif // AWARDCINEMATICSCREEN_H
