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

		LegoU16 m_type;          // 0x00
		LegoU16 m_nextLeafIndex; // 0x02

		// SIZE 0x1c
		struct Node {
			LegoU32 m_firstGroup;  // 0x00
			LegoU32 m_groupCount;  // 0x04
			undefined4 m_unk0x08;  // 0x08
			Node* m_next;          // 0x0c
			Node* m_previous;      // 0x10
			LegoS16 m_pvsStart;    // 0x14
			LegoU16 m_pvsCount;    // 0x16
			LegoU16 m_boundsIndex; // 0x18
			LegoU16 m_linked;      // 0x1a
		};

		// SIZE 0x1c
		union Payload {
			struct {
				LegoFloat m_normalX;  // 0x00
				LegoFloat m_normalY;  // 0x04
				LegoFloat m_normalZ;  // 0x08
				LegoFloat m_distance; // 0x0c
				LegoU32 m_frontStamp; // 0x10
				LegoU32 m_backStamp;  // 0x14
				LegoU16 m_frontChild; // 0x18
				LegoU16 m_backChild;  // 0x1a
			} m_plane;                // 0x00
			Node m_node;              // 0x00
		} m_data;                     // 0x04
	};
	// SIZE 0x18
	struct Bounds {
		LegoFloat m_minX; // 0x00
		LegoFloat m_minY; // 0x04
		LegoFloat m_minZ; // 0x08
		LegoFloat m_maxX; // 0x0c
		LegoFloat m_maxY; // 0x10
		LegoFloat m_maxZ; // 0x14
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
	void CollectLeavesAtPoints(GolVec3* p_points, LegoU32 p_pointCount);
	void MirrorY();
	TreeNode::Node* GetFirstVisibleLeaf() const { return m_firstVisibleLeaf; }

	// SYNTHETIC: GOLDP 0x100179a0
	// GolBoundingShape::`vector deleting destructor'

private:
	void ParseNodes(GolFileParser& p_parser);
	void ParseBounds(GolFileParser& p_parser);

	LegoU32 m_nodeCount;                // 0x04
	TreeNode* m_nodes;                  // 0x08
	TreeNode* m_root;                   // 0x0c
	undefined4 m_visitStamp;            // 0x10
	LegoS32 m_boundsCount;              // 0x14
	Bounds* m_bounds;                   // 0x18
	LegoS32 m_pvsIndexCount;            // 0x1c
	LegoU16* m_pvsIndices;              // 0x20
	TreeNode::Node* m_firstVisibleLeaf; // 0x24
	TreeNode::Node* m_lastVisibleLeaf;  // 0x28
};

#endif // GOLBOUNDINGSHAPE_H
