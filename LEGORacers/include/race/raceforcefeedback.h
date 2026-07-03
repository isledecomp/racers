#ifndef RACEFORCEFEEDBACK_H
#define RACEFORCEFEEDBACK_H

#include "decomp.h"
#include "types.h"

#include <dinput.h>

class DirectInputDevice;

// SIZE 0x28
class RaceForceFeedback {
public:
	RaceForceFeedback();
	~RaceForceFeedback();

	void Initialize(DirectInputDevice* p_device);
	void SetSurfaceIntensity(LegoFloat p_intensity);
	void PlayTurboRumble(LegoU32 p_level);
	void PlayReactionRumble();
	void PlayLightRumble();
	void PlayScrapeRumble();
	void StartEngineEffect();
	void StopEngineEffect();
	void Pause();
	void Resume();

private:
	void Destroy();
	void Update(LegoU32 p_elapsedMs, LegoFloat p_forwardSpeed);
	void Stop();
	void StartPulses();
	LegoS32 StartSurfaceRumble();
	LegoS32 UpdateSurfacePulse(LegoFloat p_forwardSpeed);
	void CreateEngineEffect();
	undefined4 UpdateEngineEffect(LegoFloat p_forwardSpeed);

	DirectInputDevice* m_device;        // 0x00
	LegoU32 m_totalMs;                  // 0x04
	LegoU32 m_phaseMs;                  // 0x08
	LegoS32 m_onMs;                     // 0x0c
	LegoU32 m_offMs;                    // 0x10
	LegoFloat m_surfaceIntensity;       // 0x14
	LegoU32 m_state;                    // 0x18
	LegoU32 m_surfaceMode;              // 0x1c
	LegoU32 m_engineEffectActive;       // 0x20
	LPDIRECTINPUTEFFECT m_engineEffect; // 0x24

	friend class RaceSession;
};

#endif // RACEFORCEFEEDBACK_H
