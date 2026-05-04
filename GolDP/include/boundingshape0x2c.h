#ifndef BOUNDINGSHAPE0x2C_H
#define BOUNDINGSHAPE0x2C_H

#include "decomp.h"
#include "goltxtparser.h"
#include "types.h"

// VTABLE: GOLDP 0x10056b74
// SIZE 0x1fc
class BdbTxtParser : public GolTxtParser {};

// VTABLE: GOLDP 0x10056b68
// SIZE 0x2c
class BoundingShape0x2c {
public:
	// SIZE 0x20
	struct StructField0x08 {
		enum {
			c_invalidIndex = 0xffff,
			e_type0 = 0,
			e_type1 = 1,
		};

		LegoU16 m_type;
		LegoU16 m_unk0x02;
		union {
			struct {
				LegoFloat m_unk0x00;
				LegoFloat m_unk0x04;
				LegoFloat m_unk0x08;
				LegoFloat m_unk0x0c;
				undefined4 m_unk0x10;
				undefined4 m_unk0x14;
				LegoU16 m_unk0x18;
				LegoU16 m_unk0x1a;
			} t0;
			struct {
				undefined4 m_unk0x00;
				undefined4 m_unk0x04;
				undefined4 m_unk0x08;
				undefined4 m_unk0x0c;
				undefined4 m_unk0x10;
				undefined2 m_unk0x14;
				undefined2 m_unk0x16;
				undefined2 m_unk0x18;
				undefined m_unk0x1a[0x1c - 0x1a];
			} t1;
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

	BoundingShape0x2c();
	virtual ~BoundingShape0x2c();                                          // vtable+0x00
	virtual void Deserialize(const LegoChar* p_path, LegoBool32 p_binary); // vtable+0x04
	virtual void Destroy();                                                // vtable+0x08

	void FUN_1001b2c0(undefined4*, undefined4*, undefined4*);
	void FUN_1001b640(undefined4*, undefined4*, undefined4*, undefined4*);

	// SYNTHETIC: GOLDP 0x100179a0
	// BoundingShape0x2c::`vector deleting destructor'

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
	LegoS16* m_unk0x20;
	undefined4 m_unk0x24;
	undefined4 m_unk0x28;
};

#endif // BOUNDINGSHAPE0x2C_H
