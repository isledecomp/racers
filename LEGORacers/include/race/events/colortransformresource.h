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
		LegoU32 m_eventId;               // 0x00
		LegoS32 m_stateEventIds[3];      // 0x04
		RaceEventTable* m_eventTable;    // 0x10
		LegoU32 m_flags;                 // 0x14
		ColorTransform m_colorTransform; // 0x18
		GolWorldEntity* m_worldEntity;   // 0x38
	};

	// .evb color-transform field tokens
	enum {
		e_shifts = 0x4e,
		e_offsets = 0x4f,
		e_clearTransform = 0x50,
	};

	ColorTransformResource();
	~ColorTransformResource() override;
	void OnStartForRacer(Racer* p_racer) override;
	void OnEndForRacer(Racer* p_racer) override;
	virtual LegoU32 GetKind(); // vtable+0x18

	void ClearFields();
	void Initialize(InitParams* p_params);
	void Destroy();

	// SYNTHETIC: LEGORACERS 0x00460a70
	// ColorTransformResource::`vector deleting destructor'

private:

public:
	enum {
		c_clearTransform = 1 << 1, // OnStart clears the active transform instead of applying one
	};

private:
	LegoU32 m_transformFlags;        // 0x20
	ColorTransform m_colorTransform; // 0x24
	GolWorldEntity* m_worldEntity;   // 0x44
};

#endif // COLORTRANSFORMRESOURCE_H
