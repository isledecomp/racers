#include "race/timeracemanager.h"

#include "core/gol.h"
#include "golerror.h"
#include "world/golworlddatabase.h"

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

// FUNCTION: LEGORACERS 0x004223c0
void TimeRaceManager::Reset()
{
	m_worldDatabase = NULL;
	m_golExport = NULL;
	m_racer = NULL;
	m_unk0x110 = NULL;
	m_unk0x390 = NULL;
	m_unk0x208 = NULL;
	m_recordLapTimes = NULL;
	m_bestLapTimes = NULL;
	m_scratchLapTimes = NULL;
	m_unk0x3b0 = 0;
	m_flags0x3b4 = 0;
	m_unk0x394 = 0;
	m_unk0x398 = 0;
	m_unk0x39c = 0;
	m_unk0x3a0.m_x = 0.0f;
	m_unk0x3a0.m_y = 0.0f;
	m_unk0x3a0.m_z = 0.0f;
}

// FUNCTION: LEGORACERS 0x00422420
void TimeRaceManager::Initialize(
	GolD3DRenderDevice* p_renderer,
	GolExport* p_golExport,
	LegoBool32 p_binary,
	LegoBool32 p_mirror
)
{
	if (m_scratchLapTimes != NULL) {
		Shutdown();
	}

	m_golExport = p_golExport;
	m_scratchLapTimes = new LegoU32[c_lapTimeCapacity];
	if (m_scratchLapTimes == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_bestLapTimes = new LegoU32[c_lapTimeCapacity];
	if (m_bestLapTimes == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_recordLapTimes = new LegoU32[c_lapTimeCapacity];
	if (m_recordLapTimes == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < c_lapCount; i++) {
		m_scratchLapTimes[i] = 0;
		m_bestLapTimes[i] = 0;
		m_recordLapTimes[i] = 0;
	}

	m_scratchLapTimes[c_recordLapTimeBaseIndex] = 0;
	m_scratchLapTimes[c_recordLapTimeBaseIndex + 1] = 0;
	m_scratchLapTimes[c_lapTimeCapacity - 1] = 0;
	m_scratchLapTimes[c_recordLapTimeBaseIndex + 2] = 0;
	m_scratchLapTimes[c_recordLapTimeBaseIndex + 3] = 0;
	m_scratchLapTimes[c_recordLapTimeBaseIndex + 4] = 0;
	m_scratchLapTimes[c_recordLapTimeBaseIndex + 5] = 0;
	m_scratchLapTimes[c_recordLapTimeBaseIndex + 6] = 0;
	m_scratchLapTimes[c_recordLapTimeBaseIndex + 7] = 0;
	m_scratchLapTimes[c_recordLapTimeBaseIndex + 8] = 0;

	m_bestLapTimes[c_recordLapTimeBaseIndex] = 0;
	m_bestLapTimes[c_recordLapTimeBaseIndex + 1] = 0;
	m_bestLapTimes[c_lapTimeCapacity - 1] = 0;
	m_bestLapTimes[c_recordLapTimeBaseIndex + 2] = 0;
	m_bestLapTimes[c_recordLapTimeBaseIndex + 3] = 0;
	m_bestLapTimes[c_recordLapTimeBaseIndex + 4] = 0;
	m_bestLapTimes[c_recordLapTimeBaseIndex + 5] = 0;
	m_bestLapTimes[c_recordLapTimeBaseIndex + 6] = 0;
	m_bestLapTimes[c_recordLapTimeBaseIndex + 7] = 0;
	m_bestLapTimes[c_recordLapTimeBaseIndex + 8] = 0;

	m_recordLapTimes[c_recordLapTimeBaseIndex] = 0;
	m_recordLapTimes[c_recordLapTimeBaseIndex + 1] = 0;
	m_recordLapTimes[c_lapTimeCapacity - 1] = 0;
	m_recordLapTimes[c_recordLapTimeBaseIndex + 2] = 0;
	m_recordLapTimes[c_recordLapTimeBaseIndex + 3] = 0;
	m_recordLapTimes[c_recordLapTimeBaseIndex + 4] = 0;
	m_recordLapTimes[c_recordLapTimeBaseIndex + 5] = 0;
	m_recordLapTimes[c_recordLapTimeBaseIndex + 6] = 0;
	m_recordLapTimes[c_recordLapTimeBaseIndex + 7] = 0;
	m_recordLapTimes[c_recordLapTimeBaseIndex + 8] = 0;

	m_worldDatabase = m_golExport->VTable0x08();
	m_worldDatabase->VTable0x14(p_renderer, "ghost", p_binary, 1.0f);

	m_unk0x110 = m_worldDatabase->GetUnk0xa0();
	m_unk0x208 = m_worldDatabase->GetUnk0xa0() + 1;
	m_unk0x390 = m_worldDatabase->GetUnk0x9c();
	m_unk0x208->FUN_0040dad0(12);

	m_unk0x3a0.m_x = -2.131681f;
	m_unk0x3a0.m_y = 0.01123f;
	m_unk0x3a0.m_z = 1.608f;

	if (p_binary) {
		m_flags0x3b4 |= c_flag0x3b4Bit2;
	}

	if (p_mirror) {
		m_flags0x3b4 |= c_flag0x3b4Bit5;
	}

	m_unk0x3ac = 0;
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
