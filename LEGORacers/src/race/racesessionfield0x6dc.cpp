#include "audio/spatialsoundinstance.h"
#include "cmbmodelpart0x34.h"
#include "decomp.h"
#include "golbinparser.h"
#include "golmateriallibrary.h"
#include "golworldentity.h"
#include "race/racesession.h"
#include "render/gold3drenderdevice.h"
#include "world/golworlddatabase.h"

#include <float.h>
#include <golerror.h>

DECOMP_SIZE_ASSERT(RacePowerupManager, 0x19a4)
DECOMP_SIZE_ASSERT(RacePowerupManager::Field0x54, 0x04)
DECOMP_SIZE_ASSERT(RacePowerupManager::Field0x68, 0x54)
DECOMP_SIZE_ASSERT(RacePowerupManager::Field0x68Field0x028, 0x68)
DECOMP_SIZE_ASSERT(RacePowerupManager::Field0x68Field0x02c, 0x68)
DECOMP_SIZE_ASSERT(RacePowerupManager::PwbTxtParser, 0x1fc)
DECOMP_SIZE_ASSERT(RacePowerupManager::Field0x1958Resource, 0x30)
DECOMP_SIZE_ASSERT(RacePowerupManager::Field0x18bc, 0x80)
DECOMP_SIZE_ASSERT(RacePowerupManager::Field0x18bc::Entry, 0x14)
DECOMP_SIZE_ASSERT(RacePowerupManager::Field0x050::Entry, 0x14)
DECOMP_SIZE_ASSERT(RacePowerupManager::Field0x1890, 0x84)
DECOMP_SIZE_ASSERT(RacePowerupManager::Field0x1894, 0x190)
DECOMP_SIZE_ASSERT(RacePowerupManager::Field0x1898, 0x17c)
DECOMP_SIZE_ASSERT(RacePowerupManager::Field0x189c, 0x68)
DECOMP_SIZE_ASSERT(RacePowerupManager::ResourceBase, 0x18)
DECOMP_SIZE_ASSERT(RacePowerupManager::ResourceBase0x2c, 0x2c)
DECOMP_SIZE_ASSERT(RacePowerupManager::ResourceBase0x30, 0x30)
DECOMP_SIZE_ASSERT(RacePowerupManager::Field0x18a0, 0xe8)
DECOMP_SIZE_ASSERT(RacePowerupManager::Field0x18a4, 0x290)
DECOMP_SIZE_ASSERT(RacePowerupManager::Field0x18a8, 0x24c)
DECOMP_SIZE_ASSERT(RacePowerupManager::Field0x18ac, 0x224)
DECOMP_SIZE_ASSERT(RacePowerupManager::Field0x18b0, 0x2c)
DECOMP_SIZE_ASSERT(RacePowerupManager::Field0x18b4, 0x34)
DECOMP_SIZE_ASSERT(RacePowerupManager::Field0x18b8, 0xe4)
DECOMP_SIZE_ASSERT(RacePowerupManager::Field0x1880, 0x18)

extern LegoU16 g_unk0x004befec[1024];
extern LegoU32 g_unk0x004c6ee4;
extern const LegoFloat g_unk0x004b02e0;
extern const LegoFloat g_unk0x004b1840;
extern const LegoFloat g_unk0x004b1844;
extern const LegoFloat g_unk0x004b1848;
extern const LegoFloat g_unk0x004b184c;
extern const LegoFloat g_unk0x004b1850;
extern const LegoFloat g_unk0x004b1854;
extern const LegoFloat g_unk0x004b1858;
extern const LegoFloat g_unk0x004b185c;
extern const LegoFloat g_unk0x004b1860;
extern const LegoFloat g_unk0x004b1864;
extern const LegoFloat g_unk0x004b1868;
extern const LegoFloat g_unk0x004b186c;

// GLOBAL: LEGORACERS 0x004b183c
extern const LegoFloat g_unk0x004b183c = 200.0f;

// GLOBAL: LEGORACERS 0x004b1870
extern const LegoFloat g_unk0x004b1870 = 500.0f;

// GLOBAL: LEGORACERS 0x004b1874
extern const LegoFloat g_unk0x004b1874 = 0.0040000002f;

// GLOBAL: LEGORACERS 0x004b1878
extern const LegoFloat g_unk0x004b1878 = 6.2831855f;

// GLOBAL: LEGORACERS 0x004c7644
LegoFloat g_unk0x004c7644 = g_unk0x004b1870 * g_unk0x004b1870;

// FUNCTION: LEGORACERS 0x00451350
RacePowerupManager::ResourceBase::ResourceBase()
{
	m_unk0x004 = 0;
	m_unk0x008 = 0;
	m_next = NULL;
	m_unk0x010 = NULL;
	m_state = 0;
}

