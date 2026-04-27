#include "audio/directsoundconversions.h"

#include "audio/soundbuffer.h"
#include "gollist.h"

#include <dsound.h>

// GLOBAL: LEGORACERS 0x004afaec
LegoFloat g_minSoundPan = -1.0f;

// GLOBAL: LEGORACERS 0x004afb28
LegoFloat g_directSoundVolumeScale = -3000.0f;

// GLOBAL: LEGORACERS 0x004afb2c
LegoFloat g_minAudibleSoundVolume = 0.005f;

// GLOBAL: LEGORACERS 0x004afb30
LegoFloat g_directSoundPanScale = 2500.0f;

// FUNCTION: LEGORACERS 0x00419650
LegoS32 ConvertVolumeToDirectSound(LegoFloat p_volume)
{
	if (p_volume < g_minAudibleSoundVolume) {
		return DSBVOLUME_MIN;
	}

	LegoFloat scaledVolume = p_volume;
	scaledVolume *= g_directSoundVolumeScale;
	return -3000 - (LegoS32) scaledVolume;
}

// FUNCTION: LEGORACERS 0x00419680
LegoS32 ConvertPanToDirectSound(LegoFloat p_pan)
{
	if (p_pan == 1.0f) {
		return DSBPAN_RIGHT;
	}

	if (p_pan == g_minSoundPan) {
		return DSBPAN_LEFT;
	}

	LegoFloat scaledPan = p_pan;
	scaledPan *= g_directSoundPanScale;
	return (LegoS32) scaledPan;
}

// FUNCTION: LEGORACERS 0x004196c0
GolListLink* GolListLink::InsertBefore(GolListLink* p_link)
{
	m_next = p_link;
	m_prev = p_link->m_prev;
	p_link->m_prev->m_next = this;
	p_link->m_prev = this;
	return p_link;
}

// FUNCTION: LEGORACERS 0x004196e0
GolListLink* GolListLink::NextValid()
{
	if (m_next->m_next) {
		return m_next;
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x004196f0
template <>
GolListLink* SoundBufferList::FirstValidLink()
{
	GolListLink* link = FirstLink();
	if (link->m_next) {
		return link;
	}

	return NULL;
}
