#include "audio/soundgroupbinding.h"
#include "bronzefalcon0xc8770.h"
#include "golerror.h"
#include "imaginarychisel0x658.h"
#include "input/inputdevice.h"
#include "slatepeak0x58.h"

DECOMP_SIZE_ASSERT(ImaginaryChisel0x658::HelperAt0x368, 0x2d0)

// Keep this fold pair out of the unrelated ObscureVantage0x58 null-return fold group.
#pragma code_seg(".text$legoracers_00466090")
// FUNCTION: LEGORACERS 0x00466090 FOLDED
ObscureVantage0x58* ImaginaryChisel0x658::HelperAt0x368::VTable0x2c(void*, undefined4, undefined4)
{
	return NULL;
}
#pragma code_seg()

// FUNCTION: LEGORACERS 0x00466a10
ImaginaryChisel0x658::HelperAt0x368::HelperAt0x368()
{
	FUN_00466b10();
}

// FUNCTION: LEGORACERS 0x00466aa0
ImaginaryChisel0x658::HelperAt0x368::~HelperAt0x368()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x00466b10
void ImaginaryChisel0x658::HelperAt0x368::FUN_00466b10()
{
	m_unk0x2cc = TRUE;
	m_unk0x2ac = 0;
	m_unk0x2b0 = NULL;
	m_unk0x2c4 = 0;
	m_unk0x2c8 = FALSE;
	m_unk0x2b4.m_top = 0;
	m_unk0x2b4.m_bottom = 0;
	m_unk0x2b4.m_left = 0;
	m_unk0x2b4.m_right = 0;
}

// FUNCTION: LEGORACERS 0x00466b50
undefined4 ImaginaryChisel0x658::HelperAt0x368::FUN_00466b50(
	ImaginaryNotion0x290::FieldAt0x54* p_createParams,
	undefined4 p_unk0x08
)
{
	if (m_flags & 1) {
		VTable0x08();
	}

	if (FUN_00472a60(p_createParams)) {
		FUN_00466bf0(p_createParams, p_unk0x08);
	}

	return m_flags & 1;
}

// FUNCTION: LEGORACERS 0x00466b90
void ImaginaryChisel0x658::HelperAt0x368::FUN_00466b90()
{
	const SlatePeak0x58* renderTarget = m_renderer->GetRenderTargetInfo();
	Rect rect = *GetGlobalRect();

	if (rect.m_left < 0) {
		rect.m_left = 0;
	}

	if (rect.m_right > renderTarget->GetWidth()) {
		rect.m_right = renderTarget->GetWidth();
	}

	if (rect.m_top < 0) {
		rect.m_top = 0;
	}

	if (rect.m_bottom > renderTarget->GetHeight()) {
		rect.m_bottom = renderTarget->GetHeight();
	}

	m_unk0x2b4 = rect;
}

// FUNCTION: LEGORACERS 0x00466bf0
void ImaginaryChisel0x658::HelperAt0x368::FUN_00466bf0(
	ImaginaryNotion0x290::FieldAt0x54* p_createParams,
	undefined4 p_unk0x08
)
{
	FUN_00466b90();
	m_unk0x58.FUN_00406980(m_golExport, m_renderer, p_createParams->m_unk0x38, p_unk0x08);

	if (!m_unk0x58.GetFrameCount()) {
		GOL_FATALERROR_MESSAGE("Invalid cinema file, at least 1 cinema is required");
	}

	m_unk0x84.FUN_004a0730(
		m_golExport,
		m_renderer,
		p_createParams->m_soundGroupBinding->GetSoundManager(),
		&m_unk0x58,
		p_createParams->m_unk0x38,
		p_unk0x08
	);
	m_unk0x58.SetUnk0x0c(&m_unk0x84);

	LegoFloat scale = (LegoFloat) ((double) (m_unk0x2b4.m_right - m_unk0x2b4.m_left) /
								   (double) (m_unk0x2b4.m_bottom - m_unk0x2b4.m_top) * p_createParams->m_unk0x50);
	m_unk0x58.FUN_00406f90(scale);

	m_unk0x2c4 = p_createParams->m_unk0x48;
	m_unk0x2ac = p_createParams->m_unk0x4c;
	if (m_unk0x2ac >= m_unk0x58.GetFrameCount()) {
		m_unk0x2c8 = TRUE;
		return;
	}

	m_unk0x2b0 = &m_unk0x58.GetFrames()[m_unk0x2ac];
	m_unk0x2b0->FUN_00406310();
	m_unk0x2b0->FUN_00406490(&m_unk0x2b4);
}

