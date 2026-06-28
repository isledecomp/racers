#include "audio/spatialsoundinstance.h"
#include "decomp.h"
#include "golbinparser.h"
#include "golboundedentity.h"
#include "golcollidableentity.h"
#include "golerror.h"
#include "golmodelbase.h"
#include "golscenenode.h"
#include "goltransformbase.h"
#include "menu/runtime/cutsceneparticle.h"
#include "race/racesession.h"
#include "world/golworlddatabase.h"

DECOMP_SIZE_ASSERT(RaceSession::Field0x2098, 0x90)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::EvbTxtParser, 0x1fc)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::Params, 0x34)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::Field0x6c, 0x08)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::Resource, 0x20)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::Resource0x24::InitParams, 0x18)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::Resource0x24, 0x24)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::Resource0x2c::InitParams, 0x20)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::Resource0x2c, 0x2c)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::Resource0x30::InitParams, 0x20)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::Resource0x30, 0x30)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::Resource0x34::InitParams, 0x38)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::Resource0x34, 0x34)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::AnimatedPartResource0x34::InitParams, 0x3c)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::AnimatedPartResource0x34, 0x34)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::ModelDistanceResource0x34::InitParams, 0x24)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::ModelDistanceResource0x34, 0x34)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::NodeTransformResource0x2c::InitParams, 0x24)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::NodeTransformResource0x2c, 0x2c)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::SkyStateResource0x34::InitParams, 0x2c)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::SkyStateResource0x34, 0x34)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::Resource0x38::InitParams, 0x30)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::Resource0x38, 0x38)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::Resource0x48, 0x48)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::Resource0x5c::InitParams, 0x4c)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::Resource0x5c, 0x5c)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::Resource0x64::InitParams, 0x5c)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::Resource0x64, 0x64)

extern LegoU16 g_unk0x004befec[1024];
extern LegoU32 g_unk0x004c6ee4;

// FUNCTION: LEGORACERS 0x0045c330 FOLDED
LegoU32 RaceSession::Field0x2098::Resource0x34::VTable0x18()
{
	return 2;
}

// FUNCTION: LEGORACERS 0x0045e150
RaceSession::Field0x2098::SkyStateResource0x34::SkyStateResource0x34()
{
	FUN_0045e1f0();
	m_flags0x1c = 0;
}

// FUNCTION: LEGORACERS 0x0045e1a0
RaceSession::Field0x2098::SkyStateResource0x34::~SkyStateResource0x34()
{
	FUN_0045e280();
}

// FUNCTION: LEGORACERS 0x0045e1f0
void RaceSession::Field0x2098::SkyStateResource0x34::FUN_0045e1f0()
{
	m_unk0x20 = NULL;
	m_unk0x24[0] = '\0';
	m_unk0x2c = 0;
	m_flags0x30 = 0;
}

// FUNCTION: LEGORACERS 0x0045e200
void RaceSession::Field0x2098::SkyStateResource0x34::FUN_0045e200(InitParams* p_params)
{
	if (m_state0x18) {
		FUN_0045e280();
	}

	m_unk0x14 = p_params->m_unk0x00;
	LegoS32* eventId = p_params->m_eventIds;
	LegoU32 i;
	for (i = 0; i < sizeOfArray(m_eventIds); i++) {
		m_eventIds[i] = *eventId++;
	}

	m_unk0x04 = p_params->m_eventTable;
	m_unk0x20 = p_params->m_unk0x14;
	m_unk0x2c = p_params->m_unk0x20;
	m_flags0x30 = p_params->m_flags0x28;
	::strncpy(m_unk0x24, p_params->m_unk0x18, sizeof(m_unk0x24));
	if (p_params->m_unk0x24) {
		m_flags0x1c |= c_flags0x1cBit2;
	}

	m_state0x18 = c_state0x18One;
	m_flags0x1c &= ~c_flags0x1cBit5;
}

// FUNCTION: LEGORACERS 0x0045e280
void RaceSession::Field0x2098::SkyStateResource0x34::FUN_0045e280()
{
	VTable0x0c();
	FUN_0045e1f0();
	Reset();
}

// FUNCTION: LEGORACERS 0x0045e2a0
void RaceSession::Field0x2098::SkyStateResource0x34::VTable0x04(GolVec3*)
{
	if (m_unk0x24[0]) {
		m_unk0x20->FUN_0041d150(m_unk0x24, m_unk0x2c);
	}

	if (m_flags0x30 & c_flags0x30Bit0) {
		m_unk0x20->m_unk0xc4 &= ~RaceSession::Field0x2f90::c_flag0xc4Bit0;
	}

	if (m_flags0x30 & c_flags0x30Bit1) {
		m_unk0x20->m_unk0xc4 |= RaceSession::Field0x2f90::c_flag0xc4Bit0;
	}

	if (m_flags0x30 & c_flags0x30Bit2) {
		m_unk0x20->m_unk0xc4 &= ~RaceSession::Field0x2f90::c_flag0xc4Bit1;
	}

	if (m_flags0x30 & c_flags0x30Bit3) {
		m_unk0x20->m_unk0xc4 |= RaceSession::Field0x2f90::c_flag0xc4Bit1;
	}

	FUN_0045edd0(m_state0x18, 1);
	m_state0x18 = c_state0x18Five;
}

// FUNCTION: LEGORACERS 0x0045e320
void RaceSession::Field0x2098::SkyStateResource0x34::VTable0x0c()
{
	FUN_0045edd0(m_state0x18, 3);
	m_state0x18 = c_state0x18One;
	m_flags0x1c &= ~c_flags0x1cBit5;
}

// FUNCTION: LEGORACERS 0x0045e340
LegoU32 RaceSession::Field0x2098::SkyStateResource0x34::VTable0x18()
{
	return 5;
}

// FUNCTION: LEGORACERS 0x0045e5e0
RaceSession::Field0x2098::Resource0x2c::Resource0x2c()
{
	m_unk0x20.m_x = 0.0f;
	m_unk0x20.m_y = 0.0f;
	m_unk0x20.m_z = 0.0f;
}

// FUNCTION: LEGORACERS 0x0045e600
RaceSession::Field0x2098::Resource0x2c::~Resource0x2c()
{
	FUN_0045e6b0();
}

// FUNCTION: LEGORACERS 0x0045e650
void RaceSession::Field0x2098::Resource0x2c::FUN_0045e650(InitParams* p_params)
{
	if (m_state0x18) {
		FUN_0045e6b0();
	}

	m_unk0x14 = p_params->m_unk0x00;
	LegoS32* eventId = p_params->m_eventIds;
	LegoU32 i;
	for (i = 0; i < sizeOfArray(m_eventIds); i++) {
		m_eventIds[i] = *eventId++;
	}

	m_unk0x04 = p_params->m_eventTable;
	m_unk0x20.m_x = p_params->m_unk0x14.m_x;
	m_unk0x20.m_y = p_params->m_unk0x14.m_y;
	m_unk0x20.m_z = p_params->m_unk0x14.m_z;
	m_state0x18 = c_state0x18Four;
}

// FUNCTION: LEGORACERS 0x0045e6b0
void RaceSession::Field0x2098::Resource0x2c::FUN_0045e6b0()
{
	m_unk0x20.m_x = 0.0f;
	m_unk0x20.m_y = 0.0f;
	m_unk0x20.m_z = 0.0f;
	Reset();
}

// FUNCTION: LEGORACERS 0x0045e6c0
void RaceSession::Field0x2098::Resource0x2c::VTable0x00(RaceState::Racer* p_racer)
{
	FUN_0045edd0(1, 1);
	if (p_racer) {
		p_racer->FUN_00439e60(&m_unk0x20);
	}
}

// FUNCTION: LEGORACERS 0x0045e6f0
void RaceSession::Field0x2098::Resource0x2c::VTable0x08(RaceState::Racer* p_racer)
{
	FUN_0045edd0(m_state0x18, 3);
	if (p_racer) {
		p_racer->FUN_00439e90();
	}

	m_state0x18 = c_state0x18Four;
}

