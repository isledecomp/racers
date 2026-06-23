#include "audio/soundnode.h"
#include "audio/spatialsoundinstance.h"
#include "camera/golcamera.h"
#include "cmbmodelpart0x34.h"
#include "duskwindbananarelic0x24.h"
#include "golbinparser.h"
#include "golerror.h"
#include "golmateriallibrary.h"
#include "material/goltexturelist.h"
#include "menu/runtime/cutsceneparticle.h"
#include "menu/runtime/cutsceneplayer.h"
#include "race/cobalttrail0x140.h"
#include "race/racecameracontroller.h"
#include "race/raceeventtable0x90.h"
#include "race/raceforcefeedback.h"
#include "race/racesession.h"
#include "race/timeracemanager.h"
#include "render/gold3drenderdevice.h"
#include "surface/purpledune0x7c.h"
#include "util/racerbillboardrenderstate0x33c.h"

#include <float.h>
#include <math.h>
#include <string.h>

extern LegoU16 g_unk0x004befec[1024];
extern LegoU32 g_unk0x004c6ee4;
extern LegoFloat g_carBuildPreviewMouseScale;
extern const LegoFloat g_carBuildModelTextureCoordinateScale;
extern LegoFloat g_minSoundPan;

DECOMP_SIZE_ASSERT(RaceState, 0x320)
DECOMP_SIZE_ASSERT(RaceState::Racer, 0xe34)
DECOMP_SIZE_ASSERT(RaceEventRecord, 0x20)
DECOMP_SIZE_ASSERT(RaceEventRecord::Target, 0x5c)
DECOMP_SIZE_ASSERT(RaceState::RacerProgressEntry, 0x0c)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x36df0Params, 0x88)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x371c0, 0x30)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x371c0Vehicle, 0x88)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x018, 0x3d0)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x018::InitParams, 0x68)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x018::Field0x1dc, 0x6c4)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x018::Field0x1dc::Field0x1a4, 0x70)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x3e8Base0xd0, 0xd0)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x3e8Base0xe4, 0xe4)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x3e8Base0x74c, 0x74c)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x3e8, 0x888)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0xc70, 0x54)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0xd8c, 0x30)
DECOMP_SIZE_ASSERT(RaceState::Field0x0f0, 0x194)
DECOMP_SIZE_ASSERT(RaceState::Field0x284, 0x1c)

extern const LegoFloat g_ghostAnimationRateScale;
extern const LegoFloat g_ghostSampleFractionScale;
extern const LegoFloat g_item0x40RadiansToTableIndex;
extern const LegoFloat g_negativeRadiansToTableIndex;
extern const LegoFloat g_violetShoalTwo;
extern LegoU32 g_unk0x004bef68;
extern LegoU32 g_unk0x004bef6c;
extern LegoFloat g_cosineTable[1024];

// GLOBAL: LEGORACERS 0x004b02e0
extern const LegoFloat g_unk0x004b02e0 = 0.2f;

// GLOBAL: LEGORACERS 0x004b0424
static const LegoFloat g_unk0x004b0424 = 100.0f;

// GLOBAL: LEGORACERS 0x004b0544
extern const LegoFloat g_unk0x004b0544 = 0.050000001f;

// GLOBAL: LEGORACERS 0x004b094c
extern const LegoFloat g_unk0x004b094c = 0.40000001f;

// GLOBAL: LEGORACERS 0x004b0950
extern const LegoFloat g_unk0x004b0950 = 0.1f;

// GLOBAL: LEGORACERS 0x004b0954
extern const LegoFloat g_unk0x004b0954 = 0.17f;

// GLOBAL: LEGORACERS 0x004b0958
extern const LegoFloat g_unk0x004b0958 = 30.0f;

// GLOBAL: LEGORACERS 0x004b095c
extern const LegoFloat g_unk0x004b095c = 300.0f;

// GLOBAL: LEGORACERS 0x004b0960
extern const LegoFloat g_unk0x004b0960 = 200.0f;

// GLOBAL: LEGORACERS 0x004b0964
extern const LegoFloat g_unk0x004b0964 = 600.0f;

// GLOBAL: LEGORACERS 0x004b0970
extern const LegoFloat g_unk0x004b0970 = 0.75f;

// GLOBAL: LEGORACERS 0x004b0988
extern const LegoFloat g_unk0x004b0988 = 0.015f;

// GLOBAL: LEGORACERS 0x004b098c
extern const LegoFloat g_unk0x004b098c = 0.69999999f;

// GLOBAL: LEGORACERS 0x004b0990
extern const LegoFloat g_unk0x004b0990 = 0.5f;

// GLOBAL: LEGORACERS 0x004b0994
extern const LegoFloat g_unk0x004b0994 = 2.2439947f;

// GLOBAL: LEGORACERS 0x004b0998
extern const LegoFloat g_unk0x004b0998 = 0.059999999f;

// GLOBAL: LEGORACERS 0x004b099c
extern const LegoFloat g_unk0x004b099c = 0.030000029f;

// GLOBAL: LEGORACERS 0x004b09a0
extern const LegoFloat g_unk0x004b09a0 = 0.0099999998f;

// GLOBAL: LEGORACERS 0x004b09a4
extern const LegoFloat g_unk0x004b09a4 = 1.0f;

// GLOBAL: LEGORACERS 0x004b0974
extern const LegoFloat g_unk0x004b0974 = 100.0f;

// GLOBAL: LEGORACERS 0x004b0978
extern const LegoFloat g_unk0x004b0978 = 62500.0f;

// GLOBAL: LEGORACERS 0x004b097c
extern const LegoFloat g_unk0x004b097c = 0.95999998f;

// GLOBAL: LEGORACERS 0x004b0980
extern const LegoFloat g_unk0x004b0980 = 0.69999999f;

// GLOBAL: LEGORACERS 0x004b0984
extern const LegoFloat g_unk0x004b0984 = 0.2f;

// GLOBAL: LEGORACERS 0x004b09a8
extern const LegoFloat g_unk0x004b09a8 = 3.5f;

// GLOBAL: LEGORACERS 0x004b09ac
static const LegoFloat g_unk0x004b09ac = 0.0111111114f;

// GLOBAL: LEGORACERS 0x004b09b8
extern const LegoFloat g_unk0x004b09b8 = 30.0f;

// GLOBAL: LEGORACERS 0x004b09bc
extern const LegoFloat g_unk0x004b09bc = 0.001953125f;

// GLOBAL: LEGORACERS 0x004b09d0
extern const LegoFloat g_unk0x004b09d0 = 1.5f;

// GLOBAL: LEGORACERS 0x004b09d4
extern const LegoFloat g_unk0x004b09d4 = 200.0f;

// GLOBAL: LEGORACERS 0x004b09dc
extern const LegoFloat g_unk0x004b09dc = 0.050000001f;

// GLOBAL: LEGORACERS 0x004b0a08
extern const LegoFloat g_unk0x004b0a08 = 0.40000001f;

// GLOBAL: LEGORACERS 0x004b0a0c
extern const LegoFloat g_unk0x004b0a0c = 0.1f;

// GLOBAL: LEGORACERS 0x004b0a10
extern const LegoFloat g_unk0x004b0a10 = 0.17f;

// GLOBAL: LEGORACERS 0x004b0a14
extern const LegoFloat g_unk0x004b0a14 = 250000.0f;

// GLOBAL: LEGORACERS 0x004b0a18
extern const LegoFloat g_unk0x004b0a18 = 30.0f;

// GLOBAL: LEGORACERS 0x004b0a1c
extern const LegoFloat g_unk0x004b0a1c = 2.0f;

// GLOBAL: LEGORACERS 0x004b0a20
extern const LegoFloat g_unk0x004b0a20 = 200.0f;

// GLOBAL: LEGORACERS 0x004b0ac0
extern const LegoFloat g_unk0x004b0ac0 = -1.0f;

// GLOBAL: LEGORACERS 0x004b0af0
extern const LegoFloat g_unk0x004b0af0 = 15.0f;

// GLOBAL: LEGORACERS 0x004b0af4
extern const LegoFloat g_unk0x004b0af4 = 6.0f;

// GLOBAL: LEGORACERS 0x004b0b24
extern const LegoFloat g_unk0x004b0b24 = 40000.0f;

// GLOBAL: LEGORACERS 0x004b0b28
extern const LegoFloat g_unk0x004b0b28 = 30.0f;

// GLOBAL: LEGORACERS 0x004b0b2c
extern const LegoFloat g_unk0x004b0b2c = 100.0f;

// GLOBAL: LEGORACERS 0x004b0b30
extern const LegoFloat g_unk0x004b0b30 = 0.0099999998f;

// GLOBAL: LEGORACERS 0x004b0b34
extern const LegoFloat g_unk0x004b0b34 = 0.029999999f;

// GLOBAL: LEGORACERS 0x004b0b38
extern const LegoFloat g_unk0x004b0b38 = 2500.0f;

// GLOBAL: LEGORACERS 0x004b0b3c
extern const LegoFloat g_unk0x004b0b3c = 10000.0f;

// GLOBAL: LEGORACERS 0x004b0b40
extern const LegoFloat g_unk0x004b0b40 = -0.60000002f;

// GLOBAL: LEGORACERS 0x004b0b44
extern const LegoFloat g_unk0x004b0b44 = -0.2f;

// GLOBAL: LEGORACERS 0x004b0b4c
extern const LegoFloat g_unk0x004b0b4c = 191.0f;

extern const LegoFloat g_twoPi;
extern const LegoFloat g_unk0x004b4bc8;

// GLOBAL: LEGORACERS 0x004c67a4
LegoFloat g_unk0x004c67a4 = (1.0f - g_unk0x004b0984) * g_unk0x004b0424 * g_unk0x004b09ac;

// GLOBAL: LEGORACERS 0x004c67a8
LegoFloat g_unk0x004c67a8 = g_unk0x004b0a20 * g_unk0x004b0a20;

// GLOBAL: LEGORACERS 0x004c67ac
undefined4 g_unk0x004c67ac;

// GLOBAL: LEGORACERS 0x004c67b0
RaceState::RacerProgressEntry RaceState::g_racerProgressEntries[RaceState::c_racerProgressEntryCount];

// GLOBAL: LEGORACERS 0x004bef3c
const LegoChar* g_unk0x004bef3c[3] = {"drivers", "champs", "chassis"};

// GLOBAL: LEGORACERS 0x004bef70
extern LegoU32 g_unk0x004bef70 = 3;

// GLOBAL: LEGORACERS 0x004c6b34
LegoFloat g_unk0x004c6b34 = g_twoPi * g_unk0x004b4bc8;

// FUNCTION: LEGORACERS 0x00436990
RaceState::Racer::Racer()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00436a20
RaceState::Racer::~Racer()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00436aa0
void RaceState::Racer::Destroy()
{
	if (m_unk0xd98) {
		m_unk0x004->FUN_00443c10(m_unk0xd98);
		m_unk0xd98 = NULL;
	}

	if (m_unk0xd94) {
		m_unk0x004->FUN_00443c10(m_unk0xd94);
		m_unk0xd94 = NULL;
	}

	if (m_unk0xd90) {
		m_unk0x004->FUN_00443c10(m_unk0xd90);
		m_unk0xd90 = NULL;
	}

	if (m_unk0xd8c) {
		m_unk0x004->FUN_00443c10(m_unk0xd8c);
		m_unk0xd8c = NULL;
	}

	if (m_unk0xd9c) {
		m_unk0x004->FUN_00443c10(m_soundD9c);
		m_unk0xd9c = NULL;
	}

	if (m_unk0xda0) {
		m_unk0x004->FUN_00443c10(m_soundDa0);
		m_unk0xda0 = NULL;
	}

	if (m_unk0xda4) {
		m_unk0x004->FUN_00443c10(m_soundDa4);
		m_unk0xda4 = NULL;
	}

	if (m_unk0xda8) {
		m_unk0x004->FUN_00443c10(m_soundDa8);
		m_unk0xda8 = NULL;
	}

	if (m_unk0xdac) {
		m_unk0x004->FUN_00443c10(m_unk0xdac);
		m_unk0xdac = NULL;
	}

	m_displayName.Reset();
	m_unk0x018.Destroy();
	m_unk0x3e8.Destroy();
	m_unk0xc70.Destroy();
	Reset();
}

// FUNCTION: LEGORACERS 0x00436bd0
void RaceState::Racer::Reset()
{
	m_unk0x004 = NULL;
	m_unk0xd0c = 0;
	m_unk0xd10 = 2;
	m_unk0xd14 = 1;
	m_unk0xcd8 = 0;
	m_unk0x00c = NULL;

	LegoU32 lapTime;
	m_lapsCompleted = 0;
	lapTime = 0;
	m_unk0xce8 = 0xffffffff;
	m_lapTimes[0] = lapTime;
	m_lapTimes[1] = lapTime;
	m_lapTimes[2] = lapTime;
	m_lapTimes[3] = lapTime;
	m_lapTimes[4] = lapTime;
	m_unk0xccc = 0;
	m_unk0xd04 = 0;
	m_unk0xd08 = 2;
	m_unk0xcdc = 150;
	m_unk0xd38 = 0;
	m_unk0xd34 = 0;
	m_unk0xd44 = 0;
	m_unk0xd4c = 0;
	m_unk0xd50 = 0;
	m_unk0xd40 = 1000;
	m_unk0xd3c = 0;
	m_unk0xd54 = 1.0f;
	m_unk0xd68 = 0;
	m_unk0xd6c = 0;
	m_unk0xd70 = 0;
	m_unk0xd8c = NULL;
	m_unk0xd90 = NULL;
	m_unk0xd94 = NULL;
	m_unk0xd98 = NULL;
	m_unk0xd9c = NULL;
	m_unk0xda0 = NULL;
	m_unk0xda4 = NULL;
	m_unk0xda8 = NULL;
	m_unk0xdac = NULL;
	m_unk0xd24 = 0;
	m_unk0xd28 = 0;
	m_unk0xd2c = 0;
	m_unk0xd30 = 0;
	m_unk0xd74 = 0;
	m_unk0xd7c = 0;
	m_unk0xd84 = 0;
	m_unk0xd88 = 0;

	LegoU8 invalidIndex = 0xff;
	m_unk0xd78 = 0;
	m_unk0xdf8.m_x = 0;
	m_unk0xd1c = invalidIndex;
	m_unk0xd1d = invalidIndex;
	m_unk0xd1e = invalidIndex;
	m_unk0xd1f = invalidIndex;
	m_unk0xd20 = invalidIndex;
	m_unk0xd21 = invalidIndex;
	m_unk0xdf8.m_y = 0;

	Field0xd5c* field0xd5c = NULL;
	m_unk0xdf8.m_z = 0;
	m_unk0xd22 = 0;
	m_unk0xe08.m_x = 0;
	m_unk0xe08.m_y = 0;
	m_unk0xe08.m_z = 0;
	m_unk0xe08.m_velocity.m_x = 0;
	m_unk0xe08.m_velocity.m_y = 0;
	m_unk0xe08.m_velocity.m_z = 0;
	m_unk0xe08.m_right.m_x = 0;
	m_unk0xe08.m_right.m_y = 0;
	m_unk0xe08.m_right.m_z = 0;
	m_unk0xcc4 = 0;
	m_unk0xcc8 = 1;
	m_unk0x010 = 0;
	m_unk0xe30 = NULL;
	m_unk0xd18 = 0xffffffff;
	m_unk0xdb0 = 0;
	m_unk0xd58 = 0;
	m_unk0xd5c[0] = field0xd5c;
	m_unk0xd5c[1] = field0xd5c;
	m_unk0xd5c[2] = field0xd5c;
	m_unk0xdb4 = NULL;
	m_unk0xdb8 = 0;
	m_unk0x014 = 0;
	m_unk0xdbc = 0;
	m_unk0xcd0 = 0;
	m_unk0xcd4 = 0;
	m_unk0xce0 = 0;
	m_unk0xd48 = 0;
}

// FUNCTION: LEGORACERS 0x00436df0
void RaceState::Racer::FUN_00436df0(
	RaceState::Field0x3b190Params0x08* p_context,
	Field0x018::InitParams* p_field0x018Params,
	Field0x36df0Params* p_params,
	RaceState* p_raceState,
	LegoU32 p_racerIndex
)
{
	if (m_unk0x00c) {
		Destroy();
	}

	m_unk0xe04 = p_racerIndex;
	m_unk0xe2c = p_context->m_unk0x34;
	m_resourceManager004 = p_context->m_resourceMgr;
	m_unk0x008 = p_context->m_unk0x18;
	m_unk0x010 = p_context->m_racerField0x010;
	m_raceState00c = p_raceState;
	m_lapTimes[5] = p_racerIndex + 1;
	m_unk0xd54 = p_params->m_unk0x78;
	m_unk0xcd0 = p_params->m_unk0x7c;
	m_unk0xcd4 = p_params->m_unk0x80;
	m_unk0xce0 = p_params->m_unk0x72;

	if (p_params->m_stringChars) {
		m_displayName.CopyFromBufSelection(p_params->m_stringChars, 0);
	}
	else {
		GolString::CopyStringToBuf16(p_params->m_displayName, &m_unk0xdbc);
		m_displayName.CopyFromBufSelection(&m_unk0xdbc, 0);
	}

	LegoU32 soundBase = p_params->m_unk0x74;
	m_unk0xd40 = soundBase;
	if (soundBase == 1000) {
		m_unk0xd23 = 26;
	}
	else if (soundBase == 1100) {
		m_unk0xd23 = 28;
	}
	else if (soundBase == 1112) {
		m_unk0xd23 = 27;
	}
	else if (soundBase == 1124) {
		m_unk0xd23 = 29;
	}
	else if (soundBase == 1136) {
		m_unk0xd23 = 30;
	}
	else if (soundBase == 1148 || soundBase == 1160) {
		m_unk0xd23 = 31;
	}

	LegoU32 colorValue = p_params->m_unk0x6c[0];
	LegoFloat colorScale = static_cast<LegoFloat>(colorValue);
	colorScale *= g_unk0x004c67a4;
	colorScale *= g_carBuildPreviewMouseScale;
	colorScale += g_unk0x004b0984;
	if (colorScale > 1.0f) {
		colorScale = 1.0f;
	}
	m_unk0xd1c = static_cast<LegoU8>(colorScale * 255.0f);

	colorValue = p_params->m_unk0x6c[1];
	colorScale = static_cast<LegoFloat>(colorValue);
	colorScale *= g_unk0x004c67a4;
	colorScale *= g_carBuildPreviewMouseScale;
	colorScale += g_unk0x004b0984;
	if (colorScale > 1.0f) {
		colorScale = 1.0f;
	}
	m_unk0xd1d = static_cast<LegoU8>(colorScale * 255.0f);

	colorValue = p_params->m_unk0x6c[2];
	colorScale = static_cast<LegoFloat>(colorValue);
	colorScale *= g_unk0x004c67a4;
	colorScale *= g_carBuildPreviewMouseScale;
	colorScale += g_unk0x004b0984;
	if (colorScale > 1.0f) {
		colorScale = 1.0f;
	}
	m_unk0xd1e = static_cast<LegoU8>(colorScale * 255.0f);

	colorValue = p_params->m_unk0x6c[3];
	colorScale = static_cast<LegoFloat>(colorValue);
	colorScale *= g_unk0x004c67a4;
	colorScale *= g_carBuildPreviewMouseScale;
	colorScale += g_unk0x004b0984;
	if (colorScale > 1.0f) {
		colorScale = 1.0f;
	}
	m_unk0xd1f = static_cast<LegoU8>(colorScale * 255.0f);

	colorValue = p_params->m_unk0x6c[4];
	colorScale = static_cast<LegoFloat>(colorValue);
	colorScale *= g_unk0x004c67a4;
	colorScale *= g_carBuildPreviewMouseScale;
	colorScale += g_unk0x004b0984;
	if (colorScale > 1.0f) {
		colorScale = 1.0f;
	}
	m_unk0xd20 = static_cast<LegoU8>(colorScale * 255.0f);

	colorValue = p_params->m_unk0x6c[5];
	colorScale = static_cast<LegoFloat>(colorValue);
	colorScale *= g_unk0x004c67a4;
	colorScale *= g_carBuildPreviewMouseScale;
	colorScale += g_unk0x004b0984;
	if (colorScale > 1.0f) {
		colorScale = 1.0f;
	}
	m_unk0xd21 = static_cast<LegoU8>(colorScale * 255.0f);

	LegoS32 unk0xd22 = m_unk0xd1f;
	unk0xd22 = m_unk0xd1d - unk0xd22;
	unk0xd22 -= m_unk0xd1e;
	unk0xd22 += m_unk0xd1c;
	if (unk0xd22 < 0) {
		m_unk0xd22 = 0;
	}
	else {
		LegoFloat d22Scale = static_cast<LegoFloat>(unk0xd22);
		d22Scale *= g_unk0x004b09bc;
		d22Scale *= g_unk0x004b09b8;
		m_unk0xd22 = static_cast<LegoU8>(d22Scale);
	}

	LegoU32 randomIndex = g_unk0x004c6ee4;
	randomIndex++;
	randomIndex &= c_randomTableMask;
	g_unk0x004c6ee4 = randomIndex;
	LegoU32 randomValue = g_unk0x004befec[randomIndex];
	m_unk0xd34 = randomValue * 8 + 2000;

	randomIndex = g_unk0x004c6ee4;
	randomIndex++;
	randomIndex &= c_randomTableMask;
	g_unk0x004c6ee4 = randomIndex;
	randomValue = g_unk0x004befec[randomIndex];
	m_unk0xd44 = randomValue * 4 + 5000;

	LegoU32 state = 2;
	m_unk0xd08 = state;
	if (p_context->m_flags0x3c & 1) {
		m_unk0xd04 |= c_flags0xd04Bit26;
	}
	if (p_context->m_flags0x3c & 0x40) {
		m_unk0xd04 |= c_flags0xd04Bit24;
	}
	if (p_context->m_flags0x3c & 0x80) {
		m_unk0xd04 |= c_flags0xd04Bit25;
	}
	if (p_context->m_flags0x3c & state) {
		m_unk0xd04 |= c_flags0xd04Bit27;
	}

	m_unk0x018.FUN_0043d7a0(p_field0x018Params, p_context);
	FUN_004371c0(&p_context->m_field0x371c0, &p_params->m_vehicle);
	FUN_004374c0();
}

