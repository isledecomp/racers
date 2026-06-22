#include "camera/golcamera.h"
#include "camera/goltransform.h"
#include "core/gol.h"
#include "decomp.h"
#include "duskwindbananarelic0x24.h"
#include "gdbmodelindexarray0xc.h"
#include "gdbvertexarray0xc.h"
#include "golmath.h"
#include "golmodelbase.h"
#include "golscenenode.h"
#include "goltransformbase.h"
#include "material/materialtable0x0c.h"
#include "race/racesession.h"
#include "render/gold3drenderdevice.h"

#include <math.h>
#include <string.h>

DECOMP_SIZE_ASSERT(RaceSession::Field0x6dc::Field0x170, 0x170)
DECOMP_SIZE_ASSERT(RaceSession::Field0x6dc::Field0x98, 0x98)

// GLOBAL: LEGORACERS 0x004b47a4
extern const LegoFloat g_unk0x004b47a4 = 0.02f;

extern LegoFloat g_minSoundPan;

// FUNCTION: LEGORACERS 0x00493ae0
RaceSession::Field0x6dc::Field0x170::Field0x170()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00493b30
RaceSession::Field0x6dc::Field0x170::~Field0x170()
{
	FUN_00493e60();
}

// FUNCTION: LEGORACERS 0x00493b80
void RaceSession::Field0x6dc::Field0x170::Reset()
{
	m_unk0x000 = NULL;
	m_unk0x004 = NULL;
	m_unk0x008 = 0;
	m_unk0x00c = 0;
	m_unk0x010 = NULL;
	m_unk0x014 = 0;
	m_unk0x0b0 = 0;
	m_unk0x0b4 = 0;
	m_unk0x0b8 = 0;
	m_unk0x0bc = 0;
	m_unk0x0c0 = 0;
	m_unk0x0c4 = 0;
	m_unk0x0c8 = 0;
	m_unk0x0cc = 0;
	m_unk0x0d0 = 0;
	m_unk0x0d4 = 0;
	m_unk0x0dc = 0;
	m_unk0x0e0 = 0;
	m_unk0x0e4 = 0;
	m_unk0x0e8 = 0;
	::memset(m_unk0x0ec, 0, sizeof(m_unk0x0ec));
	::memset(m_unk0x128, 0, sizeof(m_unk0x128));
	m_unk0x160.m_alp = 0xff;
	m_unk0x164.m_alp = 0xff;
	m_unk0x168.m_alp = 0xff;
	m_unk0x13c = 0;
	m_unk0x140 = 0;
	m_unk0x144 = NULL;
	m_unk0x148.Clear();
	m_unk0x160.m_red = 0;
	m_unk0x160.m_grn = 0;
	m_unk0x160.m_blu = 0;
	m_unk0x164.m_red = 0;
	m_unk0x164.m_grn = 0;
	m_unk0x164.m_blu = 0;
	m_unk0x168.m_red = 0;
	m_unk0x168.m_grn = 0;
	m_unk0x168.m_blu = 0;
	m_unk0x16c = 0;
}

