#ifndef GOLBOUNDEDENTITY_H
#define GOLBOUNDEDENTITY_H
#include "decomp.h"
#include "golboundingvolume.h"
#include "golorientedentity.h"

class GolModelMaterialTable;
class GolWorldDatabase;

// VTABLE: GOLDP 0x10056bec
// SIZE 0x64
class GolBoundedEntity : public GolOrientedEntity {
public:
	GolBoundedEntity();

	void FUN_1001b760(GolBoundingVolume* p_arg);
	void FUN_00403f80();
	GolBoundingVolume* GetUnk0x58() const { return m_unk0x58; }
	GolModelMaterialTable* GetUnk0x5c() const { return m_unk0x5c; }
	LegoU32 GetUnk0x60() const { return m_unk0x60; }
	void SetUnk0x60(LegoU32 p_unk0x60) { m_unk0x60 = p_unk0x60; }
	GolModelMaterialTable* GetMaterialTable() const
	{
		if (m_unk0x5c != NULL) {
			return m_unk0x5c;
		}

		return m_unk0x58->GetUnk0x18();
	}

protected:
	friend class GolWorldDatabase;

	GolBoundingVolume* m_unk0x58;
	GolModelMaterialTable* m_unk0x5c;
	LegoU32 m_unk0x60;
};

#endif // GOLBOUNDEDENTITY_H
