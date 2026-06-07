#ifndef AMETHYSTBREEZE0X104_H
#define AMETHYSTBREEZE0X104_H

#include "decomp.h"
#include "render/golrenderdevice.h"

// VTABLE: LEGORACERS 0x004af64c
// SIZE 0x104
class AmethystBreeze0x104 {
public:
	AmethystBreeze0x104();

	virtual void VTable0x00(undefined4 p_unk0x04, undefined4 p_unk0x08, undefined4 p_unk0x0c); // vtable+0x00
	virtual void VTable0x04(undefined4 p_unk0x04, undefined4 p_unk0x08, undefined4 p_unk0x0c); // vtable+0x04
	virtual void VTable0x08(undefined4 p_unk0x04);                                             // vtable+0x08

	void Reset();
	void FUN_0040eb60();
	void FUN_0040eb70(const GolRenderDevice::MaterialColor* p_material);
	void FUN_0040eba0(const GolRenderDevice::Light* p_light);

private:
	undefined m_unk0x04[0x104 - 0x04]; // 0x04
};

#endif // AMETHYSTBREEZE0X104_H
