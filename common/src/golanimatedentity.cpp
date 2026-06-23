#include "golanimatedentity.h"

#include "cmbmodelpart0x34.h"
#include "cmbmodelpartdata0x28.h"
#include "golmodelbase.h"
#include "golscenenode.h"
#include "goltransformbase.h"

#include <float.h>
#include <math.h>

DECOMP_SIZE_ASSERT(GolAnimatedEntity, 0xf4)

// GLOBAL: GOLDP 0x10056fc4
// GLOBAL: LEGORACERS 0x004af5e8
static const LegoFloat g_maxFloat = FLT_MAX;

// FUNCTION: GOLDP 0x10023420
// FUNCTION: LEGORACERS 0x0040d530
GolAnimatedEntity::GolAnimatedEntity()
{
	Reset();
}

// FUNCTION: GOLDP 0x10023490
// FUNCTION: LEGORACERS 0x0040d550
void GolAnimatedEntity::FUN_0040d550(
	GolModelBase* p_model,
	GolSceneNode* p_node,
	CmbModelPart0x34* p_modelParts,
	LegoFloat p_modelDistance
)
{
	GolModelEntity::VTable0x50(p_model, p_modelDistance);
	m_nodes[0] = p_node;
	m_modelParts[0] = p_modelParts;
}

// FUNCTION: GOLDP 0x100234c0
// FUNCTION: LEGORACERS 0x0040d580
void GolAnimatedEntity::FUN_100234c0(GolSceneNode* p_node, CmbModelPart0x34* p_modelParts, LegoFloat p_modelDistance)
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
// FUNCTION: LEGORACERS 0x0040d5d0
void GolAnimatedEntity::VTable0x54()
{
	GolModelEntity::VTable0x54();
	Reset();
}

// FUNCTION: LEGORACERS 0x0040d5f0
void GolAnimatedEntity::Reset()
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

// FUNCTION: LEGORACERS 0x0040d650
void GolAnimatedEntity::FUN_0040d650()
{
	LegoU32 i;

	for (i = 0; i < sizeOfArray(m_partIndices); i++) {
		m_partIndices[i] = -1;
	}
}

