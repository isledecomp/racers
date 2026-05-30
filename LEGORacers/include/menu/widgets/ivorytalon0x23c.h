#ifndef IVORYTALON0X23C_H
#define IVORYTALON0X23C_H

#include "compat.h"
#include "decomp.h"
#include "golstring.h"
#include "menu/widgets/obscureicon0x1a8.h"

// VTABLE: LEGORACERS 0x004b285c
// SIZE 0x23c
class IvoryTalon0x23c : public ObscureIcon0x1a8 {
public:
	IvoryTalon0x23c();

	void Reset() override;                                                                    // vtable+0x00
	~IvoryTalon0x23c() override;                                                              // vtable+0x04
	ObscureVantage0x58* VTable0x2c(void*, undefined4, undefined4) override;                   // vtable+0x2c
	ObscureVantage0x58* VTable0x30(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x30
	ObscureVantage0x58* VTable0x34(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x34
	ObscureVantage0x58* VTable0x38(Rect*, Rect*) override;                                    // vtable+0x38
	void VTable0x4c(undefined4) override;                                                     // vtable+0x4c
	void VTable0x50(undefined4) override;                                                     // vtable+0x50
	virtual void VTable0x70();                                                                // vtable+0x70

	// SYNTHETIC: LEGORACERS 0x00470f20
	// IvoryTalon0x23c::`scalar deleting destructor'

protected:
	undefined4 m_unk0x1a8[2];            // 0x1a8
	undefined4 m_unk0x1b0;               // 0x1b0
	undefined m_unk0x1b4[0x1f4 - 0x1b4]; // 0x1b4
	undefined2 m_unk0x1f4;               // 0x1f4
	undefined2 m_unk0x1f6;               // 0x1f6
	undefined4 m_unk0x1f8;               // 0x1f8
	GolString m_unk0x1fc;                // 0x1fc
	GolString m_unk0x208;                // 0x208
	undefined4 m_unk0x214;               // 0x214
	undefined m_unk0x218[0x238 - 0x218]; // 0x218
	undefined2 m_unk0x238;               // 0x238
	undefined2 m_unk0x23a;               // 0x23a
};

#endif // IVORYTALON0X23C_H
