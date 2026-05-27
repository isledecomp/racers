#ifndef GOLWDBBOUNDEDENTITY_H
#define GOLWDBBOUNDEDENTITY_H
#include "decomp.h"
#include "golwdborientedentity.h"

class GolBvbBoundingVolume;
class GolGdbMaterialList;
class GolWdbDatabase;

// VTABLE: GOLDP 0x10056bec
// SIZE 0x64
class GolWdbBoundedEntity : public GolWdbOrientedEntity {
public:
	GolWdbBoundedEntity();

	void FUN_1001b760(GolBvbBoundingVolume* p_arg);

protected:
	friend class GolWdbDatabase;

	GolBvbBoundingVolume* m_unk0x58;
	GolGdbMaterialList* m_unk0x5c;
	undefined4 m_unk0x60;
};

#endif // GOLWDBBOUNDEDENTITY_H
