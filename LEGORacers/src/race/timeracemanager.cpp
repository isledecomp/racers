#include "race/timeracemanager.h"

#include "core/gol.h"

DECOMP_SIZE_ASSERT(TimeRaceManager, 0x3b8)

// FUNCTION: LEGORACERS 0x00422350
TimeRaceManager::TimeRaceManager()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004223b0
TimeRaceManager::~TimeRaceManager()
{
	Shutdown();
}

// STUB: LEGORACERS 0x004223c0
void TimeRaceManager::Reset()
{
	// TODO
	STUB(0x4223c0);
}

// STUB: LEGORACERS 0x00422420
void TimeRaceManager::Initialize(GolD3DRenderDevice*, GolExport*, undefined4, undefined4)
{
	// TODO
	STUB(0x422420);
}

// FUNCTION: LEGORACERS 0x00422670
void TimeRaceManager::Shutdown()
{
	m_unk0x20c.VTable0x54();
	m_unk0x114.VTable0x54();
	m_unk0x1c.VTable0x54();
	m_unk0x300.VTable0x54();

	if (m_worldDatabase) {
		m_golExport->VTable0x3c(m_worldDatabase);
		m_worldDatabase = NULL;
	}
	if (m_recordLapTimes) {
		delete[] m_recordLapTimes;
		m_recordLapTimes = NULL;
	}
	if (m_bestLapTimes) {
		delete[] m_bestLapTimes;
		m_bestLapTimes = NULL;
	}
	if (m_scratchLapTimes) {
		delete[] m_scratchLapTimes;
		m_scratchLapTimes = NULL;
	}

	Reset();
}

// FUNCTION: LEGORACERS 0x004230e0
void TimeRaceManager::UpdateBestRun()
{
	LegoU32 i;
	LegoU32 bestSum = 0;
	LegoU32 latestSum = 0;

	for (i = 0; i < 3; i++) {
		m_scratchLapTimes[i] = m_racer->m_lapTimes[i];
	}

	for (i = 0; i < 3; i++) {
		bestSum += m_bestLapTimes[i];
		latestSum += m_scratchLapTimes[i];
	}

	if (latestSum < bestSum || bestSum == 0) {
		LegoU32* previousBest = m_bestLapTimes;
		m_bestLapTimes = m_scratchLapTimes;
		m_scratchLapTimes = previousBest;
	}

	m_flags0x3b4 = (m_flags0x3b4 & 0xfc) | c_flag0x3b4Bit4;

	m_racer = NULL;
}

// FUNCTION: LEGORACERS 0x004234b0
LegoBool32 TimeRaceManager::HasBeatenRecord()
{
	LegoU8 flags = m_flags0x3b4;
	if (!(flags & (c_flag0x3b4Bit0 | c_flag0x3b4Bit4))) {
		return FALSE;
	}
	if (!(flags & c_flag0x3b4Bit3)) {
		return FALSE;
	}

	LegoU32 recordSum = 0;
	LegoU32 bestSum = 0;

	for (LegoU32 i = 0; i < 3; i++) {
		recordSum += m_recordLapTimes[i];
		bestSum += m_bestLapTimes[i];
	}

	return bestSum < recordSum;
}
