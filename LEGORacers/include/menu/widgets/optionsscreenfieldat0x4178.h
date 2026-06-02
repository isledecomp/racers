#ifndef OPTIONSSCREENFIELDAT0X4178_H
#define OPTIONSSCREENFIELDAT0X4178_H

#include "compat.h"
#include "decomp.h"
#include "menu/style/menuinputbindingtable.h"
#include "menu/widgets/obscureanchor0x5c.h"
#include "menu/widgets/obscurebanner0x5ec.h"

// VTABLE: LEGORACERS 0x004b2514
// SIZE 0x6e4
class OptionsScreenFieldAt0x4178Base0x6e4 : public ObscureBanner0x5ec {
public:
	OptionsScreenFieldAt0x4178Base0x6e4();
	void Reset() override;                                                                    // vtable+0x00
	~OptionsScreenFieldAt0x4178Base0x6e4() override;                                          // vtable+0x04
	void VTable0x14(VisualState0x4*) override;                                                // vtable+0x14
	ObscureVantage0x58* VTable0x30(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x30
	ObscureVantage0x58* VTable0x34(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x34
	undefined4 VTable0x3c(undefined4) override;                                               // vtable+0x3c
	undefined4 VTable0x74(undefined4) override;                                               // vtable+0x74
	void VTable0x78() override;                                                               // vtable+0x78
	void VTable0x7c() override;                                                               // vtable+0x7c
	virtual void VTable0x80() = 0;                                                            // vtable+0x80
	virtual void VTable0x84() = 0;                                                            // vtable+0x84
	virtual void VTable0x88() = 0;                                                            // vtable+0x88
	virtual void VTable0x8c() = 0;                                                            // vtable+0x8c
	virtual void VTable0x90(LegoS32) = 0;                                                     // vtable+0x90

	// SYNTHETIC: LEGORACERS 0x0046ded0
	// OptionsScreenFieldAt0x4178Base0x6e4::`scalar deleting destructor'

protected:
	friend class ImaginaryNotion0x290;

	LegoBool32 FUN_0046dfb0(
		MenuInputBindingTable::Entry0xb8* p_createParams,
		CeruleanEmperor0x4c::Entry0xbcWithImages* p_styleEntry
	);

	ObscureAnchor0x5c m_unk0x5ec;                // 0x5ec
	ObscureAnchor0x5c m_unk0x648;                // 0x648
	undefined m_unk0x6a4[0x6bc - 0x6a4];         // 0x6a4
	LegoS32 m_unk0x6bc;                          // 0x6bc
	LegoS32 m_unk0x6c0;                          // 0x6c0
	LegoS32 m_unk0x6c4;                          // 0x6c4
	LegoS32 m_unk0x6c8;                          // 0x6c8
	LegoFloat m_unk0x6cc;                        // 0x6cc
	Rect m_unk0x6d0;                             // 0x6d0
	ObscureIcon0x1a8::SoundIdPair0x4 m_unk0x6e0; // 0x6e0
};

// VTABLE: LEGORACERS 0x004b25a8
// SIZE 0x6ec
class OptionsScreenFieldAt0x4178 : public OptionsScreenFieldAt0x4178Base0x6e4 {
public:
	OptionsScreenFieldAt0x4178();
	~OptionsScreenFieldAt0x4178() override;                                 // vtable+0x04
	ObscureVantage0x58* VTable0x2c(void*, undefined4, undefined4) override; // vtable+0x2c
	undefined4 VTable0x70(undefined4, undefined4, undefined4) override;     // vtable+0x70
	void VTable0x80() override;                                             // vtable+0x80
	void VTable0x84() override;                                             // vtable+0x84
	void VTable0x88() override;                                             // vtable+0x88
	void VTable0x8c() override;                                             // vtable+0x8c
	void VTable0x90(LegoS32) override;                                      // vtable+0x90

	// SYNTHETIC: LEGORACERS 0x0046e440
	// OptionsScreenFieldAt0x4178::`scalar deleting destructor'

private:
	friend class OptionsScreenFieldAt0x4178Base0x6e4;
	void FUN_0046e4b0();

	undefined m_unk0x6e4[0x6ec - 0x6e4]; // 0x6e4
};

#endif // OPTIONSSCREENFIELDAT0X4178_H
