#include "scene/golbillboard.h"

// VTABLE: GOLDP 0x10056760
// SIZE 0x4c
class GolBillboardEx : public GolBillboard {
public:
	void Configure(
		GolMaterial* p_position,
		LegoFloat p_width,
		LegoFloat p_height,
		LegoFloat p_maxDistanceSquared
	) override;
};
