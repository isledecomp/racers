#ifndef VELVETTHUNDER0XC8AC8_H
#define VELVETTHUNDER0XC8AC8_H

#include "compat.h"
#include "decomp.h"

// VTABLE: GOLDP 0x100564b0
class PixelDust0x4 {
public:
	virtual ~PixelDust0x4() {}

	// SYNTHETIC: GOLDP 0x10007170
	// PixelDust0x4::`scalar deleting destructor'
};

// VTABLE: GOLDP 0x10056440
// SIZE 0xc8ac8
class VelvetThunder0xc8ac8 : public PixelDust0x4 {
public:
	~VelvetThunder0xc8ac8() override; // vtable+0x00

	// SYNTHETIC: GOLDP 0x10007040
	// VelvetThunder0xc8ac8::`scalar deleting destructor'

private:
	undefined m_unk0x04[0xc8ac4]; // 0x04
};

#endif // VELVETTHUNDER0XC8AC8_H
