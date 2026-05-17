#ifndef PERIDOTTRACEROOT0X108_H
#define PERIDOTTRACEROOT0X108_H

#include "compat.h"
#include "decomp.h"
#include "types.h"

class PeridotTraceRoot0x108;

// VTABLE: LEGORACERS 0x004b0f88
// SIZE 0x08
class PeridotTraceRootEntryBase0x8 {
public:
	PeridotTraceRootEntryBase0x8();
	virtual ~PeridotTraceRootEntryBase0x8();               // vtable+0x00
	virtual undefined4 VTable0x04() = 0;                   // vtable+0x04
	virtual undefined4 VTable0x08() = 0;                   // vtable+0x08
	virtual undefined4 VTable0x0c(undefined4) = 0;         // vtable+0x0c
	virtual undefined4 VTable0x10(undefined4);             // vtable+0x10
	virtual undefined4 VTable0x14(undefined4) = 0;         // vtable+0x14
	virtual undefined4 VTable0x18(undefined4, undefined4); // vtable+0x18
	virtual undefined4 VTable0x1c(undefined4);             // vtable+0x1c
	virtual undefined4 VTable0x20(undefined4, undefined4); // vtable+0x20

	// SYNTHETIC: LEGORACERS 0x0044e050
	// PeridotTraceRootEntryBase0x8::`scalar deleting destructor'

	LegoBool32 HasUnk0x04() const { return m_unk0x04 != 0; }

protected:
	undefined4 m_unk0x04; // 0x04
};

// VTABLE: LEGORACERS 0x004b1308
// SIZE 0x10
class PeridotTraceRootEntry0x10 : public PeridotTraceRootEntryBase0x8 {
public:
	PeridotTraceRootEntry0x10();
	~PeridotTraceRootEntry0x10() override;      // vtable+0x00
	undefined4 VTable0x04() override;           // vtable+0x04
	undefined4 VTable0x08() override;           // vtable+0x08
	undefined4 VTable0x0c(undefined4) override; // vtable+0x0c
	undefined4 VTable0x14(undefined4) override; // vtable+0x14

	// SYNTHETIC: LEGORACERS 0x004510c0
	// PeridotTraceRootEntry0x10::`scalar deleting destructor'

	void FUN_00451130(PeridotTraceRoot0x108* p_root, LegoU32 p_index);
	void Reset();

private:
	PeridotTraceRoot0x108* m_root; // 0x08
	LegoU32 m_index;               // 0x0c
};

// VTABLE: LEGORACERS 0x004b12e4
// SIZE 0x10
class PeridotTraceRootEntryDerived0x10 : public PeridotTraceRootEntry0x10 {
public:
	PeridotTraceRootEntryDerived0x10();

	// SYNTHETIC: LEGORACERS 0x00450f30
	// PeridotTraceRootEntryDerived0x10::~PeridotTraceRootEntryDerived0x10

	// SYNTHETIC: LEGORACERS 0x00450f40
	// PeridotTraceRootEntryDerived0x10::`scalar deleting destructor'
};

// VTABLE: LEGORACERS 0x004b12d8
// SIZE 0x08
class PeridotTraceRootBase0x08 {
public:
	virtual void Clear() = 0;                                 // vtable+0x00
	virtual LegoU32 GetEntryCount() = 0;                      // vtable+0x04
	virtual PeridotTraceRootEntry0x10* GetEntry(LegoU32) = 0; // vtable+0x08

protected:
	LegoChar* m_directoryPath; // 0x04
};

// VTABLE: LEGORACERS 0x004b12c8
// SIZE 0x108
class PeridotTraceRoot0x108 : public PeridotTraceRootBase0x08 {
public:
	PeridotTraceRoot0x108();
	void Clear() override;                                 // vtable+0x00
	LegoU32 GetEntryCount() override;                      // vtable+0x04
	PeridotTraceRootEntry0x10* GetEntry(LegoU32) override; // vtable+0x08
	virtual ~PeridotTraceRoot0x108();                      // vtable+0x0c
	void FUN_00450fc0(const LegoChar* p_path);

	// SYNTHETIC: LEGORACERS 0x00450ef0
	// PeridotTraceRoot0x108::`scalar deleting destructor'

private:
	PeridotTraceRootEntryDerived0x10 m_entries[16]; // 0x08
};

#endif // PERIDOTTRACEROOT0X108_H