// FUNCTION: LEGORACERS 0x0045e720
LegoU32 RaceSession::Field0x2098::Resource0x2c::VTable0x18()
{
	return 11;
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RaceSession::Field0x2098::Resource0x2c::FUN_004513d0(undefined4)
{
}

// FUNCTION: LEGORACERS 0x0045e730
RaceSession::Field0x2098::Resource0x30::Resource0x30()
{
	FUN_0045e7d0();
	m_flags0x1c = 0;
}

// FUNCTION: LEGORACERS 0x0045e780
RaceSession::Field0x2098::Resource0x30::~Resource0x30()
{
	FUN_0045e860();
}

// FUNCTION: LEGORACERS 0x0045e7d0
void RaceSession::Field0x2098::Resource0x30::FUN_0045e7d0()
{
	m_unk0x20 = -1;
	m_unk0x24 = 0;
	m_unk0x28 = 0;
	m_flags0x2c = 0;
}

// FUNCTION: LEGORACERS 0x0045e7f0
void RaceSession::Field0x2098::Resource0x30::FUN_0045e7f0(InitParams* p_params)
{
	if (m_state0x18) {
		FUN_0045e860();
	}

	m_unk0x14 = p_params->m_unk0x00;
	LegoS32* eventId = p_params->m_eventIds;
	LegoU32 i;
	for (i = 0; i < sizeOfArray(m_eventIds); i++) {
		m_eventIds[i] = *eventId++;
	}

	m_unk0x04 = p_params->m_eventTable;
	m_unk0x20 = p_params->m_unk0x14;
	m_unk0x24 = p_params->m_unk0x18;
	m_unk0x28 = 0;
	if (p_params->m_unk0x1c) {
		m_flags0x1c |= c_flags0x1cBit2;
	}

	m_state0x18 = c_state0x18Four;
}

// FUNCTION: LEGORACERS 0x0045e860
void RaceSession::Field0x2098::Resource0x30::FUN_0045e860()
{
	VTable0x0c();
	FUN_0045e7d0();
	Reset();
}

// FUNCTION: LEGORACERS 0x0045e880
void RaceSession::Field0x2098::Resource0x30::VTable0x04(GolVec3*)
{
	m_unk0x28 = m_unk0x24;
	FUN_0045edd0(1, 1);
	m_state0x18 = c_state0x18Three;
}

// FUNCTION: LEGORACERS 0x0045e8a0
void RaceSession::Field0x2098::Resource0x30::VTable0x0c()
{
	if (m_unk0x28 <= 0 && !(m_flags0x2c & 1)) {
		FUN_0045edd0(m_state0x18, 3);
		m_state0x18 = c_state0x18Four;
	}
}

// FUNCTION: LEGORACERS 0x0045e8d0
void RaceSession::Field0x2098::Resource0x30::VTable0x14(LegoU32 p_elapsedMs)
{
	Resource::VTable0x14(p_elapsedMs);
	if (m_state0x18 != c_state0x18Four) {
		if (p_elapsedMs > m_unk0x28) {
			m_unk0x28 = 0;
		}
		else {
			m_unk0x28 -= p_elapsedMs;
		}

		if (!m_unk0x28) {
			VTable0x0c();
		}
	}
}

// FUNCTION: LEGORACERS 0x0045e910
LegoU32 RaceSession::Field0x2098::Resource0x30::VTable0x18()
{
	return 6;
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RaceSession::Field0x2098::Resource0x30::FUN_004513d0(undefined4)
{
}

// FUNCTION: LEGORACERS 0x0044f580 FOLDED
LegoU32 RaceSession::Field0x2098::Resource0x64::VTable0x18()
{
	return 3;
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RaceSession::Field0x2098::Resource0x64::FUN_004513d0(undefined4)
{
}

// FUNCTION: LEGORACERS 0x0045e920
RaceSession::Field0x2098::Resource0x64::Resource0x64()
{
	FUN_0045e9c0();
	m_flags0x1c = 0;
}

// FUNCTION: LEGORACERS 0x0045e970
RaceSession::Field0x2098::Resource0x64::~Resource0x64()
{
	FUN_0045ead0();
}

// FUNCTION: LEGORACERS 0x0045e9c0
void RaceSession::Field0x2098::Resource0x64::FUN_0045e9c0()
{
	m_unk0x20 = NULL;
	m_unk0x24 = NULL;
	m_unk0x30 = NULL;
	m_unk0x34 = NULL;
	m_unk0x28[0] = '\0';
	m_unk0x3c.m_x = 0.0f;
	m_unk0x3c.m_y = 0.0f;
	m_unk0x3c.m_z = 0.0f;
	m_unk0x48.m_x = 0.0f;
	m_unk0x48.m_y = 0.0f;
	m_unk0x48.m_z = 0.0f;
	m_unk0x48.m_x = 1.0f;
	m_unk0x54.m_x = 0.0f;
	m_unk0x54.m_y = 0.0f;
	m_unk0x54.m_z = 0.0f;
	m_unk0x54.m_z = 1.0f;
	m_unk0x60 = 0;
	m_unk0x38 = 0;
}

// FUNCTION: LEGORACERS 0x0045ea00
void RaceSession::Field0x2098::Resource0x64::FUN_0045ea00(InitParams* p_params)
{
	if (m_state0x18) {
		FUN_0045ead0();
	}

	m_unk0x14 = p_params->m_unk0x00;
	LegoS32* eventId = p_params->m_eventIds;
	for (LegoU32 i = 0; i < sizeOfArray(m_eventIds); i++) {
		m_eventIds[i] = *eventId++;
	}

	m_unk0x04 = p_params->m_eventTable;
	m_unk0x20 = p_params->m_unk0x14;
	m_unk0x24 = p_params->m_unk0x18;
	m_unk0x34 = p_params->m_unk0x1c;
	m_unk0x38 = p_params->m_unk0x20;
	::strncpy(m_unk0x28, p_params->m_unk0x24, sizeof(m_unk0x28));
	m_unk0x3c.m_x = p_params->m_unk0x2c.m_x;
	m_unk0x3c.m_y = p_params->m_unk0x2c.m_y;
	m_unk0x3c.m_z = p_params->m_unk0x2c.m_z;
	m_unk0x48.m_x = p_params->m_unk0x38.m_x;
	m_unk0x48.m_y = p_params->m_unk0x38.m_y;
	m_unk0x48.m_z = p_params->m_unk0x38.m_z;
	m_unk0x54.m_x = p_params->m_unk0x44.m_x;
	m_unk0x54.m_y = p_params->m_unk0x44.m_y;
	m_unk0x54.m_z = p_params->m_unk0x44.m_z;

	if (p_params->m_unk0x50) {
		m_flags0x1c |= c_flags0x1cBit1;
	}

	if (p_params->m_unk0x54) {
		m_flags0x1c |= c_flags0x1cBit2;
	}

	if (p_params->m_unk0x58) {
		m_flags0x1c |= c_flags0x1cBit3;
	}

	m_state0x18 = c_state0x18One;
	m_flags0x1c &= ~c_flags0x1cBit5;
}

// FUNCTION: LEGORACERS 0x0045ead0
void RaceSession::Field0x2098::Resource0x64::FUN_0045ead0()
{
	VTable0x0c();
	FUN_0045e9c0();
	Reset();
}

// FUNCTION: LEGORACERS 0x0045eaf0
void RaceSession::Field0x2098::Resource0x64::VTable0x04(GolVec3* p_unk0x04)
{
	if (p_unk0x04 && (m_flags0x1c & c_flags0x1cBit3)) {
		m_unk0x3c = *p_unk0x04;
	}

	if (m_unk0x20->FUN_00489d50(m_unk0x28)) {
		m_unk0x60 = 1;
		m_unk0x30 = m_unk0x20->FUN_00489d70(m_unk0x28, &m_unk0x3c, &m_unk0x48, &m_unk0x54);
	}
	else if (m_unk0x24->FUN_00489d50(m_unk0x28)) {
		m_unk0x60 = 0;
		m_unk0x30 = m_unk0x24->FUN_00489d70(m_unk0x28, &m_unk0x3c, &m_unk0x48, &m_unk0x54);
	}

	if (m_unk0x30) {
		m_flags0x1c |= c_flags0x1cBit5;
	}

	FUN_0045edd0(m_state0x18, 1);
	m_state0x18 = c_state0x18Three;
}

// FUNCTION: LEGORACERS 0x0045eb90
void RaceSession::Field0x2098::Resource0x64::VTable0x0c()
{
	if (m_unk0x30) {
		if (m_unk0x60) {
			m_unk0x20->FUN_00489f30(m_unk0x30);
		}
		else {
			m_unk0x24->FUN_00489f30(m_unk0x30);
		}

		m_unk0x30 = NULL;
	}

	FUN_0045edd0(m_state0x18, 3);
	m_state0x18 = c_state0x18One;
	m_flags0x1c &= ~c_flags0x1cBit5;
}

// FUNCTION: LEGORACERS 0x0045ebe0
void RaceSession::Field0x2098::Resource0x64::VTable0x14(LegoU32 p_elapsedMs)
{
	Resource::VTable0x14(p_elapsedMs);
	if (m_state0x18 == c_state0x18One) {
		return;
	}

	if (!(m_flags0x1c & c_flags0x1cBit5)) {
		if (m_unk0x20->FUN_00489d50(m_unk0x28)) {
			m_unk0x60 = 1;
			m_unk0x30 = m_unk0x20->FUN_00489d70(m_unk0x28, &m_unk0x3c, &m_unk0x48, &m_unk0x54);
		}
		else if (m_unk0x24->FUN_00489d50(m_unk0x28)) {
			m_unk0x60 = 0;
			m_unk0x30 = m_unk0x24->FUN_00489d70(m_unk0x28, &m_unk0x3c, &m_unk0x48, &m_unk0x54);
		}

		if (m_unk0x30) {
			m_flags0x1c |= c_flags0x1cBit5;
		}
	}

	if (m_unk0x34 && m_unk0x30) {
		m_unk0x34->VTable0x5c(0);
		GolSceneNode* node = m_unk0x34->VTable0x58(0);
		GolTransformBase* transform = node->VTable0x18(m_unk0x38);
		GolVec3 position;
		position.m_x = 0.0f;
		position.m_y = 0.0f;
		position.m_z = 0.0f;
		GolVec3 transformedPosition;

		do {
			transformedPosition = position;
			transform->VTable0x04(&transformedPosition, &position);
			transform = transform->m_unk0x04;
		} while (transform);

		LegoFloat scale = m_unk0x34->GetModel(0)->GetScale() * m_unk0x34->GetUnk0x58();
		position.m_x *= scale;
		position.m_y *= scale;
		position.m_z *= scale;

		m_unk0x34->VTable0x2c(position, &transformedPosition);
		if (m_unk0x30->m_unk0x00) {
			m_unk0x30->m_unk0x00->FUN_00489660(&transformedPosition);
		}
	}
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RaceSession::Field0x2098::Resource::VTable0x00(RaceState::Racer*)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RaceSession::Field0x2098::Resource::VTable0x04(GolVec3*)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RaceSession::Field0x2098::Resource::VTable0x08(RaceState::Racer*)
{
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void RaceSession::Field0x2098::Resource::VTable0x0c()
{
}

// FUNCTION: LEGORACERS 0x0045ed40
RaceSession::Field0x2098::Resource::Resource()
{
	m_unk0x04 = NULL;
	m_eventIds[0] = -1;
	m_eventIds[1] = -1;
	m_eventIds[2] = -1;
	m_state0x18 = 0;
	m_unk0x14 = 0;
	m_flags0x1c = 0;
}

// FUNCTION: LEGORACERS 0x0045ed90
RaceSession::Field0x2098::Resource::~Resource()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0045eda0
void RaceSession::Field0x2098::Resource::Reset()
{
	m_unk0x04 = NULL;
	m_eventIds[0] = -1;
	m_eventIds[1] = -1;
	m_eventIds[2] = -1;
	m_state0x18 = 0;
	m_unk0x14 = 0;
}

// FUNCTION: LEGORACERS 0x0045edc0
void RaceSession::Field0x2098::Resource::VTable0x14(LegoU32)
{
	if (m_state0x18 == c_state0x18Five) {
		VTable0x0c();
	}
}

// FUNCTION: LEGORACERS 0x0045edd0
void RaceSession::Field0x2098::Resource::FUN_0045edd0(LegoU32 p_unk0x04, LegoU32 p_unk0x08)
{
	LegoS32 current = -1;
	LegoS32 next = -1;

	switch (p_unk0x04) {
	case 2:
		p_unk0x04 = 0;
		break;
	case 3:
		p_unk0x04 = 1;
		break;
	case 4:
		p_unk0x04 = 2;
		break;
	default:
		p_unk0x04 = 3;
		break;
	}

	if (p_unk0x04 != 3) {
		current = m_eventIds[p_unk0x04];
	}

	if (p_unk0x08 != 3) {
		next = m_eventIds[p_unk0x08];
	}

	if (current != -1) {
		if (next != -1) {
			m_unk0x04->FUN_00462580(next, current, NULL);
		}
		else {
			m_unk0x04->FUN_00462140(current, NULL);
		}
	}
	else if (next != -1) {
		m_unk0x04->FUN_00461ef0(next, NULL);
	}
}

// FUNCTION: LEGORACERS 0x0045eee0 FOLDED
void RaceSession::Field0x2098::Resource::FUN_0045eee0(RaceState::Racer* p_racer)
{
	LegoU8 flags = m_flags0x1c;
	if (flags & c_flags0x1cBit2) {
		LegoU32 state = m_state0x18;
		if (state == c_state0x18One || state == c_state0x18Four) {
			VTable0x00(p_racer);
			if (m_flags0x1c & c_flags0x1cBit1) {
				return;
			}

			VTable0x08(p_racer);
			return;
		}
	}

	if (m_state0x18 != c_state0x18One && !(flags & c_flags0x1cBit1)) {
		VTable0x08(p_racer);
	}
}

// FUNCTION: LEGORACERS 0x0045ef40
RaceSession::Field0x2098::Field0x2098()
{
	m_unk0x5c = NULL;
	m_unk0x60 = NULL;
	m_unk0x64 = NULL;
	m_unk0x68 = NULL;
	m_unk0x6c = NULL;
	m_unk0x70 = NULL;
	m_unk0x74 = NULL;
	m_unk0x78 = NULL;
	m_unk0x7c = NULL;
	m_unk0x80 = NULL;
	m_unk0x84 = NULL;
	m_unk0x88 = NULL;
	m_unk0x8c = NULL;
	m_unk0x00 = 0;
	m_unk0x04 = 0;
	m_unk0x08 = 0;
	m_unk0x0c = 0;
	m_unk0x10 = 0;
	m_unk0x14 = 0;
	m_unk0x20 = 0;
	m_unk0x24 = 0;
}

// FUNCTION: LEGORACERS 0x0045ef90
RaceSession::Field0x2098::~Field0x2098()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0045efa0
void RaceSession::Field0x2098::FUN_0045efa0(Params* p_params)
{
	if (m_unk0x00) {
		Destroy();
	}

	m_unk0x00 = p_params->m_unk0x00;
	m_unk0x04 = p_params->m_unk0x04;
	m_unk0x08 = p_params->m_unk0x08;
	m_unk0x0c = p_params->m_unk0x0c;
	m_unk0x10 = p_params->m_unk0x10;
	m_unk0x14 = p_params->m_unk0x14;
	m_unk0x18 = p_params->m_unk0x18;
	m_unk0x1c = p_params->m_unk0x1c;
	m_unk0x20 = p_params->m_unk0x20;
	m_unk0x24 = p_params->m_unk0x24;

	GolFileParser* parser;
	if (p_params->m_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		parser->SetSuffix(".evb");
	}
	else {
		parser = new EvbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_params->m_name);
	for (GolFileParser::ParserTokenType token = parser->GetNextToken(); token; token = parser->GetNextToken()) {
		switch (token) {
		case GolFileParser::e_unknown0x2a:
			FUN_0045f220(parser, p_params->m_mirror);
			break;
		case GolFileParser::e_unknown0x28:
			FUN_0045f660(parser);
			break;
		case GolFileParser::e_unknown0x29:
			FUN_0045fa30(parser);
			break;
		case GolFileParser::e_unknown0x3d:
			FUN_0045feb0(parser, p_params->m_mirror);
			break;
		case GolFileParser::e_unknown0x39:
			FUN_00460320(parser);
			break;
		case GolFileParser::e_unknown0x42:
			FUN_00460430(parser);
			break;
		case GolFileParser::e_unknown0x4b:
			FUN_00460ad0(parser);
			break;
		case GolFileParser::e_unknown0x52:
			FUN_00460d10(parser);
			break;
		case GolFileParser::e_unknown0x4d:
			FUN_00460720(parser);
			break;
		case GolFileParser::e_unknown0x51:
			FUN_00461990(parser);
			break;
		case GolFileParser::e_unknown0x53:
			FUN_00461070(parser);
			break;
		case GolFileParser::e_unknown0x55:
			FUN_00461430(parser, p_params->m_mirror);
			break;
		case GolFileParser::e_unknown0x59:
			FUN_00461670(parser, p_params->m_mirror);
			break;
		default:
			parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}
	}

	parser->Dispose();
	delete parser;
}

// FUNCTION: LEGORACERS 0x0045f220
void RaceSession::Field0x2098::FUN_0045f220(GolFileParser* p_parser, LegoBool32 p_mirror)
{
	Field0x2098* field = this;

	if (p_parser->GetNextToken() != GolFileParser::e_leftBracket) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_leftBracket);
	}

	field->m_unk0x28 = p_parser->ReadInteger();
	if (p_parser->GetNextToken() != GolFileParser::e_rightBracket) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_rightBracket);
	}

	if (p_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	field->m_unk0x5c = new Resource0x5c[field->m_unk0x28];
	if (field->m_unk0x5c == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < field->m_unk0x28; i++) {
		if (p_parser->GetNextToken() != GolFileParser::e_unknown0x27) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
		}

		Resource0x5c::InitParams params;
		params.m_unk0x00 = p_parser->ReadInteger();

		GolFileParser::ParserTokenType token = p_parser->GetNextToken();
		params.m_unk0x3c = FALSE;
		if (token == GolFileParser::e_unknown0x3c) {
			params.m_unk0x3c = TRUE;
			if (p_parser->GetNextToken() != GolFileParser::e_leftCurly) {
				p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
			}
		}
		else if (token != GolFileParser::e_leftCurly) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		params.m_unk0x2c = 300.0f;
		params.m_unk0x28 = 30.0f;
		params.m_unk0x18 = 0;
		params.m_unk0x34 = FALSE;
		params.m_unk0x38 = FALSE;
		params.m_unk0x40 = FALSE;
		params.m_unk0x1c = 0;
		params.m_unk0x20 = 1.0f;
		params.m_unk0x24 = 1.0f;
		params.m_unk0x08 = field->m_unk0x10;
		params.m_unk0x30 = 1.0f;
		params.m_unk0x44 = NULL;
		params.m_unk0x48 = 0;

		for (token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly; token = p_parser->GetNextToken()) {
			switch (token) {
			case GolFileParser::e_unknown0x3b:
				params.m_unk0x0c.m_x = p_parser->ReadFloat();
				params.m_unk0x0c.m_y = p_parser->ReadFloat();
				params.m_unk0x0c.m_z = p_parser->ReadFloat();
				if (p_mirror) {
					params.m_unk0x0c.m_y = -params.m_unk0x0c.m_y;
				}
				break;
			case GolFileParser::e_unknown0x2c:
				params.m_unk0x18 = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x2e:
				params.m_unk0x1c = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x2f:
				params.m_unk0x20 = p_parser->ReadFloat();
				break;
			case GolFileParser::e_unknown0x30:
				params.m_unk0x24 = p_parser->ReadFloat();
				break;
			case GolFileParser::e_unknown0x31:
				params.m_unk0x28 = p_parser->ReadFloat();
				break;
			case GolFileParser::e_unknown0x32:
				params.m_unk0x2c = p_parser->ReadFloat();
				break;
			case GolFileParser::e_unknown0x2d:
				params.m_unk0x34 = TRUE;
				break;
			case GolFileParser::e_unknown0x3a:
				params.m_unk0x38 = TRUE;
				break;
			case GolFileParser::e_unknown0x3f:
				params.m_unk0x40 = TRUE;
				break;
			case GolFileParser::e_unknown0x40:
				params.m_unk0x30 = p_parser->ReadFloat();
				break;
			case GolFileParser::e_unknown0x33: {
				GolName name;
				::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));
				params.m_unk0x44 = field->m_unk0x00->FindUnk0xc0(name);
				if (params.m_unk0x44 == NULL) {
					params.m_unk0x44 = field->m_unk0x04->FindUnk0xc0(name);
				}
				break;
			}
			case GolFileParser::e_unknown0x54:
				params.m_unk0x48 = p_parser->ReadInteger();
				break;
			default:
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}

		field->m_unk0x5c[i].FUN_004641b0(&params);
	}

	if (p_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_rightCurly);
	}
}

