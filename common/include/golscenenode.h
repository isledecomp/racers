#ifndef GOLSCENENODE_H
#define GOLSCENENODE_H

#include "golnametable.h"
#include "goltxtparser.h"

class GolFileParser;
struct GolMatrix34;
struct GolMatrix4;
struct GolQuat;
struct GolVec3;
class GolTransformBase;

// VTABLE: GOLDP 0x10057454
// SIZE 0x18
class GolSceneNode : public GolNameTable {
public:
	// VTABLE: GOLDP 0x10057484
	// SIZE 0x1fc
	class DdfTxtParser : public GolTxtParser {
	public:
		// .sdf tokens
		enum {
			e_node = 0x27,
			e_position = 0x28,
			e_rotation = 0x29,
			e_parent = 0x2a,
		};

		// SYNTHETIC: GOLDP 0x10030050 FOLDED
		// GolSceneNode::DdfTxtParser::`scalar deleting destructor'

		// SYNTHETIC: GOLDP 0x1001b000 FOLDED
		// GolSceneNode::DdfTxtParser::~DdfTxtParser
	};

	class TransformComposer {
	public:
		virtual LegoBool32 HasOverride(LegoU32 p_index) = 0; // vtable+0x00
		virtual void Compose(
			LegoU32 p_index,
			const GolQuat& p_rotation,
			const GolVec3& p_position,
			const GolMatrix4& p_parentMatrix,
			GolMatrix4* p_dest
		) = 0; // vtable+0x04
	};

	GolSceneNode();
	~GolSceneNode() override;                                                // vtable+0x00
	void Allocate(LegoU32 p_capacity) override;                              // vtable+0x04
	void Clear() override;                                                   // vtable+0x08
	virtual void AllocateTransforms() = 0;                                   // vtable+0x0c
	virtual void CopyFrom(GolSceneNode* p_node);                             // vtable+0x10
	virtual void Load(const LegoChar* p_name, LegoBool32 p_binary);          // vtable+0x14
	virtual GolTransformBase* GetTransform(LegoU32 p_index) const = 0;       // vtable+0x18
	virtual LegoU32 IndexOf(const GolTransformBase&) const;                  // vtable+0x1c
	virtual void UpdateWorldMatrices(const GolMatrix4& p_m);                 // vtable+0x20
	virtual void UpdateWorldMatricesAffine(const GolMatrix34* p_m);          // vtable+0x24
	virtual void VTable0x28(undefined4, undefined4);                         // vtable+0x28
	virtual void GetWorldMatrix(LegoU32 p_index, GolMatrix34* p_dest) const; // vtable+0x2c

	// SYNTHETIC: GOLDP 0x100299a0
	// GolSceneNode::`scalar deleting destructor'

	void TransformPointToWorld(undefined4 p_param1, GolVec3* p_param2, GolVec3* p_param3);
	void TransformVectorToWorld(undefined4 p_param1, GolVec3* p_param2, GolVec3* p_param3);
	void MirrorY();
	LegoU32 GetUpdateSerial() const { return m_updateSerial; }
	LegoU32 GetCapacity() const { return m_capacity; }
	LegoU32 AdvanceUpdateSerial()
	{
		m_updateSerial++;
		if (m_updateSerial == static_cast<LegoU32>(-1)) {
			m_updateSerial = 0;
		}
		return m_updateSerial;
	}

protected:
	void Parse(GolFileParser* p_parser);

	undefined4 m_updateSerial;     // 0x0c
	LegoU32 m_capacity;            // 0x10
	TransformComposer* m_composer; // 0x14
};

#endif // GOLSCENENODE_H
