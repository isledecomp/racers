#ifndef SORDIDWATCH0XE8_H
#define SORDIDWATCH0XE8_H

#include "decomp.h"
#include "types.h"

class SordidWatch0xe8 {
public:
	// size unknown, 0xe8 is a lower bound

	undefined4 GetFlags() const { return m_flags; }

	void FUN_00412840();
	void FUN_00412970();

private:
	undefined m_unk0x000[0xb8];
	undefined4 m_flags; // 0x0b8
	undefined m_unk0x0b9[0xd0 - 0xbc];
	undefined4 m_unk0xd0;
	undefined4 m_unk0xd4;
	undefined4 m_unk0xd8;
	undefined4 m_unk0xdc;
	undefined4 m_unk0xe0;
	undefined4 m_unk0xe4;
};

#endif // SORDIDWATCH0XE8_H