// FUNCTION: LEGORACERS 0x00451370
RacePowerupManager::Field0x1880* RacePowerupManager::ResourceBase::VTable0x04(undefined4 p_flags)
{
	ResourceBase* result = this;
	this->~ResourceBase();
	if (p_flags & 1) {
		::operator delete(result);
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00451390
RacePowerupManager::ResourceBase::~ResourceBase()
{
}

// FUNCTION: LEGORACERS 0x004513a0 FOLDED
void RacePowerupManager::ResourceBase::VTable0x08(LegoU32 p_elapsedMs)
{
	if (p_elapsedMs >= m_unk0x008) {
		m_unk0x008 = 0;
		VTable0x14();
	}
	else {
		m_unk0x008 -= p_elapsedMs;
	}
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RacePowerupManager::ResourceBase::VTable0x00(LegoEventQueue::CallbackData*)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RacePowerupManager::ResourceBase::VTable0x0c(GolD3DRenderDevice*)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RacePowerupManager::ResourceBase::VTable0x10(GolD3DRenderDevice*)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RacePowerupManager::ResourceBase::VTable0x14()
{
}

// FUNCTION: LEGORACERS 0x0044e7e0 FOLDED
LegoS32 RacePowerupManager::ResourceBase::VTable0x18()
{
	return 0;
}

void RacePowerupManager::ResourceBase0x2c::VTable0x14()
{
}

void RacePowerupManager::ResourceBase0x30::VTable0x14()
{
}

// FUNCTION: LEGORACERS 0x0044f580 FOLDED
LegoS32 RacePowerupManager::Field0x18b4::VTable0x18()
{
	return 3;
}

// FUNCTION: LEGORACERS 0x0044f580 FOLDED
LegoS32 RacePowerupManager::Field0x18b8::VTable0x18()
{
	return 3;
}

// FUNCTION: LEGORACERS 0x004513e0 FOLDED
void RacePowerupManager::ResourceBase::VTable0x1c()
{
	m_unk0x004 = 1;
}

void RacePowerupManager::ResourceBase0x2c::VTable0x20(RaceState::Racer*)
{
}

void RacePowerupManager::ResourceBase0x30::VTable0x20(RaceState::Racer*)
{
}

// FUNCTION: LEGORACERS 0x004513f0
RacePowerupManager::Field0x18bc::Entry::Entry()
{
	m_unk0x0c = 0;
	m_unk0x10 = 0;
}

// FUNCTION: LEGORACERS 0x00451410
RacePowerupManager::Field0x18bc::Entry::~Entry()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00451460
void RacePowerupManager::Field0x18bc::Entry::Reset()
{
	m_unk0x00.Clear();
	m_unk0x0c = 0;
	m_unk0x10 = 0;
}

// FUNCTION: LEGORACERS 0x00451480
void RacePowerupManager::Field0x18bc::Entry::FUN_00451480(GolD3DRenderDevice* p_renderer)
{
	if (m_unk0x10) {
		Reset();
	}

	m_unk0x00.Initialize(p_renderer, 1);
	m_unk0x10 = 1;
}

// FUNCTION: LEGORACERS 0x004514b0
void RacePowerupManager::Field0x18bc::Entry::FUN_004514b0(
	GolAnimatedEntity* p_sourceEntity,
	GolAnimatedEntity* p_entity,
	const GolVec3* p_position,
	const GolVec3* p_direction,
	LegoU32 p_partIndex,
	void* p_billboardPosition
)
{
	m_unk0x0c = p_entity;
	m_unk0x0c->FUN_0040d550(
		p_sourceEntity->GetModel(0),
		p_sourceEntity->VTable0x58(0),
		p_sourceEntity->GetModelPart(0),
		p_sourceEntity->GetModelDistance(0)
	);

	LegoU32 i;
	for (i = 1; i < 3; i++) {
		if (p_sourceEntity->GetModel(i)) {
			m_unk0x0c->FUN_10023940(
				p_sourceEntity->GetModel(i),
				p_sourceEntity->VTable0x58(i),
				p_sourceEntity->GetModelPart(i),
				p_sourceEntity->GetModelDistance(i)
			);
		}
	}

	p_partIndex %= p_sourceEntity->GetModelPart(0)->GetPartCount();
	m_unk0x0c->FUN_0040dad0(p_partIndex);

	LegoU32 flags = m_unk0x0c->GetFlags();
	flags |= GolAnimatedEntity::c_flagPartAnimation;
	m_unk0x0c->SetFlags(flags);

	flags = m_unk0x0c->GetFlags();
	flags &= ~GolAnimatedEntity::c_flagLoopCurrentPart;
	m_unk0x0c->SetFlags(flags);

	if (p_billboardPosition) {
		m_unk0x00.SetPosition(0, p_billboardPosition);
		m_unk0x0c->SetPrimaryMaterialTable(&m_unk0x00);
	}

	GolVec3 up;
	up.m_x = 0.0f;
	up.m_y = 0.0f;
	up.m_z = 1.0f;
	m_unk0x0c->VTable0x08(*p_position);
	m_unk0x0c->VTable0x40(*p_direction, up);
	m_unk0x10 = 2;
}

// FUNCTION: LEGORACERS 0x004515d0
void RacePowerupManager::Field0x18bc::Entry::FUN_004515d0(LegoU32 p_elapsedMs)
{
	if (m_unk0x10 == 2) {
		m_unk0x0c->VTable0x10(p_elapsedMs);
		if (m_unk0x0c->FUN_0040e360()) {
			m_unk0x0c->VTable0x54();
			m_unk0x10 = 3;
		}
	}
}

// FUNCTION: LEGORACERS 0x00451610
void RacePowerupManager::Field0x18bc::Entry::FUN_00451610(GolD3DRenderDevice* p_renderer)
{
	if (m_unk0x10 == 2) {
		p_renderer->VTable0x94(m_unk0x0c);
	}
}

// FUNCTION: LEGORACERS 0x00451630
void RacePowerupManager::Field0x18bc::Entry::FUN_00451630()
{
	m_unk0x0c = NULL;
	m_unk0x10 = 1;
}

// FUNCTION: LEGORACERS 0x00451640
RacePowerupManager::Field0x18bc::Field0x18bc()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004516a0
RacePowerupManager::Field0x18bc::~Field0x18bc()
{
	FUN_00451700();
}

// FUNCTION: LEGORACERS 0x00451700
LegoS32 RacePowerupManager::Field0x18bc::FUN_00451700()
{
	LegoS32 i;

	for (i = 0; i < sizeOfArray(m_entries); i++) {
		m_entries[i].Reset();
	}

	return Reset();
}

// FUNCTION: LEGORACERS 0x00451730
LegoS32 RacePowerupManager::Field0x18bc::Reset()
{
	m_unk0x64[0] = NULL;
	m_unk0x64[1] = NULL;
	m_unk0x64[2] = NULL;
	m_unk0x64[3] = NULL;
	m_unk0x74 = 0;
	m_unk0x78 = 0;
	m_unk0x7c = 0;

	return 0;
}

// FUNCTION: LEGORACERS 0x00451750
void RacePowerupManager::Field0x18bc::FUN_00451750(RacePowerupManager* p_unk0x04, GolD3DRenderDevice* p_renderer)
{
	if (m_unk0x74) {
		FUN_00451700();
	}

	m_unk0x74 = p_unk0x04;

	const LegoChar* name = "brick1\0\0brick2\0\0brick3\0\0brick4\0";
	const LegoChar* endName = name + (sizeof(GolName) * 4);
	GolAnimatedEntity** entity = m_unk0x64;
	GolWorldDatabase* worldDatabase = p_unk0x04->m_unk0x05c;

	while (name < endName) {
		GolAnimatedEntity* model;
		if (worldDatabase->GetUnk0xc0NameEntries() == NULL) {
			model = NULL;
		}
		else {
			model = worldDatabase->GetUnk0xc0Name(name);
		}
		*entity = model;

		name += sizeof(GolName);
		entity++;
	}

	Entry* entry = m_entries;
	LegoS32 i;
	for (i = 5; i != 0; i--) {
		entry->FUN_00451480(p_renderer);
		entry++;
	}
}

// FUNCTION: LEGORACERS 0x004517c0
void RacePowerupManager::Field0x18bc::FUN_004517c0(
	const GolVec3* p_position,
	const GolVec3* p_direction,
	RaceState::Racer* p_racer
)
{
	DuskwindBananaRelic0x24* material;
	material = NULL;
	LegoS32 entryIndex;

	entryIndex = 0;
	while (TRUE) {
		if (m_entries[entryIndex].m_unk0x10 != 2) {
			break;
		}

		entryIndex++;
		if (entryIndex >= sizeOfArray(m_entries)) {
			break;
		}
	}

	if (entryIndex != sizeOfArray(m_entries)) {
		GolAnimatedEntity* entity = m_unk0x74->FUN_0045b9e0();
		if (entity) {
			LegoU32 sourceIndex = m_unk0x78;
			m_unk0x78 = sourceIndex + 1;
			if (m_unk0x78 == 4) {
				m_unk0x78 = 0;
			}

			if (p_racer) {
				material = m_unk0x74->m_raceState->GetMaterialLibrary()->GetItem(p_racer->m_unk0xe04);
			}

			m_entries[entryIndex]
				.FUN_004514b0(m_unk0x64[sourceIndex], entity, p_position, p_direction, m_unk0x7c, material);
			m_unk0x7c++;
		}
	}
}

// FUNCTION: LEGORACERS 0x00451860
void RacePowerupManager::Field0x18bc::FUN_00451860(LegoU32 p_elapsedMs)
{
	Entry* entry = m_entries;
	LegoS32 i;

	for (i = 5; i != 0; i--) {
		entry->FUN_004515d0(p_elapsedMs);
		if (entry->GetUnk0x10() == 3) {
			m_unk0x74->FUN_0045ba40(entry->GetUnk0x0c());
			entry->FUN_00451630();
		}

		entry++;
	}
}

// FUNCTION: LEGORACERS 0x004518a0
void RacePowerupManager::Field0x18bc::FUN_004518a0(GolD3DRenderDevice* p_renderer)
{
	Entry* entry = m_entries;
	LegoS32 i;

	for (i = 5; i != 0; i--) {
		entry->FUN_00451610(p_renderer);
		entry++;
	}
}

// FUNCTION: LEGORACERS 0x004518d0
void RacePowerupManager::Field0x18bc::FUN_004518d0()
{
	Entry* entry = m_entries;
	LegoS32 i;

	for (i = 5; i != 0; i--) {
		entry->FUN_00451630();
		entry++;
	}
}

// FUNCTION: LEGORACERS 0x00457990
RacePowerupManager::RacePowerupManager()
{
	FUN_00457a90();
}

// FUNCTION: LEGORACERS 0x00457a20
RacePowerupManager::~RacePowerupManager()
{
	FUN_00459e20();
}

// FUNCTION: LEGORACERS 0x00457a90
void RacePowerupManager::FUN_00457a90()
{
	m_unk0x000 = 0;
	m_renderer = NULL;
	m_unk0x028 = NULL;
	m_unk0x030 = NULL;
	m_unk0x034 = 0;
	m_unk0x02c = NULL;
	m_unk0x038 = 0;
	m_raceState = NULL;
	m_unk0x068 = 0;
	m_unk0x06c = 0;
	m_unk0x03c = 0;
	m_unk0x040 = 0;
	m_unk0x1958 = 0;
	m_unk0x195c = 0;
	m_unk0x1960 = 0;
	m_unk0x1964 = 0;
	m_unk0x078 = 0;
	m_unk0x07c = 0;
	m_unk0x080 = 0;
	m_unk0x084 = 0;
	m_unk0x088 = 0;
	m_unk0x08c = 0;
	m_unk0x090 = 0;
	m_unk0x094 = 0;
	m_unk0x098 = 0;
	m_unk0x09c = 0;
	m_unk0x0a0 = 0;
	m_unk0x199c = 0;
	m_unk0x19a0 = 0;
	m_unk0x064 = 0;
	m_unk0x070 = 0;
	m_unk0x048 = 0;
	m_unk0x060 = 0;
	m_unk0x1884[0] = 0;
	m_unk0x1884[1] = 0;
	m_unk0x1884[2] = 0;
	m_unk0x1884[3] = 0;
	m_unk0x1884[4] = 0;
	m_unk0x1884[5] = 0;
	m_unk0x1884[6] = 0;
	m_unk0x1884[7] = 0;
	m_unk0x1884[8] = 0;
	m_unk0x1884[9] = 0;
	m_unk0x1884[10] = 0;
	m_unk0x194c = 0;
	m_unk0x194d = 0;
	m_unk0x193c = NULL;
	m_unk0x1940 = NULL;
	m_unk0x1944 = 0;
	m_unk0x1948 = 0;
	m_unk0x1998 = 0;
	m_unk0x1950 = NULL;
	m_unk0x1954 = NULL;
	m_unk0x1890 = 0;
	m_unk0x1894 = 0;
	m_unk0x1898 = 0;
	m_unk0x189c = 0;
	m_unk0x18a0 = 0;
	m_unk0x18a4 = 0;
	m_unk0x18a8 = 0;
	m_unk0x18ac = 0;
	m_unk0x18b0 = 0;
	m_unk0x18b4 = 0;
	m_unk0x18b8 = 0;
	m_unk0x04c = 0;
	m_unk0x050 = 0;
	m_unk0x1878 = 0;
	m_unk0x187c = 0;
	m_unk0x054 = 0;
	m_unk0x1968 = 0;
	m_unk0x196c = 0;
	m_unk0x1970 = 0;
	m_unk0x1974 = 0;

	DuskwindBananaRelic0x24** entry = m_unk0x1978;
	LegoS32 count;
	for (count = c_unk0x1978SlotCount; count != 0; count--) {
		*entry = NULL;
		entry++;
	}
}

// FUNCTION: LEGORACERS 0x00457c20
void RacePowerupManager::FUN_00457c20(const Params* p_params)
{
	if (m_unk0x000) {
		FUN_00459e20();
	}

	m_unk0x000 = p_params->m_unk0x00;
	m_renderer = p_params->m_renderer;
	m_raceState = p_params->m_raceState;
	m_unk0x06c = p_params->m_unk0x0c;
	m_unk0x070 = p_params->m_unk0x10;
	m_unk0x068 = p_params->m_unk0x14;
	m_unk0x03c = p_params->m_unk0x18;
	m_cutsceneAnimation0x040 = p_params->m_unk0x1c;
	m_trailManager = p_params->m_trailManager;
	m_unk0x060 = p_params->m_unk0x2c;
	m_unk0x048 = p_params->m_unk0x24;
	m_unk0x04c = p_params->m_unk0x28;
	m_unk0x050 = p_params->m_unk0x30;
	m_unk0x054 = p_params->m_unk0x34;
	m_unk0x058 = p_params->m_unk0x38;
}

// FUNCTION: LEGORACERS 0x00457c90
void RacePowerupManager::FUN_00457c90(const LegoChar* p_unk0x04, const LegoChar* p_unk0x08, LegoBool32 p_binary)
{
	m_unk0x05c = m_unk0x000->VTable0x08();
	m_unk0x05c->VTable0x14(m_renderer, p_unk0x04, p_binary, 1.0f);
	m_unk0x014.VTable0x04(m_renderer, p_unk0x08, p_binary);
	m_unk0x064 = m_unk0x000->VTable0x08();
	m_unk0x064->VTable0x14(m_renderer, "turbo3", p_binary, 1.0f);
}

// FUNCTION: LEGORACERS 0x00457cf0
void RacePowerupManager::FUN_00457cf0(LegoBool32 p_unk0x04)
{
	FUN_00457d30(p_unk0x04);
	m_unk0x008.Initialize(m_renderer, m_unk0x1884[5] + m_unk0x1884[0]);
	m_unk0x18bc.FUN_00451750(this, m_renderer);
}

// FUNCTION: LEGORACERS 0x00457d30
void RacePowerupManager::FUN_00457d30(LegoBool32 p_mirror)
{
	if (p_mirror) {
		m_unk0x1884[0] = 3;
		m_unk0x1884[1] = 4;
		m_unk0x1884[2] = 3;
		m_unk0x1884[3] = 2;
		m_unk0x1884[4] = 4;
		m_unk0x1884[5] = 3;
		m_unk0x1884[6] = 3;
		m_unk0x1884[7] = 9;
		m_unk0x1884[8] = 5;
		m_unk0x1884[9] = 6;
		m_unk0x1884[10] = 3;
	}
	else {
		m_unk0x1884[0] = 2;
		m_unk0x1884[1] = 3;
		m_unk0x1884[2] = 2;
		m_unk0x1884[3] = 2;
		m_unk0x1884[4] = 2;
		m_unk0x1884[5] = 2;
		m_unk0x1884[6] = 2;
		m_unk0x1884[7] = 6;
		m_unk0x1884[8] = 2;
		m_unk0x1884[9] = 2;
		m_unk0x1884[10] = 2;
	}

	m_unk0x194c = 6;
	m_unk0x194d = 2;

	m_unk0x1890 = new Field0x1890[m_unk0x1884[0]];
	if (!m_unk0x1890) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x1894 = new Field0x1894[m_unk0x1884[1]];
	if (!m_unk0x1894) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x1898 = new Field0x1898[m_unk0x1884[2]];
	if (!m_unk0x1898) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x189c = new Field0x189c[m_unk0x1884[3]];
	if (!m_unk0x189c) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x18a0 = new Field0x18a0[m_unk0x1884[4]];
	if (!m_unk0x18a0) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x18a4 = new Field0x18a4[m_unk0x1884[5]];
	if (!m_unk0x18a4) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x18a8 = new Field0x18a8[m_unk0x1884[6]];
	if (!m_unk0x18a8) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x18ac = new Field0x18ac[m_unk0x1884[7]];
	if (!m_unk0x18ac) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x18b0 = new Field0x18b0[m_unk0x1884[8]];
	if (!m_unk0x18b0) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x18b4 = new Field0x18b4[m_unk0x1884[9]];
	if (!m_unk0x18b4) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x18b8 = new Field0x18b8[m_unk0x1884[10]];
	if (!m_unk0x18b8) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x1950 = new Field0x270[m_unk0x194c];
	if (!m_unk0x1950) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x1954 = new Field0x270[m_unk0x194d];
	if (!m_unk0x1954) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void RacePowerupManager::FUN_004164c0()
{
}

// FUNCTION: LEGORACERS 0x00458810
void RacePowerupManager::FUN_00458810(const LegoChar* p_name, LegoBool32 p_binary, LegoBool32 p_mirror)
{
	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".pwb");
	}
	else {
		parser = new PwbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_name);

	GolFileParser::ParserTokenType token = parser->GetNextToken();
	while (token != GolFileParser::e_syntaxerror) {
		if (token != GolFileParser::e_unknown0x27) {
			if (token == GolFileParser::e_unknown0x2f) {
				FUN_00458e80(parser, p_mirror);
			}
		}
		else {
			FUN_00458a80(parser, p_mirror);
		}

		token = parser->GetNextToken();
	}

	parser->Dispose();
	if (parser != NULL) {
		delete parser;
	}
}

// FUNCTION: LEGORACERS 0x00458940
void RacePowerupManager::FUN_00458940()
{
	m_unk0x030 = new LegoEventQueue::Event*[m_unk0x034 + m_unk0x038];
	if (!m_unk0x030) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoU32 i;
	for (i = 0; i < m_unk0x034 + m_unk0x038; i++) {
		m_unk0x030[i] = NULL;
	}

	FUN_004164c0();
	FUN_0045a340();
	FUN_004590f0();
	FUN_00459b80();

	m_sound0x1958 = m_unk0x03c->FUN_00443bd0(7);
	if (m_sound0x1958 != NULL) {
		m_sound0x1958->SetDistanceRangeWithMinSquared(g_unk0x004b183c * g_unk0x004b183c, g_unk0x004b1870);
	}

	m_sound0x195c = m_unk0x03c->FUN_00443bd0(0x34);
	if (m_sound0x195c != NULL) {
		m_sound0x195c->SetDistanceRangeWithMinSquared(g_unk0x004b183c * g_unk0x004b183c, g_unk0x004b1870);
	}

	m_sound0x1960 = m_unk0x03c->FUN_00443bd0(0x17);
	if (m_sound0x1960 != NULL) {
		m_sound0x1960->SetDistanceRangeWithMinSquared(g_unk0x004b183c * g_unk0x004b183c, g_unk0x004b1870);
	}

	m_sound0x1964 = m_unk0x03c->FUN_00443bd0(0x13);
	if (m_sound0x1964 != NULL) {
		m_sound0x1964->SetDistanceRangeWithMinSquared(g_unk0x004b183c * g_unk0x004b183c, g_unk0x004b1870);
	}
}

// FUNCTION: LEGORACERS 0x00458a80
void RacePowerupManager::FUN_00458a80(GolFileParser* p_parser, LegoBool32 p_mirror)
{
	m_unk0x034 = p_parser->ReadBracketedCountAndLeftCurly();
	if (m_unk0x034 == 0) {
		return;
	}

	m_unk0x028 = new Field0x68Field0x028[m_unk0x034];
	if (m_unk0x028 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x1968 = m_unk0x05c->FindUnk0xc0("gen");
	m_unk0x196c = m_unk0x05c->FindUnk0xc0("genblen");
	m_unk0x1978[c_unk0x1978MaterialPBrickP] = m_renderer->FindMaterialByName("pbrickP");
	m_unk0x1978[c_unk0x1978MaterialPTrailP] = m_renderer->FindMaterialByName("ptrailP");
	m_unk0x1978[c_unk0x1978MaterialPBrickM] = m_renderer->FindMaterialByName("pbrickM");
	m_unk0x1978[c_unk0x1978MaterialPTrailM] = m_renderer->FindMaterialByName("ptrailM");
	m_unk0x1978[c_unk0x1978MaterialPBrickS] = m_renderer->FindMaterialByName("pbrickS");
	m_unk0x1978[c_unk0x1978MaterialPTrailS] = m_renderer->FindMaterialByName("ptrailS");
	m_unk0x1978[c_unk0x1978MaterialPBrickT] = m_renderer->FindMaterialByName("pbrickT");
	m_unk0x1978[c_unk0x1978MaterialPTrailT] = m_renderer->FindMaterialByName("ptrailT");

	LegoU32 i;
	for (i = 0; i < m_unk0x034; i++) {
		if (p_parser->GetNextToken() != GolFileParser::e_unknown0x27) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}
		if (p_parser->GetNextToken() != GolFileParser::e_leftCurly) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		GolVec3 position;
		position.m_x = 0.0f;
		position.m_y = 0.0f;
		position.m_z = 0.0f;
		LegoU32 state = 3;
		LegoS32 duration = -1;

		GolFileParser::ParserTokenType token = p_parser->GetNextToken();
		while (token != GolFileParser::e_rightCurly) {
			switch (token) {
			case GolFileParser::e_unknown0x28:
				position.m_x = p_parser->ReadFloat();
				position.m_y = p_parser->ReadFloat();
				position.m_z = p_parser->ReadFloat();
				break;
			case GolFileParser::e_unknown0x2a:
				state = 1;
				break;
			case GolFileParser::e_unknown0x2b:
				state = 4;
				break;
			case GolFileParser::e_unknown0x2c:
				state = 2;
				break;
			case GolFileParser::e_unknown0x2d:
				state = 3;
				break;
			case GolFileParser::e_unknown0x2e:
				duration = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x30:
				p_parser->ReadStringWithMaxLength(sizeof(GolName));
				// Intentional fall-through: the original consumes the following integer too.
			case GolFileParser::e_unknown0x31:
				p_parser->ReadInteger();
				break;
			default:
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}

			token = p_parser->GetNextToken();
		}

		if (!(m_unk0x058 & 0x44)) {
			if (m_unk0x058 & 8) {
				state = 4;
			}
			else if (m_unk0x058 & 0x10) {
				state = i * sizeof(Field0x68Field0x028);
			}
		}
		else {
			state = 1;
		}

		if (p_mirror) {
			position.m_y = -position.m_y;
		}

		DuskwindBananaRelic0x24* material0 = FUN_0045ba90(&state);
		DuskwindBananaRelic0x24* material1 = FUN_0045bae0(&state);
		m_unk0x028[i].FUN_004539b0(this, m_unk0x03c, &position, m_unk0x1968, m_unk0x196c);
		m_unk0x028[i].FUN_004578e0(material0, material1);
		m_unk0x028[i].FUN_004576c0(state);
		if (duration >= 0) {
			m_unk0x028[i].SetUnk0x48(duration);
		}
	}

	if (p_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_rightCurly);
	}
}

// FUNCTION: LEGORACERS 0x00458e80
void RacePowerupManager::FUN_00458e80(GolFileParser* p_parser, LegoBool32 p_mirror)
{
	m_unk0x038 = p_parser->ReadBracketedCountAndLeftCurly();
	if (m_unk0x038 == 0) {
		return;
	}

	m_unk0x02c = new Field0x68Field0x02c[m_unk0x038];
	if (m_unk0x02c == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x1970 = m_unk0x05c->FindUnk0xc0("enh");
	m_unk0x1974 = m_unk0x05c->FindUnk0xc0("enhblen");

	LegoU32 i;
	for (i = 0; i < m_unk0x038; i++) {
		if (p_parser->GetNextToken() != GolFileParser::e_unknown0x2f) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}
		if (p_parser->GetNextToken() != GolFileParser::e_leftCurly) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		GolVec3 position;
		position.m_x = 0.0f;
		position.m_y = 0.0f;
		position.m_z = 0.0f;

		GolFileParser::ParserTokenType token = p_parser->GetNextToken();
		while (token != GolFileParser::e_rightCurly) {
			switch (token) {
			case GolFileParser::e_unknown0x28:
				position.m_x = p_parser->ReadFloat();
				position.m_y = p_parser->ReadFloat();
				position.m_z = p_parser->ReadFloat();
				break;
			case GolFileParser::e_unknown0x30:
				p_parser->ReadStringWithMaxLength(sizeof(GolName));
				// Intentional fall-through: the original consumes the following integer too.
			case GolFileParser::e_unknown0x31:
				p_parser->ReadInteger();
				break;
			default:
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}

			token = p_parser->GetNextToken();
		}

		if (p_mirror) {
			position.m_y = -position.m_y;
		}

		m_unk0x02c[i].FUN_004539b0(this, m_unk0x03c, &position, m_unk0x1970, m_unk0x1974);
		m_unk0x02c[i].FUN_00453620();
	}

	if (p_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_rightCurly);
	}
}

