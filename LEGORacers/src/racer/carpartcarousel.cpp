#include "racer/carpartcarousel.h"

#include "audio/soundgroupbinding.h"
#include "core/gol.h"
#include "decomp.h"
#include "golmath.h"
#include "golmodelbase.h"
#include "model/carbuildmodel.h"
#include "model/carpartset.h"
#include "model/legopiecelibrary.h"
#include "render/gold3drenderdevice.h"

#include <float.h>
#include <string.h>

DECOMP_SIZE_ASSERT(CarPartCarousel, 0x154)
DECOMP_SIZE_ASSERT(CarPartCarousel::CreateParams, 0x84)

// GLOBAL: LEGORACERS 0x004b02f8
extern const LegoFloat g_twoPi = 6.2831855f;

// GLOBAL: LEGORACERS 0x004b3c0c
LegoFloat g_maxFloat = FLT_MAX;

extern LegoFloat g_cosineTable[1024];

// FUNCTION: LEGORACERS 0x00485200
CarPartCarousel::CarPartCarousel()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00485270
CarPartCarousel::~CarPartCarousel()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x004852c0
void CarPartCarousel::Reset()
{
	m_pieceLibrary = NULL;
	m_buildModel = NULL;
	m_colorTable = NULL;
	m_partSet = NULL;
	m_currentPieceType = 0;
	m_rotationAngle = 0.0f;
	::memset(m_choiceIndices, 0, sizeof(m_choiceIndices));
	MenuModelCarousel::Reset();
}

// FUNCTION: LEGORACERS 0x00485300
LegoBool32 CarPartCarousel::Create(CreateParams* p_createParams, MenuStyleTable::CarouselStyle* p_styleEntry)
{
	m_partSet = p_createParams->m_partSet;
	m_pieceLibrary = p_createParams->m_pieceLibrary;
	m_buildModel = p_createParams->m_buildModel;
	m_colorTable = p_createParams->m_colorTable;
	if (FUN_0046cb10(p_createParams, p_styleEntry)) {
		FUN_004853a0();
	}

	return m_flags & 1;
}

// FUNCTION: LEGORACERS 0x00485350
LegoBool32 CarPartCarousel::VTable0x08()
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
LegoS32 CarPartCarousel::FUN_004853a0()
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
void CarPartCarousel::RefreshChoiceIndices()
{
	m_currentEntry->FUN_004513d0(m_buildModel);
	m_currentEntry->FillChoiceIndices(m_choiceIndices, 0, 30);

	for (m_unk0x68 = 0; m_unk0x68 < 30; m_unk0x68++) {
		if (m_choiceIndices[m_unk0x68] < 0) {
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x00485440
void CarPartCarousel::SelectPartByType(LegoS32 p_pieceType)
{
	if (p_pieceType == m_currentPieceType) {
		RefreshChoiceIndices();
		return;
	}

	m_unk0x70 = 0;
	m_unk0x74 = 0;
	m_currentEntry = m_partSet->FindEntry(p_pieceType);
	m_currentPieceType = p_pieceType;
	RefreshChoiceIndices();
	VTable0x50(0);
}

// FUNCTION: LEGORACERS 0x004854a0
void CarPartCarousel::VTable0x60(LegoS32 p_index)
{
	GolModelEntity* entity = GetItemEntity(p_index);
	GolModelBase* model = GetItemModel(p_index);
	LegoS32 choiceIndex = m_choiceIndices[FUN_0046c9a0(m_unk0xb8 + p_index)];
	LegoS32 pieceType;
	LegoS32 colorRecordIndex;

	m_currentEntry->GetChoice(choiceIndex, &pieceType, &colorRecordIndex);

	LegoFloat maxDistance = g_maxFloat;
	entity->VTable0x50(model, maxDistance);

	LegoPieceLibrary::PieceRecord* pieceRecord = m_pieceLibrary->FindPieceRecord(pieceType, 1);
	m_buildModel->FUN_0049b8b0(pieceRecord, 0);
	m_buildModel->FUN_0049b170(entity, pieceRecord, 0, 0, 0, 0, colorRecordIndex, 239);
	MenuModelCarousel::VTable0x60(p_index);
}

// FUNCTION: LEGORACERS 0x00485550
void CarPartCarousel::VTable0x5c(undefined4, GolModelEntity* p_entity)
{
	LegoFloat vectorX = g_cosineTable[c_vectorXCosineIndex];
	LegoFloat vectorZ = g_cosineTable[c_vectorZCosineIndex];
	GolVec3 axis = {1.0f, 0.0f, 0.0f};
	GolVec3 vector = {vectorX, 0.0f, vectorZ};

	GolMath::FUN_004496a0(&axis, &axis, &vector, m_rotationAngle);
	p_entity->FUN_00410b00(vector, axis);
}

// FUNCTION: LEGORACERS 0x004855c0
void CarPartCarousel::VTable0x50(undefined4 p_index)
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
				LegoS32 nextVisibleIndex = baseIndex + 1;
				LegoS32 count;
				if (m_unk0x6c >= baseIndex) {
					count = m_unk0x68 - m_unk0x6c;
				}
				else {
					count = m_unk0x60 - baseIndex - 1;
				}

				while (count--) {
					VTable0x60(nextVisibleIndex++);
				}
			}

			VTable0x40();
		}
	}
}

// FUNCTION: LEGORACERS 0x004856c0
void CarPartCarousel::SelectChoice(LegoS32 p_pieceType, LegoS32 p_colorRecordIndex)
{
	LegoS32 result = 0;
	LegoS32 firstChoiceIndex = m_currentEntry->NormalizeChoiceIndex(0);
	LegoS32 choiceIndex = m_currentEntry->FindChoiceIndex(p_pieceType, p_colorRecordIndex);

	for (; firstChoiceIndex != choiceIndex; result++) {
		firstChoiceIndex = m_currentEntry->NormalizeChoiceIndex(firstChoiceIndex + 1);
	}

	VTable0x50(result);
}

// FUNCTION: LEGORACERS 0x00485720
LegoS32 CarPartCarousel::VTable0x54()
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
LegoS32 CarPartCarousel::VTable0x58()
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
undefined4 CarPartCarousel::VTable0x3c(undefined4 p_elapsed)
{
	LegoFloat step = m_unk0xbc;
	LegoFloat scaled = (LegoFloat) (LegoS32) p_elapsed;
	if ((m_rotationAngle += step * scaled) > g_twoPi) {
		m_rotationAngle -= g_twoPi;
	}

	return MenuModelCarousel::VTable0x3c(p_elapsed);
}
