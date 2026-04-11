#ifndef FROSTPETAL0X34_H
#define FROSTPETAL0X34_H

#include "decomp.h"
#include "types.h"
#include "util/list.h"

class IndigoStar0x18;

// VTABLE: LEGORACERS 0x4afc08
// SIZE 0x34
class FrostPetal0x34 : public ListLink {
public:
	FrostPetal0x34();
	virtual void VTable0x00(LegoChar*); // vtable+0x00

	void SetUnk0x0c(IndigoStar0x18* p_unk0x0c) { m_unk0x0c = p_unk0x0c; }

private:
	IndigoStar0x18* m_unk0x0c; // 0x0c
	undefined4 m_unk0x10;      // 0x10
	undefined4 m_unk0x14;      // 0x14
	undefined4 m_unk0x18;      // 0x18
	ListHead m_unk0x1c;        // 0x1c
	ListHead m_unk0x28;        // 0x28
};

#endif // FROSTPETAL0X34_H