// FUNCTION: LEGORACERS 0x004590f0
void RacePowerupManager::FUN_004590f0()
{
	LegoU8 i = 0;

	if (m_unk0x1884[0] - 1 > 0) {
		do {
			m_unk0x1890[i].SetNext(&m_unk0x1890[i + 1]);
			m_unk0x1890[i]
				.FUN_00455810(this, m_raceState, m_unk0x068, m_unk0x040, m_unk0x000, m_renderer, m_unk0x1884[5] + i);
			m_unk0x1890[i].SetUnk0x010(m_unk0x03c);
			i++;
		} while (i < m_unk0x1884[0] - 1);
	}

	m_unk0x1890[m_unk0x1884[0] - 1].SetNext(NULL);
	m_unk0x1890[m_unk0x1884[0] - 1].FUN_00455810(
		this,
		m_raceState,
		m_unk0x068,
		m_unk0x040,
		m_unk0x000,
		m_renderer,
		m_unk0x1884[5] + m_unk0x1884[0] - 1
	);
	m_unk0x1890[m_unk0x1884[0] - 1].SetUnk0x010(m_unk0x03c);
	m_unk0x078 = m_unk0x1890;

	i = 0;
	if (m_unk0x1884[1] - 1 > 0) {
		do {
			m_unk0x1894[i].SetNext(&m_unk0x1894[i + 1]);
			m_unk0x1894[i].FUN_004571b0(
				this,
				m_raceState,
				m_unk0x06c,
				m_unk0x068,
				m_cutsceneAnimation0x040,
				m_renderer,
				m_unk0x000
			);
			m_unk0x1894[i].SetUnk0x010(m_unk0x03c);
			i++;
		} while (i < m_unk0x1884[1] - 1);
	}

	m_unk0x1894[m_unk0x1884[1] - 1].SetNext(NULL);
	m_unk0x1894[m_unk0x1884[1] - 1]
		.FUN_004571b0(this, m_raceState, m_unk0x06c, m_unk0x068, m_cutsceneAnimation0x040, m_renderer, m_unk0x000);
	m_unk0x1894[m_unk0x1884[1] - 1].SetUnk0x010(m_unk0x03c);
	m_unk0x07c = m_unk0x1894;

	i = 0;
	if (m_unk0x1884[2] - 1 > 0) {
		do {
			m_unk0x1898[i].SetNext(&m_unk0x1898[i + 1]);
			m_unk0x1898[i].FUN_00452ee0(m_raceState, m_unk0x068, this, m_unk0x040, m_unk0x05c->FindUnk0xb4("barrel"));
			m_unk0x1898[i].SetUnk0x010(m_unk0x03c);
			i++;
		} while (i < m_unk0x1884[2] - 1);
	}

	m_unk0x1898[m_unk0x1884[2] - 1].SetNext(NULL);
	m_unk0x1898[m_unk0x1884[2] - 1]
		.FUN_00452ee0(m_raceState, m_unk0x068, this, m_unk0x040, m_unk0x05c->FindUnk0xb4("barrel"));
	m_unk0x1898[m_unk0x1884[2] - 1].SetUnk0x010(m_unk0x03c);
	m_unk0x080 = m_unk0x1898;

	i = 0;
	if (m_unk0x1884[3] - 1 > 0) {
		do {
			m_unk0x189c[i].SetNext(&m_unk0x189c[i + 1]);
			m_unk0x189c[i].FUN_00452530(m_raceState, m_unk0x068, this);
			m_unk0x189c[i].SetUnk0x010(m_unk0x03c);
			i++;
		} while (i < m_unk0x1884[3] - 1);
	}

	m_unk0x189c[m_unk0x1884[3] - 1].SetNext(NULL);
	m_unk0x189c[m_unk0x1884[3] - 1].FUN_00452530(m_raceState, m_unk0x068, this);
	m_unk0x189c[m_unk0x1884[3] - 1].SetUnk0x010(m_unk0x03c);
	m_unk0x084 = m_unk0x189c;

	i = 0;
	if (m_unk0x1884[4] - 1 > 0) {
		do {
			m_unk0x18a0[i].SetNext(&m_unk0x18a0[i + 1]);
			m_unk0x18a0[i].FUN_004519d0(&m_unk0x000, m_unk0x068);
			m_unk0x18a0[i].SetUnk0x010(m_unk0x03c);
			i++;
		} while (i < m_unk0x1884[4] - 1);
	}

	m_unk0x18a0[m_unk0x1884[4] - 1].SetNext(NULL);
	m_unk0x18a0[m_unk0x1884[4] - 1].FUN_004519d0(&m_unk0x000, m_unk0x068);
	m_unk0x18a0[m_unk0x1884[4] - 1].SetUnk0x010(m_unk0x03c);
	m_unk0x088 = m_unk0x18a0;

	i = 0;
	if (m_unk0x1884[5] - 1 > 0) {
		do {
			m_unk0x18a4[i].SetNext(&m_unk0x18a4[i + 1]);
			m_unk0x18a4[i].FUN_00453cd0(this, m_unk0x068, i);
			m_unk0x18a4[i].SetUnk0x010(m_unk0x03c);
			i++;
		} while (i < m_unk0x1884[5] - 1);
	}

	m_unk0x18a4[m_unk0x1884[5] - 1].SetNext(NULL);
	m_unk0x18a4[m_unk0x1884[5] - 1].FUN_00453cd0(this, m_unk0x068, m_unk0x1884[5] - 1);
	m_unk0x18a4[m_unk0x1884[5] - 1].SetUnk0x010(m_unk0x03c);
	m_unk0x08c = m_unk0x18a4;

	i = 0;
	if (m_unk0x1884[6] - 1 > 0) {
		do {
			m_unk0x18a8[i].SetNext(&m_unk0x18a8[i + 1]);
			m_unk0x18a8[i].FUN_004548f0(m_unk0x000, this);
			m_unk0x18a8[i].SetUnk0x010(m_unk0x03c);
			m_unk0x18a8[i].FUN_00454a70();
			i++;
		} while (i < m_unk0x1884[6] - 1);
	}

	m_unk0x18a8[m_unk0x1884[6] - 1].SetNext(NULL);
	m_unk0x18a8[m_unk0x1884[6] - 1].FUN_004548f0(m_unk0x000, this);
	m_unk0x18a8[m_unk0x1884[6] - 1].SetUnk0x010(m_unk0x03c);
	m_unk0x18a8[m_unk0x1884[6] - 1].FUN_00454a70();
	m_unk0x090 = m_unk0x18a8;

	i = 0;
	if (m_unk0x1884[7] - 1 > 0) {
		do {
			m_unk0x18ac[i].SetNext(&m_unk0x18ac[i + 1]);
			m_unk0x18ac[i].FUN_00456510(&m_unk0x000, m_unk0x068);
			m_unk0x18ac[i].SetUnk0x010(m_unk0x03c);
			i++;
		} while (i < m_unk0x1884[7] - 1);
	}

	m_unk0x18ac[m_unk0x1884[7] - 1].SetNext(NULL);
	m_unk0x18ac[m_unk0x1884[7] - 1].FUN_00456510(&m_unk0x000, m_unk0x068);
	m_unk0x18ac[m_unk0x1884[7] - 1].SetUnk0x010(m_unk0x03c);
	m_unk0x094 = m_unk0x18ac;

	i = 0;
	if (m_unk0x1884[8] - 1 > 0) {
		do {
			m_unk0x18b0[i].SetNext(&m_unk0x18b0[i + 1]);
			m_unk0x18b0[i].FUN_0045bcd0(this);
			m_unk0x18b0[i].SetUnk0x010(m_unk0x03c);
			i++;
		} while (i < m_unk0x1884[8] - 1);
	}

	m_unk0x18b0[m_unk0x1884[8] - 1].SetNext(NULL);
	m_unk0x18b0[m_unk0x1884[8] - 1].FUN_0045bcd0(this);
	m_unk0x18b0[m_unk0x1884[8] - 1].SetUnk0x010(m_unk0x03c);
	m_unk0x098 = m_unk0x18b0;

	i = 0;
	if (m_unk0x1884[9] - 1 > 0) {
		do {
			m_unk0x18b4[i].SetNext(&m_unk0x18b4[i + 1]);
			m_unk0x18b4[i].FUN_0045c880(this, m_cutsceneAnimation0x040);
			m_unk0x18b4[i].SetUnk0x010(m_unk0x03c);
			i++;
		} while (i < m_unk0x1884[9] - 1);
	}

	m_unk0x18b4[m_unk0x1884[9] - 1].SetNext(NULL);
	m_unk0x18b4[m_unk0x1884[9] - 1].FUN_0045c880(this, m_cutsceneAnimation0x040);
	m_unk0x18b4[m_unk0x1884[9] - 1].SetUnk0x010(m_unk0x03c);
	m_unk0x09c = m_unk0x18b4;

	Field0x18b8::SetupParams params;
	params.m_unk0x00 = this;
	params.m_unk0x04 = m_unk0x054;

	i = 0;
	if (m_unk0x1884[10] - 1 > 0) {
		do {
			m_unk0x18b8[i].SetNext(&m_unk0x18b8[i + 1]);
			m_unk0x18b8[i].FUN_0045d510(&params);
			m_unk0x18b8[i].SetUnk0x010(m_unk0x03c);
			i++;
		} while (i < m_unk0x1884[10] - 1);
	}

	m_unk0x18b8[m_unk0x1884[10] - 1].SetNext(NULL);
	m_unk0x18b8[m_unk0x1884[10] - 1].FUN_0045d510(&params);
	m_unk0x18b8[m_unk0x1884[10] - 1].SetUnk0x010(m_unk0x03c);
	m_unk0x0a0 = m_unk0x18b8;

	m_unk0x1880 = NULL;
}

