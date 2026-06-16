#include "core/gol.h"
#include "decomp.h"
#include "race/racesession.h"
#include "render/gold3drenderdevice.h"

DECOMP_SIZE_ASSERT(RaceSession::Field0x27c8, 0x0c)
DECOMP_SIZE_ASSERT(RaceSession::Field0x27c8::Item, 0x2a4)

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RaceSession::Field0x27c8::Item::FUN_004513d0(GolD3DRenderDevice*)
{
}

// FUNCTION: LEGORACERS 0x00492960
void RaceSession::Field0x27c8::Item::Destroy()
{
	if (m_unk0x008) {
		m_unk0x004->VTable0x48(m_unk0x008);
		m_unk0x008 = NULL;
	}

	m_unk0x00c.VTable0x54();
	Reset();
}

// FUNCTION: LEGORACERS 0x00492990
void RaceSession::Field0x27c8::Item::Reset()
{
	LegoU32 zero = 0;

	m_unk0x004 = NULL;
	m_unk0x008 = NULL;
	m_flags0x09c = static_cast<LegoU8>(zero);
	m_unk0x0a0[0] = zero;
	m_unk0x0a0[1] = zero;
	m_unk0x0a0[2] = zero;
	m_unk0x0a0[3] = zero;
	m_unk0x0a0[4] = zero;
	m_unk0x0a0[5] = zero;
	m_unk0x0a0[6] = zero;
	m_unk0x0a0[7] = zero;
	m_unk0x0a0[8] = zero;
	m_unk0x0a0[9] = zero;
	m_unk0x0a0[10] = zero;
	m_unk0x0a0[11] = zero;
	m_unk0x0a0[12] = zero;
	m_unk0x0a0[13] = zero;
	m_unk0x0d8[0] = 0xff;
	m_unk0x0d8[1] = 0xff;
	m_unk0x0d8[2] = 0xff;
	m_unk0x0d8[3] = 0xff;

	for (LegoU32 i = 0; i < sizeOfArray(m_unk0x0dc); i++) {
		m_unk0x0dc[i][0] = zero;
		m_unk0x0dc[i][16] = zero;
		m_unk0x0dc[i][17] = zero;
		m_unk0x0dc[i][18] = zero;

		LegoU32* field = &m_unk0x0dc[i][3];
		for (LegoU32 j = 0; j < 5; j++) {
			field[-2] = zero;
			field[-1] = zero;
			field[0] = zero;
			field += 3;
		}
	}
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
