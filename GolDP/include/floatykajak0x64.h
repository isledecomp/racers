#ifndef FLOATYKAJAK0x64_H
#define FLOATYKAJAK0x64_H
#include "decomp.h"
#include "floatybuoy0x58.h"

class BoundingVolume0x64;
class ShadowWolf0xc;
class ZoweeBlubberworth0xf0;

// VTABLE: GOLDP 0x10056bec
// SIZE 0x64
class FloatyKajak0x64 : public FloatyBuoy0x58 {
public:
	FloatyKajak0x64();

	void FUN_1001b760(BoundingVolume0x64* p_arg);

protected:
	friend class ZoweeBlubberworth0xf0;

	BoundingVolume0x64* m_unk0x58;
	ShadowWolf0xc* m_unk0x5c;
	undefined4 m_unk0x60;
};

#endif // FLOATYKAJAK0x64_H
