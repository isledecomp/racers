#include "menu/screens/racerpickscreenbase0x270c.h"

#include "core/gol.h"
#include "golhashtable.h"
#include "golstream.h"

#include <string.h>

DECOMP_SIZE_ASSERT(RacerPickScreenBase0x270c, 0x270c)

// FUNCTION: LEGORACERS 0x00485890
RacerPickScreenBase0x270c::RacerPickScreenBase0x270c()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00485a00
RacerPickScreenBase0x270c::~RacerPickScreenBase0x270c()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00485af0
void RacerPickScreenBase0x270c::Reset()
{
	m_unk0x26fc = 0;
	m_unk0x77c = 0;

	::memset(m_unk0x2704, 0, sizeof(m_unk0x2704));
	::memset(m_unk0x774, 0, sizeof(m_unk0x774));
	::memset(m_unk0x76c, 0, sizeof(m_unk0x76c));
	::memset(m_unk0x4ec, 0, sizeof(m_unk0x4ec));
	::memset(m_unk0x4dc, 0, sizeof(m_unk0x4dc));
	::memset(m_unk0x73c, 0, sizeof(m_unk0x73c));
	::memset(m_unk0x780, 0, sizeof(m_unk0x780));

	m_unk0x760 = 1.0f;
	m_unk0x74c = 1.0f;
	m_unk0x75c = 0;
	m_unk0x758 = 0;
	m_unk0x754 = 0;
	m_unk0x750 = 0;

	ImaginaryTool0x368::Reset();
}

// STUB: LEGORACERS 0x00485e50
void RacerPickScreenBase0x270c::VTable0x98()
{
	STUB(0x00485e50);
}

// FUNCTION: LEGORACERS 0x00485f70
void RacerPickScreenBase0x270c::VTable0x4c()
{
	if (g_hashTable != NULL) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA\\RS_SET");
	}

	LegoS32 i;

	for (i = 0; i < m_unk0x26fc; i++) {
		FUN_0046c510(&m_unk0x98c[i], 0, i + 0x6e);
	}

	if (g_hashTable != NULL) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}

	for (i = 0; i < m_unk0x26fc; i++) {
		FUN_0046bf80(&m_unk0x1cec[i], i + 0x72, 0x37, 0x37);
	}

	VTable0x98();
}

// FUNCTION: LEGORACERS 0x00486020
void RacerPickScreenBase0x270c::VTable0x80()
{
	ColorRGBA materialColor;
	ColorRGBA lightColor;

	materialColor.m_blu = 0x78;
	materialColor.m_grn = 0x78;
	materialColor.m_red = 0x78;
	lightColor.m_blu = 0xff;
	lightColor.m_grn = 0xff;
	lightColor.m_red = 0xff;

	FUN_0047fec0(&materialColor, &lightColor);
}

// STUB: LEGORACERS 0x00486060
LegoBool32 RacerPickScreenBase0x270c::VTable0xa0(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*, undefined4*)
{
	STUB(0x00486060);
	return FALSE;
}

// FUNCTION: LEGORACERS 0x004860f0
LegoBool32 RacerPickScreenBase0x270c::Destroy()
{
	if (!m_initialized) {
		return TRUE;
	}

	for (LegoS32 i = 0; i < m_unk0x77c; i++) {
		m_unk0x232c[i].VTable0x54();
		m_unk0x4fc[i].VTable0x54();
		m_golExport->VTable0x48(m_unk0x4ec[i]);
		m_golExport->VTable0x4c(m_unk0x4dc[i]);

		if (i != 0) {
			m_golExport->VTable0x48(m_unk0x73c[i]);
		}
	}

	return ImaginaryTool0x368::Destroy();
}

// STUB: LEGORACERS 0x00486250
void RacerPickScreenBase0x270c::FUN_00486250(LegoS32)
{
	STUB(0x00486250);
}

// FUNCTION: LEGORACERS 0x00486400
void RacerPickScreenBase0x270c::FUN_00486400(LegoS32 p_index)
{
	m_unk0x780[p_index] = (m_unk0x780[p_index] + 1) % m_unk0x2700;
	FUN_004866e0(p_index);
	FUN_00486250(p_index);
	m_unk0x774[p_index] = TRUE;
}

// FUNCTION: LEGORACERS 0x004864a0
void RacerPickScreenBase0x270c::FUN_004864a0(LegoS32 p_index)
{
	m_unk0x22dc[p_index].FUN_00442fe0();
	m_unk0x780[p_index] = (m_unk0x780[p_index] + 1) % m_unk0x2700;
	FUN_004866e0(p_index);
	FUN_00486250(p_index);
	m_unk0x774[p_index] = TRUE;
}

// FUNCTION: LEGORACERS 0x004864f0
void RacerPickScreenBase0x270c::FUN_004864f0(LegoS32 p_index)
{
	m_unk0x22dc[p_index].FUN_00443050();
	m_unk0x780[p_index] = (m_unk0x780[p_index] + 1) % m_unk0x2700;
	FUN_004866e0(p_index);
	FUN_00486250(p_index);
	m_unk0x774[p_index] = TRUE;
}

// FUNCTION: LEGORACERS 0x004866e0
void RacerPickScreenBase0x270c::FUN_004866e0(LegoS32 p_index)
{
	m_unk0x1ddc[p_index].FUN_00487600(NULL);
	m_unk0x205c[p_index].FUN_00487600(NULL);
	m_unk0x774[p_index] = FALSE;
	m_unk0x76c[p_index] = FALSE;
}

// STUB: LEGORACERS 0x00486730
void RacerPickScreenBase0x270c::VTable0x9c()
{
	STUB(0x00486730);
}

// FUNCTION: LEGORACERS 0x004869b0
LegoBool32 RacerPickScreenBase0x270c::VTable0x88()
{
	for (LegoS32 i = 0; i < m_unk0x26fc; i++) {
		if (!(m_unk0x232c[i].GetFlags() & 0x10000)) {
			break;
		}

		if (!m_unk0x232c[i].FUN_0040e360()) {
			return FALSE;
		}
	}

	return TRUE;
}

// STUB: LEGORACERS 0x00486a00
LegoBool32 RacerPickScreenBase0x270c::VTable0x78(undefined4)
{
	STUB(0x00486a00);
	return FALSE;
}
