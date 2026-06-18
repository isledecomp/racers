#ifndef GOLCOLLIDABLEENTITY_H
#define GOLCOLLIDABLEENTITY_H

#include "compat.h"
#include "decomp.h"
#include "golmodelentity.h"

class GolRenderDevice;
class GolBoundingShape;
class GolModelBase;

// VTABLE: GOLDP 0x10056b04
// SIZE 0x9c
class GolCollidableEntity : public GolModelEntity {
public:
	GolCollidableEntity();

	void VTable0x1c(GolRenderDevice&) override; // vtable+0x1c
	void VTable0x54() override;                 // vtable+0x54
	virtual void VTable0x60(GolModelBase* p_model, GolBoundingShape* p_shape,
							LegoFloat p_modelDistance); // vtable+0x60

	void FUN_1001acf0(GolModelBase* p_model, GolBoundingShape* p_shape, LegoFloat p_modelDistance);
	void FUN_00403c60();
	GolBoundingShape* GetBoundingShape(LegoU32 p_index) const { return m_boundingShapes[p_index]; }

protected:
	GolBoundingShape* m_boundingShapes[3]; // 0x90
};

#endif // GOLCOLLIDABLEENTITY_H
