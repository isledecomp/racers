#ifndef OBSCUREANTHEM0X58
#define OBSCUREANTHEM0X58

#include "compat.h"
#include "decomp.h"
#include "obscurevantage0x58.h"

// VTABLE: LEGORACERS 0x004b263c
// SIZE 0x58
class ObscureAnthem0x58 : public ObscureVantage0x58 {
public:
	ObscureAnthem0x58();
	~ObscureAnthem0x58() override;                                                         // vtable+0x04
	undefined4 VTable0x2c(void*, undefined4, undefined4) override;                         // vtable+0x2c
	undefined4 VTable0x30(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4) override; // vtable+0x30
	undefined4 VTable0x34(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4) override; // vtable+0x34

	// SYNTHETIC: LEGORACERS 0x0046ea30
	// ObscureAnthem0x58::`scalar deleting destructor'
};

#endif // OBSCUREANTHEM0X58
