#ifndef BEAMENTITY_H
#define BEAMENTITY_H

#include "golmodelentity.h"

// VTABLE: LEGORACERS 0x004b47a8
// SIZE 0x98
class BeamEntity : public GolModelEntity {
public:
	BeamEntity();
	~BeamEntity();
	BeamEntity* Destroy(undefined4 p_flags);
	void VTable0x1c(GolRenderDevice& p_renderer) override; // vtable+0x1c
	void Initialize(
		GolModelBase* p_model,
		GolSceneNode* p_sceneNode,
		undefined4 p_faceCamera,
		LegoFloat p_modelDistance
	);
	void VTable0x54() override;
	GolSceneNode* VTable0x58(undefined4) override; // vtable+0x58

private:
	GolSceneNode* m_sceneNode; // 0x90
	undefined4 m_faceCamera;   // 0x94
};

#endif // BEAMENTITY_H
