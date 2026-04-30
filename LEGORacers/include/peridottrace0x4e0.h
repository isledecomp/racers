#ifndef PERIDOTTRACE0X4E0_H
#define PERIDOTTRACE0X4E0_H

#include "decomp.h"
#include "types.h"

class GolFile;
class PeridotTrace0x4e0;

// SIZE 0x24
class PeridotTraceBase0x24 {
public:
	PeridotTraceBase0x24();

	LegoBool32 HasUnk0x04() const { return m_unk0x04 != 0; }
	undefined4 GetUnk0x20() const { return m_unk0x20; }

private:
	void Init();

	undefined4 m_unk0x00;
	undefined4 m_unk0x04;
	undefined4 m_unk0x08;
	undefined4 m_unk0x0c;
	undefined4 m_unk0x10;
	undefined4 m_unk0x14;
	undefined4 m_unk0x18;
	undefined4 m_unk0x1c;
	undefined4 m_unk0x20;
};

// SIZE 0x4a8
class PeridotTrace0x4a8 : public PeridotTraceBase0x24 {
public:
	PeridotTrace0x4a8();
	~PeridotTrace0x4a8();

	void FUN_004426d0(undefined4, undefined4, undefined4);
	undefined4 FUN_00442770(GolFile& p_file);
	undefined4 FUN_004439b0();

private:
	undefined m_unk0x24[0x4a4 - 0x24]; // 0x24
	undefined4 m_unk0x4a4;
};

// SIZE 0x34
class PeridotTraceActionBase0x34 {
public:
	PeridotTraceActionBase0x34();
	~PeridotTraceActionBase0x34();

	enum {
		c_unk0x08Flag0x01 = 1 << 0,
	};

	LegoBool32 HasUnk0x08Flag0x01() const { return m_unk0x08 & c_unk0x08Flag0x01; }

private:
	undefined4 m_unk0x00;             // 0x00
	undefined4 m_unk0x04;             // 0x04
	LegoU32 m_unk0x08;                // 0x08
	undefined m_unk0x0c[0x34 - 0x0c]; // 0x0c
};

// SIZE 0x34
class PeridotTraceAction0x34 : public PeridotTraceActionBase0x34 {};

// SIZE 0x4e0
class PeridotTrace0x4e0 : public PeridotTrace0x4a8 {
public:
	PeridotTrace0x4e0();
	~PeridotTrace0x4e0();

	LegoBool32 HasUnk0x4b4Flag0x01() const { return !m_unk0x4a8->HasUnk0x04() && m_unk0x4ac.HasUnk0x08Flag0x01(); }

	void FUN_004438e0();
	undefined4 FUN_00443910();
	undefined4 FUN_00443940();
	undefined4 FUN_00443980();

private:
	PeridotTrace0x4a8* m_unk0x4a8;     // 0x4a8
	PeridotTraceAction0x34 m_unk0x4ac; // 0x4ac
};

// SIZE 0x438
class PeridotTraceState0x438 {
public:
	PeridotTraceState0x438();
	~PeridotTraceState0x438();

	void FUN_0042e920(undefined4*);
	void FUN_0042eb60(PeridotTrace0x4e0*, undefined4);
	void FUN_0042ef80(PeridotTrace0x4a8*);
	void FUN_0042f200(LegoU8 p_unk0x04);
	LegoBool32 FUN_0042f250(LegoU32 p_unk0x04);
	LegoBool32 FUN_0042f280() const;

	void SetUnk0x00(undefined4 p_arg1) { m_unk0x00 = p_arg1; }
	undefined4 GetUnk0x00() const { return m_unk0x00; }
	undefined4 GetUnk0x04() const { return m_unk0x04; }
	LegoU8 GetUnk0x22() const { return m_unk0x22; }

private:
	undefined4 m_unk0x00;              // 0x00
	undefined4 m_unk0x04;              // 0x04
	undefined m_unk0x08[0x22 - 0x08];  // 0x08
	LegoU8 m_unk0x22;                  // 0x22
	undefined m_unk0x23;               // 0x23
	LegoU8 m_unk0x24;                  // 0x24
	LegoU8 m_unk0x25;                  // 0x25
	LegoU16 m_unk0x26;                 // 0x26
	undefined m_unk0x28[0x438 - 0x28]; // 0x28
};

// SIZE 0x250
class PeridotTraceBuffer0x250 {
public:
	PeridotTraceBuffer0x250();
	~PeridotTraceBuffer0x250();

	void Reset() { m_unk0x244 = 0; }

	void FUN_0042b2f0(undefined4, undefined4, undefined4, undefined4);

private:
	undefined m_unk0x00[0x244 - 0x00];   // 0x00
	undefined4 m_unk0x244;               // 0x244
	undefined m_unk0x248[0x250 - 0x248]; // 0x248
};

#endif // PERIDOTTRACE0X4E0_H
