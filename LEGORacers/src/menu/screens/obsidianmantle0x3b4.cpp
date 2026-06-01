#include "menu/screens/obsidianmantle0x3b4.h"

#include "decomp.h"

DECOMP_SIZE_ASSERT(ObsidianMantle0x3b4, 0x3b4)
DECOMP_SIZE_ASSERT(ObsidianMantle0x3b4::Event0x40, 0x40)

// FUNCTION: LEGORACERS 0x00474c40
void ObsidianMantle0x3b4::Reset()
{
	m_unk0x37d = TRUE;
	m_unk0x368 = 0;
	m_unk0x36c = 0;
	m_unk0x370 = 0;
	m_unk0x374 = NULL;
	ImaginaryTool0x368::Reset();
}

// FUNCTION: LEGORACERS 0x00474c70
undefined4 ObsidianMantle0x3b4::VTable0x14(ObscureVantage0x58* p_vantage, void* p_item, undefined4, undefined4)
{
	Event0x40* item = static_cast<Event0x40*>(p_item);

	if (m_unk0x36c) {
		LegoS32 x = item->m_rect.m_right + item->m_rect.m_left;
		LegoS32 y = item->m_rect.m_bottom + item->m_rect.m_top;
		Rect rect = *m_unk0x374->GetGlobalRect();

		if (!m_unk0x374->FUN_00473a20(&rect, x, y)) {
			FUN_00474ef0();
		}
	}
	else {
		if (m_unk0x358 != m_unk0x374) {
			m_unk0x368 = 0;

			if (m_unk0x358 == p_vantage) {
				m_unk0x374 = m_unk0x358;
			}
			else if (m_unk0x358) {
				LegoS32 x = item->m_rect.m_right + item->m_rect.m_left;
				LegoS32 y = item->m_rect.m_bottom + item->m_rect.m_top;
				Rect rect = *m_unk0x358->GetGlobalRect();

				if (m_unk0x358->FUN_00473a20(&rect, x, y)) {
					m_unk0x374 = m_unk0x358;
				}
				else {
					m_unk0x374 = NULL;
				}
			}
			else {
				m_unk0x374 = NULL;
			}
		}

		if (m_unk0x358 != p_vantage && m_unk0x374) {
			LegoS32 x = item->m_rect.m_right + item->m_rect.m_left;
			LegoS32 y = item->m_rect.m_bottom + item->m_rect.m_top;
			Rect rect = *m_unk0x374->GetGlobalRect();

			if (!m_unk0x374->FUN_00473a20(&rect, x, y)) {
				m_unk0x374 = NULL;
				m_unk0x368 = 0;
			}
		}
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x00474e00 FOLDED
undefined4 ObsidianMantle0x3b4::VTable0x18(
	ObscureVantage0x58* p_unk0x04,
	InputEventQueue::Event* p_unk0x08,
	undefined4 p_unk0x0c,
	undefined4 p_unk0x10
)
{
	if (!m_unk0x36c) {
		FUN_00474e40();
	}

	return ImaginaryTool0x368::VTable0x18(p_unk0x04, p_unk0x08, p_unk0x0c, p_unk0x10);
}

// FUNCTION: LEGORACERS 0x00474e00 FOLDED
undefined4 ObsidianMantle0x3b4::VTable0x1c(
	ObscureVantage0x58* p_unk0x04,
	InputEventQueue::Event* p_unk0x08,
	undefined4 p_unk0x0c,
	undefined4 p_unk0x10
)
{
	if (!m_unk0x36c) {
		FUN_00474e40();
	}

	return ImaginaryTool0x368::VTable0x1c(p_unk0x04, p_unk0x08, p_unk0x0c, p_unk0x10);
}

// FUNCTION: LEGORACERS 0x00474e40
void ObsidianMantle0x3b4::FUN_00474e40()
{
	m_unk0x368 = 0;
	m_unk0x374 = NULL;
	m_unk0x36c = 0;
	m_unk0x370 = 0;
	m_unk0x37c = FALSE;
}

// FUNCTION: LEGORACERS 0x00474e70
void ObsidianMantle0x3b4::FUN_00474e70(ObscureIcon0x1a8* p_icon)
{
	if (m_unk0x36c) {
		FUN_00474ef0();
	}

	m_unk0x37e = 0;
	if (p_icon) {
		m_unk0x37e = p_icon->GetUnk0x168();
	}

	m_unk0x378 = p_icon;
	m_unk0x370 = 0;
	m_unk0x37d = TRUE;
	m_unk0x37c = FALSE;

	if (m_unk0x37e) {
		m_unk0x36c = TRUE;
		return;
	}

	m_unk0x36c = -1;
	FUN_00474f20();
}

// FUNCTION: LEGORACERS 0x00474ef0
void ObsidianMantle0x3b4::FUN_00474ef0()
{
	m_unk0x374 = NULL;
	m_unk0x368 = 0;
	m_unk0x36c = 0;

	if (m_unk0x37c) {
		m_unk0x370 = 1;
	}
	else {
		m_unk0x370 = 0;
	}
}

// FUNCTION: LEGORACERS 0x00474f20
void ObsidianMantle0x3b4::FUN_00474f20()
{
	m_unk0x36c = -1;
	m_unk0x368 = 0;
	m_unk0x370 = 0;
	m_unk0x37c = FALSE;
}

// FUNCTION: LEGORACERS 0x00474f40
LegoBool32 ObsidianMantle0x3b4::VTable0x78(undefined4 p_elapsed)
{
	if (m_unk0x370) {
		m_unk0x370 += p_elapsed;

		if (m_unk0x370 > 250) {
			m_unk0x370 = 0;
		}
	}

	if (m_unk0x374) {
		if (m_unk0x36c == 0) {
			m_unk0x368 += p_elapsed;

			if (m_unk0x368 >= 3000 || m_unk0x370) {
				m_unk0x368 = 3000;
				FUN_00474e70(m_unk0x374);
				m_unk0x37c = TRUE;
				return ImaginaryTool0x368::VTable0x78(p_elapsed);
			}
		}
		else if (m_unk0x36c > 0) {
			m_unk0x36c += p_elapsed;

			if (m_unk0x36c > 20000) {
				FUN_00474f20();
				return ImaginaryTool0x368::VTable0x78(p_elapsed);
			}
		}
	}
	else if (m_unk0x36c) {
		FUN_00474ef0();
	}

	return ImaginaryTool0x368::VTable0x78(p_elapsed);
}

// STUB: LEGORACERS 0x00475010
LegoBool32 ObsidianMantle0x3b4::VTable0x7c(Rect*, Rect*)
{
	STUB(0x00475010);
	return FALSE;
}