// FUNCTION: LEGORACERS 0x004371c0
void RaceState::Racer::FUN_004371c0(Field0x371c0* p_unk0x04, Field0x371c0Vehicle* p_unk0x08)
{
	RaceEventTable0x90* eventTable;
	undefined4 unk0x2c;
	GolBoundedEntity* unk0x0c;
	GolBoundedEntity* unk0x10;
	if (p_unk0x04) {
		eventTable = p_unk0x04->m_unk0x028;
		unk0x2c = p_unk0x04->m_unk0x02c;
		unk0x0c = p_unk0x04->m_unk0x00c;
		unk0x10 = p_unk0x04->m_unk0x010;
	}
	else {
		eventTable = m_unk0x3e8.m_unk0x6f4;
		unk0x2c = m_unk0x3e8.m_unk0x6f8;
		unk0x0c = m_unk0x3e8.m_unk0x140[0];
		unk0x10 = m_unk0x3e8.m_unk0x6fc;
	}

	GolVec3 position;
	GolVec3 vector;
	LegoFloat deltaX;
	LegoFloat deltaY;
	LegoFloat unk0x58;
	LegoU32 unk0x84;
	LegoU32 unk0x86;
	LegoU32 unk0x85;
	if (p_unk0x08) {
		deltaY = p_unk0x08->m_unk0x044 - p_unk0x08->m_unk0x038;
		unk0x58 = p_unk0x08->m_unk0x058;
		memcpy(&position, &p_unk0x08->m_unk0x04c, sizeof(position));

		deltaX = p_unk0x08->m_unk0x028.m_x - p_unk0x08->m_unk0x040;
		unk0x86 = p_unk0x08->m_unk0x086;
		LegoFloat valueFloat = p_unk0x08->m_unk0x05c;
		unk0x85 = p_unk0x08->m_unk0x085;
		memcpy(&vector, &p_unk0x08->m_unk0x028, sizeof(vector));
		valueFloat *= g_unk0x004b0544;

		LegoU32 value = static_cast<LegoU32>(valueFloat);
		unk0x84 = p_unk0x08->m_unk0x084 + value;
		if (unk0x84 > 100) {
			unk0x84 = 100;
		}

		unk0x86 += value;
		if (unk0x86 > 100) {
			unk0x86 = 100;
		}

		if (value > p_unk0x08->m_unk0x085) {
			unk0x85 = 0;
		}
		else {
			unk0x85 = p_unk0x08->m_unk0x085 - value;
		}
	}
	else {
		unk0x58 = m_unk0x3e8.m_unk0x0c8;
		unk0x84 = m_unk0x3e8.m_unk0x71c;
		memcpy(&position, &m_unk0x3e8.m_unk0x014, sizeof(position));
		unk0x86 = m_unk0x3e8.m_unk0x724;
		memcpy(&vector, &m_unk0x3e8.m_unk0x358, sizeof(vector));
		deltaY = m_unk0x3e8.m_unk0x364;
		deltaX = m_unk0x3e8.m_unk0x368;
		unk0x85 = m_unk0x3e8.m_unk0x720;
	}

	Field0x3e8* field0x3e8 = &m_unk0x3e8;
	field0x3e8->FUN_00429210(
		this,
		eventTable,
		unk0x2c,
		m_unk0x018.m_unk0x044,
		unk0x0c,
		unk0x10,
		m_unk0x004,
		unk0x58,
		8.0f,
		5.0f,
		6.2f
	);
	m_unk0x3e8.m_unk0x6ec = 0;
	m_unk0x3e8.m_racer = this;

	if (m_unk0xd04 & c_flags0xd04Bit26) {
		field0x3e8->m_flags0x6c0 |= Field0x3e8::c_flags0x6c0Bit20;
	}

	field0x3e8->FUN_0042ad70(unk0x84);
	field0x3e8->FUN_0042ada0(unk0x85);
	field0x3e8->FUN_0042add0(unk0x86);

	LegoFloat halfHeight = m_unk0x018.m_unk0x198;
	halfHeight *= 0.5f;
	LegoFloat halfWidth = m_unk0x018.m_unk0x19c;
	halfWidth *= 0.5f;
	field0x3e8->FUN_00441190(&position);
	field0x3e8->FUN_00446e60(&vector, deltaY, deltaX);

	GolVec3 corner;
	corner.m_x = halfWidth;
	corner.m_y = -halfHeight;
	corner.m_z = g_unk0x004b09a8;
	field0x3e8->FUN_00446ea0(0, &corner);

	corner.m_x = halfWidth;
	corner.m_y = halfHeight;
	corner.m_z = g_unk0x004b09a8;
	field0x3e8->FUN_00446ea0(1, &corner);

	corner.m_x = -halfWidth;
	corner.m_y = -halfHeight;
	corner.m_z = g_unk0x004b09a8;
	field0x3e8->FUN_00446ea0(2, &corner);

	corner.m_x = -halfWidth;
	corner.m_y = halfHeight;
	corner.m_z = g_unk0x004b09a8;
	field0x3e8->FUN_00446ea0(3, &corner);

	m_unk0xc70.FUN_0041fbd0(field0x3e8);
}

// FUNCTION: LEGORACERS 0x004374c0
void RaceState::Racer::FUN_004374c0()
{
	LegoU32 flags = m_unk0xd04;
	flags &= ~(c_flags0xd04Bit12 | c_flags0xd04Bit13 | c_flags0xd04Bit14);
	flags |= c_flags0xd04Bit1;
	m_unk0xd04 = flags;

	if (m_unk0xe2c) {
		m_unk0x3e8.FUN_0042a670(m_unk0xe2c);
		m_unk0x3e8.m_unk0x748 = 1;
	}

	LegoU32 invalidValue = 0xffffffff;
	m_unk0xcc4 = 0;
	m_unk0xd0c = 0;
	m_lapsCompleted = 0;
	m_unk0xd78 = 0;
	m_unk0xcc8 = 1;
	m_unk0xd10 = 2;
	m_unk0xd14 = 1;
	m_unk0xce8 = invalidValue;
	m_unk0xd18 = invalidValue;
}

// FUNCTION: LEGORACERS 0x00437540
void RaceState::Racer::FUN_00437540(RaceCameraController* p_cameraController, LegoBool32 p_state)
{
	m_unk0xd08 = p_state;
	m_unk0xdb4 = p_cameraController;

	m_soundD8c = m_unk0x004->FUN_00443bd0(0x2a);
	if (m_soundD8c) {
		m_soundD8c->SetDistanceRangeWithMinSquared(g_unk0x004b0958 * g_unk0x004b0958, g_unk0x004b095c);
	}

	m_soundD90 = m_unk0x004->FUN_00443bd0(0x2b);
	if (m_soundD90) {
		m_soundD90->SetDistanceRangeWithMinSquared(g_unk0x004b0958 * g_unk0x004b0958, g_unk0x004b095c);
	}

	m_soundD94 = m_unk0x004->FUN_00443bd0(0x2c);
	if (m_soundD94) {
		m_soundD94->SetDistanceRangeWithMinSquared(g_unk0x004b0958 * g_unk0x004b0958, g_unk0x004b095c);
	}

	m_soundD98 = m_unk0x004->FUN_00443bd0(0x2d);
	if (m_soundD98) {
		m_soundD98->SetDistanceRangeWithMinSquared(g_unk0x004b0958 * g_unk0x004b0958, g_unk0x004b095c);
	}

	m_unk0xd28 = 0.0f;
	m_unk0xd2c = 0.0f;
	m_unk0xd30 = 0.0f;

	m_unk0xd9c = m_unk0x004->FUN_00443bd0(0x20);
	m_unk0xd9c->VTable0x14(0xff);
	m_unk0xd9c->Play(TRUE);
	m_unk0xd9c->SetDistanceRangeWithMinSquared(g_unk0x004b0958 * g_unk0x004b0958, g_unk0x004b095c);
	m_unk0xd9c->SetVolume(m_unk0xd28);

	m_unk0xd24 = 0;
	m_unk0xda0 = m_unk0x004->FUN_00443bd0(0x0a);
	m_unk0xda0->SetDistanceRangeWithMinSquared(g_unk0x004b0958 * g_unk0x004b0958, g_unk0x004b095c);
	m_unk0xda0->VTable0x14(0xff);
	m_unk0xda0->SetVolume(m_unk0xd2c);

	m_unk0xda4 = m_unk0x004->FUN_00443bd0(0x3d);
	m_unk0xda4->SetDistanceRangeWithMinSquared(g_unk0x004b0958 * g_unk0x004b0958, g_unk0x004b095c);
	m_unk0xda4->VTable0x14(0xff);
	m_unk0xda4->SetVolume(m_unk0xd30);
}

// STUB: LEGORACERS 0x00437740
void RaceState::Racer::FUN_00437740(LegoU32 p_elapsedMs)
{
	LegoFloat value = m_unk0x3e8.m_unk0x618;
	Field0x018* field;

	if (value > -0.000099999997f && value < 0.000099999997f) {
		value = 0.0f;
		field = &m_unk0x018;
		field->FUN_004401b0();
	}
	else if (value >= 0.0f) {
		field = &m_unk0x018;
		field->FUN_004401b0();
	}
	else {
		field = &m_unk0x018;
		field->FUN_004401e0();
		value = -value;
	}

	LegoFloat speed = value * g_ghostAnimationRateScale;
	field->m_unk0x044->SetUnk0xb8(speed);

	if (field->m_unk0x040) {
		field->m_unk0x040->SetUnk0xb8(speed);
	}

	field->FUN_0043e070(p_elapsedMs);
}

// FUNCTION: LEGORACERS 0x004377f0
void RaceState::Racer::FUN_004377f0(LegoU32 p_elapsedMs)
{
	if (m_unk0xd04 & c_flags0xd04Bit1) {
		return;
	}

	LegoU32 lap = m_lapsCompleted;
	if (lap < m_unk0xce0) {
		m_lapTimes[lap] += p_elapsedMs;
	}

	LegoU32 countdown = m_unk0xcdc;
	m_unk0xcd8 += p_elapsedMs;
	if (m_unk0xcd8 > countdown) {
		m_unk0xcd8 = 0;
		m_unk0xcdc = 150;

		if (m_unk0xd08 == 2 && m_unk0xccc) {
			FUN_00438f20();
		}
	}

	if ((m_unk0x3e8.m_flags0x6c0 & c_flags0xaa8Bit7) && !m_unk0x3e8.m_unk0x744) {
		FUN_004397b0();
	}

	countdown = m_unk0xd34;
	if (p_elapsedMs > countdown) {
		m_unk0xd34 = 0;
	}
	else {
		m_unk0xd34 = countdown - p_elapsedMs;
	}

	countdown = m_unk0xd44;
	if (p_elapsedMs > countdown) {
		m_unk0xd44 = 0;
	}
	else {
		m_unk0xd44 = countdown - p_elapsedMs;
	}

	countdown = m_unk0xd4c;
	if (p_elapsedMs > countdown) {
		m_unk0xd4c = 0;
	}
	else {
		m_unk0xd4c = countdown - p_elapsedMs;
	}

	if (!m_unk0x3e8.m_unk0x36c) {
		m_unk0xd50 += p_elapsedMs;
	}
	else {
		m_unk0xd50 = 0;
	}

	countdown = m_unk0xd74;
	if (p_elapsedMs > countdown) {
		m_unk0xd74 = 0;
	}
	else {
		m_unk0xd74 = countdown - p_elapsedMs;
	}

	countdown = m_unk0xd7c;
	if (p_elapsedMs > countdown) {
		if (m_unk0xd04 & c_flags0xd04Bit11) {
			FUN_00439b00();
		}
	}
	else {
		m_unk0xd7c = countdown - p_elapsedMs;
	}

	countdown = m_unk0xd84;
	if (p_elapsedMs > countdown) {
		m_unk0xd84 = 0;
	}
	else {
		m_unk0xd84 = countdown - p_elapsedMs;
	}

	countdown = m_unk0xd48;
	if (p_elapsedMs < countdown && (m_unk0xd04 & c_flags0xd04Bit28)) {
		countdown -= p_elapsedMs;
		m_unk0xd48 = countdown;
		m_unk0x3e8.m_unk0x0dc =
			countdown > 500 ? static_cast<LegoFloat>(static_cast<LegoS32>(countdown - 500)) * g_ghostSampleFractionScale
							: 0.0f;
	}
	else {
		m_unk0xd48 = 0;
		m_unk0x3e8.m_unk0x0dc = 1.0f;
	}

	m_unk0xd04 &= ~c_flags0xd04Bit28;
	m_unk0x018.m_unk0x044->VTable0x04(&m_unk0xe08);
	m_unk0x018.m_unk0x044->GetOrientationRow0(&m_unk0xe08.m_right);
	GolVec3& velocity = m_unk0xe08.m_velocity;
	velocity = m_unk0x3e8.m_unk0x008;

	if (!m_unk0xd34 && m_unk0xd08 == 2) {
		if (m_unk0x00c->FUN_0043ca60(&m_unk0xe08, &m_unk0xe08.m_right, 0.0f, 169.0f, 0.30000001f)) {
			FUN_00439c90();
			g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
			m_unk0xd34 = g_unk0x004befec[g_unk0x004c6ee4] * 8 + 2000;
		}
		else {
			m_unk0xd34 = 2000;
		}
	}

	if (!m_unk0xd08) {
		FUN_00439cf0(p_elapsedMs);
		FUN_00439ea0(p_elapsedMs);
	}
	else {
		m_unk0xd78 = 0;
		m_unk0xd04 &= ~(c_flags0xd04Bit13 | c_flags0xd04Bit14);
	}

	if (m_unk0x3e8.m_unk0x3ec) {
		if (m_unk0x014) {
			m_unk0x014->FUN_00422100();
		}

		if (!m_unk0xd4c) {
			SoundVector position;
			m_unk0x018.m_unk0x044->VTable0x04(&position);

			g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
			LegoS32 randomValue = g_unk0x004befec[g_unk0x004c6ee4];
			if (randomValue % 2) {
				m_unk0x004->FUN_00443b80(0x19, &position, g_unk0x004b0958, g_unk0x004b095c, 1.0f, 1.0f);
			}
			else {
				m_unk0x004->FUN_00443b80(0x38, &position, g_unk0x004b0958, g_unk0x004b095c, 1.0f, 1.0f);
			}

			m_unk0xd4c = 250;
		}
	}

	LegoU32 flags = m_unk0xd04;
	if ((flags & c_flags0xd04Bit27) && !(flags & c_flags0xd04Bit3)) {
		m_unk0x008->FUN_0045b1e0(this, 2);
	}
}

// FUNCTION: LEGORACERS 0x00437b50
void RaceState::Racer::FUN_00437b50()
{
	GolVec3 direction;

	if (!(m_unk0xc70.m_unk0x014 & Field0xc70::c_flags0x014Bit2)) {
		FUN_00439870();
		return;
	}

	direction = m_unk0x3e8.m_unk0x168;

	LegoFloat value = 1.0f - (m_unk0x3e8.m_unk0x13c->GetOrientation().m_m[0][0] * direction.m_x +
							  m_unk0x3e8.m_unk0x13c->GetOrientation().m_m[0][1] * direction.m_y +
							  m_unk0x3e8.m_unk0x13c->GetOrientation().m_m[0][2] * direction.m_z);

	if (m_unk0x3e8.m_unk0x64c < 0.0f) {
		value = -value;
	}

	m_unk0x018.m_unk0x39c += value * 0.059999999f;
}

// STUB: LEGORACERS 0x00437be0
void RaceState::Racer::FUN_00437be0()
{
	for (LegoU32 i = 0; i <= 3; i++) {
		Field0xd8c* resource = NULL;

		switch (i) {
		case 0:
			resource = m_unk0xd8c;
			break;
		case 1:
			resource = m_unk0xd90;
			break;
		case 2:
			resource = m_unk0xd94;
			break;
		case 3:
			resource = m_unk0xd98;
			break;
		default:
			continue;
		}

		if (resource) {
			LegoU32 flags = m_unk0xd04;
			if ((flags & c_flags0xd04Bit6) && i == m_unk0xd68 && i < 3) {
				if (!resource->VTable0x0c()) {
					resource->VTable0x04(1);
				}

				GolVec3 position;
				m_unk0x018.m_unk0x044->VTable0x04(&position);
				resource->m_unk0x018 = position;
				resource->m_unk0x024 = m_unk0x3e8.m_unk0x008;
			}
			else if ((flags & c_flags0xd04Bit4) && i == 3) {
				if (!resource->VTable0x0c()) {
					resource->VTable0x04(1);
				}
			}
			else if (resource->VTable0x0c()) {
				resource->VTable0x08();
			}
		}
	}

	if (m_unk0xdac) {
		GolVec3 position;
		m_unk0x018.m_unk0x284.VTable0x04(&position);
		m_unk0xdac->m_unk0x018 = position;
	}
}

