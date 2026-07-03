#include "race/racetrailmanager.h"

#include "core/gol.h"
#include "decomp.h"
#include "gdbmodelindexarray.h"
#include "golerror.h"
#include "mesh/golmodel.h"
#include "render/gold3drenderdevice.h"

#include <float.h>

extern LegoFloat g_inv255;

// GLOBAL: LEGORACERS 0x004b4790
const LegoFloat g_raceTrailManagerMaxFloat = FLT_MAX;

DECOMP_SIZE_ASSERT(RaceTrailManager, 0x0c)
DECOMP_SIZE_ASSERT(RaceTrailManager::Trail, 0x2a4)
DECOMP_SIZE_ASSERT(RaceTrailManager::Trail::Sample, 0x4c)

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RaceTrailManager::Trail::FUN_004513d0(GolD3DRenderDevice*)
{
}

// FUNCTION: LEGORACERS 0x00492930
RaceTrailManager::Trail::Trail()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00492950
RaceTrailManager::Trail::~Trail()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00492960
void RaceTrailManager::Trail::Destroy()
{
	if (m_model) {
		m_golExport->DestroyModel(m_model);
		m_model = NULL;
	}

	m_entity.ResetModelState();
	Reset();
}

// FUNCTION: LEGORACERS 0x00492990
void RaceTrailManager::Trail::Reset()
{
	LegoU32 zero = 0;

	m_golExport = NULL;
	m_model = NULL;
	m_flags = static_cast<LegoU8>(zero);
	m_durationMs = zero;
	m_sampleMs = zero;
	m_headIndex = zero;
	m_tailIndex = zero;
	m_unk0x0b0 = zero;
	m_sampleCount = zero;
	m_ringSize = zero;
	m_pointCount = zero;
	m_unk0x0c0 = zero;
	m_centerX = 0.0f;
	m_centerY = 0.0f;
	m_centerZ = 0.0f;
	m_endScale = 0.0f;
	m_endAlpha = 0.0f;
	m_color.m_red = 0xff;
	m_color.m_grn = 0xff;
	m_color.m_blu = 0xff;
	m_color.m_alp = 0xff;

	for (LegoU32 i = 0; i < sizeOfArray(m_samples); i++) {
		m_samples[i].m_durationMs = zero;
		m_samples[i].m_center.m_x = 0.0f;
		m_samples[i].m_center.m_y = 0.0f;
		m_samples[i].m_center.m_z = 0.0f;

		for (LegoU32 j = 0; j < 5; j++) {
			m_samples[i].m_points[j].m_x = 0.0f;
			m_samples[i].m_points[j].m_y = 0.0f;
			m_samples[i].m_points[j].m_z = 0.0f;
		}
	}
}

// FUNCTION: LEGORACERS 0x00492a50
void RaceTrailManager::Trail::Initialize(GolD3DRenderDevice* p_renderer, GolExport* p_golExport)
{
	m_golExport = p_golExport;
	m_model = p_golExport->CreateModel();
	m_model->Allocate(p_renderer, 1, 0x6a, 0x35, 4, 1);
	m_entity.SetPrimaryModel(m_model, g_raceTrailManagerMaxFloat);
}

// FUNCTION: LEGORACERS 0x00492a90
void RaceTrailManager::Trail::SetMaterial(GolD3DRenderDevice*, GolMaterial* p_material)
{
	m_model->GetMaterialTable()->SetEntry(0, p_material);
}

// FUNCTION: LEGORACERS 0x00492ab0
void RaceTrailManager::Trail::SetColor(const ColorRGBA* p_color)
{
	m_color.m_red = p_color->m_red;
	m_color.m_grn = p_color->m_grn;
	m_color.m_blu = p_color->m_blu;
	m_color.m_alp = p_color->m_alp;
}