// FUNCTION: LEGORACERS 0x0045f660
void RaceSession::Field0x2098::FUN_0045f660(GolFileParser* p_parser)
{
	Field0x2098* field = this;

	if (p_parser->GetNextToken() != GolFileParser::e_leftBracket) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_leftBracket);
	}

	field->m_unk0x2c = p_parser->ReadInteger();
	if (p_parser->GetNextToken() != GolFileParser::e_rightBracket) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_rightBracket);
	}

	if (p_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	field->m_unk0x60 = new AnimatedPartResource0x34[field->m_unk0x2c];
	if (field->m_unk0x60 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < field->m_unk0x2c; i++) {
		if (p_parser->GetNextToken() != GolFileParser::e_unknown0x27) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
		}

		AnimatedPartResource0x34::InitParams params;
		params.m_unk0x00 = p_parser->ReadInteger();
		GolFileParser::ParserTokenType token = p_parser->GetNextToken();
		LegoS32 eventIndex = 1;
		params.m_unk0x30 = 0;
		if (token == GolFileParser::e_unknown0x3c) {
			eventIndex = 1;
			params.m_unk0x30 = 1;
			if (p_parser->GetNextToken() != GolFileParser::e_leftCurly) {
				p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
			}
		}
		else if (token != GolFileParser::e_leftCurly) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		params.m_eventTable = (RaceEventTable0x90*) field;
		params.m_eventIds[0] = -1;
		params.m_unk0x14 = NULL;
		params.m_eventIds[1] = -1;
		params.m_unk0x18 = 0;
		params.m_eventIds[2] = -1;
		params.m_unk0x1c = 0;
		params.m_unk0x20 = -1;
		params.m_unk0x24 = -1;
		params.m_unk0x2c = FALSE;
		params.m_unk0x28 = FALSE;
		params.m_unk0x34 = FALSE;
		params.m_unk0x38 = FALSE;

		for (token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly; token = p_parser->GetNextToken()) {
			switch (token) {
			case GolFileParser::e_unknown0x33: {
				const LegoChar* name = p_parser->ReadStringWithMaxLength(sizeof(GolName));
				LegoChar destination[sizeof(GolName)];
				::strncpy(destination, name, sizeof(destination));

				if (params.m_unk0x38) {
					GolWorldDatabase* worldDatabase = field->m_unk0x04;
					if (worldDatabase->GetUnk0xc0NameEntries()) {
						params.m_unk0x14 = worldDatabase->GetUnk0xc0Name(destination);
					}
					else {
						params.m_unk0x14 = NULL;
					}
				}
				else {
					GolWorldDatabase* worldDatabase = field->m_unk0x00;
					if (worldDatabase->GetUnk0xc0NameEntries()) {
						params.m_unk0x14 = worldDatabase->GetUnk0xc0Name(destination);
					}
					else {
						params.m_unk0x14 = NULL;
					}
				}
				break;
			}
			case GolFileParser::e_unknown0x41:
				params.m_unk0x38 = TRUE;
				break;
			case GolFileParser::e_unknown0x34:
				params.m_unk0x18 = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x35:
				params.m_unk0x1c = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x36:
				params.m_unk0x20 = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x37:
				params.m_unk0x24 = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x2d:
				params.m_unk0x28 = TRUE;
				break;
			case GolFileParser::e_unknown0x3a:
				params.m_unk0x2c = TRUE;
				break;
			case GolFileParser::e_unknown0x3f:
				params.m_unk0x34 = TRUE;
				break;
			case GolFileParser::e_unknown0x27: {
				LegoS32 eventToken = p_parser->GetNextToken() - GolFileParser::e_unknown0x34;
				if (eventToken) {
					eventToken -= 2;
					if (eventToken) {
						eventToken--;
						if (eventToken) {
							eventIndex = 3;
							p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
						}
						else {
							eventIndex = 2;
						}
					}
					else {
						eventIndex = 0;
					}
				}
				params.m_eventIds[eventIndex] = p_parser->ReadInteger();
				eventIndex = 1;
				break;
			}
			default:
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}

		field->m_unk0x60[i].FUN_00463330(&params);
	}

	if (p_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_rightCurly);
	}
}

// FUNCTION: LEGORACERS 0x0045fa30
void RaceSession::Field0x2098::FUN_0045fa30(GolFileParser* p_parser)
{
	Field0x2098* field = this;

	if (p_parser->GetNextToken() != GolFileParser::e_leftBracket) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_leftBracket);
	}

	field->m_unk0x30 = p_parser->ReadInteger();
	if (p_parser->GetNextToken() != GolFileParser::e_rightBracket) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_rightBracket);
	}

	if (p_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	field->m_unk0x64 = new Resource0x34[field->m_unk0x30];
	if (field->m_unk0x64 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < field->m_unk0x30; i++) {
		if (p_parser->GetNextToken() != GolFileParser::e_unknown0x27) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
		}

		Resource0x34::InitParams params;
		params.m_unk0x00 = p_parser->ReadInteger();
		GolFileParser::ParserTokenType token = p_parser->GetNextToken();
		params.m_unk0x30 = FALSE;
		if (token == GolFileParser::e_unknown0x3c) {
			params.m_unk0x30 = TRUE;
			if (p_parser->GetNextToken() != GolFileParser::e_leftCurly) {
				p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
			}
		}
		else if (token != GolFileParser::e_leftCurly) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		params.m_eventIds[0] = -1;
		params.m_eventIds[1] = -1;
		params.m_eventIds[2] = -1;
		params.m_eventTable = (RaceEventTable0x90*) field;
		params.m_unk0x14 = NULL;
		params.m_unk0x18 = NULL;
		params.m_unk0x1c = 0;
		params.m_unk0x20 = 0;
		params.m_unk0x24 = 0;
		params.m_unk0x28 = FALSE;
		params.m_unk0x2c = FALSE;
		params.m_unk0x34 = FALSE;

		for (token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly; token = p_parser->GetNextToken()) {
			switch (token) {
			case GolFileParser::e_unknown0x38:
				params.m_unk0x14 = field->m_unk0x0c->VTable0x4c(p_parser->ReadInteger());
				break;
			case GolFileParser::e_unknown0x34:
				params.m_unk0x20 = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x35:
				params.m_unk0x24 = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x2d:
				params.m_unk0x28 = TRUE;
				break;
			case GolFileParser::e_unknown0x3a:
				params.m_unk0x2c = TRUE;
				break;
			case GolFileParser::e_unknown0x3f:
				params.m_unk0x34 = TRUE;
				break;
			case GolFileParser::e_unknown0x27: {
				LegoS32 eventIndex = p_parser->GetNextToken() - GolFileParser::e_unknown0x34;
				if (eventIndex) {
					eventIndex -= 2;
					if (eventIndex) {
						if (--eventIndex) {
							eventIndex = 3;
							p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
						}
						else {
							eventIndex = 2;
						}
					}
					else {
						eventIndex = 0;
					}
				}
				else {
					eventIndex = 1;
				}
				params.m_eventIds[eventIndex] = p_parser->ReadInteger();
				break;
			}
			case GolFileParser::e_unknown0x33: {
				const LegoChar* name = p_parser->ReadStringWithMaxLength(sizeof(GolName));
				LegoChar destination[sizeof(GolName)];
				::strncpy(destination, name, sizeof(destination));

				GolModelEntity* entity = field->m_unk0x00->FindUnk0xb4(destination);
				if (!entity) {
					entity = field->m_unk0x00->FindUnk0xc0(destination);
					if (!entity) {
						entity = field->m_unk0x00->FindUnk0xcc(destination);
						if (!entity) {
							entity = field->m_unk0x04->FindUnk0xb4(destination);
							if (!entity) {
								entity = field->m_unk0x04->FindUnk0xc0(destination);
								if (!entity) {
									if (field->m_unk0x04->GetUnk0xccNameEntries() == NULL) {
										entity = NULL;
									}
									else {
										entity = field->m_unk0x04->GetUnk0xccName(destination);
									}
								}
							}
						}
					}
				}

				MaterialTable0x0c* materialTable;
				if (entity->GetMaterialTable(0)) {
					materialTable = entity->GetMaterialTable(0);
				}
				else {
					materialTable = entity->GetModel(0)->GetMaterialTable();
				}
				params.m_unk0x18 = materialTable;
				params.m_unk0x1c = p_parser->ReadInteger();
				break;
			}
			default:
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}

		field->m_unk0x64[i].FUN_00463120(&params);
	}

	if (p_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_rightCurly);
	}
}

