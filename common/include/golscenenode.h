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
		// SYNTHETIC: GOLDP 0x10030050 FOLDED
		// GolSceneNode::DdfTxtParser::`scalar deleting destructor'

		// SYNTHETIC: GOLDP 0x1001b000 FOLDED
		// GolSceneNode::DdfTxtParser::~DdfTxtParser
	};

	class Field0x14 {
	public:
		virtual LegoBool32 VTable0x00(LegoU32 p_index) = 0; // vtable+0x00
		virtual void VTable0x04(
			LegoU32 p_index,
			const GolQuat& p_rotation,
			const GolVec3& p_position,
			const GolMatrix4& p_parentMatrix,
			GolMatrix4* p_dest
		) = 0; // vtable+0x04
	};

	GolSceneNode();
	~GolSceneNode() override;                                             // vtable+0x00
	void Allocate(LegoU32 p_capacity) override;                           // vtable+0x04
	void Clear() override;                                                // vtable+0x08
	virtual void VTable0x0c() = 0;                                        // vtable+0x0c
	virtual void VTable0x10(GolSceneNode* p_node);                        // vtable+0x10
	virtual void VTable0x14(const LegoChar* p_name, LegoBool32 p_binary); // vtable+0x14
	virtual GolTransformBase* VTable0x18(LegoU32 p_index) const = 0;      // vtable+0x18
	virtual LegoU32 VTable0x1c(const GolTransformBase&) const;            // vtable+0x1c
	virtual void VTable0x20(const GolMatrix4& p_m);                       // vtable+0x20
	virtual void VTable0x24(const GolMatrix34* p_m);                      // vtable+0x24
	virtual void VTable0x28(undefined4, undefined4);                      // vtable+0x28
	virtual void VTable0x2c(LegoU32 p_index, GolMatrix34* p_dest) const;  // vtable+0x2c

	// SYNTHETIC: GOLDP 0x100299a0
	// GolSceneNode::`scalar deleting destructor'

	void FUN_00413230(undefined4 p_param1, GolVec3* p_param2, GolVec3* p_param3);
	void FUN_004132a0(undefined4 p_param1, GolVec3* p_param2, GolVec3* p_param3);
	void FUN_00413310();
	LegoU32 GetUpdateSerial() const { return m_unk0x0c; }
	LegoU32 GetCapacity() const { return m_capacity; }
	LegoU32 AdvanceUpdateSerial()
	{
		m_unk0x0c++;
		if (m_unk0x0c == static_cast<LegoU32>(-1)) {
			m_unk0x0c = 0;
		}
		return m_unk0x0c;
	}

protected:
	void FUN_10029c60(GolFileParser* p_parser);

	undefined4 m_unk0x0c; // 0x0c
	LegoU32 m_capacity;   // 0x10
	Field0x14* m_unk0x14; // 0x14
};

#endif // GOLSCENENODE_H
