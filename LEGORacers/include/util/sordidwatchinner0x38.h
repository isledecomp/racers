#ifndef SORDIDWATCHINNER0x38_H
#define SORDIDWATCHINNER0x38_H

#include "decomp.h"
#include "golmodelentity.h"
#include "types.h"

class DuskwindBananaRelic0x24;

// VTABLE: LEGORACERS 0x004af8c0
class SordidWatchInner0x38 : public GolWorldEntity {
public:
	SordidWatchInner0x38();

	void FUN_00414600(LegoFloat p_param1, GolVec3* p_param2);

	LegoU32 m_unk0x28;                  // 0x28
	undefined4 m_unk0x2c;               // 0x2c
	DuskwindBananaRelic0x24* m_unk0x30; // 0x30
	SordidWatchInner0x38* m_next;       // 0x34
};

#endif // SORDIDWATCHINNER0x38_H
