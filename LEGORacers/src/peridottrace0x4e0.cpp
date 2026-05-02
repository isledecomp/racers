#include "peridottrace0x4e0.h"

#include "golhashtable.h"
#include "golstream.h"

#include <string.h>

DECOMP_SIZE_ASSERT(PeridotTraceBase0x24, 0x24)
DECOMP_SIZE_ASSERT(PeridotTraceBase0x24::Record, 0x241)
DECOMP_SIZE_ASSERT(PeridotTrace0x4a8, 0x4a8)
DECOMP_SIZE_ASSERT(PeridotTrace0x4e0, 0x4e0)
DECOMP_SIZE_ASSERT(PeridotTraceActionBase0x34, 0x34)
DECOMP_SIZE_ASSERT(PeridotTraceAction0x34, 0x34)
DECOMP_SIZE_ASSERT(PeridotTraceState0x438, 0x438)
DECOMP_SIZE_ASSERT(PeridotTraceBuffer0x250, 0x250)

// GLOBAL: LEGORACERS 0x004becd8
const LegoChar* g_menuLanguageDirectories[9] =
	{"english", "spanish", "french", "german", "italian", "danish", "swedish", "norwegi", "dutch"};

extern GUID g_displayDriverGuid;

// STUB: LEGORACERS 0x0042b290
PeridotTraceBuffer0x250::PeridotTraceBuffer0x250()
{
	// TODO
	STUB(0x42b290);
}

// STUB: LEGORACERS 0x0042b2b0
PeridotTraceBuffer0x250::~PeridotTraceBuffer0x250()
{
	// TODO
	STUB(0x42b2b0);
}

// STUB: LEGORACERS 0x0042b2f0
void PeridotTraceBuffer0x250::FUN_0042b2f0(undefined4, undefined4, undefined4, undefined4)
{
	// TODO
	STUB(0x0042b2f0);
}

// FUNCTION: LEGORACERS 0x0042b6e0
PeridotTraceBase0x24::PeridotTraceBase0x24()
{
	Init();
}

// FUNCTION: LEGORACERS 0x0042b700
void PeridotTraceBase0x24::Init()
{
	m_unk0x20 = 0;
	m_unk0x00 = 0;
	m_unk0x1c = 0;
	m_unk0x04 = 0;
	m_unk0x14 = 0;
	m_unk0x18 = 0;
	m_unk0x08 = 0;
	m_unk0x0c = 0;
	m_unk0x10 = 0;
}

// STUB: LEGORACERS 0x0042b880
PeridotTraceBase0x24::Record* PeridotTraceBase0x24::FUN_0042b880()
{
	// TODO
	STUB(0x0042b880);
	return NULL;
}

// STUB: LEGORACERS 0x0042e880
PeridotTraceState0x438::PeridotTraceState0x438()
{
	// TODO
	STUB(0x42e880);
}

// STUB: LEGORACERS 0x0042e890
PeridotTraceState0x438::~PeridotTraceState0x438()
{
	// TODO
	STUB(0x42e890);
}

// FUNCTION: LEGORACERS 0x0042e920
void PeridotTraceState0x438::FUN_0042e920(InputManager* p_inputManager)
{
	FUN_0042e950();
	m_inputManager = p_inputManager;
	FUN_0042e960(p_inputManager);
	FUN_0042f020(&g_displayDriverGuid);
	m_unk0x00 = 0;
}

// STUB: LEGORACERS 0x0042e950
void PeridotTraceState0x438::FUN_0042e950()
{
	// TODO
	STUB(0x0042e950);
}

// STUB: LEGORACERS 0x0042e960
void PeridotTraceState0x438::FUN_0042e960(InputManager*)
{
	// TODO
	STUB(0x0042e960);
}

// STUB: LEGORACERS 0x0042eb60
void PeridotTraceState0x438::FUN_0042eb60(PeridotTrace0x4a8*, undefined4)
{
	// TODO
	STUB(0x0042eb60);
}