// FUNCTION: LEGORACERS 0x00437d40
void RaceState::Racer::FUN_00437d40(LegoU32 p_elapsedMs)
{
	if (!(m_unk0xd04 & c_flags0xd04Bit10) || !m_unk0xd9c) {
		return;
	}

	SoundVector position;
	m_unk0x018.m_unk0x044->VTable0x04(&position);

	GolVec3 velocity = m_unk0x3e8.m_unk0x008;
	LegoFloat frequencyScale;

	if (m_unk0xd9c && m_unk0xda0 && m_unk0xda4) {
		if (m_unk0x3e8.m_unk0x628 == 0.0f && !(m_unk0xc70.m_unk0x014 & Field0xc70::c_flags0x014Bit0)) {
			if (m_unk0x3e8.m_unk0x604 > g_unk0x004b0988) {
				if (!m_unk0xda4->IsPlaying()) {
					m_unk0xda4->Play(TRUE);
					m_unk0xd24 = 2;
				}
			}
			else if (!m_unk0xd9c->IsPlaying()) {
				m_unk0xd9c->Play(TRUE);
				m_unk0xd24 = 0;
			}
		}
		else if (!m_unk0xda0->IsPlaying()) {
			m_unk0xda0->Play(TRUE);
			m_unk0xd24 = 1;
		}

		LegoFloat elapsedStep = static_cast<LegoFloat>(p_elapsedMs) * g_unk0x004b099c;
		elapsedStep *= g_unk0x004b0998;
		LegoFloat targetVolume = (m_unk0xd04 & c_flags0xd04Bit12) ? g_unk0x004b0990 : g_unk0x004b098c;

		switch (m_unk0xd24) {
		case 2:
			if (m_unk0xd30 < targetVolume) {
				m_unk0xd30 += elapsedStep;
			}
			if (m_unk0xd30 > targetVolume) {
				m_unk0xd30 = targetVolume;
			}
			if (elapsedStep > m_unk0xd28) {
				m_unk0xd28 = 0.0f;
			}
			else {
				m_unk0xd28 -= elapsedStep;
			}
			if (elapsedStep > m_unk0xd2c) {
				m_unk0xd2c = 0.0f;
			}
			else {
				m_unk0xd2c -= elapsedStep;
			}
			break;
		case 1:
			if (m_unk0xd2c < targetVolume) {
				m_unk0xd2c += elapsedStep;
			}
			if (m_unk0xd2c > targetVolume) {
				m_unk0xd2c = targetVolume;
			}
			if (elapsedStep > m_unk0xd28) {
				m_unk0xd28 = 0.0f;
			}
			else {
				m_unk0xd28 -= elapsedStep;
			}
			if (elapsedStep > m_unk0xd30) {
				m_unk0xd30 = 0.0f;
			}
			else {
				m_unk0xd30 -= elapsedStep;
			}
			break;
		case 0:
			if (m_unk0xd28 < targetVolume) {
				LegoFloat increment = elapsedStep;
				increment *= g_unk0x004b09d0;
				m_unk0xd28 += increment;
			}
			if (m_unk0xd28 > targetVolume) {
				m_unk0xd28 = targetVolume;
			}
			if (elapsedStep > m_unk0xd2c) {
				m_unk0xd2c = 0.0f;
			}
			else {
				m_unk0xd2c -= elapsedStep;
			}
			if (elapsedStep > m_unk0xd30) {
				m_unk0xd30 = 0.0f;
			}
			else {
				m_unk0xd30 -= elapsedStep;
			}
			break;
		}

		if (m_unk0xd28 == targetVolume) {
			m_unk0xd9c->SetVolume(targetVolume);
		}
		else if (m_unk0xd28 == 0.0f) {
			m_unk0xd9c->Stop();
		}
		else {
			LegoFloat volume = m_unk0xd28;
			volume *= g_unk0x004b0994;
			volume *= g_negativeRadiansToTableIndex;
			LegoS32 index = (c_volumeTableBase - static_cast<LegoS32>(volume)) & c_volumeTableMask;
			volume = g_cosineTable[index];
			volume *= targetVolume;
			m_unk0xd9c->SetVolume(volume);
		}

		if (m_unk0xd2c == targetVolume) {
			m_unk0xda0->SetVolume(targetVolume);
		}
		else if (m_unk0xd2c == 0.0f) {
			m_unk0xda0->Stop();
		}
		else {
			LegoFloat volume = m_unk0xd2c;
			volume *= g_unk0x004b0994;
			volume *= g_negativeRadiansToTableIndex;
			LegoS32 index = (c_volumeTableBase - static_cast<LegoS32>(volume)) & c_volumeTableMask;
			volume = g_cosineTable[index];
			volume *= targetVolume;
			m_unk0xda0->SetVolume(volume);
		}

		if (m_unk0xd30 == targetVolume) {
			m_unk0xda4->SetVolume(targetVolume);
		}
		else if (m_unk0xd30 == 0.0f) {
			m_unk0xda4->Stop();
		}
		else {
			LegoFloat volume = m_unk0xd30;
			volume *= g_unk0x004b0994;
			volume *= g_negativeRadiansToTableIndex;
			LegoS32 index = (c_volumeTableBase - static_cast<LegoS32>(volume)) & c_volumeTableMask;
			volume = g_cosineTable[index];
			volume *= targetVolume;
			m_unk0xda4->SetVolume(volume);
		}

		frequencyScale = m_unk0xd54;
		if (frequencyScale < 0.0f) {
			frequencyScale = 0.0f;
		}
		else if (frequencyScale > 1.0f) {
			frequencyScale = 1.0f;
		}

		m_unk0xd9c->SetPosition(position);
		m_unk0xd9c->SetVelocity(velocity);
		m_unk0xd9c->SetFrequencyScale(frequencyScale);

		frequencyScale = m_unk0x3e8.m_unk0x604 / g_unk0x004b0954;
		LegoBool32 boostSoundElapsed = m_unk0xd50 > c_boostSoundElapsedThreshold;
		frequencyScale *= 1.0f - g_unk0x004b094c - g_unk0x004b0950;
		frequencyScale *= m_unk0xd54;
		frequencyScale += g_unk0x004b094c;
		if (boostSoundElapsed) {
			frequencyScale += g_unk0x004b0950;
		}
		if (frequencyScale < 0.0f) {
			frequencyScale = 0.0f;
		}
		else if (frequencyScale > 1.0f) {
			frequencyScale = 1.0f;
		}

		m_unk0xda0->SetPosition(position);
		m_unk0xda0->SetVelocity(velocity);
		m_unk0xda0->SetFrequencyScale(frequencyScale);

		frequencyScale = m_unk0x3e8.m_unk0x604 / g_unk0x004b0954;
		frequencyScale *= 1.0f - g_unk0x004b094c;
		frequencyScale *= m_unk0xd54;
		frequencyScale += g_unk0x004b094c;
		if (frequencyScale < 0.0f) {
			frequencyScale = 0.0f;
		}
		else if (frequencyScale > 1.0f) {
			frequencyScale = 1.0f;
		}

		m_unk0xda4->SetPosition(position);
		m_unk0xda4->SetVelocity(velocity);
		m_unk0xda4->SetFrequencyScale(frequencyScale);
	}

	if (m_unk0xda8) {
		if (m_unk0x3e8.m_unk0x618 >= g_unk0x004b09a0 && m_unk0x3e8.m_unk0x628 < 0.0f) {
			m_unk0xda8->SetPosition(position);
			m_unk0xda8->SetVelocity(velocity);
			frequencyScale = m_unk0x3e8.m_unk0x604;
			frequencyScale = g_unk0x004b0954 - frequencyScale;
			frequencyScale *= g_unk0x004b09a4;
			frequencyScale = 1.0f - frequencyScale;
			m_unk0xda8->SetFrequencyScale(frequencyScale);
			return;
		}

		m_unk0x004->FUN_00443c10(m_soundDa8);
		m_unk0xda8 = NULL;
		return;
	}

	if (m_unk0x3e8.m_unk0x618 > g_unk0x004b09a0 && m_unk0x3e8.m_unk0x628 < 0.0f) {
		m_unk0x004->FUN_00443b80(2, &position, g_unk0x004b0958, g_unk0x004b095c, 1.0f, 1.0f);
		m_unk0xda8 = m_unk0x004->FUN_00443bd0(3);

		if (m_unk0xda8) {
			m_unk0xda8->Play(TRUE);
			LegoFloat maxDistance = g_unk0x004b095c;
			LegoFloat minDistance = g_unk0x004b0958;
			m_unk0xda8->SetDistanceRangeWithMinSquared(minDistance * minDistance, maxDistance);
			m_unk0xda8->SetPosition(position);
			m_unk0xda8->SetVelocity(velocity);
			frequencyScale = m_unk0x3e8.m_unk0x604;
			frequencyScale = g_unk0x004b0954 - frequencyScale;
			frequencyScale *= g_unk0x004b09a4;
			frequencyScale = 1.0f - frequencyScale;
			m_unk0xda8->SetFrequencyScale(frequencyScale);
		}
	}
}

// FUNCTION: LEGORACERS 0x00438500
void RaceState::Racer::FUN_00438500()
{
	if (m_unk0xd08 != 2) {
		LegoU32 flags = m_unk0xd04;
		flags &= ~c_flags0xd04Bit10;
		m_unk0xd04 = flags;

		if (m_unk0xd9c) {
			m_unk0xd9c->Stop();
		}

		if (m_unk0xd9c) {
			m_unk0xda0->Stop();
		}

		if (m_unk0xd9c) {
			m_unk0xda4->Stop();
		}
	}
}

// STUB: LEGORACERS 0x00438560
void RaceState::Racer::VTable0x00(LegoEventQueue::CallbackData* p_data)
{
	if (p_data->m_unk0x00 == 1) {
		LegoU32 flags = m_unk0xd04;
		m_unk0xd04 = flags & ~c_flags0xd04Bit8;

		if (!(flags & c_flags0xd04Bit7)) {
			FUN_00439870();
		}

		if (m_unk0xd70 == 1) {
			m_unk0x3e8.VTable0x44();
			m_unk0xd70 = 0;
		}
		else if (m_unk0xd70 == 2) {
			m_unk0x3e8.VTable0x4c();
			m_unk0xd70 = 0;
		}

		return;
	}

	if (p_data->m_unk0x00 != 3) {
		return;
	}

	LegoEventQueue::Field0x30::CollisionCallbackData* collision =
		static_cast<LegoEventQueue::Field0x30::CollisionCallbackData*>(p_data->m_data);
	LegoEventQueue::Descriptor::Field0x10* firstTarget = p_data->m_target0;
	LegoEventQueue::Descriptor::Field0x10* secondTarget = collision->m_unk0x20;
	Racer* firstRacer = static_cast<Racer*>(firstTarget->m_owner);
	Racer* secondRacer = static_cast<Racer*>(secondTarget->m_owner);

	if (firstRacer->m_unk0xd04 & c_flags0xd04Bit4) {
		return;
	}

	if (secondRacer && (secondRacer->m_unk0xd04 & c_flags0xd04Bit4)) {
		return;
	}

	if (firstRacer->m_unk0x3e8.m_flags0x6c0 & c_flags0xaa8Bit7) {
		return;
	}

	if (secondRacer && (secondRacer->m_unk0x3e8.m_flags0x6c0 & c_flags0xaa8Bit7)) {
		return;
	}

	GolVec3 collisionNormal = collision->m_unk0x10;
	GolVec3 impulse = collisionNormal;
	impulse.m_x *= collision->m_unk0x1c;
	impulse.m_y *= collision->m_unk0x1c;
	impulse.m_z *= collision->m_unk0x1c;

	firstRacer->m_unk0x3e8.FUN_00429680(&impulse);

	GolVec3 relativeVelocity;
	relativeVelocity.m_x = firstTarget->m_unk0x008.m_x - secondTarget->m_unk0x008.m_x;
	relativeVelocity.m_y = firstTarget->m_unk0x008.m_y - secondTarget->m_unk0x008.m_y;
	relativeVelocity.m_z = firstTarget->m_unk0x008.m_z - secondTarget->m_unk0x008.m_z;

	LegoFloat impulseNumerator = -GOLVECTOR3_DOT(relativeVelocity, collisionNormal) * (g_unk0x004b0970 + 1.0f);

	LegoFloat collisionNormalLengthSquared = GOLVECTOR3_DOT(collisionNormal, collisionNormal);
	LegoFloat inverseMassTerm = (firstTarget->m_unk0x0cc + secondTarget->m_unk0x0cc) * collisionNormalLengthSquared;

	GolVec3 firstContactOffset;
	firstContactOffset.m_x = firstTarget->m_unk0x020.m_x - collision->m_unk0x04.m_x;
	firstContactOffset.m_y = firstTarget->m_unk0x020.m_y - collision->m_unk0x04.m_y;
	firstContactOffset.m_z = firstTarget->m_unk0x020.m_z - collision->m_unk0x04.m_z;
	GolMath::NormalizeVector3(firstContactOffset, &firstContactOffset);

	GolVec3 secondContactOffset;
	secondContactOffset.m_x = secondTarget->m_unk0x020.m_x - collision->m_unk0x04.m_x;
	secondContactOffset.m_y = secondTarget->m_unk0x020.m_y - collision->m_unk0x04.m_y;
	secondContactOffset.m_z = secondTarget->m_unk0x020.m_z - collision->m_unk0x04.m_z;
	GolMath::NormalizeVector3(secondContactOffset, &secondContactOffset);

	GolVec3 firstAngularAxis;
	firstAngularAxis.m_x = firstContactOffset.m_y * collisionNormal.m_z - collisionNormal.m_y * firstContactOffset.m_z;
	firstAngularAxis.m_y = firstContactOffset.m_z * collisionNormal.m_x - collisionNormal.m_z * firstContactOffset.m_x;
	firstAngularAxis.m_z = firstContactOffset.m_x * collisionNormal.m_y - firstContactOffset.m_y * collisionNormal.m_x;

	const GolMatrix3& firstInertia = firstTarget->m_unk0x074;
	GolVec3 firstAngular;
	firstAngular.m_x = firstInertia.m_m[2][0] * firstAngularAxis.m_z + firstInertia.m_m[1][0] * firstAngularAxis.m_y +
					   firstInertia.m_m[0][0] * firstAngularAxis.m_x;
	firstAngular.m_y = firstInertia.m_m[2][1] * firstAngularAxis.m_z + firstInertia.m_m[1][1] * firstAngularAxis.m_y +
					   firstInertia.m_m[0][1] * firstAngularAxis.m_x;
	firstAngular.m_z = firstInertia.m_m[2][2] * firstAngularAxis.m_z + firstInertia.m_m[1][2] * firstAngularAxis.m_y +
					   firstInertia.m_m[0][2] * firstAngularAxis.m_x;

	GolVec3 firstAngularContribution;
	firstAngularContribution.m_x =
		firstAngular.m_y * firstContactOffset.m_z - firstAngular.m_z * firstContactOffset.m_y;
	firstAngularContribution.m_y =
		firstAngular.m_z * firstContactOffset.m_x - firstAngular.m_x * firstContactOffset.m_z;
	firstAngularContribution.m_z =
		firstAngular.m_x * firstContactOffset.m_y - firstAngular.m_y * firstContactOffset.m_x;

	GolVec3 secondAngularAxis;
	secondAngularAxis.m_x =
		secondContactOffset.m_y * collisionNormal.m_z - collisionNormal.m_y * secondContactOffset.m_z;
	secondAngularAxis.m_y =
		secondContactOffset.m_z * collisionNormal.m_x - collisionNormal.m_z * secondContactOffset.m_x;
	secondAngularAxis.m_z =
		secondContactOffset.m_x * collisionNormal.m_y - secondContactOffset.m_y * collisionNormal.m_x;

	const GolMatrix3& secondInertia = secondTarget->m_unk0x074;
	GolVec3 secondAngular;
	secondAngular.m_x = secondInertia.m_m[2][0] * secondAngularAxis.m_z +
						secondInertia.m_m[1][0] * secondAngularAxis.m_y +
						secondInertia.m_m[0][0] * secondAngularAxis.m_x;
	secondAngular.m_y = secondInertia.m_m[2][1] * secondAngularAxis.m_z +
						secondInertia.m_m[1][1] * secondAngularAxis.m_y +
						secondInertia.m_m[0][1] * secondAngularAxis.m_x;
	secondAngular.m_z = secondInertia.m_m[2][2] * secondAngularAxis.m_z +
						secondInertia.m_m[1][2] * secondAngularAxis.m_y +
						secondInertia.m_m[0][2] * secondAngularAxis.m_x;

	GolVec3 secondAngularContribution;
	secondAngularContribution.m_x =
		secondAngular.m_y * secondContactOffset.m_z - secondAngular.m_z * secondContactOffset.m_y;
	secondAngularContribution.m_y =
		secondAngular.m_z * secondContactOffset.m_x - secondAngular.m_x * secondContactOffset.m_z;
	secondAngularContribution.m_z =
		secondAngular.m_x * secondContactOffset.m_y - secondAngular.m_y * secondContactOffset.m_x;

	GolVec3 angularContribution;
	angularContribution.m_x = firstAngularContribution.m_x + secondAngularContribution.m_x;
	angularContribution.m_y = firstAngularContribution.m_y + secondAngularContribution.m_y;
	angularContribution.m_z = firstAngularContribution.m_z + secondAngularContribution.m_z;

	LegoFloat impulseDenominator = GOLVECTOR3_DOT(collisionNormal, angularContribution) + inverseMassTerm;
	LegoFloat impulseScale = impulseNumerator / impulseDenominator;

	firstRacer->m_unk0x3e8.VTable0x20(&collisionNormal, impulseScale);
	if (firstRacer->m_unk0x014) {
		firstRacer->m_unk0x014->FUN_004220e0();
	}

	if (!secondRacer) {
		return;
	}

	secondRacer->m_unk0x3e8.VTable0x20(&collisionNormal, -impulseScale);
	if (secondRacer->m_unk0x014) {
		secondRacer->m_unk0x014->FUN_004220e0();
	}

	if (firstRacer->m_unk0xd08 == 2 && secondRacer->m_unk0xd08 == 2) {
		if (firstRacer->m_unk0x3e8.m_unk0x0dc == 1.0f) {
			firstRacer->m_unk0xd48 = 750;
		}

		if (secondRacer->m_unk0x3e8.m_unk0x0dc == 1.0f) {
			secondRacer->m_unk0xd48 = 750;
		}
	}
	else if (
		firstRacer->m_unk0x3e8.m_unk0x604 > secondRacer->m_unk0x3e8.m_unk0x604 && !firstRacer->m_unk0xd4c &&
		!secondRacer->m_unk0xd4c
	) {
		SoundVector soundPosition;
		soundPosition.m_x = firstRacer->m_unk0x3e8.m_unk0x008.m_x;
		soundPosition.m_y = firstRacer->m_unk0x3e8.m_unk0x008.m_y;
		soundPosition.m_z = firstRacer->m_unk0x3e8.m_unk0x008.m_z;
		GolMath::NormalizeVector3(soundPosition, &soundPosition);

		g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
		LegoU32 soundId = (g_unk0x004befec[g_unk0x004c6ee4] & 1) ? 0x37 : 0x18;
		m_unk0x004->FUN_00443b80(soundId, &soundPosition, g_unk0x004b0958, g_unk0x004b095c, 1.0f, 1.0f);

		firstRacer->m_unk0xd4c = 250;
		secondRacer->m_unk0xd4c = 250;

		m_unk0x018.m_unk0x27c->FUN_00489d70("carsprk", &soundPosition, NULL, NULL);

		if (firstRacer->m_unk0xd04 & c_flags0xd04Bit0) {
			secondRacer->FUN_00439240(FALSE);
		}
		else {
			firstRacer->FUN_00439240(FALSE);
		}
	}

	if ((firstRacer->m_unk0xd04 & c_flags0xd04Bit0) && !(secondRacer->m_unk0xd04 & c_flags0xd04Bit0)) {
		if (firstRacer->m_unk0xd6c == 1) {
			GolVec3 secondForward;
			secondRacer->m_unk0x018.m_unk0x044->GetOrientationRow0(&secondForward);
			LegoFloat dot = GOLVECTOR3_DOT(secondForward, collisionNormal);

			if (dot > -g_unk0x004b0980 && dot < g_unk0x004b0980) {
				GolVec3 shove = collisionNormal;
				shove.m_x *= g_unk0x004b09d4;
				shove.m_y *= g_unk0x004b09d4;
				shove.m_z *= g_unk0x004b09d4;
				secondRacer->FUN_00438e60(&shove);
			}
		}
		else if (firstRacer->m_unk0xd6c == 2) {
			secondRacer->m_unk0x3e8.VTable0x24(1.0f, 0.0089999996f, 0);
		}
		else if (firstRacer->m_unk0xd6c == 3) {
			secondRacer->m_unk0x3e8.VTable0x24(2.0f, 0.0089999996f, 0);
		}
	}

	if ((secondRacer->m_unk0xd04 & c_flags0xd04Bit0) && !(firstRacer->m_unk0xd04 & c_flags0xd04Bit0)) {
		if (secondRacer->m_unk0xd6c == 1) {
			GolVec3 firstForward;
			firstRacer->m_unk0x018.m_unk0x044->GetOrientationRow0(&firstForward);
			LegoFloat dot = GOLVECTOR3_DOT(firstForward, collisionNormal);

			if (dot > -g_unk0x004b0980 && dot < g_unk0x004b0980) {
				GolVec3 shove = collisionNormal;
				shove.m_x *= g_unk0x004b09d4;
				shove.m_y *= g_unk0x004b09d4;
				shove.m_z *= g_unk0x004b09d4;
				firstRacer->FUN_00438e60(&shove);
			}
		}
		else if (secondRacer->m_unk0xd6c == 2) {
			firstRacer->m_unk0x3e8.VTable0x24(1.0f, 0.0089999996f, 0);
		}
		else if (secondRacer->m_unk0xd6c == 3) {
			firstRacer->m_unk0x3e8.VTable0x24(2.0f, 0.0089999996f, 0);
		}
	}

	if ((firstRacer->m_unk0xd04 & c_flags0xd04Bit11) && !(secondRacer->m_unk0xd04 & c_flags0xd04Bit11) &&
		firstRacer->m_unk0xd80 && !(secondRacer->m_unk0xd04 & c_flags0xd04Bit0)) {
		secondRacer->FUN_00439900(&firstRacer->m_unk0x018.m_unk0x284, firstRacer->m_unk0xd7c);
		firstRacer->FUN_00439b00();
	}
	else if (
		(secondRacer->m_unk0xd04 & c_flags0xd04Bit11) && !(firstRacer->m_unk0xd04 & c_flags0xd04Bit11) &&
		secondRacer->m_unk0xd80 && !(firstRacer->m_unk0xd04 & c_flags0xd04Bit0)
	) {
		firstRacer->FUN_00439900(&secondRacer->m_unk0x018.m_unk0x284, secondRacer->m_unk0xd7c);
		secondRacer->FUN_00439b00();
	}

	firstRacer->m_unk0xd04 |= c_flags0xd04Bit28;
	secondRacer->m_unk0xd04 |= c_flags0xd04Bit28;
}

// FUNCTION: LEGORACERS 0x00438e60
void RaceState::Racer::FUN_00438e60(GolVec3* p_unk0x04)
{
	LegoEventQueue::Descriptor descriptor;
	if (m_unk0xd04 & c_flags0xd04Bit8) {
		return;
	}

	descriptor.m_unk0x04 = 0;
	descriptor.m_unk0x0c = 0;
	descriptor.m_unk0x00 = 1;
	descriptor.m_unk0x08 = 1;
	descriptor.m_unk0x10 = 750;
	if (m_raceState00c->GetUnk0x0f0()->FUN_0042fb50(this, &descriptor) == NULL) {
		return;
	}

	m_unk0x3e8.FUN_00447f30(2.5f, 0.89999998f, 3.1415927f);
	LegoU32 flags = m_unk0x3e8.m_flags0x6c0;
	if (!(flags & Field0x3e8::c_flags0x6c0Bit5)) {
		m_unk0x3e8.VTable0x40(p_unk0x04);
		m_unk0xd70 = 1;
	}
	else if (!(flags & Field0x3e8::c_flags0x6c0Bit6)) {
		m_unk0x3e8.VTable0x48(p_unk0x04);
		m_unk0xd70 = 2;
	}

	m_unk0xd04 |= c_flags0xd04Bit8;
}

