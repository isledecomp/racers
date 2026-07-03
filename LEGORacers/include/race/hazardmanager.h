#ifndef RACEEVENTDISPATCHER0X08_H
#define RACEEVENTDISPATCHER0X08_H

#include "decomp.h"
#include "golmath.h"
#include "golmodelentity.h"
#include "golname.h"
#include "golworldentity.h"
#include "material/materialtable0x0c.h"
#include "race/hazards/cannonballrainhazard.h"
#include "race/hazards/codepuzzlehazard.h"
#include "race/hazards/colliderrecord.h"
#include "race/hazards/cursedrophazard.h"
#include "race/hazards/fallingpillarhazard.h"
#include "race/hazards/ghosthazard.h"
#include "race/hazards/grabberhazard.h"
#include "race/hazards/hammerhazard.h"
#include "race/hazards/hazard.h"
#include "race/hazards/hazardcontext.h"
#include "race/hazards/launcherhazard.h"
#include "race/hazards/lavageyserhazard.h"
#include "race/hazards/movingobstaclehazard.h"
#include "race/hazards/multilauncherhazard.h"
#include "race/hazards/oscillatorhazard.h"
#include "race/hazards/rockethazard.h"
#include "race/hazards/rollingrockhazard.h"
#include "race/hazards/smokeventhazard.h"
#include "race/hazards/snowfallhazard.h"
#include "race/hazards/sphinxhazard.h"
#include "race/hazards/sweepcannonhazard.h"
#include "race/hazards/triggeredanimationhazard.h"
#include "race/hazards/warppadhazard.h"
#include "race/powerups/powerupprojectile.h"
#include "race/raceactionsource.h"
#include "race/racedecalmanager.h"
#include "race/racestate.h"
#include "types.h"
#include "util/legoeventqueue.h"

class GolCamera;
class GolD3DRenderDevice;
class GolFileParser;
class GolAnimatedEntity;
class GolBillboard;
class GolCollidableEntity;
class GolExport;
class GolModelEntity;
class GolNameTable;
class GolWorldDatabase;
struct CutsceneParticleRef;
class CutsceneAnimation;
class MabMaterialAnimationItem0x8;
class MabMaterialAnimationItem0x18;
class RaceEventTable;
class RacePowerupManager;
class RaceSession;
class TriggerWorld;
class SpatialSoundInstance;

// SIZE 0x08
class HazardManager {
public:
	// VTABLE: LEGORACERS 0x004b40f8
	// SIZE 0x1fc
	class HzbTxtParser : public GolTxtParser {};

	HazardManager();
	~HazardManager();

	void NotifyEventStart(LegoS32 p_unk0x04, void* p_unk0x08);
	void NotifyEventEnd(LegoS32 p_unk0x04, void* p_unk0x08);
	void ForceActivate(LegoS32 p_unk0x04);
	void NotifyEventPair(LegoS32 p_unk0x04, LegoS32 p_unk0x08, void* p_unk0x0c);
	void DispatchEventStart(LegoS32 p_unk0x04, void* p_context);
	void DispatchEventEnd(LegoS32 p_unk0x04, void* p_context);
	void DispatchEventPair(LegoS32 p_unk0x04, LegoS32 p_unk0x08, void* p_context);
	void Update(undefined4 p_unk0x04);
	void UpdatePerRacer(GolCamera* p_unk0x04, Racer* p_unk0x08);
	void Draw(GolD3DRenderDevice* p_renderer);
	void ResetAll();

private:
	friend class RaceSession;

	void Destroy();
	void LoadHazards(void* p_unk0x04, const LegoChar* p_name, LegoBool32 p_binary);

	LegoU32 m_count;    // 0x00
	Hazard** m_entries; // 0x04
};

#endif
