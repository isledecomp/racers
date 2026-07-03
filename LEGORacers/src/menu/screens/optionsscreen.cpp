#include "menu/screens/optionsscreen.h"

#include "app/golapp.h"
#include "golstring.h"
#include "menu/menugamecontext.h"
#include "menu/menuscreencreateparams.h"
#include "render/goldrawstate.h"
#include "util/displaydriverguid.h"

#include <string.h>

DECOMP_SIZE_ASSERT(OptionsScreen, 0x6750)
DECOMP_SIZE_ASSERT(OptionsScreen::DriverNameBuffer, 0x64)

// FUNCTION: LEGORACERS 0x00475510
OptionsScreen::OptionsScreen()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00475630
OptionsScreen::~OptionsScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00475700
void OptionsScreen::Reset()
{
	m_driverCount = 0;
	::memset(m_driverNameBuffers, 0, sizeof(m_driverNameBuffers));
	OptionsScreenBase::Reset();
}

// FUNCTION: LEGORACERS 0x00475730
void OptionsScreen::CreateVideoWidgets()
{
	GolDrawState* drawState = m_context->m_context->m_golApp->GetDrawState();
	GolString string;
	DisplayDriverGuid selectedDriverGuid;
	DisplayDriverGuid driverGuid;
	LegoS32 selectedDriverIndex = 0;
	LegoS32 i;

	CreateTextButton(&m_videoButton, 0xee, 0x42, 0x12);
	CreateCarousel(&m_driverCarousel, 0xf6, 0x3b);
	CreateSelector(&m_driverSelector, &m_driverCarousel, 0xf5, 0x4c);

	GUID* currentDriverGuid = drawState->GetCurrentDriverGuid();
	if (!currentDriverGuid) {
		drawState->GetDriverGuid(0, &selectedDriverGuid.m_guid);
	}
	else {
		selectedDriverGuid.m_guid = *currentDriverGuid;
	}

	m_driverCount = drawState->GetDriverCount();

	for (i = 0; i < m_driverCount && i < 5; i++) {
		CreateTextLabel(&m_driverLabels[i], 0xf7, 0xf5, 0x12);

		undefined2* driverNameBuffer = m_driverNameBuffers[i].m_data;
		GolString::CopyStringToBuf16(drawState->GetDriverName(i), driverNameBuffer);
		string.CopyFromBufSelection(driverNameBuffer, ::strlen(drawState->GetDriverName(i)) + 1);
		string.ToUpperCase();
		m_driverLabels[i].SetString(&string, 0);
		m_driverCarousel.AddItem(&m_driverLabels[i]);

		drawState->GetDriverGuid(i, &driverGuid.m_guid);
		if (::memcmp(&driverGuid, &selectedDriverGuid, sizeof(GUID)) == 0) {
			selectedDriverIndex = i;
		}
	}

	m_driverCarousel.SetSelection(selectedDriverIndex);
	OnWidgetValueChanged(&m_driverSelector);

	for (i = 0; i < 2; i++) {
		CreateTextLabel(&m_videoLabels[i], static_cast<undefined2>(i + 0x102), 0x37, static_cast<undefined2>(i + 0x5b));
	}

	HideVideoWidgets();
}

// FUNCTION: LEGORACERS 0x00475970
LegoBool32 OptionsScreen::Initialize(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	return OptionsScreenBase::Initialize(p_context, p_createParams) != FALSE;
}

// FUNCTION: LEGORACERS 0x00475990
void OptionsScreen::OnIconUnfocused(MenuWidget* p_widget)
{
	if (p_widget == &m_videoButton) {
		CreateTextButton(&m_videoNoticePopup, 0x99, 0x46, 0x72);
		ShowPopupDialog(&m_videoNoticePopup, 0xbd);
	}
	else if (p_widget == &m_videoNoticePopup) {
		m_nextPage = 3;
		m_dialog->DismissTop();
	}

	OptionsScreenBase::OnIconUnfocused(p_widget);
	if (m_nextMenuId != 0xffff) {
		m_navPending = TRUE;
	}

	m_clickedWidget = p_widget;
}

// FUNCTION: LEGORACERS 0x00475a10
void OptionsScreen::ShowMainButtons()
{
	m_videoButton.SetFlags(2);
	OptionsScreenBase::ShowMainButtons();
}

// FUNCTION: LEGORACERS 0x00475a20
void OptionsScreen::HideMainButtons()
{
	m_videoButton.ClearFlags(2);
	OptionsScreenBase::HideMainButtons();
}

// FUNCTION: LEGORACERS 0x00475a30
void OptionsScreen::ShowVideoWidgets()
{
	m_driverSelector.SetFlags(2);

	for (LegoS32 i = 0; i < 2; i++) {
		m_videoLabels[i].SetFlags(2);
	}

	m_infoLabel.SetStringByIndex(0x12, TRUE);
	m_infoLabel.WrapText(20);
	m_backButton.SetTextByIndex(0x10);
	m_driverSelector.Select(4);
}

// FUNCTION: LEGORACERS 0x00475aa0
void OptionsScreen::HideVideoWidgets()
{
	m_driverSelector.ClearFlags(2);

	for (LegoS32 i = 0; i < 2; i++) {
		m_videoLabels[i].ClearFlags(2);
	}
}

// FUNCTION: LEGORACERS 0x00475ad0
void OptionsScreen::ApplyPageChange()
{
	if (m_page == 3) {
		HideVideoWidgets();
		ApplyVideoDriver();
	}

	if (m_nextPage == 3) {
		ShowVideoWidgets();
	}

	OptionsScreenBase::ApplyPageChange();
}

// FUNCTION: LEGORACERS 0x00475b10
void OptionsScreen::ApplyVideoDriver()
{
	GolDrawState* drawState = m_context->m_context->m_golApp->GetDrawState();
	LegoU32 driverIndex = m_driverCarousel.GetSelectedIndex();
	LegoU32 flags;
	const LegoChar* driverName = drawState->GetDriverDescription(driverIndex);
	DisplayDriverGuid driverGuid;

	drawState->GetDriverGuid(driverIndex, &driverGuid.m_guid);
	m_gameState->SetDisplayDriverGuid(driverGuid);

	LegoU32 deviceIndex = 0;
	while (deviceIndex < drawState->GetDeviceCount(driverIndex) &&
		   !drawState->IsDeviceHwAccelerated(driverIndex, deviceIndex)) {
		deviceIndex++;
	}

	flags = 0;
	if (deviceIndex < drawState->GetDeviceCount(driverIndex)) {
		const LegoChar* deviceName = drawState->GetDeviceName(driverIndex, deviceIndex);
		drawState->SelectDevice(driverName, deviceName);
		flags = GolDrawState::c_flagBit14;
	}

	LegoU32 appFlags = m_context->m_context->m_golApp->GetFlags();
	LegoU32 drawStateFlags = 0;
	if (appFlags & GolApp::c_flagFullscreen) {
		drawStateFlags = GolApp::c_flagFullscreen;
	}
	if (appFlags & GolApp::c_flagBit4) {
		drawStateFlags |= GolApp::c_flagBit4;
	}
	if (appFlags & GolApp::c_flagBit8) {
		drawStateFlags |= GolApp::c_flagBit8;
	}

	drawState->ReleaseDisplay();
	undefined4 bpp = drawState->m_bpp;
	LegoS32 height = drawState->m_height;
	LegoS32 width = drawState->m_width;
	drawState->CreateDisplay(
		width,
		height,
		bpp,
		m_context->m_context->m_golApp->BuildDrawStateFlags(drawStateFlags) | flags
	);
}