// STUB: GOLDP 0x10023580
// STUB: LEGORACERS 0x0040d670
void GolAnimatedEntity::VTable0x5c(LegoU32 p_index)
{
	if (!(m_flags & c_flagPartAnimation)) {
		return;
	}

	CmbModelPart0x34* modelPart = m_modelParts[p_index];
	if (m_unk0xbc >= modelPart->GetPartCount()) {
		return;
	}

	GolSceneNode* node = m_nodes[p_index];
	if (node->GetUpdateSerial() == static_cast<LegoU32>(m_partIndices[p_index])) {
		return;
	}

	m_partIndices[p_index] = node->AdvanceUpdateSerial();

	CmbModelPartData0x18& animationData = modelPart->GetAnimationData();
	const CmbModelPartData0x28& activePart = modelPart->GetPartData()[m_unk0xbc];
	LegoU32 activeTrackIndex = activePart.GetTrackIndex();
	LegoS32 activeFrameCount;
	LegoFloat activeTime;
	if (m_flags & c_flagLoopCurrentPart) {
		activeFrameCount = activePart.GetLoopFrameCount();
		activeTime = activePart.WrapTime(m_unk0xb4);
	}
	else {
		activeFrameCount = activePart.GetFrameCount();
		activeTime = m_unk0xb4;
	}

	LegoBool32 hasQueuedPart = FALSE;
	LegoU32 queuedTrackIndex = 0;
	LegoS32 queuedFrameCount = 0;
	LegoFloat queuedTime = 0.0f;
	if (m_flags & c_flagPartTransition) {
		if (m_unk0xd8 < modelPart->GetPartCount()) {
			const CmbModelPartData0x28& queuedPart = modelPart->GetPartData()[m_unk0xd8];
			queuedTrackIndex = queuedPart.GetTrackIndex();
			if (m_flags & c_flagLoopQueuedPart) {
				queuedFrameCount = queuedPart.GetLoopFrameCount();
				queuedTime = queuedPart.WrapTime(m_unk0xd0);
			}
			else {
				queuedFrameCount = queuedPart.GetFrameCount();
				queuedTime = m_unk0xd0;
			}
			hasQueuedPart = TRUE;
		}
	}

	for (LegoU32 i = 0; i < node->GetCapacity(); i++) {
		GolTransformBase* orbit = node->VTable0x18(i);

		GolVec3 activePosition;
		activePosition.m_x = 0.0f;
		activePosition.m_y = 0.0f;
		activePosition.m_z = 0.0f;
		GolQuat activeRotation;
		activeRotation.m_x = 0.0f;
		activeRotation.m_y = 0.0f;
		activeRotation.m_z = 0.0f;
		activeRotation.m_w = 1.0f;
		GolVec3 queuedPosition;
		queuedPosition.m_x = 0.0f;
		queuedPosition.m_y = 0.0f;
		queuedPosition.m_z = 0.0f;
		GolQuat queuedRotation;
		queuedRotation.m_x = 0.0f;
		queuedRotation.m_y = 0.0f;
		queuedRotation.m_z = 0.0f;
		queuedRotation.m_w = 1.0f;
		LegoBool32 hasActivePosition = animationData.InterpolatePosition(
			&activePosition,
			modelPart->GetTrack(activeTrackIndex + i),
			activeTime,
			activeFrameCount
		);
		LegoBool32 hasActiveRotation = animationData.InterpolateRotation(
			&activeRotation,
			modelPart->GetTrack(activeTrackIndex + i),
			activeTime,
			activeFrameCount
		);

		LegoBool32 hasQueuedPosition = FALSE;
		LegoBool32 hasQueuedRotation = FALSE;
		if (hasQueuedPart) {
			hasQueuedPosition = animationData.InterpolatePosition(
				&queuedPosition,
				modelPart->GetTrack(queuedTrackIndex + i),
				queuedTime,
				queuedFrameCount
			);
			hasQueuedRotation = animationData.InterpolateRotation(
				&queuedRotation,
				modelPart->GetTrack(queuedTrackIndex + i),
				queuedTime,
				queuedFrameCount
			);
		}

		if (hasActivePosition) {
			if (hasQueuedPosition) {
				GolVec3 blendedPosition;
				blendedPosition.m_x = activePosition.m_x + (queuedPosition.m_x - activePosition.m_x) * m_unk0xec;
				blendedPosition.m_y = activePosition.m_y + (queuedPosition.m_y - activePosition.m_y) * m_unk0xec;
				blendedPosition.m_z = activePosition.m_z + (queuedPosition.m_z - activePosition.m_z) * m_unk0xec;
				orbit->SetPosition(&blendedPosition);
			}
			else {
				orbit->SetPosition(&activePosition);
			}
		}
		else if (hasQueuedPosition) {
			orbit->SetPosition(&queuedPosition);
		}

		if (hasActiveRotation) {
			if (hasQueuedRotation) {
				GolQuat blendedRotation;
				GolMath::FUN_1002f890(activeRotation, queuedRotation, m_unk0xec, &blendedRotation);
				orbit->VTable0x2c(&blendedRotation.m_x);
			}
			else {
				orbit->VTable0x2c(&activeRotation.m_x);
			}
		}
		else if (hasQueuedRotation) {
			orbit->VTable0x2c(&queuedRotation.m_x);
		}
	}
}

// FUNCTION: GOLDP 0x10023940
// FUNCTION: LEGORACERS 0x0040da30
void GolAnimatedEntity::FUN_10023940(
	GolModelBase* p_model,
	GolSceneNode* p_node,
	CmbModelPart0x34* p_modelParts,
	LegoFloat p_modelDistance
)
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
				m_nodes[j] = m_nodes[j - 1];
				m_modelParts[j] = m_modelParts[j - 1];
				m_modelDistances[j] = m_modelDistances[j - 1];
			}
			break;
		}
	}

	m_models[i] = p_model;
	m_nodes[i] = p_node;
	m_partIndices[i] = -1;
	m_modelParts[i] = p_modelParts;
	m_modelDistances[i] = p_modelDistance;
}

// FUNCTION: GOLDP 0x100239e0
void GolAnimatedEntity::FUN_100239e0(GolSceneNode* p_node, CmbModelPart0x34* p_modelParts, LegoFloat p_modelDistance)
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

// FUNCTION: LEGORACERS 0x0040dad0
void GolAnimatedEntity::FUN_0040dad0(LegoU32 p_partIndex)
{
	FUN_0040dae0(p_partIndex, 0);
}

// FUNCTION: LEGORACERS 0x0040dae0
void GolAnimatedEntity::FUN_0040dae0(LegoU32 p_partIndex, LegoS32 p_timeScale)
{
	FUN_0040d650();

	LegoU32 flags = m_flags;
	flags &= ~c_flagsPartAnimationMask;
	m_unk0xbc = p_partIndex;
	flags |= c_flagLoopCurrentPart;
	p_partIndex &= 0xffff;
	m_flags = flags;

	CmbModelPart0x34* modelPart = m_modelParts[0];
	m_radius = -1.0f;
	LegoFloat rate = modelPart->GetPartData()[p_partIndex].GetUnk0x00();
	m_unk0xb8 = rate;
	if (p_timeScale != 0) {
		LegoFloat timeScale = static_cast<LegoFloat>(p_timeScale);
		rate *= timeScale;
	}
	else {
		rate = 0.0f;
	}
	m_unk0xb4 = rate;

	const GolVec3& offset = modelPart->GetPartData()[p_partIndex].GetUnk0x04();
	m_unk0xc0 = offset;
	m_velocity = offset;
}