// FUNCTION: LEGORACERS 0x00492ae0
void RaceTrailManager::Trail::Start(Params* p_params)
{
	m_flags = c_active | c_firstSample;

	m_durationMs = p_params->m_durationMs;
	m_sampleCount = p_params->m_sampleCount;
	m_ringSize = p_params->m_sampleCount + 2;
	m_pointCount = p_params->m_pointCount;
	m_unk0x0c0 = p_params->m_unk0x10;
	m_endScale = p_params->m_endScale;
	m_endAlpha = p_params->m_endAlpha;

	if (p_params->m_unk0x0c != 0) {
		m_flags = c_active | c_flags0x09cBit2 | c_firstSample;
	}

	LegoU32 value = m_durationMs;
	m_sampleMs = value / m_sampleCount;
	LegoU32 alignedValue = m_sampleCount * m_sampleMs;
	if (alignedValue != value) {
		m_durationMs = alignedValue;
	}

	m_headIndex = 0;
	m_tailIndex = 0;
	m_unk0x0b0 = 0;

	for (LegoU32 i = 0; i < m_ringSize; i++) {
		m_samples[i].m_durationMs = 0;
		m_samples[i].m_center.m_x = 0.0f;
		m_samples[i].m_center.m_y = 0.0f;
		m_samples[i].m_center.m_z = 0.0f;

		for (LegoU32 j = 0; j < m_pointCount; j++) {
			m_samples[i].m_points[j].m_x = 0.0f;
			m_samples[i].m_points[j].m_y = 0.0f;
			m_samples[i].m_points[j].m_z = 0.0f;
		}
	}
}

// FUNCTION: LEGORACERS 0x00492bd0
void RaceTrailManager::Trail::Release()
{
	m_flags |= c_released;
}

// FUNCTION: LEGORACERS 0x00492be0
void RaceTrailManager::Trail::Update(LegoU32 p_elapsedMs)
{
	LegoU8 flags = m_flags;
	if (!(flags & c_active)) {
		return;
	}

	if (flags & c_firstSample) {
		return;
	}

	switch (flags & c_saturated) {
	case 0:
		if (flags & c_released) {
			flags |= c_saturated;
			m_flags = flags;
		}
		break;
	}

	if (m_flags & c_released) {
		AdvanceTail(p_elapsedMs);
		if (m_flags & c_active) {
			RebuildGeometry();
		}
	}
}

// STUB: LEGORACERS 0x00492c30
void RaceTrailManager::Trail::AdvanceTail(LegoU32 p_elapsedMs)
{
	LegoU32 queuedDuration = 0;
	LegoU32 index = m_tailIndex;

	do {
		index++;
		if (index == m_ringSize) {
			index = 0;
		}

		queuedDuration += m_samples[index].m_durationMs;
	} while (index != m_headIndex);

	LegoU8 flags = m_flags;
	if (!(flags & c_saturated) && queuedDuration > m_durationMs) {
		m_flags = flags | c_saturated;
	}

	if (!(m_flags & c_saturated) || p_elapsedMs == 0) {
		return;
	}

	LegoU32 remainingMs = p_elapsedMs;
	do {
		LegoU32 stepMs = remainingMs;
		if (remainingMs > m_sampleMs) {
			stepMs = m_sampleMs;
			remainingMs -= stepMs;
		}
		else {
			remainingMs = 0;
		}

		LegoU32 currentIndex = m_tailIndex;
		LegoU32 nextIndex = (currentIndex + 1) % m_ringSize;
		if (stepMs > 0) {
			Sample* next = &m_samples[nextIndex];
			LegoU32 durationMs = next->m_durationMs;
			if (stepMs >= durationMs) {
				next->m_durationMs = 0;
				stepMs -= durationMs;
				m_tailIndex = currentIndex + 1;
				if (m_tailIndex == m_ringSize) {
					m_tailIndex = 0;
				}

				currentIndex = m_tailIndex;
				nextIndex = (currentIndex + 1) % m_ringSize;
			}

			queuedDuration = 0;
			index = currentIndex;
			do {
				index++;
				if (index == m_ringSize) {
					index = 0;
				}

				queuedDuration += m_samples[index].m_durationMs;
			} while (index != m_headIndex);

			if (stepMs > 0 && queuedDuration > 0) {
				next = &m_samples[nextIndex];
				durationMs = next->m_durationMs;
				if (stepMs > durationMs) {
					stepMs = durationMs - 1;
				}

				LegoFloat amount = static_cast<LegoFloat>(static_cast<LegoS32>(stepMs)) /
								   static_cast<LegoFloat>(static_cast<LegoS32>(durationMs));
				next->m_durationMs = durationMs - stepMs;

				Sample* current = &m_samples[m_tailIndex];
				for (LegoU32 i = 0; i < m_pointCount; i++) {
					current->m_points[i].m_x += (next->m_points[i].m_x - current->m_points[i].m_x) * amount;
					current->m_points[i].m_y += (next->m_points[i].m_y - current->m_points[i].m_y) * amount;
					current->m_points[i].m_z += (next->m_points[i].m_z - current->m_points[i].m_z) * amount;
				}

				current->m_center.m_x += (next->m_center.m_x - current->m_center.m_x) * amount;
				current->m_center.m_y += (next->m_center.m_y - current->m_center.m_y) * amount;
				current->m_center.m_z += (next->m_center.m_z - current->m_center.m_z) * amount;
			}
		}

		if (m_flags & c_released) {
			if (m_tailIndex == m_headIndex || queuedDuration == 0) {
				m_flags = 0;
				return;
			}
		}
	} while (remainingMs > 0);
}