// FUNCTION: LEGORACERS 0x00459b80
void RacePowerupManager::FUN_00459b80()
{
	Field0x270::Params params;
	params.m_unk0x00 = m_unk0x000;
	params.m_unk0x04 = m_unk0x06c;
	params.m_unk0x08 = m_unk0x05c->FindUnk0xb4("Explsn");
	params.m_unk0x0c = NULL;
	params.m_unk0x10 = m_renderer->FindMaterialByName("exflash");
	params.m_unk0x14 = m_renderer->FindMaterialByName("exscar");
	params.m_unk0x18 = m_raceState->GetEventQueue();
	params.m_unk0x1c = this;
	params.m_unk0x20 = NULL;
	params.m_unk0x28 = 0;
	params.m_unk0x2c = 1000;
	params.m_unk0x30 = 5000;
	params.m_unk0x34 = 1.0f;
	params.m_unk0x38 = 15.0f;
	params.m_unk0x3c = 15.0f;
	params.m_unk0x40 = 5.0f;
	params.m_unk0x44 = 2;

	LegoU8 index = 0;
	if (m_unk0x194c - 1 > 0) {
		do {
			m_unk0x1950[index].SetNext(&m_unk0x1950[index + 1]);
			params.m_unk0x28 = 0;
			m_unk0x1950[index].FUN_00421250(&params);
			index++;
		} while (index < m_unk0x194c - 1);
	}

	m_unk0x1950[m_unk0x194c - 1].SetNext(NULL);
	params.m_unk0x28 = 0;
	m_unk0x1950[m_unk0x194c - 1].FUN_00421250(&params);
	m_unk0x1944 = m_unk0x1950;
	m_unk0x193c = NULL;

	params.m_unk0x28 = 0;
	params.m_unk0x40 = 10.0f;
	params.m_unk0x44 = 2;
	params.m_unk0x08 = m_unk0x05c->FindUnk0xb4("spikexp");
	params.m_unk0x10 = NULL;
	params.m_unk0x38 = 5.0f;
	params.m_unk0x3c = 5.0f;

	index = 0;
	if (m_unk0x194d - 1 > 0) {
		do {
			m_unk0x1954[index].SetNext(&m_unk0x1954[index + 1]);
			params.m_unk0x28 = 0;
			m_unk0x1954[index].FUN_00421250(&params);
			index++;
		} while (index < m_unk0x194d - 1);
	}

	m_unk0x1954[m_unk0x194d - 1].SetNext(NULL);
	params.m_unk0x28 = 0;
	m_unk0x1954[m_unk0x194d - 1].FUN_00421250(&params);
	m_unk0x1940 = NULL;
	m_unk0x1948 = m_unk0x1954;
}

