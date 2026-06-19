#include "core/gol.h"
#include "decomp.h"
#include "gdbmodelindexarray0xc.h"
#include "golerror.h"
#include "mesh/golmodel.h"
#include "race/racesession.h"
#include "render/gold3drenderdevice.h"

#include <float.h>

extern LegoFloat g_unk0x4b05d8;

// GLOBAL: LEGORACERS 0x004b4790
const LegoFloat g_raceSessionField0x27c8MaxFloat = FLT_MAX;

DECOMP_SIZE_ASSERT(RaceSession::Field0x27c8, 0x0c)
DECOMP_SIZE_ASSERT(RaceSession::Field0x27c8::Item, 0x2a4)
DECOMP_SIZE_ASSERT(RaceSession::Field0x27c8::Item::Field0x0dc, 0x4c)

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RaceSession::Field0x27c8::Item::FUN_004513d0(GolD3DRenderDevice*)
{
}

// FUNCTION: LEGORACERS 0x00492930
RaceSession::Field0x27c8::Item::Item()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00492950
RaceSession::Field0x27c8::Item::~Item()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00492960
void RaceSession::Field0x27c8::Item::Destroy()
{
	if (m_unk0x008) {
		m_unk0x004->VTable0x48(m_unk0x008);
		m_unk0x008 = NULL;
	}

	m_unk0x00c.VTable0x54();
	Reset();
}

// FUNCTION: LEGORACERS 0x00492990
void RaceSession::Field0x27c8::Item::Reset()
{
	LegoU32 zero = 0;

	m_unk0x004 = NULL;
	m_unk0x008 = NULL;
	m_flags0x09c = static_cast<LegoU8>(zero);
	m_unk0x0a0 = zero;
	m_unk0x0a4 = zero;
	m_unk0x0a8 = zero;
	m_unk0x0ac = zero;
	m_unk0x0b0 = zero;
	m_unk0x0b4 = zero;
	m_unk0x0b8 = zero;
	m_unk0x0bc = zero;
	m_unk0x0c0 = zero;
	m_unk0x0c4 = 0.0f;
	m_unk0x0c8 = 0.0f;
	m_unk0x0cc = 0.0f;
	m_unk0x0d0 = 0.0f;
	m_unk0x0d4 = 0.0f;
	m_unk0x0d8.m_red = 0xff;
	m_unk0x0d8.m_grn = 0xff;
	m_unk0x0d8.m_blu = 0xff;
	m_unk0x0d8.m_alp = 0xff;

	for (LegoU32 i = 0; i < sizeOfArray(m_unk0x0dc); i++) {
		m_unk0x0dc[i].m_unk0x00 = zero;
		m_unk0x0dc[i].m_unk0x40.m_x = 0.0f;
		m_unk0x0dc[i].m_unk0x40.m_y = 0.0f;
		m_unk0x0dc[i].m_unk0x40.m_z = 0.0f;

		for (LegoU32 j = 0; j < 5; j++) {
			m_unk0x0dc[i].m_unk0x04[j].m_x = 0.0f;
			m_unk0x0dc[i].m_unk0x04[j].m_y = 0.0f;
			m_unk0x0dc[i].m_unk0x04[j].m_z = 0.0f;
		}
	}
}

// FUNCTION: LEGORACERS 0x00492a50
void RaceSession::Field0x27c8::Item::FUN_00492a50(GolD3DRenderDevice* p_renderer, GolExport* p_golExport)
{
	m_unk0x004 = p_golExport;
	m_unk0x008 = p_golExport->VTable0x14();
	m_unk0x008->VTable0x18(p_renderer, 1, 0x6a, 0x35, 4, 1);
	m_unk0x00c.VTable0x50(m_unk0x008, g_raceSessionField0x27c8MaxFloat);
}