// STUB: LEGORACERS 0x00493c90
void RaceSession::Field0x6dc::Field0x170::FUN_00493c90(const SetupParams* p_params)
{
	if (m_unk0x004 != NULL) {
		FUN_00493e60();
	}

	const SetupParams* params = p_params;

	m_unk0x000 = params->m_unk0x00;
	m_unk0x014 = params->m_material;
	m_unk0x0dc = params->m_unk0x0c;
	m_unk0x0e0 = params->m_unk0x10;
	m_unk0x0e4 = params->m_unk0x14;
	m_unk0x0e8 = m_unk0x0e4 + 1;
	m_unk0x0d8 = 1.0f / (LegoS32) m_unk0x0e0;

	LegoU32 i;
	for (i = 0; i < m_unk0x0e8; i++) {
		m_unk0x0ec[i] = params->m_unk0x18[i];
		m_unk0x128[i] = params->m_unk0x54[i];
	}

	LegoU32 modelIndexCount = m_unk0x0e4 * m_unk0x0dc * m_unk0x0e0;
	LegoU32 doubledIndexCount = 2 * modelIndexCount;
	LegoU32 segmentCount = m_unk0x0e0;
	m_unk0x13c = params->m_unk0x68;

	LegoU32 generatedPointCount;
	if (m_unk0x014->GetUnk0x08() & DuskwindBananaRelic0x24::c_flag0x08Bit3) {
		generatedPointCount = 0;
		if (m_unk0x13c <= segmentCount) {
			generatedPointCount = segmentCount - m_unk0x13c;
		}
		generatedPointCount += segmentCount + 1;
	}
	else {
		generatedPointCount = segmentCount + 1;
	}

	m_unk0x16c = generatedPointCount * m_unk0x0dc * m_unk0x0e8;
	if (segmentCount >= m_unk0x13c) {
		segmentCount = 2 * segmentCount - m_unk0x13c + 1;
	}

	LegoU32 stride = segmentCount * m_unk0x0e8;
	LegoU32 vertexCount = m_unk0x0dc * (2 * (0x40 / stride) + 5) + 2;
	m_unk0x004 = m_unk0x000->VTable0x14();
	m_unk0x004->VTable0x18(params->m_renderer, 1, m_unk0x16c, doubledIndexCount, vertexCount, 1);

	m_unk0x010 = m_unk0x000->VTable0x18();
	m_unk0x010->Allocate(m_unk0x0dc);
	m_unk0x018.FUN_00494c50(m_unk0x004, m_unk0x010, params->m_unk0x70, params->m_modelDistance);
	m_unk0x004->GetMaterialTable()->SetPosition(0, params->m_material);
}

// FUNCTION: LEGORACERS 0x00493e60
void RaceSession::Field0x6dc::Field0x170::FUN_00493e60()
{
	m_unk0x018.VTable0x54();

	if (m_unk0x000 != NULL) {
		if (m_unk0x010 != NULL) {
			m_unk0x000->VTable0x4c(m_unk0x010);
		}

		if (m_unk0x004 != NULL) {
			m_unk0x000->VTable0x48(m_unk0x004);
		}
	}

	Reset();
}

// STUB: LEGORACERS 0x00493ea0
void RaceSession::Field0x6dc::Field0x170::FUN_00493ea0(const GolVec3* p_position, const GolVec3* p_direction)
{
	m_unk0x004->VTable0x28(&m_unk0x008);

	IGdbModelIndexArray0x8* indexArray;
	m_unk0x004->VTable0x30(&indexArray);
	m_unk0x00c = static_cast<GdbModelIndexArray0xc*>(indexArray)->GetMutableIndices();

	m_unk0x140 &= ~c_flags0x140Bit0;
	m_unk0x0b0 = 0;
	m_unk0x0b4 = -static_cast<LegoS32>(m_unk0x0e8);
	m_unk0x0b8 = 0;
	m_unk0x0bc = 0;
	m_unk0x0c0 = 0;
	m_unk0x0c8 = 0;
	m_unk0x0c4 = 0;
	m_unk0x0cc = 1;
	m_unk0x0d0 = 0;
	m_unk0x0d4 = 1;

	m_unk0x004->GetMutableGroups()[0] = c_group0x80000000;
	m_unk0x004->SetDirty(TRUE);

	m_unk0x148 = *p_position;
	m_unk0x154 = *p_position;

	GolVec3 localPosition;
	localPosition.Clear();
	FUN_00494290(&localPosition, &m_unk0x160, 0, 0);

	m_unk0x018.VTable0x08(*p_position);

	GolVec3 direction;
	GolMath::NormalizeVector3(*p_direction, &direction);

	GolVec3 up;
	up.m_x = 0.0f;
	up.m_y = 0.0f;
	up.m_z = 1.0f;

	LegoFloat dot = GOLVECTOR3_DOT(direction, up);
	if (dot >= 1.0f || dot <= -1.0f) {
		up.m_x = 1.0f;
		up.m_y = 0.0f;
		up.m_z = 0.0f;
	}

	m_unk0x018.VTable0x40(direction, up);
}

