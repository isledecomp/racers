#ifndef SOUNDRESOURCE_H
#define SOUNDRESOURCE_H

#include "audio/soundnode.h"
#include "race/events/raceeventresource.h"
#include "race/raceresourcemanager.h"

class GolModelEntity;
class RacerSoundSource;
class SpatialSoundInstance;

// VTABLE: LEGORACERS 0x004b1c84
// SIZE 0x5c
class SoundResource : public RaceEventResource {
public:
	enum {
		e_unknown0x2e = 0x2e,
	};

	// .evb sound field tokens
	enum {
		e_soundId = 0x2c,
		e_volume = 0x2f,
		e_frequencyScale = 0x30,
		e_minDistance = 0x31,
		e_maxDistance = 0x32,
		e_position = 0x3b,
		e_probability = 0x40,
	};

	enum {
		c_flagLooping = 1 << 0,
		c_flagAtEventPosition = 1 << 3,
		c_randomTableMask = 0x3ff,
		c_randomDelayBaseMs = 500,
		c_randomDelayRangeMs = 1000,
		c_probabilityMax = 0xff
	};

	// SIZE 0x4c
	struct InitParams {
		LegoU32 m_eventId;               // 0x00
		undefined4 m_unk0x04;            // 0x04
		RacerSoundSource* m_soundSource; // 0x08
		GolVec3 m_position;              // 0x0c
		LegoU32 m_soundId;               // 0x18
		LegoU32 m_unk0x1c;               // 0x1c
		LegoFloat m_volume;              // 0x20
		LegoFloat m_frequencyScale;      // 0x24
		LegoFloat m_minDistance;         // 0x28
		LegoFloat m_maxDistance;         // 0x2c
		LegoFloat m_probability;         // 0x30
		LegoBool32 m_looping;            // 0x34
		LegoBool32 m_noEnd;              // 0x38
		LegoBool32 m_triggerOnEnd;       // 0x3c
		LegoBool32 m_positional;         // 0x40
		GolModelEntity* m_entity;        // 0x44
		LegoU32 m_nodeIndex;             // 0x48
	};

	SoundResource();
	~SoundResource() override;
	void OnStartAt(GolVec3* p_position) override;
	void OnEnd() override;
	void Update(LegoU32 p_elapsedMs) override;
	virtual LegoU32 GetKind(); // vtable+0x18

	void Initialize(InitParams* p_params);
	void Destroy();
	void StopSound();

	// SYNTHETIC: LEGORACERS 0x0045f600
	// SoundResource::`vector deleting destructor'

private:
	SpatialSoundInstance* m_sound;    // 0x20
	RacerSoundSource* m_soundSource;  // 0x24
	GolModelEntity* m_trackedEntity;  // 0x28
	LegoU32 m_nodeIndex;              // 0x2c
	SoundVector m_position;           // 0x30
	LegoU32 m_soundId;                // 0x3c
	LegoU32 m_unk0x40;                // 0x40
	LegoFloat m_volume;               // 0x44
	LegoFloat m_frequencyScale;       // 0x48
	LegoFloat m_minDistance;          // 0x4c
	LegoFloat m_maxDistance;          // 0x50
	LegoU8 m_probability;             // 0x54
	undefined m_unk0x55[0x58 - 0x55]; // 0x55
	LegoU32 m_retriggerDelayMs;       // 0x58
};

#endif // SOUNDRESOURCE_H
