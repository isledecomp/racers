#include "floatyferry0xf4.h"

#include "cmbmodelpart0x34.h"
#include "cmbmodelpartdata0x28.h"
#include "float.h"
#include "igdbmodel0x40.h"

#include <math.h>

DECOMP_SIZE_ASSERT(FloatyFerry0xf4, 0xf4)

// GLOBAL: GOLDP 0x10056fc4
static const LegoFloat g_fltMax0x10056fc4 = FLT_MAX;

// FUNCTION: GOLDP 0x10023420
FloatyFerry0xf4::FloatyFerry0xf4()
{
	LegoU32 i;

	for (i = 0; i < sizeOfArray(m_nodes); i++) {
		m_nodes[i] = NULL;
		m_modelParts[i] = NULL;
		m_partIndices[i] = -1;
	}
	m_unk0xbc = 0;
	m_radius = -1.0f;
	m_unk0xb4 = 0;
	m_unk0xb8 = 0;
	m_unk0xd8 = 0;
	m_unk0xd0 = 0;
	m_unk0xd4 = 0;
	m_unk0xec = 0;
	m_unk0xf0 = 0;
}

// FUNCTION: GOLDP 0x10023490
void FloatyFerry0xf4::FUN_10023490(
	IGdbModel0x40* p_model,
	WhiteFalconNode0x18* p_node,
	CmbModelPart0x34* p_modelParts,
	LegoFloat p_modelDistance
)
{
	FloatyCanoe0x90::VTable0x50(p_model, p_modelDistance);
	m_nodes[0] = p_node;
	m_modelParts[0] = p_modelParts;
}

// FUNCTION: GOLDP 0x100234c0
void FloatyFerry0xf4::FUN_100234c0(
	WhiteFalconNode0x18* p_node,
	CmbModelPart0x34* p_modelParts,
	LegoFloat p_modelDistance
)
{
	m_modelDistances[0] = p_modelDistance;
	m_radius = 0.0f;
	m_unk0x60 = 0;
	m_unk0x62 = 0;
	m_unk0x64 = 0;
	m_unk0x68 = 0;
	m_unk0x58 = 1.0f;
	m_nodes[0] = p_node;
	m_modelParts[0] = p_modelParts;
	m_flags |= c_flagBit0;
}

// FUNCTION: GOLDP 0x10023510
void FloatyFerry0xf4::VTable0x54()
{
	LegoU32 i;

	FloatyCanoe0x90::VTable0x54();

	for (i = 0; i < sizeOfArray(m_nodes); i++) {
		m_nodes[i] = NULL;
		m_modelParts[i] = NULL;
		m_partIndices[i] = -1;
	}
	m_unk0xbc = 0;
	m_radius = -1.0f;
	m_unk0xb4 = 0;
	m_unk0xb8 = 0;
	m_unk0xd8 = 0;
	m_unk0xd0 = 0;
	m_unk0xd4 = 0;
	m_unk0xec = 0;
	m_unk0xf0 = 0;
}

// STUB: GOLDP 0x10023580
void FloatyFerry0xf4::VTable0x5c(LegoU32)
{
	// TODO
	STUB(0x10023580);
}

// STUB: GOLDP 0x10023940
void FloatyFerry0xf4::FUN_10023940(IGdbModel0x40*, WhiteFalconNode0x18*, CmbModelPart0x34*, LegoFloat)
{
	// TODO
	STUB(0x10023940);
}

// FUNCTION: GOLDP 0x100239e0
void FloatyFerry0xf4::FUN_100239e0(
	WhiteFalconNode0x18* p_node,
	CmbModelPart0x34* p_modelParts,
	LegoFloat p_modelDistance
)
{
	LegoU32 i;

	for (i = 0; i < 2; i++) {
		if (m_nodes[i] == NULL) {
			break;
		}
		if (p_modelDistance < m_modelDistances[i]) {
			LegoU32 j;
			for (j = 2; j > i; j--) {
				m_nodes[j] = m_nodes[j - 1];
				m_modelParts[j] = m_modelParts[j - 1];
				m_modelDistances[j] = m_modelDistances[j - 1];
			}
			break;
		}
	}
	m_nodes[i] = p_node;
	m_partIndices[i] = -1;
	m_modelParts[i] = p_modelParts;
	m_modelDistances[i] = p_modelDistance;
}

