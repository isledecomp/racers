#ifndef RACESETUP_H
#define RACESETUP_H

#include "race/racer/racer.h"

class GolMaterialLibrary;
class GolTextureList;

// SIZE 0x1c
class RaceSetup {
public:
	RaceSetup();
	~RaceSetup();

private:
	friend class RaceState;

	enum {
		c_rubberBandFlags = Racer::c_flagMagnetHeld | Racer::c_flagGrabbed,
	};

	void Reset();
	void Destroy();
	void Initialize(Racer* p_racers, LegoU32 p_racerCount);
	LegoU32 Update(LegoU32 p_elapsedMs);

	Racer* m_racers;                       // 0x00
	LegoU32 m_racerCount;                  // 0x04
	LegoU32 m_updateDelayMs;               // 0x08
	LegoFloat m_rubberBandBoost;           // 0x0c
	GolTextureList* m_textureList;         // 0x10
	GolMaterialLibrary* m_materialLibrary; // 0x14
	LegoU8 m_lapCount;                     // 0x18
	undefined m_unk0x19[0x1c - 0x19];      // 0x19
};

#endif // RACESETUP_H
