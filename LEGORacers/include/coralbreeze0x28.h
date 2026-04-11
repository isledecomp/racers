#ifndef CORALBREEZE0X28_H
#define CORALBREEZE0X28_H

#include "decomp.h"
#include "types.h"
#include "util/list.h"

class IndigoStar0x18;

// SIZE 0x28
class CoralBreeze0x28 : public ListLink {
public:
	CoralBreeze0x28() {}

	virtual undefined4 VTable0x00(undefined4) = 0; // vtable+0x00
	virtual undefined4 VTable0x04() = 0;           // vtable+0x04

	void SetUnk0x0c(IndigoStar0x18* p_unk0x0c) { m_unk0x0c = p_unk0x0c; }

protected:
	IndigoStar0x18* m_unk0x0c; // 0x0c
	ListHead m_unk0x10;        // 0x10
	ListHead m_unk0x1c;        // 0x1c
};

#endif // CORALBREEZE0X28_H
