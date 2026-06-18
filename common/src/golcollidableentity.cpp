#include "golcollidableentity.h"

#include "golboundingshape.h"
#include "render/golrenderdevice.h"

DECOMP_SIZE_ASSERT(GolCollidableEntity, 0x9c)

// FUNCTION: GOLDP 0x1001ac70
GolCollidableEntity::GolCollidableEntity()
{
	m_boundingShapes[0] = NULL;
	m_boundingShapes[1] = NULL;
	m_boundingShapes[2] = NULL;
}

// FUNCTION: GOLDP 0x1001aca0
void GolCollidableEntity::VTable0x60(GolModelBase* p_model, GolBoundingShape* p_shape, LegoFloat p_modelDistance)
{
	GolModelEntity::VTable0x50(p_model, p_modelDistance);
	m_boundingShapes[0] = p_shape;
}

// FUNCTION: GOLDP 0x1001acd0
void GolCollidableEntity::VTable0x54()
{
	m_boundingShapes[0] = NULL;
	m_boundingShapes[1] = NULL;
	m_boundingShapes[2] = NULL;
	GolModelEntity::VTable0x54();
}

// FUNCTION: GOLDP 0x1001acf0
void GolCollidableEntity::FUN_1001acf0(GolModelBase* p_model, GolBoundingShape* p_shape, LegoFloat p_modelDistance)
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
void GolCollidableEntity::VTable0x1c(GolRenderDevice& p_renderer)
{
	p_renderer.VTable0x90(this);
}

// FUNCTION: LEGORACERS 0x00403c60
void GolCollidableEntity::FUN_00403c60()
{
	for (LegoU32 i = 0; i < sizeOfArray(m_boundingShapes); i++) {
		if (m_boundingShapes[i] != NULL) {
			m_boundingShapes[i]->FUN_00403f20();
		}
	}
	FUN_00411040();
}