// FUNCTION: LEGORACERS 0x00492ee0
void RaceTrailManager::Trail::AddSampleWithCenter(LegoU32 p_elapsedMs, GolVec3* p_positions, GolVec3 p_center)
{
	m_centerX = p_center.m_x;
	m_centerY = p_center.m_y;
	m_centerZ = p_center.m_z;
	AddSample(p_elapsedMs, p_positions);
}

// FUNCTION: LEGORACERS 0x00492f10
void RaceTrailManager::Trail::AddSample(LegoU32 p_elapsedMs, GolVec3* p_positions)
{
	if (m_flags & c_firstSample) {
		for (LegoU32 i = 0; i < m_pointCount; i++) {
			m_samples[m_headIndex].m_points[i].m_x = p_positions[i].m_x;
			m_samples[m_headIndex].m_points[i].m_y = p_positions[i].m_y;
			m_samples[m_headIndex].m_points[i].m_z = p_positions[i].m_z;
		}

		m_samples[m_headIndex].m_center.m_x = m_centerX;
		m_samples[m_headIndex].m_center.m_y = m_centerY;
		m_samples[m_headIndex].m_center.m_z = m_centerZ;
		m_headIndex++;
		m_flags &= ~c_firstSample;
		return;
	}

	if (p_elapsedMs != 0) {
		do {
			LegoU32 remainingMs = 0;
			LegoU32 stepMs = m_sampleMs - 1;
			if (p_elapsedMs > stepMs) {
				remainingMs = p_elapsedMs - m_sampleMs;
			}
			else {
				stepMs = p_elapsedMs;
			}

			Sample* activeFrame = &m_samples[m_headIndex];
			activeFrame->m_durationMs += stepMs;
			AdvanceTail(stepMs);

			if (activeFrame->m_durationMs >= m_sampleMs) {
				LegoU32 overflowMs = activeFrame->m_durationMs - m_sampleMs;
				activeFrame->m_durationMs = m_sampleMs;

				m_headIndex++;
				if (m_headIndex == m_ringSize) {
					m_headIndex = 0;
				}

				if (overflowMs > m_sampleMs) {
					overflowMs = m_sampleMs;
				}

				m_samples[m_headIndex].m_durationMs = overflowMs;
			}

			for (LegoU32 i = 0; i < m_pointCount; i++) {
				m_samples[m_headIndex].m_points[i].m_x = p_positions[i].m_x;
				m_samples[m_headIndex].m_points[i].m_y = p_positions[i].m_y;
				m_samples[m_headIndex].m_points[i].m_z = p_positions[i].m_z;
			}

			m_samples[m_headIndex].m_center.m_x = m_centerX;
			m_samples[m_headIndex].m_center.m_y = m_centerY;
			m_samples[m_headIndex].m_center.m_z = m_centerZ;
			p_elapsedMs = remainingMs;
		} while (p_elapsedMs != 0);
	}

	RebuildGeometry();
	m_flags |= c_drawable;
}

