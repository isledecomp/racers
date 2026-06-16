#include "audio/streamingsoundinstance.h"
#include "race/racestate.h"
#include "world/golworlddatabase.h"

DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x008::Action, 0x2c)

extern const LegoFloat g_unk0x004b0958;
extern const LegoFloat g_unk0x004b095c;

// FUNCTION: LEGORACERS 0x0045a950
LegoU32 RaceState::Racer::Field0x008::FUN_0045a950(Racer* p_racer, LegoU32 p_unk0x08)
{
	switch (p_unk0x08) {
	case 0:
		return FUN_0045aa30(p_racer, 0);
	case 1:
		return FUN_0045ab50(p_racer, 1);
	case 2:
		return FUN_0045ac80(p_racer, 2);
	case 3:
		return FUN_0045af80(p_racer, 3);
	default:
		return p_unk0x08;
	}
}

// FUNCTION: LEGORACERS 0x0045a9b0
LegoU32 RaceState::Racer::Field0x008::FUN_0045a9b0(Racer* p_racer, LegoU32 p_unk0x08)
{
	LegoU32 result = p_unk0x08;

	switch (p_unk0x08) {
	case 0:
		result = FUN_0045ace0(p_racer, 0);
		break;
	case 1:
		result = FUN_0045ad30(p_racer, 1);
		break;
	case 2:
		result = 25 - m_unk0x187c;
		if (result >= 3) {
			result = FUN_0045adf0(p_racer, 2);
		}
		break;
	case 3:
		result = 25 - m_unk0x187c;
		if (result >= 3) {
			result = FUN_0045aeb0(p_racer, 3);
		}
		break;
	}

	return result;
}

// STUB: LEGORACERS 0x0045aa30
LegoU32 RaceState::Racer::Field0x008::FUN_0045aa30(Racer*, LegoU32)
{
	STUB(0x0045aa30);
	return 0;
}

// STUB: LEGORACERS 0x0045ab50
LegoU32 RaceState::Racer::Field0x008::FUN_0045ab50(Racer*, LegoU32)
{
	STUB(0x0045ab50);
	return 0;
}

// STUB: LEGORACERS 0x0045ac80
LegoU32 RaceState::Racer::Field0x008::FUN_0045ac80(Racer*, LegoU32)
{
	STUB(0x0045ac80);
	return 0;
}

// STUB: LEGORACERS 0x0045ace0
LegoU32 RaceState::Racer::Field0x008::FUN_0045ace0(Racer*, LegoU32)
{
	STUB(0x0045ace0);
	return 0;
}

// STUB: LEGORACERS 0x0045ad30
LegoU32 RaceState::Racer::Field0x008::FUN_0045ad30(Racer*, LegoU32)
{
	STUB(0x0045ad30);
	return 0;
}

// STUB: LEGORACERS 0x0045adf0
LegoU32 RaceState::Racer::Field0x008::FUN_0045adf0(Racer*, LegoU32)
{
	STUB(0x0045adf0);
	return 0;
}

// STUB: LEGORACERS 0x0045aeb0
LegoU32 RaceState::Racer::Field0x008::FUN_0045aeb0(Racer*, LegoU32)
{
	STUB(0x0045aeb0);
	return 0;
}

// STUB: LEGORACERS 0x0045af80
LegoU32 RaceState::Racer::Field0x008::FUN_0045af80(Racer*, LegoU32)
{
	STUB(0x0045af80);
	return 0;
}

