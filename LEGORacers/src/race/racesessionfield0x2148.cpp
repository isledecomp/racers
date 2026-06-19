#include "decomp.h"
#include "golanimatedentity.h"
#include "golfileparser.h"
#include "golmath.h"
#include "golmodelentity.h"
#include "golnametable.h"
#include "race/raceeventdispatcher0x08.h"
#include "race/raceeventtable0x90.h"
#include "world/golworlddatabase.h"

#include <string.h>

DECOMP_SIZE_ASSERT(RaceEventDispatcher0x08, 0x08)
DECOMP_SIZE_ASSERT(RaceEventDispatcher0x08::Context, 0x60)
DECOMP_SIZE_ASSERT(RaceEventDispatcher0x08::Item, 0x10)
DECOMP_SIZE_ASSERT(RaceEventDispatcher0x08::ItemI, 0x18)
DECOMP_SIZE_ASSERT(RaceEventDispatcher0x08::Item6, 0x20)
DECOMP_SIZE_ASSERT(RaceEventDispatcher0x08::Item0x3f, 0x18)
DECOMP_SIZE_ASSERT(RaceEventDispatcher0x08::Item0x40, 0x58)
DECOMP_SIZE_ASSERT(RaceEventDispatcher0x08::Item0x28, 0x20)

extern LegoFloat g_cosineTable[1024];
extern const LegoFloat g_negativeRadiansToTableIndex;
extern const LegoFloat g_twoPi;
extern LegoU16 g_unk0x004befec[1024];
extern LegoU32 g_unk0x004c6ee4;

// GLOBAL: LEGORACERS 0x004b0b48
extern const LegoFloat g_item0x40RadiansToTableIndex = 162.974655f;

// GLOBAL: LEGORACERS 0x004b03f0
extern const LegoFloat g_item0x40Pi = 3.1415927f;

// GLOBAL: LEGORACERS 0x004b4270
extern const LegoFloat g_item0x40TrackedEntityZOffset = 17.0f;

static const LegoFloat g_itemIActionPositionX = 132.673004f;
static const LegoFloat g_itemIActionPositionY = 86.304001f;
static const LegoFloat g_itemIActionPositionZ = 14.722000f;
static const LegoFloat g_itemIActionDirectionX = 1.0f;
static const LegoFloat g_itemIActionDirectionY = -0.5f;
static const LegoFloat g_itemIActionDirectionZ = 0.0f;
static const LegoFloat g_item6CycleMs = 10000.0f;
static const LegoFloat g_item6InvCycleMs = 0.0001f;
static const LegoFloat g_item6Tau = 6.2831855f;
static const LegoFloat g_item6CosineIndexScale = -162.974655f;
static const GolVec3 g_item0x3fActionDirection = {1.0f, 0.0f, 0.0f};
static const GolVec3 g_item0x3fActionPositions[] = {
	{-357.582703f, 458.126984f, -11.665112f},
	{-351.203125f, 518.713013f, -94.215683f},
	{-362.258179f, 397.303925f, -94.959518f},
};