// STUB: LEGORACERS 0x0042ef80
void PeridotTraceState0x438::FUN_0042ef80(PeridotTrace0x4a8*)
{
	// TODO
	STUB(0x0042ef80);
}

// FUNCTION: LEGORACERS 0x0042ef90
void PeridotTraceState0x438::SetLanguageResourcePath()
{
	LegoChar path[24];

	::strcpy(path, "MENUDATA\\");
	::strcat(path, g_menuLanguageDirectories[m_languageIndex]);

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString(path);
	}
}

// STUB: LEGORACERS 0x0042f020
void PeridotTraceState0x438::FUN_0042f020(const GUID*)
{
	// TODO
	STUB(0x0042f020);
}

// FUNCTION: LEGORACERS 0x0042f200
void PeridotTraceState0x438::FUN_0042f200(LegoU8 p_unk0x04)
{
	m_unk0x00 = 1;
	m_unk0x24 |= p_unk0x04;
}

// FUNCTION: LEGORACERS 0x0042f250
LegoBool32 PeridotTraceState0x438::FUN_0042f250(LegoU32 p_unk0x04)
{
	LegoBool32 result = FALSE;

	if (!static_cast<LegoU16>(m_unk0x26 & p_unk0x04)) {
		result = TRUE;
		m_unk0x26 |= p_unk0x04;
		m_unk0x00 = result;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0042f280
LegoBool32 PeridotTraceState0x438::FUN_0042f280() const
{
	return m_unk0x26 == 0x0fff;
}

// FUNCTION: LEGORACERS 0x00442660
PeridotTrace0x4a8::PeridotTrace0x4a8()
{
	::memset(m_unk0x24, 0, sizeof(m_unk0x24));
	m_unk0x4a4 = 0;
}

// STUB: LEGORACERS 0x00442680
PeridotTrace0x4a8::~PeridotTrace0x4a8()
{
	// TODO
	STUB(0x442680);
}

// STUB: LEGORACERS 0x004426d0
void PeridotTrace0x4a8::FUN_004426d0(undefined4, undefined4, undefined4)
{
	// TODO
	STUB(0x004426d0);
}

// STUB: LEGORACERS 0x00442770
undefined4 PeridotTrace0x4a8::FUN_00442770(GolFile& p_file)
{
	// TODO
	STUB(0x00442770);
	return 0;
}

// STUB: LEGORACERS 0x004437e0
PeridotTrace0x4e0::PeridotTrace0x4e0()
{
	// TODO
	STUB(0x4437e0);
}

// STUB: LEGORACERS 0x00443840
PeridotTrace0x4e0::~PeridotTrace0x4e0()
{
	// TODO
	STUB(0x443840);
}

// STUB: LEGORACERS 0x004438e0
void PeridotTrace0x4e0::FUN_004438e0()
{
	// TODO
	STUB(0x4438e0);
}

// STUB: LEGORACERS 0x00443910
undefined4 PeridotTrace0x4e0::FUN_00443910()
{
	// TODO
	STUB(0x00443910);
	return 0;
}

// STUB: LEGORACERS 0x00443940
undefined4 PeridotTrace0x4e0::FUN_00443940()
{
	// TODO
	STUB(0x00443940);
	return 0;
}

// STUB: LEGORACERS 0x00443980
undefined4 PeridotTrace0x4e0::FUN_00443980()
{
	// TODO
	STUB(0x00443980);
	return 0;
}

// STUB: LEGORACERS 0x004439b0
undefined4 PeridotTrace0x4a8::FUN_004439b0()
{
	// TODO
	STUB(0x004439b0);
	return 0;
}

// STUB: LEGORACERS 0x0044e0a0
PeridotTraceActionBase0x34::~PeridotTraceActionBase0x34()
{
	// TODO
	STUB(0x44e0a0);
}

// STUB: LEGORACERS 0x00450e30
PeridotTraceActionBase0x34::PeridotTraceActionBase0x34()
{
	// TODO
	STUB(0x450e30);
}