// FUNCTION: LEGORACERS 0x00494030
void RaceSession::Field0x6dc::Field0x170::FUN_00494030(const GolVec3* p_position)
{
	GolTransformBase* transform = m_unk0x010->VTable0x18(m_unk0x0d0);

	GolVec3 vector;
	vector.m_x = m_unk0x154.m_x - m_unk0x148.m_x;
	vector.m_y = m_unk0x154.m_y - m_unk0x148.m_y;
	vector.m_z = m_unk0x154.m_z - m_unk0x148.m_z;

	GolVec3 transformed;
	m_unk0x018.VTable0x38(vector, &transformed);
	transform->SetPosition(&transformed);

	vector.m_x = p_position->m_x - m_unk0x154.m_x;
	vector.m_y = p_position->m_y - m_unk0x154.m_y;
	vector.m_z = p_position->m_z - m_unk0x154.m_z;
	m_unk0x018.VTable0x38(vector, &transformed);

	vector.m_x = 0.0f;
	vector.m_y = 0.0f;
	vector.m_z = 1.0f;
	transform->VTable0x28(&transformed, &vector);

	m_unk0x0d0++;
	m_unk0x154 = *p_position;
	m_unk0x140 &= ~c_flags0x140Bit2;
}

// FUNCTION: LEGORACERS 0x00494140
void RaceSession::Field0x6dc::Field0x170::FUN_00494140(const GolVec3* p_position)
{
	GolVec3 delta;
	delta.m_x = p_position->m_x - m_unk0x154.m_x;
	delta.m_y = p_position->m_y - m_unk0x154.m_y;
	delta.m_z = p_position->m_z - m_unk0x154.m_z;

	LegoFloat distanceSquared = GOLVECTOR3_DOT(delta, delta);
	if (distanceSquared < g_unk0x004b47a4) {
		return;
	}

	GolVec3 localPosition;
	localPosition.m_x = static_cast<LegoFloat>(::sqrt(distanceSquared));
	localPosition.m_y = 0.0f;
	localPosition.m_z = 0.0f;

	FUN_00494290(&localPosition, &m_unk0x160, m_unk0x0d4, 0);
	FUN_00494480();

	if (m_unk0x014->GetUnk0x08() & DuskwindBananaRelic0x24::c_flag0x08Bit3) {
		m_unk0x0d4++;
		if (m_unk0x0d4 > m_unk0x13c) {
			FUN_00494290(&localPosition, &m_unk0x160, 0, 0);
			m_unk0x0d4 = 1;
		}
	}

	FUN_004946b0();
	FUN_00494030(p_position);
}

// FUNCTION: LEGORACERS 0x00494230
void RaceSession::Field0x6dc::Field0x170::FUN_00494230()
{
	if (m_unk0x0c8 != 0) {
		FUN_004946b0();

		GolModelBase* model = m_unk0x004;
		model->GetMutableGroups()[m_unk0x0cc] = c_group0xc0000000;
		LegoU32 dirty = TRUE;
		model->SetDirty(dirty);
		m_unk0x140 |= dirty;
	}

	m_unk0x004->VTable0x34(FALSE);
	m_unk0x004->VTable0x2c(FALSE, FALSE);
}

// STUB: LEGORACERS 0x00494290
void RaceSession::Field0x6dc::Field0x170::FUN_00494290(
	const GolVec3* p_position,
	const ColorRGBA* p_color,
	LegoU32 p_textureColumn,
	LegoU32 p_offsetIndex
)
{
	if (m_unk0x0b4 + static_cast<LegoS32>(m_unk0x0e8 * 2) >= 0x40) {
		FUN_004944e0();
	}
	else {
		m_unk0x0b8 = m_unk0x0b4;
		m_unk0x0b4 += m_unk0x0e8;
	}

	for (LegoU32 i = 0; i < m_unk0x0e8; i++) {
		GolVec3 vertex;
		vertex.m_x = p_position->m_x + m_unk0x0ec[i].m_x;
		vertex.m_y = p_position->m_y + m_unk0x0ec[i].m_y;
		vertex.m_z = p_position->m_z + m_unk0x0ec[i].m_z;

		if (m_unk0x140 & c_flags0x140Bit1) {
			vertex += m_unk0x144[p_offsetIndex];
		}

		m_unk0x008->VTable0x24(m_unk0x0bc, vertex);
		m_unk0x008->VTable0x30(m_unk0x0bc, *p_color);

		GolVec2 texture;
		texture.m_x = static_cast<LegoFloat>(static_cast<LegoS32>(p_textureColumn));
		texture.m_y = m_unk0x128[i];
		m_unk0x008->VTable0x28(m_unk0x0bc, texture);

		m_unk0x0bc++;
	}
}

