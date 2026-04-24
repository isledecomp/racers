#ifndef TOPAZBURST0X14_H
#define TOPAZBURST0X14_H

#include "decomp.h"
#include "types.h"

// SIZE 0x14
class TopazBurst0x14 {
public:
	// SIZE 0x18
	class Entry {
	public:
		Entry();
		~Entry();

	private:
		void FUN_0049cb00();

		undefined m_unk0x00;              // 0x00
		undefined m_unk0x01[0x08 - 0x01]; // 0x01
		undefined4 m_unk0x08;             // 0x08
		undefined m_unk0x0c[0x10 - 0x0c]; // 0x0c
		undefined4 m_unk0x10;             // 0x10
		undefined* m_unk0x14;             // 0x14
	};

	TopazBurst0x14();
	~TopazBurst0x14();

private:
	void FUN_0049ce40();

	undefined4 m_unk0x00; // 0x00
	undefined4 m_unk0x04; // 0x04
	undefined4 m_unk0x08; // 0x08
	Entry* m_unk0x0c;     // 0x0c
	undefined4 m_unk0x10; // 0x10
};

#endif // TOPAZBURST0X14_H
