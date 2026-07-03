#ifndef GOLSCENETRANSFORMNODE_H
#define GOLSCENETRANSFORMNODE_H

#include "compat.h"
#include "decomp.h"
#include "golscenenode.h"

class GolTransformBase;
class GolTransform;
class GolD3DRenderDevice;
struct GolMatrix4;

// VTABLE: GOLDP 0x1005672c
// SIZE 0x1c
class GolSceneTransformNode : public GolSceneNode {
public:
	GolSceneTransformNode();
	~GolSceneTransformNode() override; // vtable+0x00

	void Clear() override;                                                    // vtable+0x08
	void AllocateTransforms() override;                                       // vtable+0x0c
	GolTransformBase* GetTransform(LegoU32 p_index) const override;           // vtable+0x18
	LegoU32 IndexOf(const GolTransformBase&) const override;                  // vtable+0x1c
	void UpdateWorldMatrices(const GolMatrix4& p_m) override;                 // vtable+0x20
	void UpdateWorldMatricesAffine(const GolMatrix34* p_m) override;          // vtable+0x24
	void GetWorldMatrix(LegoU32 p_index, GolMatrix34* p_dest) const override; // vtable+0x2c

	void UpdateWorldViewMatrices(const GolMatrix4& p_m1, const GolMatrix4& p_m2, const GolMatrix4& p_m3);

	// SYNTHETIC: GOLDP 0x10017940
	// GolSceneTransformNode::`vector deleting destructor'

private:
	friend class GolD3DRenderDevice;

	GolTransform* m_transforms; // 0x18
};

#endif // GOLSCENETRANSFORMNODE_H