// GOLDP compiles the time-scale-0 start as a single, standalone function, whereas
// LEGORACERS factors it into FUN_0040dad0 -> FUN_0040dae0 -> FUN_0040d650.
// The GOLDP call is probably also to FUN_0040dad0, but inlining isn't right.
// FUNCTION: GOLDP 0x10023a70
void GolAnimatedEntity::FUN_10023a70(LegoU32 p_partIndex)
{
	FUN_0040d650();

	LegoU32 flags = m_flags;
	flags &= ~c_flagsPartAnimationMask;
	m_unk0xbc = p_partIndex;
	flags |= c_flagLoopCurrentPart;
	p_partIndex &= 0xffff;
	m_flags = flags;

	CmbModelPart0x34* modelPart = m_modelParts[0];
	m_radius = -1.0f;
	LegoFloat rate = modelPart->GetPartData()[p_partIndex].GetUnk0x00();
	m_unk0xb8 = rate;
	rate = 0.0f;
	m_unk0xb4 = rate;

	const GolVec3& offset = modelPart->GetPartData()[p_partIndex].GetUnk0x04();
	m_unk0xc0 = offset;
	m_velocity = offset;
}

// FUNCTION: LEGORACERS 0x0040db80
void GolAnimatedEntity::FUN_0040db80(
	LegoU32 p_partIndex,
	LegoS32 p_transitionTime,
	LegoFloat p_time,
	LegoBool32 p_updateCurrent,
	LegoBool32 p_updateQueued,
	LegoBool32 p_loop
)
{
	FUN_0040d650();
	if (p_transitionTime == 0) {
		LegoS32 timeScale;
		if (p_time != 0.0f) {
			const CmbModelPartData0x28& activePart = m_modelParts[0]->GetPartData()[m_unk0xbc];
			timeScale = static_cast<LegoS32>(p_time / activePart.GetUnk0x00());
		}
		else {
			timeScale = 0;
		}

		FUN_0040dae0(p_partIndex, timeScale);
		if (!p_loop) {
			m_flags &= ~c_flagLoopCurrentPart;
		}
		return;
	}

	LegoU32 flags = m_flags;
	LegoU32 currentPartIndex = (flags & c_flagPartTransition) ? m_unk0xd8 : m_unk0xbc;
	if (p_partIndex == currentPartIndex) {
		return;
	}

	if (flags & c_flagPartTransition) {
		m_unk0xb8 = m_unk0xd4;
		m_unk0xb4 = m_unk0xd0;
		m_unk0xbc = m_unk0xd8;
		m_radius = -1.0f;
		m_unk0xc0 = m_unk0xdc;
		m_velocity = m_unk0xdc;
		if (flags & c_flagLoopQueuedPart) {
			flags |= c_flagLoopCurrentPart;
		}
		else {
			flags &= ~c_flagLoopCurrentPart;
		}
		m_flags = flags;
	}

	flags = m_flags;
	flags &= ~0x00580000;
	flags |= c_flagPartTransition;
	m_unk0xd8 = static_cast<LegoU16>(p_partIndex);
	m_flags = flags;
	if (p_loop) {
		flags |= c_flagLoopQueuedPart;
		m_flags = flags;
	}

	LegoU32 queuedPartIndex = static_cast<LegoU16>(p_partIndex);
	LegoBool32 updateQueued = p_updateQueued;
	m_unk0xd4 = m_modelParts[0]->GetPartData()[queuedPartIndex].GetUnk0x00();
	m_unk0xec = 0.0f;
	m_unk0xd0 = p_time;
	LegoBool32 updateCurrent = p_updateCurrent;
	m_unk0xcc = updateCurrent;
	m_unk0xe8 = updateQueued;
	m_unk0xf0 = 1.0f / static_cast<LegoFloat>(p_transitionTime);
	if (!updateCurrent) {
		m_unk0xc0.m_x = 0.0f;
		m_unk0xc0.m_y = 0.0f;
		m_unk0xc0.m_z = 0.0f;
	}

	m_unk0xdc = m_modelParts[0]->GetPartData()[queuedPartIndex].GetUnk0x04();
}

