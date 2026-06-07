#include "racer/siennacircuit0x154.h"

#include "audio/soundgroupbinding.h"
#include "core/gol.h"
#include "decomp.h"
#include "golmath.h"
#include "mesh/golmodelbase.h"
#include "model/carbuildmodel.h"
#include "model/carpartset.h"
#include "model/legopiecelibrary.h"
#include "render/gold3drenderdevice.h"

#include <float.h>
#include <string.h>

DECOMP_SIZE_ASSERT(SiennaCircuit0x154, 0x154)
DECOMP_SIZE_ASSERT(SiennaCircuit0x154::CreateParams, 0x84)

// GLOBAL: LEGORACERS 0x004b02f8
extern const LegoFloat g_siennaCircuitTwoPi = 6.2831855f;

// GLOBAL: LEGORACERS 0x004b3c0c
LegoFloat g_siennaCircuitMaxFloat = FLT_MAX;

// GLOBAL: LEGORACERS 0x004bf9b4
LegoFloat g_siennaCircuitVectorZ = 0.76516724f;

// GLOBAL: LEGORACERS 0x004c05b4
LegoFloat g_siennaCircuitVectorX = 0.64383155f;

// FUNCTION: LEGORACERS 0x00485200
SiennaCircuit0x154::SiennaCircuit0x154()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00485270
SiennaCircuit0x154::~SiennaCircuit0x154()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x004852c0
void SiennaCircuit0x154::Reset()
{
	m_pieceLibrary = NULL;
	m_unk0xc8 = NULL;
	m_unk0xcc = NULL;
	m_unk0xc0 = NULL;
	m_unk0x14c = 0;
	m_unk0x150 = 0.0f;
	::memset(m_unk0xd4, 0, sizeof(m_unk0xd4));
	MenuModelCarousel::Reset();
}

// FUNCTION: LEGORACERS 0x00485300
LegoBool32 SiennaCircuit0x154::FUN_00485300(CreateParams* p_createParams, MenuStyleTable::CarouselStyle* p_styleEntry)
{
	m_unk0xc0 = p_createParams->m_unk0x74;
	m_pieceLibrary = p_createParams->m_pieceLibrary;
	m_unk0xc8 = p_createParams->m_unk0x7c;
	m_unk0xcc = p_createParams->m_unk0x80;
	if (FUN_0046cb10(p_createParams, p_styleEntry)) {
		FUN_004853a0();
	}

	return m_flags & 1;
}

// FUNCTION: LEGORACERS 0x00485350
LegoBool32 SiennaCircuit0x154::VTable0x08()
{
	LegoBool32 result = TRUE;

	if (result & m_flags) {
		for (LegoS32 i = 0; i < m_unk0x60; i++) {
			m_golExport->VTable0x48(m_unk0x7c[i].m_model);
			m_unk0x7c[i].m_model = NULL;
		}

		result = MenuModelCarousel::VTable0x08();
	}

	return result;
}