// FUNCTION: LEGORACERS 0x00466d00
void ImaginaryChisel0x658::HelperAt0x368::FUN_00466d00(SaffronQuartz0x2c::Frame0xb8* p_frame)
{
	m_unk0x2b0->FUN_00406330();
	m_unk0x2b0->FUN_00406380();
	m_unk0x2b0 = p_frame;
	m_unk0x2b0->FUN_00406330();
	m_unk0x2b0->FUN_00406310();
	m_unk0x2b0->FUN_00406490(&m_unk0x2b4);
	m_unk0x84.FUN_004a3150();
}

// FUNCTION: LEGORACERS 0x00466d60
LegoBool32 ImaginaryChisel0x658::HelperAt0x368::VTable0x08()
{
	m_unk0x58.Clear();
	m_unk0x84.Clear();
	FUN_00466b10();

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00466d90
undefined4 ImaginaryChisel0x658::HelperAt0x368::VTable0x3c(undefined4 p_elapsedMs)
{
	if (m_unk0x2c8) {
		return FALSE;
	}

	if (m_unk0x2b0->GetUnk0x44() & 4) {
		if (m_unk0x2c4 && ++m_unk0x2ac < m_unk0x58.GetFrameCount()) {
			m_unk0x2b0 = &m_unk0x58.GetFrames()[m_unk0x2ac];
			m_unk0x2b0->FUN_00406330();
			m_unk0x2b0->FUN_00406310();
			m_unk0x84.FUN_004a3150();
		}
		else {
			m_unk0x2c8 = TRUE;
		}
	}

	m_unk0x2b0->FUN_00406390(p_elapsedMs);
	m_unk0x84.FUN_004a2dc0(p_elapsedMs);

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00466e40
undefined4 ImaginaryChisel0x658::HelperAt0x368::VTable0x38(Rect*, Rect*)
{
	if (m_unk0x2c8) {
		return FALSE;
	}

	m_renderer->VTable0xe4();
	m_unk0x2b0->FUN_004064c0(m_renderer, 0);
	m_unk0x84.FUN_004a2f30(m_renderer);
	m_unk0x84.FUN_004a3070(m_renderer);
	m_unk0x84.FUN_004a30b0(m_renderer);
	m_renderer->VTable0xec(0);
	m_renderer->VTable0xe8(0);

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00466ec0
ObscureVantage0x58* ImaginaryChisel0x658::HelperAt0x368::VTable0x30(
	OnyxCircularBuffer0x1c::Item* p_item,
	undefined4,
	undefined4
)
{
	ObscureVantage0x58* result = this;

	if (!m_unk0x2b0 || m_unk0x2b0->GetUnk0x48() >= m_unk0x2b0->GetUnk0x58()) {
		if (m_unk0x2cc) {
			if (!p_item->m_isRepeat) {
				LegoU32 keySource = p_item->m_keyCode & InputDevice::c_sourceMask;
				if (keySource == InputDevice::c_sourceKeyboard || keySource == InputDevice::c_sourceMouse ||
					keySource == InputDevice::c_sourceJoystickButton) {
					m_unk0x2c8 = TRUE;
					return result;
				}
			}
		}
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00466f20
ObscureVantage0x58* ImaginaryChisel0x658::HelperAt0x368::VTable0x34(
	OnyxCircularBuffer0x1c::Item*,
	undefined4,
	undefined4
)
{
	ObscureVantage0x58* result = this;

	if ((!m_unk0x2b0 || m_unk0x2b0->GetUnk0x48() >= m_unk0x2b0->GetUnk0x58()) && m_unk0x2cc) {
		m_unk0x2c8 = TRUE;
		return result;
	}

	return NULL;
}
