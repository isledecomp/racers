#ifndef GOLANIMATEDENTITY_H
#define GOLANIMATEDENTITY_H

#include "compat.h"
#include "decomp.h"
#include "golmodelentity.h"
#include "types.h"

class CmbModelPart;
class GolModelBase;
class GolSceneNode;

// VTABLE: GOLDP 0x10056fc8
// VTABLE: LEGORACERS 0x004af5ec
// SIZE 0xf4
class GolAnimatedEntity : public GolModelEntity {
public:
	enum {
		c_flagPartAnimation = 1 << 16,
		c_flagPartTransition = 1 << 17,
		c_flagLoopCurrentPart = 1 << 18,
		c_flagPartAnimationDone = 1 << 19,
		c_flagRestartQueuedPart = 1 << 20,
		c_flagLoopQueuedPart = 1 << 22,
		c_flagLoopWrapped = 1 << 25,
		c_flagsPartAnimationMask = 0x005a0000,
	};

	GolAnimatedEntity();

	void Update(LegoS32 p_elapsed) override;                                               // vtable+0x10
	void ComputeVisibility(const GolViewFrustum& p_view, ResultStruct* p_result) override; // vtable+0x14
	void ComputeBoundsFromModel(LegoU32 p_index) override;                                 // vtable+0x4c
	void ResetModelState() override;                                                       // vtable+0x54
	GolSceneNode* GetSceneNode(LegoU32 p_arg1) override;                                   // vtable+0x58
	void ApplyPartAnimation(LegoU32 p_arg1) override;                                      // vtable+0x5c

	void SetModel(GolModelBase* p_model, GolSceneNode* p_node, CmbModelPart* p_modelParts, LegoFloat p_modelDistance);
	void SetNode(GolSceneNode* p_node, CmbModelPart* p_modelParts, LegoFloat p_modelDistance);
	void AddModel(GolModelBase* p_model, GolSceneNode* p_node, CmbModelPart* p_modelParts, LegoFloat p_modelDistance);
	void AddNode(GolSceneNode* p_node, CmbModelPart* p_modelParts, LegoFloat p_modelDistance);
	void PlayPart(LegoU32 p_partIndex);
	void PlayPartDirect(LegoU32 p_partIndex);
	void TransitionToPart(
		LegoU32 p_partIndex,
		LegoS32 p_transitionTime,
		LegoFloat p_time,
		LegoBool32 p_updateCurrent,
		LegoBool32 p_updateQueued,
		LegoBool32 p_loop
	);
	LegoBool32 IsPartAnimationDone();
	void SamplePartPosition(
		LegoU32 p_modelIndex,
		LegoU32 p_trackOffset,
		LegoU32 p_partDataIndex,
		LegoS32 p_frame,
		GolVec3* p_dest
	);
	void SamplePartRotation(
		LegoU32 p_modelIndex,
		LegoU32 p_trackOffset,
		LegoU32 p_partDataIndex,
		LegoS32 p_frame,
		GolQuat* p_dest
	);
	void ResetPartIndices();
	CmbModelPart* GetModelPart(LegoU32 p_index = 0) const { return m_modelParts[p_index]; }
	LegoU32 GetFlags() const { return m_flags; }
	void SetFlags(LegoU32 p_flags) { m_flags = p_flags; }
	void SetActiveValue(LegoFloat p_value) { m_partTimeMs = p_value; }
	void SetPartAnimationEnabled(LegoBool32 p_enabled)
	{
		if (p_enabled) {
			m_flags |= c_flagPartAnimation;
		}
		else {
			m_flags &= ~c_flagPartAnimation;
		}
	}
	LegoU16 GetActiveState() const { return (m_flags & 0x20000) ? m_queuedPartIndex : m_currentPartIndex; }
	LegoU16 GetCurrentPartIndex() const { return m_currentPartIndex; }
	LegoU16 GetQueuedPartIndex() const { return m_queuedPartIndex; }
	LegoFloat GetActiveValue() const { return (m_flags & 0x20000) ? m_queuedPartTimeMs : m_partTimeMs; }
	LegoFloat GetPartTimeMs() const { return m_partTimeMs; }
	LegoFloat GetMsPerFrame() const { return m_msPerFrame; }
	void SetQueuedPartIndex(LegoU16 p_partIndex) { m_queuedPartIndex = p_partIndex; }
	void QueuePartTransition(LegoU16 p_partIndex)
	{
		m_queuedPartIndex = p_partIndex;
		m_flags = (m_flags & ~(c_flagPartTransition | c_flagLoopCurrentPart | c_flagPartAnimationDone)) |
				  c_flagRestartQueuedPart | c_flagLoopQueuedPart;
	}
	void SetMsPerFrame(LegoFloat p_unk0xb8) { m_msPerFrame = p_unk0xb8; }
	void PlayPartScaled(LegoU32 p_partIndex, LegoS32 p_timeScale);

private:
	void Reset();

	GolSceneNode* m_nodes[3];         // 0x90
	LegoS32 m_partIndices[3];         // 0x9c
	CmbModelPart* m_modelParts[3];    // 0xa8
	LegoFloat m_partTimeMs;           // 0xb4
	LegoFloat m_msPerFrame;           // 0xb8
	LegoU16 m_currentPartIndex;       // 0xbc
	undefined m_unk0xbe[0xc0 - 0xbe]; // 0xbe
	GolVec3 m_currentPartVelocity;    // 0xc0
	LegoBool32 m_advanceCurrent;      // 0xcc
	LegoFloat m_queuedPartTimeMs;     // 0xd0
	LegoFloat m_queuedMsPerFrame;     // 0xd4
	LegoU16 m_queuedPartIndex;        // 0xd8
	undefined m_unk0xda[0xdc - 0xda]; // 0xda
	GolVec3 m_queuedPartVelocity;     // 0xdc
	LegoBool32 m_advanceQueued;       // 0xe8
	LegoFloat m_transitionProgress;   // 0xec
	LegoFloat m_transitionRate;       // 0xf0
};

#endif // GOLANIMATEDENTITY_H