// FUNCTION: LEGORACERS 0x00459e20
void RacePowerupManager::FUN_00459e20()
{
	if (m_unk0x1964 != NULL) {
		m_unk0x03c->FUN_00443c10(m_unk0x1964);
		m_unk0x1964 = NULL;
	}

	if (m_unk0x1960 != NULL) {
		m_unk0x03c->FUN_00443c10(m_unk0x1960);
		m_unk0x1960 = NULL;
	}

	if (m_unk0x195c != NULL) {
		m_unk0x03c->FUN_00443c10(m_unk0x195c);
		m_unk0x195c = NULL;
	}

	if (m_unk0x1958 != NULL) {
		m_unk0x03c->FUN_00443c10(m_unk0x1958);
		m_unk0x1958 = NULL;
	}

	m_unk0x008.Clear();

	if (m_unk0x1954 != NULL) {
		LegoU32 i;

		for (i = 0; i < m_unk0x194d; i++) {
			m_unk0x1954[i].FUN_004214b0();
		}

		if (m_unk0x1954 != NULL) {
			m_unk0x1954->VTable0x04(3);
		}
		m_unk0x1954 = NULL;
	}

	if (m_unk0x1950 != NULL) {
		LegoU32 i;

		for (i = 0; i < m_unk0x194c; i++) {
			m_unk0x1950[i].FUN_004214b0();
		}

		if (m_unk0x1950 != NULL) {
			m_unk0x1950->VTable0x04(3);
		}
		m_unk0x1950 = NULL;
	}

	if (m_unk0x18b8 != NULL) {
		LegoU32 i;

		for (i = 0; i < m_unk0x1884[10]; i++) {
			m_unk0x18b8[i].FUN_0045d540();
		}

		if (m_unk0x18b8 != NULL) {
			m_unk0x18b8->VTable0x04(3);
		}
		m_unk0x18b8 = NULL;
	}

	if (m_unk0x18b4 != NULL) {
		LegoU32 i;

		for (i = 0; i < m_unk0x1884[9]; i++) {
			m_unk0x18b4[i].FUN_0045c8b0();
		}

		if (m_unk0x18b4 != NULL) {
			m_unk0x18b4->VTable0x04(3);
		}
		m_unk0x18b4 = NULL;
	}

	if (m_unk0x18b0 != NULL) {
		LegoU32 i;

		for (i = 0; i < m_unk0x1884[8]; i++) {
			m_unk0x18b0[i].FUN_0045bd10();
		}

		if (m_unk0x18b0 != NULL) {
			m_unk0x18b0->VTable0x04(3);
		}
		m_unk0x18b0 = NULL;
	}

	if (m_unk0x18ac != NULL) {
		LegoU32 i;

		for (i = 0; i < m_unk0x1884[7]; i++) {
			m_unk0x18ac[i].FUN_00456540();
		}

		if (m_unk0x18ac != NULL) {
			m_unk0x18ac->VTable0x04(3);
		}
		m_unk0x18ac = NULL;
	}

	if (m_unk0x18a8 != NULL) {
		LegoU32 i;

		for (i = 0; i < m_unk0x1884[6]; i++) {
			m_unk0x18a8[i].FUN_00454ab0();
		}

		if (m_unk0x18a8 != NULL) {
			m_unk0x18a8->VTable0x04(3);
		}
		m_unk0x18a8 = NULL;
	}

	if (m_unk0x18a4 != NULL) {
		LegoU32 i;

		for (i = 0; i < m_unk0x1884[5]; i++) {
			m_unk0x18a4[i].FUN_00453d90();
		}

		if (m_unk0x18a4 != NULL) {
			m_unk0x18a4->VTable0x04(3);
		}
		m_unk0x18a4 = NULL;
	}

	if (m_unk0x18a0 != NULL) {
		LegoU32 i;

		for (i = 0; i < m_unk0x1884[4]; i++) {
			m_unk0x18a0[i].FUN_00451a10();
		}

		if (m_unk0x18a0 != NULL) {
			m_unk0x18a0->VTable0x04(3);
		}
		m_unk0x18a0 = NULL;
	}

	if (m_unk0x189c != NULL) {
		LegoU32 i;

		for (i = 0; i < m_unk0x1884[3]; i++) {
			m_unk0x189c[i].FUN_00452510();
		}

		if (m_unk0x189c != NULL) {
			m_unk0x189c->VTable0x04(3);
		}
		m_unk0x189c = NULL;
	}

	if (m_unk0x1898 != NULL) {
		LegoU32 i;

		for (i = 0; i < m_unk0x1884[2]; i++) {
			m_unk0x1898[i].FUN_00452eb0();
		}

		if (m_unk0x1898 != NULL) {
			m_unk0x1898->VTable0x04(3);
		}
		m_unk0x1898 = NULL;
	}

	if (m_unk0x1894 != NULL) {
		LegoU32 i;

		for (i = 0; i < m_unk0x1884[1]; i++) {
			m_unk0x1894[i].FUN_00457170();
		}

		if (m_unk0x1894 != NULL) {
			m_unk0x1894->VTable0x04(3);
		}
		m_unk0x1894 = NULL;
	}

	if (m_unk0x1890 != NULL) {
		LegoU32 i;

		for (i = 0; i < m_unk0x1884[0]; i++) {
			m_unk0x1890[i].FUN_004557c0();
		}

		if (m_unk0x1890 != NULL) {
			m_unk0x1890->VTable0x04(3);
		}
		m_unk0x1890 = NULL;
	}

	if (m_unk0x000 != NULL && m_unk0x05c != 0) {
		m_unk0x000->VTable0x3c(m_unk0x05c);
		m_unk0x05c = 0;
	}

	m_unk0x014.VTable0x08();
	m_unk0x060 = 0;

	if (m_unk0x000 != NULL && m_unk0x064 != 0) {
		m_unk0x000->VTable0x3c(m_unk0x064);
		m_unk0x064 = 0;
	}

	if (m_unk0x030 != NULL) {
		LegoU32 i;

		for (i = 0; i < m_unk0x034 + m_unk0x038; i++) {
			if (m_unk0x030[i] != NULL) {
				m_unk0x030[i]->m_active = 0;
			}
		}

		delete[] m_unk0x030;
		m_unk0x030 = NULL;
	}

	if (m_unk0x02c != NULL) {
		delete[] m_unk0x02c;
		m_unk0x02c = NULL;
	}

	if (m_unk0x028 != NULL) {
		delete[] m_unk0x028;
		m_unk0x028 = NULL;
	}

	LegoS32 i;
	for (i = 25; i != 0; i--) {
		m_unk0x0a4[25 - i].VTable0x54();
	}

	FUN_00457a90();
}

// FUNCTION: LEGORACERS 0x0045a340
void RacePowerupManager::FUN_0045a340()
{
	LegoEventQueue* eventQueue = m_raceState->GetEventQueue();
	LegoEventQueue::Descriptor descriptor;

	descriptor.m_unk0x00 = 4;
	descriptor.m_unk0x04 = 1;
	descriptor.m_unk0x08 = 0;
	descriptor.m_unk0x0c = 0;

	LegoU32 i;
	for (i = 0; i < m_unk0x034; i++) {
		Field0x68Field0x028* entry = &m_unk0x028[i];
		descriptor.m_data = entry->GetUnk0x08();
		m_unk0x030[i] = eventQueue->FUN_0042fb50(entry, &descriptor);
	}

	Field0x68Field0x02c* entries0x02c = m_unk0x02c;
	for (i = 0; i < m_unk0x038; i++) {
		Field0x68Field0x02c* entry = &entries0x02c[i];
		descriptor.m_data = entry->GetUnk0x08();
		m_unk0x030[m_unk0x034 + i] = eventQueue->FUN_0042fb50(entry, &descriptor);
	}
}

// FUNCTION: LEGORACERS 0x0045a3f0
void RacePowerupManager::FUN_0045a3f0(LegoU32 p_elapsedMs)
{
	if (m_unk0x1968 != NULL) {
		m_unk0x1968->VTable0x10(p_elapsedMs);
	}
	if (m_unk0x196c != NULL) {
		m_unk0x196c->VTable0x10(p_elapsedMs);
	}
	if (m_unk0x1970 != NULL) {
		m_unk0x1970->VTable0x10(p_elapsedMs);
	}
	if (m_unk0x1974 != NULL) {
		m_unk0x1974->VTable0x10(p_elapsedMs);
	}

	if (m_unk0x028 != NULL) {
		LegoU32 i;

		for (i = 0; i < m_unk0x034; i++) {
			m_unk0x028[i].FUN_00457710(p_elapsedMs);
		}

		for (i = 0; i < m_unk0x038; i++) {
			m_unk0x02c[i].FUN_00453690(p_elapsedMs);
		}
	}
}

// FUNCTION: LEGORACERS 0x0045a490
void RacePowerupManager::FUN_0045a490(LegoU32 p_elapsedMs)
{
	FUN_0045a3f0(p_elapsedMs);

	m_unk0x199c += static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs)) * g_unk0x004b1874;
	if (m_unk0x199c > g_unk0x004b1878) {
		m_unk0x199c -= g_unk0x004b1878;
	}

	Field0x1880* node0x1880;
	for (node0x1880 = m_unk0x1880; node0x1880 != NULL; node0x1880 = node0x1880->GetNext()) {
		node0x1880->VTable0x08(p_elapsedMs);
	}

	Field0x270* node0x270;
	for (node0x270 = m_unk0x193c; node0x270 != NULL; node0x270 = node0x270->GetNext()) {
		node0x270->FUN_004217d0(p_elapsedMs);
	}

	for (node0x270 = m_unk0x1940; node0x270 != NULL; node0x270 = node0x270->GetNext()) {
		node0x270->FUN_004217d0(p_elapsedMs);
	}

	m_unk0x18bc.FUN_00451860(p_elapsedMs);

	node0x1880 = m_unk0x1880;
	Field0x1880* previous0x1880 = NULL;
	while (node0x1880 != NULL) {
		Field0x1880* next0x1880 = node0x1880->GetNext();
		if (node0x1880->GetUnk0x04() == 6) {
			if (previous0x1880 == NULL) {
				m_unk0x1880 = next0x1880;
			}
			else {
				previous0x1880->SetNext(next0x1880);
			}

			node0x1880->VTable0x1c();

			switch (node0x1880->VTable0x18()) {
			case 1:
				switch (node0x1880->GetState()) {
				case 0:
					node0x1880->SetNext(m_unk0x088);
					m_unk0x088 = node0x1880;
					break;
				case 1:
					node0x1880->SetNext(m_unk0x08c);
					m_unk0x08c = node0x1880;
					break;
				case 2:
					node0x1880->SetNext(m_unk0x090);
					m_unk0x090 = node0x1880;
					break;
				case 3:
					node0x1880->SetNext(m_unk0x094);
					m_unk0x094 = node0x1880;
					break;
				}
				break;
			case 4:
				switch (node0x1880->GetState()) {
				case 0:
					node0x1880->SetNext(m_unk0x07c);
					m_unk0x07c = node0x1880;
					break;
				case 1:
					node0x1880->SetNext(m_unk0x080);
					m_unk0x080 = node0x1880;
					break;
				case 2:
					node0x1880->SetNext(m_unk0x078);
					m_unk0x078 = node0x1880;
					break;
				case 3:
					node0x1880->SetNext(m_unk0x084);
					m_unk0x084 = node0x1880;
					break;
				}
				break;
			case 2:
				node0x1880->SetNext(m_unk0x098);
				m_unk0x098 = node0x1880;
				break;
			case 3:
				if (node0x1880->GetState() > 2) {
					if (node0x1880->GetState() == 3) {
						node0x1880->SetNext(m_unk0x0a0);
						m_unk0x0a0 = node0x1880;
					}
				}
				else {
					node0x1880->SetNext(m_unk0x09c);
					m_unk0x09c = node0x1880;
				}
				break;
			}
		}
		else {
			previous0x1880 = node0x1880;
		}

		node0x1880 = next0x1880;
	}

	node0x270 = m_unk0x193c;
	Field0x270* previous0x270 = NULL;
	while (node0x270 != NULL) {
		Field0x270* next0x270 = node0x270->GetNext();
		if (node0x270->GetUnk0x04() == 1) {
			if (previous0x270 == NULL) {
				m_unk0x193c = next0x270;
			}
			else {
				previous0x270->SetNext(next0x270);
			}

			node0x270->SetNext(m_unk0x1944);
			m_unk0x1944 = node0x270;
		}
		else {
			previous0x270 = node0x270;
		}

		node0x270 = next0x270;
	}

	node0x270 = m_unk0x1940;
	previous0x270 = NULL;
	while (node0x270 != NULL) {
		Field0x270* next0x270 = node0x270->GetNext();
		if (node0x270->GetUnk0x04() == 1) {
			if (previous0x270 == NULL) {
				m_unk0x1940 = next0x270;
			}
			else {
				previous0x270->SetNext(next0x270);
			}

			node0x270->SetNext(m_unk0x1948);
			m_unk0x1948 = node0x270;
		}
		else {
			previous0x270 = node0x270;
		}

		node0x270 = next0x270;
	}

	if (m_unk0x060 != NULL) {
		m_unk0x060->FUN_00416090(p_elapsedMs);
	}

	if (m_unk0x1958 != NULL) {
		FUN_0045b7a0(m_unk0x1958, 0, 3);
	}
	if (m_unk0x195c != NULL) {
		FUN_0045b7a0(m_unk0x195c, 3, 3);
	}
	if (m_unk0x1960 != NULL) {
		FUN_0045b7a0(m_unk0x1960, 1, 3);
	}
	if (m_unk0x1964 != NULL) {
		FUN_0045b7a0(m_unk0x1964, 1, 4);
	}
}