// STUB: LEGORACERS 0x00494480
void RaceSession::Field0x6dc::Field0x170::FUN_00494480()
{
	GdbModelIndexArray0xc::Indices* indices = &m_unk0x00c[m_unk0x0c8];
	m_unk0x0c8 += m_unk0x0e4 * 2;

	for (LegoU32 i = 0; i < m_unk0x0e4; i++) {
		indices->m_a = static_cast<LegoU8>(m_unk0x0b8 + i);
		indices->m_b = static_cast<LegoU8>(m_unk0x0b4 + i + 1);
		indices->m_c = static_cast<LegoU8>(m_unk0x0b4 + i);
		indices->m_x = 0;
		indices++;

		indices->m_a = static_cast<LegoU8>(m_unk0x0b8 + i);
		indices->m_b = static_cast<LegoU8>(m_unk0x0b8 + i + 1);
		indices->m_c = static_cast<LegoU8>(m_unk0x0b4 + i + 1);
		indices->m_x = 0;
		indices++;
	}
}

// STUB: LEGORACERS 0x004944e0
void RaceSession::Field0x6dc::Field0x170::FUN_004944e0()
{
	LegoU32 vertexCount = m_unk0x0bc - m_unk0x0c0;
	LegoU32 triangleCount = m_unk0x0c8 - m_unk0x0c4;
	LegoU32* groups = m_unk0x004->GetMutableGroups();

	if (vertexCount != 0 || triangleCount != 0) {
		if (!(m_unk0x140 & c_flags0x140Bit2)) {
			groups[m_unk0x0cc++] = c_group0xa0000000 | (m_unk0x0d0 & 0x00ffffff);
			m_unk0x004->SetDirty(TRUE);
			m_unk0x140 |= c_flags0x140Bit2;
		}

		groups[m_unk0x0cc++] =
			((m_unk0x0b0 & 0x3f) << 22) | (((vertexCount - 1) << 16) & 0x003f0000) | (m_unk0x0c0 & 0xffff);
		m_unk0x004->SetDirty(TRUE);
		groups[m_unk0x0cc++] = c_group0x20000000 | ((triangleCount & 0x7f) << 16) | (m_unk0x0c4 & 0xffff);
		m_unk0x004->SetDirty(TRUE);
	}

	groups[m_unk0x0cc++] = (((m_unk0x0e8 - 1) << 16) & 0x003f0000) | ((m_unk0x0bc - m_unk0x0e8) & 0xffff);
	m_unk0x004->SetDirty(TRUE);

	m_unk0x0b4 = m_unk0x0e8;
	m_unk0x0b0 = m_unk0x0e8;
	m_unk0x0b8 = 0;
	m_unk0x0c0 = m_unk0x0bc;
	m_unk0x0c4 = m_unk0x0c8;
}

// STUB: LEGORACERS 0x004946b0
void RaceSession::Field0x6dc::Field0x170::FUN_004946b0()
{
	LegoU32 vertexCount = m_unk0x0bc - m_unk0x0c0;
	LegoU32 triangleCount = m_unk0x0c8 - m_unk0x0c4;

	if (vertexCount == 0 && triangleCount == 0) {
		return;
	}

	LegoU32* groups = m_unk0x004->GetMutableGroups();
	if (!(m_unk0x140 & c_flags0x140Bit2)) {
		groups[m_unk0x0cc++] = c_group0xa0000000 | (m_unk0x0d0 & 0x00ffffff);
		m_unk0x004->SetDirty(TRUE);
		m_unk0x140 |= c_flags0x140Bit2;
	}

	groups[m_unk0x0cc++] =
		((m_unk0x0b0 & 0x3f) << 22) | (((vertexCount - 1) << 16) & 0x003f0000) | (m_unk0x0c0 & 0xffff);
	m_unk0x004->SetDirty(TRUE);
	groups[m_unk0x0cc++] = c_group0x20000000 | ((triangleCount & 0x7f) << 16) | (m_unk0x0c4 & 0xffff);
	m_unk0x004->SetDirty(TRUE);

	m_unk0x0b0 += vertexCount;
	m_unk0x0c0 = m_unk0x0bc;
	m_unk0x0c4 = m_unk0x0c8;
}

