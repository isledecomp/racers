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

	void SetBoundingVolume(GolBoundingVolume* p_boundingVolume);
	void MirrorY();
	GolBoundingVolume* GetBoundingVolume() const { return m_boundingVolume; }
	GolModelMaterialTable* GetMaterialTableOverride() const { return m_materialTableOverride; }
	LegoU32 GetBoundedFlags() const { return m_boundedFlags; }
	void SetBoundedFlags(LegoU32 p_boundedFlags) { m_boundedFlags = p_boundedFlags; }
	GolModelMaterialTable* GetMaterialTable() const
	{
		if (m_materialTableOverride != NULL) {
			return m_materialTableOverride;
		}

		return m_boundingVolume->GetMaterialTable();
	}

protected:
	friend class GolWorldDatabase;

	GolBoundingVolume* m_boundingVolume;            // 0x58
	GolModelMaterialTable* m_materialTableOverride; // 0x5c
	LegoU32 m_boundedFlags;                         // 0x60
};

#endif // GOLBOUNDEDENTITY_H