// FUNCTION: LEGORACERS 0x0048a400
RaceEventDispatcher0x08::Item::Item()
{
	m_unk0x04 = NULL;
	m_unk0x0c = 0;
	m_unk0x08 = 0;
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RaceEventDispatcher0x08::Item::VTable0x00(undefined4)
{
}

// FUNCTION: LEGORACERS 0x0048a440
RaceEventDispatcher0x08::Item::~Item()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048a450
LegoS32 RaceEventDispatcher0x08::Item::Reset()
{
	m_unk0x04 = NULL;
	m_unk0x0c = 0;
	m_unk0x08 = 0;

	return 0;
}

// FUNCTION: LEGORACERS 0x0048a460
void RaceEventDispatcher0x08::Item::VTable0x14(undefined4)
{
	if (m_unk0x0c == 3) {
		VTable0x08(NULL);
	}
}

// FUNCTION: LEGORACERS 0x0048a470
void RaceEventDispatcher0x08::Item::FUN_0048a470(void* p_unk0x04)
{
	if (m_unk0x0c == 1) {
		VTable0x04(p_unk0x04);
	}
}

// FUNCTION: LEGORACERS 0x0048a490
void RaceEventDispatcher0x08::Item::FUN_0048a490(void* p_unk0x04)
{
	if (m_unk0x0c != 1) {
		VTable0x08(p_unk0x04);
	}
}

// FUNCTION: LEGORACERS 0x0046c9f0 FOLDED
void RaceEventDispatcher0x08::Item::VTable0x18(GolCamera*, RaceState::Racer*)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RaceEventDispatcher0x08::Item::VTable0x1c(GolD3DRenderDevice*)
{
}

// FUNCTION: LEGORACERS 0x0044e7e0 FOLDED
LegoBool32 RaceEventDispatcher0x08::Item::VTable0x20()
{
	return FALSE;
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void RaceEventDispatcher0x08::Item::VTable0x24()
{
}

// FUNCTION: LEGORACERS 0x0046c9f0 FOLDED
void RaceEventDispatcher0x08::Item::VTable0x28(LegoS32, void*)
{
}

// FUNCTION: LEGORACERS 0x0046c9f0 FOLDED
void RaceEventDispatcher0x08::Item::VTable0x2c(LegoS32, void*)
{
}

// FUNCTION: LEGORACERS 0x0048a4b0
RaceEventDispatcher0x08::RaceEventDispatcher0x08()
{
	m_entries = NULL;
	m_count = 0;
}

// FUNCTION: LEGORACERS 0x0048a4c0
RaceEventDispatcher0x08::~RaceEventDispatcher0x08()
{
	Destroy();
}

// STUB: LEGORACERS 0x0048a4d0
void RaceEventDispatcher0x08::FUN_0048a4d0(void*, const LegoChar*, LegoBool32)
{
	STUB(0x48a4d0);
}

// FUNCTION: LEGORACERS 0x0048aa70
void RaceEventDispatcher0x08::Destroy()
{
	LegoU32 i;

	if (m_entries) {
		for (i = 0; i < m_count; i++) {
			m_entries[i]->Reset();
			delete m_entries[i];
		}

		delete[] m_entries;
		m_entries = NULL;
	}

	m_count = 0;
}

// FUNCTION: LEGORACERS 0x0048aad0
void RaceEventDispatcher0x08::FUN_0048aad0(LegoS32 p_unk0x04, void* p_unk0x08)
{
	LegoU32 i;

	for (i = 0; i < m_count; i++) {
		Item* item = m_entries[i];
		if (item->m_unk0x08 != -1 && item->m_unk0x08 == p_unk0x04) {
			item->FUN_0048a470(NULL);
		}

		m_entries[i]->VTable0x28(p_unk0x04, p_unk0x08);
	}
}

// FUNCTION: LEGORACERS 0x0048ab20
void RaceEventDispatcher0x08::FUN_0048ab20(LegoS32 p_unk0x04, void* p_unk0x08)
{
	LegoU32 i;

	for (i = 0; i < m_count; i++) {
		Item* item = m_entries[i];
		if (item->m_unk0x08 != -1 && item->m_unk0x08 == p_unk0x04) {
			item->FUN_0048a490(NULL);
		}

		m_entries[i]->VTable0x2c(p_unk0x04, p_unk0x08);
	}
}

// FUNCTION: LEGORACERS 0x0048ab70
void RaceEventDispatcher0x08::FUN_0048ab70(LegoS32 p_unk0x04)
{
	LegoU32 i;

	for (i = 0; i < m_count; i++) {
		Item* item = m_entries[i];
		if (item->m_unk0x08 != -1 && item->m_unk0x08 == p_unk0x04) {
			item->m_unk0x0c = 3;
		}
	}
}

// FUNCTION: LEGORACERS 0x0048abb0
void RaceEventDispatcher0x08::FUN_0048abb0(LegoS32 p_unk0x04, LegoS32 p_unk0x08, void* p_unk0x0c)
{
	LegoU32 i;

	for (i = 0; i < m_count; i++) {
		Item* item = m_entries[i];
		if (item->m_unk0x08 != -1 && item->m_unk0x08 == p_unk0x04) {
			item->FUN_0048a470(NULL);
		}

		item = m_entries[i];
		if (item->m_unk0x08 != -1 && item->m_unk0x08 == p_unk0x08) {
			item->FUN_0048a490(NULL);
		}

		m_entries[i]->VTable0x28(p_unk0x04, p_unk0x0c);
		m_entries[i]->VTable0x2c(p_unk0x08, p_unk0x0c);
	}
}

// FUNCTION: LEGORACERS 0x0048ac30
void RaceEventDispatcher0x08::FUN_0048ac30(LegoS32 p_unk0x04, void* p_context)
{
	Context* context = static_cast<Context*>(p_context);
	undefined unk0x08[12];
	LegoU32 i;

	for (i = 0; i < m_count; i++) {
		Item* item = m_entries[i];
		if (item->m_unk0x08 != -1 && item->VTable0x20()) {
			item = m_entries[i];
			if (item->m_unk0x08 == p_unk0x04) {
				item->FUN_0048a470(p_context);
			}
		}

		context->m_unk0x5c->VTable0x04(unk0x08);
		m_entries[i]->VTable0x28(p_unk0x04, unk0x08);
	}
}

// FUNCTION: LEGORACERS 0x0048aca0
void RaceEventDispatcher0x08::FUN_0048aca0(LegoS32 p_unk0x04, void* p_context)
{
	Context* context = static_cast<Context*>(p_context);
	undefined unk0x08[12];
	LegoU32 i;

	for (i = 0; i < m_count; i++) {
		Item* item = m_entries[i];
		if (item->m_unk0x08 != -1 && item->VTable0x20()) {
			item = m_entries[i];
			if (item->m_unk0x08 == p_unk0x04) {
				item->FUN_0048a490(p_context);
			}
		}

		context->m_unk0x5c->VTable0x04(unk0x08);
		m_entries[i]->VTable0x2c(p_unk0x04, unk0x08);
	}
}

// FUNCTION: LEGORACERS 0x0048ad10
void RaceEventDispatcher0x08::FUN_0048ad10(LegoS32 p_unk0x04, LegoS32 p_unk0x08, void* p_context)
{
	Context* context = static_cast<Context*>(p_context);
	undefined unk0x0c[12];
	LegoU32 i;

	for (i = 0; i < m_count; i++) {
		Item* item = m_entries[i];
		if (item->m_unk0x08 != -1) {
			if (item->VTable0x20()) {
				item = m_entries[i];
				if (item->m_unk0x08 == p_unk0x04) {
					item->FUN_0048a470(p_context);
				}
			}
		}

		item = m_entries[i];
		if (item->m_unk0x08 != -1 && item->VTable0x20()) {
			item = m_entries[i];
			if (item->m_unk0x08 == p_unk0x08) {
				item->FUN_0048a490(p_context);
			}
		}

		context->m_unk0x5c->VTable0x04(unk0x0c);
		m_entries[i]->VTable0x28(p_unk0x04, unk0x0c);
		m_entries[i]->VTable0x2c(p_unk0x08, unk0x0c);
	}
}

// FUNCTION: LEGORACERS 0x0048add0
void RaceEventDispatcher0x08::FUN_0048add0(undefined4 p_unk0x04)
{
	LegoU32 i;

	for (i = 0; i < m_count; i++) {
		m_entries[i]->VTable0x14(p_unk0x04);
	}
}

// FUNCTION: LEGORACERS 0x0048ae00
void RaceEventDispatcher0x08::FUN_0048ae00(GolCamera* p_unk0x04, RaceState::Racer* p_unk0x08)
{
	LegoU32 i;

	for (i = 0; i < m_count; i++) {
		m_entries[i]->VTable0x18(p_unk0x04, p_unk0x08);
	}
}

// FUNCTION: LEGORACERS 0x0048ae30
void RaceEventDispatcher0x08::FUN_0048ae30(GolD3DRenderDevice* p_renderer)
{
	LegoU32 i;

	for (i = 0; i < m_count; i++) {
		m_entries[i]->VTable0x1c(p_renderer);
	}
}

// FUNCTION: LEGORACERS 0x0048ae60
void RaceEventDispatcher0x08::FUN_0048ae60()
{
	LegoU32 i;

	for (i = 0; i < m_count; i++) {
		m_entries[i]->VTable0x24();
	}
}

// FUNCTION: LEGORACERS 0x0048ae80
RaceEventDispatcher0x08::ItemI::ItemI()
{
	m_unk0x10 = NULL;
	m_unk0x14 = 0;
}

// FUNCTION: LEGORACERS 0x0048aec0
RaceEventDispatcher0x08::ItemI::~ItemI()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048af10
void RaceEventDispatcher0x08::ItemI::VTable0x10(Context* p_context, GolFileParser*)
{
	if (m_unk0x0c) {
		Reset();
	}

	m_unk0x08 = 0;
	m_unk0x10 = p_context->GetUnk0x38();
	m_unk0x14 = p_context->GetUnk0x40();
	m_unk0x0c = 1;
}

// FUNCTION: LEGORACERS 0x0048af50
#pragma code_seg(".text$zz_itemi_reset")
LegoS32 RaceEventDispatcher0x08::ItemI::Reset()
{
	VTable0x08(NULL);
	m_unk0x10 = NULL;
	m_unk0x14 = 0;
	return Item::Reset();
}
#pragma code_seg()

// FUNCTION: LEGORACERS 0x0048af80
void RaceEventDispatcher0x08::ItemI::VTable0x04(void* p_racer)
{
	RaceState::Racer* racer = static_cast<RaceState::Racer*>(p_racer);
	if (racer && m_unk0x0c != 2 && !(racer->GetUnk0xd04() & c_racerFlags0xd04Bit4)) {
		RaceState::Racer::Field0x008::ActionTarget target;
		target.m_unk0x0c.m_x = g_itemIActionDirectionX;
		target.m_unk0x0c.m_y = g_itemIActionDirectionY;
		target.m_unk0x0c.m_z = g_itemIActionDirectionZ;
		target.m_unk0x00.m_x = g_itemIActionPositionX;
		target.m_unk0x00.m_y = g_itemIActionPositionY;
		target.m_unk0x00.m_z = g_itemIActionPositionZ;

		if (m_unk0x14) {
			target.m_unk0x0c.m_y = -g_itemIActionDirectionY;
			target.m_unk0x00.m_y = -g_itemIActionPositionY;
		}

		target.m_positionSource = NULL;
		m_unk0x10->SetUnk0x1998(&target);
		m_unk0x10->FUN_0045b260(racer, 3);
		m_unk0x10->SetUnk0x1998(NULL);
		m_unk0x0c = 2;
	}
}

// FUNCTION: LEGORACERS 0x0048b040
void RaceEventDispatcher0x08::ItemI::VTable0x08(void* p_unk0x04)
{
	if (p_unk0x04) {
		m_unk0x0c = 1;
	}
}

#pragma code_seg(".text$zz_itemi_vt14")
void RaceEventDispatcher0x08::Item0x3f::VTable0x14(undefined4 p_unk0x04)
{
	if (m_unk0x0c != 1) {
		Item::VTable0x14(p_unk0x04);
	}
}

// FUNCTION: LEGORACERS 0x0048b060
void RaceEventDispatcher0x08::ItemI::VTable0x14(undefined4 p_unk0x04)
{
	if (m_unk0x0c != 1) {
		Item::VTable0x14(p_unk0x04);
	}
}
#pragma code_seg()

// FUNCTION: LEGORACERS 0x00452430 FOLDED
#pragma code_seg(".text$animatedpartresource_vt18")
LegoBool32 RaceEventDispatcher0x08::ItemI::VTable0x20()
{
	return 1;
}
#pragma code_seg()

// FUNCTION: LEGORACERS 0x0048b080
RaceEventDispatcher0x08::Item6::Item6()
{
	m_unk0x10 = NULL;
	m_unk0x14 = 0.0f;
	m_unk0x18 = 0.0f;
	m_unk0x1c = 0.0f;
}

// FUNCTION: LEGORACERS 0x0048b0c0
RaceEventDispatcher0x08::Item6::~Item6()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048b110
void RaceEventDispatcher0x08::Item6::VTable0x10(Context* p_context, GolFileParser* p_parser)
{
	if (m_unk0x0c) {
		Reset();
	}

	m_unk0x08 = -1;
	m_unk0x04 = p_context->GetUnk0x0c();

	GolName name;
	::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));

	m_unk0x10 = p_context->GetUnk0x10()->FindUnk0xb4(name);
	if (!m_unk0x10) {
		m_unk0x10 = p_context->GetUnk0x10()->FindUnk0xc0(name);
	}

	if (!m_unk0x10) {
		m_unk0x10 = p_context->GetUnk0x14()->FindUnk0xb4(name);
	}

	if (!m_unk0x10) {
		m_unk0x10 = p_context->GetUnk0x14()->FindUnk0xc0(name);
	}

	m_unk0x14 = p_parser->ReadFloat();
	m_unk0x18 = p_parser->ReadFloat();
	m_unk0x0c = 1;
}

