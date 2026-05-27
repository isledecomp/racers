#ifndef GOLWDBCOLLIDABLEENTITY_H
#define GOLWDBCOLLIDABLEENTITY_H

#include "compat.h"
#include "decomp.h"
#include "scene/golwdbmodelentity.h"

class GolRenderDevice;
class GolBdbBoundingShape;
class GolGdbModelBase;

// VTABLE: GOLDP 0x10056b04
// SIZE 0x9c
class GolWdbCollidableEntity : public GolWdbModelEntity {
public:
	GolWdbCollidableEntity();

	void VTable0x1c(GolRenderDevice&) override; // vtable+0x1c
	void VTable0x54() override;                 // vtable+0x54
	virtual void VTable0x60(
		GolGdbModelBase* p_model,
		GolBdbBoundingShape* p_shape,
		LegoFloat p_modelDistance
	); // vtable+0x60

	void FUN_1001acf0(GolGdbModelBase* p_model, GolBdbBoundingShape* p_shape, LegoFloat p_modelDistance);

protected:
	GolBdbBoundingShape* m_boundingShapes[3]; // 0x90
};

#endif // GOLWDBCOLLIDABLEENTITY_H
