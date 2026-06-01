#include "menu/screens/carbuildscreen.h"

#include "audio/soundgroupbinding.h"

DECOMP_SIZE_ASSERT(CarBuildScreen, 0x3c34)

// STUB: LEGORACERS 0x004736b0
CarBuildScreen::CarBuildScreen()
{
	STUB(0x004736b0);
}

// STUB: LEGORACERS 0x004737b0
CarBuildScreen::~CarBuildScreen()
{
	STUB(0x004737b0);
}

// FUNCTION: LEGORACERS 0x004738a0
void CarBuildScreen::Reset()
{
	m_unk0x3c18 = 0;
	m_unk0x3c1c = 0;
	ImaginaryShape0x2b20::Reset();
}

// FUNCTION: LEGORACERS 0x004738c0
void CarBuildScreen::VTable0x4c()
{
	ImaginaryShape0x2b20::VTable0x4c();
	FUN_0046c1b0(&m_unk0x2b20, 0xb5, 0xb5);
	FUN_0046c110(&m_unk0x318c, 0xb2, 0xb0);
	FUN_0046c110(&m_unk0x2f70, 0xb1, 0xb0);
	FUN_0046c110(&m_unk0x33a8, 0xb3, 0xb0);
	FUN_0046c1b0(&m_unk0x2d48, 0xb4, 0xb4);

	ObscureGlyph0x21c* glyph0 = &m_unk0x35c4;
	FUN_0046c110(glyph0, 0xb8, 0xb0);

	ObscureGlyph0x21c* glyph1 = &m_unk0x37e0;
	FUN_0046c110(glyph1, 0xb7, 0xb0);

	glyph0->ClearFlags(ObscureIcon0x1a8::c_flagBit1);
	glyph1->ClearFlags(ObscureIcon0x1a8::c_flagBit1);
	FUN_0046c110(&m_unk0x39fc, 0x3f, 0xb0);
}

// STUB: LEGORACERS 0x004739a0
LegoBool32 CarBuildScreen::VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*)
{
	STUB(0x004739a0);
	return FALSE;
}

// STUB: LEGORACERS 0x00473b80
undefined4 CarBuildScreen::FUN_00473b80(undefined4, undefined4)
{
	STUB(0x00473b80);
	return 0;
}

// STUB: LEGORACERS 0x00473ee0
LegoBool32 CarBuildScreen::FUN_00473ee0(ObscureVantage0x58*, InputEventQueue::Event*, undefined4, undefined4)
{
	STUB(0x00473ee0);
	return FALSE;
}

// STUB: LEGORACERS 0x00474330
LegoBool32 CarBuildScreen::FUN_00474330(ObscureVantage0x58*, InputEventQueue::Event*, undefined4, undefined4)
{
	STUB(0x00474330);
	return FALSE;
}

// STUB: LEGORACERS 0x00474470
LegoBool32 CarBuildScreen::FUN_00474470(ObscureVantage0x58*, InputEventQueue::Event*, undefined4, undefined4)
{
	STUB(0x00474470);
	return FALSE;
}

// FUNCTION: LEGORACERS 0x004744c0
undefined4 CarBuildScreen::VTable0x18(
	ObscureVantage0x58* p_source,
	InputEventQueue::Event* p_event,
	undefined4 p_unk0x0c,
	undefined4 p_unk0x10
)
{
	if (m_unk0x2ae0 != 6) {
		if (!m_unk0x364) {
			ObsidianMantle0x3b4::VTable0x18(p_source, p_event, p_unk0x0c, p_unk0x10);
			if (p_source != GetUnk0xd8() || !FUN_00473ee0(p_source, p_event, p_unk0x0c, p_unk0x10)) {
				switch (m_unk0x2ae0) {
				case 1:
					return FUN_00474470(p_source, p_event, p_unk0x0c, p_unk0x10);
				case 2:
					return 0;
				case 3:
					return 0;
				default:
					return 0;
				}
			}
		}
	}

	return 1;
}

