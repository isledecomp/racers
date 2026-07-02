#include "menu/screens/carmodelscreenbase.h"

#include "audio/soundgroupbinding.h"
#include "decomp.h"
#include "golstream.h"
#include "menu/menudialog.h"
#include "menu/menugamecontext.h"

#include <string.h>

DECOMP_SIZE_ASSERT(CarModelScreenBase, 0x2b20)

// GLOBAL: LEGORACERS 0x004b2cf4
static const LegoFloat g_unk0x004b2cf4 = 6.2831855f;

// GLOBAL: LEGORACERS 0x004c7664
LegoFloat g_unk0x004c7664 = g_unk0x004b2cf4 * 0.125f;

// FUNCTION: LEGORACERS 0x00476d50
CarModelScreenBase::CarModelScreenBase()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00476ef0
CarModelScreenBase::~CarModelScreenBase()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00476ff0
void CarModelScreenBase::Reset()
{
	m_mode = 1;
	m_nextMode = 1;

	m_carouselAction = 0;
	m_unk0x2ad8 = 0;
	m_unk0x28d0 = 0;
	m_unk0x28cc = 0;
	m_unk0x28c8 = 0;
	m_unk0x2b1c = 0;
	m_partCategoryUnlockFlags = 0;

	memset(m_partCategoryAvailable, 0, sizeof(m_partCategoryAvailable));

	CarBuildScreenBase::Reset();
}

// FUNCTION: LEGORACERS 0x00477050
void CarModelScreenBase::FUN_00477050()
{
	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA\\GARAGE");
	}

	CreateFramedSceneView(&m_sceneView, 0, 3);

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}

	CarPartPlacement::CreateParams params;
	::memset(&params, 0, sizeof(params));
	params.m_golExport = m_golExport;
	params.m_renderer = m_renderer;
	params.m_sceneView = &m_sceneView;
	params.m_soundGroupBinding = m_soundGroupBinding;
	params.m_context = m_context;
	params.m_screen = this;
	params.m_piecePosition.m_x = 0.0f;
	params.m_piecePosition.m_y = 0.0f;
	params.m_piecePosition.m_z = 1.0f;
	params.m_unk0x28 = 0.001f;
	params.m_unk0x2c = m_context->m_context->m_useBinaryFiles;
	m_partPlacement.Create(&params);

	m_sceneView.AddElement(&m_partPlacement);
	m_partPlacement.PitchViewAnalog(0.0f);
}

// FUNCTION: LEGORACERS 0x00477130
void CarModelScreenBase::FUN_00477130()
{
	CreateCarousel(&m_categoryCarousel, 0x3e, 0xaf);
	CreateSelector(&m_categorySelector, &m_categoryCarousel, 0xaa, 0x4d);

	for (LegoU32 i = 0; i < 12; i++) {
		CreateImage(&m_categoryIcons[i], 0x9d, static_cast<undefined2>(i + 0x9e));
	}
}

// FUNCTION: LEGORACERS 0x00477190
void CarModelScreenBase::VTable0x4c()
{
	CreateImage(&m_unk0x3b4, 0x49, 0x49);
	FUN_00477050();
	FUN_00477130();
	FUN_0047fcf0(&m_partCarousel, 0xae, 0x3b);
	CreateSelector(&m_pieceSelector, &m_partCarousel, 0xac, 0xcc);

	m_partCarousel.SelectPartByType(m_context->m_partSet.GetEntries()[m_partCategoryAvailable[0]].GetPieceType());
}

// FUNCTION: LEGORACERS 0x00477210
void CarModelScreenBase::VTable0x80()
{
	ColorRGBA lightColor;
	ColorRGBA materialColor;

	materialColor.m_blu = 0x78;
	materialColor.m_grn = 0x78;
	materialColor.m_red = 0x78;
	materialColor.m_alp = 0x78;
	lightColor.m_blu = 0xff;
	lightColor.m_grn = 0xff;
	lightColor.m_red = 0xff;
	lightColor.m_alp = 0xff;

	FUN_0047fec0(&materialColor, &lightColor);
}

