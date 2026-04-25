#ifndef PERIDOTTRACE0X4E0_H
#define PERIDOTTRACE0X4E0_H

#include "decomp.h"
#include "types.h"

// SIZE 0x4a8
class PeridotTrace0x4a8 {
public:
	PeridotTrace0x4a8();
	~PeridotTrace0x4a8();

	LegoBool32 HasUnk0x04() const { return m_unk0x04 != 0; }

private:
	undefined4 m_unk0x00;              // 0x00
	undefined* m_unk0x04;              // 0x04
	undefined m_unk0x08[0x4a8 - 0x08]; // 0x08
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
class PeridotTrace0x4e0 {
public:
	PeridotTrace0x4e0();
	~PeridotTrace0x4e0();

	LegoBool32 HasUnk0x4b4Flag0x01() const { return !m_unk0x4a8->HasUnk0x04() && m_unk0x4ac.HasUnk0x08Flag0x01(); }

	void FUN_004438e0();

private:
	PeridotTrace0x4a8 m_unk0x00;       // 0x00
	PeridotTrace0x4a8* m_unk0x4a8;     // 0x4a8
	PeridotTraceAction0x34 m_unk0x4ac; // 0x4ac
};

// SIZE 0x438
class PeridotTraceState0x438 {
public:
	PeridotTraceState0x438();
	~PeridotTraceState0x438();

	LegoU8 GetUnk0x22() const { return m_unk0x22; }

private:
	undefined m_unk0x00[0x22 - 0x00];  // 0x00
	LegoU8 m_unk0x22;                  // 0x22
	undefined m_unk0x23[0x438 - 0x23]; // 0x23
};

// SIZE 0x250
class PeridotTraceBuffer0x250 {
public:
	PeridotTraceBuffer0x250();
	~PeridotTraceBuffer0x250();

	void Reset() { m_unk0x244 = 0; }

private:
	undefined m_unk0x00[0x244 - 0x00];   // 0x00
	undefined4 m_unk0x244;               // 0x244
	undefined m_unk0x248[0x250 - 0x248]; // 0x248
};

#endif // PERIDOTTRACE0X4E0_H
