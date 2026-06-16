#include "race/racestate.h"

#include "audio/soundnode.h"
#include "camera/golcamera.h"
#include "menu/runtime/cutsceneparticle.h"
#include "menu/runtime/cutsceneplayer.h"
#include "race/cobalttrail0x140.h"
#include "race/racecameracontroller.h"
#include "render/gold3drenderdevice.h"

#include <string.h>

DECOMP_SIZE_ASSERT(RaceState, 0x320)
DECOMP_SIZE_ASSERT(RaceState::Racer, 0xe34)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x018, 0x3d0)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x3e8, 0x158)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0xc70, 0x54)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0xc70::Field0x050, 0x30)
DECOMP_SIZE_ASSERT(RaceState::Field0x0f0, 0x194)
DECOMP_SIZE_ASSERT(RaceState::Field0x284, 0x1c)
DECOMP_SIZE_ASSERT(RaceState::Field0x2a0, 0x78)

extern LegoU16 g_unk0x004befec[1024];
extern LegoU32 g_unk0x004c6ee4;

extern const LegoFloat g_violetShoalTwo;

// GLOBAL: LEGORACERS 0x004b0958
extern const LegoFloat g_unk0x004b0958 = 30.0f;

// GLOBAL: LEGORACERS 0x004b095c
extern const LegoFloat g_unk0x004b095c = 300.0f;

// GLOBAL: LEGORACERS 0x004b0af0
extern const LegoFloat g_unk0x004b0af0 = 15.0f;

// GLOBAL: LEGORACERS 0x004b0af4
extern const LegoFloat g_unk0x004b0af4 = 6.0f;

// GLOBAL: LEGORACERS 0x004b0b38
extern const LegoFloat g_unk0x004b0b38 = 2500.0f;

// GLOBAL: LEGORACERS 0x004b0b3c
extern const LegoFloat g_unk0x004b0b3c = 10000.0f;

// GLOBAL: LEGORACERS 0x004b0b4c
extern const LegoFloat g_unk0x004b0b4c = 191.0f;

// STUB: LEGORACERS 0x004371c0
void RaceState::Racer::FUN_004371c0(undefined4*, LegoFloat)
{
	STUB(0x004371c0);
}

// STUB: LEGORACERS 0x004374c0
void RaceState::Racer::FUN_004374c0()
{
	STUB(0x004374c0);
}

// STUB: LEGORACERS 0x00438500
void RaceState::Racer::FUN_00438500()
{
	STUB(0x00438500);
}

// STUB: LEGORACERS 0x00439100
void RaceState::Racer::FUN_00439100()
{
	LegoU32 state = m_unk0xccc;
	if (!state) {
		FUN_00439c90();
		return;
	}

	LegoU32 flags = m_unk0xd04;
	LegoU32 index = m_unk0xd58;

	if (flags & c_flags0xd04Bit24) {
		m_unk0x008->FUN_0045a950(this, 1);
		m_unk0xccc = 0;
		FUN_00439520();
		return;
	}

	if (flags & c_flags0xd04Bit25) {
		index = 3;
	}

	switch (state) {
	case 3:
		if (!((flags & c_flags0xd04Bit27) && index != 3)) {
			m_unk0x008->FUN_0045b1e0(this, index);
		}
		m_unk0xccc = 0;
		FUN_00439520();
		return;
	case 1:
		m_unk0x008->FUN_0045a950(this, index);
		m_unk0xccc = 0;
		FUN_00439520();
		return;
	case 4:
		FUN_00439240(TRUE);
		m_unk0x008->FUN_0045a9b0(this, index);
		m_unk0xccc = 0;
		FUN_00439520();
		return;
	case 2:
		FUN_00439240(TRUE);
		m_unk0x008->FUN_0045b030(this, index);
		m_unk0xccc = 0;
		FUN_00439520();
		return;
	default:
		return;
	}
}

// FUNCTION: LEGORACERS 0x00439210
LegoU32 RaceState::Racer::FUN_00439210(LegoU32 p_unk0x04)
{
	m_unk0xcd8 = 0;
	m_unk0xccc = p_unk0x04;
	m_unk0xcdc = 300;
	return p_unk0x04;
}

// FUNCTION: LEGORACERS 0x00439240
void RaceState::Racer::FUN_00439240(LegoBool32 p_unk0x04)
{
	if (m_unk0xd44 <= 0) {
		SoundVector position;
		m_unk0x018.m_unk0x044->VTable0x04(&position);

		LegoU32 randomIndex;
		if (p_unk0x04) {
			randomIndex = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
			LegoU32 randomValue = g_unk0x004befec[randomIndex];
			g_unk0x004c6ee4 = randomIndex;
			m_unk0x004->FUN_00443b80(
				randomValue % c_feedbackVariantCount + m_unk0xd40 + c_feedbackHighOffset,
				&position,
				100.0f,
				400.0f,
				1.0f,
				1.0f
			);
		}
		else {
			randomIndex = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
			g_unk0x004c6ee4 = randomIndex;
			LegoU32 randomValue = g_unk0x004befec[randomIndex];
			m_unk0x004->FUN_00443b80(
				m_unk0xd40 + randomValue % c_feedbackVariantCount,
				&position,
				100.0f,
				400.0f,
				1.0f,
				1.0f
			);
		}

		randomIndex = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
		g_unk0x004c6ee4 = randomIndex;
		LegoU16 randomValue = g_unk0x004befec[randomIndex];
		m_unk0xd44 = randomValue * 4 + 5000;
	}
}