// STUB: GOLDP 0x10023b10
// STUB: LEGORACERS 0x0040dd60
void GolAnimatedEntity::VTable0x10(LegoS32 p_elapsed)
{
	m_flags &= ~c_flagLoopWrapped;
	if (!(m_flags & c_flagPartAnimation)) {
		GolModelEntity::VTable0x10(p_elapsed);
		return;
	}

	FUN_0040d650();
	LegoU32 flags = m_flags;
	if (flags & c_flagPartTransition) {
		m_radius = -1.0f;
		LegoFloat elapsed = static_cast<LegoFloat>(p_elapsed);
		m_unk0xec += m_unk0xf0 * elapsed;
		if (m_unk0xec >= 1.0f) {
			LegoS32 consumed = static_cast<LegoS32>((m_unk0xec - 1.0f) / m_unk0xf0);
			p_elapsed -= consumed;

			m_unk0xb8 = m_unk0xd4;
			m_unk0xb4 = m_unk0xd0;
			m_unk0xbc = m_unk0xd8;
			m_unk0xc0 = m_unk0xdc;
			m_velocity = m_unk0xdc;

			flags &= ~(c_flagPartTransition | c_flagLoopCurrentPart | c_flagRestartQueuedPart);
			if (flags & c_flagLoopQueuedPart) {
				flags |= c_flagLoopCurrentPart;
			}
			m_flags = flags;
		}
		else {
			if (m_unk0xcc) {
				const CmbModelPartData0x28& activePart = m_modelParts[0]->GetPartData()[m_unk0xbc];
				m_unk0xb4 += m_unk0xb8 * elapsed;
				LegoFloat endFrame = static_cast<LegoFloat>(activePart.GetFrameCount() - 1);
				if (m_unk0xb4 > endFrame) {
					if (flags & c_flagLoopCurrentPart) {
						m_unk0xb4 = activePart.WrapTime(m_unk0xb4);
					}
					else {
						m_unk0xb4 = endFrame;
					}
				}
			}

			if (m_unk0xe8) {
				const CmbModelPartData0x28& queuedPart = m_modelParts[0]->GetPartData()[m_unk0xd8];
				m_unk0xd0 += m_unk0xd4 * elapsed;
				LegoFloat endFrame = static_cast<LegoFloat>(queuedPart.GetFrameCount() - 1);
				if (m_unk0xd0 > endFrame) {
					if (m_flags & c_flagLoopQueuedPart) {
						m_unk0xd0 = queuedPart.WrapTime(m_unk0xd0);
					}
					else {
						m_unk0xd0 = endFrame;
					}
				}
			}

			m_velocity = m_unk0xdc - m_unk0xc0;
			m_velocity = m_unk0xc0 + (m_velocity * m_unk0xec);
		}
	}

	if (m_flags & c_flagPartTransition) {
		GolModelEntity::VTable0x10(p_elapsed);
		return;
	}

	const CmbModelPartData0x28& activePart = m_modelParts[0]->GetPartData()[m_unk0xbc];
	m_unk0xb4 += m_unk0xb8 * static_cast<LegoFloat>(p_elapsed);
	LegoFloat endFrame = static_cast<LegoFloat>(activePart.GetFrameCount() - 1);
	if (m_unk0xb4 >= endFrame) {
		if (m_flags & c_flagLoopCurrentPart) {
			LegoFloat oldTime = m_unk0xb4;
			m_unk0xb4 = activePart.WrapTime(m_unk0xb4);
			if (m_unk0xb4 < oldTime) {
				m_flags |= c_flagLoopWrapped;
			}
		}
		else {
			if (m_flags & c_flagRestartQueuedPart) {
				FUN_0040dad0(m_unk0xd8);
			}
			else {
				m_unk0xb4 = endFrame;
			}
			m_flags |= c_flagPartAnimationDone;
		}
	}

	GolModelEntity::VTable0x10(p_elapsed);
}

