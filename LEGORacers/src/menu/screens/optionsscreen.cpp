#include "menu/screens/optionsscreen.h"

#include "app/golapp.h"
#include "golstring.h"
#include "menu/menugamecontext.h"
#include "menu/menuscreencreateparams.h"
#include "render/goldrawstate.h"
#include "util/displaydriverguid.h"

#include <string.h>

DECOMP_SIZE_ASSERT(OptionsScreen, 0x6750)

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
	m_unk0x51a8 = 0;
	::memset(m_unk0x646c, 0, sizeof(m_unk0x646c));
	OptionsScreenBase::Reset();
}

// FUNCTION: LEGORACERS 0x00475730
void OptionsScreen::VTable0x98()
{
	GolDrawState* drawState = m_context->m_context->m_golApp->GetDrawState();
	GolString string;
	DisplayDriverGuid selectedDriverGuid;
	DisplayDriverGuid driverGuid;
	LegoS32 selectedDriverIndex = 0;
	LegoS32 i;

	FUN_0047fdc0(&m_unk0x51ac, 0xee, 0x42, 0x12);
	CreateCarousel(&m_unk0x578c, 0xf6, 0x3b);
	CreateSelector(&m_unk0x5820, &m_unk0x578c, 0xf5, 0x4c);

	GUID* currentDriverGuid = drawState->GetCurrentDriverGuid();
	if (!currentDriverGuid) {
		drawState->GetDriverGuid(0, &selectedDriverGuid.m_guid);
	}
	else {
		selectedDriverGuid.m_guid = *currentDriverGuid;
	}

	m_unk0x51a8 = drawState->GetDriverCount();

	for (i = 0; i < m_unk0x51a8 && i < 5; i++) {
		CreateTextLabel(&m_unk0x6214[i], 0xf7, 0xf5, 0x12);

		undefined2* driverNameBuffer = reinterpret_cast<undefined2*>(&m_unk0x646c[i * 0x64]);
		GolString::CopyStringToBuf16(drawState->GetDriverName(i), driverNameBuffer);
		string.CopyFromBufSelection(driverNameBuffer, ::strlen(drawState->GetDriverName(i)) + 1);
		string.ToUpperCase();
		m_unk0x6214[i].VTable0x40(&string, 0);
		m_unk0x578c.FUN_0046d9c0(&m_unk0x6214[i]);

		drawState->GetDriverGuid(i, &driverGuid.m_guid);
		if (::memcmp(&driverGuid, &selectedDriverGuid, sizeof(GUID)) == 0) {
			selectedDriverIndex = i;
		}
	}

	m_unk0x578c.VTable0x50(selectedDriverIndex);
	VTable0x44(&m_unk0x5820);

	for (i = 0; i < 2; i++) {
		CreateTextLabel(&m_unk0x6660[i], static_cast<undefined2>(i + 0x102), 0x37, static_cast<undefined2>(i + 0x5b));
	}

	FUN_00475aa0();
}

// FUNCTION: LEGORACERS 0x00475970
LegoBool32 OptionsScreen::VTable0x8c(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	return OptionsScreenBase::VTable0x8c(p_context, p_createParams) != FALSE;
}

// FUNCTION: LEGORACERS 0x00475990
void OptionsScreen::VTable0x38(MenuWidget* p_widget)
{
	if (p_widget == &m_unk0x51ac) {
		FUN_0047fdc0(&m_unk0x549c, 0x99, 0x46, 0x72);
		FUN_0046c730(&m_unk0x549c, 0xbd);
	}
	else if (p_widget == &m_unk0x549c) {
		m_unk0x369 = 3;
		m_unk0x284->FUN_00468cf0();
	}

	OptionsScreenBase::VTable0x38(p_widget);
	if (m_unk0x360 != 0xffff) {
		m_unk0x364 = TRUE;
	}

	m_unk0x35c = p_widget;
}

// FUNCTION: LEGORACERS 0x00475a10
void OptionsScreen::VTable0x9c()
{
	m_unk0x51ac.SetFlags(2);
	OptionsScreenBase::VTable0x9c();
}

// FUNCTION: LEGORACERS 0x00475a20
void OptionsScreen::VTable0xa0()
{
	m_unk0x51ac.ClearFlags(2);
	OptionsScreenBase::VTable0xa0();
}

// FUNCTION: LEGORACERS 0x00475a30
void OptionsScreen::FUN_00475a30()
{
	m_unk0x5820.SetFlags(2);

	for (LegoS32 i = 0; i < 2; i++) {
		m_unk0x6660[i].SetFlags(2);
	}

	m_unk0x3d0.VTable0x44(0x12, TRUE);
	m_unk0x3d0.FUN_0046f6b0(20);
	m_unk0x18d8.FUN_00482790(0x10);
	m_unk0x5820.VTable0x4c(4);
}

// FUNCTION: LEGORACERS 0x00475aa0
void OptionsScreen::FUN_00475aa0()
{
	m_unk0x5820.ClearFlags(2);

	for (LegoS32 i = 0; i < 2; i++) {
		m_unk0x6660[i].ClearFlags(2);
	}
}

// FUNCTION: LEGORACERS 0x00475ad0
void OptionsScreen::VTable0xa4()
{
	if (m_unk0x368 == 3) {
		FUN_00475aa0();
		FUN_00475b10();
	}

	if (m_unk0x369 == 3) {
		FUN_00475a30();
	}

	OptionsScreenBase::VTable0xa4();
}

// FUNCTION: LEGORACERS 0x00475b10
void OptionsScreen::FUN_00475b10()
{
	GolDrawState* drawState = m_context->m_context->m_golApp->GetDrawState();
	LegoU32 driverIndex = m_unk0x578c.GetUnk0x6c();
	LegoU32 flags;
	const LegoChar* driverName = drawState->GetDriverDescription(driverIndex);
	DisplayDriverGuid driverGuid;

	drawState->GetDriverGuid(driverIndex, &driverGuid.m_guid);
	m_unk0x370->SetDisplayDriverGuid(driverGuid);

	LegoU32 deviceIndex = 0;
	while (deviceIndex < drawState->GetDeviceCount(driverIndex) &&
		   !drawState->IsDeviceHwAccelerated(driverIndex, deviceIndex)) {
		deviceIndex++;
	}

	flags = 0;
	if (deviceIndex < drawState->GetDeviceCount(driverIndex)) {
		const LegoChar* deviceName = drawState->GetDeviceName(driverIndex, deviceIndex);
		drawState->VTable0x0c(driverName, deviceName);
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

	drawState->VTable0x50();
	undefined4 bpp = drawState->m_bpp;
	LegoS32 height = drawState->m_height;
	LegoS32 width = drawState->m_width;
	drawState
		->VTable0x54(width, height, bpp, m_context->m_context->m_golApp->BuildDrawStateFlags(drawStateFlags) | flags);
}
