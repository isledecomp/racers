#include "mabmaterialanimationitem0x18.h"

#include "mabmaterialanimationitem0x8.h"

DECOMP_SIZE_ASSERT(MabMaterialAnimationItem0x18, 0x18)

// FUNCTION: GOLDP 0x10025d20
// FUNCTION: LEGORACERS 0x00410350
MabMaterialAnimationItem0x18::MabMaterialAnimationItem0x18()
{
	m_unk0x00 = NULL;
	m_unk0x04 = 0;
	m_unk0x06 = 0;
	m_unk0x08 = 0;
	m_unk0x0a = 0;
	m_unk0x0c = 0.0f;
	m_unk0x10 = 0.0f;
	m_flags = 0;
}

// FUNCTION: GOLDP 0x10025d40
// FUNCTION: LEGORACERS 0x00410370
void MabMaterialAnimationItem0x18::FUN_10025d40(undefined2 p_arg1, undefined2 p_arg2, undefined2 p_arg3, LegoS32 p_arg4)
{
	if (m_flags & c_flagBit0) {
		Reset();
	}

	LegoFloat f = static_cast<LegoFloat>(p_arg4);
	m_unk0x06 = p_arg1;
	m_unk0x08 = p_arg2;
	m_unk0x0a = p_arg3;
	m_unk0x10 = 0.0f;
	m_unk0x0c = f / 1000.0f;
	m_flags = c_flagBit0;
}

// FUNCTION: LEGORACERS 0x004103c0
void MabMaterialAnimationItem0x18::FUN_004103c0(const MabMaterialAnimationItem0x18& p_other)
{
	if (m_flags & c_flagBit0) {
		Reset();
	}

	m_unk0x06 = p_other.m_unk0x06;
	m_unk0x08 = p_other.m_unk0x08;
	m_unk0x0a = p_other.m_unk0x0a;
	m_unk0x0c = p_other.m_unk0x0c;
	m_unk0x10 = 0.0f;
	m_flags = c_flagBit0;
}

// FUNCTION: LEGORACERS 0x00410410
void MabMaterialAnimationItem0x18::Reset()
{
	m_unk0x00 = NULL;
	m_unk0x04 = 0;
	m_unk0x06 = 0;
	m_unk0x08 = 0;
	m_unk0x0a = 0;
	m_unk0x0c = 0.0f;
	m_unk0x10 = 0.0f;
	m_flags = 0;
}

// FUNCTION: GOLDP 0x10025da0
// FUNCTION: LEGORACERS 0x00410430
void MabMaterialAnimationItem0x18::FUN_10025da0(FloatyPontoon0x4c::Field0x2c* p_arg1, LegoU32 p_arg2, LegoBool32 p_arg3)
{
	m_unk0x00 = p_arg1;
	m_unk0x04 = p_arg2;
	if (p_arg3) {
		m_flags |= c_flagBit2;
	}
	else {
		m_flags &= ~c_flagBit2;
	}
	m_flags |= c_flagBit1;
}

// FUNCTION: LEGORACERS 0x00410470
void MabMaterialAnimationItem0x18::FUN_00410470()
{
	m_flags &= ~(c_flagBit1 | c_flagBit2);
}

// FUNCTION: LEGORACERS 0x00410480
void MabMaterialAnimationItem0x18::FUN_00410480()
{
	m_unk0x10 = 0.0f;
}

// FUNCTION: LEGORACERS 0x00410490
void MabMaterialAnimationItem0x18::FUN_00410490()
{
	if (m_unk0x0a > 0) {
		m_unk0x10 = static_cast<LegoFloat>(m_unk0x0a - 1);
	}
	else {
		m_unk0x10 = 0.0f;
	}
}

// FUNCTION: LEGORACERS 0x004104c0
void MabMaterialAnimationItem0x18::FUN_004104c0(LegoS32 p_elapsedMs, MabMaterialAnimationItem0x8* p_items, LegoU32)
{
	if (!(m_flags & c_flagBit1)) {
		return;
	}

	LegoU32 firstFrame = m_unk0x06;
	LegoU32 frameCount = m_unk0x08;
	LegoS32 lastFrame = firstFrame + frameCount - 1;

	LegoFloat secondsPerFrame = m_unk0x0c;
	LegoFloat elapsed = static_cast<LegoFloat>(p_elapsedMs);
	m_unk0x10 += secondsPerFrame * elapsed;

	LegoU32 frame = static_cast<LegoU32>(m_unk0x10);
	if (!(m_flags & c_flagBit2) && frame >= m_unk0x0a) {
		FUN_00410470();
		FUN_00410480();
		return;
	}

	frame %= m_unk0x0a;

	LegoS32 selectedFrame = lastFrame;
	if (lastFrame >= static_cast<LegoS32>(firstFrame)) {
		MabMaterialAnimationItem0x8* item = &p_items[selectedFrame];
		for (; selectedFrame >= static_cast<LegoS32>(firstFrame); selectedFrame--, item--) {
			if (frame >= item->GetFrame()) {
				break;
			}
		}
	}

	if (selectedFrame < static_cast<LegoS32>(firstFrame)) {
		selectedFrame = lastFrame;
	}

	m_unk0x00->SetPosition(m_unk0x04, p_items[selectedFrame].GetMaterial());
}

// FUNCTION: LEGORACERS 0x00410560
DuskwindBananaRelic0x24* MabMaterialAnimationItem0x18::FUN_00410560(
	LegoS32 p_elapsedMs,
	MabMaterialAnimationItem0x8* p_items,
	LegoU32
)
{
	LegoFloat secondsPerFrame = m_unk0x0c;
	LegoFloat elapsed = static_cast<LegoFloat>(p_elapsedMs);
	LegoS32 frame = static_cast<LegoS32>(secondsPerFrame * elapsed);
	frame %= m_unk0x0a;

	LegoS32 firstFrame = m_unk0x06;
	LegoS32 lastFrame = firstFrame + m_unk0x08 - 1;
	LegoS32 selectedFrame = lastFrame;
	if (selectedFrame >= firstFrame) {
		MabMaterialAnimationItem0x8* item = &p_items[selectedFrame];
		for (; selectedFrame >= firstFrame; selectedFrame--, item--) {
			if (static_cast<LegoU32>(frame) >= item->GetFrame()) {
				break;
			}
		}
	}

	if (selectedFrame < firstFrame) {
		return p_items[lastFrame].GetMaterial();
	}

	return p_items[selectedFrame].GetMaterial();
}