// STUB: LEGORACERS 0x00439340
void RaceState::Racer::FUN_00439340()
{
	LegoU32 value = m_unk0xd04 & 0xfffffffd;
	m_unk0xd04 = value;

	value = 1;
	m_unk0xad4 = value;

	if (m_unk0xe2c) {
		m_unk0xb30 = 0;
	}

	m_unk0xd14 = value;
	value = m_unk0xd08;
	m_unk0xd0c = 0;
	m_unk0xd10 = 2;

	if (value == 2) {
		g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
		value = g_unk0x004befec[g_unk0x004c6ee4];
		if ((value & 0xff) < m_unk0xd1e) {
			m_unk0x008->FUN_0045b1e0(this, 0);
		}
	}
}

// FUNCTION: LEGORACERS 0x004393d0
void RaceState::Racer::FUN_004393d0()
{
	SoundVector position;
	m_unk0x018.m_unk0x044->VTable0x04(&position);

	m_unk0x004->FUN_00443b80(0x3e, &position, g_unk0x004b0958, g_unk0x004b095c, 1.0f, 1.0f);
	m_unk0xd04 |= c_flags0xd04Bit10;
}

// STUB: LEGORACERS 0x00439420
LegoBool32 RaceState::Racer::FUN_00439420(Field0xd5c* p_unk0x04)
{
	if (m_unk0xd58 != sizeOfArray(m_unk0xd5c)) {
		LegoU32 index = 0;
		Field0xd5c** current = m_unk0xd5c;

		while (*current) {
			index++;
			current++;

			if (index >= sizeOfArray(m_unk0xd5c)) {
				return FALSE;
			}
		}

		m_unk0xd5c[index] = p_unk0x04;
		m_unk0x004->FUN_00443b50(m_unk0xd58 + 11);

		LegoU32 count = m_unk0xd58;
		count++;
		m_unk0xd58 = count;

		if (count == sizeOfArray(m_unk0xd5c)) {
			FUN_00439240(TRUE);
		}

		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00439490
RaceState::Racer::Field0xd5c* RaceState::Racer::FUN_00439490()
{
	Field0xd5c* result;
	LegoU32 index;

	if (m_unk0xd58) {
		index = 0;
		Field0xd5c** current = m_unk0xd5c;
		while (index < sizeOfArray(m_unk0xd5c) && !*current) {
			index++;
			current++;
		}

		if (index >= sizeOfArray(m_unk0xd5c)) {
			return NULL;
		}
	}
	else {
		return NULL;
	}

	result = m_unk0xd5c[index];
	m_unk0xd5c[index] = NULL;

	GolVec3 position;
	m_unk0x018.m_unk0x044->VTable0x04(&position);
	m_unk0xd58--;
	result->FUN_00453790(position);
	return result;
}

// FUNCTION: LEGORACERS 0x00439520
LegoU32 RaceState::Racer::FUN_00439520()
{
	LegoU32 result = m_unk0xd58;

	if (result) {
		Field0xd5c** current = m_unk0xd5c;
		LegoS32 remaining = sizeOfArray(m_unk0xd5c);
		do {
			if (*current) {
				(*current)->FUN_004537f0();
				result = m_unk0xd58 - 1;
				m_unk0xd58 = result;
				*current = NULL;
			}

			current++;
		} while (--remaining);
	}

	return result;
}

// FUNCTION: LEGORACERS 0x004395a0
void RaceState::Racer::FUN_004395a0()
{
	LegoU32 flags = m_unk0xd04;
	if (flags & c_flags0xd04Bit3) {
		m_unk0xd04 = flags & ~c_flags0xd04Bit3;
		m_unk0x3e8.VTable0x34();
	}
}

// FUNCTION: LEGORACERS 0x00439660
void RaceState::Racer::FUN_00439660()
{
	m_unk0xd04 &= ~c_flags0xd04Bit4;

	Field0x018* field = &m_unk0x018;
	field->FUN_0043db60();

	if (m_unk0xd08 == 2 && m_unk0xb2c) {
		m_unk0x3e8.FUN_00429af0();
		field->m_unk0x000 |= Field0x018::c_flags0x000Bit2;
		return;
	}

	m_unk0xaa8 &= ~c_flags0xaa8Bit12;
	field->m_unk0x000 |= Field0x018::c_flags0x000Bit2;
}

// FUNCTION: LEGORACERS 0x00439730
void RaceState::Racer::FUN_00439730()
{
	m_unk0xd04 &= ~c_flags0xd04Bit6;
	m_unk0x018.FUN_0043fd70();
	m_unk0xc70.m_unk0x014 &= ~(Field0xc70::c_flags0x014Bit0 | Field0xc70::c_flags0x014Bit8);
	m_unk0x3e8.FUN_00429330();
}

// FUNCTION: LEGORACERS 0x00439770
LegoU32 RaceState::Racer::FUN_00439770(LegoU32 p_unk0x04)
{
	m_unk0xd04 |= c_flags0xd04Bit0;
	m_unk0xd6c = p_unk0x04;
	return p_unk0x04;
}

// STUB: LEGORACERS 0x00439790
void RaceState::Racer::FUN_00439790()
{
	m_unk0xd04 &= ~c_flags0xd04Bit0;
}

// FUNCTION: LEGORACERS 0x004397b0
void RaceState::Racer::FUN_004397b0()
{
	m_unk0x3e8.VTable0x3c();
}

// FUNCTION: LEGORACERS 0x00439870
void RaceState::Racer::FUN_00439870()
{
	SoundVector position;

	if (m_unk0xd04 & c_flags0xd04Bit7) {
		if (m_unk0xc70.m_unk0x014 & Field0xc70::c_flags0x014Bit2) {
			m_unk0xc70.FUN_004202c0();
		}

		LegoU8 flags0xaa8 = static_cast<LegoU8>(m_unk0xaa8);
		LegoU8 testFlag = c_flags0xaa8Bit3;
		if (!(testFlag & flags0xaa8)) {
			if (m_unk0xc70.m_unk0x014 & Field0xc70::c_flags0x014Bit3) {
				m_unk0x018.m_unk0x044->VTable0x04(&position);
				m_unk0x004->FUN_00443b80(0x41, &position, g_unk0x004b0958, g_unk0x004b095c, 1.0f, 1.0f);
			}

			if (!(m_unk0xc70.m_unk0x014 & Field0xc70::c_flags0x014Bit0)) {
				m_unk0x018.FUN_0043dcd0();
			}
		}

		LegoU32 flags0xd04 = m_unk0xd04;
		flags0xd04 &= ~c_flags0xd04Bit7;
		m_unk0xd04 = flags0xd04;
	}
}

// STUB: LEGORACERS 0x00439b00
void RaceState::Racer::FUN_00439b00()
{
	STUB(0x00439b00);
}

// FUNCTION: LEGORACERS 0x00439c90
void RaceState::Racer::FUN_00439c90()
{
	SoundVector position;
	m_unk0x018.m_unk0x044->VTable0x04(&position);

	m_unk0x004->FUN_00443b80(m_unk0xd23, &position, g_unk0x004b0958, g_unk0x004b095c, 1.0f, 1.0f);
	m_unk0xadc->FUN_00462580(999, 999, &position);
}

// FUNCTION: LEGORACERS 0x0043a0c0
void RaceState::Racer::FUN_0043a0c0()
{
	m_unk0xe30->m_unk0x03c = (m_unk0xe30->m_unk0x03c + 1) & 3;
}

// FUNCTION: LEGORACERS 0x0043a0e0
void RaceState::Racer::FUN_0043a0e0()
{
	Field0x00c::Entry* unk0xe2c = m_unk0xe2c;
	m_unk0xd08 = 2;

	if (!unk0xe2c) {
		unk0xe2c = m_unk0x00c->FUN_0043d070(this);
		m_unk0xe2c = unk0xe2c;

		if (unk0xe2c) {
			m_unk0xc70.FUN_004202f0(unk0xe2c);
		}
		else {
			m_unk0xc70.m_unk0x014 |= 0x80;
		}
	}
}

// STUB: LEGORACERS 0x0043a1a0
void RaceState::Racer::FUN_0043a1a0()
{
	STUB(0x0043a1a0);
}

// FUNCTION: LEGORACERS 0x0043a210
void RaceState::Racer::FUN_0043a210(LegoU32 p_unk0x04)
{
	if (!(m_unk0xd04 & c_flags0xd04Bit1)) {
		LegoU32 unk0xd00 = m_lapTimes[5];
		if (p_unk0x04 < unk0xd00) {
			FUN_00439240(TRUE);
		}
		else if (p_unk0x04 > unk0xd00) {
			FUN_00439240(FALSE);
		}

		m_lapTimes[5] = p_unk0x04;
	}
	else {
		m_lapTimes[5] = p_unk0x04;
	}
}

// FUNCTION: LEGORACERS 0x0043a300
void RaceState::Racer::FUN_0043a300(LegoU32 p_unk0x04, LegoBool32 p_unk0x08)
{
	if (m_unk0xdb4) {
		m_unk0xdb4->FUN_004283f0(p_unk0x04, p_unk0x08);
		m_unk0xdb4->m_unk0x000 = TRUE;
		m_unk0xdb8 = p_unk0x04;

		if (p_unk0x08) {
			m_unk0xd04 |= c_flags0xd04Bit22;
		}
		else {
			m_unk0xd04 &= ~c_flags0xd04Bit22;
		}
	}
}

// FUNCTION: LEGORACERS 0x0043a360
void RaceState::Racer::FUN_0043a360()
{
	if (m_unk0xdb4) {
		m_unk0xdb4->FUN_004283f0(m_unk0xdb8, m_unk0xd04 & 0x00400000);
		m_unk0xdb4->m_unk0x000 = TRUE;
	}
}

// FUNCTION: LEGORACERS 0x0043a390
void RaceState::Racer::FUN_0043a390()
{
	LegoU32 flags = m_unk0xd04;
	if (!(flags & c_flags0xd04Bit12) && (flags & c_flags0xd04Bit10)) {
		RaceCameraController* controller = m_unk0xdb4;
		if (controller) {
			LegoU32 index = m_unk0xdb8;
			LegoBool32 enabled = flags & c_flags0xd04Bit22;
			index++;
			index &= 3;
			m_unk0xdb8 = index;
			controller->FUN_004283f0(index, enabled);
			m_unk0xdb4->m_unk0x000 = TRUE;
		}
	}
}

// FUNCTION: LEGORACERS 0x0043a3e0
void RaceState::Racer::FUN_0043a3e0()
{
	if (m_unk0xdb4) {
		m_unk0xdb4->m_unk0x000 = TRUE;
	}
}

// FUNCTION: LEGORACERS 0x0043a3f0
void RaceState::Racer::FUN_0043a3f0()
{
	m_unk0xdb4->m_unk0x004 = TRUE;
}

// FUNCTION: LEGORACERS 0x0043a400
void RaceState::Racer::FUN_0043a400()
{
	m_unk0xdb4->m_unk0x004 = FALSE;
}

// FUNCTION: LEGORACERS 0x0043a410
RaceState::Field0x284::Field0x284()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0043a420
RaceState::Field0x284::~Field0x284()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0043a430
void RaceState::Field0x284::Reset()
{
	m_unk0x00[0] = 0;
	m_unk0x00[1] = 0;
	m_unk0x00[2] = 0;
	m_unk0x00[3] = 0;
}

// FUNCTION: LEGORACERS 0x0043a440
void RaceState::Field0x284::Destroy()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0043ae40
RaceState::RaceState()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0043aee0
RaceState::~RaceState()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0043af80
void RaceState::Reset()
{
	m_unk0x0f0.m_racers = NULL;
	m_unk0x0f0.m_unk0x058 = 0;
	m_unk0x0f0.m_racerCount = 0;
	m_unk0x0f0.m_unk0x05c = 0;

	LegoS32 i;
	for (i = 0; i < sizeOfArray(m_unk0x0f0.m_unk0x064); i++) {
		m_unk0x0f0.m_unk0x064[i] = 0;
		m_unk0x0f0.m_unk0x0a4[i].m_x = 0.0f;
		m_unk0x0f0.m_unk0x0a4[i].m_y = 0.0f;
		m_unk0x0f0.m_unk0x0a4[i].m_z = 0.0f;
		m_unk0x0f0.m_unk0x0ec[i].m_x = 0.0f;
		m_unk0x0f0.m_unk0x0ec[i].m_y = 0.0f;
		m_unk0x0f0.m_unk0x0ec[i].m_z = 0.0f;
		m_unk0x0f0.m_unk0x134[i].m_x = 0.0f;
		m_unk0x0f0.m_unk0x134[i].m_y = 0.0f;
		m_unk0x0f0.m_unk0x134[i].m_z = 0.0f;
		m_unk0x0f0.m_unk0x17c[i] = 0;
	}

	m_unk0x0f0.m_unk0x07c = NULL;
	m_unk0x0f0.m_unk0x080[0] = 0;
	m_unk0x0f0.m_unk0x080[1] = 0;
	m_unk0x0f0.m_unk0x080[2] = 0;

	for (i = 0; i < sizeOfArray(m_unk0x0f0.m_unk0x08c); i++) {
		m_unk0x0f0.m_unk0x08c[i] = 0;
		m_unk0x0f0.m_unk0x094[i] = 0;
	}

	m_unk0x0f0.m_unk0x09c = 0;
	m_unk0x0f0.m_unk0x0a0 = 0;
	m_unk0x284.m_unk0x10 = 0;
	m_unk0x284.m_unk0x14 = 0;
	m_unk0x284.m_lapCount = 0;
}

// STUB: LEGORACERS 0x0043b030
void RaceState::Destroy()
{
	STUB(0x0043b030);
}

// FUNCTION: LEGORACERS 0x0043beb0
void RaceState::RecordBestTimes(LegoRacers::Context* p_context)
{
	LegoU32 bestLapTime = c_invalidTime;
	LegoU32 bestRaceTime = c_invalidTime;
	LegoU32 bestRacerIndex = c_invalidTime;
	LegoU32 racerCount = m_unk0x0f0.m_racerCount;

	if (racerCount > 0) {
		LegoU32 racerIndex;

		racerIndex = 0;
		do {
			if (!p_context->m_playerSetupSlots[racerIndex].m_unk0x10) {
				Racer* racer = &m_unk0x0f0.m_racers[racerIndex];
				LegoU32 lapCount = m_unk0x284.m_lapCount;
				if (lapCount <= racer->m_lapsCompleted) {
					if (lapCount) {
						LegoU32 remaining = lapCount;
						LegoU32 raceTime = 0;
						LegoU32* lapTimes = racer->m_lapTimes;

						do {
							LegoU32 lapTime = *lapTimes;
							if (lapTime < bestLapTime) {
								bestLapTime = lapTime;
								bestRacerIndex = racerIndex;
							}
							raceTime += lapTime;
							lapTimes++;
						} while (--remaining);

						if (raceTime < bestRaceTime) {
							bestRaceTime = raceTime;
						}
					}
					else if (0 < bestRaceTime) {
						bestRaceTime = 0;
					}
				}
			}

			racerIndex++;
		} while (racerIndex < racerCount);
	}

	if (bestLapTime < c_invalidTime) {
		LegoU32* lapRecord = &p_context->m_bestLapTimes[p_context->m_currentRaceIndex];
		if (!*lapRecord || bestLapTime <= *lapRecord) {
			*lapRecord = bestLapTime;
			p_context->m_bestLapHolders[p_context->m_currentRaceIndex] = bestRacerIndex;
		}
	}

	if (bestRaceTime < c_invalidTime) {
		LegoU32* raceRecord = &p_context->m_bestRaceTimes[p_context->m_currentRaceIndex];
		if (!*raceRecord || bestRaceTime <= *raceRecord) {
			*raceRecord = bestRaceTime;
			p_context->m_bestRaceHolders[p_context->m_currentRaceIndex] = bestRacerIndex;
		}
	}
}

// FUNCTION: LEGORACERS 0x0043bff0
void RaceState::FUN_0043bff0(GolD3DRenderDevice* p_renderer)
{
	for (LegoU32 i = 0; i < m_unk0x0f0.m_racerCount; i++) {
		m_unk0x0f0.m_racers[i].m_unk0x018.FUN_0043fc20(p_renderer);
	}
}

// STUB: LEGORACERS 0x0043c030
void RaceState::FUN_0043c030(LegoU32)
{
	STUB(0x0043c030);
}

// FUNCTION: LEGORACERS 0x0043c6a0
void RaceState::FUN_0043c6a0(GolCamera* p_camera)
{
	LegoU32 i = 0;
	if (i < m_unk0x0f0.m_racerCount) {
		do {
			m_unk0x0f0.m_racers[i].m_unk0x018.FUN_0043fa50(p_camera);
			i++;
		} while (i < m_unk0x0f0.m_racerCount);
	}
}

// STUB: LEGORACERS 0x0043ccb0
void RaceState::FUN_0043ccb0()
{
	STUB(0x0043ccb0);
}

// FUNCTION: LEGORACERS 0x0043cd30
void RaceState::FUN_0043cd30(GolRenderDevice* p_renderer, Racer* p_racer)
{
	for (LegoU32 i = 0; i < m_unk0x0f0.m_racerCount; i++) {
		if (p_racer != &m_unk0x0f0.m_racers[i] || p_racer->m_unk0xdb8 != 3 ||
			(p_racer->m_unk0xd04 & c_racerFlags0xd04Bit12) || !(p_racer->m_unk0xd04 & c_racerFlags0xd04Bit10)) {
			m_unk0x0f0.m_racers[i].m_unk0x018.m_unk0x004.VTable0x1c(*p_renderer);
		}
	}
}

// FUNCTION: LEGORACERS 0x0043d120
void RaceState::FUN_0043d120()
{
	RaceResourceManager::Resource* resource = m_unk0x0f0.m_unk0x07c;
	if (resource) {
		m_unk0x0f0.m_unk0x05c->FUN_00443c10(resource);
		m_unk0x0f0.m_unk0x07c = NULL;
	}
}

// FUNCTION: LEGORACERS 0x0043d9f0
void RaceState::Racer::Field0x018::FUN_0043d9f0()
{
	m_unk0x218.AssignEntryByName(0, m_unk0x074);
}

// FUNCTION: LEGORACERS 0x0043da10
void RaceState::Racer::Field0x018::FUN_0043da10()
{
	m_unk0x224.AssignEntryByName(0, "trbskid");
}

// FUNCTION: LEGORACERS 0x0043da30
void RaceState::Racer::Field0x018::FUN_0043da30()
{
	m_unk0x224.AssignEntryByName(0, "skid");
}

// FUNCTION: LEGORACERS 0x0043db60
void RaceState::Racer::Field0x018::FUN_0043db60()
{
	m_unk0x000 |= c_flags0x000Bit1;

	for (LegoU32 i = 0; i < sizeOfArray(m_unk0x068); i++) {
		m_unk0x03c->SetModelDistance(i, m_unk0x068[i]);
		m_unk0x044->SetModelDistance(i, m_unk0x068[i]);
		m_unk0x048->SetModelDistance(i, m_unk0x068[i]);

		if (m_unk0x040) {
			m_unk0x040->SetModelDistance(i, m_unk0x068[i]);
		}
	}
}

// FUNCTION: LEGORACERS 0x0043dcd0
void RaceState::Racer::Field0x018::FUN_0043dcd0()
{
	for (LegoU32 i = 0; i < sizeOfArray(m_unk0x1e4); i++) {
		if (m_unk0x1e4[i]) {
			m_unk0x1e0->FUN_00492820(m_unk0x1e4[i], 1000);
			m_unk0x1e4[i] = NULL;
		}

		LegoU8 flags = m_unk0x1f4[i];
		if (flags & c_slotFlagsBit1) {
			flags &= ~c_slotFlagsBit1;
			flags |= c_slotFlagsBit2;
			m_unk0x1f4[i] = flags;
		}
		else {
			m_unk0x1f4[i] = 0;
		}
	}

	if (m_unk0x274) {
		m_unk0x27c->FUN_00489f30(m_unk0x274);
		m_unk0x274 = NULL;
	}

	m_unk0x000 &= ~c_flags0x000Bit3;
}

// FUNCTION: LEGORACERS 0x0043dd50
void RaceState::Racer::Field0x018::FUN_0043dd50(LegoU32 p_unk0x04, const LegoChar* p_unk0x08)
{
	if (m_unk0x230[p_unk0x04]) {
		if (::strncmp(m_unk0x240[p_unk0x04], p_unk0x08, sizeof(GolName)) == 0) {
			return;
		}

		m_unk0x27c->FUN_00489f00(m_unk0x230[p_unk0x04]);
		m_unk0x230[p_unk0x04] = NULL;
	}

	::memcpy(m_unk0x240[p_unk0x04], p_unk0x08, sizeof(GolName));
	if (m_unk0x27c->FUN_00489d50(p_unk0x08)) {
		m_unk0x230[p_unk0x04] = m_unk0x27c->FUN_00489d70(p_unk0x08, NULL, NULL, NULL);
		m_unk0x260[p_unk0x04] = TRUE;
	}
	else if (m_unk0x280->FUN_00489d50(p_unk0x08)) {
		m_unk0x230[p_unk0x04] = m_unk0x280->FUN_00489d70(p_unk0x08, NULL, NULL, NULL);
		m_unk0x260[p_unk0x04] = FALSE;
	}

	CutsceneParticleRef* ref = m_unk0x230[p_unk0x04];
	if (!ref) {
		return;
	}

	GolVec3 position = m_unk0x1dc->m_unk0x1a4[p_unk0x04].m_unk0x000;
	CutsceneParticle* particle = ref->m_unk0x00;
	GolWorldEntity* entity = m_unk0x044;

	if (particle) {
		entity->VTable0x44(particle->GetUnk0x160());
	}

	if (m_unk0x230[p_unk0x04]->m_unk0x00) {
		m_unk0x230[p_unk0x04]->m_unk0x00->FUN_00489660(&position);
	}
}

// STUB: LEGORACERS 0x0043de90
void RaceState::Racer::Field0x018::FUN_0043de90(LegoU32 p_unk0x04)
{
	CutsceneParticleRef* ref = m_unk0x230[p_unk0x04];
	if (ref) {
		m_unk0x240[p_unk0x04][0] = 0;
		m_unk0x27c->FUN_00489f00(ref);
		m_unk0x230[p_unk0x04] = NULL;
	}
}

// FUNCTION: LEGORACERS 0x0043def0
void RaceState::Racer::Field0x018::FUN_0043def0()
{
	CutsceneParticleRef* ref = m_unk0x270;
	if (ref) {
		return;
	}
	if (m_unk0x230[3]) {
		return;
	}
	if (m_unk0x230[2]) {
		return;
	}

	ref = m_unk0x27c->FUN_00489d70("dust", NULL, NULL, NULL);
	m_unk0x270 = ref;
	if (!ref) {
		return;
	}

	GolVec3 position = m_unk0x1dc->m_unk0x1a4[3].m_unk0x000;
	CutsceneParticle* particle = ref->m_unk0x00;
	GolWorldEntity* entity = m_unk0x044;

	if (particle) {
		entity->VTable0x44(particle->GetUnk0x160());
	}

	if (m_unk0x270->m_unk0x00) {
		m_unk0x270->m_unk0x00->FUN_00489660(&position);
	}
}

// FUNCTION: LEGORACERS 0x0043df90
void RaceState::Racer::Field0x018::FUN_0043df90()
{
	CutsceneParticleRef* ref = m_unk0x278;
	if (ref) {
		return;
	}

	ref = m_unk0x27c->FUN_00489d70("carsmke", NULL, NULL, NULL);
	m_unk0x278 = ref;
	if (!ref) {
		return;
	}

	GolVec3 position = m_unk0x1dc->m_unk0x1a4[3].m_unk0x000;
	GolVec3 other = m_unk0x1dc->m_unk0x1a4[2].m_unk0x000;
	GolWorldEntity* entity = m_unk0x044;

	position.m_x = (position.m_x + other.m_x) * 0.5f;
	position.m_y = (position.m_y + other.m_y) * 0.5f;
	position.m_z = (position.m_z + other.m_z) * 0.5f + g_violetShoalTwo;

	CutsceneParticle* particle = ref->m_unk0x00;
	if (particle) {
		entity->VTable0x44(particle->GetUnk0x160());
	}

	if (m_unk0x278->m_unk0x00) {
		m_unk0x278->m_unk0x00->FUN_00489660(&position);
	}
}

// STUB: LEGORACERS 0x0043e620
void RaceState::Racer::Field0x018::FUN_0043e620()
{
	STUB(0x0043e620);
}

// FUNCTION: LEGORACERS 0x0043fa50
void RaceState::Racer::Field0x018::FUN_0043fa50(GolCamera* p_camera)
{
	LegoU32 flags = m_unk0x000;
	if ((flags & c_flags0x000Bit4) || !(flags & c_flags0x000Bit2)) {
		return;
	}

	GolVec3 entityPosition;
	m_unk0x044->VTable0x04(&entityPosition);

	GolVec3 cameraPosition;
	p_camera->GetTransform()->GetPosition(&cameraPosition);

	LegoFloat deltaX = entityPosition.m_x - cameraPosition.m_x;
	LegoFloat deltaY = entityPosition.m_y - cameraPosition.m_y;
	LegoFloat deltaZ = entityPosition.m_z - cameraPosition.m_z;
	LegoFloat distanceSquared = deltaZ * deltaZ + deltaY * deltaY + deltaX * deltaX;
	if (distanceSquared < m_unk0x044->GetModelDistance(0)) {
		m_unk0x000 |= c_flags0x000Bit4;

		GolVec3 up;
		m_unk0x044->GetUnk0x34(&up);

		GolVec3 center;
		m_unk0x044->FUN_100286d0(&center);

		LegoFloat scale = m_unk0x044->GetUnk0x58();
		if (scale != 1.0f) {
			m_unk0x07c.m_unk0x104 = m_unk0x198 * scale;
			m_unk0x07c.m_unk0x108 = scale * m_unk0x19c;
		}
		else {
			m_unk0x07c.m_unk0x104 = m_unk0x198 * 1.0f;
			m_unk0x07c.m_unk0x108 = m_unk0x19c * 1.0f;
		}

		m_unk0x07c.m_unk0x10c = g_unk0x004b0af0;
		center.m_z += g_unk0x004b0af4;

		RaceSessionField0x27d4::Item::Field0x004* field = &m_unk0x07c;
		field->m_unk0x0e8.m_x = center.m_x;
		field->m_unk0x0e8.m_y = center.m_y;
		field->m_unk0x0e8.m_z = center.m_z;

		up.m_x = -up.m_x;
		up.m_y = -up.m_y;
		MaterialTable0x0c* materialTable = &m_unk0x218;
		GolVec3* upVector = &up;
		GolVec3* vector = &m_unk0x058;
		m_unk0x07c.GetUnk0x010().SetPrimaryMaterialTable(materialTable);
		up.m_z = -up.m_z;
		field->FUN_00414c90(vector, upVector);
		field->FUN_00414a30(m_unk0x064);
	}
}

// STUB: LEGORACERS 0x0043fc20
void RaceState::Racer::Field0x018::FUN_0043fc20(GolD3DRenderDevice* p_renderer)
{
	if (m_unk0x000 & c_flags0x000Bit4) {
		GolVec3 cameraPosition;
		p_renderer->GetUnk0x0c()->GetTransform()->GetPosition(&cameraPosition);

		GolVec3 position;
		LegoFloat deltaX = m_unk0x07c.m_unk0x0e8.m_x;
		RaceSessionField0x27d4::Item::Field0x004* field = &m_unk0x07c;
		position.m_y = m_unk0x07c.m_unk0x0e8.m_y;
		position.m_z = field->m_unk0x0e8.m_z;

		deltaX = cameraPosition.m_x - deltaX;
		LegoFloat deltaY = cameraPosition.m_y - position.m_y;
		LegoFloat deltaZ = cameraPosition.m_z - position.m_z;
		LegoFloat distanceSquared = deltaZ * deltaZ + deltaY * deltaY + deltaX * deltaX;

		LegoS32 alpha;
		if (distanceSquared <= g_unk0x004b0b38) {
			alpha = c_fadeAlphaMax;
		}
		else if (distanceSquared < g_unk0x004b0b3c) {
			alpha = c_fadeAlphaMax -
					static_cast<LegoS32>(
						((distanceSquared - g_unk0x004b0b38) / (g_unk0x004b0b3c - g_unk0x004b0b38)) * g_unk0x004b0b4c
					);
		}
		else {
			alpha = 0;
		}

		if (alpha) {
			p_renderer->SetAlphaOverride(alpha, c_alphaOverrideFlag);
			field->FUN_00415a40(p_renderer);
			p_renderer->ClearAlphaOverride();
		}
	}

	if (m_racer->m_unk0xd04 & c_racerFlags0xd04Bit11) {
		p_renderer->VTable0x94(&m_unk0x284);
	}
}

// FUNCTION: LEGORACERS 0x0043fd70
void RaceState::Racer::Field0x018::FUN_0043fd70()
{
	FUN_0043dcd0();
	FUN_0043da30();
}

// STUB: LEGORACERS 0x0043fdb0
void RaceState::Racer::Field0x018::FUN_0043fdb0()
{
	m_unk0x000 &= ~c_flags0x000Bit8;
	FUN_0043dcd0();
}

// FUNCTION: LEGORACERS 0x00440030
void RaceState::Racer::Field0x018::FUN_00440030()
{
	m_unk0x004.FUN_00411e30(4);

	if (m_unk0x03c && !(m_unk0x000 & c_flags0x000Bit11)) {
		m_unk0x004.FUN_00411ec0(m_unk0x03c);
	}

	if (m_unk0x040 && !(m_unk0x000 & c_flags0x000Bit11)) {
		m_unk0x004.FUN_00411ec0(m_unk0x040);
	}

	if (m_unk0x044 && !(m_unk0x000 & c_flags0x000Bit10)) {
		m_unk0x004.FUN_00411ec0(m_unk0x044);
	}

	if (m_unk0x048 && !(m_unk0x000 & c_flags0x000Bit12)) {
		m_unk0x004.FUN_00411ec0(m_unk0x048);
	}
}

// FUNCTION: LEGORACERS 0x004400a0
void RaceState::Racer::Field0x018::FUN_004400a0(ColorTransform0x20* p_unk0x04)
{
	m_unk0x3a0 = *p_unk0x04;

	LegoU32 unk0x3c4 = m_unk0x3c4;
	m_unk0x3c0 = 1;

	if (!unk0x3c4) {
		m_unk0x004.VTable0x24(&m_unk0x3a0);
	}
}

// FUNCTION: LEGORACERS 0x004400e0
void RaceState::Racer::Field0x018::FUN_004400e0()
{
	LegoU32 unk0x3c4 = m_unk0x3c4;
	m_unk0x3c0 = 0;

	if (!unk0x3c4) {
		m_unk0x004.VTable0x28();
	}
}

// FUNCTION: LEGORACERS 0x00440100
void RaceState::Racer::Field0x018::FUN_00440100(ColorTransform0x20* p_unk0x04, undefined4 p_unk0x08)
{
	m_unk0x3c4 = 1;
	m_unk0x3c8 = p_unk0x08;
	m_unk0x004.VTable0x24(p_unk0x04);
}

// FUNCTION: LEGORACERS 0x00440130
void RaceState::Racer::Field0x018::FUN_00440130()
{
	LegoU32 unk0x3c0 = m_unk0x3c0;
	m_unk0x3c4 = 0;
	m_unk0x3c8 = 0;

	if (unk0x3c0) {
		m_unk0x004.VTable0x24(&m_unk0x3a0);
	}
	else {
		m_unk0x004.VTable0x28();
	}
}

// FUNCTION: LEGORACERS 0x00440160
void RaceState::Racer::Field0x018::FUN_00440160(LegoFloat p_unk0x04)
{
	m_unk0x044->SetUnk0x58AndInvalidateRadius(p_unk0x04);
	m_unk0x03c->SetUnk0x58AndInvalidateRadius(p_unk0x04);

	if (m_unk0x040) {
		m_unk0x040->SetUnk0x58AndInvalidateRadius(p_unk0x04);
	}

	m_unk0x048->SetUnk0x58AndInvalidateRadius(p_unk0x04);
}

// FUNCTION: LEGORACERS 0x004401a0
void RaceState::Racer::Field0x018::FUN_004401a0()
{
	m_unk0x048->FUN_0040dad0(9);
}
