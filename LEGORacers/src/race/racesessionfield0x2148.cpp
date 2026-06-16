#include "decomp.h"
#include "race/raceeventdispatcher0x08.h"

DECOMP_SIZE_ASSERT(RaceEventDispatcher0x08, 0x08)
DECOMP_SIZE_ASSERT(RaceEventDispatcher0x08::Item, 0x10)

// FUNCTION: LEGORACERS 0x0048a400
RaceEventDispatcher0x08::Item::Item()
{
	m_unk0x04 = 0;
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
	m_unk0x04 = 0;
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
void RaceEventDispatcher0x08::Item::VTable0x18(GolCamera*, undefined4)
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
void RaceEventDispatcher0x08::FUN_0048ac30(LegoS32 p_unk0x04, Context* p_context)
{
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

		p_context->m_unk0x5c->VTable0x04(unk0x08);
		m_entries[i]->VTable0x28(p_unk0x04, unk0x08);
	}
}

// FUNCTION: LEGORACERS 0x0048aca0
void RaceEventDispatcher0x08::FUN_0048aca0(LegoS32 p_unk0x04, Context* p_context)
{
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

		p_context->m_unk0x5c->VTable0x04(unk0x08);
		m_entries[i]->VTable0x2c(p_unk0x04, unk0x08);
	}
}

// FUNCTION: LEGORACERS 0x0048ad10
void RaceEventDispatcher0x08::FUN_0048ad10(LegoS32 p_unk0x04, LegoS32 p_unk0x08, Context* p_context)
{
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

		p_context->m_unk0x5c->VTable0x04(unk0x0c);
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
void RaceEventDispatcher0x08::FUN_0048ae00(GolCamera* p_unk0x04, undefined4 p_unk0x08)
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