// FUNCTION: LEGORACERS 0x00477250
LegoBool32 CarModelScreenBase::VTable0x8c(MenuGameContext* p_unk0x04, MenuScreenCreateParams* p_unk0x08)
{
	if (!MenuGameScreen::VTable0x8c(p_unk0x04, p_unk0x08)) {
		return FALSE;
	}

	FUN_00477290();
	OnWidgetValueChanged(&m_pieceSelector);

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00477290
void CarModelScreenBase::FUN_00477290()
{
	LegoS32 mask = 1;
	SaveSystem* saveSystem = &m_context->m_saveSystem;
	m_partCategoryUnlockFlags = saveSystem->GetGameState().GetPartUnlockFlags();

	LegoS32 i;
	for (i = 0; i < c_alwaysAvailablePartCategoryCount; i++) {
		m_partCategoryAvailable[i] = TRUE;
	}

	for (i = 0; i < c_saveUnlockedPartCategoryCount; i++) {
		if (m_partCategoryUnlockFlags & mask) {
			m_partCategoryAvailable[i + c_alwaysAvailablePartCategoryCount] = TRUE;
		}
		mask <<= 1;
	}

	for (i = 0; i < m_context->m_carBuildModel.GetPlacedPieceCount(); i++) {
		LegoS32 index = m_context->m_partSet.FindEntryIndex(m_context->m_carBuildModel.FUN_0049bd50(i));
		m_partCategoryAvailable[index] = TRUE;
	}

	for (i = 0; i < c_partCategoryCount; i++) {
		if (m_partCategoryAvailable[i]) {
			m_categoryCarousel.AddItem(&m_categoryIcons[i]);
		}
	}

	m_categoryCarousel.SetSelection(0);
}

// FUNCTION: LEGORACERS 0x00477380
void CarModelScreenBase::VTable0x84()
{
	FUN_004773a0();
	m_context->m_menuStack.Pop();
}

// FUNCTION: LEGORACERS 0x004773a0
void CarModelScreenBase::FUN_004773a0()
{
	memset(m_carBuildSaveBuffer, 0, c_carBuildSaveBufferSize);
	m_context->m_carBuildModel.FUN_0049c820(m_carBuildSaveBuffer);
	m_context->m_saveSystem.GetActiveRecord().SetCarData(m_carBuildSaveBuffer);
}

// FUNCTION: LEGORACERS 0x004773e0
LegoBool32 CarModelScreenBase::MovePieceByDrag(
	LegoS32 p_deltaX,
	LegoS32 p_deltaY,
	LegoU16 p_sound,
	LegoBool32 p_unk0x10
)
{
	LegoU32 fallbackSound = p_sound ? 8 : 0;

	if (m_mode == 6) {
		return FALSE;
	}

	LegoS32 deltaX = p_deltaX;
	if (deltaX && p_deltaY && !p_unk0x10) {
		CarPartPlacement* placement = &m_partPlacement;
		if (placement->MovePieceX(deltaX) && placement->MovePieceY(p_deltaY)) {
			m_soundGroupBinding->PlaySoundByIndex(p_sound & 0xffff);
			return TRUE;
		}

		placement->MovePieceX(-deltaX);
		m_soundGroupBinding->PlaySoundByIndex(fallbackSound & 0xffff);
		return FALSE;
	}

	CarPartPlacement* placement = &m_partPlacement;
	LegoBool32 result = placement->MovePieceX(deltaX);
	result |= placement->MovePieceY(p_deltaY);
	if (result) {
		m_soundGroupBinding->PlaySoundByIndex(p_sound & 0xffff);
	}
	else {
		m_soundGroupBinding->PlaySoundByIndex(fallbackSound & 0xffff);
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00477600
void CarModelScreenBase::ShowPlacementError()
{
	FUN_0047fdc0(&m_errorPopup, 0x99, 0x42, 0x72);
	FUN_0046c730(&m_errorPopup, 0xba);
}

// FUNCTION: LEGORACERS 0x00477630
void CarModelScreenBase::OnIconUnfocused(MenuWidget* p_unk0x04)
{
	if (p_unk0x04 == &m_errorPopup) {
		m_unk0x284->FUN_00468cf0();
	}
}

// FUNCTION: LEGORACERS 0x00477650
void CarModelScreenBase::OnWidgetValueChanged(MenuWidget* p_source)
{
	if (m_mode == 6) {
		return;
	}

	if (p_source == &m_pieceSelector) {
		m_partPlacement.SelectPieceChoice(m_partCarousel.GetChoiceIndex(m_partCarousel.GetSelectedIndex()));
		return;
	}

	if (p_source == &m_categorySelector) {
		MenuWidget* child = m_categoryCarousel.GetSelectedChild();
		LegoU32 i;
		for (i = 0; i < c_partCategoryCount; i++) {
			if (child == &m_categoryIcons[i]) {
				CarPartCarousel* partCarousel = &m_partCarousel;
				partCarousel->SelectPartByType(m_context->m_partSet.GetEntries()[i].GetPieceType());
				m_partPlacement.SelectPieceChoice(partCarousel->GetChoiceIndex(partCarousel->GetSelectedIndex()));
				return;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00477700
void CarModelScreenBase::OnCarouselSettled(MenuWidget* p_source)
{
	if (p_source == &m_sceneView) {
		switch (m_carouselAction) {
		case 4: {
			CarPartCarousel* partCarousel = &m_partCarousel;
			partCarousel->RefreshChoiceIndices();
			partCarousel->SetSelection(partCarousel->WrapIndex(m_partCarousel.GetSelectedIndex()));
			m_partPlacement.SelectPieceChoice(partCarousel->GetChoiceIndex(partCarousel->GetSelectedIndex()));
		}
		case 5:
			m_nextMode = 1;
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x00477770
void CarModelScreenBase::ApplyModeChange()
{
	switch (m_mode) {
	case 1:
		ExitBrowseMode();
		break;
	case 2:
		ExitCarViewMode();
		break;
	case 3:
		ExitPieceViewMode();
		break;
	case 6:
		ExitBusyMode();
		break;
	}

	switch (m_nextMode) {
	case 1:
		EnterBrowseMode();
		if (m_unk0xd8.GetFlags() & 8) {
			m_unk0xd8.ClearFocus();
		}
		break;
	case 2:
		EnterCarViewMode();
		break;
	case 3:
		EnterPieceViewMode();
		break;
	case 5:
		m_nextMode = 6;
		m_carouselAction = 5;
		m_partPlacement.BeginResetAnimation();
		break;
	case 6:
		EnterBusyMode();
		break;
	}

	m_unk0x35c = NULL;
	m_mode = m_nextMode;
}

// FUNCTION: LEGORACERS 0x00477880
LegoBool32 CarModelScreenBase::VTable0x78(undefined4 p_unk0x04)
{
	if (m_mode != m_nextMode) {
		if (m_unk0x35c == NULL || !(m_unk0x35c->GetUnk0x54() & 1)) {
			ApplyModeChange();
		}
	}

	return CarBuildScreenBase::VTable0x78(p_unk0x04);
}