// FUNCTION: LEGORACERS 0x0048b220
void RaceEventDispatcher0x08::Item6::VTable0x04(void*)
{
	m_unk0x0c = 2;
	m_unk0x1c = 0.0f;
}

// FUNCTION: LEGORACERS 0x0048b240
void RaceEventDispatcher0x08::Item6::VTable0x14(undefined4 p_elapsedMs)
{
	Item::VTable0x14(p_elapsedMs);

	m_unk0x1c += static_cast<LegoFloat>(static_cast<LegoU32>(p_elapsedMs));
	if (m_unk0x1c >= g_item6CycleMs) {
		m_unk0x1c -= g_item6CycleMs;
	}

	LegoFloat scaledTime = m_unk0x1c;
	scaledTime *= g_item6InvCycleMs;
	scaledTime *= g_item6Tau;
	scaledTime *= g_item6CosineIndexScale;

	LegoS32 index = -256 - static_cast<LegoS32>(scaledTime);
	index &= 0x3ff;
	LegoFloat scale = g_cosineTable[index];

	LegoFloat amount = m_unk0x14;
	amount *= scale;
	m_unk0x10->FUN_00411700(amount);

	amount = m_unk0x18;
	amount *= scale;
	m_unk0x10->FUN_00411730(amount);
}

