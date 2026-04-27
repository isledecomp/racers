#include "audio/soundinstance.h"

#include "audio/directsoundgroup.h"
#include "audio/soundbuffer.h"
#include "audio/soundmanager.h"

DECOMP_SIZE_ASSERT(SoundInstance, 0x14)

// FUNCTION: LEGORACERS 0x0041b4b0
SoundInstance::SoundInstance()
{
	m_soundGroup = NULL;
	m_soundBuffer = NULL;
}

// FUNCTION: LEGORACERS 0x0041b4f0
SoundInstance::~SoundInstance()
{
	if (m_soundBuffer) {
		m_soundBuffer->ClearSoundInstance();

		if (m_soundBuffer) {
			delete m_soundBuffer;
		}
	}

	if (m_soundGroup) {
		Remove();
	}
}

// FUNCTION: LEGORACERS 0x0041b530
LegoBool32 SoundInstance::Play(LegoBool32 p_loop)
{
	return m_soundBuffer->Play(p_loop);
}

// FUNCTION: LEGORACERS 0x0041b540
void SoundInstance::Stop()
{
	m_soundBuffer->StopOrRelease();
}

// FUNCTION: LEGORACERS 0x0041b550
LegoBool32 SoundInstance::IsPlaying()
{
	if (m_soundBuffer) {
		return m_soundBuffer->IsPlaying();
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x0041b560
void SoundInstance::SetVolume(LegoFloat p_volume)
{
	SoundManager* soundManager = GetSoundGroup()->GetSoundManager();
	m_soundBuffer->SetVolume(soundManager->GetVolumeScale() * p_volume);
}

// FUNCTION: LEGORACERS 0x0041b590
void SoundInstance::SetPan(LegoFloat p_pan)
{
	m_soundBuffer->SetPan(p_pan);
}

// FUNCTION: LEGORACERS 0x0041b5a0
void SoundInstance::SetFrequencyScale(LegoFloat p_scale)
{
	m_soundBuffer->SetFrequencyScale(p_scale);
}

// FUNCTION: LEGORACERS 0x0041b5b0
void SoundInstance::SetPriority(LegoS32 p_priority)
{
	m_soundBuffer->SetPriority(p_priority);
}

// TODO: Match the original fold group for sound-instance getters.
#pragma code_seg(".text$soundinstance_getsoundGroup")
// FUNCTION: LEGORACERS 0x0041b5c0 FOLDED
DirectSoundGroup* SoundInstance::GetSoundGroup()
{
	return m_soundGroup;
}
#pragma code_seg()
