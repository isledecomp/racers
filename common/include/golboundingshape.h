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
	class BdbTxtParser : public GolTxtParser {};

	// SIZE 0x20
	struct StructField0x08 {
		enum {
			c_invalidIndex = 0xffff,
			e_type0 = 0,
			e_type1 = 1,
		};

		LegoU16 m_type;
		LegoU16 m_unk0x02;

		// SIZE 0x1c
		struct Node {
			LegoU32 m_firstGroup;
			LegoU32 m_groupCount;
			undefined4 m_unk0x08;
			Node* m_next;
			Node* m_previous;
			LegoS16 m_unk0x14;
			LegoU16 m_unk0x16;
			LegoU16 m_unk0x18;
			LegoU16 m_unk0x1a;
		};

		// SIZE 0x1c
		union Payload {
			struct {
				LegoFloat m_unk0x00;
				LegoFloat m_unk0x04;
				LegoFloat m_unk0x08;
				LegoFloat m_unk0x0c;
				LegoU32 m_unk0x10;
				LegoU32 m_unk0x14;
				LegoU16 m_unk0x18;
				LegoU16 m_unk0x1a;
			} m_t0;
			struct {
				undefined4 m_unk0x00;
				undefined4 m_unk0x04;
				undefined4 m_unk0x08;
				StructField0x08* m_unk0x0c;
				StructField0x08* m_unk0x10;
				LegoS16 m_unk0x14;
				LegoU16 m_unk0x16;
				LegoU16 m_unk0x18;
				undefined m_unk0x1a[0x1c - 0x1a];
			} m_t1;
			Node m_node;
		} m_unk0x04;
	};
	// SIZE 0x18
	struct StructField0x18 {
		LegoFloat m_unk0x00;
		LegoFloat m_unk0x04;
		LegoFloat m_unk0x08;
		LegoFloat m_unk0x0c;
		LegoFloat m_unk0x10;
		LegoFloat m_unk0x14;
	};

	GolBoundingShape();
	virtual ~GolBoundingShape();                                           // vtable+0x00
	virtual void Deserialize(const LegoChar* p_path, LegoBool32 p_binary); // vtable+0x04
	virtual void Destroy();                                                // vtable+0x08

	void FUN_1001b2c0(const GolViewFrustum* p_frustum, StructField0x08::Node** p_first, StructField0x08::Node** p_last);
	void FUN_1001b640(
		const GolViewFrustum* p_frustum,
		StructField0x08* p_entry,
		StructField0x08::Node** p_first,
		StructField0x08::Node** p_last
	);
	void FUN_00403cc0(GolVec3* p_unk0x04, LegoU32 p_unk0x08);
	void FUN_00403f20();
	StructField0x08::Node* GetUnk0x24() const { return m_unk0x24; }

	// SYNTHETIC: GOLDP 0x100179a0
	// GolBoundingShape::`vector deleting destructor'

private:
	void FUN_1001b010(GolFileParser& p_parser);
	void FUN_1001b1a0(GolFileParser& p_parser);

	LegoU32 m_unk0x04;
	StructField0x08* m_unk0x08;
	StructField0x08* m_unk0x0c;
	undefined4 m_unk0x10;
	LegoS32 m_unk0x14;
	StructField0x18* m_unk0x18;
	LegoS32 m_unk0x1c;
	LegoU16* m_unk0x20;
	StructField0x08::Node* m_unk0x24;
	StructField0x08::Node* m_unk0x28;
};

#endif // GOLBOUNDINGSHAPE_H