// FUNCTION: LEGORACERS 0x00438f20
void RaceState::Racer::FUN_00438f20()
{
	if (m_unk0x008->GetUnk0x187c() >= 20) {
		m_unk0xcdc = 1000;
	}
	else {
		LegoU32 state = m_unk0xcd0;
		if (state && state == m_unk0xccc && m_unk0xd58 < m_unk0xcd4) {
			m_unk0xcdc = 1000;
		}
		else {
			switch (m_unk0xccc) {
			case 3:
				g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
				if ((g_unk0x004befec[g_unk0x004c6ee4] & 0xff) >= m_unk0xd1e) {
					m_unk0xcdc = 1000;
				}
				else {
					if ((m_unk0xd04 & c_flags0xd04Bit12) && m_unk0xd58 == 3) {
						return;
					}
					if (m_unk0x3e8.m_flags0x6c0 & c_flags0xaa8Bit1) {
						return;
					}

					FUN_00439100();
				}
				return;
			case 1: {
				GolVec3 position;
				m_unk0x018.m_unk0x044->VTable0x04(&position);

				GolVec3 direction;
				m_unk0x018.m_unk0x044->GetOrientationRow0(&direction);

				if (!m_unk0x00c
						 ->FUN_0043ca60(&position, &direction, g_unk0x004b0974, g_unk0x004b0978, g_unk0x004b097c)) {
					return;
				}
				g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
				if ((g_unk0x004befec[g_unk0x004c6ee4] & 0xff) >= m_unk0xd1c) {
					m_unk0xcdc = 1000;
				}
				else {
					FUN_00439100();
				}
				return;
			}
			case 4:
				g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
				if ((g_unk0x004befec[g_unk0x004c6ee4] & 0xff) >= m_unk0xd1d) {
					m_unk0xcdc = 1000;
				}
				else {
					FUN_00439100();
				}
				return;
			case 2:
				g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
				if ((g_unk0x004befec[g_unk0x004c6ee4] & 0xff) >= m_unk0xd1f) {
					m_unk0xcdc = 1000;
				}
				else {
					FUN_00439100();
				}
				return;
			default:
				return;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00439100
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
	}
	else {
		if (flags & c_flags0xd04Bit25) {
			index = 3;
		}

		switch (state) {
		case 3:
			if (!((flags & c_flags0xd04Bit27) && index != 3)) {
				m_unk0x008->FUN_0045b1e0(this, index);
			}
			break;
		case 1:
			m_unk0x008->FUN_0045a950(this, index);
			break;
		case 4:
			FUN_00439240(TRUE);
			m_unk0x008->FUN_0045a9b0(this, index);
			break;
		case 2:
			FUN_00439240(TRUE);
			m_unk0x008->FUN_0045b030(this, index);
			break;
		default:
			return;
		}
	}

	m_unk0xccc = 0;
	FUN_00439520();
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
	m_unk0x3e8.m_unk0x6ec = value;

	if (m_unk0xe2c) {
		m_unk0x3e8.m_unk0x748 = 0;
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

// FUNCTION: LEGORACERS 0x00439420
LegoBool32 RaceState::Racer::FUN_00439420(Field0xd5c* p_unk0x04)
{
	if (m_unk0xd58 != sizeOfArray(m_unk0xd5c)) {
		LegoU32 index = 0;
		Field0xd5c** current = m_unk0xd5c;

		while (TRUE) {
			if (!*current) {
				break;
			}

			index++;
			current++;

			if (index >= sizeOfArray(m_unk0xd5c)) {
				return FALSE;
			}
		}

		m_unk0xd5c[index] = p_unk0x04;
		m_unk0x004->FUN_00443b50(m_unk0xd58 + 11);

		LegoU32 count = m_unk0xd58 + 1;
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

// FUNCTION: LEGORACERS 0x00439570
void RaceState::Racer::FUN_00439570()
{
	LegoU32 flags = m_unk0xd04;
	if (!(flags & c_flags0xd04Bit3)) {
		m_unk0xd04 = flags | c_flags0xd04Bit3;
		m_unk0x3e8.VTable0x2c();
		m_unk0x3e8.VTable0x30();
	}
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

// FUNCTION: LEGORACERS 0x004395d0
void RaceState::Racer::FUN_004395d0()
{
	m_unk0xd04 |= c_flags0xd04Bit4;
	FUN_00439b00();
	m_unk0x018.FUN_0043dcd0();
	m_unk0x018.FUN_0043dbb0();
	m_unk0x018.m_unk0x000 &= ~(Field0x018::c_flags0x000Bit2 | Field0x018::c_flags0x000Bit4);
	m_unk0x018.FUN_0043fd70();
	m_unk0x018.FUN_0043fdb0();
	Field0x3e8* field0x3e8 = &m_unk0x3e8;
	field0x3e8->VTable0x2c();

	if (m_unk0xd08 == 2 && m_unk0x3e8.m_unk0x744) {
		field0x3e8->FUN_00429a90();
	}
	else {
		field0x3e8->m_flags0x6c0 |= c_flags0xaa8Bit12;
	}

	if (m_unk0x014) {
		m_unk0x014->FUN_00422030(3);
	}
}

// FUNCTION: LEGORACERS 0x00439660
void RaceState::Racer::FUN_00439660()
{
	m_unk0xd04 &= ~c_flags0xd04Bit4;

	Field0x018* field = &m_unk0x018;
	field->FUN_0043db60();

	if (m_unk0xd08 == 2 && m_unk0x3e8.m_unk0x744) {
		m_unk0x3e8.FUN_00429af0();
		field->m_unk0x000 |= Field0x018::c_flags0x000Bit2;
		return;
	}

	m_unk0x3e8.m_flags0x6c0 &= ~c_flags0xaa8Bit12;
	field->m_unk0x000 |= Field0x018::c_flags0x000Bit2;
}

// FUNCTION: LEGORACERS 0x004396c0
void RaceState::Racer::FUN_004396c0(LegoU32 p_unk0x04)
{
	m_unk0xd04 |= c_flags0xd04Bit6;

	if (m_unk0xd08 != 2) {
		m_unk0x018.FUN_0043fd30();
	}

	m_unk0xc70.m_unk0x014 = (m_unk0xc70.m_unk0x014 & ~Field0xc70::c_flags0x014Bit8) | Field0xc70::c_flags0x014Bit0;
	m_unk0x3e8.FUN_00446fa0();
	m_unk0x3e8.FUN_004292e0();
	m_unk0xd68 = p_unk0x04;

	if (m_unk0x014) {
		m_unk0x014->FUN_00422030(p_unk0x04);
	}
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

// FUNCTION: LEGORACERS 0x00439790
void RaceState::Racer::FUN_00439790()
{
	m_unk0xd04 &= ~c_flags0xd04Bit0;
}

// FUNCTION: LEGORACERS 0x004397a0
void RaceState::Racer::FUN_004397a0()
{
	m_unk0x3e8.VTable0x38();
}

// FUNCTION: LEGORACERS 0x004397b0
void RaceState::Racer::FUN_004397b0()
{
	m_unk0x3e8.VTable0x3c();
}

// FUNCTION: LEGORACERS 0x004397c0
void RaceState::Racer::FUN_004397c0(LegoBool32 p_unk0x04)
{
	if (!(m_unk0xd04 & c_flags0xd04Bit7) || p_unk0x04 != m_unk0xc70.m_unk0x030) {
		m_unk0xc70.FUN_00420260(p_unk0x04);

		if (m_unk0xc70.m_unk0x014 & Field0xc70::c_flags0x014Bit2) {
			m_unk0xd04 |= c_flags0xd04Bit7;

			if (!m_unk0xd08 && !(m_unk0x3e8.m_flags0x6c0 & c_flags0xaa8Bit3)) {
				SoundVector position;
				m_unk0x018.FUN_0043def0();

				if (!(m_unk0x018.m_unk0x000 & Field0x018::c_flags0x000Bit3)) {
					m_unk0x018.FUN_0043dc00();
				}

				m_unk0x018.m_unk0x044->VTable0x04(&position);
				m_unk0x004->FUN_00443b80(0x39, &position, g_unk0x004b0958, g_unk0x004b095c, 1.0f, 1.0f);
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00439870
void RaceState::Racer::FUN_00439870()
{
	SoundVector position;

	if (m_unk0xd04 & c_flags0xd04Bit7) {
		if (m_unk0xc70.m_unk0x014 & Field0xc70::c_flags0x014Bit2) {
			m_unk0xc70.FUN_004202c0();
		}

		LegoU8 flags0xaa8 = static_cast<LegoU8>(m_unk0x3e8.m_flags0x6c0);
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

// FUNCTION: LEGORACERS 0x00439900
void RaceState::Racer::FUN_00439900(GolAnimatedEntity* p_unk0x04, LegoU32 p_durationMs)
{
	LegoU32 flags0xd04 = m_unk0xd04;
	m_unk0xd7c = p_durationMs;
	flags0xd04 |= c_flags0xd04Bit11;
	m_unk0xd80 = 1000;
	m_unk0xd04 = flags0xd04;

	LegoU32 flags0xc70 = m_unk0xc70.m_unk0x014;
	flags0xc70 |= Field0xc70::c_flags0x014Bit4;
	GolAnimatedEntity* entity = &m_unk0x018.m_unk0x284;
	m_unk0xc70.m_unk0x014 = flags0xc70;

	LegoU32 flags0x384 = m_unk0x018.m_unk0x384;
	flags0x384 |= Field0x018::c_flags0x384Bit1;
	m_unk0x018.m_unk0x384 = flags0x384;

	entity->FUN_0040d550(
		p_unk0x04->GetModel(0),
		p_unk0x04->VTable0x58(0),
		p_unk0x04->GetModelPart(0),
		p_unk0x04->GetModelDistance(0)
	);

	for (LegoU32 i = 1; i < 3; i++) {
		if (p_unk0x04->GetModel(i)) {
			entity->FUN_10023940(
				p_unk0x04->GetModel(i),
				p_unk0x04->VTable0x58(i),
				p_unk0x04->GetModelPart(i),
				p_unk0x04->GetModelDistance(i)
			);
		}
	}

	entity->FUN_0040dad0(0);
	entity->SetPartAnimationEnabled(TRUE);
	entity->CopyOrientationFrom(*p_unk0x04);
	entity->CopyPositionFrom(*p_unk0x04);

	m_soundDac = m_unk0x004->FUN_00443bd0(8);
	if (m_soundDac) {
		m_soundDac->Play(TRUE);
		m_soundDac->SetDistanceRangeWithMinSquared(g_unk0x004b0958 * g_unk0x004b0958, g_unk0x004b095c);

		GolVec3 position;
		p_unk0x04->VTable0x04(&position);
		m_soundDac->SetPosition(position);
	}

	ColorTransform0x20 transform;
	transform.m_redShift = 0;
	transform.m_grnShift = 1;
	transform.m_bluShift = 0;
	transform.m_alpShift = 1;
	transform.m_redOffset = 0x40;
	transform.m_grnOffset = 0;
	transform.m_bluOffset = 0;
	transform.m_alpOffset = 0;
	m_unk0x018.FUN_00440100(&transform, p_durationMs);
	m_unk0x3e8.FUN_00429380();
}

// FUNCTION: LEGORACERS 0x00439b00
void RaceState::Racer::FUN_00439b00()
{
	if (m_unk0xdac) {
		m_resourceManager004->FUN_00443c10(m_unk0xdac);
		m_unk0xdac = NULL;
	}

	LegoU32 flags0xd04 = m_unk0xd04;
	m_unk0xd7c = 0;
	flags0xd04 &= ~c_flags0xd04Bit11;
	m_unk0xd04 = flags0xd04;

	m_unk0xc70.m_unk0x014 &= ~Field0xc70::c_flags0x014Bit4;
	m_unk0x018.m_unk0x284.VTable0x54();
	m_unk0x018.FUN_00440130();
	m_unk0x3e8.FUN_004293c0();
}

// FUNCTION: LEGORACERS 0x00439b70
void RaceState::Racer::FUN_00439b70()
{
	LegoU32 state = m_unk0xd0c;
	if (state) {
		LegoU32 oldState = m_unk0xd10;
		m_unk0xd10 = state;
		m_unk0xd14 = oldState;
		m_unk0xd0c = 0;
	}
}

// FUNCTION: LEGORACERS 0x00439ba0
LegoU32 RaceState::Racer::FUN_00439ba0()
{
	LegoU32 result = m_unk0xd0c;
	if (result != 1) {
		if (result == 0 && m_unk0xd10 == 2 && m_unk0xd14 == 1) {
			LegoU32 lapTransitionCount = m_unk0xce8 + 1;
			m_unk0xce8 = lapTransitionCount;

			if (static_cast<LegoS32>(lapTransitionCount) > 0) {
				result = m_lapsCompleted;
				if (lapTransitionCount > result) {
					RaceState* raceState = m_unk0x00c;
					m_lapsCompleted = result + 1;
					result = raceState->FUN_0043cda0(this);
					m_unk0xd88 = result;

					if (result) {
						result = m_unk0xce0;
						if (m_lapsCompleted < result) {
							m_unk0xd84 = 2000;
						}
					}
				}
			}
		}

		LegoU32 state = m_unk0xd0c;
		m_unk0xd14 = m_unk0xd10;
		m_unk0xd10 = state;
		m_unk0xd0c = 1;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00439c40
void RaceState::Racer::FUN_00439c40()
{
	LegoU32 state = m_unk0xd0c;
	if (state != 2) {
		LegoU32 oldState = m_unk0xd10;
		m_unk0xd10 = state;
		m_unk0xd14 = oldState;
		m_unk0xd0c = 2;
	}
}

// FUNCTION: LEGORACERS 0x00439c70
RaceState::Racer::Field0x00c::StandingsDeltaEntry* RaceState::Racer::FUN_00439c70(
	Field0x00c::StandingsDeltaEntry* p_entries
)
{
	return m_unk0x00c->FUN_0043cf30(this, p_entries);
}

// FUNCTION: LEGORACERS 0x00439c90
void RaceState::Racer::FUN_00439c90()
{
	SoundVector position;
	m_unk0x018.m_unk0x044->VTable0x04(&position);

	m_unk0x004->FUN_00443b80(m_unk0xd23, &position, g_unk0x004b0958, g_unk0x004b095c, 1.0f, 1.0f);
	m_unk0x3e8.m_unk0x6f4->FUN_00462580(999, 999, &position);
}

// FUNCTION: LEGORACERS 0x00439cf0
void RaceState::Racer::FUN_00439cf0(LegoU32 p_elapsedMs)
{
	RaceSessionField0x27f4::Entry* field0xcc4 = m_unk0xcc4;
	if (field0xcc4) {
		LegoU32 flags = m_unk0xd04;
		LegoBool32 isBlocked = FALSE;

		if (flags & c_flags0xd04Bit4) {
			m_unk0xd78 = 0;
			m_unk0xd04 = flags & ~(c_flags0xd04Bit13 | c_flags0xd04Bit14);
			return;
		}

		LegoU32 countdown = m_unk0xd78;
		if (countdown) {
			if (p_elapsedMs >= countdown) {
				m_unk0xd78 = 0;
				m_unk0xd04 = flags & ~c_flags0xd04Bit14;
			}
			else {
				m_unk0xd78 = countdown - p_elapsedMs;
			}
		}

		GolVec3 direction = m_unk0x3e8.m_unk0x168;
		for (LegoU32 i = 0; i < sizeOfArray(field0xcc4->m_unk0x20.m_items); i++) {
			if (isBlocked) {
				break;
			}

			if (field0xcc4->m_unk0x20.m_items[i] != 0xff) {
				m_unk0x010->FUN_0041e940(field0xcc4->m_unk0x20.m_items[i]);
				field0xcc4 = m_unk0xcc4;
				LegoFloat dot = direction.m_z * field0xcc4->m_unk0x00.m_z + direction.m_y * field0xcc4->m_unk0x00.m_y +
								direction.m_x * field0xcc4->m_unk0x00.m_x;
				if (dot <= g_unk0x004b02e0) {
					isBlocked = TRUE;
				}
			}
		}

		flags = m_unk0xd04;
		if (flags & c_flags0xd04Bit13) {
			if (isBlocked) {
				m_unk0xd78 = 0;
				m_unk0xd04 = flags & ~c_flags0xd04Bit13;
			}
			else if (!m_unk0xd78) {
				m_unk0xd04 = (flags & ~(c_flags0xd04Bit13 | c_flags0xd04Bit14)) | c_flags0xd04Bit14;
			}
		}
		else {
			if (!(flags & c_flags0xd04Bit14)) {
				if (!isBlocked) {
					m_unk0xd78 = 500;
					m_unk0xd04 = flags | c_flags0xd04Bit13;
				}
			}
			else if (!isBlocked) {
				m_unk0xd78 = 500;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00439e60
void RaceState::Racer::FUN_00439e60(GolVec3* p_unk0x04)
{
	m_unk0xd04 |= c_flags0xd04Bit15;
	m_unk0xdf8.m_x = p_unk0x04->m_x;
	m_unk0xdf8.m_y = p_unk0x04->m_y;
	m_unk0xdf8.m_z = p_unk0x04->m_z;
}

// FUNCTION: LEGORACERS 0x00439e90
void RaceState::Racer::FUN_00439e90()
{
	m_unk0xd04 &= ~c_flags0xd04Bit15;
}

// FUNCTION: LEGORACERS 0x00439ea0
void RaceState::Racer::FUN_00439ea0(LegoU32)
{
	LegoU32 flags = m_unk0xd04 & ~(c_flags0xd04Bit16 | c_flags0xd04Bit17);
	m_unk0xd04 = flags;

	if (m_unk0xd04 & c_flags0xd04Bit15) {
		GolVec3 direction = m_unk0x3e8.m_unk0x168;
		GolVec3 position;
		m_unk0x018.m_unk0x044->VTable0x04(&position);

		GolVec3 delta;
		delta.m_x = m_unk0xdf8.m_x - position.m_x;
		delta.m_y = m_unk0xdf8.m_y - position.m_y;
		delta.m_z = m_unk0xdf8.m_z - position.m_z;
		GolMath::NormalizeVector3(delta, &delta);

		LegoFloat forwardDot = direction.m_z * delta.m_z + direction.m_y * delta.m_y + direction.m_x * delta.m_x;
		if (forwardDot < 0.5f) {
			GolVec3 side;
			side.m_x = direction.m_y - 0.0f;
			side.m_y = 0.0f - direction.m_x;
			side.m_z = 0.0f;
			if (GOLVECTOR3_DOT(side, delta) > 0.0f) {
				m_unk0xd04 |= c_flags0xd04Bit16;
			}
			else {
				m_unk0xd04 |= c_flags0xd04Bit17;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00439fc0
void RaceState::Racer::FUN_00439fc0(RaceSessionField0x27f4::Entry* p_unk0x04, GolBoundingVolume::Field0x0c* p_unk0x08)
{
	LegoBool32 isForward;
	if (p_unk0x08->m_unk0x24.m_z * p_unk0x04->m_unk0x00.m_z + p_unk0x08->m_unk0x24.m_y * p_unk0x04->m_unk0x00.m_y +
			p_unk0x08->m_unk0x24.m_x * p_unk0x04->m_unk0x00.m_x <
		0.0f) {
		isForward = FALSE;
	}
	else {
		isForward = TRUE;
	}

	if (p_unk0x04 != m_unk0xcc4 || isForward != m_unk0xcc8) {
		if (p_unk0x04->m_unk0x1c == 0.0f) {
			LegoU32 flags = m_unk0xd04;
			if (isForward) {
				if (!(flags & c_flags0xd04Bit19)) {
					m_unk0xd18++;
				}
			}
			else {
				m_unk0xcc8 = isForward;
				m_unk0xd04 = flags | c_flags0xd04Bit19;
				m_unk0xd0c = 0;
				m_unk0xd10 = 2;
				m_unk0xd14 = 2;
				m_unk0xcc4 = p_unk0x04;
				return;
			}

			m_unk0xd04 = flags & ~c_flags0xd04Bit19;
		}
		else {
			LegoU32 flags = m_unk0xd04;
			if (!(flags & c_flags0xd04Bit19)) {
				m_unk0xcc4 = p_unk0x04;
				m_unk0xcc8 = isForward;
				return;
			}

			m_unk0xd18--;
			m_unk0xd04 = flags & ~c_flags0xd04Bit19;
		}

		m_unk0xcc4 = p_unk0x04;
		m_unk0xcc8 = isForward;
	}
}

// FUNCTION: LEGORACERS 0x0043a0a0
LegoFloat RaceState::Racer::FUN_0043a0a0()
{
	if (m_unk0xcc4) {
		return static_cast<LegoFloat>(m_unk0xd18) + m_unk0xcc4->m_unk0x1c;
	}

	return 0.0f;
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

// FUNCTION: LEGORACERS 0x0043a130
void RaceState::Racer::FUN_0043a130()
{
	m_unk0xd04 |= c_flags0xd04Bit20;

	if (m_unk0xd08 != 2) {
		m_unk0xc70.m_unk0x014 |= Field0xc70::c_flags0x014Bit7;
		m_unk0x018.FUN_0043dc00();
	}

	if (m_unk0x3e8.m_unk0x744) {
		m_unk0x3e8.m_unk0x7e8 = 0.0f;
		if (!(m_unk0x3e8.m_flags0x6c0 & c_flags0xaa8Bit18)) {
			m_unk0x3e8.m_unk0x7ec = 0.0f;
		}
	}

	FUN_004395a0();
}

// FUNCTION: LEGORACERS 0x0043a1a0
void RaceState::Racer::FUN_0043a1a0()
{
	LegoU32 flags0xd04 = m_unk0xd04;
	LegoU32 state = m_unk0xd08;
	flags0xd04 &= ~c_flags0xd04Bit20;
	m_unk0xd04 = flags0xd04;

	if (state != 2) {
		LegoU32 flags0x014 = m_unk0xc70.m_unk0x014;
		flags0x014 &= ~Field0xc70::c_flags0x014Bit7;
		m_unk0xc70.m_unk0x014 = flags0x014;
		m_unk0x018.FUN_0043dcd0();
	}

	if (m_unk0x3e8.m_unk0x744) {
		LegoU32 flags0xaa8 = m_unk0x3e8.m_flags0x6c0;
		m_unk0x3e8.m_unk0x7e8 = 1.0f;
		if (!(flags0xaa8 & c_flags0xaa8Bit18)) {
			m_unk0x3e8.m_unk0x7ec = 1.0f;
		}
	}

	FUN_004395a0();
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

// FUNCTION: LEGORACERS 0x0043a270
void RaceState::Racer::FUN_0043a270()
{
	LegoU32 soundId = 1;
	SoundVector position;
	m_unk0x018.m_unk0x044->VTable0x04(&position);

	LegoU32 randomIndex = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
	g_unk0x004c6ee4 = randomIndex;
	LegoS32 randomValue = g_unk0x004befec[randomIndex];
	switch (randomValue % 3) {
	case 1:
		soundId = 0x46;
		break;
	case 2:
		soundId = 0x47;
		break;
	}

	m_unk0x004->FUN_00443b80(soundId, &position, g_unk0x004b0960, g_unk0x004b0964, 1.0f, 1.0f);
	m_unk0xd74 = 500;
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
	m_racers = NULL;
	m_racerCount = 0;
	m_updateDelayMs = 0;
	m_unk0x0c = 0.0f;
}

// FUNCTION: LEGORACERS 0x0043a440
void RaceState::Field0x284::Destroy()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0043a450
void RaceState::Field0x284::FUN_0043a450(Racer* p_racers, LegoU32 p_racerCount)
{
	if (m_racers) {
		Destroy();
	}

	m_racers = p_racers;
	m_racerCount = p_racerCount;
	m_updateDelayMs = 15000;
}

// STUB: LEGORACERS 0x0043a480
LegoU32 RaceState::Field0x284::FUN_0043a480(LegoU32 p_elapsedMs)
{
	LegoU32 delayMs = m_updateDelayMs;
	LegoFloat bestProgress = -1.0f;
	LegoU32 result;

	if (p_elapsedMs > delayMs) {
		result = m_racerCount;
		LegoU32 racerIndex = 0;
		LegoU32 ignoredState;
		m_updateDelayMs = 0;

		if (result <= 0) {
			goto ResetRacerPacing;
		}

		ignoredState = 2;
		do {
			LegoU32 state = m_racers[racerIndex].m_unk0xd08;
			if (state != ignoredState && m_racers[racerIndex].FUN_0043a0a0() > bestProgress) {
				bestProgress = m_racers[racerIndex].FUN_0043a0a0();
			}

			result = m_racerCount;
			racerIndex++;
		} while (racerIndex < result);

		if (bestProgress == g_minSoundPan) {
		ResetRacerPacing:
			result = m_racerCount;
			LegoU32 index = 0;
			if (result > 0) {
				LegoU32 flags0xaa8Mask = c_racerFlags0xaa8Bit18;
				do {
					Racer* racer = &m_racers[index];
					if (!(racer->m_unk0xd04 & c_racerFlags0xd04RubberBandMask)) {
						LegoU32 flags0xaa8 = racer->m_unk0x3e8.m_flags0x6c0;
						racer->m_unk0x3e8.m_unk0x7e8 = 1.0f;
						if (!(flags0xaa8Mask & flags0xaa8)) {
							racer->m_unk0x3e8.m_unk0x7ec = 1.0f;
						}
					}

					result = m_racerCount;
					index++;
				} while (index < result);
			}
		}
		else {
			result = m_racerCount;
			racerIndex = 0;
			if (result > 0) {
				LegoU32 flags0xaa8Mask = c_racerFlags0xaa8Bit18;
				do {
					if (racerIndex) {
						Racer* racer = &m_racers[racerIndex];
						if (!(racer->m_unk0xd04 & c_racerFlags0xd04RubberBandMask)) {
							if (racer->FUN_0043a0a0() > bestProgress) {
								LegoFloat adjustment = 1.0f - g_unk0x004b09dc;
								adjustment += m_unk0x0c;
								LegoU32 flags0xaa8 = m_racers[racerIndex].m_unk0x3e8.m_flags0x6c0;
								Racer::Field0x3e8* field0x3e8 = &m_racers[racerIndex].m_unk0x3e8;
								field0x3e8->m_unk0x7e8 = adjustment;
								if (!(flags0xaa8Mask & flags0xaa8)) {
									field0x3e8->m_unk0x7ec = adjustment;
								}
							}
							else if (racer->FUN_0043a0a0() < bestProgress) {
								LegoFloat adjustment = g_unk0x004b09dc + m_unk0x0c;
								adjustment += 1.0f;
								LegoU32 flags0xaa8 = m_racers[racerIndex].m_unk0x3e8.m_flags0x6c0;
								Racer::Field0x3e8* field0x3e8 = &m_racers[racerIndex].m_unk0x3e8;
								field0x3e8->m_unk0x7e8 = adjustment;
								if (!(flags0xaa8Mask & flags0xaa8)) {
									field0x3e8->m_unk0x7ec = adjustment;
								}
							}
						}
					}

					result = m_racerCount;
					racerIndex++;
				} while (racerIndex < result);
			}
		}
	}
	else {
		result = delayMs - p_elapsedMs;
		m_updateDelayMs = result;
	}

	return result;
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
	m_unk0x0f0.m_unk0x080[0] = NULL;
	m_unk0x0f0.m_unk0x080[1] = NULL;
	m_unk0x0f0.m_unk0x080[2] = NULL;

	for (i = 0; i < sizeOfArray(m_unk0x0f0.m_unk0x08c); i++) {
		m_unk0x0f0.m_unk0x08c[i] = 0;
		m_unk0x0f0.m_unk0x094[i] = 0;
	}

	m_unk0x0f0.m_unk0x09c = 0;
	m_unk0x0f0.m_routeRecords = NULL;
	m_unk0x284.m_unk0x10 = 0;
	m_unk0x284.m_unk0x14 = 0;
	m_unk0x284.m_lapCount = 0;
}

// FUNCTION: LEGORACERS 0x0043b030
void RaceState::Destroy()
{
	m_unk0x284.Destroy();

	if (m_unk0x284.m_unk0x14) {
		m_unk0x0f0.m_golExport->DestroyMaterialList(m_unk0x284.m_unk0x14);
		m_unk0x284.m_unk0x14 = NULL;
	}

	if (m_unk0x284.m_unk0x10) {
		m_unk0x0f0.m_golExport->DestroyTextureList(m_unk0x284.m_unk0x10);
		m_unk0x284.m_unk0x10 = NULL;
	}

	LegoS32 i;
	for (i = 0; i < 2; i++) {
		if (m_unk0x0f0.m_unk0x08c[i]) {
			delete m_unk0x0f0.m_unk0x08c[i];
			m_unk0x0f0.m_unk0x08c[i] = NULL;
		}

		if (m_unk0x0f0.m_unk0x094[i]) {
			delete m_unk0x0f0.m_unk0x094[i];
			m_unk0x0f0.m_unk0x094[i] = NULL;
		}
	}

	GolNameTable* table = &m_unk0x0b4;
	table->Clear();

	table = &m_unk0x080;
	table->Clear();

	table = &m_unk0x000;
	table->Clear();

	if (m_unk0x0f0.m_unk0x07c) {
		m_unk0x0f0.m_unk0x05c->FUN_00443c10(m_unk0x0f0.m_unk0x07c);
		m_unk0x0f0.m_unk0x07c = NULL;
	}

	LegoU32 racerIndex;
	for (racerIndex = 0; racerIndex < m_unk0x0f0.m_racerCount; racerIndex++) {
		if (m_unk0x0f0.m_unk0x064[racerIndex]) {
			m_unk0x0f0.m_unk0x064[racerIndex]->m_active = 0;
			m_unk0x0f0.m_unk0x064[racerIndex] = NULL;
		}
	}

	LegoEventQueue* queue = &m_unk0x0f0;
	queue->Destroy();

	if (m_unk0x0f0.m_racers) {
		for (racerIndex = 0; racerIndex < m_unk0x0f0.m_racerCount; racerIndex++) {
			(*(m_unk0x0f0.m_racers + racerIndex)).Destroy();
		}

		delete[] m_unk0x0f0.m_racers;

		m_unk0x0f0.m_racers = NULL;
	}

	Reset();
}

// FUNCTION: LEGORACERS 0x0043b190
void RaceState::FUN_0043b190(Field0x3b190Params0x04* p_unk0x04, Field0x3b190Params0x08* p_unk0x08, LegoBool32 p_binary)
{
	m_unk0x0f0.m_field0x010 = p_unk0x08->m_racerField0x010;
	m_unk0x0f0.m_unk0x05c = p_unk0x08->m_resourceMgr;
	m_unk0x0f0.m_unk0x060 = p_unk0x08->m_unk0x18;
	m_unk0x0f0.m_golExport = p_unk0x08->m_golExport;
	m_unk0x0f0.m_timeRaceManager = p_unk0x04->m_timeRaceManager;
	m_unk0x0f0.m_routeRecords = p_unk0x04->m_routeRecords;
	m_unk0x284.m_lapCount = p_unk0x04->m_lapCount;
	static_cast<LegoEventQueue*>(&m_unk0x0f0)->VTable0x08(100);

	m_unk0x0f0.m_unk0x04c = this;
	m_unk0x0f0.m_racerCount = p_unk0x04->m_racerCount;
	m_unk0x0f0.m_racers = new Racer[m_unk0x0f0.m_racerCount];
	if (m_unk0x0f0.m_racers == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x284.m_unk0x10 = m_unk0x0f0.m_golExport->CreateTextureList();
	m_unk0x284.m_unk0x14 = m_unk0x0f0.m_golExport->CreateMaterialList();
	m_unk0x284.m_unk0x10->VTable0x1c(p_unk0x08->m_renderer, m_unk0x0f0.m_racerCount);
	m_unk0x284.m_unk0x14->VTable0x1c(p_unk0x08->m_renderer, m_unk0x0f0.m_racerCount);

	DriverCosmeticTable::LoadParams driverParams;
	driverParams.m_golExport = p_unk0x08->m_golExport;
	driverParams.m_renderer = p_unk0x08->m_renderer;
	driverParams.m_entryCapacity = m_unk0x0f0.m_racerCount;
	driverParams.m_filename = g_unk0x004bef3c[0];
	driverParams.m_binary = p_binary;
	m_unk0x000.Load(&driverParams);

	ChampionDefinitionList::LoadParams championParams;
	championParams.m_golExport = p_unk0x08->m_golExport;
	championParams.m_renderer = p_unk0x08->m_renderer;
	championParams.m_entryCapacity = m_unk0x0f0.m_racerCount;
	championParams.m_fileName = g_unk0x004bef3c[1];
	championParams.m_binary = p_binary;
	m_unk0x080.FUN_0041d370(&championParams);

	ChassisModelTable::Params chassisParams;
	chassisParams.m_golExport = p_unk0x08->m_golExport;
	chassisParams.m_renderer = p_unk0x08->m_renderer;
	chassisParams.m_instantiateCount = m_unk0x0f0.m_racerCount;
	chassisParams.m_filename = g_unk0x004bef3c[2];
	chassisParams.m_binary = p_binary;
	m_unk0x0b4.FUN_0041db10(&chassisParams);

	for (LegoU32 i = 0; i < m_unk0x0f0.m_racerCount; i++) {
		p_unk0x08->m_unk0x34 = p_unk0x04->m_unk0x20[i];
		FUN_0043b480(p_unk0x04->m_unk0x04[i], p_unk0x08, i, p_unk0x04->m_unk0x3c);
	}

	m_unk0x0b4.FUN_0041dae0();
	m_unk0x080.ClearDefinitions();
	m_unk0x000.ClearEntries();
	m_unk0x284.m_unk0x10->LoadTextures();
	m_unk0x284.m_unk0x14->FUN_10026970();
	m_unk0x284.FUN_0043a450(m_unk0x0f0.m_racers, m_unk0x0f0.m_racerCount);
}

// STUB: LEGORACERS 0x0043b480
void RaceState::FUN_0043b480(
	LegoRacers::Context::PlayerSetupSlot* p_unk0x04,
	Field0x3b190Params0x08* p_unk0x08,
	LegoU32 p_unk0x0c,
	undefined4 p_unk0x10
)
{
	Racer::Field0x36df0Params racerParams;
	Racer::Field0x018::InitParams initParams;
	::memset(&racerParams, 0, sizeof(racerParams));
	::memset(&initParams, 0, sizeof(initParams));

	ChampionDefinitionList::ChampionDefinition* championDefinition = NULL;
	ChassisModelTable::Item* chassisItem;
	if (p_unk0x04->m_driverName[0]) {
		DriverCosmeticTable::Entry* driverEntry =
			static_cast<DriverCosmeticTable::Entry*>(m_unk0x000.GetName(p_unk0x04->m_driverName));

		initParams.m_unk0x0c = m_unk0x000.LoadEntry(p_unk0x04->m_driverName);
		championDefinition =
			static_cast<ChampionDefinitionList::ChampionDefinition*>(m_unk0x080.GetName(driverEntry->m_unk0x1a));
		initParams.m_unk0x00 = m_unk0x080.FUN_0041d780(driverEntry->m_unk0x1a);
		chassisItem = static_cast<ChassisModelTable::Item*>(m_unk0x0b4.GetName(championDefinition->m_unk0x18));
		m_unk0x0b4.InstantiateModels(chassisItem, &initParams.m_unk0x08, &initParams.m_unk0x04);

		racerParams.m_vehicle.m_unk0x084 = chassisItem->m_unk0x100;
		racerParams.m_vehicle.m_unk0x085 = chassisItem->m_unk0x101;
		racerParams.m_vehicle.m_unk0x086 = chassisItem->m_unk0x102;
		racerParams.m_unk0x6c[0] = driverEntry->m_unk0x24;
		racerParams.m_unk0x6c[1] = driverEntry->m_unk0x25;
		racerParams.m_unk0x6c[2] = driverEntry->m_unk0x26;
		racerParams.m_unk0x6c[3] = driverEntry->m_unk0x27;
		racerParams.m_unk0x6c[4] = driverEntry->m_unk0x28;
		racerParams.m_unk0x6c[5] = driverEntry->m_unk0x29;
		racerParams.m_unk0x74 = driverEntry->m_unk0x2a * 12 + 1100;

		switch (driverEntry->m_unk0x22) {
		case 1:
		case 2:
		case 3:
		case 4:
			racerParams.m_unk0x7c = driverEntry->m_unk0x22;
			break;
		default:
			racerParams.m_unk0x7c = 0;
			break;
		}

		racerParams.m_unk0x80 = driverEntry->m_unk0x23;
		racerParams.m_stringChars = m_unk0x000.GetStringBuffer(p_unk0x04->m_driverName);
	}
	else {
		LegoU32 customIndex = m_unk0x0f0.m_unk0x09c;
		m_unk0x0f0.m_unk0x08c[customIndex] = new GolModelEntity;
		if (m_unk0x0f0.m_unk0x08c[customIndex] == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_unk0x0f0.m_unk0x094[customIndex] = new GolAnimatedEntity;
		if (m_unk0x0f0.m_unk0x094[customIndex] == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		p_unk0x04->m_textures->LoadTextures();
		p_unk0x04->m_materials->FUN_10026970();
		initParams.m_unk0x00 = m_unk0x0f0.m_unk0x08c[customIndex];
		initParams.m_unk0x00->VTable0x50(p_unk0x04->m_model, g_unk0x004b0a14);

		if (p_unk0x04->m_altModel == NULL) {
			LegoChar fallbackName[3];
			fallbackName[0] = 'b';
			fallbackName[1] = 'b';
			fallbackName[2] = '\0';
			m_unk0x000.GetName(fallbackName);
			initParams.m_unk0x0c = m_unk0x000.LoadEntry(fallbackName);
		}
		else {
			p_unk0x04->m_altTextures->LoadTextures();
			p_unk0x04->m_altMaterials->FUN_10026970();
			initParams.m_unk0x0c = m_unk0x0f0.m_unk0x094[customIndex];
			initParams.m_unk0x0c
				->FUN_0040d550(p_unk0x04->m_altModel, m_unk0x000.m_rootNode, &m_unk0x000.m_modelParts, g_unk0x004b0a14);
		}

		chassisItem = static_cast<ChassisModelTable::Item*>(m_unk0x0b4.GetName(p_unk0x04->m_chassisName));
		m_unk0x0b4.InstantiateModels(chassisItem, &initParams.m_unk0x08, &initParams.m_unk0x04);
		racerParams.m_vehicle.m_unk0x084 = chassisItem->m_unk0x100;
		racerParams.m_vehicle.m_unk0x085 = chassisItem->m_unk0x101;
		racerParams.m_vehicle.m_unk0x086 = chassisItem->m_unk0x102;

		for (LegoU32 i = 0; i < sizeOfArray(racerParams.m_unk0x6c); i++) {
			racerParams.m_unk0x6c[i] = 100;
		}

		racerParams.m_unk0x74 = p_unk0x0c * 100 + 1000;
		::strcpy(racerParams.m_displayName, p_unk0x04->m_playerName);
		m_unk0x0f0.m_unk0x09c = customIndex + 1;
	}

	initParams.m_unk0x10 = chassisItem->m_unk0xc4;
	initParams.m_racer = &m_unk0x0f0.m_racers[p_unk0x0c];
	initParams.m_unk0x20 = chassisItem->m_unk0xdc.m_x;
	initParams.m_unk0x24 = chassisItem->m_unk0xdc.m_y;
	initParams.m_unk0x28 = chassisItem->m_unk0xe4.m_x;
	initParams.m_unk0x2c = chassisItem->m_unk0xe4.m_y;
	::strncpy(initParams.m_materialName, "carshad", sizeof(initParams.m_materialName));
	initParams.m_materialName[sizeof(initParams.m_materialName) - 1] = static_cast<LegoChar>('0' + p_unk0x0c);

	for (LegoU32 i = 0; i < sizeOfArray(initParams.m_unk0x38); i++) {
		initParams.m_unk0x38[i] = chassisItem->m_unk0x58[i];
	}

	racerParams.m_vehicle.m_unk0x028 = chassisItem->m_unk0x88[1];
	racerParams.m_vehicle.m_unk0x038 = chassisItem->m_unk0x88[2].m_y;
	racerParams.m_vehicle.m_unk0x040 = chassisItem->m_unk0x88[3].m_x;
	racerParams.m_vehicle.m_unk0x044 = chassisItem->m_unk0x88[3].m_y;

	racerParams.m_unk0x72 = m_unk0x284.m_lapCount;
	racerParams.m_vehicle.m_unk0x060 = p_unk0x08->m_unk0x28;
	racerParams.m_vehicle.m_unk0x064 = p_unk0x08->m_unk0x2c;
	racerParams.m_vehicle.m_unk0x068 = p_unk0x08->m_unk0x0c;
	racerParams.m_unk0x78 = chassisItem->m_unk0xec;

	if (championDefinition) {
		racerParams.m_vehicle.m_unk0x04c.m_x = championDefinition->m_unk0x24;
		racerParams.m_vehicle.m_unk0x04c.m_y = championDefinition->m_unk0x28;
		racerParams.m_vehicle.m_unk0x04c.m_z = championDefinition->m_unk0x2c;
		racerParams.m_vehicle.m_unk0x058 = championDefinition->m_unk0x20;
		racerParams.m_vehicle.m_unk0x05c = 0.0f;
	}
	else {
		racerParams.m_vehicle.m_unk0x04c.m_x =
			p_unk0x04->m_unk0x18 * g_carBuildModelTextureCoordinateScale + chassisItem->m_unk0xb8.m_x;
		racerParams.m_vehicle.m_unk0x04c.m_y =
			p_unk0x04->m_unk0x1c * g_carBuildModelTextureCoordinateScale + chassisItem->m_unk0xb8.m_y;
		racerParams.m_vehicle.m_unk0x04c.m_z = chassisItem->m_unk0xb8.m_z;
		racerParams.m_vehicle.m_unk0x058 = chassisItem->m_unk0xd0 + p_unk0x04->m_unk0x14;
		racerParams.m_vehicle.m_unk0x05c = p_unk0x04->m_unk0x14;
	}

	m_unk0x0f0.m_unk0x17c[p_unk0x0c] = p_unk0x0c;
	if (m_unk0x0f0.m_timeRaceManager) {
		if (m_unk0x0f0.m_timeRaceManager->HasRecordRunLapTimes()) {
			m_unk0x0f0.m_unk0x17c[p_unk0x0c] = 2;
		}
		else {
			m_unk0x0f0.m_unk0x17c[p_unk0x0c] = 1;
		}
	}
	else if (p_unk0x10 && p_unk0x0c == 0) {
		m_unk0x0f0.m_unk0x17c[0] = 2;
	}

	LegoU32 placementIndex = m_unk0x0f0.m_unk0x17c[p_unk0x0c];
	initParams.m_unk0x08->VTable0x08(m_unk0x0f0.m_unk0x0a4[placementIndex]);
	initParams.m_unk0x08->VTable0x40(m_unk0x0f0.m_unk0x0ec[placementIndex], m_unk0x0f0.m_unk0x134[placementIndex]);

	m_unk0x0f0.m_racers[p_unk0x0c].FUN_00436df0(p_unk0x08, &initParams, &racerParams, this, p_unk0x0c);

	PurpleDune0x7c* shadowTexture = m_unk0x284.m_unk0x10->GetItem(p_unk0x0c);
	DuskwindBananaRelic0x24* shadowMaterial = m_unk0x284.m_unk0x14->GetItem(p_unk0x0c);
	shadowTexture->SetNameFromBuffer(chassisItem->m_unk0x50);
	shadowTexture->SetTextureFlags(GoldDune0x38::c_unk0x36Bit2 | GoldDune0x38::c_unk0x36Bit3);
	shadowMaterial->SetName(chassisItem->m_unk0x50);

	DuskWindBananaRelicParams shadowMaterialParams;
	::memset(&shadowMaterialParams, 0, sizeof(shadowMaterialParams));
	shadowMaterialParams.m_unk0x00 =
		DuskwindBananaRelic0x24::c_flag0x08Bit2 | DuskwindBananaRelic0x24::c_flag0x08Bit3 |
		DuskwindBananaRelic0x24::c_flag0x08Bit5 | DuskwindBananaRelic0x24::c_flag0x08Bit7 |
		DuskwindBananaRelic0x24::c_flag0x08Bit9 | DuskwindBananaRelic0x24::c_flag0x08Bit10 |
		DuskwindBananaRelic0x24::c_flag0x08Bit13 | DuskwindBananaRelic0x24::c_flag0x08Bit15 |
		DuskwindBananaRelic0x24::c_flag0x08Bit20 | DuskwindBananaRelic0x24::c_flag0x08Bit22;
	shadowMaterialParams.m_unk0x04 = shadowTexture;
	shadowMaterial->FUN_100257e0(p_unk0x08->m_renderer, shadowMaterialParams);

	Racer* racer = &m_unk0x0f0.m_racers[p_unk0x0c];
	racer->m_unk0xc70.m_unk0x050 = &m_unk0x2a0;

	LegoEventQueue::Descriptor descriptor;
	descriptor.m_unk0x00 = 3;
	descriptor.m_unk0x04 = 5;
	descriptor.m_unk0x08 = 0;
	descriptor.m_unk0x0c = 0;
	descriptor.m_data = &racer->m_unk0x3e8;
	descriptor.m_unk0x14 = 0;
	m_unk0x0f0.m_unk0x064[p_unk0x0c] = m_unk0x0f0.FUN_0042fb50(racer, &descriptor);
}

// FUNCTION: LEGORACERS 0x0043bc10
void RaceState::FUN_0043bc10(const LegoChar* p_name, LegoBool32 p_binary, LegoBool32 p_mirror)
{
	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".spb");
	}
	else {
		parser = new SpbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_name);
	parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
	LegoU32 count = parser->ReadBracketedCountAndLeftCurly();

	if (count > 0) {
		LegoU32 remaining = count;
		do {
			parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
			LegoU32 index = parser->ReadInteger();
			parser->ReadLeftCurly();

			GolFileParser::ParserTokenType token = parser->GetNextToken();
			while (token != GolFileParser::e_rightCurly) {
				switch (token) {
				case GolFileParser::e_unknown0x28:
					m_unk0x0f0.m_unk0x0a4[index].m_x = parser->ReadFloat();
					m_unk0x0f0.m_unk0x0a4[index].m_y = parser->ReadFloat();
					m_unk0x0f0.m_unk0x0a4[index].m_z = parser->ReadFloat();
					if (p_mirror) {
						m_unk0x0f0.m_unk0x0a4[index].m_y = -m_unk0x0f0.m_unk0x0a4[index].m_y;
					}
					break;
				case GolFileParser::e_unknown0x29:
					m_unk0x0f0.m_unk0x0ec[index].m_x = parser->ReadFloat();
					m_unk0x0f0.m_unk0x0ec[index].m_y = parser->ReadFloat();
					m_unk0x0f0.m_unk0x0ec[index].m_z = parser->ReadFloat();
					m_unk0x0f0.m_unk0x134[index].m_x = parser->ReadFloat();
					m_unk0x0f0.m_unk0x134[index].m_y = parser->ReadFloat();
					m_unk0x0f0.m_unk0x134[index].m_z = parser->ReadFloat();
					if (p_mirror) {
						m_unk0x0f0.m_unk0x0ec[index].m_y = -m_unk0x0f0.m_unk0x0ec[index].m_y;
						m_unk0x0f0.m_unk0x134[index].m_y = -m_unk0x0f0.m_unk0x134[index].m_y;
					}
					break;
				default:
					parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
					break;
				}

				token = parser->GetNextToken();
			}
		} while (--remaining);
	}

	parser->ReadRightCurly();
	parser->Dispose();
	if (parser != NULL) {
		delete parser;
	}
}

// FUNCTION: LEGORACERS 0x0043be60
void RaceState::FUN_0043be60(GolD3DRenderDevice* p_renderer, GolExport* p_golExport)
{
	for (LegoU32 i = 0; i < m_unk0x0f0.m_racerCount; i++) {
		m_unk0x0f0.m_racers[i].m_unk0x018.FUN_0043d990(p_renderer, p_golExport);
	}
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

// FUNCTION: LEGORACERS 0x0043c030
void RaceState::FUN_0043c030(LegoU32 p_elapsedMs)
{
	Racer* racer = m_unk0x0f0.m_racers;
	Racer* end = racer + m_unk0x0f0.m_racerCount;

	for (; racer < end; racer++) {
		if (racer->m_unk0xc70.m_unk0x014 & Racer::Field0xc70::c_flags0x014Bit7) {
			racer->m_unk0xc70.FUN_0041fd60(p_elapsedMs);
		}
		else {
			if (racer->m_unk0xd08 != 2) {
				racer->m_unk0xc70.FUN_0041fc00(p_elapsedMs);
			}
			else if (racer->m_unk0xc70.m_unk0x014 & Racer::Field0xc70::c_flags0x014Bit6) {
				racer->m_unk0xc70.FUN_004203b0(p_elapsedMs);
			}
		}
	}

	for (racer = m_unk0x0f0.m_racers; racer < end; racer++) {
		racer->m_unk0x3e8.VTable0x04(p_elapsedMs);
	}

	for (racer = m_unk0x0f0.m_racers; racer < end; racer++) {
		if (racer->m_unk0xd04 & Racer::c_flags0xd04Bit7) {
			racer->FUN_00437b50();
		}
	}

	Field0x0f0* queue = &m_unk0x0f0;
	queue->VTable0x10(p_elapsedMs);

	for (racer = m_unk0x0f0.m_racers; racer < end; racer++) {
		racer->FUN_00437740(p_elapsedMs);
	}

	for (racer = m_unk0x0f0.m_racers; racer < end; racer++) {
		racer->FUN_00437d40(p_elapsedMs);
		racer->FUN_00437be0();
	}

	for (racer = m_unk0x0f0.m_racers; racer < end; racer++) {
		racer->FUN_004377f0(p_elapsedMs);
	}

	FUN_0043c1b0();
	m_unk0x284.FUN_0043a480(p_elapsedMs);
}

// STUB: LEGORACERS 0x0043c1b0
void RaceState::FUN_0043c1b0()
{
	RacerProgressEntry* entries = g_racerProgressEntries;
	LegoU32 racerCount = m_unk0x0f0.m_racerCount;

	LegoU32 racerIndex;
	for (racerIndex = 0; racerIndex < racerCount; racerIndex++) {
		Racer* racer = &m_unk0x0f0.m_racers[racerIndex];
		entries[racerIndex].m_racer = racer;
		entries[racerIndex].m_unk0x08 = racer->FUN_0043a0a0();
	}

	LegoU32 sortIndex;
	for (sortIndex = 0; sortIndex + 1 < racerCount; sortIndex++) {
		LegoU32 minIndex = sortIndex;
		LegoFloat minProgress = entries[sortIndex].m_unk0x08;

		LegoU32 scanIndex;
		for (scanIndex = sortIndex + 1; scanIndex < racerCount; scanIndex++) {
			if (minProgress > entries[scanIndex].m_unk0x08) {
				minProgress = entries[scanIndex].m_unk0x08;
				minIndex = scanIndex;
			}
		}

		if (minIndex > sortIndex) {
			LegoFloat progress = entries[sortIndex].m_unk0x08;
			entries[sortIndex].m_unk0x08 = entries[minIndex].m_unk0x08;
			entries[minIndex].m_unk0x08 = progress;

			Racer* racer = entries[sortIndex].m_racer;
			entries[sortIndex].m_racer = entries[minIndex].m_racer;
			entries[minIndex].m_racer = racer;
		}
	}

	LegoU32 groupStart;
	for (groupStart = 0; groupStart + 1 < racerCount;) {
		LegoU32 groupEnd = groupStart + 1;
		while (groupEnd < racerCount && entries[groupStart].m_unk0x08 == entries[groupEnd].m_unk0x08) {
			groupEnd++;
		}

		RaceSessionField0x27f4::Entry* pathField = entries[groupStart].m_racer->m_unk0xcc4;
		if (groupEnd > groupStart + 1 && pathField) {
			LegoU32 tiedIndex;
			for (tiedIndex = groupStart; tiedIndex < groupEnd; tiedIndex++) {
				GolVec3 position;
				entries[tiedIndex].m_racer->m_unk0x018.m_unk0x044->VTable0x04(&position);

				LegoFloat nearestPlaneDistance = FLT_MAX;
				LegoU32 planeIndex;
				for (planeIndex = 0; planeIndex < sizeOfArray(pathField->m_unk0x20.m_items); planeIndex++) {
					if (pathField->m_unk0x20.m_items[planeIndex] != 0xff) {
						RaceSessionField0x27f4::Entry* plane =
							m_unk0x0f0.m_field0x010->FUN_0041e940(pathField->m_unk0x20.m_items[planeIndex]);
						LegoFloat distance = plane->m_unk0x00.m_x * position.m_x + plane->m_unk0x00.m_y * position.m_y +
											 plane->m_unk0x00.m_z * position.m_z + plane->m_unk0x0c;
						if (distance < nearestPlaneDistance) {
							nearestPlaneDistance = distance;
						}
					}
				}

				entries[tiedIndex].m_unk0x04 = nearestPlaneDistance;
			}

			LegoU32 tiedSortIndex;
			for (tiedSortIndex = groupStart; tiedSortIndex + 1 < groupEnd; tiedSortIndex++) {
				LegoU32 maxIndex = tiedSortIndex;
				LegoFloat maxDistance = entries[tiedSortIndex].m_unk0x04;

				LegoU32 tiedScanIndex;
				for (tiedScanIndex = tiedSortIndex + 1; tiedScanIndex < groupEnd; tiedScanIndex++) {
					if (maxDistance < entries[tiedScanIndex].m_unk0x04) {
						maxDistance = entries[tiedScanIndex].m_unk0x04;
						maxIndex = tiedScanIndex;
					}
				}

				if (maxIndex > tiedSortIndex) {
					RacerProgressEntry progressEntry = entries[tiedSortIndex];
					entries[tiedSortIndex] = entries[maxIndex];
					entries[maxIndex] = progressEntry;
				}
			}
		}

		groupStart++;
	}

	LegoU32 rankIndex;
	for (rankIndex = 0; rankIndex < racerCount; rankIndex++) {
		if (!(entries[rankIndex].m_racer->m_unk0xd04 & Racer::c_flags0xd04Bit12)) {
			entries[rankIndex].m_racer->FUN_0043a210(racerCount - rankIndex);
		}
	}

	SpatialSoundInstance* sound = m_unk0x0f0.m_sound;
	Racer* trackedRacer = m_unk0x0f0.m_racer080;
	if (sound && trackedRacer) {
		GolVec3 trackedPosition;
		trackedRacer->m_unk0x018.m_unk0x044->VTable0x04(&trackedPosition);

		Racer* nearestRacer = NULL;
		LegoFloat nearestDistanceSquared = FLT_MAX;
		LegoU32 nearestIndex;
		for (nearestIndex = 0; nearestIndex < racerCount; nearestIndex++) {
			Racer* racer = &m_unk0x0f0.m_racers[nearestIndex];
			if (racer != trackedRacer) {
				GolVec3 position;
				racer->m_unk0x018.m_unk0x044->VTable0x04(&position);

				LegoFloat deltaX = trackedPosition.m_x - position.m_x;
				LegoFloat deltaY = trackedPosition.m_y - position.m_y;
				LegoFloat deltaZ = trackedPosition.m_z - position.m_z;
				LegoFloat distanceSquared = deltaZ * deltaZ + deltaY * deltaY + deltaX * deltaX;
				if (distanceSquared < nearestDistanceSquared) {
					nearestDistanceSquared = distanceSquared;
					nearestRacer = racer;
				}
			}
		}

		if (nearestDistanceSquared >= g_unk0x004b0a20 * g_unk0x004b0a20) {
			if (sound->IsPlaying()) {
				sound->Stop();
				return;
			}
		}
		else {
			if (!sound->IsPlaying()) {
				sound->Play(TRUE);
			}

			GolVec3 position;
			nearestRacer->m_unk0x018.m_unk0x044->VTable0x04(&position);
			sound->SetPosition(position);

			GolVec3 velocity = nearestRacer->m_unk0x3e8.m_unk0x008;
			velocity.m_x *= 2.0f;
			velocity.m_y *= 2.0f;
			velocity.m_z *= 2.0f;
			sound->SetVelocity(velocity);

			LegoFloat frequencyScale = nearestRacer->m_unk0x3e8.m_unk0x604 / g_unk0x004b0a10;
			frequencyScale *= 1.0f - g_unk0x004b0a08 - g_unk0x004b0a0c;
			frequencyScale *= nearestRacer->m_unk0xd54;
			frequencyScale += g_unk0x004b0a08;

			if (frequencyScale < 0.0f) {
				frequencyScale = 0.0f;
			}
			else if (frequencyScale > 1.0f) {
				frequencyScale = 1.0f;
			}

			if (nearestRacer->m_unk0xd50 > Racer::c_boostSoundElapsedThreshold) {
				frequencyScale += g_unk0x004b02e0;
			}

			sound->SetFrequencyScale(frequencyScale);
		}
	}
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

// FUNCTION: LEGORACERS 0x0043ccb0
void RaceState::FUN_0043ccb0()
{
	for (LegoU32 i = 0; i < m_unk0x0f0.m_racerCount; i++) {
		m_unk0x0f0.m_racers[i].FUN_00439340();
	}

	SpatialSoundInstance* sound = m_unk0x0f0.m_soundSource->FUN_00443bd0(0x4f);
	m_unk0x0f0.m_sound = sound;
	if (sound) {
		LegoFloat maxDistance = g_unk0x004b0a20;
		sound->m_minDistanceSquared = g_unk0x004b0a18 * g_unk0x004b0a18;
		sound->m_maxDistanceSquared = maxDistance * maxDistance;
		m_unk0x0f0.m_sound->SetVolume(0.8f);
	}
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

// FUNCTION: LEGORACERS 0x0043d5a0
RaceState::Racer::Field0x018::Field0x018()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0043d620
RaceState::Racer::Field0x018::~Field0x018()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0043d6a0
void RaceState::Racer::Field0x018::Reset()
{
	m_unk0x03c = NULL;
	m_unk0x040 = NULL;
	m_unk0x044 = NULL;
	m_unk0x048 = NULL;
	m_racer = NULL;
	m_unk0x058.m_x = 0.0f;
	m_unk0x058.m_y = 0.0f;
	m_unk0x058.m_z = -1.0f;
	m_unk0x064 = NULL;
	m_unk0x1dc = NULL;
	m_unk0x000 = 0;
	m_unk0x04c.m_x = 0.0f;
	m_unk0x04c.m_y = 0.0f;
	m_unk0x04c.m_z = 0.0f;

	for (LegoU32 i = 0; i < sizeOfArray(m_unk0x1e4); i++) {
		m_unk0x1f4[i] = 0;
		m_unk0x1f8[i] = 0;
		m_unk0x208[i] = 0;
		m_unk0x1a8[i].m_x = 0.0f;
		m_unk0x1a8[i].m_y = 0.0f;
		m_unk0x1a8[i].m_z = 0.0f;
		m_unk0x1e4[i] = NULL;
		m_unk0x230[i] = NULL;
		m_unk0x260[i] = 0;
		m_unk0x240[i][0] = 0;
	}

	m_unk0x270 = NULL;
	m_unk0x278 = NULL;
	m_unk0x274 = NULL;
	m_unk0x27c = NULL;
	m_unk0x280 = NULL;
	m_unk0x1e0 = NULL;
	m_unk0x378 = 0;
	m_unk0x37c = 0;
	m_unk0x380 = NULL;
	m_unk0x390 = 0;
	m_unk0x394 = 0;
	m_unk0x398 = 0;
	m_unk0x39c = 0;
	m_unk0x38c = 0;
	m_unk0x384 = 0;
	m_unk0x388 = 0;
	m_unk0x3c0 = 0;
	m_unk0x3c4 = 0;
	m_unk0x3c8 = 0;
	m_unk0x3cc = 4;
}

// FUNCTION: LEGORACERS 0x0043d7a0
void RaceState::Racer::Field0x018::FUN_0043d7a0(InitParams* p_params, RaceState::Field0x3b190Params0x08* p_context)
{
	if (m_unk0x000 & c_alphaOverrideFlag) {
		Destroy();
	}

	m_unk0x03c = p_params->m_unk0x00;
	m_unk0x040 = p_params->m_unk0x04;
	m_unk0x044 = p_params->m_unk0x08;
	m_unk0x048 = p_params->m_unk0x0c;
	m_unk0x04c = p_params->m_unk0x10;
	m_unk0x064 = p_context->m_unk0x08;
	Racer* racer = p_params->m_racer;
	m_racer = racer;
	m_racerField0x3e8 = &racer->m_unk0x3e8;
	m_unk0x27c = p_context->m_unk0x1c;
	m_unk0x280 = p_context->m_unk0x20;
	m_unk0x1e0 = p_context->m_unk0x24;
	m_unk0x000 = c_alphaOverrideFlag | c_flags0x000Bit1;
	if (p_context->m_unk0x30) {
		m_unk0x000 = c_alphaOverrideFlag | c_flags0x000Bit1 | c_flags0x000Bit2;
	}

	m_unk0x198 = p_params->m_unk0x20;
	m_unk0x19c = p_params->m_unk0x24;
	m_unk0x1a0 = p_params->m_unk0x28;
	m_unk0x1a4 = p_params->m_unk0x2c;
	::strncpy(m_unk0x074, p_params->m_materialName, sizeof(m_unk0x074));

	m_unk0x218.Initialize(p_context->m_renderer, 1);
	m_unk0x218.AssignEntryByName(0, m_unk0x074);
	m_unk0x224.Initialize(p_context->m_renderer, 1);
	m_unk0x224.AssignEntryByName(0, "skid");

	g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
	m_unk0x388 = g_unk0x004befec[g_unk0x004c6ee4] % 2000;

	for (LegoU32 i = 0; i < sizeOfArray(m_unk0x1a8); i++) {
		m_unk0x1a8[i] = p_params->m_unk0x38[i];
	}

	m_unk0x044->FUN_0040dad0(0);
	m_unk0x044->SetFlags(m_unk0x044->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);

	if (m_unk0x040) {
		m_unk0x040->FUN_0040dad0(0);
		m_unk0x040->SetFlags(m_unk0x040->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	}

	m_unk0x048->FUN_0040dad0(9);
	m_unk0x048->SetFlags(m_unk0x048->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);

	if (p_context->m_flags0x3c & 0x200) {
		m_unk0x000 |= c_flags0x000Bit10;
	}
	if (p_context->m_flags0x3c & 0x400) {
		m_unk0x000 |= c_flags0x000Bit11;
	}
	if (p_context->m_flags0x3c & 0x800) {
		m_unk0x000 |= c_flags0x000Bit12;
	}

	FUN_00440030();
}

// FUNCTION: LEGORACERS 0x0043d990
void RaceState::Racer::Field0x018::FUN_0043d990(GolD3DRenderDevice* p_renderer, GolExport* p_golExport)
{
	for (LegoU32 i = 0; i < sizeOfArray(m_unk0x068); i++) {
		m_unk0x068[i] = m_unk0x03c->GetModelDistance(i);
	}

	FUN_0043e620();
	FUN_0043ff20(p_renderer);
	m_unk0x07c.FUN_00414950(p_golExport, p_renderer, 0x10);
	m_unk0x07c.GetUnk0x010().EnableFlagBit1();
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

// FUNCTION: LEGORACERS 0x0043da50
void RaceState::Racer::Field0x018::Destroy()
{
	m_unk0x284.VTable0x54();
	m_unk0x07c.FUN_004149f0();
	m_unk0x224.Clear();
	m_unk0x218.Clear();

	if (m_unk0x274) {
		m_unk0x27c->FUN_00489f00(m_unk0x274);
		m_unk0x274 = NULL;
	}

	if (m_unk0x278) {
		m_unk0x27c->FUN_00489f00(m_unk0x278);
		m_unk0x278 = NULL;
	}

	if (m_unk0x270) {
		m_unk0x27c->FUN_00489f00(m_unk0x270);
		m_unk0x270 = NULL;
	}

	for (LegoU32 i = 0; i < sizeOfArray(m_unk0x230); i++) {
		CutsceneParticleRef* particleRef = m_unk0x230[i];
		if (particleRef) {
			if (m_unk0x260[i]) {
				m_unk0x27c->FUN_00489f00(particleRef);
			}
			else {
				m_unk0x280->FUN_00489f00(particleRef);
			}

			m_unk0x230[i] = NULL;
			m_unk0x240[i][0] = 0;
		}
	}

	m_unk0x27c = NULL;
	m_unk0x07c.FUN_004149f0();
	m_unk0x224.Clear();
	m_unk0x218.Clear();
	Reset();
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

// FUNCTION: LEGORACERS 0x0043dbb0
void RaceState::Racer::Field0x018::FUN_0043dbb0()
{
	m_unk0x000 &= ~c_flags0x000Bit1;

	for (LegoU32 i = 0; i < sizeOfArray(m_unk0x068); i++) {
		m_unk0x03c->SetModelDistance(i, g_unk0x004b0ac0);
		m_unk0x044->SetModelDistance(i, g_unk0x004b0ac0);
		m_unk0x048->SetModelDistance(i, g_unk0x004b0ac0);

		if (m_unk0x040) {
			m_unk0x040->SetModelDistance(i, g_unk0x004b0ac0);
		}
	}
}

// FUNCTION: LEGORACERS 0x0043dc00
void RaceState::Racer::Field0x018::FUN_0043dc00()
{
	if (!(m_racer->m_unk0xd04 & c_racerFlags0xd04Bit3)) {
		for (LegoU32 i = 0; i < sizeOfArray(m_unk0x1f4); i++) {
			if ((m_unk0x1dc->m_flags0x6c0 & Field0x1dc::c_flags0x6c0Bit1) || i >= 2) {
				m_unk0x1f4[i] = TRUE;
			}
			else {
				m_unk0x1f4[i] &= ~(c_slotFlagsBit0 | c_slotFlagsBit1);
			}
		}

		if (!m_unk0x274) {
			m_unk0x274 = m_unk0x27c->FUN_00489d70("tiresmk", NULL, NULL, NULL);

			if (m_unk0x274) {
				GolVec3 position = m_unk0x1dc->m_unk0x1a4[3].m_unk0x000;
				GolAnimatedEntity* entity = m_unk0x044;
				if (m_unk0x274->m_unk0x00) {
					entity->VTable0x44(m_unk0x274->m_unk0x00->GetUnk0x160());
				}

				if (m_unk0x274->m_unk0x00) {
					m_unk0x274->m_unk0x00->FUN_00489660(&position);
				}
			}
		}

		m_unk0x000 |= c_flags0x000Bit3;
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

// FUNCTION: LEGORACERS 0x0043de90
void RaceState::Racer::Field0x018::FUN_0043de90(LegoU32 p_unk0x04)
{
	if (m_unk0x230[p_unk0x04]) {
		m_unk0x240[p_unk0x04][0] = 0;
		if (m_unk0x260[p_unk0x04]) {
			m_unk0x27c->FUN_00489f00(m_unk0x230[p_unk0x04]);
		}
		else {
			m_unk0x280->FUN_00489f00(m_unk0x230[p_unk0x04]);
		}
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

// STUB: LEGORACERS 0x0043e070
void RaceState::Racer::Field0x018::FUN_0043e070(LegoU32 p_elapsedMs)
{
	FUN_0043e740(p_elapsedMs);
	FUN_0043ec10(p_elapsedMs);
	m_unk0x004.VTable0x00();

	if (m_unk0x3c4) {
		if (p_elapsedMs >= m_unk0x3c8) {
			FUN_00440130();
		}
		else {
			m_unk0x3c8 -= p_elapsedMs;
		}
	}

	if (!(m_racer->m_unk0xd04 & c_racerFlags0xd04Bit4)) {
		if (m_unk0x1dc->m_flags0x6c0 & Field0x1dc::c_flags0x6c0Bit1) {
			if (!(m_unk0x000 & c_flags0x000Bit8)) {
				FUN_0043fd90();
			}
		}
		else if (m_unk0x000 & c_flags0x000Bit8) {
			FUN_0043fdb0();
		}

		for (LegoU32 slotIndex = 0; slotIndex < sizeOfArray(m_unk0x1f4); slotIndex++) {
			if (m_unk0x1f4[slotIndex] & c_slotFlagsBit2) {
				LegoU32 elapsed = m_unk0x208[slotIndex] + p_elapsedMs;
				m_unk0x208[slotIndex] = elapsed;

				if (elapsed > 1000) {
					m_unk0x1f4[slotIndex] &= ~c_slotFlagsBit2;
					m_unk0x208[slotIndex] = 0;
				}
			}
		}

		if ((m_racer->m_unk0xd04 & c_racerFlags0xd04Bit3) && (m_unk0x000 & c_flags0x000Bit3)) {
			FUN_0043dcd0();
		}

		FUN_0043f1e0(p_elapsedMs);

		if (m_racer->m_unk0xd04 & c_racerFlags0xd04Bit11) {
			FUN_0043f530(p_elapsedMs);
		}
		else {
			m_unk0x37c = 1000;
		}

		GolVec3 velocity = m_unk0x1dc->m_unk0x008 * 0.5f;

		for (LegoU32 particleIndex = 0; particleIndex < sizeOfArray(m_unk0x230); particleIndex++) {
			CutsceneParticleRef* ref = m_unk0x230[particleIndex];
			if (ref) {
				GolVec3 position = m_unk0x1dc->m_unk0x1a4[particleIndex].m_unk0x000;
				CutsceneParticle* particle = ref->m_unk0x00;

				if (particle) {
					m_unk0x044->VTable0x44(particle->GetUnk0x160());
				}

				if (ref->m_unk0x00) {
					ref->m_unk0x00->FUN_00489660(&position);
				}

				if (ref->m_unk0x00) {
					ref->m_unk0x00->FUN_00489690(&velocity);
				}
			}
		}

		if (m_racer->m_unk0x3e8.m_unk0x6dc > 400) {
			m_unk0x000 |= c_flags0x000Bit9;
		}

		if (m_unk0x000 & c_flags0x000Bit9) {
			LegoU32 state = m_racer->m_unk0x3e8.m_unk0x36c;
			if (m_unk0x3cc < state) {
				m_unk0x000 &= ~c_flags0x000Bit9;

				SoundVector position;
				m_unk0x044->VTable0x04(&position);

				switch (state - m_unk0x3cc) {
				case 1:
					m_racer->m_unk0x004->FUN_00443b80(0x3f, &position, g_unk0x004b0958, g_unk0x004b095c, 1.0f, 1.0f);
					break;
				case 2:
				case 3:
					m_racer->m_unk0x004->FUN_00443b80(0x40, &position, g_unk0x004b0958, g_unk0x004b095c, 1.0f, 1.0f);
					break;
				case 4:
					m_racer->m_unk0x004->FUN_00443b80(4, &position, g_unk0x004b0958, g_unk0x004b095c, 1.0f, 1.0f);
					break;
				}

				m_unk0x27c->FUN_00489d70("carland", &position, NULL, NULL);
			}

			m_unk0x3cc = state;
		}

		if (m_unk0x270) {
			CutsceneParticle* particle = m_unk0x270->m_unk0x00;
			if (particle && particle->GetSpawnedCount() >= 10) {
				m_unk0x27c->FUN_00489f30(m_unk0x270);
				m_unk0x270 = NULL;
			}
			else {
				g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
				GolVec3 position = (g_unk0x004befec[g_unk0x004c6ee4] & 2) ? m_unk0x1dc->m_unk0x1a4[3].m_unk0x000
																		  : m_unk0x1dc->m_unk0x1a4[2].m_unk0x000;

				particle = m_unk0x270->m_unk0x00;
				if (particle) {
					m_unk0x044->VTable0x44(particle->GetUnk0x160());
				}

				if (m_unk0x270->m_unk0x00) {
					m_unk0x270->m_unk0x00->FUN_00489660(&position);
				}

				if (m_unk0x270->m_unk0x00) {
					m_unk0x270->m_unk0x00->FUN_00489690(&velocity);
				}
			}
		}

		if (m_unk0x278) {
			CutsceneParticle* particle = m_unk0x278->m_unk0x00;
			if (particle && particle->GetSpawnedCount() >= 4) {
				m_unk0x27c->FUN_00489f30(m_unk0x278);
				m_unk0x278 = NULL;
			}
			else {
				GolVec3 position = m_unk0x1dc->m_unk0x1a4[3].m_unk0x000;
				GolVec3 other = m_unk0x1dc->m_unk0x1a4[2].m_unk0x000;
				position.m_x = (position.m_x + other.m_x) * 0.5f;
				position.m_y = (position.m_y + other.m_y) * 0.5f;
				position.m_z = (position.m_z + other.m_z) * 0.5f + g_violetShoalTwo;

				particle = m_unk0x278->m_unk0x00;
				if (particle) {
					m_unk0x044->VTable0x44(particle->GetUnk0x160());
				}

				if (m_unk0x278->m_unk0x00) {
					m_unk0x278->m_unk0x00->FUN_00489660(&position);
				}

				if (m_unk0x278->m_unk0x00) {
					m_unk0x278->m_unk0x00->FUN_00489690(&velocity);
				}
			}
		}

		if (m_unk0x274) {
			GolVec3 position;
			position.m_x = 0.0f;
			position.m_y = 0.0f;
			position.m_z = 0.0f;

			g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
			LegoBool32 chooseSecond = (g_unk0x004befec[g_unk0x004c6ee4] >> 1) & 1;
			LegoBool32 found = FALSE;

			for (LegoU32 tireIndex = 0; tireIndex < sizeOfArray(m_unk0x1f4); tireIndex++) {
				if (m_unk0x1f4[tireIndex] & c_slotFlagsBit1) {
					if (!chooseSecond || !found) {
						position = m_unk0x1dc->m_unk0x1a4[tireIndex].m_unk0x000;
						found = TRUE;
					}
					else {
						break;
					}
				}
			}

			CutsceneParticle* particle = m_unk0x274->m_unk0x00;
			if (particle) {
				m_unk0x044->VTable0x44(particle->GetUnk0x160());
			}

			if (m_unk0x274->m_unk0x00) {
				m_unk0x274->m_unk0x00->FUN_00489660(&position);
			}

			if (m_unk0x274->m_unk0x00) {
				m_unk0x274->m_unk0x00->FUN_00489690(&velocity);
			}
		}
	}

	m_unk0x000 &= ~c_flags0x000Bit4;
}

// FUNCTION: LEGORACERS 0x0043e620
void RaceState::Racer::Field0x018::FUN_0043e620()
{
	m_unk0x044->CopyOrientationAndPositionTo(m_unk0x03c);

	GolVec3 position;
	m_unk0x03c->VTable0x2c(m_unk0x04c, &position);
	m_unk0x048->VTable0x08(position);
	m_unk0x048->CopyOrientationFrom(*m_unk0x03c);

	if (m_unk0x040 != NULL) {
		m_unk0x044->CopyOrientationAndPositionTo(m_unk0x040);
	}
}

// FUNCTION: LEGORACERS 0x0043e740
void RaceState::Racer::Field0x018::FUN_0043e740(LegoS32 p_elapsedMs)
{
	GolVec3 position;
	m_unk0x044->VTable0x04(&position);

	const GolMatrix3& oldOrientation = m_unk0x044->GetOrientation();
	GolVec3 oldRow0;
	GolVec3 oldRow1;
	GolVec3 oldRow2;
	oldRow0.m_x = oldOrientation.m_m[0][0];
	oldRow0.m_y = oldOrientation.m_m[0][1];
	oldRow0.m_z = oldOrientation.m_m[0][2];
	oldRow1.m_x = oldOrientation.m_m[1][0];
	oldRow1.m_y = oldOrientation.m_m[1][1];
	oldRow1.m_z = oldOrientation.m_m[1][2];
	oldRow2.m_x = oldOrientation.m_m[2][0];
	oldRow2.m_y = oldOrientation.m_m[2][1];
	oldRow2.m_z = oldOrientation.m_m[2][2];
	m_unk0x044->VTable0x10(p_elapsedMs);

	const GolVec3& modelRow2 = m_unk0x03c->GetOrientation().m_rows[2];
	GolVec3 targetRow0;
	targetRow0.m_x = oldRow1.m_y * modelRow2.m_z - oldRow1.m_z * modelRow2.m_y;
	targetRow0.m_y = oldRow1.m_z * modelRow2.m_x - oldRow1.m_x * modelRow2.m_z;
	targetRow0.m_z = oldRow1.m_x * modelRow2.m_y - oldRow1.m_y * modelRow2.m_x;

	LegoFloat length = static_cast<LegoFloat>(sqrt(
		(oldRow0.m_z - targetRow0.m_z) * (oldRow0.m_z - targetRow0.m_z) +
		(oldRow0.m_y - targetRow0.m_y) * (oldRow0.m_y - targetRow0.m_y) +
		(oldRow0.m_x - targetRow0.m_x) * (oldRow0.m_x - targetRow0.m_x)
	));
	if (targetRow0.m_z * oldRow2.m_z + targetRow0.m_y * oldRow2.m_y + targetRow0.m_x * oldRow2.m_x < 0.0f) {
		length = -length;
	}

	LegoFloat elapsed = static_cast<LegoFloat>(p_elapsedMs);
	LegoFloat scale = g_unk0x004b0b28;
	scale = -scale;
	m_unk0x398 += (scale * length) * elapsed / m_racerField0x3e8->m_unk0x0c8;
	LegoFloat decay = elapsed;
	decay *= g_unk0x004b0b30;
	decay *= m_unk0x398;
	if ((m_unk0x398 > 0.0f && decay < m_unk0x398) || (m_unk0x398 < 0.0f && decay > m_unk0x398)) {
		m_unk0x398 -= decay;
	}
	else {
		m_unk0x398 = 0.0f;
	}

	GolVec3 targetRow1;
	targetRow1.m_x = modelRow2.m_y * oldRow0.m_z - modelRow2.m_z * oldRow0.m_y;
	targetRow1.m_y = modelRow2.m_z * oldRow0.m_x - modelRow2.m_x * oldRow0.m_z;
	targetRow1.m_z = modelRow2.m_x * oldRow0.m_y - modelRow2.m_y * oldRow0.m_x;

	length = static_cast<LegoFloat>(sqrt(
		(oldRow1.m_z - targetRow1.m_z) * (oldRow1.m_z - targetRow1.m_z) +
		(oldRow1.m_y - targetRow1.m_y) * (oldRow1.m_y - targetRow1.m_y) +
		(oldRow1.m_x - targetRow1.m_x) * (oldRow1.m_x - targetRow1.m_x)
	));
	if (targetRow1.m_z * oldRow2.m_z + targetRow1.m_y * oldRow2.m_y + targetRow1.m_x * oldRow2.m_x < 0.0f) {
		length = -length;
	}

	scale = g_unk0x004b0b2c;
	scale = -scale;
	m_unk0x39c += (scale * length) * elapsed / m_racerField0x3e8->m_unk0x0c8;
	decay = elapsed;
	decay *= g_unk0x004b0b34;
	decay *= m_unk0x39c;
	if ((m_unk0x39c > 0.0f && decay < m_unk0x39c) || (m_unk0x39c < 0.0f && decay > m_unk0x39c)) {
		m_unk0x39c -= decay;
	}
	else {
		m_unk0x39c = 0.0f;
	}

	GolVec3 row0;
	if (m_unk0x398 == 0.0f) {
		row0 = oldRow0;
	}
	else {
		LegoFloat value = m_unk0x398;
		oldRow0.m_x = oldRow2.m_x * value;
		oldRow0.m_y = oldRow2.m_y * value;
		oldRow0.m_z = oldRow2.m_z * value;
		GolCameraBase::FUN_00404550(&targetRow0, &oldRow0, &row0);
	}

	GolVec3 row1;
	if (m_unk0x39c == 0.0f) {
		row1 = oldRow1;
	}
	else {
		LegoFloat value = m_unk0x39c;
		oldRow1.m_x = oldRow2.m_x * value;
		oldRow1.m_y = oldRow2.m_y * value;
		oldRow1.m_z = oldRow2.m_z * value;
		GolCameraBase::FUN_00404550(&targetRow1, &oldRow1, &row1);
	}

	m_unk0x03c->VTable0x08(position);
	m_unk0x03c->FUN_00410a00(row0, row1);

	if (m_unk0x040 != NULL) {
		m_unk0x03c->CopyOrientationAndPositionTo(m_unk0x040);
		m_unk0x040->VTable0x10(p_elapsedMs);
	}

	m_unk0x03c->VTable0x2c(m_unk0x04c, &position);
	m_unk0x048->VTable0x08(position);
	m_unk0x048->FUN_0043ebd0(*m_unk0x03c);
}

// FUNCTION: LEGORACERS 0x0043ebd0
void GolOrientedEntity::FUN_0043ebd0(const GolOrientedEntity& p_other)
{
	m_orientation.m_m[0][0] = p_other.m_orientation.m_m[0][0];
	m_orientation.m_m[0][1] = p_other.m_orientation.m_m[0][1];
	m_orientation.m_m[0][2] = p_other.m_orientation.m_m[0][2];
	m_orientation.m_m[1][0] = p_other.m_orientation.m_m[1][0];
	m_orientation.m_m[1][1] = p_other.m_orientation.m_m[1][1];
	m_orientation.m_m[1][2] = p_other.m_orientation.m_m[1][2];
	m_orientation.m_m[2][0] = p_other.m_orientation.m_m[2][0];
	m_orientation.m_m[2][1] = p_other.m_orientation.m_m[2][1];
	m_orientation.m_m[2][2] = p_other.m_orientation.m_m[2][2];
}

// FUNCTION: LEGORACERS 0x0043ec10
void RaceState::Racer::Field0x018::FUN_0043ec10(LegoU32 p_elapsedMs)
{
	Field0xc70* field0xc70 = &m_racer->m_unk0xc70;
	LegoFloat activeValue = field0xc70->m_unk0x00c;
	LegoFloat speed = m_unk0x1dc->m_unk0x618;
	LegoU32 activePart = m_unk0x048->GetActiveState();
	LegoU32 eventFlags = m_unk0x384;

	m_unk0x048->VTable0x10(p_elapsedMs);
	m_unk0x384 = 0;

	if (p_elapsedMs < m_unk0x388) {
		m_unk0x388 -= p_elapsedMs;
	}
	else {
		m_unk0x388 = 0;
	}

	if (m_racer->m_lapsCompleted >= g_unk0x004bef70) {
		if (m_racer->m_lapTimes[5] == 1) {
			if (activePart == c_animationPart13 || activePart == c_animationPart15 || activePart == c_animationPart14) {
				return;
			}

			g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
			if (g_unk0x004befec[g_unk0x004c6ee4] % 2 != 0) {
				m_unk0x048->FUN_0040dad0(c_animationPart14);
				m_unk0x048->QueuePartTransition(c_animationPart15);
			}
			else {
				m_unk0x048->FUN_0040dad0(c_animationPart13);
			}
			return;
		}

		if (activePart == c_animationPart12 || activePart == c_animationPart11) {
			return;
		}

		m_unk0x048->FUN_0040dad0(c_animationPart11);
		m_unk0x048->QueuePartTransition(c_animationPart12);
		return;
	}

	if (m_unk0x38c > g_unk0x004b0544 && speed < g_carBuildPreviewMouseScale && activePart != c_animationPart0) {
		m_racer->FUN_00439240(FALSE);
		m_unk0x048->FUN_0040dad0(c_animationPart0);
		m_unk0x048->QueuePartTransition(c_animationPart9);
		m_unk0x38c = 0.0f;

		if (m_racer->m_unk0x014 != NULL) {
			m_racer->m_unk0x014->FUN_004220c0();
		}
		return;
	}

	m_unk0x38c = speed;

	if (eventFlags & c_flags0x384Bit0) {
		m_unk0x048->FUN_0040dad0(c_animationPart1);
		m_unk0x048->QueuePartTransition(c_animationPart9);
		return;
	}

	if (eventFlags & c_flags0x384Bit1) {
		m_unk0x048->FUN_0040dad0(c_animationPart10);
		m_unk0x048->QueuePartTransition(c_animationPart9);

		if (m_racer->m_unk0x014 != NULL) {
			m_racer->m_unk0x014->FUN_004220c0();
		}
		return;
	}

	if (activePart == c_animationPart0 || activePart == c_animationPart1 || activePart == c_animationPart10 ||
		activePart == c_animationPart13 || activePart == c_animationPart15 || activePart == c_animationPart12) {
		return;
	}

	if (field0xc70->m_unk0x010 < 0.0f && speed < 0.0f) {
		if (activePart == c_animationPart2 || activePart == c_animationPart3) {
			return;
		}

		m_unk0x048->FUN_0040dad0(c_animationPart2);
		m_unk0x048->QueuePartTransition(c_animationPart3);
		return;
	}

	if (activePart == c_animationPart3) {
		m_unk0x048->FUN_0040dad0(c_animationPart4);
		m_unk0x048->QueuePartTransition(c_animationPart9);
		return;
	}

	if (activePart == c_animationPart7 || activePart == c_animationPart16 || activePart == c_animationPart8 ||
		activePart == c_animationPart17) {
		return;
	}

	if (m_unk0x388 == 0) {
		GolVec3 position;
		m_unk0x044->VTable0x04(&position);

		Racer* racer = m_racer;
		RaceState* raceState = racer->m_unk0x00c;
		Racer* nearbyRacer = raceState->FUN_0043cbb0(&position, 2.0f, g_unk0x004b0b24);
		m_unk0x380 = nearbyRacer;

		if (nearbyRacer != NULL) {
			GolAnimatedEntity* nearbyEntity = nearbyRacer->m_unk0x018.m_unk0x044;
			GolVec3 row0 = m_unk0x044->GetOrientation().m_rows[0];
			GolVec3 row1 = m_unk0x044->GetOrientation().m_rows[1];

			GolVec3 nearbyPosition;
			nearbyEntity->VTable0x04(&nearbyPosition);

			GolVec3 direction;
			direction.m_x = nearbyPosition.m_x - position.m_x;
			direction.m_y = nearbyPosition.m_y - position.m_y;
			direction.m_z = nearbyPosition.m_z - position.m_z;
			GolMath::NormalizeVector3(direction, &direction);

			LegoFloat forwardDot = row0.m_z * direction.m_z + row0.m_y * direction.m_y + row0.m_x * direction.m_x;
			LegoU32 animationPart = 0;
			if (forwardDot < g_unk0x004b02e0 && forwardDot > g_unk0x004b0b44) {
				LegoFloat sideDot = row1.m_z * direction.m_z + row1.m_y * direction.m_y + row1.m_x * direction.m_x;
				animationPart = sideDot < 0.0f ? c_animationPart7 : c_animationPart16;
			}
			else if (forwardDot < g_unk0x004b02e0 && forwardDot > g_unk0x004b0b40) {
				LegoFloat sideDot = row1.m_z * direction.m_z + row1.m_y * direction.m_y + row1.m_x * direction.m_x;
				animationPart = sideDot < 0.0f ? c_animationPart8 : c_animationPart17;
			}

			if (animationPart) {
				g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
				m_unk0x388 =
					(g_unk0x004befec[g_unk0x004c6ee4] % c_avoidanceCooldownRangeMs) + c_avoidanceCooldownBaseMs;
				m_unk0x048->FUN_0040dad0(animationPart);
				m_unk0x048->QueuePartTransition(c_animationPart9);
				return;
			}
		}
	}

	if (activeValue < 0.0f) {
		if (activePart != c_animationPart5) {
			m_unk0x048->FUN_0040db80(c_animationPart5, c_animationTransitionMs, 0.0f, TRUE, TRUE, TRUE);
		}
		return;
	}

	if (activeValue > 0.0f) {
		if (activePart != c_animationPart6) {
			m_unk0x048->FUN_0040db80(c_animationPart6, c_animationTransitionMs, 0.0f, TRUE, TRUE, TRUE);
		}
		return;
	}

	if (activeValue == 0.0f && activePart != c_animationPart9) {
		m_unk0x048->FUN_0040db80(c_animationPart9, c_animationTransitionMs, 0.0f, TRUE, TRUE, TRUE);
	}
}

// STUB: LEGORACERS 0x0043f1e0
void RaceState::Racer::Field0x018::FUN_0043f1e0(LegoU32 p_elapsedMs)
{
	if (!(m_unk0x000 & c_flags0x000Bit3)) {
		return;
	}

	GolVec3 position;

	{
		for (LegoU32 i = 0; i < sizeOfArray(m_unk0x1f4); i++) {
			LegoU8 flags = m_unk0x1f4[i];
			if (flags & c_slotFlagsBit0) {
				if (!(flags & c_slotFlagsBit1) &&
					(m_unk0x1dc->m_unk0x1a4[i].m_flags0x03c & Field0x1dc::Field0x1a4::c_flags0x03cBit0)) {
					flags |= c_slotFlagsBit1;
					m_unk0x1f4[i] = flags;
				}
				else if (!(m_unk0x1dc->m_unk0x1a4[i].m_flags0x03c & Field0x1dc::Field0x1a4::c_flags0x03cBit0)) {
					LegoU32 elapsed = m_unk0x1f8[i] + p_elapsedMs;
					m_unk0x1f8[i] = elapsed;
					if (elapsed > 150) {
						m_unk0x1f4[i] &= ~c_slotFlagsBit1;
						m_unk0x1f8[i] = 0;
					}
				}
				else {
					m_unk0x1f8[i] = 0;
				}

				if (m_unk0x1e4[i]) {
					m_unk0x044->VTable0x2c(m_unk0x1a8[i], &position);
					m_unk0x1e4[i]->FUN_00491fa0(p_elapsedMs, position);
				}
			}
			else {
				m_unk0x1f4[i] = flags & ~c_slotFlagsBit1;
			}
		}
	}

	if (m_unk0x1dc->m_flags0x6c0 & Field0x1dc::c_flags0x6c0Bit1) {
		m_unk0x1f4[0] |= c_slotFlagsWithoutBit0;
		m_unk0x1f4[1] |= c_slotFlagsWithoutBit0;
		m_unk0x1f4[2] |= c_slotFlagsWithoutBit0;
		m_unk0x1f4[3] |= c_slotFlagsWithoutBit0;
	}
	else if (m_racer->m_unk0xd04 & c_racerFlags0xd04Bit6) {
		m_unk0x1f4[0] &= ~c_slotFlagsBit0;
		m_unk0x1f4[2] |= c_slotFlagsBit0;
		m_unk0x1f4[1] &= ~c_slotFlagsBit0;
		m_unk0x1f4[3] |= c_slotFlagsBit0;
	}
	else {
		GolVec3 slipDirection = m_unk0x1dc->m_unk0x5f8;
		const GolVec3& side = m_unk0x044->GetOrientation().m_rows[1];
		LegoFloat dot = slipDirection.m_y;
		dot *= side.m_y;
		dot += side.m_z * slipDirection.m_z;
		dot += side.m_x * slipDirection.m_x;
		if (dot > 0.0f) {
			m_unk0x1f4[0] &= ~c_slotFlagsBit0;
			m_unk0x1f4[2] &= ~c_slotFlagsBit0;
			m_unk0x1f4[1] |= c_slotFlagsBit0;
			m_unk0x1f4[3] |= c_slotFlagsBit0;
		}
		else {
			m_unk0x1f4[0] |= c_slotFlagsBit0;
			m_unk0x1f4[2] |= c_slotFlagsBit0;
			m_unk0x1f4[1] &= ~c_slotFlagsBit0;
			m_unk0x1f4[3] &= ~c_slotFlagsBit0;
		}
	}

	{
		RaceSessionField0x27d4::Item** itemSlot = m_unk0x1e4;
		LegoU32 i = 0;
		LegoU8 colorByte = 0xff;
		do {
			LegoU32 flags0x000Bit8 = m_unk0x000 & c_flags0x000Bit8;
			if (flags0x000Bit8) {
				RaceSessionField0x27d4::Item* item = *itemSlot;
				if (item && item->GetUnk0x314() == 1000) {
					m_unk0x1e0->FUN_00492820(item, 0);
					*itemSlot = NULL;
				}
			}
			else {
				RaceSessionField0x27d4::Item* item = *itemSlot;
				if (item && item->GetUnk0x314() == 250) {
					m_unk0x1e0->FUN_00492820(item, 0);
					*itemSlot = NULL;
				}
			}

			if (m_unk0x1f4[i] & c_slotFlagsBit0) {
				if (!*itemSlot) {
					if (m_unk0x000 & c_flags0x000Bit8) {
						*itemSlot = m_unk0x1e0->FUN_004927c0(250);
					}
					else {
						*itemSlot = m_unk0x1e0->FUN_004927c0(1000);
					}

					if (*itemSlot) {
						ColorRGBA color;
						color.m_red = colorByte;
						color.m_grn = colorByte;
						color.m_blu = colorByte;
						color.m_alp = colorByte;
						(*itemSlot)->FUN_00491d80(&color);
						(*itemSlot)->FUN_00491d20(&m_unk0x224);

						if (i == 0 || i == 1) {
							(*itemSlot)->SetUnk0x324(m_unk0x1a0);
						}
						else {
							(*itemSlot)->SetUnk0x324(m_unk0x1a4);
						}
					}
				}
			}
			else if (*itemSlot) {
				m_unk0x1e0->FUN_00492820(*itemSlot, 0);
				*itemSlot = NULL;
			}
			i++;
			itemSlot++;
		} while (i < sizeOfArray(m_unk0x1e4));
	}
}

// STUB: LEGORACERS 0x0043f530
void RaceState::Racer::Field0x018::FUN_0043f530(LegoU32 p_elapsedMs)
{
	if (p_elapsedMs > m_unk0x378) {
		m_unk0x378 = 1000;
	}
	else {
		m_unk0x378 -= p_elapsedMs;
	}

	if (p_elapsedMs > m_unk0x37c) {
		m_unk0x37c = 0;
	}
	else {
		m_unk0x37c -= p_elapsedMs;
	}

	LegoFloat phase = static_cast<LegoFloat>(m_unk0x378) * g_unk0x004c6b34;
	LegoS32 tableIndex = (0xffffff00 - static_cast<LegoS32>(phase * g_negativeRadiansToTableIndex)) & c_randomTableMask;
	LegoFloat offsetX = g_cosineTable[tableIndex];
	tableIndex = static_cast<LegoS32>(phase * g_item0x40RadiansToTableIndex) & c_randomTableMask;
	LegoFloat offsetY = g_cosineTable[tableIndex];

	GolModelEntity* entity = &m_unk0x284;
	GolVec3 position;
	entity->VTable0x04(&position);

	GolVec3 target;
	m_unk0x03c->VTable0x04(&target);
	target.m_x += 6.0f * offsetX;
	target.m_y += 6.0f * offsetY;
	target.m_z += 9.0f;

	LegoFloat speed = m_unk0x1dc->m_unk0x604;
	if (speed <= 0.1f) {
		speed = 0.1f;
	}

	LegoFloat elapsed = static_cast<LegoFloat>(p_elapsedMs);
	LegoFloat maxMove = elapsed * speed;
	GolVec3 delta;
	delta.m_x = target.m_x - position.m_x;
	delta.m_y = target.m_y - position.m_y;
	delta.m_z = target.m_z - position.m_z;

	if (delta.m_z * delta.m_z + delta.m_y * delta.m_y + delta.m_x * delta.m_x > maxMove * maxMove) {
		GolMath::NormalizeVector3(delta, &delta);
		position.m_x += delta.m_x * maxMove;
		position.m_y += delta.m_y * maxMove;
		position.m_z += delta.m_z * maxMove;
	}
	else {
		position = target;
	}
	entity->VTable0x08(position);

	GolVec3 up;
	up.m_x = 0.0f;
	up.m_y = 0.0f;
	up.m_z = 1.0f;

	m_unk0x03c->VTable0x04(&target);
	delta.m_x = target.m_x - position.m_x;
	delta.m_y = target.m_y - position.m_y;
	delta.m_z = target.m_z - position.m_z;
	GolMath::NormalizeVector3(delta, &delta);

	GolVec3 right;
	right.m_x = up.m_y * delta.m_z - up.m_z * delta.m_y;
	right.m_y = up.m_z * delta.m_x - up.m_x * delta.m_z;
	right.m_z = up.m_x * delta.m_y - up.m_y * delta.m_x;
	GolMath::NormalizeVector3(right, &right);

	if (m_unk0x37c > 0) {
		GolMatrix3 currentOrientation;
		entity->VTable0x44(&currentOrientation);
		GolVec3 unit;
		GolMath::NormalizeVector3(right, &unit);

		LegoFloat dot = unit.m_z * up.m_z + unit.m_y * up.m_y + unit.m_x * up.m_x;
		up.m_x -= unit.m_x * dot;
		up.m_y -= unit.m_y * dot;
		up.m_z -= unit.m_z * dot;
		GolMath::NormalizeVector3(up, &up);

		GolVec3 cross;
		cross.m_x = up.m_y * unit.m_z - up.m_z * unit.m_y;
		cross.m_y = up.m_z * unit.m_x - up.m_x * unit.m_z;
		cross.m_z = up.m_x * unit.m_y - up.m_y * unit.m_x;

		GolMatrix3 desiredOrientation;
		desiredOrientation.m_m[0][0] = unit.m_x;
		desiredOrientation.m_m[0][1] = unit.m_y;
		desiredOrientation.m_m[0][2] = unit.m_z;
		desiredOrientation.m_m[1][0] = cross.m_x;
		desiredOrientation.m_m[1][1] = cross.m_y;
		desiredOrientation.m_m[1][2] = cross.m_z;
		desiredOrientation.m_m[2][0] = up.m_x;
		desiredOrientation.m_m[2][1] = up.m_y;
		desiredOrientation.m_m[2][2] = up.m_z;

		LegoFloat amount = static_cast<LegoFloat>(m_unk0x37c) * 0.001f;
		GolQuat desiredRotation;
		GolQuat currentRotation;
		GolQuat blendedRotation;
		GolMath::FUN_1002f5a0(desiredOrientation, &desiredRotation);
		GolMath::FUN_1002f5a0(currentOrientation, &currentRotation);
		GolMath::FUN_1002f890(desiredRotation, currentRotation, amount, &blendedRotation);

		GolMatrix3 orientation;
		GolMath::FUN_00449340(&blendedRotation, &orientation.m_m[0][0]);
		entity->VTable0x3c(orientation);
	}
	else {
		entity->VTable0x40(right, up);
	}

	LegoFloat scale = entity->GetUnk0x58();
	if (scale > 0.66600001f) {
		scale -= elapsed * 0.0099999998f * 0.065999999f;
		if (scale < 0.66600001f) {
			scale = 0.66600001f;
		}
		entity->SetUnk0x58ThenInvalidateRadius(scale);
	}

	entity->VTable0x10(p_elapsedMs);
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

// FUNCTION: LEGORACERS 0x0043fbc0
void RaceState::Racer::Field0x018::FUN_0043fbc0(GolD3DRenderDevice* p_renderer)
{
	if (!(m_unk0x000 & c_flags0x000Bit10)) {
		p_renderer->VTable0x94(m_unk0x044);
	}

	if (!(m_unk0x000 & c_flags0x000Bit11)) {
		p_renderer->VTable0x94(m_unk0x03c);

		if (m_unk0x040) {
			p_renderer->VTable0x94(m_unk0x040);
		}
	}

	if (!(m_unk0x000 & c_flags0x000Bit12)) {
		p_renderer->VTable0x94(m_unk0x048);
	}
}

// FUNCTION: LEGORACERS 0x0043fc20
void RaceState::Racer::Field0x018::FUN_0043fc20(GolD3DRenderDevice* p_renderer)
{
	if (m_unk0x000 & c_flags0x000Bit4) {
		RaceSessionField0x27d4::Item::Field0x004* field = &m_unk0x07c;
		GolVec3 cameraPosition;
		p_renderer->GetUnk0x0c()->GetTransform()->GetPosition(&cameraPosition);

		GolVec3 position;
		LegoFloat deltaX = field->m_unk0x0e8.m_x;
		position.m_y = field->m_unk0x0e8.m_y;
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

// FUNCTION: LEGORACERS 0x0043fd30
void RaceState::Racer::Field0x018::FUN_0043fd30()
{
	if (m_racer->m_unk0xd08 != 2) {
		FUN_0043def0();
		FUN_0043df90();

		if (m_racer->m_unk0xd68 > 0) {
			FUN_0043da10();
			FUN_0043dc00();
		}
	}
}

// FUNCTION: LEGORACERS 0x0043fd70
void RaceState::Racer::Field0x018::FUN_0043fd70()
{
	FUN_0043dcd0();
	FUN_0043da30();
}

// FUNCTION: LEGORACERS 0x0043fd90
void RaceState::Racer::Field0x018::FUN_0043fd90()
{
	m_unk0x000 |= c_flags0x000Bit8;

	if (m_racer->m_unk0xd08 != 2) {
		FUN_0043dc00();
	}
}

// FUNCTION: LEGORACERS 0x0043fdb0
void RaceState::Racer::Field0x018::FUN_0043fdb0()
{
	m_unk0x000 &= ~c_flags0x000Bit8;
	FUN_0043dcd0();
}

// FUNCTION: LEGORACERS 0x0043fdc0
LegoBool32 RaceState::Racer::Field0x018::FUN_0043fdc0(const GolVec3* p_start, const GolVec3* p_end, GolVec3* p_hit)
{
	GolVec3 center;
	LegoFloat radius;
	m_unk0x03c->FUN_10027fe0(0, &center, &radius);
	LegoFloat radiusSquared = radius * radius;

	GolVec3 direction;
	direction.m_x = p_end->m_x - p_start->m_x;
	direction.m_y = p_end->m_y - p_start->m_y;
	direction.m_z = p_end->m_z - p_start->m_z;
	GolMath::NormalizeVector3(direction, &direction);

	LegoFloat centerDeltaX = center.m_x - p_start->m_x;
	LegoFloat centerDeltaY = center.m_y - p_start->m_y;
	LegoFloat centerDeltaZ = center.m_z - p_start->m_z;
	LegoFloat projection = centerDeltaZ * direction.m_z + centerDeltaY * direction.m_y + centerDeltaX * direction.m_x;
	LegoFloat discriminant =
		radiusSquared - ((centerDeltaY * centerDeltaY + centerDeltaZ * centerDeltaZ + centerDeltaX * centerDeltaX) -
						 projection * projection);
	if (discriminant <= 0.0f) {
		return FALSE;
	}

	LegoFloat distance = projection - static_cast<LegoFloat>(sqrt(discriminant));
	LegoFloat segmentDeltaX = p_start->m_x - p_end->m_x;
	LegoFloat segmentDeltaY = p_start->m_y - p_end->m_y;
	LegoFloat segmentDeltaZ = p_start->m_z - p_end->m_z;
	if (distance * distance >
		segmentDeltaZ * segmentDeltaZ + segmentDeltaY * segmentDeltaY + segmentDeltaX * segmentDeltaX) {
		return FALSE;
	}

	GolVec3 hitDelta;
	hitDelta.m_x = direction.m_x;
	hitDelta.m_x *= distance;
	hitDelta.m_y = direction.m_y;
	hitDelta.m_y *= distance;
	hitDelta.m_z = direction.m_z;
	hitDelta.m_z *= distance;
	p_hit->m_x = p_start->m_x + hitDelta.m_x;
	p_hit->m_y = p_start->m_y + hitDelta.m_y;
	p_hit->m_z = p_start->m_z + hitDelta.m_z;

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0043ff20
void RaceState::Racer::Field0x018::FUN_0043ff20(GolD3DRenderDevice* p_renderer)
{
	DuskwindBananaRelic0x24* material = p_renderer->FindMaterialByName(m_unk0x074);
	g_racerBillboardRenderState0x33c.FUN_004097c0(p_renderer, material->GetUnk0x04());

	GolVec3 position;
	m_unk0x044->VTable0x04(&position);
	LegoFloat origin[2];
	origin[0] = position.m_x;
	origin[1] = position.m_y;

	ColorRGBA color = {0, 0, 0, 0};
	g_racerBillboardRenderState0x33c.FUN_00409850(&color);

	color.m_red = 8;
	color.m_grn = 8;
	color.m_blu = 8;
	color.m_alp = 0xff;
	g_racerBillboardRenderState0x33c.FUN_004098a0(&color);

	LegoFloat unk0x0c = m_unk0x198;
	unk0x0c *= 1.15f;
	LegoFloat unk0x08 = m_unk0x19c;
	unk0x08 *= 1.15f;
	g_racerBillboardRenderState0x33c.FUN_004098f0(origin, unk0x08, unk0x0c, g_unk0x004bef68 | g_unk0x004bef6c);
	g_racerBillboardRenderState0x33c.FUN_00409970(m_unk0x044, 0);
	g_racerBillboardRenderState0x33c.FUN_00409970(m_unk0x03c, 0);

	if (m_unk0x040) {
		g_racerBillboardRenderState0x33c.FUN_00409970(m_unk0x040, 0);
	}

	g_racerBillboardRenderState0x33c.FUN_004099d0();
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

// FUNCTION: LEGORACERS 0x004401b0
void RaceState::Racer::Field0x018::FUN_004401b0()
{
	if (m_unk0x044->GetActiveState()) {
		m_unk0x044->FUN_0040dad0(0);
	}
}

// FUNCTION: LEGORACERS 0x004401e0
void RaceState::Racer::Field0x018::FUN_004401e0()
{
	CmbModelPart0x34* modelPart = m_unk0x044->GetModelPart();

	if (modelPart->GetPartCount() > 1 && m_unk0x044->GetActiveState() != 1) {
		m_unk0x044->FUN_0040dad0(1);
	}
}