// FUNCTION: LEGORACERS 0x0048b2f0
RaceEventDispatcher0x08::Item0x3f::Item0x3f()
{
	m_unk0x10 = NULL;
	m_unk0x14 = 0;
}

// FUNCTION: LEGORACERS 0x0048b330
RaceEventDispatcher0x08::Item0x3f::~Item0x3f()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048b380
void RaceEventDispatcher0x08::Item0x3f::VTable0x10(Context* p_context, GolFileParser*)
{
	if (m_unk0x0c) {
		Reset();
	}

	m_unk0x10 = p_context->GetUnk0x38();
	m_unk0x14 = p_context->GetUnk0x40();
	m_unk0x08 = 8;
	m_unk0x0c = 1;
}

// FUNCTION: LEGORACERS 0x0048b3c0
void RaceEventDispatcher0x08::Item0x3f::VTable0x04(void*)
{
	RaceState::Racer::Field0x008::ActionTarget target;
	target.m_unk0x0c = g_item0x3fActionDirection;

	g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
	LegoS32 positionIndex = g_unk0x004befec[g_unk0x004c6ee4] % c_positionCount;
	target.m_positionSource = NULL;
	target.m_unk0x00 = g_item0x3fActionPositions[positionIndex];
	if (m_unk0x14) {
		target.m_unk0x00.m_y = -target.m_unk0x00.m_y;
	}

	m_unk0x10->SetUnk0x1998(&target);
	m_unk0x10->FUN_0045a9b0(NULL, 3);
	m_unk0x10->SetUnk0x1998(NULL);
	m_unk0x0c = 2;
}

