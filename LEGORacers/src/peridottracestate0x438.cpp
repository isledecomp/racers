#include "golhashtable.h"
#include "golstream.h"
#include "peridottrace0x4e0.h"

#include <string.h>

DECOMP_SIZE_ASSERT(PeridotTraceState0x438, 0x438)

// GLOBAL: LEGORACERS 0x004becd8
const LegoChar* g_menuLanguageDirectories[9] =
	{"english", "spanish", "french", "german", "italian", "danish", "swedish", "norwegi", "dutch"};

extern DisplayDriverGuid g_displayDriverGuid;

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
	FUN_0042f020(g_displayDriverGuid);
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

// FUNCTION: LEGORACERS 0x0042f020
void PeridotTraceState0x438::FUN_0042f020(const DisplayDriverGuid& p_guid)
{
	const LegoU32* source = p_guid.GetWords();

	m_unk0x00 = 1;

	SerializedGuidWord* dest = m_displayDriverGuid.m_words;
	for (LegoU32 i = 0; i < sizeOfArray(m_displayDriverGuid.m_words); i++, source++, dest++) {
		dest->Set(*source);
	}
}

// FUNCTION: LEGORACERS 0x0042f060
void PeridotTraceState0x438::FUN_0042f060(DisplayDriverGuid& p_guid)
{
	const SerializedGuidWord* source = m_displayDriverGuid.m_words;
	LegoU32* dest = p_guid.GetWords();
	for (LegoU32 i = 0; i < sizeOfArray(m_displayDriverGuid.m_words); i++, source++, dest++) {
		*dest = source->Get();
	}
}

// FUNCTION: LEGORACERS 0x0042f1f0
LegoU8 PeridotTraceState0x438::FUN_0042f1f0() const
{
	return m_unk0x25 | 1;
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

// FUNCTION: LEGORACERS 0x0042f310
LegoBool32 PeridotTraceState0x438::FUN_0042f310(
	LegoU32 p_unk0x04,
	LegoBool32 p_unk0x08,
	LegoU32 p_unk0x0c,
	GolString* p_string
)
{
	if (p_unk0x04 >= 13) {
		p_unk0x04 -= 13;
		if (p_unk0x04 >= 13) {
			return FALSE;
		}
	}

	LegoU32 current;
	if (!p_unk0x08) {
		current = m_unk0x28[p_unk0x04];
	}
	else {
		current = m_unk0x5c[p_unk0x04];
	}

	if (current && p_unk0x0c >= current) {
		return FALSE;
	}

	if (!p_unk0x08) {
		m_unk0x28[p_unk0x04] = p_unk0x0c;
		PeridotTraceBuffer0x250::CopyStringToBuffer(p_string, m_unk0x90[p_unk0x04], 14);
	}
	else {
		m_unk0x5c[p_unk0x04] = p_unk0x0c;
		PeridotTraceBuffer0x250::CopyStringToBuffer(p_string, m_unk0x1fc[p_unk0x04], 14);
	}

	m_unk0x00 = 1;
	return TRUE;
}
