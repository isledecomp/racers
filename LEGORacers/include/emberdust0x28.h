#ifndef EMBERDUST0X28_H
#define EMBERDUST0X28_H

#include "compat.h"
#include "coralbreeze0x28.h"
#include "decomp.h"

// VTABLE: LEGORACERS 0x004afd04
// SIZE 0x28
class EmberDust0x28 : public CoralBreeze0x28 {
public:
	EmberDust0x28();
	~EmberDust0x28();
	undefined4 VTable0x00(undefined4) override; // vtable+0x00
	undefined4 VTable0x04() override;           // vtable+0x04
};

#endif // EMBERDUST0X28_H
