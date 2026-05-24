#ifndef OBSCURERUNE0X4D8
#define OBSCURERUNE0X4D8

#include "compat.h"
#include "decomp.h"
#include "obscuresigil0xdc.h"
#include "obscuretome0x3dc.h"

// VTABLE: LEGORACERS 0x004b1e40
// SIZE 0x4d8
class ObscureRune0x4d8 : public ObscureSigil0xdc {
public:
	ObscureRune0x4d8();
	~ObscureRune0x4d8() override; // vtable+0x04

	// SYNTHETIC: LEGORACERS 0x00466100
	// ObscureRune0x4d8::`scalar deleting destructor'

protected:
	ObscureTome0x3fc m_unk0xdc; // 0x0dc
};

#endif // OBSCURERUNE0X4D8
