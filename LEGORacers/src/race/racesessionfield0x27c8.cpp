#include "decomp.h"
#include "race/racesession.h"
#include "render/gold3drenderdevice.h"

DECOMP_SIZE_ASSERT(RaceSession::Field0x27c8, 0x0c)
DECOMP_SIZE_ASSERT(RaceSession::Field0x27c8::Item, 0x2a4)

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RaceSession::Field0x27c8::Item::FUN_004513d0(GolD3DRenderDevice*)
{
}

// STUB: LEGORACERS 0x00492960
void RaceSession::Field0x27c8::Item::Destroy()
{
	STUB(0x00492960);
}

// FUNCTION: LEGORACERS 0x00493790
void RaceSession::Field0x27c8::Item::FUN_00493790(GolD3DRenderDevice* p_renderer)
{
	if (m_flags0x09c & c_flags0x09cBit5) {
		p_renderer->VTable0x94(&m_unk0x00c);
	}
}

// FUNCTION: LEGORACERS 0x004937b0
RaceSession::Field0x27c8::Field0x27c8()
{
	m_items = NULL;
	m_count = 0;
}

// FUNCTION: LEGORACERS 0x004937f0
RaceSession::Field0x27c8::~Field0x27c8()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00493800
void RaceSession::Field0x27c8::Destroy()
{
	if (m_items) {
		for (LegoU32 i = 0; i < m_count; i++) {
			m_items[i].Destroy();
		}

		Item* items = m_items;
		if (items) {
			items->VTable0x00(3);
		}

		m_items = NULL;
	}

	m_count = 0;
}

// STUB: LEGORACERS 0x00493950
void RaceSession::Field0x27c8::Item::VTable0x00(undefined4)
{
	STUB(0x00493950);
}

// STUB: LEGORACERS 0x00493a20
void RaceSession::Field0x27c8::FUN_00493a20(LegoU32)
{
	STUB(0x00493a20);
}

// FUNCTION: LEGORACERS 0x00493a60
LegoU32 RaceSession::Field0x27c8::FUN_00493a60(GolD3DRenderDevice* p_renderer)
{
	LegoU32 i;
	LegoU32 result = m_count;

	for (i = 0; i < result; i++) {
		LegoU8 flags = m_items[i].GetFlags0x09c();
		if (flags & Item::c_flags0x09cBit0) {
			m_items[i].FUN_004513d0(p_renderer);
		}

		result = m_count;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00493aa0
LegoU32 RaceSession::Field0x27c8::FUN_00493aa0(GolD3DRenderDevice* p_renderer)
{
	LegoU32 i;
	LegoU32 result = m_count;

	for (i = 0; i < result; i++) {
		if (m_items[i].IsActive()) {
			m_items[i].FUN_00493790(p_renderer);
		}

		result = m_count;
	}

	return result;
}