// FUNCTION: LEGORACERS 0x0045feb0
void RaceSession::Field0x2098::FUN_0045feb0(GolFileParser* p_parser, LegoBool32 p_mirror)
{
	Field0x2098* field = this;

	field->m_unk0x34 = p_parser->ReadBracketedCountAndLeftCurly();
	field->m_unk0x68 = new Resource0x64[field->m_unk0x34];
	if (field->m_unk0x68 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < field->m_unk0x34; i++) {
		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);

		Resource0x64::InitParams params;
		params.m_unk0x00 = p_parser->ReadInteger();

		GolFileParser::ParserTokenType token = p_parser->GetNextToken();
		LegoS32 eventIndex;
		params.m_unk0x54 = FALSE;
		if (token == GolFileParser::e_unknown0x3c) {
			eventIndex = 1;
			params.m_unk0x54 = eventIndex;
			p_parser->ReadLeftCurly();
		}
		else {
			if (token != GolFileParser::e_leftCurly) {
				p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
			}
			eventIndex = 1;
		}

		params.m_unk0x14 = field->m_unk0x18;
		params.m_unk0x18 = field->m_unk0x1c;
		params.m_eventIds[0] = -1;
		params.m_eventIds[1] = -1;
		params.m_eventTable = (RaceEventTable0x90*) field;
		params.m_eventIds[2] = -1;
		params.m_unk0x24[0] = '\0';
		params.m_unk0x50 = FALSE;
		params.m_unk0x58 = FALSE;
		params.m_unk0x2c.m_x = 0.0f;
		params.m_unk0x2c.m_y = 0.0f;
		params.m_unk0x2c.m_z = 0.0f;
		params.m_unk0x38.m_x = 1.0f;
		params.m_unk0x38.m_y = 0.0f;
		params.m_unk0x38.m_z = 0.0f;
		params.m_unk0x44.m_x = 0.0f;
		params.m_unk0x44.m_y = 0.0f;
		params.m_unk0x44.m_z = 1.0f;
		params.m_unk0x1c = NULL;
		params.m_unk0x20 = 0;
		LegoBool32 token0x3f = FALSE;

		for (token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly; token = p_parser->GetNextToken()) {
			switch (token) {
			case GolFileParser::e_unknown0x3d:
				::strncpy(
					params.m_unk0x24,
					p_parser->ReadStringWithMaxLength(sizeof(params.m_unk0x24)),
					sizeof(params.m_unk0x24)
				);
				break;
			case GolFileParser::e_unknown0x3a:
				params.m_unk0x50 = eventIndex;
				break;
			case GolFileParser::e_unknown0x3b:
				params.m_unk0x2c.m_x = p_parser->ReadFloat();
				params.m_unk0x2c.m_y = p_parser->ReadFloat();
				params.m_unk0x2c.m_z = p_parser->ReadFloat();
				if (p_mirror) {
					params.m_unk0x2c.m_y = -params.m_unk0x2c.m_y;
				}
				break;
			case GolFileParser::e_unknown0x3e:
				params.m_unk0x38.m_x = p_parser->ReadFloat();
				params.m_unk0x38.m_y = p_parser->ReadFloat();
				params.m_unk0x38.m_z = p_parser->ReadFloat();
				params.m_unk0x44.m_x = p_parser->ReadFloat();
				params.m_unk0x44.m_y = p_parser->ReadFloat();
				params.m_unk0x44.m_z = p_parser->ReadFloat();
				if (p_mirror) {
					params.m_unk0x38.m_y = -params.m_unk0x38.m_y;
					params.m_unk0x44.m_y = -params.m_unk0x44.m_y;
				}
				break;
			case GolFileParser::e_unknown0x3f:
				params.m_unk0x58 = eventIndex;
				break;
			case GolFileParser::e_unknown0x41:
				token0x3f = eventIndex;
				break;
			case GolFileParser::e_unknown0x33: {
				const LegoChar* name = p_parser->ReadStringWithMaxLength(sizeof(GolName));
				LegoChar destination[sizeof(GolName)];
				::strncpy(destination, name, sizeof(destination));

				if (token0x3f) {
					GolWorldDatabase* worldDatabase = field->m_unk0x04;
					if (worldDatabase->GetUnk0xc0NameEntries() == NULL) {
						GolModelEntity* entity = NULL;
						params.m_unk0x1c = entity;
					}
					else {
						params.m_unk0x1c = worldDatabase->GetUnk0xc0Name(destination);
					}
				}
				else {
					GolWorldDatabase* worldDatabase = field->m_unk0x00;
					if (worldDatabase->GetUnk0xc0NameEntries() == NULL) {
						GolModelEntity* entity = NULL;
						params.m_unk0x1c = entity;
					}
					else {
						params.m_unk0x1c = worldDatabase->GetUnk0xc0Name(destination);
					}
				}
				break;
			}
			case GolFileParser::e_unknown0x54:
				params.m_unk0x20 = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x27: {
				LegoS32 eventToken = p_parser->GetNextToken() - GolFileParser::e_unknown0x34;
				if (eventToken) {
					eventToken -= 2;
					if (eventToken) {
						if (--eventToken) {
							eventIndex = 3;
							p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
						}
						else {
							eventIndex = 2;
						}
					}
					else {
						eventIndex = 0;
					}
				}
				params.m_eventIds[eventIndex] = p_parser->ReadInteger();
				eventIndex = 1;
				break;
			}
			default:
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}

		field->m_unk0x68[i].FUN_0045ea00(&params);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00460320
void RaceSession::Field0x2098::FUN_00460320(GolFileParser* p_parser)
{
	if (p_parser->GetNextToken() != GolFileParser::e_leftBracket) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_leftBracket);
	}

	m_unk0x38 = p_parser->ReadInteger();
	if (p_parser->GetNextToken() != GolFileParser::e_rightBracket) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_rightBracket);
	}

	if (p_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	m_unk0x6c = new Field0x6c[m_unk0x38];
	if (m_unk0x6c == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_unk0x38; i++) {
		if (p_parser->GetNextToken() != GolFileParser::e_unknown0x27) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
		}

		m_unk0x6c[i].m_unk0x00 = p_parser->ReadInteger();
		if (p_parser->GetNextToken() != GolFileParser::e_leftCurly) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		if (p_parser->GetNextToken() != GolFileParser::e_unknown0x39) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
		}

		m_unk0x6c[i].m_unk0x04 = p_parser->ReadInteger();
		if (p_parser->GetNextToken() != GolFileParser::e_rightCurly) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_rightCurly);
		}
	}

	if (p_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_rightCurly);
	}
}

