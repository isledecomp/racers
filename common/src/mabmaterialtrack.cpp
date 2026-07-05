#include "mabmaterialtrack.h"

#include "mabmaterialframe.h"
#include "material/materialtable.h"

#include <stddef.h>

DECOMP_SIZE_ASSERT(MabMaterialTrack, 0x18)

// FUNCTION: GOLDP 0x10025d20
// FUNCTION: LEGORACERS 0x00410350
MabMaterialTrack::MabMaterialTrack()
{
	m_materialTable = NULL;
	m_materialIndex = 0;
	m_firstFrame = 0;
	m_frameCount = 0;
	m_durationFrames = 0;
	m_framesPerMs = 0.0f;
	m_frameCursor = 0.0f;
	m_flags = 0;
}

// FUNCTION: GOLDP 0x10025d40
// FUNCTION: LEGORACERS 0x00410370
void MabMaterialTrack::Configure(undefined2 p_arg1, undefined2 p_arg2, undefined2 p_arg3, LegoS32 p_arg4)
{
	if (m_flags & c_flagConfigured) {
		Reset();
	}

	LegoFloat f = static_cast<LegoFloat>(p_arg4);
	m_firstFrame = p_arg1;
	m_frameCount = p_arg2;
	m_durationFrames = p_arg3;
	m_frameCursor = 0.0f;
	m_framesPerMs = f / 1000.0f;
	m_flags = c_flagConfigured;
}

// FUNCTION: LEGORACERS 0x004103c0
void MabMaterialTrack::ConfigureFrom(const MabMaterialTrack& p_other)
{
	if (m_flags & c_flagConfigured) {
		Reset();
	}

	m_firstFrame = p_other.m_firstFrame;
	m_frameCount = p_other.m_frameCount;
	m_durationFrames = p_other.m_durationFrames;
	m_framesPerMs = p_other.m_framesPerMs;
	m_frameCursor = 0.0f;
	m_flags = c_flagConfigured;
}

// FUNCTION: LEGORACERS 0x00410410
void MabMaterialTrack::Reset()
{
	m_materialTable = NULL;
	m_materialIndex = 0;
	m_firstFrame = 0;
	m_frameCount = 0;
	m_durationFrames = 0;
	m_framesPerMs = 0.0f;
	m_frameCursor = 0.0f;
	m_flags = 0;
}

// FUNCTION: GOLDP 0x10025da0
// FUNCTION: LEGORACERS 0x00410430
void MabMaterialTrack::Assign(MaterialTable* p_arg1, LegoU32 p_arg2, LegoBool32 p_arg3)
{
	m_materialTable = p_arg1;
	m_materialIndex = p_arg2;
	if (p_arg3) {
		m_flags |= c_flagLooping;
	}
	else {
		m_flags &= ~c_flagLooping;
	}
	m_flags |= c_flagAssigned;
}

// FUNCTION: LEGORACERS 0x00410470
void MabMaterialTrack::Unassign()
{
	m_flags &= ~(c_flagAssigned | c_flagLooping);
}

// FUNCTION: LEGORACERS 0x00410480
void MabMaterialTrack::Rewind()
{
	m_frameCursor = 0.0f;
}

// FUNCTION: LEGORACERS 0x00410490
void MabMaterialTrack::SeekToLastFrame()
{
	if (m_durationFrames > 0) {
		m_frameCursor = static_cast<LegoFloat>(m_durationFrames - 1);
	}
	else {
		m_frameCursor = 0.0f;
	}
}

// FUNCTION: LEGORACERS 0x004104c0
void MabMaterialTrack::Update(LegoS32 p_elapsedMs, MabMaterialFrame* p_items, LegoU32)
{
	if (!(m_flags & c_flagAssigned)) {
		return;
	}

	LegoU32 firstFrame = m_firstFrame;
	LegoU32 frameCount = m_frameCount;
	LegoS32 lastFrame = firstFrame + frameCount - 1;

	LegoFloat secondsPerFrame = m_framesPerMs;
	LegoFloat elapsed = static_cast<LegoFloat>(p_elapsedMs);
	m_frameCursor += secondsPerFrame * elapsed;

	LegoU32 frame = static_cast<LegoU32>(m_frameCursor);
	if (!(m_flags & c_flagLooping) && frame >= m_durationFrames) {
		Unassign();
		Rewind();
		return;
	}

	frame %= m_durationFrames;

	LegoS32 i;
	for (i = lastFrame; i >= static_cast<LegoS32>(firstFrame); i--) {
		if (frame >= p_items[i].GetFrame()) {
			break;
		}
	}

	LegoS32 selectedFrame = i;
	if (selectedFrame < static_cast<LegoS32>(firstFrame)) {
		selectedFrame = lastFrame;
	}

	m_materialTable->SetEntry(m_materialIndex, p_items[selectedFrame].GetMaterial());
}

// FUNCTION: LEGORACERS 0x00410560
GolMaterial* MabMaterialTrack::SampleMaterial(LegoS32 p_elapsedMs, MabMaterialFrame* p_items, LegoU32)
{
	LegoFloat secondsPerFrame = m_framesPerMs;
	LegoFloat elapsed = static_cast<LegoFloat>(p_elapsedMs);
	LegoS32 frame = static_cast<LegoS32>(secondsPerFrame * elapsed);
	frame %= m_durationFrames;

	LegoS32 firstFrame = m_firstFrame;
	LegoS32 lastFrame = firstFrame + m_frameCount - 1;
	LegoS32 i;
	for (i = lastFrame; i >= firstFrame; i--) {
		if (static_cast<LegoU32>(frame) >= p_items[i].GetFrame()) {
			break;
		}
	}

	LegoS32 selectedFrame = i;
	if (selectedFrame < firstFrame) {
		selectedFrame = lastFrame;
	}

	return p_items[selectedFrame].GetMaterial();
}
