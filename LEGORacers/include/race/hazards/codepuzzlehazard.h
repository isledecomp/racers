#ifndef CODEPUZZLEHAZARD_H
#define CODEPUZZLEHAZARD_H

#include "golmath.h"
#include "golmodelentity.h"
#include "race/hazards/hazard.h"
#include "race/hazards/hazardcontext.h"

class CutsceneAnimation;
class GolAnimatedEntity;
class GolCollidableEntity;
class MabMaterialTrack;
class MabMaterialFrame;
class SpatialSoundInstance;

struct CutsceneParticleRef;
struct SoundVector;

// VTABLE: LEGORACERS 0x004b447c
// SIZE 0x3c
class CodePuzzleHazard : public Hazard {
public:
	CodePuzzleHazard();
	~CodePuzzleHazard() override;
	void OnActivate(void* p_racer) override;                               // vtable+0x04
	void OnDeactivate(void* p_context) override;                           // vtable+0x08
	void Load(HazardContext* p_context, GolFileParser* p_parser) override; // vtable+0x10
	void Update(undefined4 p_elapsedMs) override;                          // vtable+0x14
	void OnEventStart(LegoS32 p_eventId, void* p_context) override;        // vtable+0x28

	LegoS32 ClearFields();
	LegoS32 Reset();
	void ResetCodeModels();

	// SYNTHETIC: LEGORACERS 0x0048d290
	// CodePuzzleHazard::`scalar deleting destructor'

private:
	enum {
		c_randomTableMask = 0x3ff,
		c_successFirstEvent = 0x12,
		c_successSecondEvent = 0x1c,
		c_goodInputEvent = 0x15,
		c_badInputEvent = 0x1e,
		c_correctCodeEvent = 0x1d,
		c_wrongCodeEvent = 0x14,
		c_firstCodeEvent = 0xc8,
		c_secondCodeEvent = 0xca,
		c_thirdCodeEvent = 0xcc,
		c_delayMs = 2500,
	};

	GolModelEntity* m_codeModel1;       // 0x10
	GolModelEntity* m_codeModel2;       // 0x14
	GolModelEntity* m_codeModel3;       // 0x18
	MabMaterialTrack* m_codeItem1;      // 0x1c
	MabMaterialTrack* m_codeItem2;      // 0x20
	MabMaterialTrack* m_codeItem3;      // 0x24
	MabMaterialFrame* m_materialFrames; // 0x28
	LegoU32 m_materialFrameCount;       // 0x2c
	LegoU8 m_codeEvent1;                // 0x30
	LegoU8 m_codeEvent2;                // 0x31
	LegoU8 m_codeEvent3;                // 0x32
	LegoU8 m_resetEvent1;               // 0x33
	LegoU8 m_resetEvent2;               // 0x34
	LegoU8 m_resetEvent3;               // 0x35
	LegoU8 m_codeProgress;              // 0x36
	LegoU32 m_delayMs;                  // 0x38
};

#endif // CODEPUZZLEHAZARD_H
