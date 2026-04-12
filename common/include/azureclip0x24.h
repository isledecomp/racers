#ifndef AZURECLIP0X24_H
#define AZURECLIP0X24_H

#include "decomp.h"

// SIZE 0x24
class AzureClip0x24 {
public:
	AzureClip0x24();

private:
	undefined m_unk0x00;              // 0x00
	undefined m_unk0x01[0x0c - 0x01]; // 0x01
	undefined m_unk0x0c;              // 0x0c
	undefined m_unk0x0d[0x10 - 0x0d]; // 0x0d
	undefined4 m_unk0x10;             // 0x10
	undefined4 m_unk0x14;             // 0x14
	undefined4 m_unk0x18;             // 0x18
	undefined4 m_unk0x1c;             // 0x1c
	undefined4 m_unk0x20;             // 0x20
};

#endif // AZURECLIP0X24_H
