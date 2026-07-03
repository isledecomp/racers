#ifndef HAZARDMANAGER_H
#define HAZARDMANAGER_H

#include "decomp.h"
#include "goltxtparser.h"
#include "types.h"

class GolCamera;
class GolD3DRenderDevice;
class Hazard;
class Racer;

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

#endif // HAZARDMANAGER_H
