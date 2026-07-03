#ifndef COLORTRANSFORMRESOURCE_H
#define COLORTRANSFORMRESOURCE_H

#include "gdbvertexarray.h"
#include "race/events/raceeventresource.h"

class GolWorldEntity;

// VTABLE: LEGORACERS 0x004b1de0
// SIZE 0x48
class ColorTransformResource : public RaceEventResource {
public:
	// SIZE 0x3c
	struct InitParams {
		undefined4 m_unk0x00;         // 0x00
		LegoS32 m_stateEventIds[3];   // 0x04
		RaceEventTable* m_eventTable; // 0x10
		LegoU32 m_flags0x14;          // 0x14
		ColorTransform m_unk0x18;     // 0x18
		GolWorldEntity* m_unk0x38;    // 0x38
	};

	ColorTransformResource();
	~ColorTransformResource() override;
	void OnStartForRacer(Racer* p_racer) override;
	void OnEndForRacer(Racer* p_racer) override;
	virtual LegoU32 GetKind(); // vtable+0x18

	void FUN_00465560();
	void FUN_00465570(InitParams* p_params);
	void FUN_004655e0();

	// SYNTHETIC: LEGORACERS 0x00460a70
	// ColorTransformResource::`vector deleting destructor'

private:
	enum {
		c_flags0x20Bit1 = 1 << 1,
	};

	LegoU32 m_flags0x20;             // 0x20
	ColorTransform m_colorTransform; // 0x24
	GolWorldEntity* m_unk0x44;       // 0x44
};

#endif // COLORTRANSFORMRESOURCE_H
