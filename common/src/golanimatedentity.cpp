#include "golanimatedentity.h"

#include "cmbmodelpart.h"
#include "cmbmodelpartdata.h"
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
void GolAnimatedEntity::SetModel(
	GolModelBase* p_model,
	GolSceneNode* p_node,
	CmbModelPart* p_modelParts,
	LegoFloat p_modelDistance
)
{
	GolModelEntity::SetPrimaryModel(p_model, p_modelDistance);
	m_nodes[0] = p_node;
	m_modelParts[0] = p_modelParts;
}

// FUNCTION: GOLDP 0x100234c0
// FUNCTION: LEGORACERS 0x0040d580
void GolAnimatedEntity::SetNode(GolSceneNode* p_node, CmbModelPart* p_modelParts, LegoFloat p_modelDistance)
{
	m_modelDistances[0] = p_modelDistance;
	m_radius = 0.0f;
	m_textureScrollU = 0;
	m_textureScrollV = 0;
	m_textureScrollSpeedU = 0;
	m_textureScrollSpeedV = 0;
	m_scale = 1.0f;
	m_nodes[0] = p_node;
	m_modelParts[0] = p_modelParts;
	m_flags |= c_flagBit0;
}

// FUNCTION: GOLDP 0x10023510
// FUNCTION: LEGORACERS 0x0040d5d0
void GolAnimatedEntity::ResetModelState()
{
	GolModelEntity::ResetModelState();
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

	m_currentPartIndex = 0;
	m_radius = -1.0f;
	m_partTimeMs = 0;
	m_msPerFrame = 0;
	m_queuedPartIndex = 0;
	m_queuedPartTimeMs = 0;
	m_queuedMsPerFrame = 0;
	m_transitionProgress = 0;
	m_transitionRate = 0;
}

// FUNCTION: LEGORACERS 0x0040d650
void GolAnimatedEntity::ResetPartIndices()
{
	LegoU32 i;

	for (i = 0; i < sizeOfArray(m_partIndices); i++) {
		m_partIndices[i] = -1;
	}
}

// STUB: GOLDP 0x10023580
// STUB: LEGORACERS 0x0040d670
void GolAnimatedEntity::ApplyPartAnimation(LegoU32 p_index)
{
	if (!(m_flags & c_flagPartAnimation)) {
		return;
	}

	CmbModelPart* modelPart = m_modelParts[p_index];
	if (m_currentPartIndex >= modelPart->GetPartCount()) {
		return;
	}

	GolSceneNode* node = m_nodes[p_index];
	if (node->GetUpdateSerial() == static_cast<LegoU32>(m_partIndices[p_index])) {
		return;
	}

	m_partIndices[p_index] = node->AdvanceUpdateSerial();

	CmbModelPartTrackData& animationData = modelPart->GetAnimationData();
	const CmbModelPartData& activePart = modelPart->GetPartData()[m_currentPartIndex];
	LegoU32 activeTrackIndex = activePart.GetTrackIndex();
	LegoS32 activeFrameCount;
	LegoFloat activeTime;
	if (m_flags & c_flagLoopCurrentPart) {
		activeFrameCount = activePart.GetLoopFrameCount();
		activeTime = activePart.WrapTime(m_partTimeMs);
	}
	else {
		activeFrameCount = activePart.GetFrameCount();
		activeTime = m_partTimeMs;
	}

	LegoBool32 hasQueuedPart = FALSE;
	LegoU32 queuedTrackIndex = 0;
	LegoS32 queuedFrameCount = 0;
	LegoFloat queuedTime = 0.0f;
	if (m_flags & c_flagPartTransition) {
		if (m_queuedPartIndex < modelPart->GetPartCount()) {
			const CmbModelPartData& queuedPart = modelPart->GetPartData()[m_queuedPartIndex];
			queuedTrackIndex = queuedPart.GetTrackIndex();
			if (m_flags & c_flagLoopQueuedPart) {
				queuedFrameCount = queuedPart.GetLoopFrameCount();
				queuedTime = queuedPart.WrapTime(m_queuedPartTimeMs);
			}
			else {
				queuedFrameCount = queuedPart.GetFrameCount();
				queuedTime = m_queuedPartTimeMs;
			}
			hasQueuedPart = TRUE;
		}
	}

	for (LegoU32 i = 0; i < node->GetCapacity(); i++) {
		GolTransformBase* orbit = node->GetTransform(i);

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
				blendedPosition.m_x =
					activePosition.m_x + (queuedPosition.m_x - activePosition.m_x) * m_transitionProgress;
				blendedPosition.m_y =
					activePosition.m_y + (queuedPosition.m_y - activePosition.m_y) * m_transitionProgress;
				blendedPosition.m_z =
					activePosition.m_z + (queuedPosition.m_z - activePosition.m_z) * m_transitionProgress;
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
				GolMath::LerpQuat(activeRotation, queuedRotation, m_transitionProgress, &blendedRotation);
				orbit->SetRotation(&blendedRotation.m_x);
			}
			else {
				orbit->SetRotation(&activeRotation.m_x);
			}
		}
		else if (hasQueuedRotation) {
			orbit->SetRotation(&queuedRotation.m_x);
		}
	}
}