LegoS32 RaceEventDispatcher0x08::Item0x3f::Reset()
{
	VTable0x08(NULL);
	m_unk0x10 = NULL;
	m_unk0x14 = 0;
	return Item::Reset();
}

// FUNCTION: LEGORACERS 0x0048d470 FOLDED
void RaceEventDispatcher0x08::Item0x3f::VTable0x08(void*)
{
	m_unk0x0c = 1;
}

// FUNCTION: LEGORACERS 0x0048b480
RaceEventDispatcher0x08::Item0x40::Item0x40()
{
	ClearFields();
}

// FUNCTION: LEGORACERS 0x0048b4f0
RaceEventDispatcher0x08::Item0x40::~Item0x40()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048b540
void RaceEventDispatcher0x08::Item0x40::ClearFields()
{
	m_unk0x38 = NULL;
	m_unk0x34 = NULL;
	m_unk0x48 = 0;
	m_unk0x4c = 0;
	m_unk0x50 = 0;
	m_unk0x3c = 0.0f;
	m_unk0x40 = 0.0f;
	m_unk0x44 = 0.0f;
	m_unk0x10.m_x = 0.0f;
	m_unk0x10.m_y = 0.0f;
	m_unk0x10.m_z = 0.0f;
	m_unk0x1c.m_x = 0.0f;
	m_unk0x1c.m_y = 0.0f;
	m_unk0x1c.m_z = 0.0f;
	m_unk0x28.m_x = 0.0f;
	m_unk0x28.m_y = 0.0f;
	m_unk0x28.m_z = 0.0f;
	m_unk0x54 = 0;
}