// FUNCTION: LEGORACERS 0x00492a90
void RaceSession::Field0x27c8::Item::FUN_00492a90(GolD3DRenderDevice*, DuskwindBananaRelic0x24* p_material)
{
	m_unk0x008->GetMaterialTable()->SetPosition(0, p_material);
}

// FUNCTION: LEGORACERS 0x00492ab0
void RaceSession::Field0x27c8::Item::FUN_00492ab0(const ColorRGBA* p_color)
{
	m_unk0x0d8.m_red = p_color->m_red;
	m_unk0x0d8.m_grn = p_color->m_grn;
	m_unk0x0d8.m_blu = p_color->m_blu;
	m_unk0x0d8.m_alp = p_color->m_alp;
}

// FUNCTION: LEGORACERS 0x00492ae0
void RaceSession::Field0x27c8::Item::FUN_00492ae0(Params* p_params)
{
	m_flags0x09c = c_flags0x09cBit0 | c_flags0x09cBit3;

	m_unk0x0a0 = p_params->m_unk0x00;
	m_unk0x0b4 = p_params->m_unk0x04;
	m_unk0x0b8 = p_params->m_unk0x04 + 2;
	m_unk0x0bc = p_params->m_unk0x08;
	m_unk0x0c0 = p_params->m_unk0x10;
	m_unk0x0d0 = p_params->m_unk0x14;
	m_unk0x0d4 = p_params->m_unk0x18;

	if (p_params->m_unk0x0c != 0) {
		m_flags0x09c = c_flags0x09cBit0 | c_flags0x09cBit2 | c_flags0x09cBit3;
	}

	LegoU32 value = m_unk0x0a0;
	m_unk0x0a4 = value / m_unk0x0b4;
	LegoU32 alignedValue = m_unk0x0b4 * m_unk0x0a4;
	if (alignedValue != value) {
		m_unk0x0a0 = alignedValue;
	}

	m_unk0x0a8 = 0;
	m_unk0x0ac = 0;
	m_unk0x0b0 = 0;

	for (LegoU32 i = 0; i < m_unk0x0b8; i++) {
		m_unk0x0dc[i].m_unk0x00 = 0;
		m_unk0x0dc[i].m_unk0x40.m_x = 0.0f;
		m_unk0x0dc[i].m_unk0x40.m_y = 0.0f;
		m_unk0x0dc[i].m_unk0x40.m_z = 0.0f;

		for (LegoU32 j = 0; j < m_unk0x0bc; j++) {
			m_unk0x0dc[i].m_unk0x04[j].m_x = 0.0f;
			m_unk0x0dc[i].m_unk0x04[j].m_y = 0.0f;
			m_unk0x0dc[i].m_unk0x04[j].m_z = 0.0f;
		}
	}
}

// FUNCTION: LEGORACERS 0x00492bd0
void RaceSession::Field0x27c8::Item::FUN_00492bd0()
{
	m_flags0x09c |= c_flags0x09cBit1;
}

// STUB: LEGORACERS 0x00492be0
void RaceSession::Field0x27c8::Item::FUN_00492be0(LegoU32 p_elapsedMs)
{
	LegoU8 flags = m_flags0x09c;
	if (!(flags & c_flags0x09cBit0)) {
		return;
	}

	if (flags & c_flags0x09cBit3) {
		return;
	}

	switch (flags & c_flags0x09cBit4) {
	case 0:
		if (!(flags & c_flags0x09cBit1)) {
			flags |= c_flags0x09cBit4;
			m_flags0x09c = flags;
		}
		break;
	}

	if (m_flags0x09c & c_flags0x09cBit1) {
		FUN_00492c30(p_elapsedMs);
		if (m_flags0x09c & c_flags0x09cBit0) {
			FUN_004931a0();
		}
	}
}

