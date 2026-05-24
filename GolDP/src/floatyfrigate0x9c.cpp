#include "floatyfrigate0x9c.h"

#include "whitefalcon0x140.h"

DECOMP_SIZE_ASSERT(FloatyFrigate0x9c, 0x9c)

// FUNCTION: GOLDP 0x1001ac70
FloatyFrigate0x9c::FloatyFrigate0x9c()
{
	m_boundingShapes[0] = NULL;
	m_boundingShapes[1] = NULL;
	m_boundingShapes[2] = NULL;
}

// FUNCTION: GOLDP 0x1001aca0
void FloatyFrigate0x9c::VTable0x60(IGdbModel0x40* p_model, BoundingShape0x2c* p_shape, LegoFloat p_modelDistance)
{
	FloatyCanoe0x90::VTable0x50(p_model, p_modelDistance);
	m_boundingShapes[0] = p_shape;
}

// FUNCTION: GOLDP 0x1001acd0
void FloatyFrigate0x9c::VTable0x54()
{
	m_boundingShapes[0] = NULL;
	m_boundingShapes[1] = NULL;
	m_boundingShapes[2] = NULL;
	FloatyCanoe0x90::VTable0x54();
}

// FUNCTION: GOLDP 0x1001acf0
void FloatyFrigate0x9c::FUN_1001acf0(IGdbModel0x40* p_model, BoundingShape0x2c* p_shape, LegoFloat p_modelDistance)
{
	LegoU32 i;

	for (i = 0; i < 2; i++) {
		if (m_models[i] == NULL) {
			break;
		}
		if (p_modelDistance < m_modelDistances[i]) {
			LegoU32 j;
			for (j = 2; j > i; j--) {
				m_models[j] = m_models[j - 1];
				m_boundingShapes[j] = m_boundingShapes[j - 1];
				m_modelDistances[j] = m_modelDistances[j - 1];
			}
			break;
		}
	}
	m_models[i] = p_model;
	m_boundingShapes[i] = p_shape;
	m_modelDistances[i] = p_modelDistance;
}

// FUNCTION: GOLDP 0x1001ad70
void FloatyFrigate0x9c::VTable0x1c(WhiteFalcon0x140& p_renderer)
{
	p_renderer.VTable0x90(this);
}
