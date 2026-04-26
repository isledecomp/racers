#ifndef SPATIALSOUNDINSTANCE_H
#define SPATIALSOUNDINSTANCE_H

#include "compat.h"
#include "decomp.h"
#include "types.h"

struct SoundNode;
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

	// SYNTHETIC: LEGORACERS 0x00417c50
	// SpatialSoundInstance::`scalar deleting destructor'

protected:
	LegoFloat m_volume;                // 0x04
	LegoFloat m_frequencyScale;        // 0x08
	LegoFloat m_spatialVolume;         // 0x0c
	LegoFloat m_spatialPan;            // 0x10
	LegoFloat m_spatialFrequencyScale; // 0x14
	LegoFloat m_positionX;             // 0x18
	LegoFloat m_positionY;             // 0x1c
	LegoFloat m_positionZ;             // 0x20
	LegoFloat m_velocityX;             // 0x24
	LegoFloat m_velocityY;             // 0x28
	LegoFloat m_velocityZ;             // 0x2c
	LegoFloat m_minDistanceSquared;    // 0x30
	LegoFloat m_maxDistanceSquared;    // 0x34
};

#endif // SPATIALSOUNDINSTANCE_H
