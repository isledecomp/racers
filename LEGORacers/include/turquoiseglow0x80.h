#ifndef TURQUOISEGLOW0X80_H
#define TURQUOISEGLOW0X80_H

#include "compat.h"
#include "decomp.h"
#include "golnametable.h"

// VTABLE: LEGORACERS 0x004b00a4
// SIZE 0x80
class TurquoiseGlow0x80 : public GolNameTable {
public:
	TurquoiseGlow0x80();
	~TurquoiseGlow0x80() override; // vtable+0x00

	void Clear() override; // vtable+0x08

	// SYNTHETIC: LEGORACERS 0x004206f0
	// TurquoiseGlow0x80::`scalar deleting destructor'

private:
	undefined m_unk0x04[0x80 - 0x0c]; // 0x04
};

#endif // TURQUOISEGLOW0X80_H
