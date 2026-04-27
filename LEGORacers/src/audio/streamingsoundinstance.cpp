#include "audio/streamingsoundinstance.h"

#include "audio/directsoundgroup.h"
#include "audio/soundbuffer.h"

DECOMP_SIZE_ASSERT(StreamingSoundInstance, 0x48)

// GLOBAL: LEGORACERS 0x004afc00
LegoFloat g_streamingSoundPriorityScale = 2048.0f;

// FUNCTION: LEGORACERS 0x0041acb0
StreamingSoundInstance::StreamingSoundInstance()
{
	m_soundGroup = NULL;
}

// FUNCTION: LEGORACERS 0x0041ad00
StreamingSoundInstance::~StreamingSoundInstance()
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

// FUNCTION: LEGORACERS 0x0041ad80
void StreamingSoundInstance::Play(LegoBool32 p_loop)
{
	m_soundBuffer->Play(p_loop);
}

// FUNCTION: LEGORACERS 0x0041ad90
void StreamingSoundInstance::Stop()
{
	m_soundBuffer->StopOrRelease();
}

// FUNCTION: LEGORACERS 0x0041ada0
LegoBool32 StreamingSoundInstance::IsPlaying()
{
	if (m_soundBuffer) {
		return m_soundBuffer->IsPlaying();
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x0041adb0
void StreamingSoundInstance::UpdateSpatial(SoundNode* p_node)
{
	SpatialSoundInstance::UpdateSpatial(p_node);
	m_soundBuffer->SetVolume(m_spatialVolume);
	m_soundBuffer->SetPan(m_spatialPan);
	m_soundBuffer->SetFrequencyScale(m_spatialFrequencyScale);
	m_soundBuffer->SetPriority((LegoS32) (m_soundBuffer->GetVolume() * g_streamingSoundPriorityScale));
}

// FUNCTION: LEGORACERS 0x0041ae00 FOLDED
DirectSoundGroup* StreamingSoundInstance::GetSoundGroup()
{
	return m_soundGroup;
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void StreamingSoundInstance::VTable0x14(undefined4)
{
}