// STUB: GOLDP 0x10023ef0
// STUB: LEGORACERS 0x0040e0b0
void GolAnimatedEntity::VTable0x4c(LegoU32 p_index)
{
	GolModelBase* model = m_models[p_index];
	if (model == NULL) {
		FUN_10026fa0(0.0f);
		return;
	}

	GolVec3 center;
	LegoFloat radius;
	LegoFloat scale;
	if (m_flags & c_flagPartAnimation) {
		CmbModelPartData0x28* partData = m_modelParts[p_index]->GetPartData();
		const GolVec4& bounds = partData[m_unk0xbc].GetBounds();
		center.m_x = bounds.m_x;
		center.m_y = bounds.m_y;
		center.m_z = bounds.m_z;
		radius = bounds.m_u;

		if (m_flags & c_flagPartTransition) {
			const GolVec4& bounds2 = partData[m_unk0xd8].GetBounds();
			GolVec3 center2;
			center2.m_x = bounds2.m_x;
			center2.m_y = bounds2.m_y;
			center2.m_z = bounds2.m_z;

			center = (center + center2) * 0.5f;
			if (radius < bounds2.m_u) {
				radius = bounds2.m_u;
			}

			GolVec3 delta = center - center2;
			radius +=
				static_cast<LegoFloat>(sqrt(delta.m_x * delta.m_x + delta.m_y * delta.m_y + delta.m_z * delta.m_z));
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
// FUNCTION: LEGORACERS 0x0040e270
void GolAnimatedEntity::VTable0x14(const GolViewFrustum& p_view, ResultStruct* p_result)
{
	GolVec3 position;
	FUN_100286d0(&position);

	LegoU32 i = 0;
	LegoFloat* threshold = m_modelDistances;
	if (*threshold != g_maxFloat) {
		LegoFloat distanceSquared = position.DistanceSquaredTo(p_view.m_position);
		for (; distanceSquared > *threshold;) {
			i++;
			threshold++;
			if (i >= sizeOfArray(m_models)) {
				p_result->m_visibility = 0;
				return;
			}
		}
	}

	p_result->m_lodIndex = i;
	if (m_models[i] == NULL) {
		p_result->m_visibility = 0;
		return;
	}

	if (i != 0) {
		VTable0x4c(i);
		FUN_100286d0(&position);
	}
	p_result->m_visibility = p_view.ClassifySphere(position, FUN_10028710());
}

// FUNCTION: LEGORACERS 0x0040e360
LegoBool32 GolAnimatedEntity::FUN_0040e360()
{
	LegoU32 flags = m_flags;
	const CmbModelPartData0x28& activePart = m_modelParts[0]->GetPartData()[m_unk0xbc];

	return (flags & c_flagPartAnimationDone) ||
		   (!(flags & c_flagLoopCurrentPart) && static_cast<LegoFloat>(activePart.GetFrameCount() - 1) <= m_unk0xb4);
}

// STUB: LEGORACERS 0x0040e3c0
void GolAnimatedEntity::FUN_0040e3c0(
	LegoU32 p_modelIndex,
	LegoU32 p_trackOffset,
	LegoU32 p_partDataIndex,
	LegoS32 p_frame,
	GolVec3* p_dest
)
{
	LegoFloat timeScale = m_unk0xb8;
	CmbModelPart0x34* modelPart = m_modelParts[p_modelIndex];
	CmbModelPartData0x28* partData = modelPart->GetPartData();
	CmbModelPartData0x18& animationData = modelPart->GetAnimationData();
	LegoFloat time = static_cast<LegoFloat>(p_frame) * timeScale;
	const CmbModelPartData0x28& part = partData[p_partDataIndex];
	LegoU32 trackIndex = part.GetTrackIndex();
	trackIndex += p_trackOffset;
	const CmbModelPartTrack0x14& track = modelPart->GetTrack(trackIndex);
	LegoS32 frameCount = part.GetFrameCount();

	animationData.InterpolatePosition(p_dest, track, time, frameCount);
}

// STUB: LEGORACERS 0x0040e420
void GolAnimatedEntity::FUN_0040e420(
	LegoU32 p_modelIndex,
	LegoU32 p_trackOffset,
	LegoU32 p_partDataIndex,
	LegoS32 p_frame,
	GolQuat* p_dest
)
{
	LegoFloat timeScale = m_unk0xb8;
	CmbModelPart0x34* modelPart = m_modelParts[p_modelIndex];
	CmbModelPartData0x28* partData = modelPart->GetPartData();
	CmbModelPartData0x18& animationData = modelPart->GetAnimationData();
	LegoFloat time = static_cast<LegoFloat>(p_frame) * timeScale;
	const CmbModelPartData0x28& part = partData[p_partDataIndex];
	LegoU32 trackIndex = part.GetTrackIndex();
	trackIndex += p_trackOffset;
	const CmbModelPartTrack0x14& track = modelPart->GetTrack(trackIndex);
	LegoS32 frameCount = part.GetFrameCount();

	animationData.InterpolateRotation(p_dest, track, time, frameCount);
}

// FUNCTION: GOLDP 0x100241a0
// FUNCTION: LEGORACERS 0x0040e480
GolSceneNode* GolAnimatedEntity::VTable0x58(LegoU32 p_arg1)
{
	return m_nodes[p_arg1];
}
