#ifndef OBSCURECAROUSEL0X78_H
#define OBSCURECAROUSEL0X78_H

#include "compat.h"
#include "decomp.h"
#include "menu/style/ceruleanemperor0x4c.h"
#include "menu/widgets/obscureanthem0x58.h"

class SoundGroupBinding;

// VTABLE: LEGORACERS 0x004b23f0
// SIZE 0x78
class ObscureCarousel0x78 : public ObscureAnthem0x58 {
public:
	// SIZE 0x38
	class CreateParams0x38 : public ObscureVantage0x58::CreateParams0x38 {};

	ObscureCarousel0x78();
	void Reset() override;                                                                    // vtable+0x00
	~ObscureCarousel0x78() override;                                                          // vtable+0x04
	void VTable0x14(VisualState0x4*) override;                                                // vtable+0x14
	ObscureVantage0x58* VTable0x30(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x30
	virtual void VTable0x40() = 0;                                                            // vtable+0x40
	virtual void VTable0x44(undefined4) = 0;                                                  // vtable+0x44
	virtual void VTable0x48(VisualState0x4*, VisualState0x4*);                                // vtable+0x48
	virtual void VTable0x4c(VisualState0x4*, VisualState0x4*);                                // vtable+0x4c
	virtual void VTable0x50(undefined4) = 0;                                                  // vtable+0x50
	virtual LegoS32 VTable0x54() = 0;                                                         // vtable+0x54
	virtual LegoS32 VTable0x58() = 0;                                                         // vtable+0x58

	LegoBool32 FUN_0046c970(CreateParams0x38* p_createParams, CeruleanEmperor0x4c::Entry0x18* p_styleEntry);
	LegoU32 GetUnk0x6c() const { return m_unk0x6c; }

	// SYNTHETIC: LEGORACERS 0x0046c8d0
	// ObscureCarousel0x78::`scalar deleting destructor'

protected:
	LegoS32 FUN_0046c9a0(LegoS32 p_index);

	CeruleanEmperor0x4c::Entry0x18* m_unk0x58; // 0x58
	SoundGroupBinding* m_unk0x5c;              // 0x5c
	LegoS32 m_unk0x60;                         // 0x60
	undefined4 m_unk0x64;                      // 0x64
	LegoS32 m_unk0x68;                         // 0x68
	LegoS32 m_unk0x6c;                         // 0x6c
	LegoS32 m_unk0x70;                         // 0x70
	LegoS32 m_unk0x74;                         // 0x74
};

// VTABLE: LEGORACERS 0x004b24b4
// SIZE 0x94
class ObscureCarousel0x94 : public ObscureCarousel0x78 {
public:
	ObscureCarousel0x94();
	void Reset() override;                            // vtable+0x00
	~ObscureCarousel0x94() override;                  // vtable+0x04
	void VTable0x40() override;                       // vtable+0x40
	void VTable0x50(undefined4) override;             // vtable+0x50
	virtual void VTable0x5c(ObscureVantage0x58*) = 0; // vtable+0x5c

	void FUN_0046d920(ObscureVantage0x58* p_child);
	void FUN_0046d9c0(ObscureVantage0x58* p_unk0x04);
	void FUN_0046da00(ObscureVantage0x58* p_child);
	ObscureVantage0x58* FUN_0046da40(LegoS32 p_index);
	void FUN_0046da60();

	// SYNTHETIC: LEGORACERS 0x0046d870
	// ObscureCarousel0x94::`scalar deleting destructor'

protected:
	ObscureVantage0x58* m_unk0x78;    // 0x78
	undefined m_unk0x7c[0x8c - 0x7c]; // 0x7c
	LegoFloat m_unk0x8c;              // 0x8c
	LegoFloat m_unk0x90;              // 0x90
};

// VTABLE: LEGORACERS 0x004b2bac
// SIZE 0x94
class ObscureCarouselNavigator0x94 : public ObscureCarousel0x94 {
public:
	// FUNCTION: LEGORACERS 0x00488dd0
	ObscureCarouselNavigator0x94() {}

	ObscureVantage0x58* VTable0x38(Rect*, Rect*) override; // vtable+0x38
	undefined4 VTable0x3c(undefined4) override;            // vtable+0x3c
	void VTable0x44(undefined4) override;                  // vtable+0x44
	LegoS32 VTable0x54() override;                         // vtable+0x54
	LegoS32 VTable0x58() override;                         // vtable+0x58
	void VTable0x5c(ObscureVantage0x58*) override;         // vtable+0x5c

	// SYNTHETIC: LEGORACERS 0x0046c870
	// ObscureCarouselNavigator0x94::~ObscureCarouselNavigator0x94

	// SYNTHETIC: LEGORACERS 0x00475610
	// ObscureCarouselNavigator0x94::`scalar deleting destructor'
};

#endif // OBSCURECAROUSEL0X78_H