// STUB: LEGORACERS 0x00492c30
void RaceSession::Field0x27c8::Item::FUN_00492c30(LegoU32 p_elapsedMs)
{
	LegoU32 queuedDuration = 0;
	LegoU32 index = m_unk0x0ac;

	do {
		index++;
		if (index == m_unk0x0b8) {
			index = 0;
		}

		queuedDuration += m_unk0x0dc[index].m_unk0x00;
	} while (index != m_unk0x0a8);

	LegoU8 flags = m_flags0x09c;
	if (!(flags & c_flags0x09cBit4) && queuedDuration > m_unk0x0a0) {
		m_flags0x09c = flags | c_flags0x09cBit4;
	}

	if (!(m_flags0x09c & c_flags0x09cBit4) || p_elapsedMs == 0) {
		return;
	}

	LegoU32 remainingMs = p_elapsedMs;
	do {
		LegoU32 stepMs = remainingMs;
		if (remainingMs > m_unk0x0a4) {
			stepMs = m_unk0x0a4;
			remainingMs -= stepMs;
		}
		else {
			remainingMs = 0;
		}

		LegoU32 currentIndex = m_unk0x0ac;
		LegoU32 nextIndex = (currentIndex + 1) % m_unk0x0b8;
		if (stepMs > 0) {
			Field0x0dc* next = &m_unk0x0dc[nextIndex];
			LegoU32 durationMs = next->m_unk0x00;
			if (stepMs >= durationMs) {
				next->m_unk0x00 = 0;
				stepMs -= durationMs;
				m_unk0x0ac = currentIndex + 1;
				if (m_unk0x0ac == m_unk0x0b8) {
					m_unk0x0ac = 0;
				}

				currentIndex = m_unk0x0ac;
				nextIndex = (currentIndex + 1) % m_unk0x0b8;
			}

			queuedDuration = 0;
			index = currentIndex;
			do {
				index++;
				if (index == m_unk0x0b8) {
					index = 0;
				}

				queuedDuration += m_unk0x0dc[index].m_unk0x00;
			} while (index != m_unk0x0a8);

			if (stepMs > 0 && queuedDuration > 0) {
				next = &m_unk0x0dc[nextIndex];
				durationMs = next->m_unk0x00;
				if (stepMs > durationMs) {
					stepMs = durationMs - 1;
				}

				LegoFloat amount = static_cast<LegoFloat>(static_cast<LegoS32>(stepMs)) /
								   static_cast<LegoFloat>(static_cast<LegoS32>(durationMs));
				next->m_unk0x00 = durationMs - stepMs;

				Field0x0dc* current = &m_unk0x0dc[m_unk0x0ac];
				for (LegoU32 i = 0; i < m_unk0x0bc; i++) {
					current->m_unk0x04[i].m_x += (next->m_unk0x04[i].m_x - current->m_unk0x04[i].m_x) * amount;
					current->m_unk0x04[i].m_y += (next->m_unk0x04[i].m_y - current->m_unk0x04[i].m_y) * amount;
					current->m_unk0x04[i].m_z += (next->m_unk0x04[i].m_z - current->m_unk0x04[i].m_z) * amount;
				}

				current->m_unk0x40.m_x += (next->m_unk0x40.m_x - current->m_unk0x40.m_x) * amount;
				current->m_unk0x40.m_y += (next->m_unk0x40.m_y - current->m_unk0x40.m_y) * amount;
				current->m_unk0x40.m_z += (next->m_unk0x40.m_z - current->m_unk0x40.m_z) * amount;
			}
		}

		if (m_flags0x09c & c_flags0x09cBit1) {
			if (m_unk0x0ac == m_unk0x0a8 || queuedDuration == 0) {
				m_flags0x09c = 0;
				return;
			}
		}
	} while (remainingMs > 0);
}

// FUNCTION: LEGORACERS 0x00492ee0
void RaceSession::Field0x27c8::Item::FUN_00492ee0(
	LegoU32 p_elapsedMs,
	GolVec3* p_positions,
	LegoFloat p_unk0x0c,
	LegoFloat p_unk0x10,
	LegoFloat p_unk0x14
)
{
	m_unk0x0c4 = p_unk0x0c;
	m_unk0x0c8 = p_unk0x10;
	m_unk0x0cc = p_unk0x14;
	FUN_00492f10(p_elapsedMs, p_positions);
}