// FUNCTION: LEGORACERS 0x0048b580
void RaceEventDispatcher0x08::Item0x40::VTable0x10(Context* p_context, GolFileParser* p_parser)
{
	if (m_unk0x0c) {
		Reset();
	}

	GolName name;
	name[0] = '\0';

	m_unk0x54 = p_context->GetUnk0x40();
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token;
	while ((token = p_parser->GetNextToken()) != GolFileParser::e_rightCurly) {
		switch (token) {
		case GolFileParser::e_unknown0x42:
			::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));
			break;
		case GolFileParser::e_unknown0x37:
			m_unk0x10.m_x = p_parser->ReadFloat();
			m_unk0x10.m_y = p_parser->ReadFloat();
			m_unk0x10.m_z = p_parser->ReadFloat();
			if (m_unk0x54) {
				m_unk0x10.m_y = -m_unk0x10.m_y;
			}
			break;
		case GolFileParser::e_unknown0x46:
			m_unk0x50 = p_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x3b:
			m_unk0x08 = p_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x47:
			m_unk0x3c = p_parser->ReadFloat();
			m_unk0x40 = p_parser->ReadFloat();
			m_unk0x44 = p_parser->ReadFloat();
			break;
		default:
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}
	}

	m_unk0x34 = p_context->GetUnk0x38();
	if (name[0]) {
		m_unk0x38 = p_context->GetUnk0x10()->FindUnk0xc0(name);
	}
	m_unk0x0c = 1;
}

// FUNCTION: LEGORACERS 0x0048b700
LegoS32 RaceEventDispatcher0x08::Item0x40::Reset()
{
	VTable0x08(NULL);
	ClearFields();
	return Item::Reset();
}

// FUNCTION: LEGORACERS 0x0048b720
void RaceEventDispatcher0x08::Item0x40::VTable0x04(void*)
{
	m_unk0x4c = c_actionCooldownMs;
	m_unk0x0c = 2;
}

// FUNCTION: LEGORACERS 0x0048b740
void RaceEventDispatcher0x08::Item0x40::VTable0x14(undefined4 p_elapsedMs)
{
	if (m_unk0x0c != 1) {
		RaceState::Racer::Field0x008::ActionTarget target;
		Item::VTable0x14(p_elapsedMs);

		LegoU32 elapsedMs = static_cast<LegoU32>(p_elapsedMs);
		m_unk0x48 += elapsedMs;
		if (m_unk0x48 >= m_unk0x50) {
			m_unk0x48 = 0;
		}

		LegoU32 currentTime = m_unk0x48;
		LegoU32 halfPeriod = m_unk0x50 >> 1;
		LegoFloat lateralAngle = static_cast<LegoFloat>(static_cast<LegoS32>(currentTime)) /
								 static_cast<LegoFloat>(static_cast<LegoS32>(halfPeriod));
		lateralAngle *= m_unk0x3c;
		if (currentTime > halfPeriod) {
			lateralAngle = g_item0x40Pi - lateralAngle;
		}

		LegoS32 index = static_cast<LegoS32>(lateralAngle * g_item0x40RadiansToTableIndex) & 0x3ff;
		m_unk0x28.m_x = g_cosineTable[index];

		index = (0xffffff00 - static_cast<LegoS32>(lateralAngle * g_negativeRadiansToTableIndex)) & 0x3ff;
		m_unk0x28.m_y = g_cosineTable[index];
		if (m_unk0x54) {
			m_unk0x28.m_y = -m_unk0x28.m_y;
		}

		LegoU32 quarterPeriod = m_unk0x50 >> 2;
		LegoFloat verticalAngle = static_cast<LegoFloat>(static_cast<LegoS32>(currentTime)) /
								  static_cast<LegoFloat>(static_cast<LegoS32>(quarterPeriod));
		verticalAngle *= g_twoPi;
		verticalAngle *= g_item0x40RadiansToTableIndex;
		index = static_cast<LegoS32>(verticalAngle) & 0x3ff;
		m_unk0x28.m_z = g_cosineTable[index] * m_unk0x40 + m_unk0x44;

		GolMath::NormalizeVector3(m_unk0x28, &m_unk0x28);

		if (m_unk0x38) {
			m_unk0x38->VTable0x04(&m_unk0x10);
			m_unk0x10.m_z -= g_item0x40TrackedEntityZOffset;
		}

		m_unk0x4c += elapsedMs;
		if (m_unk0x4c >= c_actionCooldownMs) {
			target.m_positionSource = &m_unk0x10;
			m_unk0x34->SetUnk0x1998(&target);
			m_unk0x34->FUN_0045a950(NULL, 2);
			m_unk0x34->SetUnk0x1998(NULL);
			m_unk0x4c = 0;
		}
	}
}