// FUNCTION: LEGORACERS 0x00494820
void RaceSession::Field0x6dc::Field0x170::FUN_00494820(
	const ColorRGBA* p_unk0x04,
	const ColorRGBA* p_unk0x08,
	const ColorRGBA* p_unk0x0c
)
{
	m_unk0x160 = *p_unk0x04;
	m_unk0x164 = *p_unk0x08;
	m_unk0x168 = *p_unk0x0c;
}

// FUNCTION: LEGORACERS 0x00494850
void RaceSession::Field0x6dc::Field0x170::FUN_00494850(GolD3DRenderDevice* p_renderer)
{
	if (m_unk0x140 & 1) {
		m_unk0x018.VTable0x1c(*p_renderer);
	}
}

// STUB: LEGORACERS 0x00494870
void RaceSession::Field0x6dc::Field0x170::FUN_00494870(const GolVec3* p_position, LegoFloat p_amount)
{
	if (m_unk0x0e0 <= 1) {
		FUN_00494140(p_position);
		return;
	}

	GolVec3 delta;
	delta.m_x = p_position->m_x - m_unk0x154.m_x;
	delta.m_y = p_position->m_y - m_unk0x154.m_y;
	delta.m_z = p_position->m_z - m_unk0x154.m_z;

	LegoFloat distanceSquared = GOLVECTOR3_DOT(delta, delta);
	if (distanceSquared <= 0.0f) {
		return;
	}

	LegoFloat distance = static_cast<LegoFloat>(::sqrt(distanceSquared));
	LegoFloat stepDistance = distance * m_unk0x0d8;
	const ColorRGBA* endColor = p_amount > 0.0f ? &m_unk0x164 : &m_unk0x168;
	LegoU32 offsetIndex = 0;

	for (LegoU32 i = 0; i < m_unk0x0e0 - 1; i++) {
		LegoFloat amount = p_amount + m_unk0x0d8 * static_cast<LegoFloat>(static_cast<LegoS32>(i + 1));

		GolVec3 localPosition;
		localPosition.m_x = stepDistance * static_cast<LegoFloat>(static_cast<LegoS32>(i + 1));
		localPosition.m_y = 0.0f;
		localPosition.m_z = 0.0f;

		ColorRGBA color;
		GolVec3 worldPosition;
		FUN_00494ad0(&m_unk0x154, p_position, &m_unk0x160, endColor, &color, &worldPosition, amount);

		FUN_00494290(&localPosition, &color, m_unk0x0d4, offsetIndex);
		FUN_00494480();

		if (m_unk0x014->GetUnk0x08() & DuskwindBananaRelic0x24::c_flag0x08Bit3) {
			m_unk0x0d4++;
			if (m_unk0x0d4 > m_unk0x13c) {
				FUN_00494290(&localPosition, &color, 0, offsetIndex);
				m_unk0x0d4 = 1;
			}
		}

		offsetIndex++;
	}

	GolVec3 localPosition;
	localPosition.m_x = distance;
	localPosition.m_y = 0.0f;
	localPosition.m_z = 0.0f;
	FUN_00494290(&localPosition, endColor, m_unk0x0d4, offsetIndex);
	FUN_00494480();

	if (m_unk0x014->GetUnk0x08() & DuskwindBananaRelic0x24::c_flag0x08Bit3) {
		m_unk0x0d4++;
		if (m_unk0x0d4 > m_unk0x13c) {
			m_unk0x0d4 = 1;
		}
	}

	FUN_004946b0();
	FUN_00494030(p_position);
}

