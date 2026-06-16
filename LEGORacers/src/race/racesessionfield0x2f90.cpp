#include "core/gol.h"
#include "golanimatedentity.h"
#include "mesh/gdbvertexarray0xc.h"
#include "mesh/golmodelbase.h"
#include "race/racesession.h"
#include "world/golworlddatabase.h"

DECOMP_SIZE_ASSERT(RaceSession::Field0x2f90, 0xc8)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2f90::Entry, 0x10)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2f90::Entry::Keyframe, 0x10)

// GLOBAL: LEGORACERS 0x004afddc
extern const LegoFloat g_unk0x004afddc = 40.0f;

extern const LegoFloat g_unk0x004afde0;

// FUNCTION: LEGORACERS 0x0041c430
RaceSession::Field0x2f90::Field0x2f90()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0041c4b0
RaceSession::Field0x2f90::~Field0x2f90()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x0041c500
void RaceSession::Field0x2f90::Reset()
{
	m_entries = NULL;
	m_count = 0;
	m_unk0xb8 = 0;
	m_unk0xb4 = 0;
	m_unk0xbc = 0;
	m_unk0xc0 = 0;
	m_unk0xa0 = NULL;
	m_unk0xa4 = NULL;
	m_unk0xc4 = 0;
	m_unk0x9c = NULL;
	m_unk0xac = 0.0f;
}

// FUNCTION: LEGORACERS 0x0041cbe0
void RaceSession::Field0x2f90::Clear()
{
	if (m_unk0x9c) {
		m_unk0xa4->VTable0x3c(m_unk0x9c);
		m_unk0x9c = NULL;
	}

	if (m_unk0xa0) {
		m_unk0xa4->VTable0x48(m_unk0xa0);
		m_unk0xa0 = NULL;
	}

	m_unk0xa4 = NULL;
	m_unk0x0c.VTable0x54();

	if (m_nameEntries != NULL) {
		GolNameTable::Clear();
	}

	if (m_entries) {
		LegoU32 i;

		for (i = 0; i < m_count; i++) {
			if (m_entries[i].m_unk0x08) {
				delete[] m_entries[i].m_unk0x08;
				m_entries[i].m_unk0x08 = NULL;
			}
		}

		delete[] m_entries;
		m_entries = NULL;
	}

	Reset();
}

// FUNCTION: LEGORACERS 0x0041ccb0
void RaceSession::Field0x2f90::FUN_0041ccb0(LegoU32 p_elapsedMs)
{
	m_unk0x9c->FUN_00416090(p_elapsedMs);

	for (LegoU32 count = 0; count < m_count; count++) {
		m_entries[count].m_unk0x00 += p_elapsedMs;
		if (m_entries[count].m_unk0x00 > m_entries[count].m_unk0x08[m_entries[count].m_unk0x04].m_unk0x00) {
			m_entries[count].m_unk0x04++;
			if (m_entries[count].m_unk0x04 == m_entries[count].m_unk0x0c) {
				m_entries[count].m_unk0x04 = 0;
			}

			m_entries[count].m_unk0x00 = 0;
		}
	}

	if (m_unk0xbc > 0) {
		m_unk0xc0 += p_elapsedMs;
		if (m_unk0xc0 > m_unk0xbc) {
			m_unk0xbc = 0;
			m_unk0xc0 = 0;
		}
	}

	ColorRGBA color0;
	ColorRGBA color1;
	ColorRGBA color2;
	FUN_0041ce60(&m_entries[m_unk0xb8], &color0, &color1, &color2);

	if (m_unk0xbc > 0) {
		ColorRGBA transitionColor0;
		ColorRGBA transitionColor1;
		ColorRGBA transitionColor2;
		FUN_0041ce60(&m_entries[m_unk0xb4], &transitionColor0, &transitionColor1, &transitionColor2);

		LegoFloat elapsedMs = static_cast<LegoFloat>(static_cast<LegoS32>(m_unk0xc0));
		LegoFloat transitionMs = static_cast<LegoFloat>(static_cast<LegoS32>(m_unk0xbc));
		LegoFloat amount = elapsedMs / transitionMs;
		FUN_0041cf20(&transitionColor0, &color0, &color0, amount);
		FUN_0041cf20(&transitionColor1, &color1, &color1, amount);
		FUN_0041cf20(&transitionColor2, &color2, &color2, amount);
	}

	FUN_0041cfc0(&color0, &color1, &color2);
}