// FUNCTION: LEGORACERS 0x00492f10
void RaceSession::Field0x27c8::Item::FUN_00492f10(LegoU32 p_elapsedMs, GolVec3* p_positions)
{
	if (m_flags0x09c & c_flags0x09cBit3) {
		for (LegoU32 i = 0; i < m_unk0x0bc; i++) {
			m_unk0x0dc[m_unk0x0a8].m_unk0x04[i].m_x = p_positions[i].m_x;
			m_unk0x0dc[m_unk0x0a8].m_unk0x04[i].m_y = p_positions[i].m_y;
			m_unk0x0dc[m_unk0x0a8].m_unk0x04[i].m_z = p_positions[i].m_z;
		}

		m_unk0x0dc[m_unk0x0a8].m_unk0x40.m_x = m_unk0x0c4;
		m_unk0x0dc[m_unk0x0a8].m_unk0x40.m_y = m_unk0x0c8;
		m_unk0x0dc[m_unk0x0a8].m_unk0x40.m_z = m_unk0x0cc;
		m_unk0x0a8++;
		m_flags0x09c &= ~c_flags0x09cBit3;
		return;
	}

	if (p_elapsedMs != 0) {
		do {
			LegoU32 remainingMs = 0;
			LegoU32 stepMs = m_unk0x0a4 - 1;
			if (p_elapsedMs > stepMs) {
				remainingMs = p_elapsedMs - m_unk0x0a4;
			}
			else {
				stepMs = p_elapsedMs;
			}

			Field0x0dc* activeFrame = &m_unk0x0dc[m_unk0x0a8];
			activeFrame->m_unk0x00 += stepMs;
			FUN_00492c30(stepMs);

			if (activeFrame->m_unk0x00 >= m_unk0x0a4) {
				LegoU32 overflowMs = activeFrame->m_unk0x00 - m_unk0x0a4;
				activeFrame->m_unk0x00 = m_unk0x0a4;

				m_unk0x0a8++;
				if (m_unk0x0a8 == m_unk0x0b8) {
					m_unk0x0a8 = 0;
				}

				if (overflowMs > m_unk0x0a4) {
					overflowMs = m_unk0x0a4;
				}

				m_unk0x0dc[m_unk0x0a8].m_unk0x00 = overflowMs;
			}

			for (LegoU32 i = 0; i < m_unk0x0bc; i++) {
				m_unk0x0dc[m_unk0x0a8].m_unk0x04[i].m_x = p_positions[i].m_x;
				m_unk0x0dc[m_unk0x0a8].m_unk0x04[i].m_y = p_positions[i].m_y;
				m_unk0x0dc[m_unk0x0a8].m_unk0x04[i].m_z = p_positions[i].m_z;
			}

			m_unk0x0dc[m_unk0x0a8].m_unk0x40.m_x = m_unk0x0c4;
			m_unk0x0dc[m_unk0x0a8].m_unk0x40.m_y = m_unk0x0c8;
			m_unk0x0dc[m_unk0x0a8].m_unk0x40.m_z = m_unk0x0cc;
			p_elapsedMs = remainingMs;
		} while (p_elapsedMs != 0);
	}

	FUN_004931a0();
	m_flags0x09c |= c_flags0x09cBit5;
}