void RaceEventDispatcher0x08::Item0x40::VTable0x08(void*)
{
	m_unk0x0c = 1;
}

// FUNCTION: LEGORACERS 0x0048b890
RaceEventDispatcher0x08::Item0x28::Item0x28()
{
	m_unk0x10 = NULL;
	m_unk0x14 = 0;
	m_unk0x18 = NULL;
	m_unk0x1c = 0;
}

// FUNCTION: LEGORACERS 0x0048b8d0
RaceEventDispatcher0x08::Item0x28::~Item0x28()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048b920
void RaceEventDispatcher0x08::Item0x28::VTable0x10(Context* p_context, GolFileParser*)
{
	if (m_unk0x0c) {
		Reset();
	}

	m_unk0x08 = 0x0a;
	m_unk0x04 = p_context->GetUnk0x0c();
	m_unk0x14 = p_context->GetUnk0x1c();
	m_unk0x10 = p_context->GetUnk0x10()->FindUnk0xc0("piltop");

	GolNameTable* nameTable = p_context->GetUnk0x2c();
	m_unk0x18 = nameTable->GetNameEntries() == NULL ? NULL : static_cast<Field0x18*>(nameTable->GetName("pilcol"));

	m_unk0x10->SetFlags(m_unk0x10->GetFlags() & ~GolAnimatedEntity::c_flagPartAnimation);
	m_unk0x0c = 1;
}

// FUNCTION: LEGORACERS 0x0048b9b0 FOLDED
LegoS32 RaceEventDispatcher0x08::Item0x28::Reset()
{
	VTable0x08(NULL);
	m_unk0x10 = NULL;
	m_unk0x14 = 0;
	m_unk0x18 = NULL;
	m_unk0x1c = 0;
	return Item::Reset();
}

// FUNCTION: LEGORACERS 0x0048b9b0 FOLDED
LegoS32 RaceEventDispatcher0x08::Item6::Reset()
{
	VTable0x08(NULL);
	m_unk0x10 = NULL;
	m_unk0x14 = 0.0f;
	m_unk0x18 = 0.0f;
	m_unk0x1c = 0.0f;
	return Item::Reset();
}

// FUNCTION: LEGORACERS 0x0048b9e0
void RaceEventDispatcher0x08::Item0x28::VTable0x04(void*)
{
	m_unk0x10->SetFlags(m_unk0x10->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_unk0x10->FUN_0040dad0(0);
	m_unk0x10->SetFlags(m_unk0x10->GetFlags() & ~GolAnimatedEntity::c_flagLoopCurrentPart);
	m_unk0x1c = 0;
	m_unk0x0c = 2;
}

void RaceEventDispatcher0x08::Item0x28::VTable0x08(void*)
{
}

// FUNCTION: LEGORACERS 0x0048ba20
void RaceEventDispatcher0x08::Item0x28::VTable0x14(undefined4 p_elapsedMs)
{
	if (m_unk0x0c != 1) {
		Item::VTable0x14(p_elapsedMs);

		if (m_unk0x1c == 0 && m_unk0x10->GetUnk0xb4() > 50.0f) {
			m_unk0x18->m_flags0x08 &= ~c_field0x18FlagBit16;
			m_unk0x18->m_flags0x08 &= ~c_field0x18FlagBit17;
			m_unk0x04->FUN_00462580(7, 7, NULL);
			m_unk0x1c = 1;
		}
	}
}

// FUNCTION: LEGORACERS 0x0048ba90
void RaceEventDispatcher0x08::Item0x28::VTable0x24()
{
	m_unk0x0c = 1;
	m_unk0x1c = 0;
	m_unk0x18->m_flags0x08 |= c_field0x18FlagBit16;
	m_unk0x18->m_flags0x08 |= c_field0x18FlagBit17;
	m_unk0x10->SetFlags(m_unk0x10->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_unk0x10->FUN_0040dae0(0, 0);
	m_unk0x10->VTable0x5c(0);
	m_unk0x10->SetFlags(m_unk0x10->GetFlags() & ~GolAnimatedEntity::c_flagPartAnimation);
}

void RaceEventDispatcher0x08::Item6::VTable0x08(void*)
{
	m_unk0x0c = 1;
}