// FUNCTION: LEGORACERS 0x0045a7b0
void RacePowerupManager::FUN_0045a7b0(LegoBool32 p_unk0x04)
{
	if (!p_unk0x04) {
		LegoU32 i;

		for (i = 0; i < m_unk0x034; i++) {
			m_unk0x028[i].VTable0x10(m_renderer);
		}

		for (i = 0; i < m_unk0x038; i++) {
			m_unk0x02c[i].VTable0x10(m_renderer);
		}
	}

	Field0x1880* node0x1880 = m_unk0x1880;
	while (node0x1880 != NULL) {
		if (!p_unk0x04 || (node0x1880->VTable0x18() == 3 && node0x1880->GetState() == 3)) {
			node0x1880->VTable0x0c(m_renderer);
		}

		node0x1880 = node0x1880->GetNext();
	}

	if (!p_unk0x04) {
		Field0x270* node0x193c = m_unk0x193c;
		while (node0x193c != NULL) {
			node0x193c->FUN_004513d0(m_renderer);
			node0x193c = node0x193c->GetNext();
		}

		Field0x270* node0x1940 = m_unk0x1940;
		while (node0x1940 != NULL) {
			node0x1940->FUN_004513d0(m_renderer);
			node0x1940 = node0x1940->GetNext();
		}
	}

	m_unk0x18bc.FUN_004518a0(m_renderer);
}

// FUNCTION: LEGORACERS 0x0045a8a0
void RacePowerupManager::FUN_0045a8a0()
{
	LegoU32 i;

	for (i = 0; i < m_unk0x034; i++) {
		m_unk0x028[i].VTable0x14(m_renderer);
	}

	for (i = 0; i < m_unk0x038; i++) {
		m_unk0x02c[i].VTable0x14(m_renderer);
	}

	Field0x1880* node0x1880 = m_unk0x1880;
	while (node0x1880 != NULL) {
		node0x1880->VTable0x10(m_renderer);
		node0x1880 = node0x1880->GetNext();
	}

	Field0x270* node0x193c = m_unk0x193c;
	while (node0x193c != NULL) {
		node0x193c->FUN_00421ae0(m_renderer);
		node0x193c = node0x193c->GetNext();
	}

	Field0x270* node0x1940 = m_unk0x1940;
	while (node0x1940 != NULL) {
		node0x1940->FUN_00421ae0(m_renderer);
		node0x1940 = node0x1940->GetNext();
	}
}

// FUNCTION: LEGORACERS 0x0045a950
void RacePowerupManager::FUN_0045a950(RaceState::Racer* p_racer, LegoU32 p_unk0x08)
{
	switch (p_unk0x08) {
	case 0:
		FUN_0045aa30(p_racer, 0);
		return;
	case 1:
		FUN_0045ab50(p_racer, 1);
		return;
	case 2:
		FUN_0045ac80(p_racer, 2);
		return;
	case 3:
		FUN_0045af80(p_racer, 3);
		return;
	default:
		return;
	}
}

// FUNCTION: LEGORACERS 0x0045a9b0
void RacePowerupManager::FUN_0045a9b0(RaceState::Racer* p_racer, LegoU32 p_unk0x08)
{
	switch (p_unk0x08) {
	case 0:
		FUN_0045ace0(p_racer, 0);
		break;
	case 1:
		FUN_0045ad30(p_racer, 1);
		break;
	case 2:
		if (25 - m_unk0x187c >= 3) {
			FUN_0045adf0(p_racer, 2);
		}
		break;
	case 3:
		if (25 - m_unk0x187c >= 3) {
			FUN_0045aeb0(p_racer, 3);
		}
		break;
	}
}

// FUNCTION: LEGORACERS 0x0045aa30
LegoU32 RacePowerupManager::FUN_0045aa30(RaceState::Racer* p_racer, LegoU32 p_unk0x08)
{
	ActionSetup setup;
	setup.m_racer = p_racer;
	setup.m_unk0x08 = NULL;
	setup.m_unk0x04 = NULL;

	if (!m_unk0x1998) {
		GolVec3 position;
		p_racer->m_unk0x018.m_unk0x044->VTable0x04(&position);

		GolVec3 direction;
		p_racer->m_unk0x018.m_unk0x044->GetOrientationRow0(&direction);

		if (p_racer->m_unk0xd08 != 2) {
			setup.m_unk0x08 =
				m_unk0x050->FUN_0045c6a0(&position, &direction, g_unk0x004b1840, g_unk0x004b1844, g_unk0x004b184c);
		}

		if (!setup.m_unk0x08) {
			setup.m_unk0x04 =
				m_raceState->FUN_0043ca60(&position, &direction, g_unk0x004b1840, g_unk0x004b1844, g_unk0x004b1848);
		}
	}

	setup.m_unk0x0c = m_unk0x1998;
	setup.m_unk0x10 = 0;

	Field0x18a0* action = static_cast<Field0x18a0*>(m_unk0x088);
	if (!action) {
		action = static_cast<Field0x18a0*>(FUN_0045b2e0(1, p_unk0x08, -1, -1, -1));
	}
	else {
		m_unk0x088 = action->m_next;
	}

	action->m_next = m_unk0x1880;
	m_unk0x1880 = action;
	LegoU32 result = action->FUN_00451a50(&setup);
	action->m_state = p_unk0x08;
	return result;
}

// FUNCTION: LEGORACERS 0x0045ab50
LegoU32 RacePowerupManager::FUN_0045ab50(RaceState::Racer* p_racer, LegoU32 p_unk0x08)
{
	Field0x050::Entry* entry = NULL;

	GolVec3 position;
	p_racer->m_unk0x018.m_unk0x044->VTable0x04(&position);

	GolVec3 direction;
	p_racer->m_unk0x018.m_unk0x044->GetOrientationRow0(&direction);

	RaceState::Racer* target =
		m_raceState->FUN_0043c910(&position, &direction, g_unk0x004b185c, g_unk0x004b1860, g_unk0x004b1868);
	if (!target) {
		target = m_raceState->FUN_0043ca60(&position, &direction, g_unk0x004b185c, g_unk0x004b1864, g_unk0x004b186c);
		if (!target && p_racer->m_unk0xd08 != 2) {
			entry = m_unk0x050->FUN_0045c6a0(&position, &direction, g_unk0x004b1840, g_unk0x004b1844, g_unk0x004b184c);
		}
	}

	Field0x18a4* action = static_cast<Field0x18a4*>(m_unk0x08c);
	if (!action) {
		action = static_cast<Field0x18a4*>(FUN_0045b2e0(1, p_unk0x08, -1, -1, -1));
	}
	else {
		m_unk0x08c = action->m_next;
	}

	Field0x1880* next = m_unk0x1880;
	Field0x050::Entry* setupEntry = entry;
	action->m_next = next;
	GolWorldDatabase* worldDatabase = m_unk0x05c;
	m_unk0x1880 = action;
	Field0x18a4* activeAction = static_cast<Field0x18a4*>(m_unk0x1880);
	LegoU32 result = activeAction->FUN_00453de0(
		worldDatabase->GetUnk0x9c(),
		p_racer,
		target,
		setupEntry,
		GetMaterialAnimationItems0x18(),
		0
	);
	action->m_state = p_unk0x08;
	return result;
}

// FUNCTION: LEGORACERS 0x0045ac80
void RacePowerupManager::FUN_0045ac80(RaceState::Racer* p_racer, LegoU32 p_unk0x08)
{
	Field0x18a8* action = static_cast<Field0x18a8*>(m_unk0x090);
	if (!action) {
		action = static_cast<Field0x18a8*>(FUN_0045b2e0(1, p_unk0x08, -1, -1, -1));
	}
	else {
		m_unk0x090 = action->m_next;
	}

	action->m_next = m_unk0x1880;
	m_unk0x1880 = action;
	action->FUN_00454cb0(p_racer, m_unk0x1998);
	action->m_state = p_unk0x08;
}

// FUNCTION: LEGORACERS 0x0045ace0
void RacePowerupManager::FUN_0045ace0(RaceState::Racer* p_racer, LegoU32 p_unk0x08)
{
	Field0x1894* action = static_cast<Field0x1894*>(m_unk0x07c);
	if (!action) {
		action = static_cast<Field0x1894*>(FUN_0045b2e0(4, p_unk0x08, -1, -1, -1));
	}
	else {
		m_unk0x07c = action->m_next;
	}

	action->m_next = m_unk0x1880;
	m_unk0x1880 = action;
	action->FUN_00457230(p_racer);
	action->m_state = p_unk0x08;
}

// FUNCTION: LEGORACERS 0x0045ad30
LegoU32 RacePowerupManager::FUN_0045ad30(RaceState::Racer* p_racer, LegoU32 p_unk0x08)
{
	Field0x1898* action = static_cast<Field0x1898*>(m_unk0x080);
	if (!action) {
		action = static_cast<Field0x1898*>(FUN_0045b2e0(4, p_unk0x08, -1, -1, -1));
	}
	else {
		m_unk0x080 = action->m_next;
	}

	action->m_next = m_unk0x1880;
	m_unk0x1880 = action;

	GolVec3 position;
	p_racer->m_unk0x018.m_unk0x044->VTable0x04(&position);

	GolVec3 direction;
	p_racer->m_unk0x018.m_unk0x044->GetOrientationRow0(&direction);
	direction.m_x = -direction.m_x;
	direction.m_y = -direction.m_y;
	direction.m_z = -direction.m_z;

	RaceState::Racer* target =
		m_raceState->FUN_0043ca60(&position, &direction, g_unk0x004b1850, g_unk0x004b1854, g_unk0x004b1858);
	LegoU32 result = action->FUN_00452f60(p_racer, target);
	action->m_state = p_unk0x08;
	return result;
}