// STUB: LEGORACERS 0x004931a0
void RaceSession::Field0x27c8::Item::FUN_004931a0()
{
	LegoU32 frameCount;
	if (m_unk0x0a8 > m_unk0x0ac) {
		frameCount = m_unk0x0a8 - m_unk0x0ac + 1;
	}
	else {
		frameCount = m_unk0x0b8 - m_unk0x0ac + m_unk0x0a8 + 1;
	}

	Field0x0dc* activeFrame = &m_unk0x0dc[m_unk0x0a8];
	GolVec3 center;
	center.m_x = activeFrame->m_unk0x04[0].m_x;
	center.m_y = activeFrame->m_unk0x04[1].m_y;
	center.m_z = activeFrame->m_unk0x04[2].m_z;
	m_unk0x00c.VTable0x08(center);

	GdbVertexArray0xc* vertexArray;
	LegoFloat uStep = 1.0f / static_cast<LegoFloat>(static_cast<LegoS32>(m_unk0x0bc + 1));
	LegoFloat vStep = 1.0f / static_cast<LegoFloat>(static_cast<LegoS32>(m_unk0x0b4 + 1));
	m_unk0x008->VTable0x28(&vertexArray);

	ColorRGBA color = m_unk0x0d8;
	LegoU8 alphaStep = static_cast<LegoU8>(static_cast<LegoS32>(
		((static_cast<LegoFloat>(m_unk0x0d8.m_alp) * g_unk0x4b05d8 - m_unk0x0d4) /
		 static_cast<LegoFloat>(static_cast<LegoS32>(m_unk0x0b4 + 1))) *
		255.0f
	));

	LegoU32 vertexIndex = 0;
	LegoU32 elapsedMs = 0;
	GolVec2 texCoord;
	texCoord.m_x = 0.0f;
	texCoord.m_y = 0.0f;

	for (LegoU32 frameOffset = 0; frameOffset < frameCount; frameOffset++) {
		LegoU32 frameIndex = (m_unk0x0a8 + m_unk0x0b8 - frameOffset) % m_unk0x0b8;
		Field0x0dc* frame = &m_unk0x0dc[frameIndex];

		LegoFloat tailAmount;
		if (frameOffset) {
			tailAmount = static_cast<LegoFloat>(static_cast<LegoS32>(elapsedMs)) /
						 static_cast<LegoFloat>(static_cast<LegoS32>(m_unk0x0a0)) * (1.0f - m_unk0x0d0);
			color.m_alp -= alphaStep;
		}
		else {
			tailAmount = 0.0f;
		}

		texCoord.m_x = 0.0f;
		for (LegoU32 pointIndex = 0; pointIndex < m_unk0x0bc; pointIndex++) {
			if (vertexIndex < 0x6a) {
				GolVec3 position = frame->m_unk0x04[pointIndex];
				if (m_unk0x0d0 != 1.0f && tailAmount != 0.0f) {
					position.m_x += (frame->m_unk0x40.m_x - position.m_x) * tailAmount;
					position.m_y += (frame->m_unk0x40.m_y - position.m_y) * tailAmount;
					position.m_z += (frame->m_unk0x40.m_z - position.m_z) * tailAmount;
				}

				position.m_x -= center.m_x;
				position.m_y -= center.m_y;
				position.m_z -= center.m_z;
				vertexArray->VTable0x24(vertexIndex, position);
				vertexArray->VTable0x30(vertexIndex, color);
				vertexArray->VTable0x28(vertexIndex, texCoord);
				vertexIndex++;
			}

			texCoord.m_x += uStep;
		}

		texCoord.m_y += vStep;
		elapsedMs += frame->m_unk0x00;
	}

	m_unk0x008->VTable0x2c(1, FALSE);

	LegoU32 rowsPerGroup = 0x40 / m_unk0x0bc;
	LegoU32 groupCount;
	if (rowsPerGroup > frameCount) {
		rowsPerGroup = frameCount;
		groupCount = 1;
	}
	else {
		groupCount = frameCount / (rowsPerGroup - 1) + 1;
	}

	IGdbModelIndexArray0x8* indexArrayBase;
	m_unk0x008->VTable0x30(&indexArrayBase);
	GdbModelIndexArray0xc* indexArray = static_cast<GdbModelIndexArray0xc*>(indexArrayBase);
	GdbModelIndexArray0xc::Indices* indices = indexArray->GetMutableIndices();

	LegoU32 triangleIndex = 0;
	for (LegoU32 rowIndex = 0; rowIndex < rowsPerGroup - 1; rowIndex++) {
		LegoU32 rowBase = rowIndex * m_unk0x0bc;
		for (LegoU32 pointIndex = 0; pointIndex < m_unk0x0bc; pointIndex++) {
			LegoU32 nextPoint = (pointIndex + 1) % m_unk0x0bc;
			if (triangleIndex < 0x35) {
				indices[triangleIndex].m_a = static_cast<LegoU8>(rowBase + pointIndex + m_unk0x0bc);
				indices[triangleIndex].m_b = static_cast<LegoU8>(rowBase + pointIndex);
				indices[triangleIndex].m_c = static_cast<LegoU8>(rowBase + m_unk0x0bc + nextPoint);
				indices[triangleIndex].m_x = 0;
				triangleIndex++;
			}

			if (triangleIndex < 0x35) {
				indices[triangleIndex].m_a = static_cast<LegoU8>(rowBase + m_unk0x0bc + nextPoint);
				indices[triangleIndex].m_b = static_cast<LegoU8>(rowBase + pointIndex);
				indices[triangleIndex].m_c = static_cast<LegoU8>(rowBase + nextPoint);
				indices[triangleIndex].m_x = 0;
				triangleIndex++;
			}
		}
	}

	LegoU32 batchTriangleCount = triangleIndex;
	if (m_unk0x0bc > 2) {
		LegoU32 lastRowBase = (rowsPerGroup - 1) * m_unk0x0bc;
		for (LegoU32 pointIndex = 1; pointIndex < m_unk0x0bc - 1; pointIndex++) {
			if (triangleIndex < 0x35) {
				indices[triangleIndex].m_a = static_cast<LegoU8>(lastRowBase);
				indices[triangleIndex].m_b = static_cast<LegoU8>(lastRowBase + pointIndex);
				indices[triangleIndex].m_c = static_cast<LegoU8>(lastRowBase + pointIndex + 1);
				indices[triangleIndex].m_x = 0;
				triangleIndex++;
			}
		}
	}

	m_unk0x008->VTable0x34(1);

	LegoU32* groups = m_unk0x008->GetMutableGroups();
	groups[0] = GolModel::c_groupTypeMaterial;
	LegoU32 groupWordIndex = 1;
	LegoU32 firstVertex = 0;
	for (LegoU32 groupIndex = 0; groupIndex < groupCount; groupIndex++) {
		if (groupWordIndex < 4) {
			groups[groupWordIndex++] = (firstVertex & GolModel::c_materialMatrixIndexMask) |
									   (((rowsPerGroup * m_unk0x0bc + 0xffff) << GolModel::c_groupDataUpperWordShift) &
										(GolModel::c_vertexCountMask << GolModel::c_groupDataUpperWordShift));
		}

		LegoU32 groupTriangleCount = triangleIndex;
		if (groupIndex >= groupCount - 1) {
			groupTriangleCount = batchTriangleCount;
		}

		if (groupWordIndex < 4) {
			groups[groupWordIndex++] =
				GolModel::c_groupTypeTriangleBatch |
				((groupTriangleCount & GolModel::c_triangleCountMask) << GolModel::c_groupDataUpperWordShift);
		}

		firstVertex += rowsPerGroup * m_unk0x0bc;
	}

	if (groupWordIndex < 4) {
		groups[groupWordIndex] = GolModel::c_groupTypeEnd;
	}
	else if (groups[3] != GolModel::c_groupTypeEnd) {
		groups[3] = GolModel::c_groupTypeEnd;
	}
}

