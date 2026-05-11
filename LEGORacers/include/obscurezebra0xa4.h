#ifndef OBSCUREZEBRA0XA4
#define OBSCUREZEBRA0XA4

#include "compat.h"
#include "decomp.h"
#include "obscurevantage0x58.h"

// VTABLE: LEGORACERS 0x004b29f4
// SIZE 0xa4
class ObscureZebra0xa4 : public ObscureVantage0x58 {
public:
	ObscureZebra0xa4();
	void Reset() override;                        // vtable+0x00
	~ObscureZebra0xa4() override;                 // vtable+0x04
	void VTable0x14(Rect*) override;              // vtable+0x14
	undefined4 VTable0x38(Rect*, Rect*) override; // vtable+0x38

	// SYNTHETIC: LEGORACERS 0x004734f0
	// ObscureZebra0xa4::`scalar deleting destructor'

protected:
	undefined m_unk0x58[0x60 - 0x58]; // 0x58
	undefined4 m_unk0x60;             // 0x60
	undefined4 m_unk0x64;             // 0x64
	undefined4 m_unk0x68;             // 0x68
	undefined4 m_unk0x6c;             // 0x6c
	undefined m_unk0x70[0x78 - 0x70]; // 0x6c
	undefined4 m_unk0x78;             // 0x78
	undefined4 m_unk0x7c;             // 0x7c
	undefined4 m_unk0x80;             // 0x80
	undefined4 m_unk0x84;             // 0x84
	undefined m_unk0x88[0x90 - 0x88]; // 0x88
	undefined4 m_unk0x90;             // 0x90
	undefined4 m_unk0x94;             // 0x94
	undefined4 m_unk0x98;             // 0x98
	undefined4 m_unk0x9c;             // 0x9c
	undefined4 m_unk0xa0;             // 0xa0
};

#endif // OBSCUREZEBRA0XA4
