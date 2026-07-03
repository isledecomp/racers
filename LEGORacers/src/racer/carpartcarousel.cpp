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
	Destroy();
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
	if (MenuModelCarousel::Create(p_createParams, p_styleEntry)) {
		InitializeItemModels();
	}

	return m_flags & 1;
}

// FUNCTION: LEGORACERS 0x00485350
LegoBool32 CarPartCarousel::Destroy()
{
	LegoBool32 result = TRUE;

	if (result & m_flags) {
		for (LegoS32 i = 0; i < m_slotCount; i++) {
			m_golExport->DestroyModel(m_items[i].m_model);
			m_items[i].m_model = NULL;
		}

		result = MenuModelCarousel::Destroy();
	}

	return result;
}

// FUNCTION: LEGORACERS 0x004853a0
LegoS32 CarPartCarousel::InitializeItemModels()
{
	LegoS32 maxHighPieceOffset = m_pieceLibrary->GetMaxHighPieceOffset();
	LegoS32 result = m_slotCount;

	for (LegoS32 i = 0; i < result; i++) {
		GolModelBase* model = GetItemModel(i);
		model->Allocate(m_renderer, 2, 3 * maxHighPieceOffset, maxHighPieceOffset, 100, 5);
		result = m_slotCount;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x004853f0
void CarPartCarousel::RefreshChoiceIndices()
{
	m_currentEntry->FUN_004513d0(m_buildModel);
	m_currentEntry->FillChoiceIndices(m_choiceIndices, 0, 30);

	for (m_itemCount = 0; m_itemCount < 30; m_itemCount++) {
		if (m_choiceIndices[m_itemCount] < 0) {
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

	m_scrolling = 0;
	m_scrollDurationMs = 0;
	m_currentEntry = m_partSet->FindEntry(p_pieceType);
	m_currentPieceType = p_pieceType;
	RefreshChoiceIndices();
	SetSelection(0);
}

// FUNCTION: LEGORACERS 0x004854a0
void CarPartCarousel::RefreshItemModel(LegoS32 p_index)
{
	GolModelEntity* entity = GetItemEntity(p_index);
	GolModelBase* model = GetItemModel(p_index);
	LegoS32 choiceIndex = m_choiceIndices[WrapIndex(m_ringBaseIndex + p_index)];
	LegoS32 pieceType;
	LegoS32 colorRecordIndex;

	m_currentEntry->GetChoice(choiceIndex, &pieceType, &colorRecordIndex);

	LegoFloat maxDistance = g_maxFloat;
	entity->SetPrimaryModel(model, maxDistance);

	LegoPieceLibrary::PieceRecord* pieceRecord = m_pieceLibrary->FindPieceRecord(pieceType, 1);
	m_buildModel->CenterOnPiece(pieceRecord, 0);
	m_buildModel->BuildPieceModel(entity, pieceRecord, 0, 0, 0, 0, colorRecordIndex, 239);
	MenuModelCarousel::RefreshItemModel(p_index);
}

// FUNCTION: LEGORACERS 0x00485550
void CarPartCarousel::LayoutItem(undefined4, GolModelEntity* p_entity)
{
	LegoFloat vectorX = g_cosineTable[c_vectorXCosineIndex];
	LegoFloat vectorZ = g_cosineTable[c_vectorZCosineIndex];
	GolVec3 axis = {1.0f, 0.0f, 0.0f};
	GolVec3 vector = {vectorX, 0.0f, vectorZ};

	GolMath::RotateAboutAxis(&axis, &axis, &vector, m_rotationAngle);
	p_entity->SetUpDirection(vector, axis);
}

// FUNCTION: LEGORACERS 0x004855c0
void CarPartCarousel::SetSelection(undefined4 p_index)
{
	if (m_itemCount) {
		m_selectedIndex = p_index;
		m_ringBaseIndex = WrapIndex(p_index - m_focusedSlot);

		if (!m_scrolling) {
			if (m_itemCount >= m_slotCount - 1) {
				for (LegoS32 i = 0; i < m_slotCount; i++) {
					RefreshItemModel(i);
				}
			}
			else {
				for (LegoS32 i = 0; i < m_slotCount; i++) {
					GetItemEntity(i)->ResetModelState();
				}

				RefreshItemModel(m_focusedSlot);

				LegoS32 index = m_focusedSlot;
				LegoS32 previousVisibleIndex = index - 1;
				if (m_selectedIndex <= index) {
					index = m_selectedIndex;
				}
				index--;

				if (index >= 0) {
					LegoS32 count = index + 1;
					do {
						RefreshItemModel(previousVisibleIndex--);
					} while (--count);
				}

				LegoS32 baseIndex = static_cast<LegoS32>(m_focusedSlot);
				LegoS32 nextVisibleIndex = baseIndex + 1;
				LegoS32 count;
				if (m_selectedIndex >= baseIndex) {
					count = m_itemCount - m_selectedIndex;
				}
				else {
					count = m_slotCount - baseIndex - 1;
				}

				while (count--) {
					RefreshItemModel(nextVisibleIndex++);
				}
			}

			SnapToSelection();
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

	SetSelection(result);
}

// FUNCTION: LEGORACERS 0x00485720
LegoS32 CarPartCarousel::ScrollNext()
{
	if (!m_itemCount) {
		return 0;
	}

	if (!m_scrolling) {
		if (m_selectedIndex >= m_itemCount - 1 && m_itemCount < m_slotCount - 1) {
			m_soundGroupBinding->PlaySoundByIndex(m_style->m_soundIds[2]);
			return m_selectedIndex;
		}

		MenuModelCarousel::ScrollNext();
		SetSelection(WrapIndex(m_selectedIndex + 1));

		if (m_itemCount >= m_slotCount - 1 ||
			m_itemCount - m_selectedIndex > m_slotCount - static_cast<LegoS32>(m_focusedSlot) - 1) {
			RefreshItemModel(m_slotCount - 1);
		}

		m_soundGroupBinding->PlaySoundByIndex(m_style->m_soundIds[0]);
	}

	return m_selectedIndex;
}

// FUNCTION: LEGORACERS 0x004857b0
LegoS32 CarPartCarousel::ScrollPrevious()
{
	if (!m_itemCount) {
		return 0;
	}

	if (!m_scrolling) {
		if (!m_selectedIndex && m_itemCount < m_slotCount - 1) {
			m_soundGroupBinding->PlaySoundByIndex(m_style->m_soundIds[2]);
			return m_selectedIndex;
		}

		MenuModelCarousel::ScrollPrevious();
		SetSelection(WrapIndex(m_selectedIndex - 1));

		if (m_itemCount >= m_slotCount - 1 || m_selectedIndex > static_cast<LegoS32>(m_focusedSlot) - 1) {
			RefreshItemModel(0);
		}

		m_soundGroupBinding->PlaySoundByIndex(m_style->m_soundIds[1]);
	}

	return m_selectedIndex;
}

// FUNCTION: LEGORACERS 0x00485840
undefined4 CarPartCarousel::OnEvent(undefined4 p_elapsed)
{
	LegoFloat step = m_scrollStep;
	LegoFloat scaled = (LegoFloat) (LegoS32) p_elapsed;
	if ((m_rotationAngle += step * scaled) > g_twoPi) {
		m_rotationAngle -= g_twoPi;
	}

	return MenuModelCarousel::OnEvent(p_elapsed);
}
