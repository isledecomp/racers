#include "menu/screens/racerpickscreenbase.h"

#include <string.h>

DECOMP_SIZE_ASSERT(RacerPickScreenBase, 0x3ff4)

// FUNCTION: LEGORACERS 0x00488ce0
RacerPickScreenBase::RacerPickScreenBase()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00488df0
RacerPickScreenBase::~RacerPickScreenBase()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00488eb0
void RacerPickScreenBase::Reset()
{
	::memset(m_nameBuffers, 0, sizeof(m_nameBuffers));
	RacerModelScreenBase::Reset();
}

// FUNCTION: LEGORACERS 0x00488ed0
void RacerPickScreenBase::CreateWidgets()
{
	RacerModelScreenBase::CreateWidgets();

	LegoS32 i;

	for (i = 0; i < m_modelSlotCount; i++) {
		CreateCarousel(&m_nameCarousels[i], 0x3d, 0x3b);
		CreateSelector(&m_nameSelectors[i], &m_nameCarousels[i], i + 0x70, 0x4c);
	}

	for (i = 0; i < m_modelSlotCount; i++) {
		LegoS32 j;

		for (j = 0; j < 3; j++) {
			CreateTextLabel(&m_nameLabels[i * 3 + j], 0x96, 0x37, i + 2);
		}
	}
}

// FUNCTION: LEGORACERS 0x00488f80
LegoBool32 RacerPickScreenBase::Initialize(
	MenuGameContext* p_context,
	MenuScreenCreateParams* p_createParams,
	undefined4* p_params
)
{
	if (!RacerModelScreenBase::Initialize(p_context, p_createParams, p_params)) {
		return FALSE;
	}

	for (LegoS32 i = 0; i < m_modelSlotCount; i++) {
		for (LegoS32 j = 0; j < 3; j++) {
			m_nameStrings[i * 3 + j].CopyFromBufSelection(
				m_nameBuffers[i * 3 + j],
				sizeOfArray(m_nameBuffers[i * 3 + j])
			);
		}

		if (m_recordCounts[i]) {
			RebuildNameCarousel(i);
			OnWidgetValueChanged(&m_nameSelectors[i]);
		}
	}

	return m_initialized;
}

// FUNCTION: LEGORACERS 0x00489050
void RacerPickScreenBase::RefreshNameLabels(LegoS32 p_index)
{
	SaveRecordCursor* modelState = &m_recordCursors[p_index];
	modelState->SelectPrevious();
	modelState->SelectPrevious();

	for (LegoS32 i = 0; i < 3; i++) {
		LegoS32 widgetIndex = p_index * 3 + i;
		modelState->SelectNext()->GetName(&m_nameStrings[widgetIndex]);
		m_nameLabels[widgetIndex].SetString(&m_nameStrings[widgetIndex], 0);
	}

	modelState->SelectPrevious();
}

// FUNCTION: LEGORACERS 0x004890c0
void RacerPickScreenBase::RebuildNameCarousel(LegoS32 p_index)
{
	MenuCarouselNavigator* carousel = &m_nameCarousels[p_index];

	carousel->RemoveAllItems();

	if (m_recordCounts[p_index] && m_initialized) {
		RefreshNameLabels(p_index);

		for (LegoS32 i = 0; i < 3; i++) {
			carousel->AddItem(&m_nameLabels[p_index * 3 + i]);
		}

		carousel->SetSelection(1);
	}
}

// FUNCTION: LEGORACERS 0x00489130
void RacerPickScreenBase::OnWidgetValueChanged(MenuWidget* p_source)
{
	for (LegoS32 i = 0; i < m_modelSlotCount; i++) {
		if (&m_nameSelectors[i] == p_source) {
			undefined4 state = m_nameSelectors[i].GetStepDirection();

			if (state != -1) {
				if (state != 1) {
					SwapSlotModel(i);
				}
				else {
					SelectNextRecord(i);
				}
			}
			else {
				SelectPreviousRecord(i);
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004891a0
void RacerPickScreenBase::OnCarouselSettled(MenuWidget* p_source)
{
	for (LegoS32 i = 0; i < m_modelSlotCount; i++) {
		if (&m_nameCarousels[i] == p_source) {
			RebuildNameCarousel(0);
		}
	}
}

// FUNCTION: LEGORACERS 0x004891f0
void RacerPickScreenBase::ActivateNameSelectors(LegoS32 p_index)
{
	if (p_index > 0) {
		m_nameSelectors[p_index].SetFlags(2);
		return;
	}

	for (LegoS32 i = 0; i < m_modelSlotCount; i++) {
		m_nameSelectors[i].SetFlags(2);
	}
}

// FUNCTION: LEGORACERS 0x00489250
void RacerPickScreenBase::EnableNameSelectors(LegoS32 p_index)
{
	if (p_index > 0) {
		m_nameSelectors[p_index].Enable(5);
		if (m_recordCounts[p_index]) {
			m_sceneViews[p_index].SetDrawWorld(TRUE);
		}
		else {
			m_sceneViews[p_index].SetDrawWorld(FALSE);
		}
		return;
	}
	else {
		for (LegoS32 i = 0; i < m_modelSlotCount; i++) {
			m_nameSelectors[i].Enable(5);
			m_sceneViews[i].SetDrawWorld(m_recordCounts[i] != 0);
		}
	}
}

// FUNCTION: LEGORACERS 0x00489320
void RacerPickScreenBase::DisableNameSelectors(LegoS32 p_index)
{
	if (p_index > 0) {
		m_nameSelectors[p_index].Disable(5);
		if (m_recordCounts[p_index]) {
			m_sceneViews[p_index].SetDrawWorld(TRUE);
		}
		else {
			m_sceneViews[p_index].SetDrawWorld(FALSE);
		}
		return;
	}
	else {
		for (LegoS32 i = 0; i < m_modelSlotCount; i++) {
			m_nameSelectors[i].Disable(5);
			m_sceneViews[i].SetDrawWorld(m_recordCounts[i] != 0);
		}
	}
}
