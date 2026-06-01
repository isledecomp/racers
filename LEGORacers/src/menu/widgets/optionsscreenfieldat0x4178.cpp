#include "menu/widgets/optionsscreenfieldat0x4178.h"

#include "audio/soundgroupbinding.h"

DECOMP_SIZE_ASSERT(OptionsScreenFieldAt0x4178Base0x6dc, 0x6dc)
DECOMP_SIZE_ASSERT(OptionsScreenFieldAt0x4178, 0x6ec)

// FUNCTION: LEGORACERS 0x004113b0 FOLDED
undefined4 OptionsScreenFieldAt0x4178Base0x6dc::VTable0x3c(undefined4)
{
	return NULL;
}

// FUNCTION: LEGORACERS 0x0046de60
OptionsScreenFieldAt0x4178Base0x6dc::OptionsScreenFieldAt0x4178Base0x6dc()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046def0
OptionsScreenFieldAt0x4178Base0x6dc::~OptionsScreenFieldAt0x4178Base0x6dc()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x0046df60
void OptionsScreenFieldAt0x4178Base0x6dc::Reset()
{
	m_unk0x6c0 = 0;
	m_unk0x6c8 = 0;
	m_unk0x6c4 = 0;
	m_unk0x6cc = 0.0f;
	m_unk0x5e8 = NULL;
	m_unk0x648.VTable0x08();
	m_unk0x5ec.VTable0x08();
	ObscureIcon0x1a8::Reset();
}

// FUNCTION: LEGORACERS 0x0046e090
void OptionsScreenFieldAt0x4178Base0x6dc::VTable0x14(VisualState0x4* p_visualState)
{
	m_unk0x648.VTable0x14(p_visualState);
	m_unk0x5ec.VTable0x14(p_visualState);
	ObscureVantage0x58::VTable0x14(p_visualState);
}

// FUNCTION: LEGORACERS 0x0046e0d0
void OptionsScreenFieldAt0x4178Base0x6dc::VTable0x78()
{
	if (m_unk0x6c0) {
		VTable0x90(m_unk0x6c0 - 1);
		if (m_eventHandler) {
			m_eventHandler->VTable0x44(this);
		}

		m_soundGroupBinding->FUN_0046e970(GetUnk0x6e0());
		return;
	}

	m_soundGroupBinding->FUN_0046e970(GetUnk0x6e2());
}

// FUNCTION: LEGORACERS 0x0046e130
void OptionsScreenFieldAt0x4178Base0x6dc::VTable0x7c()
{
	if (m_unk0x6c0 != m_unk0x6bc - 1) {
		VTable0x90(m_unk0x6c0 + 1);
		if (m_eventHandler) {
			m_eventHandler->VTable0x44(this);
		}

		m_soundGroupBinding->FUN_0046e970(GetUnk0x6e0());
		return;
	}

	m_soundGroupBinding->FUN_0046e970(GetUnk0x6e2());
}

// FUNCTION: LEGORACERS 0x0046e190
undefined4 OptionsScreenFieldAt0x4178Base0x6dc::VTable0x74(undefined4 p_event)
{
	if ((p_event & InputDevice::c_sourceMask) == InputDevice::c_sourceMouse) {
		return p_event;
	}

	switch (p_event) {
	case InputDevice::c_sourceJoystickButton | 0x7:
	case InputDevice::c_sourceJoystickButton | 0xa:
	case InputDevice::c_sourceKeyboard | 0xcd:
	case InputDevice::c_sourceJoystickAxisButton | 0x0:
		return InputDevice::c_sourceJoystickButton | 0xa;
	case InputDevice::c_sourceJoystickButton | 0x9:
	case InputDevice::c_sourceJoystickButton | 0xb:
	case InputDevice::c_sourceKeyboard | 0xcb:
	case InputDevice::c_sourceJoystickAxisButton | 0x1:
		return InputDevice::c_sourceJoystickButton | 0xb;
	default:
		return InputDevice::c_sourceJoystickButton | 0x1;
	}
}

// STUB: LEGORACERS 0x0046e210
ObscureVantage0x58* OptionsScreenFieldAt0x4178Base0x6dc::VTable0x30(InputEventQueue::Event*, undefined4, undefined4)
{
	STUB(0x0046e210);
	return NULL;
}

// STUB: LEGORACERS 0x0046e340
ObscureVantage0x58* OptionsScreenFieldAt0x4178Base0x6dc::VTable0x34(InputEventQueue::Event*, undefined4, undefined4)
{
	STUB(0x0046e340);
	return NULL;
}

// FUNCTION: LEGORACERS 0x0046e3f0
OptionsScreenFieldAt0x4178::OptionsScreenFieldAt0x4178()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046e460
OptionsScreenFieldAt0x4178::~OptionsScreenFieldAt0x4178()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x0046e530
void OptionsScreenFieldAt0x4178::VTable0x80()
{
	Rect rect;
	rect.m_top = 0;
	rect.m_left = 0;
	rect.m_bottom = m_unk0x34.m_bottom - m_unk0x34.m_top;
	rect.m_right = m_unk0x1ac.GetRect()->m_right - m_unk0x1ac.GetRect()->m_left;
	m_unk0x1ac.VTable0x10(&rect);

	rect.m_right = m_unk0x34.m_right - m_unk0x34.m_left;
	rect.m_left = rect.m_right + (m_unk0x3c8.GetRect()->m_left - m_unk0x3c8.GetRect()->m_right);
	m_unk0x3c8.VTable0x10(&rect);
}

// STUB: LEGORACERS 0x0046e5b0
void OptionsScreenFieldAt0x4178::VTable0x84()
{
	STUB(0x0046e5b0);
}

// STUB: LEGORACERS 0x0046e630
void OptionsScreenFieldAt0x4178::VTable0x88()
{
	STUB(0x0046e630);
}

// STUB: LEGORACERS 0x0046e6b0
void OptionsScreenFieldAt0x4178::VTable0x8c()
{
	STUB(0x0046e6b0);
}

// STUB: LEGORACERS 0x0046e6f0
void OptionsScreenFieldAt0x4178::VTable0x90(LegoS32 p_unk0x04)
{
	if (p_unk0x04 != m_unk0x6c0) {
		double step = m_unk0x6cc;
		double index = p_unk0x04;
		Rect* currentRect = m_unk0x5ec.GetRect();
		Rect rect;
		LegoS32 left = currentRect->m_left;
		rect.m_top = currentRect->m_top;
		LegoS32 width = currentRect->m_right - left;
		rect.m_bottom = currentRect->m_bottom;
		rect.m_left = m_unk0x6c4 + static_cast<LegoS32>(step * index) - (width >> 1);
		rect.m_right = width + rect.m_left;
		m_unk0x5ec.VTable0x10(&rect);

		m_unk0x6c0 = p_unk0x04;
		if (m_eventHandler) {
			m_eventHandler->VTable0x44(this);
		}
	}
}

// STUB: LEGORACERS 0x0046e780
undefined4 OptionsScreenFieldAt0x4178::VTable0x70(undefined4, undefined4, undefined4)
{
	STUB(0x0046e780);
	return 0;
}

// STUB: LEGORACERS 0x0046e810
ObscureVantage0x58* OptionsScreenFieldAt0x4178::VTable0x2c(void*, undefined4, undefined4)
{
	STUB(0x0046e810);
	return NULL;
}
