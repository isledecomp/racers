#ifndef EMBERDUST0X28_H
#define EMBERDUST0X28_H

#include "decomp.h"
#include "util/list.h"

// VTABLE: LEGORACERS 0x4afd04
// SIZE 0x28
class EmberDust0x28 : public ListLink {
public:
	~EmberDust0x28();
	virtual undefined4 VTable0x00(undefined4); // vtable+0x00
	virtual undefined4 VTable0x04();           // vtable+0x04

private:
	undefined m_unk0x0c[0x1c]; // 0x0c
};

#endif // EMBERDUST0X28_H
