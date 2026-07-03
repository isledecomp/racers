#ifndef GOLCAMERAMATRICES_H
#define GOLCAMERAMATRICES_H

#include "camera/goltransform.h"
#include "compat.h"
#include "types.h"

// SIZE 0x220
class GolCameraMatrices {
public:
	GolTransform m_unk0x00; // 0x00
	GolMatrix4 m_unk0xd0;   // 0xd0
	GolMatrix4 m_unk0x110;  // 0x110
	GolMatrix4 m_unk0x150;  // 0x150
	GolMatrix4 m_unk0x190;  // 0x190
	GolMatrix4 m_unk0x1d0;  // 0x1d0
	LegoFloat m_unk0x210;   // 0x210
	LegoFloat m_unk0x214;   // 0x214
	LegoFloat m_unk0x218;   // 0x218
	LegoFloat m_unk0x21c;   // 0x21c
};

#endif // GOLCAMERAMATRICES_H