// FUNCTION: GOLDP 0x10023940
// FUNCTION: LEGORACERS 0x0040da30
void GolAnimatedEntity::AddModel(
	GolModelBase* p_model,
	GolSceneNode* p_node,
	CmbModelPart* p_modelParts,
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
void GolAnimatedEntity::AddNode(GolSceneNode* p_node, CmbModelPart* p_modelParts, LegoFloat p_modelDistance)
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
void GolAnimatedEntity::PlayPart(LegoU32 p_partIndex)
{
	PlayPartScaled(p_partIndex, 0);
}

// FUNCTION: LEGORACERS 0x0040dae0
void GolAnimatedEntity::PlayPartScaled(LegoU32 p_partIndex, LegoS32 p_timeScale)
{
	ResetPartIndices();

	LegoU32 flags = m_flags;
	flags &= ~c_flagsPartAnimationMask;
	m_currentPartIndex = p_partIndex;
	flags |= c_flagLoopCurrentPart;
	p_partIndex &= 0xffff;
	m_flags = flags;

	CmbModelPart* modelPart = m_modelParts[0];
	m_radius = -1.0f;
	LegoFloat rate = modelPart->GetPartData()[p_partIndex].GetMsPerFrame();
	m_msPerFrame = rate;
	if (p_timeScale != 0) {
		LegoFloat timeScale = static_cast<LegoFloat>(p_timeScale);
		rate *= timeScale;
	}
	else {
		rate = 0.0f;
	}
	m_partTimeMs = rate;

	const GolVec3& offset = modelPart->GetPartData()[p_partIndex].GetVelocity();
	m_currentPartVelocity = offset;
	m_velocity = offset;
}

// GOLDP compiles the time-scale-0 start as a single, standalone function, whereas
// LEGORACERS factors it into 0x0040dad0 -> 0x0040dae0 -> 0x0040d650 (unannotated
// helpers). The GOLDP call is probably also to the first one, but inlining isn't right.
// FUNCTION: GOLDP 0x10023a70
void GolAnimatedEntity::PlayPartDirect(LegoU32 p_partIndex)
{
	ResetPartIndices();

	LegoU32 flags = m_flags;
	flags &= ~c_flagsPartAnimationMask;
	m_currentPartIndex = p_partIndex;
	flags |= c_flagLoopCurrentPart;
	p_partIndex &= 0xffff;
	m_flags = flags;

	CmbModelPart* modelPart = m_modelParts[0];
	m_radius = -1.0f;
	LegoFloat rate = modelPart->GetPartData()[p_partIndex].GetMsPerFrame();
	m_msPerFrame = rate;
	rate = 0.0f;
	m_partTimeMs = rate;

	const GolVec3& offset = modelPart->GetPartData()[p_partIndex].GetVelocity();
	m_currentPartVelocity = offset;
	m_velocity = offset;
}

// FUNCTION: LEGORACERS 0x0040db80
void GolAnimatedEntity::TransitionToPart(
	LegoU32 p_partIndex,
	LegoS32 p_transitionTime,
	LegoFloat p_time,
	LegoBool32 p_updateCurrent,
	LegoBool32 p_updateQueued,
	LegoBool32 p_loop
)
{
	ResetPartIndices();
	if (p_transitionTime == 0) {
		LegoS32 timeScale;
		if (p_time != 0.0f) {
			const CmbModelPartData& activePart = m_modelParts[0]->GetPartData()[m_currentPartIndex];
			timeScale = static_cast<LegoS32>(p_time / activePart.GetMsPerFrame());
		}
		else {
			timeScale = 0;
		}

		PlayPartScaled(p_partIndex, timeScale);
		if (!p_loop) {
			m_flags &= ~c_flagLoopCurrentPart;
		}
		return;
	}

	LegoU32 flags = m_flags;
	LegoU32 currentPartIndex = (flags & c_flagPartTransition) ? m_queuedPartIndex : m_currentPartIndex;
	if (p_partIndex == currentPartIndex) {
		return;
	}

	if (flags & c_flagPartTransition) {
		m_msPerFrame = m_queuedMsPerFrame;
		m_partTimeMs = m_queuedPartTimeMs;
		m_currentPartIndex = m_queuedPartIndex;
		m_radius = -1.0f;
		m_currentPartVelocity = m_queuedPartVelocity;
		m_velocity = m_queuedPartVelocity;
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
	m_queuedPartIndex = static_cast<LegoU16>(p_partIndex);
	m_flags = flags;
	if (p_loop) {
		flags |= c_flagLoopQueuedPart;
		m_flags = flags;
	}

	LegoU32 queuedPartIndex = static_cast<LegoU16>(p_partIndex);
	LegoBool32 updateQueued = p_updateQueued;
	m_queuedMsPerFrame = m_modelParts[0]->GetPartData()[queuedPartIndex].GetMsPerFrame();
	m_transitionProgress = 0.0f;
	m_queuedPartTimeMs = p_time;
	LegoBool32 updateCurrent = p_updateCurrent;
	m_advanceCurrent = updateCurrent;
	m_advanceQueued = updateQueued;
	m_transitionRate = 1.0f / static_cast<LegoFloat>(p_transitionTime);
	if (!updateCurrent) {
		m_currentPartVelocity.m_x = 0.0f;
		m_currentPartVelocity.m_y = 0.0f;
		m_currentPartVelocity.m_z = 0.0f;
	}

	m_queuedPartVelocity = m_modelParts[0]->GetPartData()[queuedPartIndex].GetVelocity();
}

// FUNCTION: GOLDP 0x10023b10
// STUB: LEGORACERS 0x0040dd60
void GolAnimatedEntity::Update(LegoS32 p_elapsed)
{
	m_flags &= ~c_flagLoopWrapped;
	if (m_flags & c_flagPartAnimation) {
		ResetPartIndices();
		LegoU32 flags = m_flags;
		if (flags & c_flagPartTransition) {
			m_radius = -1.0f;
			LegoFloat elapsed = static_cast<LegoFloat>(p_elapsed);
			m_transitionProgress += m_transitionRate * elapsed;
			if (m_transitionProgress >= 1.0f) {
				LegoFloat consumed = (m_transitionProgress - 1.0f) / m_transitionRate;

				m_msPerFrame = m_queuedMsPerFrame;
				m_partTimeMs = m_queuedPartTimeMs;
				m_currentPartIndex = m_queuedPartIndex;
				m_currentPartVelocity = m_queuedPartVelocity;
				m_velocity = m_queuedPartVelocity;

				flags &= ~(c_flagPartTransition | c_flagLoopCurrentPart | c_flagRestartQueuedPart);
				m_flags = flags;
				p_elapsed -= static_cast<LegoS32>(consumed);
				if (flags & c_flagLoopQueuedPart) {
					flags |= c_flagLoopCurrentPart;
					m_flags = flags;
				}
			}
			else {
				if (m_advanceCurrent) {
					const CmbModelPartData& activePart = m_modelParts[0]->GetPartData()[m_currentPartIndex];
					LegoFloat activeRate = m_msPerFrame;
					m_partTimeMs += activeRate * elapsed;
					LegoFloat endFrame = static_cast<LegoFloat>(activePart.GetFrameCount() - 1);
					if (m_partTimeMs > endFrame) {
						if (flags & c_flagLoopCurrentPart) {
							m_partTimeMs = activePart.WrapTime(m_partTimeMs);
						}
						else {
							m_partTimeMs = endFrame;
						}
					}
				}

				if (m_advanceQueued) {
					const CmbModelPartData& queuedPart = m_modelParts[0]->GetPartData()[m_queuedPartIndex];
					LegoFloat queuedRate = m_queuedMsPerFrame;
					m_queuedPartTimeMs += queuedRate * elapsed;
					LegoFloat endFrame = static_cast<LegoFloat>(queuedPart.GetFrameCount() - 1);
					if (m_queuedPartTimeMs > endFrame) {
						if (m_flags & c_flagLoopQueuedPart) {
							m_queuedPartTimeMs = queuedPart.WrapTime(m_queuedPartTimeMs);
						}
						else {
							m_queuedPartTimeMs = endFrame;
						}
					}
				}

				GolVec3* velocity = &m_velocity;
				velocity->m_x = m_queuedPartVelocity.m_x - m_currentPartVelocity.m_x;
				velocity->m_y = m_queuedPartVelocity.m_y - m_currentPartVelocity.m_y;
				velocity->m_z = m_queuedPartVelocity.m_z - m_currentPartVelocity.m_z;
				GolVec3 blendedVelocity;
				blendedVelocity.m_x = velocity->m_x * m_transitionProgress;
				blendedVelocity.m_y = velocity->m_y * m_transitionProgress;
				blendedVelocity.m_z = velocity->m_z * m_transitionProgress;
				velocity->m_x = m_currentPartVelocity.m_x + blendedVelocity.m_x;
				velocity->m_y = m_currentPartVelocity.m_y + blendedVelocity.m_y;
				velocity->m_z = m_currentPartVelocity.m_z + blendedVelocity.m_z;
			}
		}

		if (!(m_flags & c_flagPartTransition)) {
			const CmbModelPartData& activePart = m_modelParts[0]->GetPartData()[m_currentPartIndex];
			m_partTimeMs += m_msPerFrame * static_cast<LegoFloat>(p_elapsed);
			LegoFloat currentTime = m_partTimeMs;
			LegoFloat endFrame = static_cast<LegoFloat>(activePart.GetFrameCount() - 1);
			if (m_partTimeMs >= endFrame) {
				if (m_flags & c_flagLoopCurrentPart) {
					LegoFloat wrappedTime = activePart.WrapTime(currentTime);
					if (wrappedTime < m_partTimeMs) {
						m_flags |= c_flagLoopWrapped;
					}

					m_partTimeMs = wrappedTime;
					GolModelEntity::Update(p_elapsed);
					return;
				}
				else {
					if (m_flags & c_flagRestartQueuedPart) {
#ifdef BUILDING_GOL
						PlayPartDirect(m_queuedPartIndex);
#else
						PlayPart(m_queuedPartIndex);
#endif
					}
					else {
						m_partTimeMs = endFrame;
					}
					m_flags |= c_flagPartAnimationDone;
				}
			}
		}
	}

	GolModelEntity::Update(p_elapsed);
}

// STUB: GOLDP 0x10023ef0
// STUB: LEGORACERS 0x0040e0b0
void GolAnimatedEntity::ComputeBoundsFromModel(LegoU32 p_index)
{
	GolModelBase* model = m_models[p_index];
	if (model == NULL) {
		SetBoundsRadius(0.0f);
		return;
	}

	GolVec3 center;
	LegoFloat radius;
	LegoFloat scale;
	if (m_flags & c_flagPartAnimation) {
		CmbModelPartData* partData = m_modelParts[p_index]->GetPartData();
		const GolVec4& bounds = partData[m_currentPartIndex].GetBounds();
		center.m_x = bounds.m_x;
		center.m_y = bounds.m_y;
		center.m_z = bounds.m_z;
		radius = bounds.m_u;

		if (m_flags & c_flagPartTransition) {
			const GolVec4& bounds2 = partData[m_queuedPartIndex].GetBounds();
			GolVec3 center2;
			center2.m_x = bounds2.m_x;
			center2.m_y = bounds2.m_y;
			center2.m_z = bounds2.m_z;

			center.m_x = (center.m_x + center2.m_x) * 0.5f;
			center.m_y = (center.m_y + center2.m_y) * 0.5f;
			center.m_z = (center.m_z + center2.m_z) * 0.5f;
			if (radius < bounds2.m_u) {
				radius = bounds2.m_u;
			}

			LegoFloat deltaX = center.m_x - center2.m_x;
			LegoFloat deltaY = center.m_y - center2.m_y;
			LegoFloat deltaZ = center.m_z - center2.m_z;
			radius += static_cast<LegoFloat>(sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ));
		}

		scale = model->GetScale() * m_scale;
	}
	else {
		center = model->GetBoundingCenter();
		radius = model->GetBoundingRadius();
		scale = m_scale;
	}

	center *= scale;

	GolVec3 position;
	LocalToWorld(center, &position);
	SetBoundsCenterAndSpan(position);
	SetBoundsRadius(radius * scale);
}

// FUNCTION: GOLDP 0x100240b0
// FUNCTION: LEGORACERS 0x0040e270
void GolAnimatedEntity::ComputeVisibility(const GolViewFrustum& p_view, ResultStruct* p_result)
{
	GolVec3 position;
	GetBoundsCenter(&position);

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
		ComputeBoundsFromModel(i);
		GetBoundsCenter(&position);
	}
	p_result->m_visibility = p_view.ClassifySphere(position, GetBoundsRadius());
}

