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
	void Draw(GolRenderDevice& p_renderer) override; // vtable+0x1c
	void Initialize(
		GolModelBase* p_model,
		GolSceneNode* p_sceneNode,
		undefined4 p_faceCamera,
		LegoFloat p_modelDistance
	);
	void ResetModelState() override;
	GolSceneNode* GetSceneNode(undefined4) override; // vtable+0x58

private:
	GolSceneNode* m_sceneNode; // 0x90
	undefined4 m_faceCamera;   // 0x94
};

#endif // BEAMENTITY_H
