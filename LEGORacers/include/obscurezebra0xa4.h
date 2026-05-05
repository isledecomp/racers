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
	void VTable0x00() override;                             // vtable+0x00
	~ObscureZebra0xa4() override;                           // vtable+0x04
	void VTable0x14(undefined4) override;                   // vtable+0x14
	undefined4 VTable0x38(undefined4, undefined4) override; // vtable+0x38

	// SYNTHETIC: LEGORACERS 0x004734f0
	// ObscureZebra0xa4::`scalar deleting destructor'

protected:
	undefined m_unk0x58[0xa4 - 0x58]; // 0x58
};

#endif // OBSCUREZEBRA0XA4
