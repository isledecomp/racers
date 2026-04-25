#ifndef TANZANITEWISP0X88_H
#define TANZANITEWISP0X88_H

#include "decomp.h"

// SIZE 0x88
class TanzaniteWisp0x88 {
public:
	TanzaniteWisp0x88();
	~TanzaniteWisp0x88();

	void Reset()
	{
		m_unk0x78 = 0;
		m_unk0x80 = 0;
	}

private:
	undefined m_unk0x00[0x78 - 0x00]; // 0x00
	undefined4 m_unk0x78;             // 0x78
	undefined m_unk0x7c[0x80 - 0x7c]; // 0x7c
	undefined4 m_unk0x80;             // 0x80
	undefined m_unk0x84[0x88 - 0x84]; // 0x84
};

#endif // TANZANITEWISP0X88_H