// FUNCTION: LEGORACERS 0x00474550
undefined4 CarBuildScreen::VTable0x1c(
	ObscureVantage0x58* p_source,
	InputEventQueue::Event* p_event,
	undefined4 p_unk0x0c,
	undefined4 p_unk0x10
)
{
	if (m_unk0x2ae0 == 6) {
		return 1;
	}

	ObsidianMantle0x3b4::VTable0x1c(p_source, p_event, p_unk0x0c, p_unk0x10);
	if (p_source == GetUnk0xd8() && FUN_00474330(p_source, p_event, p_unk0x0c, p_unk0x10)) {
		return 1;
	}

	if ((p_event->m_keyCode & InputDevice::c_sourceMask) == InputDevice::c_sourceMouse) {
		m_unk0x2ae4 = 1;
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x004745e0
void CarBuildScreen::VTable0x20(ObscureVantage0x58* p_source)
{
	if (p_source == GetUnk0xd8()) {
		switch (m_unk0x2ae4) {
		case 2:
			m_soundGroupBinding->FUN_0046e970(5);
			break;
		case 3:
			m_soundGroupBinding->FUN_0046e970(17);
			break;
		default:
			return;
		}

		m_cursorHelper->SetCursorEnabled(FALSE);
	}

	if (p_source == &m_unk0x2b20) {
		m_cursorHelper->SetCursorEnabled(FALSE);
	}
}

// FUNCTION: LEGORACERS 0x00474640
void CarBuildScreen::VTable0x24(ObscureVantage0x58* p_source)
{
	if (p_source == GetUnk0xd8()) {
		switch (m_unk0x2ae0) {
		case 2:
			m_unk0x2308.FUN_00478120();
			m_unk0x2308.FUN_004783d0();
			m_soundGroupBinding->FUN_0046e970(5);
			break;
		case 3:
			m_soundGroupBinding->FUN_0046e970(17);
			break;
		default:
			return;
		}

		m_cursorHelper->SetCursorEnabled(TRUE);
	}

	if (p_source == &m_unk0x2b20) {
		m_cursorHelper->SetCursorEnabled(TRUE);
	}
}

// FUNCTION: LEGORACERS 0x004746c0
undefined4 CarBuildScreen::VTable0x28(ObscureVantage0x58* p_source, void*, undefined4 p_unk0x0c, undefined4 p_unk0x10)
{
	if (p_source == GetUnk0xd8()) {
		switch (m_unk0x2ae0) {
		case 2:
			FUN_004774e0(p_unk0x0c, p_unk0x10);
			break;
		case 3:
			FUN_00473b80(p_unk0x0c, p_unk0x10);
			return 1;
		}
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x00474710
void CarBuildScreen::VTable0x34(ObscureIcon0x1a8* p_icon)
{
	m_unk0x35c = NULL;
	if (p_icon == &m_unk0x2b20) {
		m_unk0x2ae4 = 3;
	}
	else if (p_icon == &m_unk0x2d48) {
		m_unk0x2ae4 = 2;
	}
}

// STUB: LEGORACERS 0x00474750
void CarBuildScreen::VTable0x38(ObscureVantage0x58*)
{
	STUB(0x00474750);
}

// STUB: LEGORACERS 0x00474820
void CarBuildScreen::VTable0x44(ObscureVantage0x58*)
{
	STUB(0x00474820);
}

// STUB: LEGORACERS 0x00474940
void CarBuildScreen::FUN_00474940()
{
	STUB(0x00474940);
}

// FUNCTION: LEGORACERS 0x00474b10
LegoBool32 CarBuildScreen::VTable0x78(undefined4 p_elapsed)
{
	FUN_00474940();

	if (p_elapsed >= m_unk0x3c18) {
		m_unk0x3c18 = 0;
	}
	else {
		m_unk0x3c18 -= p_elapsed;
	}

	if (p_elapsed >= m_unk0x3c1c) {
		m_unk0x3c1c = 0;
	}
	else {
		m_unk0x3c1c -= p_elapsed;
	}

	return ImaginaryShape0x2b20::VTable0x78(p_elapsed);
}

// STUB: LEGORACERS 0x004774e0
void CarBuildScreen::FUN_004774e0(undefined4, undefined4)
{
	STUB(0x004774e0);
}
