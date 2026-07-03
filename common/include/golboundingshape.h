#ifndef GOLBOUNDINGSHAPE_H
#define GOLBOUNDINGSHAPE_H

#include "decomp.h"
#include "golmath.h"
#include "goltxtparser.h"
#include "types.h"

class GolViewFrustum;

// VTABLE: GOLDP 0x10056b68
// SIZE 0x2c
class GolBoundingShape {
public:
	// .bdb binary block tags (cf. data/liblr1/LibLR1/BDB.cs).
	enum BdbBlockType {
		c_bdbShapeTypes = 0x27,
		c_bdbBoundingBoxes = 0x2a,
		c_bdbIndexList = 0x2b,
	};

	enum BdbShapeSubtype {
		c_shapeFloat = 0x28,
		c_shapeFixedPoint = 0x29,
	};

	// VTABLE: GOLDP 0x10056b74
	// SIZE 0x1fc
	class BdbTxtParser : public GolTxtParser {
	public:
		// .bdf tokens
		enum {
			e_nodes = 0x27,
			e_plane = 0x28,
			e_leaf = 0x29,
			e_bounds = 0x2a,
			e_pvsIndices = 0x2b,
		};
	};

	// SIZE 0x20
	struct TreeNode {
		enum {
			c_invalidIndex = 0xffff,
			e_plane = 0,
			e_leaf = 1,
		};

		LegoU16 m_type;
		LegoU16 m_nextLeafIndex;

		// SIZE 0x1c
		struct Node {
			LegoU32 m_firstGroup;
			LegoU32 m_groupCount;
			undefined4 m_unk0x08;
			Node* m_next;
			Node* m_previous;
			LegoS16 m_pvsStart;
			LegoU16 m_pvsCount;
			LegoU16 m_boundsIndex;
			LegoU16 m_linked;
		};

		// SIZE 0x1c
		union Payload {
			struct {
				LegoFloat m_normalX;
				LegoFloat m_normalY;
				LegoFloat m_normalZ;
				LegoFloat m_distance;
				LegoU32 m_frontStamp;
				LegoU32 m_backStamp;
				LegoU16 m_frontChild;
				LegoU16 m_backChild;
			} m_plane;
			Node m_node;
		} m_data;
	};
	// SIZE 0x18
	struct Bounds {
		LegoFloat m_minX;
		LegoFloat m_minY;
		LegoFloat m_minZ;
		LegoFloat m_maxX;
		LegoFloat m_maxY;
		LegoFloat m_maxZ;
	};

	GolBoundingShape();
	virtual ~GolBoundingShape();                                           // vtable+0x00
	virtual void Deserialize(const LegoChar* p_path, LegoBool32 p_binary); // vtable+0x04
	virtual void Destroy();                                                // vtable+0x08

	void CollectVisibleLeaves(const GolViewFrustum* p_frustum, TreeNode::Node** p_first, TreeNode::Node** p_last);
	void CollectLeavesFromPvs(
		const GolViewFrustum* p_frustum,
		TreeNode* p_entry,
		TreeNode::Node** p_first,
		TreeNode::Node** p_last
	);
	void CollectLeavesAtPoints(GolVec3* p_unk0x04, LegoU32 p_unk0x08);
	void MirrorY();
	TreeNode::Node* GetFirstVisibleLeaf() const { return m_firstVisibleLeaf; }

	// SYNTHETIC: GOLDP 0x100179a0
	// GolBoundingShape::`vector deleting destructor'

private:
	void ParseNodes(GolFileParser& p_parser);
	void ParseBounds(GolFileParser& p_parser);

	LegoU32 m_nodeCount;
	TreeNode* m_nodes;
	TreeNode* m_root;
	undefined4 m_visitStamp;
	LegoS32 m_boundsCount;
	Bounds* m_bounds;
	LegoS32 m_pvsIndexCount;
	LegoU16* m_pvsIndices;
	TreeNode::Node* m_firstVisibleLeaf;
	TreeNode::Node* m_lastVisibleLeaf;
};

#endif // GOLBOUNDINGSHAPE_H
