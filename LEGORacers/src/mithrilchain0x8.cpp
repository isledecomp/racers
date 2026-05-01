#include "mithrilchain0x8.h"

#include "golerror.h"

DECOMP_SIZE_ASSERT(MithrilChain0x8, 0x8)
DECOMP_SIZE_ASSERT(MithrilChain0x8::Entry, 0x18)

// FUNCTION: LEGORACERS 0x0045c3b0
MithrilChain0x8::MithrilChain0x8()
{
	m_entries = NULL;
	m_count = 0;
}

// FUNCTION: LEGORACERS 0x00490500
MithrilChain0x8::Entry::Entry()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x00490510
MithrilChain0x8::Entry::~Entry()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00490520
void MithrilChain0x8::Entry::Reset()
{
	Deactivate();
}

// FUNCTION: LEGORACERS 0x00490530
void MithrilChain0x8::Entry::Clear()
{
	m_unk0x00 = 0;
	m_unk0x04 = 0;
	m_remainingMs = 0;
	m_durationMs = 0;
	m_flags = 0;
	m_unk0x08[0] = 0;
	m_unk0x08[1] = 0;
	m_unk0x08[2] = 0;
	m_unk0x08[3] = 0;
}

// FUNCTION: LEGORACERS 0x00490580
void MithrilChain0x8::Entry::Deactivate()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x00490590
void MithrilChain0x8::Entry::Update(LegoU32 p_elapsedMs)
{
	if (m_flags & c_flagActive) {
		if (!m_remainingMs) {
			if (m_flags & c_flagExpired) {
				Deactivate();
			}
			else {
				m_flags |= c_flagExpired;
			}
		}

		if (p_elapsedMs > m_remainingMs) {
			m_remainingMs = 0;
			return;
		}

		m_remainingMs -= p_elapsedMs;
	}
}

// STUB: LEGORACERS 0x004905e0
void MithrilChain0x8::Entry::Draw(BronzeFalcon0xc8770*)
{
	// TODO
	STUB(0x4905e0);
}

// FUNCTION: LEGORACERS 0x00494d90
MithrilChain0x8::~MithrilChain0x8()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00494da0
void MithrilChain0x8::Reset()
{
	if (m_entries) {
		for (LegoU32 i = 0; i < m_count; i++) {
			m_entries[i].Reset();
		}

		delete[] m_entries;
		m_entries = NULL;
	}

	m_count = 0;
}

// FUNCTION: LEGORACERS 0x00494e10
void MithrilChain0x8::Allocate(LegoU32 p_count)
{
	if (m_entries) {
		Reset();
	}

	if (p_count) {
		m_entries = new Entry[p_count];
		if (!m_entries) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_count = p_count;
	}
}

// FUNCTION: LEGORACERS 0x00494f60
void MithrilChain0x8::Update(LegoU32 p_elapsedMs)
{
	for (LegoU32 i = 0; i < m_count; i++) {
		if (m_entries[i].IsActive()) {
			m_entries[i].Update(p_elapsedMs);
		}
	}
}

// FUNCTION: LEGORACERS 0x00494fa0
void MithrilChain0x8::Draw(BronzeFalcon0xc8770* p_renderer)
{
	for (LegoU32 i = 0; i < m_count; i++) {
		if (m_entries[i].IsActive()) {
			m_entries[i].Draw(p_renderer);
		}
	}
}
