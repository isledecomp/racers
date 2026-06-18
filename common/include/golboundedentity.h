#ifndef GOLBOUNDEDENTITY_H
#define GOLBOUNDEDENTITY_H
#include "decomp.h"
#include "golorientedentity.h"

class GolBoundingVolume;
class GolModelMaterialTable;
class GolWorldDatabase;

// VTABLE: GOLDP 0x10056bec
// SIZE 0x64
class GolBoundedEntity : public GolOrientedEntity {
public:
	GolBoundedEntity();

	void FUN_1001b760(GolBoundingVolume* p_arg);
	void FUN_00403f80();

protected:
	friend class GolWorldDatabase;

	GolBoundingVolume* m_unk0x58;
	GolModelMaterialTable* m_unk0x5c;
	undefined4 m_unk0x60;
};

#endif // GOLBOUNDEDENTITY_H