// FUNCTION: LEGORACERS 0x0040e360
LegoBool32 GolAnimatedEntity::IsPartAnimationDone()
{
	LegoU32 flags = m_flags;
	const CmbModelPartData& activePart = m_modelParts[0]->GetPartData()[m_currentPartIndex];

	return (flags & c_flagPartAnimationDone) ||
		   (!(flags & c_flagLoopCurrentPart) && static_cast<LegoFloat>(activePart.GetFrameCount() - 1) <= m_partTimeMs);
}

// STUB: LEGORACERS 0x0040e3c0
void GolAnimatedEntity::SamplePartPosition(
	LegoU32 p_modelIndex,
	LegoU32 p_trackOffset,
	LegoU32 p_partDataIndex,
	LegoS32 p_frame,
	GolVec3* p_dest
)
{
	CmbModelPart* modelPart = m_modelParts[p_modelIndex];
	LegoFloat timeScale = m_msPerFrame;
	CmbModelPartData* partData = modelPart->GetPartData();
	CmbModelPartTrackData& animationData = modelPart->GetAnimationData();
	LegoFloat time = static_cast<LegoFloat>(p_frame) * timeScale;
	const CmbModelPartData& part = partData[p_partDataIndex];
	LegoU32 trackIndex = part.GetTrackIndex();
	trackIndex += p_trackOffset;
	const CmbModelPartTrack& track = modelPart->GetTrack(trackIndex);
	LegoS32 frameCount = part.GetFrameCount();

	animationData.InterpolatePosition(p_dest, track, time, frameCount);
}

