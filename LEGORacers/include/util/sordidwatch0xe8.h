#ifndef SORDIDWATCH0XE8_H
#define SORDIDWATCH0XE8_H

#include "decomp.h"
#include "types.h"

class SordidWatch0xe8 {
public:
	struct SordidWatchInner0x38 {
		undefined m_unk0x00[0x30];
		undefined4 m_unk0x30;
		SordidWatchInner0x38* m_unk0x34;
	};

	// size unknown, 0xe8 is a lower bound

	undefined4 GetFlags() const { return m_flags; }

	void FUN_00412840();
	void FUN_00412970();

private:
	undefined m_unk0x000[0xa8];       // 0x00
	undefined4 m_unk0xa8;             // 0xa8
	SordidWatchInner0x38* m_unk0xac;  // 0xac
	SordidWatchInner0x38* m_unk0xb0;  // 0xb0
	undefined4 m_unk0xb4;             // 0xb4
	undefined4 m_flags;               // 0xb8
	undefined m_unk0xb9[0xd0 - 0xbc]; // 0xb9
	undefined4 m_unk0xd0;             // 0xd0
	undefined4 m_unk0xd4;             // 0xd4
	undefined4 m_unk0xd8;             // 0xd8
	undefined4 m_unk0xdc;             // 0xdc
	undefined4 m_unk0xe0;             // 0xe0
	undefined4 m_unk0xe4;             // 0xe4
};

#endif // SORDIDWATCH0XE8_H