// FUNCTION: LEGORACERS 0x0045adf0
void RacePowerupManager::FUN_0045adf0(RaceState::Racer* p_racer, LegoU32 p_unk0x08)
{
	Field0x1890* action = static_cast<Field0x1890*>(m_unk0x078);
	if (!action) {
		action = static_cast<Field0x1890*>(FUN_0045b2e0(4, p_unk0x08, -1, -1, -1));
	}
	else {
		m_unk0x078 = action->m_next;
	}

	action->m_next = m_unk0x1880;
	m_unk0x1880 = action;

	GolAnimatedEntity* model0;
	if (m_unk0x05c->GetUnk0xc0NameEntries() == NULL) {
		model0 = NULL;
	}
	else {
		model0 = m_unk0x05c->GetUnk0xc0Name("magnet");
	}

	GolAnimatedEntity* model1;
	if (m_unk0x05c->GetUnk0xc0NameEntries() == NULL) {
		model1 = NULL;
	}
	else {
		model1 = m_unk0x05c->GetUnk0xc0Name("magring");
	}

	GolAnimatedEntity* model2;
	if (m_unk0x05c->GetUnk0xc0NameEntries() == NULL) {
		model2 = NULL;
	}
	else {
		model2 = m_unk0x05c->GetUnk0xc0Name("insd");
	}

	action->FUN_00455830(p_racer, model0, model1, model2);
	action->m_state = p_unk0x08;
}

// FUNCTION: LEGORACERS 0x0045aeb0
LegoU32 RacePowerupManager::FUN_0045aeb0(RaceState::Racer* p_racer, LegoU32 p_unk0x08)
{
	GolAnimatedEntity* model0;
	GolAnimatedEntity* model1;
	GolAnimatedEntity* model2;

	Field0x189c* action = static_cast<Field0x189c*>(m_unk0x084);
	if (!action) {
		action = static_cast<Field0x189c*>(FUN_0045b2e0(4, p_unk0x08, -1, -1, -1));
	}
	else {
		m_unk0x084 = action->m_next;
	}

	action->m_next = m_unk0x1880;
	m_unk0x1880 = action;

	if (m_unk0x05c->GetUnk0xc0NameEntries() == NULL) {
		model0 = NULL;
	}
	else {
		model0 = m_unk0x05c->GetUnk0xc0Name("curse");
	}

	if (m_unk0x05c->GetUnk0xc0NameEntries() == NULL) {
		model1 = NULL;
	}
	else {
		model1 = m_unk0x05c->GetUnk0xc0Name("cgreen");
	}

	if (m_unk0x05c->GetUnk0xc0NameEntries() == NULL) {
		model2 = NULL;
	}
	else {
		model2 = m_unk0x05c->GetUnk0xc0Name("cgreen2");
	}

	action->FUN_00452550(p_racer, model0, model1, model2, m_unk0x1998);
	const LegoU32 curseSubtype = 3;
	action->m_state = curseSubtype;
	return curseSubtype;
}

// FUNCTION: LEGORACERS 0x0045af80
void RacePowerupManager::FUN_0045af80(RaceState::Racer* p_racer, LegoU32 p_unk0x08)
{
	for (LegoU32 i = 0; i < 3; i++) {
		Field0x18ac* action = static_cast<Field0x18ac*>(m_unk0x094);
		if (!action) {
			action = static_cast<Field0x18ac*>(FUN_0045b2e0(1, p_unk0x08, -1, -1, -1));
		}
		else {
			m_unk0x094 = action->m_next;
		}

		action->m_next = m_unk0x1880;
		m_unk0x1880 = action;

		GolAnimatedEntity* model0;
		if (m_unk0x05c->GetUnk0xc0NameEntries() == NULL) {
			model0 = NULL;
		}
		else {
			model0 = m_unk0x05c->GetUnk0xc0Name("dmissil");
		}

		GolAnimatedEntity* model1;
		if (m_unk0x05c->GetUnk0xc0NameEntries() == NULL) {
			model1 = NULL;
		}
		else {
			model1 = m_unk0x05c->GetUnk0xc0Name("dmissil");
		}

		action->FUN_00456560(model1, model0, p_racer, i);
		action->m_state = p_unk0x08;
	}
}

// FUNCTION: LEGORACERS 0x0045b030
void RacePowerupManager::FUN_0045b030(RaceState::Racer* p_racer, LegoU32 p_unk0x08)
{
	if (25 - m_unk0x187c >= 2) {
		LegoU32 subtype = p_unk0x08;
		Field0x18b0* action = static_cast<Field0x18b0*>(m_unk0x098);
		if (action == NULL) {
			action = static_cast<Field0x18b0*>(FUN_0045b2e0(2, 0, 1, 2, 3));
		}
		else {
			m_unk0x098 = action->GetNext();
		}

		action->SetNext(m_unk0x1880);
		m_unk0x1880 = action;

		GolAnimatedEntity* model;
		GolAnimatedEntity* inputModel;
		switch (subtype) {
		case 0:
			if (m_unk0x05c->GetUnk0xc0NameEntries() == NULL) {
				model = NULL;
			}
			else {
				model = m_unk0x05c->GetUnk0xc0Name("shield0");
			}

			if (m_unk0x05c->GetUnk0xc0NameEntries()) {
				inputModel = m_unk0x05c->GetUnk0xc0Name("shldin0");
			}
			else {
				inputModel = NULL;
			}
			break;
		case 1:
			if (m_unk0x05c->GetUnk0xc0NameEntries() == NULL) {
				model = NULL;
			}
			else {
				model = m_unk0x05c->GetUnk0xc0Name("shield1");
			}

			if (m_unk0x05c->GetUnk0xc0NameEntries()) {
				inputModel = m_unk0x05c->GetUnk0xc0Name("shldin1");
			}
			else {
				inputModel = NULL;
			}
			break;
		case 2:
			if (m_unk0x05c->GetUnk0xc0NameEntries() == NULL) {
				model = NULL;
			}
			else {
				model = m_unk0x05c->GetUnk0xc0Name("shield2");
			}

			if (m_unk0x05c->GetUnk0xc0NameEntries()) {
				inputModel = m_unk0x05c->GetUnk0xc0Name("shldin2");
			}
			else {
				inputModel = NULL;
			}
			break;
		case 3:
			if (m_unk0x05c->GetUnk0xc0NameEntries() == NULL) {
				model = NULL;
			}
			else {
				model = m_unk0x05c->GetUnk0xc0Name("shield3");
			}

			if (m_unk0x05c->GetUnk0xc0NameEntries()) {
				inputModel = m_unk0x05c->GetUnk0xc0Name("shldin3");
			}
			else {
				inputModel = NULL;
			}
			break;
		default:
			model = NULL;
			inputModel = NULL;
			break;
		}

		action->FUN_0045bd30(p_racer, subtype, model, inputModel);
		action->SetState(subtype);
	}
}

// FUNCTION: LEGORACERS 0x0045b1e0
void RacePowerupManager::FUN_0045b1e0(RaceState::Racer* p_racer, LegoU32 p_unk0x08)
{
	if (p_unk0x08 == 3) {
		FUN_0045b260(p_racer, 3);
	}
	else if (25 - m_unk0x187c >= 3) {
		Field0x18b4* action = static_cast<Field0x18b4*>(m_unk0x09c);
		if (!action) {
			action = static_cast<Field0x18b4*>(FUN_0045b2e0(3, 0, 1, 2, -1));
		}
		else {
			m_unk0x09c = action->m_next;
		}

		action->m_next = m_unk0x1880;
		m_unk0x1880 = action;
		action->FUN_0045c8f0(p_racer, p_unk0x08);
		action->m_state = p_unk0x08;
	}
}

// FUNCTION: LEGORACERS 0x0045b260
LegoU32 RacePowerupManager::FUN_0045b260(RaceState::Racer* p_racer, LegoU32 p_unk0x08)
{
	Field0x18b8* action = static_cast<Field0x18b8*>(m_unk0x0a0);
	if (!action) {
		action = static_cast<Field0x18b8*>(FUN_0045b2e0(3, p_unk0x08, -1, -1, -1));
	}
	else {
		m_unk0x0a0 = action->m_next;
	}

	action->m_next = m_unk0x1880;
	m_unk0x1880 = action;

	GolModelEntity* model;
	if (m_unk0x05c->GetUnk0xb4NameEntries() == NULL) {
		model = NULL;
	}
	else {
		model = m_unk0x05c->GetUnk0xb4Name("warpprt");
	}

	LegoU32 result = action->FUN_0045d560(p_racer, model, m_unk0x1998);
	action->m_state = p_unk0x08;
	return result;
}

// FUNCTION: LEGORACERS 0x0045b2e0
RacePowerupManager::Field0x1880* RacePowerupManager::FUN_0045b2e0(
	LegoU32 p_unk0x04,
	LegoU32 p_unk0x08,
	LegoS32 p_unk0x0c,
	LegoS32 p_unk0x10,
	LegoS32 p_unk0x14
)
{
	Field0x1880* previous = NULL;
	Field0x1880* bestPrevious = NULL;
	Field0x1880* best = NULL;
	LegoS32 bestScore = 0;
	LegoU32 bestPriority = 0xffffffff;

	for (Field0x1880* action = m_unk0x1880; action != NULL; action = action->GetNext()) {
		if (action->VTable0x18() == static_cast<LegoS32>(p_unk0x04)) {
			LegoU32 subtype = action->GetState();
			if (subtype == p_unk0x08 || subtype == static_cast<LegoU32>(p_unk0x0c) ||
				subtype == static_cast<LegoU32>(p_unk0x10) || subtype == static_cast<LegoU32>(p_unk0x14)) {
				LegoS32 score = action->GetUnk0x04();
				if (score > bestScore) {
					bestPriority = action->GetUnk0x008();
					bestScore = action->GetUnk0x04();
					best = action;
					bestPrevious = previous;
				}
				else if (score == bestScore) {
					LegoU32 priority = action->GetUnk0x008();
					if (priority < bestPriority) {
						bestScore = action->GetUnk0x04();
						bestPriority = priority;
						best = action;
						bestPrevious = previous;
					}
				}
			}
		}

		previous = action;
	}

	if (bestPrevious == NULL) {
		m_unk0x1880 = best->GetNext();
	}
	else {
		bestPrevious->SetNext(best->GetNext());
	}

	best->SetNext(NULL);
	best->VTable0x1c();

	return best;
}

// STUB: LEGORACERS 0x0045b3a0
RacePowerupManager::Field0x270* __stdcall RacePowerupManager::FUN_0045b3a0(Field0x270** p_head)
{
	Field0x270* selected = NULL;
	Field0x270* selectedPrevious = NULL;
	LegoU32 selectedRemaining = 0xffffffff;
	LegoS32 targetState = 3;
	LegoU32 pass = 0;
	Field0x270* current = *p_head;
	Field0x270* head = current;

	for (;;) {
		Field0x270* previous = NULL;

		while (current != NULL) {
			if (current->GetUnk0x04() == targetState && current->GetUnk0x238() < selectedRemaining) {
				selectedRemaining = current->GetUnk0x238();
				selected = current;
				selectedPrevious = previous;
			}

			previous = current;
			current = current->GetNext();
		}

		if (selected == NULL) {
			current = head;
			targetState = 2;
			pass++;
			if (pass < 3) {
				continue;
			}

			Field0x270* result = current;
			*p_head = result->GetNext();
			result->SetNext(NULL);
			return result;
		}

		break;
	}

	if (selectedPrevious == NULL) {
		*p_head = selected->GetNext();
		selected->SetNext(selectedPrevious);
		return selected;
	}

	selectedPrevious->SetNext(selected->GetNext());
	selected->SetNext(NULL);
	return selected;
}

