#include "audio/nullsoundgroup.h"

#include "audio/nullsoundinstance.h"
#include "audio/nullstreamingsoundinstance.h"
#include "audio/soundinstance.h"
#include "audio/streamingsoundinstance.h"
#include "types.h"

DECOMP_SIZE_ASSERT(SoundGroup, 0x10)
DECOMP_SIZE_ASSERT(NullSoundGroup, 0x28)

// GLOBAL: LEGORACERS 0x004afd00
LegoFloat g_defaultNullSoundVolume = 1.0f;

// FUNCTION: LEGORACERS 0x0041c200
NullSoundGroup::NullSoundGroup()
{
	m_soundManager = NULL;
}

// FUNCTION: LEGORACERS 0x0041c240
NullSoundGroup::~NullSoundGroup()
{
	Unload();
}

// FUNCTION: LEGORACERS 0x0041c250
void NullSoundGroup::Load(const LegoChar*)
{
	Unload();
}

// FUNCTION: LEGORACERS 0x0041c260
void NullSoundGroup::Unload()
{
	while (TRUE) {
		GolListLink* link = m_soundInstances.LastLink();

		if (!m_soundInstances.IsValidLastLink(link)) {
			break;
		}

		DestroySoundInstance((SoundInstance*) &m_soundInstances.GetItem(*link));
	}

	while (TRUE) {
		GolListLink* link = m_streamingSoundInstances.LastLink();

		if (!m_streamingSoundInstances.IsValidLastLink(link)) {
			break;
		}

		DestroyStreamingSoundInstance((StreamingSoundInstance*) &m_streamingSoundInstances.GetItem(*link));
	}
}

// FUNCTION: LEGORACERS 0x0041c2a0
SoundInstance* NullSoundGroup::CreateSoundInstance(LegoU32)
{
	NullSoundInstance* sound = new NullSoundInstance();

	if (sound) {
		sound->SetSoundGroup(this);
		m_soundInstances.Append(*sound);
		sound->SetVolume(g_defaultNullSoundVolume);
	}

	return (SoundInstance*) sound;
}

// FUNCTION: LEGORACERS 0x0041c330
void NullSoundGroup::PlaySpatialSound(LegoU32, SoundNode*, LegoFloat, LegoFloat, LegoFloat, LegoFloat)
{
}

// FUNCTION: LEGORACERS 0x0041c340
StreamingSoundInstance* NullSoundGroup::CreateStreamingSoundInstance(LegoU32)
{
	NullStreamingSoundInstance* sound = new NullStreamingSoundInstance();

	if (sound) {
		sound->SetSoundGroup(this);
		m_streamingSoundInstances.Append(*sound);
		sound->SetVolume(g_defaultNullSoundVolume);
	}

	return (StreamingSoundInstance*) sound;
}

// FUNCTION: LEGORACERS 0x0044a1e0 FOLDED
LegoBool32 NullSoundGroup::IsLoaded()
{
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0044e7e0 FOLDED
LegoU32 NullSoundGroup::GetSoundCount()
{
	return 0;
}

// FUNCTION: LEGORACERS 0x0041b2d0 FOLDED
void NullSoundGroup::DestroySoundInstance(SoundInstance* p_sound)
{
	p_sound->SetSoundGroup(NULL);
	p_sound->Remove();
	delete p_sound;
}

// FUNCTION: LEGORACERS 0x0041b470 FOLDED
void NullSoundGroup::DestroyStreamingSoundInstance(StreamingSoundInstance* p_sound)
{
	p_sound->SetSoundGroup(NULL);
	p_sound->Remove();
	delete p_sound;
}

// FUNCTION: LEGORACERS 0x0041b4a0 FOLDED
SoundManager* NullSoundGroup::GetSoundManager()
{
	return m_soundManager;
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void NullSoundGroup::PlaySoundByIndex(LegoU32)
{
}