// STUB: LEGORACERS 0x0040e420
void GolAnimatedEntity::SamplePartRotation(
	LegoU32 p_modelIndex,
	LegoU32 p_trackOffset,
	LegoU32 p_partDataIndex,
	LegoS32 p_frame,
	GolQuat* p_dest
)
{
	CmbModelPart* modelPart = m_modelParts[p_modelIndex];
	LegoFloat timeScale = m_msPerFrame;
	CmbModelPartData* partData = modelPart->GetPartData();
	CmbModelPartTrackData& animationData = modelPart->GetAnimationData();
	LegoFloat time = static_cast<LegoFloat>(p_frame) * timeScale;
	const CmbModelPartData& part = partData[p_partDataIndex];
	LegoU32 trackIndex = part.GetTrackIndex();
	trackIndex += p_trackOffset;
	const CmbModelPartTrack& track = modelPart->GetTrack(trackIndex);
	LegoS32 frameCount = part.GetFrameCount();

	animationData.InterpolateRotation(p_dest, track, time, frameCount);
}

// FUNCTION: GOLDP 0x100241a0
// FUNCTION: LEGORACERS 0x0040e480
GolSceneNode* GolAnimatedEntity::GetSceneNode(LegoU32 p_arg1)
{
	return m_nodes[p_arg1];
}