// STUB: LEGORACERS 0x004931a0
void RaceTrailManager::Trail::RebuildGeometry()
{
	LegoU32 frameCount;
	if (m_headIndex > m_tailIndex) {
		frameCount = m_headIndex - m_tailIndex + 1;
	}
	else {
		frameCount = m_ringSize - m_tailIndex + m_headIndex + 1;
	}

	Sample* activeFrame = &m_samples[m_headIndex];
	GolVec3 center;
	center.m_x = activeFrame->m_points[0].m_x;
	center.m_y = activeFrame->m_points[1].m_y;
	center.m_z = activeFrame->m_points[2].m_z;
	m_entity.SetPosition(center);

	GdbVertexArray* vertexArray;
	LegoFloat uStep = 1.0f / static_cast<LegoFloat>(static_cast<LegoS32>(m_pointCount + 1));
	LegoFloat vStep = 1.0f / static_cast<LegoFloat>(static_cast<LegoS32>(m_sampleCount + 1));
	m_model->GetVertexArray(&vertexArray);

	ColorRGBA color = m_color;
	LegoU8 alphaStep = static_cast<LegoU8>(static_cast<LegoS32>(
		((static_cast<LegoFloat>(m_color.m_alp) * g_inv255 - m_endAlpha) /
		 static_cast<LegoFloat>(static_cast<LegoS32>(m_sampleCount + 1))) *
		255.0f
	));

	LegoU32 vertexIndex = 0;
	LegoU32 elapsedMs = 0;
	GolVec2 texCoord;
	texCoord.m_x = 0.0f;
	texCoord.m_y = 0.0f;

	for (LegoU32 frameOffset = 0; frameOffset < frameCount; frameOffset++) {
		LegoU32 frameIndex = (m_headIndex + m_ringSize - frameOffset) % m_ringSize;
		Sample* frame = &m_samples[frameIndex];

		LegoFloat tailAmount;
		if (frameOffset) {
			tailAmount = static_cast<LegoFloat>(static_cast<LegoS32>(elapsedMs)) /
						 static_cast<LegoFloat>(static_cast<LegoS32>(m_durationMs)) * (1.0f - m_endScale);
			color.m_alp -= alphaStep;
		}
		else {
			tailAmount = 0.0f;
		}

		texCoord.m_x = 0.0f;
		for (LegoU32 pointIndex = 0; pointIndex < m_pointCount; pointIndex++) {
			if (vertexIndex < 0x6a) {
				GolVec3 position = frame->m_points[pointIndex];
				if (m_endScale != 1.0f && tailAmount != 0.0f) {
					position.m_x += (frame->m_center.m_x - position.m_x) * tailAmount;
					position.m_y += (frame->m_center.m_y - position.m_y) * tailAmount;
					position.m_z += (frame->m_center.m_z - position.m_z) * tailAmount;
				}

				position.m_x -= center.m_x;
				position.m_y -= center.m_y;
				position.m_z -= center.m_z;
				vertexArray->SetPosition(vertexIndex, position);
				vertexArray->SetColor(vertexIndex, color);
				vertexArray->SetTextureCoordinate(vertexIndex, texCoord);
				vertexIndex++;
			}

			texCoord.m_x += uStep;
		}

		texCoord.m_y += vStep;
		elapsedMs += frame->m_durationMs;
	}

	m_model->AddFlagsWithBounds(1, FALSE);

	LegoU32 rowsPerGroup = 0x40 / m_pointCount;
	LegoU32 groupCount;
	if (rowsPerGroup > frameCount) {
		rowsPerGroup = frameCount;
		groupCount = 1;
	}
	else {
		groupCount = frameCount / (rowsPerGroup - 1) + 1;
	}

	GdbModelIndexArrayBase* indexArrayBase;
	m_model->GetIndexArrayInto(&indexArrayBase);
	GdbModelIndexArray* indexArray = static_cast<GdbModelIndexArray*>(indexArrayBase);
	GdbModelIndexArray::Indices* indices = indexArray->GetMutableIndices();

	LegoU32 triangleIndex = 0;
	for (LegoU32 rowIndex = 0; rowIndex < rowsPerGroup - 1; rowIndex++) {
		LegoU32 rowBase = rowIndex * m_pointCount;
		for (LegoU32 pointIndex = 0; pointIndex < m_pointCount; pointIndex++) {
			LegoU32 nextPoint = (pointIndex + 1) % m_pointCount;
			if (triangleIndex < 0x35) {
				indices[triangleIndex].m_a = static_cast<LegoU8>(rowBase + pointIndex + m_pointCount);
				indices[triangleIndex].m_b = static_cast<LegoU8>(rowBase + pointIndex);
				indices[triangleIndex].m_c = static_cast<LegoU8>(rowBase + m_pointCount + nextPoint);
				indices[triangleIndex].m_x = 0;
				triangleIndex++;
			}

			if (triangleIndex < 0x35) {
				indices[triangleIndex].m_a = static_cast<LegoU8>(rowBase + m_pointCount + nextPoint);
				indices[triangleIndex].m_b = static_cast<LegoU8>(rowBase + pointIndex);
				indices[triangleIndex].m_c = static_cast<LegoU8>(rowBase + nextPoint);
				indices[triangleIndex].m_x = 0;
				triangleIndex++;
			}
		}
	}

	LegoU32 batchTriangleCount = triangleIndex;
	if (m_pointCount > 2) {
		LegoU32 lastRowBase = (rowsPerGroup - 1) * m_pointCount;
		for (LegoU32 pointIndex = 1; pointIndex < m_pointCount - 1; pointIndex++) {
			if (triangleIndex < 0x35) {
				indices[triangleIndex].m_a = static_cast<LegoU8>(lastRowBase);
				indices[triangleIndex].m_b = static_cast<LegoU8>(lastRowBase + pointIndex);
				indices[triangleIndex].m_c = static_cast<LegoU8>(lastRowBase + pointIndex + 1);
				indices[triangleIndex].m_x = 0;
				triangleIndex++;
			}
		}
	}

	m_model->AddFlags(1);

	LegoU32* groups = m_model->GetMutableGroups();
	groups[0] = GolModel::c_groupTypeMaterial;
	LegoU32 groupWordIndex = 1;
	LegoU32 firstVertex = 0;
	for (LegoU32 groupIndex = 0; groupIndex < groupCount; groupIndex++) {
		if (groupWordIndex < 4) {
			groups[groupWordIndex++] =
				(firstVertex & GolModel::c_materialMatrixIndexMask) |
				(((rowsPerGroup * m_pointCount + 0xffff) << GolModel::c_groupDataUpperWordShift) &
				 (GolModel::c_vertexCountMask << GolModel::c_groupDataUpperWordShift));
		}

		LegoU32 groupTriangleCount = batchTriangleCount;
		if (groupIndex >= groupCount - 1) {
			groupTriangleCount = triangleIndex;
		}

		if (groupWordIndex < 4) {
			groups[groupWordIndex++] =
				GolModel::c_groupTypeTriangleBatch |
				((groupTriangleCount & GolModel::c_triangleCountMask) << GolModel::c_groupDataUpperWordShift);
		}

		firstVertex += rowsPerGroup * m_pointCount;
	}

	if (groupWordIndex < 4) {
		groups[groupWordIndex] = GolModel::c_groupTypeEnd;
	}
	else if (groups[3] != GolModel::c_groupTypeEnd) {
		groups[3] = GolModel::c_groupTypeEnd;
	}
}