// FUNCTION: LEGORACERS 0x0041ce60
void RaceSession::Field0x2f90::FUN_0041ce60(
	Entry* p_entry,
	ColorRGBA* p_unk0x08,
	ColorRGBA* p_unk0x0c,
	ColorRGBA* p_unk0x10
)
{
	LegoU32 keyframeCount = p_entry->m_unk0x0c;

	if (keyframeCount == 1) {
		*p_unk0x08 = p_entry->m_unk0x08[0].m_unk0x04;
		*p_unk0x0c = p_entry->m_unk0x08[0].m_unk0x08;
		*p_unk0x10 = p_entry->m_unk0x08[0].m_unk0x0c;
	}
	else {
		LegoU32 keyframeIndex = p_entry->m_unk0x04;
		LegoU32 nextIndex = (keyframeIndex + 1) % keyframeCount;
		LegoFloat elapsedMs = static_cast<LegoFloat>(static_cast<LegoS32>(p_entry->m_unk0x00));
		LegoFloat keyframeMs =
			static_cast<LegoFloat>(static_cast<LegoS32>(p_entry->m_unk0x08[p_entry->m_unk0x04].m_unk0x00));
		LegoFloat amount = elapsedMs / keyframeMs;

		FUN_0041cf20(
			&p_entry->m_unk0x08[p_entry->m_unk0x04].m_unk0x04,
			&p_entry->m_unk0x08[nextIndex].m_unk0x04,
			p_unk0x08,
			amount
		);
		FUN_0041cf20(
			&p_entry->m_unk0x08[p_entry->m_unk0x04].m_unk0x08,
			&p_entry->m_unk0x08[nextIndex].m_unk0x08,
			p_unk0x0c,
			amount
		);
		FUN_0041cf20(
			&p_entry->m_unk0x08[p_entry->m_unk0x04].m_unk0x0c,
			&p_entry->m_unk0x08[nextIndex].m_unk0x0c,
			p_unk0x10,
			amount
		);
	}
}

// FUNCTION: LEGORACERS 0x0041cf20
void RaceSession::Field0x2f90::FUN_0041cf20(
	const ColorRGBA* p_from,
	const ColorRGBA* p_to,
	ColorRGBA* p_result,
	LegoFloat p_amount
)
{
	LegoFloat inverseAmount = 1.0f - p_amount;

	p_result->m_red = static_cast<LegoU8>(p_from->m_red * inverseAmount + p_to->m_red * p_amount);
	p_result->m_grn = static_cast<LegoU8>(p_from->m_grn * inverseAmount + p_to->m_grn * p_amount);
	p_result->m_blu = static_cast<LegoU8>(p_from->m_blu * inverseAmount + p_to->m_blu * p_amount);
}

// FUNCTION: LEGORACERS 0x0041cfc0
void RaceSession::Field0x2f90::FUN_0041cfc0(
	const ColorRGBA* p_unk0x04,
	const ColorRGBA* p_unk0x08,
	const ColorRGBA* p_unk0x0c
)
{
	GdbVertexArray0xc* vertices;
	const ColorRGBA* color = NULL;

	m_unk0xa0->VTable0x28(&vertices);

	LegoU32 i;
	for (i = 0; i < 3; i++) {
		switch (i) {
		case 0:
			color = p_unk0x0c;
			break;
		case 1:
			color = p_unk0x08;
			break;
		case 2:
			color = p_unk0x04;
			break;
		}

		for (LegoU32 j = 0; j < 11; j++) {
			vertices->VTable0x30(i * 11 + j, *color);
		}
	}

	m_unk0xa0->VTable0x2c(1, FALSE);
}

// FUNCTION: LEGORACERS 0x0041d040
void RaceSession::Field0x2f90::FUN_0041d040(GolVec3* p_position)
{
	p_position->m_z -= g_unk0x004afde0 - m_unk0xac;
	m_unk0x0c.VTable0x08(*p_position);
	p_position->m_z += g_unk0x004afddc - m_unk0xac;

	LegoU32 i;
	for (i = 0; i < m_unk0x9c->GetUnk0x4c(); i++) {
		m_unk0x9c->GetUnk0x9c()[i].VTable0x08(*p_position);
	}

	for (i = 0; i < m_unk0x9c->GetUnk0x54(); i++) {
		GolWorldEntity* entity = &m_unk0x9c->GetUnk0xa0()[i];
		entity->VTable0x08(*p_position);
	}
}

// FUNCTION: LEGORACERS 0x0041d0f0
void RaceSession::Field0x2f90::FUN_0041d0f0(GolD3DRenderDevice* p_renderer)
{
	LegoU8 flags = m_unk0xc4;
	flags = ~flags;
	if (flags & c_flag0xc4Bit0) {
		p_renderer->VTable0xe8(TRUE);
		p_renderer->VTable0x94(&m_unk0x0c);

		flags = m_unk0xc4;
		flags = ~flags;
		if (flags & c_flag0xc4Bit1) {
			m_unk0x9c->FUN_00416040();
		}

		p_renderer->VTable0xe4();
	}
}