// FUNCTION: GOLDP 0x10023a70
void FloatyFerry0xf4::FUN_10023a70(LegoU32 p_partIndex)
{
	LegoS32 noPart = -1;

	m_partIndices[0] = noPart;
	m_partIndices[1] = noPart;
	m_partIndices[2] = noPart;
	LegoU32 flags = m_flags;
	m_unk0xbc = p_partIndex;
	flags &= ~c_flagsPartAnimationMask;
	flags |= c_flagBit18;
	p_partIndex &= 0xffff;
	m_flags = flags;

	CmbModelPart0x34* modelPart = m_modelParts[0];
	m_radius = -1.0f;
	m_unk0xb8 = modelPart->GetPartData()[p_partIndex].GetUnk0x00();
	m_unk0xb4 = 0;
	const GolVec3& position = modelPart->GetPartData()[p_partIndex].GetUnk0x04();
	m_unk0xc0 = position;
	m_velocity = position;
}

// STUB: GOLDP 0x10023b10
void FloatyFerry0xf4::VTable0x10(LegoS32)
{
	// TODO
	STUB(0x10023b10);
}

// STUB: GOLDP 0x10023ef0
void FloatyFerry0xf4::VTable0x4c(LegoU32 p_index)
{
	STUB(0x10023ef0);

	IGdbModel0x40* model = m_models[p_index];
	if (model == NULL) {
		FUN_10026fa0(0.0f);
		return;
	}

	GolVec3 center;
	LegoFloat radius;
	LegoFloat scale;
	if (m_flags & c_flagBit16) {
		CmbModelPartData0x28* partData = m_modelParts[p_index]->GetPartData();
		const GolVec4& bounds = partData[m_unk0xbc].GetBounds();
		center.m_x = bounds.m_x;
		center.m_y = bounds.m_y;
		center.m_z = bounds.m_z;
		radius = bounds.m_u;

		if (m_flags & c_flagBit17) {
			const GolVec4& bounds2 = partData[m_unk0xd8].GetBounds();
			GolVec3 center2;
			center2.m_x = bounds2.m_x;
			center2.m_y = bounds2.m_y;
			center2.m_z = bounds2.m_z;

			center = (center + center2) * 0.5f;
			if (radius < bounds2.m_u) {
				radius = bounds2.m_u;
			}

			LegoFloat deltaX = center.m_x - center2.m_x;
			LegoFloat deltaY = center.m_y - center2.m_y;
			LegoFloat deltaZ = center.m_z - center2.m_z;
			radius += static_cast<LegoFloat>(sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ));
		}

		scale = model->GetScale() * m_unk0x58;
	}
	else {
		center = model->GetBoundingCenter();
		radius = model->GetBoundingRadius();
		scale = m_unk0x58;
	}

	center *= scale;

	GolVec3 position;
	VTable0x2c(center, &position);
	FUN_10026f70(position);
	FUN_10026fa0(radius * scale);
}

// FUNCTION: GOLDP 0x100240b0
void FloatyFerry0xf4::VTable0x14(const WhiteFalconView0xcc& p_view, ResultStruct* p_result)
{
	LegoU32 i;
	LegoFloat* threshold;
	GolVec3 position;

	FUN_100286d0(&position);
	i = 0;
	threshold = m_modelDistances;
	if (*threshold != g_fltMax0x10056fc4) {
		LegoFloat distanceSquared = position.DistanceSquaredTo(p_view.m_position);
		for (; distanceSquared > *threshold;) {
			i++;
			threshold++;
			if (i >= 3) {
				p_result->m_visibility = 0;
				return;
			}
		}
	}
	p_result->m_lodIndex = i;
	if (m_models[i] == NULL) {
		p_result->m_visibility = 0;
	}
	else {
		if (i != 0) {
			VTable0x4c(i);
			FUN_100286d0(&position);
		}
		p_result->m_visibility = p_view.FUN_1002bc20(position, FUN_10028710());
	}
}

// FUNCTION: GOLDP 0x100241a0
WhiteFalconNode0x18* FloatyFerry0xf4::VTable0x58(LegoU32 p_arg1)
{
	return m_nodes[p_arg1];
}