// FUNCTION: LEGORACERS 0x00493790
void RaceTrailManager::Trail::DrawTransparent(GolD3DRenderDevice* p_renderer)
{
	if (m_flags & c_drawable) {
		p_renderer->DrawModelEntity(&m_entity);
	}
}

// FUNCTION: LEGORACERS 0x004937b0
RaceTrailManager::RaceTrailManager()
{
	m_trails = NULL;
	m_trailCount = 0;
}

// FUNCTION: LEGORACERS 0x004937f0
RaceTrailManager::~RaceTrailManager()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00493800
void RaceTrailManager::Destroy()
{
	if (m_trails) {
		for (LegoU32 i = 0; i < m_trailCount; i++) {
			m_trails[i].Destroy();
		}

		Trail* trails = m_trails;
		delete[] trails;

		m_trails = NULL;
	}

	m_trailCount = 0;
}

// FUNCTION: LEGORACERS 0x00493850
void RaceTrailManager::Initialize(GolD3DRenderDevice* p_renderer, GolExport* p_golExport, LegoU32 p_trailCount)
{
	if (m_trails) {
		Destroy();
	}

	m_trails = new Trail[p_trailCount];
	if (m_trails == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_trailCount = p_trailCount;
	GolMaterial* material = p_renderer->FindMaterialByName("streak");

	LegoU32 i;
	for (i = 0; i < m_trailCount; i++) {
		m_trails[i].Initialize(p_renderer, p_golExport);
		m_trails[i].SetMaterial(p_renderer, material);
	}
}

// FUNCTION: LEGORACERS 0x004939b0
RaceTrailManager::Trail* RaceTrailManager::AcquireTrail(Trail::Params* p_params)
{
	LegoU32 count = m_trailCount;
	LegoU32 i;

	for (i = 0; i < count; i++) {
		if (!(m_trails[i].m_flags & Trail::c_active)) {
			break;
		}
	}

	if (i == count) {
		return NULL;
	}

	m_trails[i].Start(p_params);
	return &m_trails[i];
}

// FUNCTION: LEGORACERS 0x00493a10
void RaceTrailManager::ReleaseTrail(Trail* p_trail)
{
	p_trail->Release();
}

// FUNCTION: LEGORACERS 0x00493a20
LegoU32 RaceTrailManager::Update(LegoU32 p_elapsedMs)
{
	LegoU32 i;
	LegoU32 result = m_trailCount;

	for (i = 0; i < result; i++) {
		LegoU8 flags = m_trails[i].GetFlags();
		if (flags & Trail::c_active) {
			m_trails[i].Update(p_elapsedMs);
		}

		result = m_trailCount;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00493a60
LegoU32 RaceTrailManager::DrawOpaque(GolD3DRenderDevice* p_renderer)
{
	LegoU32 i;
	LegoU32 result = m_trailCount;

	for (i = 0; i < result; i++) {
		LegoU8 flags = m_trails[i].GetFlags();
		if (flags & Trail::c_active) {
			m_trails[i].FUN_004513d0(p_renderer);
		}

		result = m_trailCount;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00493aa0
LegoU32 RaceTrailManager::DrawTransparent(GolD3DRenderDevice* p_renderer)
{
	LegoU32 i;
	LegoU32 result = m_trailCount;

	for (i = 0; i < result; i++) {
		if (m_trails[i].IsActive()) {
			m_trails[i].DrawTransparent(p_renderer);
		}

		result = m_trailCount;
	}

	return result;
}