// FUNCTION: LEGORACERS 0x0045b470
void RacePowerupManager::FUN_0045b470(const GolVec3* p_position, undefined4 p_unk0x08, RaceState::Racer* p_racer)
{
	Field0x270* item = m_unk0x1944;
	if (item == NULL) {
		item = FUN_0045b3a0(&m_unk0x193c);
	}
	else {
		m_unk0x1944 = item->GetNext();
	}

	item->SetNext(m_unk0x193c);
	m_unk0x193c = item;
	item->FUN_00421520(p_position, p_unk0x08, p_racer);
}

// FUNCTION: LEGORACERS 0x0045b4d0
void RacePowerupManager::FUN_0045b4d0(const GolVec3* p_position, undefined4 p_unk0x08, RaceState::Racer* p_racer)
{
	FUN_0045b470(p_position, p_unk0x08, p_racer);
}

// FUNCTION: LEGORACERS 0x0045b4f0
void RacePowerupManager::FUN_0045b4f0(const GolVec3* p_position, undefined4 p_unk0x08, RaceState::Racer* p_racer)
{
	Field0x270* item = m_unk0x1948;
	if (item == NULL) {
		item = FUN_0045b3a0(&m_unk0x1940);
	}
	else {
		m_unk0x1948 = item->GetNext();
	}

	item->SetNext(m_unk0x1940);
	m_unk0x1940 = item;
	item->FUN_00421520(p_position, p_unk0x08, p_racer);
}

// FUNCTION: LEGORACERS 0x0045b550
void RacePowerupManager::FUN_0045b550(const GolVec3* p_unk0x04, const GolVec3* p_position, RaceState::Racer* p_racer)
{
	GolVec3 position;

	g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
	LegoU32 count = (static_cast<LegoU32>(g_unk0x004befec[g_unk0x004c6ee4]) % c_randomBurstMax) + 1;
	if (count != 0) {
		Field0x18bc* field0x18bc = &m_unk0x18bc;
		LegoU32 remaining = count;

		do {
			g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
			position.m_z = 0.0f;
			LegoS32 offsetX = g_unk0x004befec[g_unk0x004c6ee4] % c_randomOffsetRange;
			position.m_x = p_position->m_x + offsetX * 0.0040000002f - g_unk0x004b02e0;

			g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
			LegoS32 offsetY = g_unk0x004befec[g_unk0x004c6ee4] % c_randomOffsetRange;

			position.m_y = p_position->m_y + offsetY * 0.0040000002f - g_unk0x004b02e0;
			field0x18bc->FUN_004517c0(p_unk0x04, &position, p_racer);
		} while (--remaining != 0);
	}
}

// FUNCTION: LEGORACERS 0x0045b640
void RacePowerupManager::FUN_0045b640(RaceState::Racer* p_racer)
{
	for (LegoU32 i = 0; i < m_unk0x1884[8]; i++) {
		Field0x18b0* action = &m_unk0x18b0[i];
		if (action->GetUnk0x04() > 1 && action->m_unk0x20 == p_racer) {
			action->SetUnk0x04(6);
		}
	}
}

// FUNCTION: LEGORACERS 0x0045b690 FOLDED
void RacePowerupManager::FUN_0045b690(RaceState::Racer* p_racer)
{
	for (LegoU32 i = 0; i < m_unk0x1884[9]; i++) {
		if (m_unk0x18b4[i].m_unk0x004 > 1 && m_unk0x18b4[i].m_unk0x018 == p_racer) {
			m_unk0x18b4[i].m_unk0x004 = 6;
			m_unk0x18b4[i].m_unk0x018 = NULL;
		}
	}
}

// FUNCTION: LEGORACERS 0x0045b6f0
void RacePowerupManager::FUN_0045b6f0(RaceState::Racer* p_racer)
{
	for (LegoU32 i = 0; i < m_unk0x1884[0]; i++) {
		Field0x1890* action = &m_unk0x1890[i];
		if (action->GetUnk0x04() > 1 && action->m_unk0x78 == p_racer) {
			action->SetUnk0x04(6);
		}
	}
}

// FUNCTION: LEGORACERS 0x0045b740
void RacePowerupManager::FUN_0045b740(RaceState::Racer* p_racer)
{
	for (LegoU32 i = 0; i < m_unk0x1884[10]; i++) {
		Field0x18b8* item = &m_unk0x18b8[i];
		if (item->m_unk0x0a8 == p_racer) {
			if (item->m_unk0x004 == 2) {
				item->m_unk0x004 = 6;
			}
			else if (item->m_unk0x004 == 3) {
				item->m_unk0x008 = 0;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x0045b7a0
void RacePowerupManager::FUN_0045b7a0(Field0x1958Resource* p_resource, LegoU32 p_unk0x08, LegoS32 p_unk0x0c)
{
	RaceState::Racer* racer = m_raceState->GetCurrentRacer();
	if (racer == NULL) {
		if (p_resource->VTable0x0c()) {
			p_resource->VTable0x08();
		}
		return;
	}

	ResourceBase0x30* nearest = NULL;
	LegoFloat nearestDistanceSquared = FLT_MAX;
	GolVec3 referencePosition;
	GolVec3 position;
	GolVec3 direction;

	racer->m_unk0x018.GetUnk0x044()->VTable0x04(&referencePosition);

	for (Field0x1880* node = m_unk0x1880; node != NULL; node = node->GetNext()) {
		if (node->VTable0x18() == 1 && node->GetState() == p_unk0x08 && node->GetUnk0x04() == p_unk0x0c) {
			ResourceBase0x30* resource = static_cast<ResourceBase0x30*>(node);
			resource->VTable0x24(&position);

			LegoFloat dx = referencePosition.m_x - position.m_x;
			LegoFloat dy = referencePosition.m_y - position.m_y;
			LegoFloat dz = referencePosition.m_z - position.m_z;
			LegoFloat distanceSquared = dz * dz + dy * dy + dx * dx;
			if (distanceSquared < nearestDistanceSquared) {
				nearestDistanceSquared = distanceSquared;
				nearest = resource;
			}
		}
	}

	if (nearestDistanceSquared < g_unk0x004c7644) {
		if (!p_resource->VTable0x0c()) {
			p_resource->VTable0x04(1);
		}

		nearest->VTable0x24(&referencePosition);
		nearest->VTable0x28(&direction);

		p_resource->m_unk0x18 = referencePosition;
		p_resource->m_unk0x24.m_x = direction.m_x;
		p_resource->m_unk0x24.m_y = direction.m_y;
		p_resource->m_unk0x24.m_z = direction.m_z;
	}
	else if (p_resource->VTable0x0c()) {
		p_resource->VTable0x08();
	}
}

// FUNCTION: LEGORACERS 0x0045b900
void RacePowerupManager::FUN_0045b900()
{
	LegoU32 i;

	for (i = 0; i < m_unk0x034; i++) {
		m_unk0x028[i].SetFlags0x50Bit0();
	}

	for (i = 0; i < m_unk0x038; i++) {
		m_unk0x02c[i].SetFlags0x50Bit0();
	}
}

// FUNCTION: LEGORACERS 0x0045b950
void RacePowerupManager::FUN_0045b950()
{
	LegoU32 i;

	for (i = 0; i < m_unk0x034; i++) {
		m_unk0x028[i].ClearFlags0x50Bit0();
	}

	for (i = 0; i < m_unk0x038; i++) {
		m_unk0x02c[i].ClearFlags0x50Bit0();
	}
}

// FUNCTION: LEGORACERS 0x0045b9a0
LegoBool32 RacePowerupManager::FUN_0045b9a0(RaceState::Racer* p_racer)
{
	Field0x1880* node = m_unk0x1880;
	while (node != NULL) {
		if (node->VTable0x18() == 1 && static_cast<Field0x18b0*>(node)->FUN_0045bc40() == p_racer) {
			break;
		}

		node = node->GetNext();
	}

	if (node == NULL) {
		return FALSE;
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0045b9e0 FOLDED
GolAnimatedEntity* RacePowerupManager::FUN_0045b9e0()
{
	LegoU32 index = 0;
	LegoU32 flags = m_unk0x1878;
	LegoU32 count = m_unk0x187c;

	if (count == sizeOfArray(m_unk0x0a4)) {
		return NULL;
	}

	for (; flags & 1; index++) {
		if (index >= sizeOfArray(m_unk0x0a4)) {
			break;
		}

		flags >>= 1;
	}

	m_unk0x1878 |= 1 << index;
	m_unk0x187c = count + 1;
	return &m_unk0x0a4[index];
}

// FUNCTION: LEGORACERS 0x0045ba40 FOLDED
LegoU32 RacePowerupManager::FUN_0045ba40(GolAnimatedEntity* p_entity)
{
	LegoS32 index = p_entity - m_unk0x0a4;

	m_unk0x1878 &= ~(1 << index);
	m_unk0x187c--;

	return m_unk0x187c;
}

// FUNCTION: LEGORACERS 0x0045ba90
DuskwindBananaRelic0x24* RacePowerupManager::FUN_0045ba90(LegoU32* p_unk0x04)
{
	switch (*p_unk0x04) {
	case 1:
		return m_unk0x1978[c_unk0x1978Slot1A];
	case 2:
		return m_unk0x1978[c_unk0x1978Slot2A];
	case 3:
		return m_unk0x1978[c_unk0x1978Slot3A];
	case 4:
		return m_unk0x1978[c_unk0x1978Slot4A];
	default:
		return NULL;
	}
}

// FUNCTION: LEGORACERS 0x0045bae0
DuskwindBananaRelic0x24* RacePowerupManager::FUN_0045bae0(LegoU32* p_unk0x04)
{
	switch (*p_unk0x04) {
	case 1:
		return m_unk0x1978[c_unk0x1978Slot1B];
	case 2:
		return m_unk0x1978[c_unk0x1978Slot2B];
	case 3:
		return m_unk0x1978[c_unk0x1978Slot3B];
	case 4:
		return m_unk0x1978[c_unk0x1978Slot4B];
	default:
		return NULL;
	}
}

// FUNCTION: LEGORACERS 0x0045bb30
void RacePowerupManager::FUN_0045bb30()
{
	LegoU32 i;

	for (i = 0; i < m_unk0x034; i++) {
		m_unk0x028[i].VTable0x0c();
	}

	for (i = 0; i < m_unk0x038; i++) {
		m_unk0x02c[i].VTable0x0c();
	}

	Field0x270* node0x193c = m_unk0x193c;
	while (node0x193c != NULL) {
		node0x193c->FUN_004217b0();
		node0x193c = node0x193c->GetNext();
	}

	Field0x270* node0x1940 = m_unk0x1940;
	while (node0x1940 != NULL) {
		node0x1940->FUN_004217b0();
		node0x1940 = node0x1940->GetNext();
	}

	m_unk0x18bc.FUN_004518d0();

	Field0x1880* node0x1880 = m_unk0x1880;
	while (node0x1880 != NULL) {
		node0x1880->SetUnk0x04(6);
		node0x1880 = node0x1880->GetNext();
	}

	FUN_0045a490(0);
}
