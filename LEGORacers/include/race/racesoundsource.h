#ifndef RACESOUNDSOURCE_H
#define RACESOUNDSOURCE_H

#include "race/racer/racersoundsource.h"

class RaceSession;
class SoundManager;

// SIZE 0x14
class RaceSoundSource : public RacerSoundSource {
public:
	RaceSoundSource();
	~RaceSoundSource();
	void DestroyGroups();
	void Initialize(SoundManager* p_soundManager);
	void LoadSfxBank(const LegoChar* p_name);
	void LoadVoiceBanks(const LegoChar* p_name1, const LegoChar* p_name2);
	void LoadAmbientBank(const LegoChar* p_name);
};

#endif // RACESOUNDSOURCE_H