// STUB: LEGORACERS 0x00494ad0
void RaceSession::Field0x6dc::Field0x170::FUN_00494ad0(
	const GolVec3* p_fromPosition,
	const GolVec3* p_toPosition,
	const ColorRGBA* p_fromColor,
	const ColorRGBA* p_toColor,
	ColorRGBA* p_colorResult,
	GolVec3* p_positionResult,
	LegoFloat p_amount
)
{
	p_positionResult->m_x = p_fromPosition->m_x + (p_toPosition->m_x - p_fromPosition->m_x) * p_amount;
	p_positionResult->m_y = p_fromPosition->m_y + (p_toPosition->m_y - p_fromPosition->m_y) * p_amount;
	p_positionResult->m_z = p_fromPosition->m_z + (p_toPosition->m_z - p_fromPosition->m_z) * p_amount;

	p_colorResult->m_red = static_cast<LegoU8>(
		p_fromColor->m_red + static_cast<LegoS32>((p_toColor->m_red - p_fromColor->m_red) * p_amount)
	);
	p_colorResult->m_grn = static_cast<LegoU8>(
		p_fromColor->m_grn + static_cast<LegoS32>((p_toColor->m_grn - p_fromColor->m_grn) * p_amount)
	);
	p_colorResult->m_blu = static_cast<LegoU8>(
		p_fromColor->m_blu + static_cast<LegoS32>((p_toColor->m_blu - p_fromColor->m_blu) * p_amount)
	);
	p_colorResult->m_alp = static_cast<LegoU8>(
		p_fromColor->m_alp + static_cast<LegoS32>((p_toColor->m_alp - p_fromColor->m_alp) * p_amount)
	);
}

// FUNCTION: LEGORACERS 0x00494be0
void RaceSession::Field0x6dc::Field0x170::FUN_00494be0(const GolVec3* p_offsets)
{
	m_unk0x144 = p_offsets;
	m_unk0x140 |= c_flags0x140Bit1;
}

// FUNCTION: LEGORACERS 0x00494c00
RaceSession::Field0x6dc::Field0x98::Field0x98()
{
	m_unk0x90 = 0;
	m_unk0x94 = 0;
}

// FUNCTION: LEGORACERS 0x00494c20
RaceSession::Field0x6dc::Field0x98* RaceSession::Field0x6dc::Field0x98::FUN_00494c20(undefined4 p_flags)
{
	Field0x98* result = this;
	this->~Field0x98();
	if (p_flags & 1) {
		::operator delete(result);
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00494c40
RaceSession::Field0x6dc::Field0x98::~Field0x98()
{
	VTable0x54();
}

// FUNCTION: LEGORACERS 0x00494c50
void RaceSession::Field0x6dc::Field0x98::FUN_00494c50(
	GolModelBase* p_model,
	GolSceneNode* p_sceneNode,
	undefined4 p_unk0x0c,
	LegoFloat p_modelDistance
)
{
	GolModelEntity::VTable0x50(p_model, p_modelDistance);
	m_unk0x90 = p_sceneNode;
	m_unk0x94 = p_unk0x0c;
}

// FUNCTION: LEGORACERS 0x00494c80
void RaceSession::Field0x6dc::Field0x98::VTable0x54()
{
	m_unk0x90 = 0;
}

// FUNCTION: LEGORACERS 0x00494c90
GolSceneNode* RaceSession::Field0x6dc::Field0x98::VTable0x58(undefined4)
{
	return m_unk0x90;
}

// STUB: LEGORACERS 0x00494ca0
void RaceSession::Field0x6dc::Field0x98::VTable0x1c(GolRenderDevice& p_renderer)
{
	if (m_unk0x94 != 0) {
		GolVec3 cameraRight;
		p_renderer.GetUnk0x0c()->GetTransform()->GetRight(&cameraRight);
		cameraRight.m_x = -cameraRight.m_x;
		cameraRight.m_y = -cameraRight.m_y;
		cameraRight.m_z = -cameraRight.m_z;

		GolVec3 localRight;
		VTable0x38(cameraRight, &localRight);

		for (LegoU32 i = 0; i < m_unk0x90->GetCapacity(); i++) {
			GolTransformBase* transform = m_unk0x90->VTable0x18(i);
			GolVec3 right;
			transform->VTable0x20(&cameraRight, &right);

			LegoFloat dot =
				localRight.m_z * cameraRight.m_z + localRight.m_y * cameraRight.m_y + localRight.m_x * cameraRight.m_x;
			if (dot < 1.0f && dot > g_minSoundPan) {
				transform->VTable0x28(&cameraRight, &localRight);
			}
		}
	}

	p_renderer.VTable0x94(this);
}