// FUNCTION: LEGORACERS 0x00460430
void RaceSession::Field0x2098::FUN_00460430(GolFileParser* p_parser)
{
	Field0x2098* field = this;

	field->m_unk0x3c = p_parser->ReadBracketedCountAndLeftCurly();
	field->m_unk0x70 = new SkyStateResource0x34[field->m_unk0x3c];
	if (field->m_unk0x70 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < field->m_unk0x3c; i++) {
		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);

		SkyStateResource0x34::InitParams params;
		params.m_unk0x00 = p_parser->ReadInteger();

		GolFileParser::ParserTokenType token = p_parser->GetNextToken();
		params.m_unk0x24 = FALSE;
		if (token == GolFileParser::e_unknown0x3c) {
			params.m_unk0x24 = TRUE;
			p_parser->ReadLeftCurly();
		}
		else if (token != GolFileParser::e_leftCurly) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		params.m_unk0x14 = field->m_unk0x20;
		params.m_eventIds[0] = -1;
		params.m_eventIds[1] = -1;
		params.m_eventTable = (RaceEventTable0x90*) field;
		params.m_eventIds[2] = -1;
		params.m_unk0x18[0] = '\0';
		params.m_unk0x20 = 0;
		params.m_flags0x28 = 0;

		for (token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly; token = p_parser->GetNextToken()) {
			switch (token) {
			case GolFileParser::e_unknown0x43:
				::strncpy(
					params.m_unk0x18,
					p_parser->ReadStringWithMaxLength(sizeof(params.m_unk0x18)),
					sizeof(params.m_unk0x18)
				);
				break;
			case GolFileParser::e_unknown0x44:
				params.m_unk0x20 = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x45:
				params.m_flags0x28 |= 2;
				break;
			case GolFileParser::e_unknown0x46:
				params.m_flags0x28 |= 1;
				break;
			case GolFileParser::e_unknown0x47:
				params.m_flags0x28 |= 8;
				break;
			case GolFileParser::e_unknown0x48:
				params.m_flags0x28 |= 4;
				break;
			case GolFileParser::e_unknown0x27: {
				LegoS32 eventIndex = p_parser->GetNextToken() - GolFileParser::e_unknown0x34;
				if (eventIndex) {
					eventIndex -= 2;
					if (eventIndex) {
						if (--eventIndex) {
							eventIndex = 3;
							p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
						}
						else {
							eventIndex = 2;
						}
					}
					else {
						eventIndex = 0;
					}
				}
				else {
					eventIndex = 1;
				}

				params.m_eventIds[eventIndex] = p_parser->ReadInteger();
				break;
			}
			default:
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}

		field->m_unk0x70[i].FUN_0045e200(&params);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00460720
void RaceSession::Field0x2098::FUN_00460720(GolFileParser* p_parser)
{
	Field0x2098* field = this;

	field->m_unk0x44 = p_parser->ReadBracketedCountAndLeftCurly();
	field->m_unk0x7c = new Resource0x48[field->m_unk0x44];
	if (field->m_unk0x7c == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < field->m_unk0x44; i++) {
		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);

		Resource0x48::InitParams params;
		params.m_unk0x00 = p_parser->ReadInteger();

		GolFileParser::ParserTokenType token = p_parser->GetNextToken();
		params.m_flags0x14 = 0;
		if (token == GolFileParser::e_unknown0x3c) {
			params.m_flags0x14 = 5;
			p_parser->ReadLeftCurly();
		}
		else if (token != GolFileParser::e_leftCurly) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		params.m_eventIds[0] = -1;
		params.m_eventTable = (RaceEventTable0x90*) field;
		params.m_eventIds[1] = -1;
		params.m_unk0x38 = NULL;
		params.m_eventIds[2] = -1;

		for (token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly; token = p_parser->GetNextToken()) {
			switch (token) {
			case GolFileParser::e_unknown0x33: {
				GolName name;
				::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));

				if (field->m_unk0x00->GetUnk0xb4NameEntries()) {
					params.m_unk0x38 = field->m_unk0x00->GetUnk0xb4Name(name);
				}
				else {
					params.m_unk0x38 = NULL;
				}

				if (params.m_unk0x38) {
					break;
				}

				if (field->m_unk0x00->GetUnk0xc0NameEntries()) {
					params.m_unk0x38 = field->m_unk0x00->GetUnk0xc0Name(name);
				}
				else {
					params.m_unk0x38 = NULL;
				}

				if (params.m_unk0x38) {
					break;
				}

				if (field->m_unk0x00->GetUnk0xccNameEntries()) {
					params.m_unk0x38 = field->m_unk0x00->GetUnk0xccName(name);
				}
				else {
					params.m_unk0x38 = NULL;
				}
				break;
			}
			case GolFileParser::e_unknown0x4e:
				params.m_unk0x18.m_redShift = p_parser->ReadInteger();
				params.m_unk0x18.m_grnShift = p_parser->ReadInteger();
				params.m_unk0x18.m_bluShift = p_parser->ReadInteger();
				params.m_unk0x18.m_alpShift = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x4f:
				params.m_unk0x18.m_redOffset = p_parser->ReadInteger();
				params.m_unk0x18.m_grnOffset = p_parser->ReadInteger();
				params.m_unk0x18.m_bluOffset = p_parser->ReadInteger();
				params.m_unk0x18.m_alpOffset = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x50:
				params.m_flags0x14 |= 2;
				break;
			case GolFileParser::e_unknown0x3a:
				params.m_flags0x14 |= 4;
				break;
			case GolFileParser::e_unknown0x27: {
				LegoS32 eventIndex = p_parser->GetNextToken() - GolFileParser::e_unknown0x34;
				if (eventIndex) {
					eventIndex -= 2;
					if (eventIndex) {
						if (--eventIndex) {
							eventIndex = 3;
							p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
						}
						else {
							eventIndex = 2;
						}
					}
					else {
						eventIndex = 0;
					}
				}
				else {
					eventIndex = 1;
				}

				params.m_eventIds[eventIndex] = p_parser->ReadInteger();
				break;
			}
			default:
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}

		field->m_unk0x7c[i].FUN_00465570(&params);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00460ad0
void RaceSession::Field0x2098::FUN_00460ad0(GolFileParser* p_parser)
{
	Field0x2098* field = this;

	field->m_unk0x40 = p_parser->ReadBracketedCountAndLeftCurly();
	field->m_unk0x74 = new Resource0x30[field->m_unk0x40];
	if (field->m_unk0x74 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < field->m_unk0x40; i++) {
		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);

		Resource0x30::InitParams params;
		params.m_unk0x00 = p_parser->ReadInteger();

		GolFileParser::ParserTokenType token = p_parser->GetNextToken();
		params.m_unk0x1c = FALSE;
		if (token == GolFileParser::e_unknown0x3c) {
			params.m_unk0x1c = TRUE;
			p_parser->ReadLeftCurly();
		}
		else if (token != GolFileParser::e_leftCurly) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		params.m_eventIds[0] = -1;
		params.m_eventTable = (RaceEventTable0x90*) field;
		params.m_eventIds[1] = -1;
		params.m_unk0x14 = -1;
		params.m_eventIds[2] = -1;
		params.m_unk0x18 = 0;

		for (token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly; token = p_parser->GetNextToken()) {
			switch (token) {
			case GolFileParser::e_unknown0x49:
				params.m_unk0x14 = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x4c:
				params.m_unk0x18 = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x27: {
				LegoS32 eventIndex = p_parser->GetNextToken() - GolFileParser::e_unknown0x34;
				if (eventIndex) {
					eventIndex -= 2;
					if (eventIndex) {
						if (--eventIndex) {
							eventIndex = 3;
							p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
						}
						else {
							eventIndex = 2;
						}
					}
					else {
						eventIndex = 0;
					}
				}
				else {
					eventIndex = 1;
				}

				params.m_eventIds[eventIndex] = p_parser->ReadInteger();
				break;
			}
			default:
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}

		field->m_unk0x74[i].FUN_0045e7f0(&params);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00460d10
void RaceSession::Field0x2098::FUN_00460d10(GolFileParser* p_parser)
{
	Field0x2098* field = this;

	field->m_unk0x4c = p_parser->ReadBracketedCountAndLeftCurly();
	field->m_unk0x78 = new NodeTransformResource0x2c[field->m_unk0x4c];
	if (field->m_unk0x78 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < field->m_unk0x4c; i++) {
		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);

		NodeTransformResource0x2c::InitParams params;
		params.m_unk0x00 = p_parser->ReadInteger();

		GolFileParser::ParserTokenType token = p_parser->GetNextToken();
		params.m_unk0x20 = FALSE;
		if (token == GolFileParser::e_unknown0x3c) {
			params.m_unk0x20 = TRUE;
			p_parser->ReadLeftCurly();
		}
		else if (token != GolFileParser::e_leftCurly) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		params.m_eventIds[0] = -1;
		params.m_eventIds[1] = -1;
		params.m_eventIds[2] = -1;
		params.m_eventTable = (RaceEventTable0x90*) field;
		params.m_unk0x14 = NULL;
		params.m_unk0x18 = NULL;
		params.m_unk0x1c = 0;

		GolName name;
		for (token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly; token = p_parser->GetNextToken()) {
			switch (token) {
			case GolFileParser::e_unknown0x33:
				::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));

				params.m_unk0x14 = field->m_unk0x08->FindUnk0xd8(name);
				break;
			case GolFileParser::e_unknown0x4a:
				::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));

				params.m_unk0x18 = field->m_unk0x00->FindUnk0xc0(name);
				if (params.m_unk0x18 == NULL) {
					params.m_unk0x18 = field->m_unk0x04->FindUnk0xc0(name);
				}
				break;
			case GolFileParser::e_unknown0x54:
				params.m_unk0x1c = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x27: {
				LegoS32 eventIndex;
				switch (p_parser->GetNextToken()) {
				case GolFileParser::e_unknown0x34:
					eventIndex = 1;
					break;
				case GolFileParser::e_unknown0x36:
					eventIndex = 0;
					break;
				case GolFileParser::e_unknown0x37:
					eventIndex = 2;
					break;
				default:
					p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
					eventIndex = 3;
					break;
				}

				params.m_eventIds[eventIndex] = p_parser->ReadInteger();
				break;
			}
			default:
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}

		field->m_unk0x78[i].FUN_00463900(&params);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00461070
void RaceSession::Field0x2098::FUN_00461070(GolFileParser* p_parser)
{
	Field0x2098* field = this;

	field->m_unk0x50 = p_parser->ReadBracketedCountAndLeftCurly();
	field->m_unk0x84 = new ModelDistanceResource0x34[field->m_unk0x50];
	if (field->m_unk0x84 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < field->m_unk0x50; i++) {
		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);

		ModelDistanceResource0x34::InitParams params;
		params.m_unk0x00 = p_parser->ReadInteger();

		GolFileParser::ParserTokenType token = p_parser->GetNextToken();
		params.m_unk0x1c = FALSE;
		if (token == GolFileParser::e_unknown0x3c) {
			params.m_unk0x1c = TRUE;
			p_parser->ReadLeftCurly();
		}
		else if (token != GolFileParser::e_leftCurly) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		params.m_eventIds[0] = -1;
		params.m_eventIds[1] = -1;
		params.m_eventIds[2] = -1;
		params.m_eventTable = (RaceEventTable0x90*) field;
		params.m_unk0x14 = NULL;
		params.m_unk0x18 = FALSE;
		params.m_unk0x20 = FALSE;
		LegoBool32 useAlternateDatabase = FALSE;
		LegoS32 eventIndex = 1;

		for (token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly; token = p_parser->GetNextToken()) {
			switch (token) {
			case GolFileParser::e_unknown0x33: {
				GolName name;
				::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));

				if (!useAlternateDatabase) {
					params.m_unk0x14 = field->m_unk0x00->FindUnk0xb4(name);
					if (params.m_unk0x14 == NULL) {
						params.m_unk0x14 = field->m_unk0x00->FindUnk0xc0(name);
					}
					if (params.m_unk0x14 == NULL) {
						params.m_unk0x14 = field->m_unk0x00->FindUnk0xcc(name);
					}
				}
				else {
					params.m_unk0x14 = field->m_unk0x04->FindUnk0xb4(name);
					if (params.m_unk0x14 == NULL) {
						params.m_unk0x14 = field->m_unk0x04->FindUnk0xc0(name);
					}
					if (params.m_unk0x14 == NULL) {
						params.m_unk0x14 = field->m_unk0x04->FindUnk0xcc(name);
					}
				}
				break;
			}
			case GolFileParser::e_unknown0x3a:
				params.m_unk0x18 = eventIndex;
				break;
			case GolFileParser::e_unknown0x41:
				useAlternateDatabase = eventIndex;
				break;
			case GolFileParser::e_unknown0x46:
				params.m_unk0x20 = eventIndex;
				break;
			case GolFileParser::e_unknown0x27: {
				LegoS32 tokenIndex = p_parser->GetNextToken() - GolFileParser::e_unknown0x34;
				if (tokenIndex) {
					tokenIndex -= 2;
					if (tokenIndex) {
						if (--tokenIndex == 0) {
							eventIndex = 2;
						}
						else {
							eventIndex = 3;
							p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
						}
					}
					else {
						eventIndex = 0;
					}
				}

				params.m_eventIds[eventIndex] = p_parser->ReadInteger();
				eventIndex = 1;
				break;
			}
			default:
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}

		field->m_unk0x84[i].FUN_00463700(&params);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00461430
void RaceSession::Field0x2098::FUN_00461430(GolFileParser* p_parser, LegoBool32 p_mirror)
{
	Field0x2098* field = this;

	field->m_unk0x54 = p_parser->ReadBracketedCountAndLeftCurly();
	field->m_unk0x88 = new Resource0x2c[field->m_unk0x54];
	if (field->m_unk0x88 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	if (field->m_unk0x54) {
		Resource0x2c* resource = field->m_unk0x88;
		for (LegoU32 i = 0; i < field->m_unk0x54; i++, resource++) {
			p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);

			Resource0x2c::InitParams params;
			params.m_unk0x00 = p_parser->ReadInteger();

			p_parser->ReadLeftCurly();
			params.m_eventIds[0] = -1;
			params.m_eventIds[1] = -1;
			params.m_eventIds[2] = -1;
			params.m_eventTable = (RaceEventTable0x90*) field;
			params.m_unk0x14.m_x = 0.0f;
			params.m_unk0x14.m_y = 0.0f;
			params.m_unk0x14.m_z = 0.0f;

			for (GolFileParser::ParserTokenType token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly;
				 token = p_parser->GetNextToken()) {
				switch (token) {
				case GolFileParser::e_unknown0x3b:
					params.m_unk0x14.m_x = p_parser->ReadFloat();
					params.m_unk0x14.m_y = p_parser->ReadFloat();
					params.m_unk0x14.m_z = p_parser->ReadFloat();
					if (p_mirror) {
						params.m_unk0x14.m_y = -params.m_unk0x14.m_y;
					}
					break;
				case GolFileParser::e_unknown0x27: {
					LegoS32 eventIndex = p_parser->GetNextToken() - GolFileParser::e_unknown0x34;
					if (eventIndex) {
						eventIndex -= 2;
						if (eventIndex) {
							if (--eventIndex) {
								eventIndex = 3;
								p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
							}
							else {
								eventIndex = 2;
							}
						}
						else {
							eventIndex = 0;
						}
					}
					else {
						eventIndex = 1;
					}

					params.m_eventIds[eventIndex] = p_parser->ReadInteger();
					break;
				}
				default:
					p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
					break;
				}
			}

			resource->FUN_0045e650(&params);
		}
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00461670
void RaceSession::Field0x2098::FUN_00461670(GolFileParser* p_parser, LegoBool32 p_mirror)
{
	Field0x2098* field = this;

	field->m_unk0x58 = p_parser->ReadBracketedCountAndLeftCurly();
	field->m_unk0x8c = new Resource0x38[field->m_unk0x58];
	if (field->m_unk0x8c == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < field->m_unk0x58; i++) {
		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);

		Resource0x38::InitParams params;
		params.m_unk0x00 = p_parser->ReadInteger();

		GolFileParser::ParserTokenType token = p_parser->GetNextToken();
		params.m_unk0x2c = FALSE;
		if (token == GolFileParser::e_unknown0x3c) {
			params.m_unk0x2c = TRUE;
			p_parser->ReadLeftCurly();
		}
		else if (token != GolFileParser::e_leftCurly) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		params.m_eventIds[0] = -1;
		params.m_eventIds[1] = -1;
		params.m_eventIds[2] = -1;
		params.m_eventTable = (RaceEventTable0x90*) field;
		params.m_unk0x14.m_x = 0.0f;
		params.m_unk0x14.m_y = 0.0f;
		params.m_unk0x14.m_z = 0.0f;
		params.m_unk0x20 = 0;
		params.m_unk0x24 = -1;
		params.m_unk0x28 = FALSE;

		for (token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly; token = p_parser->GetNextToken()) {
			switch (token) {
			case GolFileParser::e_unknown0x3e:
				params.m_unk0x14.m_x = p_parser->ReadFloat();
				params.m_unk0x14.m_y = p_parser->ReadFloat();
				params.m_unk0x14.m_z = p_parser->ReadFloat();
				if (p_mirror) {
					params.m_unk0x14.m_y = -params.m_unk0x14.m_y;
				}
				break;
			case GolFileParser::e_unknown0x4c:
				params.m_unk0x20 = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x5a:
				params.m_unk0x24 = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x27: {
				LegoS32 eventIndex = p_parser->GetNextToken() - GolFileParser::e_unknown0x34;
				if (eventIndex) {
					eventIndex -= 2;
					if (eventIndex) {
						if (--eventIndex) {
							eventIndex = 3;
							p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
						}
						else {
							eventIndex = 2;
						}
					}
					else {
						eventIndex = 0;
					}
				}
				else {
					eventIndex = 1;
				}

				params.m_eventIds[eventIndex] = p_parser->ReadInteger();
				break;
			}
			default:
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}

		field->m_unk0x8c[i].FUN_00462f40(&params);
	}

	p_parser->ReadRightCurly();
}

// STUB: LEGORACERS 0x00461990
void RaceSession::Field0x2098::FUN_00461990(GolFileParser* p_parser)
{
	Field0x2098* field = this;

	field->m_unk0x48 = p_parser->ReadBracketedCountAndLeftCurly();
	field->m_unk0x80 = new Resource0x24[field->m_unk0x48];
	if (field->m_unk0x80 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < field->m_unk0x48; i++) {
		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);

		Resource0x24::InitParams params;
		params.m_unk0x00 = p_parser->ReadInteger();

		p_parser->ReadLeftCurly();
		params.m_eventIds[0] = -1;
		params.m_eventIds[1] = -1;
		params.m_eventTable = (RaceEventTable0x90*) field;
		params.m_eventIds[2] = -1;
		params.m_unk0x14 = 1;

		for (GolFileParser::ParserTokenType token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly;
			 token = p_parser->GetNextToken()) {
			switch (token) {
			case GolFileParser::e_unknown0x36:
				params.m_unk0x14 = 0;
				break;
			case GolFileParser::e_unknown0x37:
				params.m_unk0x14 = 2;
				break;
			case GolFileParser::e_unknown0x27: {
				LegoS32 eventIndex = p_parser->GetNextToken() - GolFileParser::e_unknown0x34;
				if (eventIndex) {
					eventIndex -= 2;
					if (eventIndex) {
						if (--eventIndex) {
							eventIndex = 3;
							p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
						}
						else {
							eventIndex = 2;
						}
					}
					else {
						eventIndex = 0;
					}
				}
				else {
					eventIndex = 1;
				}

				params.m_eventIds[eventIndex] = p_parser->ReadInteger();
				break;
			}
			default:
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}

		field->m_unk0x80[i].FUN_00464610(&params);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00461ba0
void RaceSession::Field0x2098::Destroy()
{
	if (m_unk0x5c) {
		delete[] m_unk0x5c;
		m_unk0x5c = NULL;
	}

	if (m_unk0x60) {
		delete[] m_unk0x60;
		m_unk0x60 = NULL;
	}

	if (m_unk0x64) {
		delete[] m_unk0x64;
		m_unk0x64 = NULL;
	}

	if (m_unk0x68) {
		delete[] m_unk0x68;
		m_unk0x68 = NULL;
	}

	if (m_unk0x6c) {
		delete[] m_unk0x6c;
		m_unk0x6c = NULL;
	}

	if (m_unk0x70) {
		delete[] m_unk0x70;
		m_unk0x70 = NULL;
	}

	if (m_unk0x74) {
		delete[] m_unk0x74;
		m_unk0x74 = NULL;
	}

	if (m_unk0x78) {
		delete[] m_unk0x78;
		m_unk0x78 = NULL;
	}

	if (m_unk0x7c) {
		delete[] m_unk0x7c;
		m_unk0x7c = NULL;
	}

	if (m_unk0x80) {
		delete[] m_unk0x80;
		m_unk0x80 = NULL;
	}

	if (m_unk0x84) {
		delete[] m_unk0x84;
		m_unk0x84 = NULL;
	}

	if (m_unk0x88) {
		delete[] m_unk0x88;
		m_unk0x88 = NULL;
	}

	if (m_unk0x8c) {
		delete[] m_unk0x8c;
		m_unk0x8c = NULL;
	}

	m_unk0x00 = 0;
	m_unk0x04 = 0;
	m_unk0x08 = 0;
	m_unk0x0c = 0;
	m_unk0x10 = 0;
	m_unk0x14 = 0;
	m_unk0x20 = 0;
	m_unk0x24 = 0;
}

// FUNCTION: LEGORACERS 0x00461cc0
void RaceSession::Field0x2098::FUN_00461cc0(LegoU32 p_elapsedMs)
{
	LegoU32 i;

	if (m_unk0x5c) {
		for (i = 0; i < m_unk0x28; i++) {
			m_unk0x5c[i].VTable0x14(p_elapsedMs);
		}
	}

	if (m_unk0x60) {
		for (i = 0; i < m_unk0x2c; i++) {
			m_unk0x60[i].VTable0x14(p_elapsedMs);
		}
	}

	if (m_unk0x64) {
		for (i = 0; i < m_unk0x30; i++) {
			m_unk0x64[i].VTable0x14(p_elapsedMs);
		}
	}

	if (m_unk0x68) {
		for (i = 0; i < m_unk0x34; i++) {
			m_unk0x68[i].VTable0x14(p_elapsedMs);
		}
	}

	if (m_unk0x70) {
		for (i = 0; i < m_unk0x3c; i++) {
			m_unk0x70[i].VTable0x14(p_elapsedMs);
		}
	}

	if (m_unk0x74) {
		for (i = 0; i < m_unk0x40; i++) {
			m_unk0x74[i].VTable0x14(p_elapsedMs);
		}
	}

	if (m_unk0x78) {
		for (i = 0; i < m_unk0x4c; i++) {
			m_unk0x78[i].VTable0x14(p_elapsedMs);
		}
	}

	if (m_unk0x7c) {
		for (i = 0; i < m_unk0x44; i++) {
			m_unk0x7c[i].VTable0x14(p_elapsedMs);
		}
	}

	if (m_unk0x80) {
		for (i = 0; i < m_unk0x48; i++) {
			m_unk0x80[i].VTable0x14(p_elapsedMs);
		}
	}

	if (m_unk0x84) {
		for (i = 0; i < m_unk0x50; i++) {
			m_unk0x84[i].VTable0x14(p_elapsedMs);
		}
	}

	if (m_unk0x88) {
		for (i = 0; i < m_unk0x54; i++) {
			m_unk0x88[i].VTable0x14(p_elapsedMs);
		}
	}

	if (m_unk0x8c) {
		LegoU32 count = m_unk0x58;

		for (i = 0; i < count; i++) {
			m_unk0x8c[i].VTable0x14(p_elapsedMs);
			count = m_unk0x58;
		}
	}
}

// FUNCTION: LEGORACERS 0x00462c60
void RaceSession::Field0x2098::FUN_00462c60()
{
	LegoU32 i;

	if (m_unk0x5c) {
		for (i = 0; i < m_unk0x28; i++) {
			m_unk0x5c[i].SetState0x18(Resource::c_state0x18Five);
		}
	}

	if (m_unk0x60) {
		for (i = 0; i < m_unk0x2c; i++) {
			m_unk0x60[i].SetState0x18(Resource::c_state0x18Five);
		}
	}

	if (m_unk0x64) {
		for (i = 0; i < m_unk0x30; i++) {
			m_unk0x64[i].SetState0x18(Resource::c_state0x18Five);
		}
	}

	if (m_unk0x68) {
		for (i = 0; i < m_unk0x34; i++) {
			m_unk0x68[i].SetState0x18(Resource::c_state0x18Five);
		}
	}

	if (m_unk0x70) {
		for (i = 0; i < m_unk0x3c; i++) {
			m_unk0x70[i].SetState0x18(Resource::c_state0x18Five);
		}
	}

	if (m_unk0x74) {
		for (i = 0; i < m_unk0x40; i++) {
			m_unk0x74[i].SetState0x18(Resource::c_state0x18Five);
		}
	}

	if (m_unk0x78) {
		for (i = 0; i < m_unk0x4c; i++) {
			m_unk0x78[i].SetState0x18(Resource::c_state0x18Five);
		}
	}

	if (m_unk0x84) {
		for (i = 0; i < m_unk0x50; i++) {
			m_unk0x84[i].SetState0x18(Resource::c_state0x18Five);
		}
	}

	FUN_00461cc0(0);
}

// FUNCTION: LEGORACERS 0x00462da0
void RaceSession::Field0x2098::FUN_00462da0(RaceState::Racer* p_racer)
{
	LegoU32 i;

	if (m_unk0x7c) {
		for (i = 0; i < m_unk0x44; i++) {
			Resource* resource = &m_unk0x7c[i];
			resource->FUN_0045eee0(p_racer);
		}
	}

	if (m_unk0x80) {
		for (i = 0; i < m_unk0x48; i++) {
			Resource* resource = &m_unk0x80[i];
			resource->FUN_0045eee0(p_racer);
		}
	}

	if (m_unk0x88) {
		for (i = 0; i < m_unk0x54; i++) {
			Resource* resource = &m_unk0x88[i];
			resource->FUN_0045eee0(p_racer);
		}
	}

	if (m_unk0x8c) {
		LegoU32 count = m_unk0x58;

		for (i = 0; i < count; i++) {
			Resource* resource = &m_unk0x8c[i];
			resource->FUN_0045eee0(p_racer);
			count = m_unk0x58;
		}
	}
}

// FUNCTION: LEGORACERS 0x00462e70
RaceSession::Field0x2098::Resource0x38::Resource0x38()
{
	FUN_00462f10();
}

// FUNCTION: LEGORACERS 0x00462ec0
RaceSession::Field0x2098::Resource0x38::~Resource0x38()
{
	FUN_00462fc0();
}

// FUNCTION: LEGORACERS 0x00462f10
void RaceSession::Field0x2098::Resource0x38::FUN_00462f10()
{
	m_unk0x30 = -1;
	m_unk0x04 = NULL;
	m_state0x18 = 0;
	m_unk0x14 = 0;
	m_unk0x20.m_x = 0.0f;
	m_unk0x20.m_y = 0.0f;
	m_unk0x20.m_z = 0.0f;
	m_unk0x2c = 0;
	m_flags0x34 = 0;
}

// FUNCTION: LEGORACERS 0x00462f40
void RaceSession::Field0x2098::Resource0x38::FUN_00462f40(InitParams* p_params)
{
	if (m_state0x18) {
		FUN_00462fc0();
	}

	m_unk0x14 = p_params->m_unk0x00;
	LegoS32* eventId = p_params->m_eventIds;
	for (LegoU32 i = 0; i < sizeOfArray(m_eventIds); i++) {
		m_eventIds[i] = *eventId++;
	}

	m_unk0x04 = p_params->m_eventTable;
	m_unk0x20 = p_params->m_unk0x14;
	m_unk0x2c = p_params->m_unk0x20;
	m_unk0x30 = p_params->m_unk0x24;
	if (p_params->m_unk0x28) {
		m_flags0x1c |= c_flags0x1cBit1;
	}
	if (p_params->m_unk0x2c) {
		m_flags0x1c |= c_flags0x1cBit2;
	}

	m_state0x18 = c_state0x18One;
}

// FUNCTION: LEGORACERS 0x00462fc0
void RaceSession::Field0x2098::Resource0x38::FUN_00462fc0()
{
	FUN_00462f10();
	Reset();
}

// FUNCTION: LEGORACERS 0x00462fe0
void RaceSession::Field0x2098::Resource0x38::VTable0x00(RaceState::Racer* p_racer)
{
	if (m_flags0x34 & c_flags0x34Bit0) {
		if (p_racer) {
			switch (m_unk0x2c) {
			case 0:
				p_racer->m_unk0x3e8.VTable0x40(&m_unk0x20);
				break;
			case 1:
				p_racer->m_unk0x3e8.VTable0x48(&m_unk0x20);
				break;
			}
		}

		FUN_0045edd0(1, 1);
		m_state0x18 = c_state0x18Three;
	}
}

// FUNCTION: LEGORACERS 0x00463040
void RaceSession::Field0x2098::Resource0x38::VTable0x08(RaceState::Racer* p_racer)
{
	if (p_racer) {
		switch (m_unk0x2c) {
		case 0:
			p_racer->m_unk0x3e8.VTable0x44();
			break;
		case 1:
			p_racer->m_unk0x3e8.VTable0x4c();
			break;
		}
	}

	FUN_0045edd0(m_state0x18, 3);
	m_state0x18 = c_state0x18One;
}

// FUNCTION: LEGORACERS 0x00463090
LegoU32 RaceSession::Field0x2098::Resource0x38::VTable0x18()
{
	return 12;
}

// FUNCTION: LEGORACERS 0x004630a0
RaceSession::Field0x2098::Resource0x34::Resource0x34()
{
	m_unk0x20 = NULL;
	m_unk0x24 = NULL;
	m_unk0x28 = NULL;
	m_unk0x2c = NULL;
	m_unk0x30 = 0;
	m_flags0x1c = 0;
}

// FUNCTION: LEGORACERS 0x004630d0
RaceSession::Field0x2098::Resource0x34::~Resource0x34()
{
	FUN_004631e0();
}

// FUNCTION: LEGORACERS 0x00463120
void RaceSession::Field0x2098::Resource0x34::FUN_00463120(InitParams* p_params)
{
	if (m_state0x18) {
		FUN_004631e0();
	}

	m_unk0x14 = p_params->m_unk0x00;
	LegoS32* eventId = p_params->m_eventIds;
	for (LegoU32 i = 0; i < sizeOfArray(m_eventIds); i++) {
		m_eventIds[i] = *eventId++;
	}

	m_unk0x04 = p_params->m_eventTable;
	m_unk0x20 = p_params->m_unk0x14;
	if (p_params->m_unk0x28) {
		m_flags0x1c |= c_flags0x1cBit0;
	}
	if (p_params->m_unk0x2c) {
		m_flags0x1c |= c_flags0x1cBit1;
	}
	if (p_params->m_unk0x30) {
		m_flags0x1c |= c_flags0x1cBit2;
	}
	if (p_params->m_unk0x34) {
		m_flags0x1c |= c_flags0x1cBit3;
	}

	m_unk0x24 = &m_unk0x20->GetUnk0x0c()[p_params->m_unk0x20];
	MabMaterialAnimationItem0x18* item = &m_unk0x20->GetUnk0x0c()[p_params->m_unk0x24];
	m_unk0x28 = item;
	m_unk0x2c = item->GetUnk0x00();
	m_unk0x30 = item->GetUnk0x04();
	if (p_params->m_unk0x18) {
		m_unk0x2c = p_params->m_unk0x18;
		m_unk0x30 = p_params->m_unk0x1c;
	}

	m_state0x18 = c_state0x18One;
}

// FUNCTION: LEGORACERS 0x004631e0
void RaceSession::Field0x2098::Resource0x34::FUN_004631e0()
{
	VTable0x0c();
	m_unk0x20 = NULL;
	Reset();
}

// FUNCTION: LEGORACERS 0x00463200
void RaceSession::Field0x2098::Resource0x34::VTable0x14(LegoU32 p_elapsedMs)
{
	Resource::VTable0x14(p_elapsedMs);
	if (m_state0x18 == c_state0x18Three && !(m_flags0x1c & c_flags0x1cBit0) && !m_unk0x24->IsAssigned()) {
		VTable0x0c();
	}
}

// FUNCTION: LEGORACERS 0x00463230
void RaceSession::Field0x2098::Resource0x34::VTable0x04(GolVec3*)
{
	m_unk0x28->FUN_00410470();
	m_unk0x24->FUN_10025da0(m_unk0x2c, m_unk0x30, m_flags0x1c & c_flags0x1cBit0);
	m_unk0x24->FUN_00410480();
	FUN_0045edd0(m_state0x18, c_state0x18One);
	m_state0x18 = c_state0x18Three;
}

// FUNCTION: LEGORACERS 0x00463280
void RaceSession::Field0x2098::Resource0x34::VTable0x0c()
{
	m_unk0x24->FUN_00410470();
	m_unk0x28->FUN_10025da0(m_unk0x2c, m_unk0x30, TRUE);
	m_unk0x28->FUN_00410480();
	FUN_0045edd0(m_state0x18, c_state0x18Three);
	m_state0x18 = c_state0x18One;
}

// FUNCTION: LEGORACERS 0x004632c0
RaceSession::Field0x2098::AnimatedPartResource0x34::AnimatedPartResource0x34()
{
	m_unk0x20 = NULL;
	m_flags0x1c = 0;
}

// FUNCTION: LEGORACERS 0x004632e0
RaceSession::Field0x2098::AnimatedPartResource0x34::~AnimatedPartResource0x34()
{
	FUN_004633e0();
}

// FUNCTION: LEGORACERS 0x00463330
void RaceSession::Field0x2098::AnimatedPartResource0x34::FUN_00463330(InitParams* p_params)
{
	if (m_state0x18) {
		FUN_004633e0();
	}

	m_unk0x14 = p_params->m_unk0x00;
	LegoS32* eventId = p_params->m_eventIds;
	for (LegoU32 i = 0; i < sizeOfArray(m_eventIds); i++) {
		m_eventIds[i] = *eventId++;
	}

	m_unk0x04 = p_params->m_eventTable;
	m_unk0x20 = p_params->m_unk0x14;
	m_unk0x24 = p_params->m_unk0x18;
	m_unk0x28 = p_params->m_unk0x1c;
	m_unk0x2c = p_params->m_unk0x20;
	m_unk0x30 = p_params->m_unk0x24;

	if (p_params->m_unk0x28) {
		m_flags0x1c |= c_flags0x1cBit0;
	}

	if (p_params->m_unk0x2c) {
		m_flags0x1c |= c_flags0x1cBit1;
	}

	if (p_params->m_unk0x30) {
		m_flags0x1c |= c_flags0x1cBit2;
	}

	if (p_params->m_unk0x34) {
		m_flags0x1c |= c_flags0x1cBit3;
	}

	if (p_params->m_unk0x38) {
		m_flags0x1c |= c_flags0x1cBit4;
	}

	m_unk0x20->SetFlags(m_unk0x20->GetFlags() | c_entityFlag0x200000);
	m_state0x18 = c_state0x18One;
}

// FUNCTION: LEGORACERS 0x004633e0
void RaceSession::Field0x2098::AnimatedPartResource0x34::FUN_004633e0()
{
	m_unk0x20 = NULL;
	Reset();
}

// STUB: LEGORACERS 0x004633f0
void RaceSession::Field0x2098::AnimatedPartResource0x34::VTable0x14(LegoU32 p_elapsedMs)
{
	Resource::VTable0x14(p_elapsedMs);

	GolAnimatedEntity* entity = m_unk0x20;
	LegoU32 state = m_state0x18;
	LegoS32 currentPart = entity->GetCurrentPartIndex();

	if (state == 2) {
		if (currentPart == m_unk0x2c) {
			LegoU32 flags = entity->GetFlags();
			if (!(flags & c_entityFlags0x120000) || static_cast<LegoU32>(entity->GetQueuedPartIndex()) == 0xffff) {
				LegoU32 loop = m_flags0x1c & c_flags0x1cBit0;
				entity->SetQueuedPartIndex(static_cast<LegoU16>(m_unk0x24));
				flags = entity->GetFlags();
				flags &= ~c_entityFlags0x4e0000;
				flags |= GolAnimatedEntity::c_flagRestartQueuedPart;
				if (loop) {
					flags |= GolAnimatedEntity::c_flagLoopQueuedPart;
				}
				entity->SetFlags(flags);
			}
		}
	}
	else if (state == 4) {
		if (currentPart == m_unk0x30) {
			LegoU32 flags = entity->GetFlags();
			if (!(flags & c_entityFlags0x120000) || static_cast<LegoU32>(entity->GetQueuedPartIndex()) == 0xffff) {
				entity->SetQueuedPartIndex(static_cast<LegoU16>(m_unk0x28));
				flags = entity->GetFlags();
				flags &= ~c_entityFlags0x0e0000;
				flags |= GolAnimatedEntity::c_flagRestartQueuedPart | GolAnimatedEntity::c_flagLoopQueuedPart;
				entity->SetFlags(flags);
			}
		}
	}
	else if (state == 3) {
		if (!(m_flags0x1c & c_flags0x1cBit0) && currentPart == m_unk0x24) {
			LegoU32 flags = entity->GetFlags();
			if (!(flags & c_entityFlags0x120000) || static_cast<LegoU32>(entity->GetQueuedPartIndex()) == 0xffff) {
				LegoS32 queuedPart = m_unk0x30;
				if (queuedPart == -1) {
					entity->SetQueuedPartIndex(static_cast<LegoU16>(m_unk0x28));
					flags = entity->GetFlags();
					flags &= ~c_entityFlags0x0e0000;
					flags |= GolAnimatedEntity::c_flagRestartQueuedPart | GolAnimatedEntity::c_flagLoopQueuedPart;
					entity->SetFlags(flags);
				}
				else {
					entity->SetQueuedPartIndex(static_cast<LegoU16>(queuedPart));
					flags = entity->GetFlags();
					flags &= ~c_entityFlags0x4e0000;
					flags |= GolAnimatedEntity::c_flagRestartQueuedPart;
					entity->SetFlags(flags);
				}
			}
		}
	}

	if (currentPart == m_unk0x2c) {
		if (m_state0x18 != 2) {
			FUN_0045edd0(m_state0x18, 0);
			m_state0x18 = 2;
		}
	}
	else if (currentPart == m_unk0x24) {
		if (m_state0x18 != 3) {
			FUN_0045edd0(m_state0x18, 1);
			m_state0x18 = 3;
		}
	}
	else if (currentPart == m_unk0x30) {
		if (m_state0x18 != 4) {
			FUN_0045edd0(m_state0x18, 2);
			m_state0x18 = 4;
		}
	}
	else if (currentPart == m_unk0x28 && m_state0x18 != c_state0x18One) {
		FUN_0045edd0(m_state0x18, 3);
		m_state0x18 = c_state0x18One;
	}
}

// FUNCTION: LEGORACERS 0x00463570
void RaceSession::Field0x2098::AnimatedPartResource0x34::VTable0x04(GolVec3*)
{
	LegoS32 queuedPart = m_unk0x2c;
	GolAnimatedEntity* entity = m_unk0x20;
	if (queuedPart != -1) {
		entity->SetQueuedPartIndex(static_cast<LegoU16>(queuedPart));
		LegoU32 flags = entity->GetFlags();
		flags &= ~c_entityFlags0x4e0000;
		flags |= GolAnimatedEntity::c_flagRestartQueuedPart;
		entity->SetFlags(flags);
	}
	else {
		queuedPart = m_unk0x24;
		entity->SetQueuedPartIndex(static_cast<LegoU16>(queuedPart));
		LegoU32 flags = entity->GetFlags();
		flags &= ~c_entityFlags0x0e0000;
		flags |= GolAnimatedEntity::c_flagRestartQueuedPart | GolAnimatedEntity::c_flagLoopQueuedPart;
		entity->SetFlags(flags);
	}
}

// STUB: LEGORACERS 0x004635c0
void RaceSession::Field0x2098::AnimatedPartResource0x34::VTable0x0c()
{
	LegoU32 state = m_state0x18;
	LegoU32 nextState = c_state0x18One;
	if (state != nextState) {
		GolAnimatedEntity* entity = m_unk0x20;
		LegoS32 targetPart = m_unk0x28;
		LegoS32 currentPart = entity->GetCurrentPartIndex();
		if (currentPart != targetPart) {
			LegoS32 queuedPart = m_unk0x30;
			if (queuedPart != -1) {
				if (currentPart != queuedPart) {
					queuedPart = m_unk0x30;
					if (queuedPart != -1) {
						entity->SetQueuedPartIndex(static_cast<LegoU16>(queuedPart));
						LegoU32 flags = entity->GetFlags();
						flags &= ~c_entityFlags0x4e0000;
						flags |= GolAnimatedEntity::c_flagRestartQueuedPart;
						entity->SetFlags(flags);
						SetState0x18(nextState);
						return;
					}
				}
			}
			else {
				entity->SetQueuedPartIndex(static_cast<LegoU16>(targetPart));
				LegoU32 flags = entity->GetFlags();
				flags &= ~c_entityFlags0x0e0000;
				flags |= GolAnimatedEntity::c_flagRestartQueuedPart | GolAnimatedEntity::c_flagLoopQueuedPart;
				entity->SetFlags(flags);
			}
		}
	}

	SetState0x18(nextState);
}

// FUNCTION: LEGORACERS 0x00463640
RaceSession::Field0x2098::ModelDistanceResource0x34::ModelDistanceResource0x34()
{
	m_flags0x1c = 0;
	FUN_004636e0();
}

// FUNCTION: LEGORACERS 0x00463690
RaceSession::Field0x2098::ModelDistanceResource0x34::~ModelDistanceResource0x34()
{
	FUN_004637a0();
}

// FUNCTION: LEGORACERS 0x004636e0
void RaceSession::Field0x2098::ModelDistanceResource0x34::FUN_004636e0()
{
	m_modelDistances[0] = 0.0f;
	m_modelDistances[1] = 0.0f;
	m_modelDistances[2] = 0.0f;
	m_unk0x30 = FALSE;
	m_unk0x20 = NULL;
}

// FUNCTION: LEGORACERS 0x00463700
void RaceSession::Field0x2098::ModelDistanceResource0x34::FUN_00463700(InitParams* p_params)
{
	if (m_state0x18) {
		FUN_004637a0();
	}

	m_unk0x14 = p_params->m_unk0x00;
	LegoS32* eventId = p_params->m_eventIds;
	LegoU32 i;
	for (i = 0; i < sizeOfArray(m_eventIds); i++) {
		m_eventIds[i] = *eventId++;
	}

	m_unk0x04 = p_params->m_eventTable;
	m_unk0x20 = p_params->m_unk0x14;
	m_unk0x30 = p_params->m_unk0x20;
	if (p_params->m_unk0x18) {
		m_flags0x1c |= c_flags0x1cBit1;
	}
	if (p_params->m_unk0x1c) {
		m_flags0x1c |= c_flags0x1cBit2;
	}

	for (i = 0; i < sizeOfArray(m_modelDistances); i++) {
		m_modelDistances[i] = m_unk0x20->GetModelDistance(i);
		if (!m_unk0x30) {
			LegoFloat modelDistance = -1.0f;
			m_unk0x20->SetModelDistance(i, modelDistance);
		}
	}

	m_state0x18 = c_state0x18One;
}

// FUNCTION: LEGORACERS 0x004637a0
void RaceSession::Field0x2098::ModelDistanceResource0x34::FUN_004637a0()
{
	FUN_004636e0();
	Reset();
}

// FUNCTION: LEGORACERS 0x004637c0
void RaceSession::Field0x2098::ModelDistanceResource0x34::VTable0x04(GolVec3*)
{
	for (LegoU32 i = 0; i < sizeOfArray(m_modelDistances); i++) {
		LegoFloat modelDistance;
		if (m_unk0x30) {
			modelDistance = -1.0f;
		}
		else {
			modelDistance = m_modelDistances[i];
		}
		m_unk0x20->SetModelDistance(i, modelDistance);
	}

	m_state0x18 = c_state0x18Three;
}

// FUNCTION: LEGORACERS 0x00463800
void RaceSession::Field0x2098::ModelDistanceResource0x34::VTable0x0c()
{
	for (LegoU32 i = 0; i < sizeOfArray(m_modelDistances); i++) {
		LegoFloat modelDistance;
		if (m_unk0x30) {
			modelDistance = m_modelDistances[i];
		}
		else {
			modelDistance = -1.0f;
		}
		m_unk0x20->SetModelDistance(i, modelDistance);
	}

	m_state0x18 = c_state0x18One;
}

// FUNCTION: LEGORACERS 0x00463840
LegoU32 RaceSession::Field0x2098::ModelDistanceResource0x34::VTable0x18()
{
	return 10;
}

// FUNCTION: LEGORACERS 0x00463850
RaceSession::Field0x2098::NodeTransformResource0x2c::NodeTransformResource0x2c()
{
	FUN_004638f0();
	m_flags0x1c = 0;
}

// FUNCTION: LEGORACERS 0x004638a0
RaceSession::Field0x2098::NodeTransformResource0x2c::~NodeTransformResource0x2c()
{
	FUN_00463970();
}

// FUNCTION: LEGORACERS 0x004638f0
void RaceSession::Field0x2098::NodeTransformResource0x2c::FUN_004638f0()
{
	m_unk0x20 = NULL;
	m_unk0x24 = NULL;
	m_unk0x28 = 0;
}

// FUNCTION: LEGORACERS 0x00463900
void RaceSession::Field0x2098::NodeTransformResource0x2c::FUN_00463900(InitParams* p_params)
{
	if (m_state0x18) {
		FUN_00463970();
	}

	m_unk0x14 = p_params->m_unk0x00;
	LegoS32* eventId = p_params->m_eventIds;
	for (LegoU32 i = 0; i < sizeOfArray(m_eventIds); i++) {
		m_eventIds[i] = *eventId++;
	}

	m_unk0x04 = p_params->m_eventTable;
	m_unk0x20 = p_params->m_unk0x14;
	m_unk0x24 = p_params->m_unk0x18;
	m_unk0x28 = p_params->m_unk0x1c;
	if (p_params->m_unk0x20) {
		m_flags0x1c |= c_flags0x1cBit2;
	}

	m_state0x18 = c_state0x18One;
}

// FUNCTION: LEGORACERS 0x00463970
void RaceSession::Field0x2098::NodeTransformResource0x2c::FUN_00463970()
{
	VTable0x0c();
	FUN_004638f0();
	Reset();
}

// FUNCTION: LEGORACERS 0x00463990
void RaceSession::Field0x2098::NodeTransformResource0x2c::VTable0x04(GolVec3*)
{
	FUN_0045edd0(1, 1);
	m_state0x18 = c_state0x18Three;
}

// FUNCTION: LEGORACERS 0x004639b0
void RaceSession::Field0x2098::NodeTransformResource0x2c::VTable0x0c()
{
	FUN_0045edd0(m_state0x18, 3);
	m_state0x18 = c_state0x18One;
}

// FUNCTION: LEGORACERS 0x004639d0
void RaceSession::Field0x2098::NodeTransformResource0x2c::VTable0x14(LegoU32 p_elapsedMs)
{
	if (m_state0x18 != c_state0x18One) {
		Resource::VTable0x14(p_elapsedMs);

		if (m_unk0x20) {
			m_unk0x24->VTable0x5c(0);
			GolSceneNode* node = m_unk0x24->VTable0x58(0);
			GolTransformBase* transform = node->VTable0x18(m_unk0x28);

			GolVec3 position;
			GolVec3 up;
			GolVec3 right;
			transform->GetPosition(&position);
			transform->GetUp(&up);
			transform->GetRight(&right);

			LegoFloat scale = m_unk0x24->GetModel(0)->GetScale() * m_unk0x24->GetUnk0x58();
			position.m_x *= scale;
			position.m_y *= scale;
			position.m_z *= scale;

			GolVec3 transformedPosition;
			GolVec3 transformedUp;
			GolVec3 transformedRight;
			m_unk0x24->VTable0x2c(position, &transformedPosition);
			m_unk0x24->VTable0x34(up, &transformedUp);
			m_unk0x24->VTable0x34(right, &transformedRight);
			m_unk0x20->VTable0x08(transformedPosition);
			m_unk0x20->VTable0x40(transformedUp, transformedRight);
		}
	}
}

// FUNCTION: LEGORACERS 0x00463ad0
LegoU32 RaceSession::Field0x2098::NodeTransformResource0x2c::VTable0x18()
{
	return 9;
}

// FUNCTION: LEGORACERS 0x00464130
RaceSession::Field0x2098::Resource0x5c::Resource0x5c()
{
	m_unk0x20 = NULL;
	m_unk0x24 = NULL;
	m_flags0x1c = 0;
	m_unk0x28 = NULL;
	m_unk0x2c = 0;
	m_unk0x54 = 0xff;
}

// FUNCTION: LEGORACERS 0x00464160
RaceSession::Field0x2098::Resource0x5c::~Resource0x5c()
{
	FUN_00464290();
}

// FUNCTION: LEGORACERS 0x004641b0
void RaceSession::Field0x2098::Resource0x5c::FUN_004641b0(InitParams* p_params)
{
	if (m_state0x18) {
		FUN_00464290();
	}

	m_unk0x14 = p_params->m_unk0x00;
	m_unk0x24 = p_params->m_unk0x08;
	m_unk0x3c = p_params->m_unk0x18;
	m_unk0x40 = p_params->m_unk0x1c;
	m_unk0x44 = p_params->m_unk0x20;
	m_unk0x48 = p_params->m_unk0x24;
	m_unk0x4c = p_params->m_unk0x28;
	m_unk0x50 = p_params->m_unk0x2c;
	m_unk0x30.m_x = p_params->m_unk0x0c.m_x;
	m_unk0x30.m_y = p_params->m_unk0x0c.m_y;
	m_unk0x30.m_z = p_params->m_unk0x0c.m_z;
	m_unk0x28 = p_params->m_unk0x44;
	m_unk0x2c = p_params->m_unk0x48;
	m_unk0x54 = static_cast<LegoU8>(p_params->m_unk0x30 * 255.0f);

	g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
	m_unk0x58 = static_cast<LegoU32>(g_unk0x004befec[g_unk0x004c6ee4]) % c_randomDelayRangeMs + c_randomDelayBaseMs;

	if (p_params->m_unk0x34) {
		m_flags0x1c |= c_flags0x1cBit0;
	}
	if (p_params->m_unk0x38) {
		m_flags0x1c |= c_flags0x1cBit1;
	}
	if (p_params->m_unk0x3c) {
		m_flags0x1c |= c_flags0x1cBit2;
	}
	if (p_params->m_unk0x40) {
		m_flags0x1c |= c_flags0x1cBit3;
	}

	m_state0x18 = c_state0x18One;
}

// FUNCTION: LEGORACERS 0x00464290
void RaceSession::Field0x2098::Resource0x5c::FUN_00464290()
{
	if (m_unk0x20) {
		m_unk0x24->FUN_00443c10(m_res0x20);
		m_unk0x20 = NULL;
	}

	m_unk0x24 = NULL;
	m_unk0x28 = NULL;
	m_unk0x2c = 0;
	m_flags0x1c = 0;
	Reset();
}

// FUNCTION: LEGORACERS 0x004642c0
void RaceSession::Field0x2098::Resource0x5c::VTable0x04(GolVec3* p_unk0x04)
{
	if (p_unk0x04 && (m_flags0x1c & c_flags0x1cBit3)) {
		m_unk0x30.m_x = p_unk0x04->m_x;
		m_unk0x30.m_y = p_unk0x04->m_y;
		m_unk0x30.m_z = p_unk0x04->m_z;
	}

	if (m_unk0x54 < c_probabilityMax) {
		m_state0x18 = c_state0x18Three;
		return;
	}

	if (m_unk0x28) {
		FUN_004644b0();
	}

	if (!(m_flags0x1c & c_flags0x1cBit0)) {
		m_unk0x24->FUN_00443b80(m_unk0x3c, &m_unk0x30, m_unk0x4c, m_unk0x50, m_unk0x44, m_unk0x48);
		return;
	}

	m_unk0x20 = m_unk0x24->FUN_00443bd0(m_unk0x3c);
	if (m_unk0x20) {
		m_unk0x20->Play(TRUE);
		m_unk0x20->SetDistanceRangeWithMinSquared(m_unk0x4c * m_unk0x4c, m_unk0x50);
		m_unk0x20->SetVolume(m_unk0x44);
		m_unk0x20->SetFrequencyScale(m_unk0x48);
		m_unk0x20->SetPosition(&m_unk0x30);

		GolVec3 velocity;
		velocity.m_x = 0.0f;
		velocity.m_y = 0.0f;
		velocity.m_z = 0.0f;
		m_unk0x20->SetVelocity(velocity);
		m_state0x18 = c_state0x18Three;
	}
}

// FUNCTION: LEGORACERS 0x004643b0
void RaceSession::Field0x2098::Resource0x5c::VTable0x0c()
{
	if (m_unk0x20) {
		m_unk0x24->FUN_00443c10(m_res0x20);
		m_unk0x20 = NULL;
	}

	m_state0x18 = c_state0x18One;
}

// FUNCTION: LEGORACERS 0x004643e0
void RaceSession::Field0x2098::Resource0x5c::VTable0x14(LegoU32 p_elapsedMs)
{
	Resource::VTable0x14(p_elapsedMs);
	if (m_state0x18 == c_state0x18One) {
		return;
	}

	if (m_unk0x58 > p_elapsedMs) {
		m_unk0x58 -= p_elapsedMs;
	}
	else {
		m_unk0x58 = 0;
	}

	if (m_unk0x28) {
		FUN_004644b0();
	}

	if (m_unk0x54 >= c_probabilityMax || m_unk0x58) {
		return;
	}

	g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
	m_unk0x58 = static_cast<LegoU32>(g_unk0x004befec[g_unk0x004c6ee4]) % c_randomDelayRangeMs + c_randomDelayBaseMs;

	g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
	if (static_cast<LegoS32>(g_unk0x004befec[g_unk0x004c6ee4]) % c_probabilityMax >= m_unk0x54) {
		return;
	}

	m_unk0x24->FUN_00443b80(m_unk0x3c, &m_unk0x30, m_unk0x4c, m_unk0x50, m_unk0x44, m_unk0x48);
}

// FUNCTION: LEGORACERS 0x004644b0
void RaceSession::Field0x2098::Resource0x5c::FUN_004644b0()
{
	GolSceneNode* node = m_unk0x28->VTable0x58(0);
	GolTransformBase* transform = node->VTable0x18(m_unk0x2c);

	GolVec3 position;
	position.m_x = 0.0f;
	position.m_y = 0.0f;
	position.m_z = 0.0f;
	GolVec3 transformedPosition;

	do {
		transformedPosition = position;
		transform->VTable0x04(&transformedPosition, &position);
		transform = transform->m_unk0x04;
	} while (transform);

	LegoFloat scale = m_unk0x28->GetModel(0)->GetScale() * m_unk0x28->GetUnk0x58();
	position.m_x = position.m_x * scale;
	position.m_y = position.m_y * scale;
	position.m_z = position.m_z * scale;

	m_unk0x28->VTable0x2c(position, &m_unk0x30);
	if (m_unk0x20) {
		m_unk0x20->SetPosition(&m_unk0x30);
	}
}

// FUNCTION: LEGORACERS 0x0044f2e0 FOLDED
#pragma code_seg(".text$kbd_vt20")
LegoU32 RaceSession::Field0x2098::Resource0x5c::VTable0x18()
{
	return 0;
}
#pragma code_seg()

// TODO: Prevent unwanted ICF with NullMusicGroup::IsLoaded while this folded return helper is still isolated.
// FUNCTION: LEGORACERS 0x00452430 FOLDED
#pragma code_seg(".text$animatedpartresource_vt18")
LegoU32 RaceSession::Field0x2098::AnimatedPartResource0x34::VTable0x18()
{
	return 1;
}
#pragma code_seg()