// FUNCTION: LEGORACERS 0x0045b030
void RaceState::Racer::Field0x008::FUN_0045b030(Racer* p_racer, LegoU32 p_unk0x08)
{
	if (25 - m_unk0x187c >= 2) {
		LegoU32 subtype = p_unk0x08;
		Action* action = m_unk0x098;
		if (!action) {
			action = FUN_0045b2e0(2, 0, 1, 2, 3);
		}
		else {
			m_unk0x098 = action->m_next;
		}

		action->m_next = m_unk0x1880;
		m_unk0x1880 = action;

		GolAnimatedEntity* model;
		GolAnimatedEntity* inputModel;
		switch (subtype) {
		case 0:
			if (!m_unk0x05c->GetUnk0xc0NameEntries()) {
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
			if (!m_unk0x05c->GetUnk0xc0NameEntries()) {
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
			if (!m_unk0x05c->GetUnk0xc0NameEntries()) {
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
			if (!m_unk0x05c->GetUnk0xc0NameEntries()) {
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
		action->m_unk0x014 = subtype;
	}
}

// FUNCTION: LEGORACERS 0x0045b1e0
void RaceState::Racer::Field0x008::FUN_0045b1e0(Racer* p_racer, LegoU32 p_unk0x08)
{
	if (p_unk0x08 == 3) {
		FUN_0045b260(p_racer, 3);
	}
	else if (25 - m_unk0x187c >= 3) {
		Action* action = m_unk0x09c;
		if (!action) {
			action = FUN_0045b2e0(3, 0, 1, 2, -1);
		}
		else {
			m_unk0x09c = action->m_next;
		}

		action->m_next = m_unk0x1880;
		m_unk0x1880 = action;
		action->FUN_0045c8f0(p_racer, p_unk0x08);
		action->m_unk0x014 = p_unk0x08;
	}
}

// FUNCTION: LEGORACERS 0x0045b260
LegoU32 RaceState::Racer::Field0x008::FUN_0045b260(Racer* p_racer, LegoU32 p_unk0x08)
{
	Action* action = m_unk0x0a0;
	if (!action) {
		action = FUN_0045b2e0(3, p_unk0x08, -1, -1, -1);
	}
	else {
		m_unk0x0a0 = action->m_next;
	}

	action->m_next = m_unk0x1880;
	m_unk0x1880 = action;

	GolModelEntity* model;
	if (!m_unk0x05c->GetUnk0xb4NameEntries()) {
		model = NULL;
	}
	else {
		model = m_unk0x05c->GetUnk0xb4Name("warpprt");
	}

	LegoU32 result = action->FUN_0045d560(p_racer, model, m_unk0x1998);
	action->m_unk0x014 = p_unk0x08;
	return result;
}

// FUNCTION: LEGORACERS 0x0045b2e0
RaceState::Racer::Field0x008::Action* RaceState::Racer::Field0x008::FUN_0045b2e0(
	LegoU32 p_unk0x04,
	LegoU32 p_unk0x08,
	LegoS32 p_unk0x0c,
	LegoS32 p_unk0x10,
	LegoS32 p_unk0x14
)
{
	Action* previous = NULL;
	Action* bestPrevious = NULL;
	Action* best = NULL;
	LegoS32 bestScore = 0;
	LegoU32 bestPriority = 0xffffffff;

	for (Action* action = m_unk0x1880; action; action = action->m_next) {
		if (action->VTable0x18() == p_unk0x04) {
			LegoU32 subtype = action->m_unk0x014;
			if (subtype == p_unk0x08 || subtype == static_cast<LegoU32>(p_unk0x0c) ||
				subtype == static_cast<LegoU32>(p_unk0x10) || subtype == static_cast<LegoU32>(p_unk0x14)) {
				LegoS32 score = action->m_unk0x004;
				if (score > bestScore) {
					bestPriority = action->m_unk0x008;
					bestScore = action->m_unk0x004;
					best = action;
					bestPrevious = previous;
				}
				else if (score == bestScore) {
					LegoU32 priority = action->m_unk0x008;
					if (priority < bestPriority) {
						bestScore = action->m_unk0x004;
						bestPriority = priority;
						best = action;
						bestPrevious = previous;
					}
				}
			}
		}

		previous = action;
	}

	if (!bestPrevious) {
		m_unk0x1880 = best->m_next;
	}
	else {
		bestPrevious->m_next = best->m_next;
	}

	best->m_next = NULL;
	best->VTable0x1c();

	return best;
}

// FUNCTION: LEGORACERS 0x0045b640
void RaceState::Racer::Field0x008::FUN_0045b640(Racer* p_racer)
{
	for (LegoU32 i = 0; i < m_unk0x188c; i++) {
		Field0x18b0* entry = &m_unk0x18b0[i];
		if (entry->m_unk0x004 > 1 && entry->m_unk0x020 == p_racer) {
			entry->m_unk0x004 = 6;
		}
	}
}

// FUNCTION: LEGORACERS 0x0045b9e0
GolAnimatedEntity* RaceState::Racer::Field0x008::FUN_0045b9e0()
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

// FUNCTION: LEGORACERS 0x0045bd30
void RaceState::Racer::Field0x008::Action::FUN_0045bd30(
	Racer* p_racer,
	LegoU32 p_unk0x08,
	GolAnimatedEntity* p_unk0x0c,
	GolAnimatedEntity* p_unk0x10
)
{
	LegoU32 soundId = 0x4c;

	m_unk0x018 = m_unk0x024->FUN_0045b9e0();
	if (!m_unk0x018) {
		m_unk0x004 = 6;
		return;
	}

	m_unk0x01c = m_unk0x024->FUN_0045b9e0();
	if (!m_unk0x01c) {
		m_unk0x004 = 6;
		return;
	}

	m_unk0x020 = p_racer;
	if (m_unk0x020->m_unk0xd04 & Racer::c_flags0xd04Bit0) {
		m_unk0x024->FUN_0045b640(m_unk0x020);
	}

	switch (p_unk0x08) {
	case 0:
		m_unk0x008 = 4000;
		soundId = 0x4c;
		break;
	case 1:
		m_unk0x008 = 6000;
		soundId = 0x35;
		break;
	case 2:
		m_unk0x008 = 8000;
		soundId = 0x4d;
		break;
	case 3:
		m_unk0x008 = 10000;
		soundId = 0x4e;
		break;
	}

	m_unk0x028 = m_unk0x010->FUN_00443bd0(soundId);
	if (m_unk0x028) {
		m_unk0x028->Play(TRUE);
		m_unk0x028->SetDistanceRange(g_unk0x004b0958, g_unk0x004b095c);
	}

	m_unk0x004 = 3;
	m_unk0x020->FUN_00439770(p_unk0x08);
	if (m_unk0x020->m_unk0xd04 & Racer::c_flags0xd04Bit11) {
		m_unk0x020->FUN_00439b00();
	}
	m_unk0x014 = p_unk0x08;

	m_unk0x018->FUN_0040d550(
		p_unk0x0c->GetModel(0),
		p_unk0x0c->VTable0x58(0),
		p_unk0x0c->GetModelPart(0),
		p_unk0x0c->GetModelDistance(0)
	);

	LegoU32 i;
	for (i = 1; i < 3; i++) {
		GolModelBase* model = p_unk0x0c->GetModel(i);
		if (model) {
			m_unk0x018->FUN_10023940(
				model,
				p_unk0x0c->VTable0x58(i),
				p_unk0x0c->GetModelPart(i),
				p_unk0x0c->GetModelDistance(i)
			);
		}
	}

	m_unk0x018->FUN_0040dad0(0);
	m_unk0x018->SetFlags(m_unk0x018->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_unk0x018->SetUnk0xb8(p_unk0x0c->GetUnk0xb8());
	m_unk0x018->FUN_00411680(p_unk0x0c->FUN_00411640());
	m_unk0x018->FUN_004116b0(p_unk0x0c->FUN_00411660());
	m_unk0x018->FUN_00411700(p_unk0x0c->FUN_004116e0());
	m_unk0x018->FUN_00411730(p_unk0x0c->FUN_004116f0());
	m_unk0x018->CopyPositionFrom(*m_unk0x020->m_unk0x018.m_unk0x044);

	m_unk0x01c->FUN_0040d550(
		p_unk0x10->GetModel(0),
		p_unk0x10->VTable0x58(0),
		p_unk0x10->GetModelPart(0),
		p_unk0x10->GetModelDistance(0)
	);

	for (i = 1; i < 3; i++) {
		GolModelBase* model = p_unk0x10->GetModel(i);
		if (model) {
			m_unk0x01c->FUN_10023940(
				model,
				p_unk0x10->VTable0x58(i),
				p_unk0x10->GetModelPart(i),
				p_unk0x10->GetModelDistance(i)
			);
		}
	}

	m_unk0x01c->FUN_0040dad0(0);
	m_unk0x01c->SetFlags(m_unk0x01c->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_unk0x01c->SetUnk0xb8(p_unk0x10->GetUnk0xb8());
	m_unk0x01c->FUN_00411680(p_unk0x10->FUN_00411640());
	m_unk0x01c->FUN_004116b0(p_unk0x10->FUN_00411660());
	m_unk0x01c->FUN_00411700(p_unk0x10->FUN_004116e0());
	m_unk0x01c->FUN_00411730(p_unk0x10->FUN_004116f0());
	m_unk0x01c->CopyPositionFrom(*m_unk0x018);
}

// STUB: LEGORACERS 0x0045c8f0
void RaceState::Racer::Field0x008::Action::FUN_0045c8f0(Racer*, LegoU32)
{
	STUB(0x0045c8f0);
}

// STUB: LEGORACERS 0x0045d560
LegoU32 RaceState::Racer::Field0x008::Action::FUN_0045d560(Racer*, GolModelEntity*, LegoU32)
{
	STUB(0x0045d560);
	return 0;
}
