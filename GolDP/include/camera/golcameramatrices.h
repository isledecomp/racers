#ifndef GOLCAMERAMATRICES_H
#define GOLCAMERAMATRICES_H

#include "camera/goltransform.h"
#include "compat.h"
#include "types.h"

// SIZE 0x220
class GolCameraMatrices {
public:
	GolTransform m_transform;          // 0x00
	GolMatrix4 m_view;                 // 0xd0
	GolMatrix4 m_projection;           // 0x110
	GolMatrix4 m_screenProjection;     // 0x150
	GolMatrix4 m_viewProjection;       // 0x190
	GolMatrix4 m_viewScreenProjection; // 0x1d0
	LegoFloat m_viewportWidth;         // 0x210
	LegoFloat m_viewportHeight;        // 0x214
	LegoFloat m_viewportLeft;          // 0x218
	LegoFloat m_viewportTop;           // 0x21c
};

#endif // GOLCAMERAMATRICES_H
