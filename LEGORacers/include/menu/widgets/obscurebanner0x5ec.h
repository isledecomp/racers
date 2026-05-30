#ifndef OBSCUREBANNER0X5EC_H
#define OBSCUREBANNER0X5EC_H

#include "compat.h"
#include "decomp.h"
#include "menu/style/ceruleanemperor0x4c.h"
#include "menu/widgets/obscurecarousel0x78.h"
#include "menu/widgets/obscureglyph0x21c.h"
#include "menu/widgets/obscuretome0x3fc.h"

// VTABLE: LEGORACERS 0x004b1fa0
// SIZE 0x5ec
class ObscureBanner0x5ec : public ObscureIcon0x1a8 {
public:
	// SIZE 0x90
	class CreateParams0x90 : public ObscureIcon0x1a8::CreateParams0x84 {
	public:
		ObscureGlyph0x21c::CreateParams0x9c* m_unk0x84; // 0x84
		ObscureGlyph0x21c::CreateParams0x9c* m_unk0x88; // 0x88
		ObscureTome0x3fc::CreateParams0x60* m_unk0x8c;  // 0x8c
	};

	ObscureBanner0x5ec();
	void Reset() override;                                                                          // vtable+0x00
	~ObscureBanner0x5ec() override;                                                                 // vtable+0x04
	LegoBool32 VTable0x20(CopperCrest0x40::Helper0x44*, undefined4, undefined4) override;           // vtable+0x20
	ObscureVantageEventResult VTable0x24(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x24
	ObscureVantageEventResult VTable0x28(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x28
	void VTable0x44(undefined4) override;                                                           // vtable+0x44
	void VTable0x48(undefined4) override;                                                           // vtable+0x48
	void VTable0x4c(undefined4) override;                                                           // vtable+0x4c
	void VTable0x50(undefined4) override;                                                           // vtable+0x50
	void VTable0x58(undefined4) override;                                                           // vtable+0x58
	virtual undefined4 VTable0x70(undefined4, undefined4, undefined4);                              // vtable+0x70
	virtual undefined4 VTable0x74(undefined4) = 0;                                                  // vtable+0x74
	virtual void VTable0x78() = 0;                                                                  // vtable+0x78
	virtual void VTable0x7c() = 0;                                                                  // vtable+0x7c

	// SYNTHETIC: LEGORACERS 0x00466fd0
	// ObscureBanner0x5ec::`scalar deleting destructor'

protected:
	LegoBool32 FUN_004670a0(CreateParams0x90* p_createParams, const CeruleanEmperor0x4c::Entry0xbc* p_styleEntry);
	LegoBool32 FUN_00467150(CreateParams0x90* p_createParams, const CeruleanEmperor0x4c::Entry0xbc* p_styleEntry);
	LegoBool32 FUN_004677e0(CreateParams0x90* p_createParams);
	void FUN_00467180(undefined4 p_param);
	void FUN_004671e0(undefined4 p_param);

	undefined4 m_unk0x1a8;                      // 0x1a8
	ObscureGlyph0x21c m_unk0x1ac;               // 0x1ac
	ObscureGlyph0x21c m_unk0x3c8;               // 0x3c8
	undefined4 m_unk0x5e4;                      // 0x5e4
	CeruleanEmperor0x4c::Entry0xbc* m_unk0x5e8; // 0x5e8
};

// VTABLE: LEGORACERS 0x004b2020
// SIZE 0x9f4
class ObscureBanner0x9f4 : public ObscureBanner0x5ec {
public:
	// SIZE 0x98
	class CreateParams0x98 : public ObscureBanner0x5ec::CreateParams0x90 {
	public:
		ObscureCarousel0x94* m_unk0x90; // 0x90
		undefined4 m_unk0x94;           // 0x94
	};

	ObscureBanner0x9f4();
	void Reset() override;                                                                          // vtable+0x00
	~ObscureBanner0x9f4() override;                                                                 // vtable+0x04
	LegoBool32 VTable0x08() override;                                                               // vtable+0x08
	void VTable0x14(VisualState0x4*) override;                                                      // vtable+0x14
	ObscureVantageEventResult VTable0x24(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x24
	ObscureVantage0x58* VTable0x30(InputEventQueue::Event*, undefined4, undefined4) override;       // vtable+0x30
	ObscureVantage0x58* VTable0x34(InputEventQueue::Event*, undefined4, undefined4) override;       // vtable+0x34
	undefined4 VTable0x3c(undefined4) override;                                                     // vtable+0x3c
	undefined4 VTable0x74(undefined4) override;                                                     // vtable+0x74
	void VTable0x78() override;                                                                     // vtable+0x78
	void VTable0x7c() override;                                                                     // vtable+0x7c

	LegoBool32 FUN_00467800(CreateParams0x98* p_createParams, CeruleanEmperor0x4c::Entry0xbc* p_styleEntry);

	// SYNTHETIC: LEGORACERS 0x00467730
	// ObscureBanner0x9f4::`scalar deleting destructor'

protected:
	LegoBool32 FUN_00467560(InputEventQueue::Event* p_event, undefined4 p_result);
	LegoBool32 FUN_00467670(InputEventQueue::Event* p_event, undefined4 p_result);

	ObscureTome0x3fc m_unk0x5ec;     // 0x5ec
	ObscureCarousel0x94* m_unk0x9e8; // 0x9e8
	undefined4 m_unk0x9ec;           // 0x9ec
	undefined4 m_unk0x9f0;           // 0x9f0
};

#endif // OBSCUREBANNER0X5EC_H
