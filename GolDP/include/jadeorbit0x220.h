#ifndef JADEORBIT0X220_H
#define JADEORBIT0X220_H

#include "compat.h"
#include "jadeorbit0xd0.h"
#include "types.h"

// SIZE 0x220
class JadeOrbit0x220 {
public:
	JadeOrbit0xd0 m_unk0x00; // 0x00
	GolMatrix4 m_unk0xd0;    // 0xd0
	GolMatrix4 m_unk0x110;   // 0x110
	GolMatrix4 m_unk0x150;   // 0x150
	GolMatrix4 m_unk0x190;   // 0x190
	GolMatrix4 m_unk0x1d0;   // 0x1d0
	LegoFloat m_unk0x210;    // 0x210
	LegoFloat m_unk0x214;    // 0x214
	LegoFloat m_unk0x218;    // 0x218
	LegoFloat m_unk0x21c;    // 0x21c
};

#endif // JADEORBIT0X220_H
