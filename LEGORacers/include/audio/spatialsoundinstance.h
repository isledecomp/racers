#ifndef SPATIALSOUNDINSTANCE_H
#define SPATIALSOUNDINSTANCE_H

#include "audio/soundnode.h"
#include "compat.h"
#include "decomp.h"
#include "types.h"

class DirectSoundGroup;

// VTABLE: LEGORACERS 0x004afad0
// SIZE 0x38
class SpatialSoundInstance {
public:
	SpatialSoundInstance();
	virtual ~SpatialSoundInstance();           // vtable+0x00
	virtual void Play(LegoBool32 p_loop);      // vtable+0x04
	virtual void Stop();                       // vtable+0x08
	virtual LegoBool32 IsPlaying();            // vtable+0x0c
	virtual DirectSoundGroup* GetSoundGroup(); // vtable+0x10
	virtual void VTable0x14(undefined4);       // vtable+0x14
	virtual void UpdateSpatial(SoundNode*);    // vtable+0x18

	void SetVolume(LegoFloat p_volume);

	// SYNTHETIC: LEGORACERS 0x00417c50
	// SpatialSoundInstance::`scalar deleting destructor'

protected:
	friend class DirectSoundGroup;

	void UpdateSpatialFromOrigin();
	void UpdateSpatialFromNode(SoundNode* p_node);

	LegoFloat m_volume;                // 0x04
	LegoFloat m_frequencyScale;        // 0x08
	LegoFloat m_spatialVolume;         // 0x0c
	LegoFloat m_spatialPan;            // 0x10
	LegoFloat m_spatialFrequencyScale; // 0x14
	SoundVector m_position;            // 0x18
	SoundVector m_velocity;            // 0x24
	LegoFloat m_minDistanceSquared;    // 0x30
	LegoFloat m_maxDistanceSquared;    // 0x34
};

#endif // SPATIALSOUNDINSTANCE_H
