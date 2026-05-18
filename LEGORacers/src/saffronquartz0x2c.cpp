#include "saffronquartz0x2c.h"

#include "amberlens0x344.h"
#include "bluebellfog0x4.h"
#include "bronzefalcon0xc8770.h"
#include "gol.h"
#include "zoweeblubberworth0xf0.h"

#include <string.h>

DECOMP_SIZE_ASSERT(SaffronQuartz0x2c, 0x2c)
DECOMP_SIZE_ASSERT(SaffronQuartz0x2c::Frame0xb8, 0xb8)
DECOMP_SIZE_ASSERT(SaffronQuartz0x2c::Frame0xb8::Event0x20, 0x20)

// FUNCTION: LEGORACERS 0x00405520
SaffronQuartz0x2c::Frame0xb8::Event0x20::Event0x20()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00405560
SaffronQuartz0x2c::Frame0xb8::Event0x20::~Event0x20()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00405570
void SaffronQuartz0x2c::Frame0xb8::Event0x20::Reset()
{
	m_name[0] = '\0';
	m_unk0x0c = 0;
	m_unk0x10 = 0;
	m_unk0x18 = NULL;
	m_unk0x1c = NULL;
	m_unk0x14 = 0;
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void SaffronQuartz0x2c::Frame0xb8::Event0x20::VTable0x04(undefined4)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void SaffronQuartz0x2c::Frame0xb8::Event0x20::VTable0x08(BronzeFalcon0xc8770*)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void SaffronQuartz0x2c::Frame0xb8::Event0x20::VTable0x0c(BronzeFalcon0xc8770*)
{
}

// FUNCTION: LEGORACERS 0x00405590
void SaffronQuartz0x2c::Frame0xb8::Event0x20::VTable0x10(Frame0xb8* p_frame, BluebellFog0x4* p_event)
{
	m_unk0x14 = 1;
	if (p_event) {
		p_event->VTable0x00(p_frame, m_name, this);
	}
}

// FUNCTION: LEGORACERS 0x004055c0
void SaffronQuartz0x2c::Frame0xb8::Event0x20::VTable0x14(Frame0xb8* p_frame, BluebellFog0x4* p_event)
{
	m_unk0x14 = 0;
	if (p_event) {
		p_event->VTable0x04(p_frame, m_name, this);
	}
}

// FUNCTION: LEGORACERS 0x00405890
SaffronQuartz0x2c::Frame0xb8::Frame0xb8()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004058a0
SaffronQuartz0x2c::Frame0xb8::~Frame0xb8()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004058b0
void SaffronQuartz0x2c::Frame0xb8::Reset()
{
	m_unk0x00 = NULL;
	m_unk0x54 = 30;
	m_unk0x58 = 30;
	m_unk0x04 = 0;
	m_unk0x08 = NULL;
	m_unk0x0c = 0;
	m_unk0x10 = NULL;
	m_unk0x14 = 0;
	m_unk0x18 = NULL;
	m_unk0x1c = 0;
	m_unk0x20 = NULL;
	m_unk0x24 = 0;
	m_unk0x28 = NULL;
	m_unk0x2c = 0;
	m_unk0x30 = NULL;
	m_unk0x34 = 0;
	m_unk0x38 = NULL;
	m_unk0x3c = 0;
	m_unk0x40 = NULL;
	m_unk0x44 = 0;
	m_unk0x4c = 0;
	m_unk0x48 = 0;
	m_unk0x50 = 0;
	m_unk0xa4 = 0.0f;
	m_unk0x5c = 0;
	::memset(m_unk0x60, 0, sizeof(m_unk0x60));
	m_unk0x80 = NULL;
	m_unk0x84 = 0;
	::memset(m_unk0x88, 0, sizeof(m_unk0x88));
	m_unk0xa8.m_bottom = 0;
	m_unk0xa8.m_top = 0;
	m_unk0xa8.m_left = 0;
	m_unk0xa8.m_right = 0;
}

// FUNCTION: LEGORACERS 0x004062a0
void SaffronQuartz0x2c::Frame0xb8::Destroy()
{
	if (m_unk0x30) {
		delete[] m_unk0x30;
	}

	if (m_unk0x38) {
		delete[] m_unk0x38;
	}

	if (m_unk0x08) {
		m_unk0x08->VTable0x00(3);
	}

	if (m_unk0x10) {
		m_unk0x10->VTable0x00(3);
	}

	if (m_unk0x18) {
		m_unk0x18->VTable0x00(3);
	}

	if (m_unk0x20) {
		m_unk0x20->VTable0x00(3);
	}

	if (m_unk0x28) {
		m_unk0x28->VTable0x00(3);
	}

	Reset();
}

// FUNCTION: LEGORACERS 0x00406310
void SaffronQuartz0x2c::Frame0xb8::FUN_00406310()
{
	if (m_unk0x44 & c_flagComplete) {
		FUN_00406330();
	}

	m_unk0x44 &= ~c_flagComplete;
	m_unk0x44 |= c_flagPlaying;
}

// FUNCTION: LEGORACERS 0x00406330
void SaffronQuartz0x2c::Frame0xb8::FUN_00406330()
{
	m_unk0x48 = 0;
	m_unk0x50 = 0;
	m_unk0x34 = 0;
	m_unk0x3c = 0;
	m_unk0xa4 = 0.0f;

	while (m_unk0x40) {
		m_unk0x40->VTable0x14(this, m_unk0x00->GetUnk0x0c());
		FUN_004066b0(m_unk0x40);
	}

	m_unk0x44 &= ~(c_flagComplete | c_flagLooped);
}

// FUNCTION: LEGORACERS 0x00406380
void SaffronQuartz0x2c::Frame0xb8::FUN_00406380()
{
	m_unk0x44 &= ~(c_flagPlaying | c_flagComplete | c_flagLooped);
}

// FUNCTION: LEGORACERS 0x00406390
void SaffronQuartz0x2c::Frame0xb8::FUN_00406390(LegoS32 p_elapsedMs)
{
	if (m_unk0x44 & c_flagPlaying) {
		LegoU32 elapsed = m_unk0x50 + p_elapsedMs * m_unk0x58;
		LegoU32 frame = elapsed / 1000;

		if (frame >= m_unk0x4c) {
			FUN_004065d0(m_unk0x48, frame);
			if (m_unk0x44 & c_flagLoop) {
				FUN_00406330();
				frame = 0;
				m_unk0x44 |= c_flagLooped;
				elapsed = 0;
				m_unk0xa4 = 0.0f;
			}
			else {
				m_unk0x44 &= ~(c_flagPlaying | c_flagLooped);
				m_unk0x44 |= c_flagComplete;
				return;
			}
		}
		else {
			m_unk0x44 &= ~(c_flagComplete | c_flagLooped);
		}

		FUN_004065d0(m_unk0x48, frame);

		if (m_unk0x58 == m_unk0x54) {
			m_unk0xa4 = (LegoFloat) ((double) p_elapsedMs + m_unk0xa4);
		}
		else {
			double frameElapsed = (double) (LegoS32) (elapsed - m_unk0x50);
			frameElapsed = frameElapsed / (double) (LegoS32) m_unk0x54;
			m_unk0xa4 = (LegoFloat) (frameElapsed + m_unk0xa4);
		}

		if (m_unk0xa4 >= 1.0f) {
			LegoS32 ticks = (LegoS32) m_unk0xa4;
			FUN_004065a0(ticks);
			m_unk0xa4 = m_unk0xa4 - (LegoFloat) ticks;
		}

		m_unk0x50 = elapsed;
		m_unk0x48 = frame;
	}
}

// FUNCTION: LEGORACERS 0x00406490
void SaffronQuartz0x2c::Frame0xb8::FUN_00406490(Rect* p_rect)
{
	m_unk0xa8 = *p_rect;
	m_unk0x44 |= c_flagHasRect;
}

// FUNCTION: LEGORACERS 0x004064c0
void SaffronQuartz0x2c::Frame0xb8::FUN_004064c0(BronzeFalcon0xc8770* p_renderer, LegoU32 p_lensIndex)
{
	if (m_unk0x5c) {
		LegoU32 lensIndex = p_lensIndex;
		if (p_lensIndex >= m_unk0x5c) {
			lensIndex = m_unk0x5c - 1;
		}

		if (m_unk0x44 & c_flagHasRect) {
			m_unk0x60[lensIndex]->VTable0x0c(&m_unk0xa8);
		}

		p_renderer->VTable0x20(m_unk0x60[lensIndex]);
		p_renderer->VTable0x5c();
		p_renderer->VTable0xec(4);
	}

	p_renderer->VTable0x28();
	if (m_unk0x80 || m_unk0x84) {
		if (m_unk0x80) {
			p_renderer->VTable0x2c(m_unk0x80);
		}

		for (LegoU32 i = 0; i < m_unk0x84; i++) {
			p_renderer->VTable0x30(m_unk0x88[i]);
		}
	}

	for (Event0x20* event3 = m_unk0x40; event3; event3 = event3->m_unk0x1c) {
		event3->VTable0x08(p_renderer);
	}

	for (Event0x20* event4 = m_unk0x40; event4; event4 = event4->m_unk0x1c) {
		event4->VTable0x0c(p_renderer);
	}
}

// FUNCTION: LEGORACERS 0x004065a0
void SaffronQuartz0x2c::Frame0xb8::FUN_004065a0(undefined4 p_unk0x04)
{
	for (Event0x20* event = m_unk0x40; event; event = event->m_unk0x1c) {
		event->VTable0x04(p_unk0x04);
	}
}

// STUB: LEGORACERS 0x004065d0
void SaffronQuartz0x2c::Frame0xb8::FUN_004065d0(LegoU32, LegoU32)
{
	STUB(0x004065d0);
}

// FUNCTION: LEGORACERS 0x00406680
void SaffronQuartz0x2c::Frame0xb8::FUN_00406680(Event0x20* p_event)
{
	p_event->m_unk0x18 = NULL;

	if (m_unk0x40) {
		m_unk0x40->m_unk0x18 = p_event;
		p_event->m_unk0x1c = m_unk0x40;
	}
	else {
		p_event->m_unk0x1c = NULL;
	}

	m_unk0x40 = p_event;
}

// FUNCTION: LEGORACERS 0x004066b0
void SaffronQuartz0x2c::Frame0xb8::FUN_004066b0(Event0x20* p_event)
{
	Event0x20* previous = p_event->m_unk0x18;
	Event0x20* next = p_event->m_unk0x1c;

	if (previous) {
		previous->m_unk0x1c = next;
	}
	else {
		m_unk0x40 = next;
	}

	if (next) {
		next->m_unk0x18 = previous;
	}
}

// FUNCTION: LEGORACERS 0x004066d0
LegoU32 SaffronQuartz0x2c::Frame0xb8::FUN_004066d0(AmberLens0x344* p_lens)
{
	LegoU32 count = m_unk0x5c;
	for (LegoU32 i = 0; i < count; i++) {
		if (m_unk0x60[i] == p_lens) {
			return i;
		}
	}

	m_unk0x5c = count + 1;
	m_unk0x60[count] = p_lens;

	return count;
}

// FUNCTION: LEGORACERS 0x00406710
void SaffronQuartz0x2c::Frame0xb8::FUN_00406710(AmberLens0x344* p_lens)
{
	if (m_unk0x5c) {
		LegoU32 i = 0;
		while (i < m_unk0x5c && m_unk0x60[i] != p_lens) {
			i++;
		}

		while (i < m_unk0x5c - 1) {
			m_unk0x60[i] = m_unk0x60[i + 1];
			i++;
		}

		m_unk0x5c--;
		m_unk0x60[m_unk0x5c] = NULL;
	}
}

// FUNCTION: LEGORACERS 0x00406760
void SaffronQuartz0x2c::Frame0xb8::FUN_00406760(const WhiteFalcon0x140::Field0x124* p_material)
{
	m_unk0x80 = p_material;
}

// FUNCTION: LEGORACERS 0x00406770
void SaffronQuartz0x2c::Frame0xb8::FUN_00406770(const WhiteFalcon0x140::Field0x124* p_material)
{
	if (m_unk0x80 == p_material) {
		m_unk0x80 = NULL;
	}
}

// FUNCTION: LEGORACERS 0x00406790
LegoU32 SaffronQuartz0x2c::Frame0xb8::FUN_00406790(const WhiteFalcon0x140::Field0x124* p_light)
{
	LegoU32 count = m_unk0x84;
	for (LegoU32 i = 0; i < count; i++) {
		if (m_unk0x88[i] == p_light) {
			return i;
		}
	}

	if (count >= sizeOfArray(m_unk0x88)) {
		FUN_004067f0(m_unk0x88[0]);
	}

	m_unk0x88[m_unk0x84] = p_light;
	m_unk0x84++;

	return m_unk0x84;
}

// FUNCTION: LEGORACERS 0x004067f0
void SaffronQuartz0x2c::Frame0xb8::FUN_004067f0(const WhiteFalcon0x140::Field0x124* p_light)
{
	if (m_unk0x84) {
		LegoU32 i = 0;
		while (i < m_unk0x84 && m_unk0x88[i] != p_light) {
			i++;
		}

		while (i < m_unk0x84 - 1) {
			m_unk0x88[i] = m_unk0x88[i + 1];
			i++;
		}

		m_unk0x84--;
		m_unk0x88[m_unk0x84] = NULL;
	}
}

// STUB: LEGORACERS 0x00406860
void SaffronQuartz0x2c::Frame0xb8::FUN_00406860()
{
	STUB(0x00406860);
}

// FUNCTION: LEGORACERS 0x00406890
AmberLens0x344* SaffronQuartz0x2c::Frame0xb8::FUN_00406890()
{
	if (m_unk0x5c) {
		return m_unk0x60[m_unk0x5c - 1];
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x004068a0
SaffronQuartz0x2c::SaffronQuartz0x2c()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00406910
SaffronQuartz0x2c::~SaffronQuartz0x2c()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x00406960
void SaffronQuartz0x2c::Reset()
{
	m_unk0x0c = NULL;
	m_golExport = NULL;
	m_renderer = NULL;
	m_unk0x18 = 0;
	m_unk0x1c = NULL;
	m_unk0x20 = NULL;
	m_frameCount = 0;
	m_frames = NULL;
}

// STUB: LEGORACERS 0x00406980
void SaffronQuartz0x2c::FUN_00406980(GolExport*, BronzeFalcon0xc8770*, const LegoChar*, undefined4)
{
	STUB(0x00406980);
}

// FUNCTION: LEGORACERS 0x00406af0
void SaffronQuartz0x2c::Clear()
{
	if (m_unk0x1c) {
		if (m_golExport) {
			LegoU32 i;
			for (i = 0; i < m_unk0x18; i++) {
				if (m_unk0x1c[i]) {
					m_unk0x1c[i]->VTable0x18();
					m_golExport->VTable0x3c(m_unk0x1c[i]);
				}
			}
		}

		delete[] m_unk0x1c;
	}

	if (m_unk0x20) {
		delete[] m_unk0x20;
	}

	if (m_frames) {
		delete[] m_frames;
	}

	GolNameTable::Clear();
	Reset();
}

// STUB: LEGORACERS 0x00406b90
void SaffronQuartz0x2c::FUN_00406b90(undefined4)
{
	STUB(0x00406b90);
}

// STUB: LEGORACERS 0x00406c50
void SaffronQuartz0x2c::FUN_00406c50(undefined4)
{
	STUB(0x00406c50);
}

// STUB: LEGORACERS 0x00406cb0
void SaffronQuartz0x2c::FUN_00406cb0(undefined4)
{
	STUB(0x00406cb0);
}

// STUB: LEGORACERS 0x00406de0
undefined4 SaffronQuartz0x2c::FUN_00406de0(const LegoChar*)
{
	STUB(0x00406de0);
	return 0;
}

// STUB: LEGORACERS 0x00406e30
undefined4 SaffronQuartz0x2c::FUN_00406e30(const LegoChar*)
{
	STUB(0x00406e30);
	return 0;
}

// STUB: LEGORACERS 0x00406e80
undefined4 SaffronQuartz0x2c::FUN_00406e80(const LegoChar*)
{
	STUB(0x00406e80);
	return 0;
}

// STUB: LEGORACERS 0x00406ed0
undefined4 SaffronQuartz0x2c::FUN_00406ed0(const LegoChar*)
{
	STUB(0x00406ed0);
	return 0;
}

// STUB: LEGORACERS 0x00406f20
undefined4 SaffronQuartz0x2c::FUN_00406f20(LegoU32, undefined4)
{
	STUB(0x00406f20);
	return 0;
}

// STUB: LEGORACERS 0x00406f40
undefined4 SaffronQuartz0x2c::FUN_00406f40(LegoU32, undefined4)
{
	STUB(0x00406f40);
	return 0;
}

// STUB: LEGORACERS 0x00406f60
undefined4 SaffronQuartz0x2c::FUN_00406f60(LegoU32, undefined4, undefined4)
{
	STUB(0x00406f60);
	return 0;
}

// STUB: LEGORACERS 0x00406f90
LegoU32 SaffronQuartz0x2c::FUN_00406f90(LegoFloat)
{
	STUB(0x00406f90);
	return 0;
}