// FUNCTION: LEGORACERS 0x00493790
void RaceSession::Field0x27c8::Item::FUN_00493790(GolD3DRenderDevice* p_renderer)
{
	if (m_flags0x09c & c_flags0x09cBit5) {
		p_renderer->VTable0x94(&m_unk0x00c);
	}
}

// FUNCTION: LEGORACERS 0x004937b0
RaceSession::Field0x27c8::Field0x27c8()
{
	m_items = NULL;
	m_count = 0;
}

// FUNCTION: LEGORACERS 0x004937f0
RaceSession::Field0x27c8::~Field0x27c8()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00493800
void RaceSession::Field0x27c8::Destroy()
{
	if (m_items) {
		for (LegoU32 i = 0; i < m_count; i++) {
			m_items[i].Destroy();
		}

		Item* items = m_items;
		if (items) {
			items->VTable0x00(3);
		}

		m_items = NULL;
	}

	m_count = 0;
}

// FUNCTION: LEGORACERS 0x00493850
void RaceSession::Field0x27c8::FUN_00493850(GolD3DRenderDevice* p_renderer, GolExport* p_golExport, LegoU32 p_count)
{
	if (m_items) {
		Destroy();
	}

	m_items = new Item[p_count];
	if (m_items == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_count = p_count;
	DuskwindBananaRelic0x24* material = p_renderer->FindMaterialByName("streak");

	LegoU32 i;
	for (i = 0; i < m_count; i++) {
		m_items[i].FUN_00492a50(p_renderer, p_golExport);
		m_items[i].FUN_00492a90(p_renderer, material);
	}
}

// STUB: LEGORACERS 0x00493950
RaceSession::Field0x27c8::Item* RaceSession::Field0x27c8::Item::VTable0x00(undefined4 p_flags)
{
	if (p_flags & 2) {
		if (p_flags & 1) {
			delete[] this;
		}

		return this;
	}

	Destroy();
	if (p_flags & 1) {
		delete this;
	}

	return this;
}

// FUNCTION: LEGORACERS 0x004939b0
RaceSession::Field0x27c8::Item* RaceSession::Field0x27c8::FUN_004939b0(Item::Params* p_params)
{
	LegoU32 count = m_count;
	LegoU32 i;

	for (i = 0; i < count; i++) {
		if (!(m_items[i].m_flags0x09c & Item::c_flags0x09cBit0)) {
			break;
		}
	}

	if (i == count) {
		return NULL;
	}

	m_items[i].FUN_00492ae0(p_params);
	return &m_items[i];
}

// FUNCTION: LEGORACERS 0x00493a10
void RaceSession::Field0x27c8::FUN_00493a10(Item* p_item)
{
	p_item->FUN_00492bd0();
}

// FUNCTION: LEGORACERS 0x00493a20
LegoU32 RaceSession::Field0x27c8::FUN_00493a20(LegoU32 p_elapsedMs)
{
	LegoU32 i;
	LegoU32 result = m_count;

	for (i = 0; i < result; i++) {
		LegoU8 flags = m_items[i].GetFlags0x09c();
		if (flags & Item::c_flags0x09cBit0) {
			m_items[i].FUN_00492be0(p_elapsedMs);
		}

		result = m_count;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00493a60
LegoU32 RaceSession::Field0x27c8::FUN_00493a60(GolD3DRenderDevice* p_renderer)
{
	LegoU32 i;
	LegoU32 result = m_count;

	for (i = 0; i < result; i++) {
		LegoU8 flags = m_items[i].GetFlags0x09c();
		if (flags & Item::c_flags0x09cBit0) {
			m_items[i].FUN_004513d0(p_renderer);
		}

		result = m_count;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00493aa0
LegoU32 RaceSession::Field0x27c8::FUN_00493aa0(GolD3DRenderDevice* p_renderer)
{
	LegoU32 i;
	LegoU32 result = m_count;

	for (i = 0; i < result; i++) {
		if (m_items[i].IsActive()) {
			m_items[i].FUN_00493790(p_renderer);
		}

		result = m_count;
	}

	return result;
}
