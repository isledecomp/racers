#include "glassstream0x94.h"

#include "glassblock0x3368.h"
#include "golhashtable.h"
#include "golstream.h"

#include <stdio.h>
#include <string.h>

DECOMP_SIZE_ASSERT(GlassStream0x94, 0x94)

// GLOBAL: LEGORACERS 0x004c4804
LegoChar g_unk0x4c4804[9];

// FUNCTION: LEGORACERS 0x0041ec10
GlassStream0x94::GlassStream0x94()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0041ec90
GlassStream0x94::~GlassStream0x94()
{
	Shutdown();
}

// FUNCTION: LEGORACERS 0x0041ece0
void GlassStream0x94::Reset()
{
	m_context = NULL;
	m_unk0x50 = NULL;

	for (LegoS32 i = 0; i < 2; i++) {
		for (LegoS32 j = 0; j < 4; j++) {
			m_unk0x54[i][j][0] = 0;
			m_unk0x54[i][j][1] = 0;
		}
	}
}

// FUNCTION: LEGORACERS 0x0041ed10
LegoS32 GlassStream0x94::Initialize(LegoRacers::Context* p_context, GlassBlock0x3368* p_block)
{
	if (m_context) {
		Shutdown();
	}

	m_context = p_context;
	m_unk0x50 = p_block;
	sprintf(p_context->m_commonDataDirectory, "GAMEDATA\\COMMON");
	return m_unk0x04.SetContext(m_context);
}

// FUNCTION: LEGORACERS 0x0041ed60
void GlassStream0x94::Shutdown()
{
	m_unk0x04.FUN_004402a0();
	Reset();
}

// FUNCTION: LEGORACERS 0x0041ed80
void GlassStream0x94::Run()
{
	LegoU32 i;

	for (i = 0;; i++) {
		if (i >= sizeOfArray(m_context->m_raceSlots)) {
			if (!(m_context->m_unk0x1e & LegoRacers::Context::c_flagBit5)) {
				break;
			}
		}

		undefined flags = m_context->m_unk0x1e;

		if (flags & LegoRacers::Context::c_flagBit5) {
			flags &= ~LegoRacers::Context::c_flagBit5;
			i = 0;
			m_context->m_unk0x1e = flags;
			m_context->m_unk0xd8 = 0;
			m_unk0x04.FUN_00440860();
			m_context->m_unk0x1e |= LegoRacers::Context::c_flagBit6;
		}
		else {
			if (i == 0) {
				LegoRacers::Context*& context = m_context;
				context->m_unk0x1e |= LegoRacers::Context::c_flagBit6;
			}
			else {
				flags &= ~LegoRacers::Context::c_flagBit6;
				m_context->m_unk0x1e = flags;
			}
		}

		if (m_context->m_raceSlots[i].m_unk0x00 && m_context->m_unk0x00) {
			if (m_context->m_unk0x1e & LegoRacers::Context::c_flagBit3) {
				return;
			}

			if (m_context->m_unk0x32c == c_singleRaceCount) {
				if (m_unk0x04.FUN_004402f0(c_firstScoreIndex) < c_scoreThresholdStep * i) {
					m_context->m_unk0x1c = c_rankDefaultStatus;
					return;
				}
			}

			strcpy(m_context->m_gameDataDirectory, "GAMEDATA\\");
			memcpy(g_unk0x4c4804, m_context->m_raceSlots[i].m_raceName, sizeof(m_context->m_raceSlots[i].m_raceName));
			g_unk0x4c4804[sizeof(m_context->m_raceSlots[i].m_raceName)] = '\0';
			strcat(m_context->m_gameDataDirectory, g_unk0x4c4804);

			LegoChar* gameDataDirectory = m_context->m_gameDataDirectory;
			if (g_hashTable) {
				g_hashTable->SetCurrentEntryFromString(gameDataDirectory);
			}

			m_unk0x50->Initialize(m_context, g_unk0x4c4804, m_context->m_raceSlots[i].m_unk0x04, NULL);
			m_unk0x50->FUN_00432530(&m_unk0x04);
			m_unk0x50->Run();
			m_unk0x50->Shutdown();
			m_context->m_golApp->ClearFileSourceDirectoryCaches();
		}

		m_context->m_unk0xd8++;
	}

	if (!(m_context->m_unk0x1e & LegoRacers::Context::c_flagBit3) && m_context->m_unk0x00) {
		LegoU32 rankIndex = 0;
		ScarletNova0x5c* slot = m_context->m_unk0x108;
		undefined4 slotValue = slot->m_unk0x0c;

		if (slotValue) {
			LegoU32 slotCount = m_context->m_unk0x100;

			while (slotValue && rankIndex < slotCount) {
				slot++;
				rankIndex++;
				slotValue = slot->m_unk0x0c;
			}
		}

		switch (m_unk0x04.FUN_00440300(rankIndex)) {
		case 0:
			m_context->m_unk0x1c = c_rank0Status;
			break;
		case 1:
			m_context->m_unk0x1c = c_rank1Status;
			break;
		case 2:
			m_context->m_unk0x1c = c_rank2Status;
			break;
		default:
			m_context->m_unk0x1c = c_rankDefaultStatus;
			break;
		}
	}
}