// FUNCTION: LEGORACERS 0x004853a0
LegoS32 SiennaCircuit0x154::FUN_004853a0()
{
	LegoS32 maxHighPieceOffset = m_pieceLibrary->GetMaxHighPieceOffset();
	LegoS32 result = m_unk0x60;

	for (LegoS32 i = 0; i < result; i++) {
		GolModelBase* model = GetItemModel(i);
		model->VTable0x18(m_renderer, 2, 3 * maxHighPieceOffset, maxHighPieceOffset, 100, 5);
		result = m_unk0x60;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x004853f0
void SiennaCircuit0x154::FUN_004853f0()
{
	m_unk0xd0->FUN_004513d0(m_unk0xc8);
	m_unk0xd0->FillChoiceIndices(m_unk0xd4, 0, 30);

	for (m_unk0x68 = 0; m_unk0x68 < 30; m_unk0x68++) {
		if (m_unk0xd4[m_unk0x68] < 0) {
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x00485440
void SiennaCircuit0x154::FUN_00485440(LegoS32 p_unk0x04)
{
	if (p_unk0x04 == m_unk0x14c) {
		FUN_004853f0();
		return;
	}

	m_unk0x70 = 0;
	m_unk0x74 = 0;
	m_unk0xd0 = m_unk0xc0->FindEntry(p_unk0x04);
	m_unk0x14c = p_unk0x04;
	FUN_004853f0();
	VTable0x50(0);
}

// FUNCTION: LEGORACERS 0x004854a0
void SiennaCircuit0x154::VTable0x60(LegoS32 p_index)
{
	GolModelEntity* entity = GetItemEntity(p_index);
	GolModelBase* model = GetItemModel(p_index);
	LegoS32 choiceIndex = m_unk0xd4[FUN_0046c9a0(m_unk0xb8 + p_index)];
	LegoS32 pieceType;
	LegoS32 colorRecordIndex;

	m_unk0xd0->GetChoice(choiceIndex, &pieceType, &colorRecordIndex);
	entity->VTable0x50(model, g_siennaCircuitMaxFloat);

	LegoPieceLibrary::PieceRecord* pieceRecord = m_pieceLibrary->FindPieceRecord(pieceType, 1);
	m_unk0xc8->FUN_0049b8b0(pieceRecord, 0);
	m_unk0xc8->FUN_0049b170(entity, pieceRecord, 0, 0, 0, 0, colorRecordIndex, 239);
	MenuModelCarousel::VTable0x60(p_index);
}

// FUNCTION: LEGORACERS 0x00485550
void SiennaCircuit0x154::VTable0x5c(undefined4, GolModelEntity* p_entity)
{
	GolVec3 axis = {1.0f, 0.0f, 0.0f};
	GolVec3 vector = {g_siennaCircuitVectorX, 0.0f, g_siennaCircuitVectorZ};

	GolMath::FUN_004496a0(&axis, &axis, &vector, m_unk0x150);
	p_entity->FUN_00410b00(vector, axis);
}

// FUNCTION: LEGORACERS 0x004855c0
void SiennaCircuit0x154::VTable0x50(undefined4 p_index)
{
	if (m_unk0x68) {
		m_unk0x6c = p_index;
		m_unk0xb8 = FUN_0046c9a0(p_index - m_unk0x64);

		if (!m_unk0x70) {
			if (m_unk0x68 >= m_unk0x60 - 1) {
				for (LegoS32 i = 0; i < m_unk0x60; i++) {
					VTable0x60(i);
				}
			}
			else {
				for (LegoS32 i = 0; i < m_unk0x60; i++) {
					GetItemEntity(i)->VTable0x54();
				}

				VTable0x60(m_unk0x64);

				LegoS32 index = m_unk0x64;
				LegoS32 previousVisibleIndex = index - 1;
				if (m_unk0x6c <= index) {
					index = m_unk0x6c;
				}
				index--;

				if (index >= 0) {
					LegoS32 count = index + 1;
					do {
						VTable0x60(previousVisibleIndex--);
					} while (--count);
				}

				LegoS32 baseIndex = static_cast<LegoS32>(m_unk0x64);
				LegoS32 count;
				if (m_unk0x6c < baseIndex) {
					count = m_unk0x60 - baseIndex - 1;
				}
				else {
					count = m_unk0x68 - m_unk0x6c;
				}

				if (count) {
					LegoS32 nextVisibleIndex = baseIndex + 1;
					do {
						VTable0x60(nextVisibleIndex++);
					} while (--count);
				}
			}

			VTable0x40();
		}
	}
}

// FUNCTION: LEGORACERS 0x004856c0
void SiennaCircuit0x154::FUN_004856c0(LegoS32 p_unk0x04, LegoS32 p_unk0x08)
{
	LegoS32 result = 0;
	LegoS32 firstChoiceIndex = m_unk0xd0->NormalizeChoiceIndex(0);
	LegoS32 choiceIndex = m_unk0xd0->FindChoiceIndex(p_unk0x04, p_unk0x08);

	for (; firstChoiceIndex != choiceIndex; result++) {
		firstChoiceIndex = m_unk0xd0->NormalizeChoiceIndex(firstChoiceIndex + 1);
	}

	VTable0x50(result);
}

// FUNCTION: LEGORACERS 0x00485720
LegoS32 SiennaCircuit0x154::VTable0x54()
{
	if (!m_unk0x68) {
		return 0;
	}

	if (!m_unk0x70) {
		if (m_unk0x6c >= m_unk0x68 - 1 && m_unk0x68 < m_unk0x60 - 1) {
			m_unk0x5c->FUN_0046e970(m_unk0x58->m_unk0x00[2]);
			return m_unk0x6c;
		}

		MenuModelCarousel::VTable0x54();
		VTable0x50(FUN_0046c9a0(m_unk0x6c + 1));

		if (m_unk0x68 >= m_unk0x60 - 1 || m_unk0x68 - m_unk0x6c > m_unk0x60 - static_cast<LegoS32>(m_unk0x64) - 1) {
			VTable0x60(m_unk0x60 - 1);
		}

		m_unk0x5c->FUN_0046e970(m_unk0x58->m_unk0x00[0]);
	}

	return m_unk0x6c;
}

// FUNCTION: LEGORACERS 0x004857b0
LegoS32 SiennaCircuit0x154::VTable0x58()
{
	if (!m_unk0x68) {
		return 0;
	}

	if (!m_unk0x70) {
		if (!m_unk0x6c && m_unk0x68 < m_unk0x60 - 1) {
			m_unk0x5c->FUN_0046e970(m_unk0x58->m_unk0x00[2]);
			return m_unk0x6c;
		}

		MenuModelCarousel::VTable0x58();
		VTable0x50(FUN_0046c9a0(m_unk0x6c - 1));

		if (m_unk0x68 >= m_unk0x60 - 1 || m_unk0x6c > static_cast<LegoS32>(m_unk0x64) - 1) {
			VTable0x60(0);
		}

		m_unk0x5c->FUN_0046e970(m_unk0x58->m_unk0x00[1]);
	}

	return m_unk0x6c;
}

// FUNCTION: LEGORACERS 0x00485840
undefined4 SiennaCircuit0x154::VTable0x3c(undefined4 p_elapsed)
{
	if ((m_unk0x150 += m_unk0xbc * (LegoS32) p_elapsed) > g_siennaCircuitTwoPi) {
		m_unk0x150 -= g_siennaCircuitTwoPi;
	}

	return MenuModelCarousel::VTable0x3c(p_elapsed);
}
