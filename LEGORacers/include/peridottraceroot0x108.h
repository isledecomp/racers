#ifndef PERIDOTTRACEROOT0X108_H
#define PERIDOTTRACEROOT0X108_H

#include "compat.h"
#include "decomp.h"
#include "types.h"

// SIZE 0x10
class PeridotTraceRootEntry0x10 {
public:
	PeridotTraceRootEntry0x10();
	~PeridotTraceRootEntry0x10();

	void FUN_00451150();

private:
	undefined m_unk0x00[0x10]; // 0x00
};

// VTABLE: LEGORACERS 0x004b12d8
// SIZE 0x08
class PeridotTraceRootBase0x08 {
public:
	virtual void VTable0x00() = 0;                              // vtable+0x00
	virtual LegoU32 VTable0x04() = 0;                           // vtable+0x04
	virtual PeridotTraceRootEntry0x10* VTable0x08(LegoU32) = 0; // vtable+0x08

protected:
	undefined* m_unk0x04; // 0x04
};

// VTABLE: LEGORACERS 0x004b12c8
// SIZE 0x108
class PeridotTraceRoot0x108 : public PeridotTraceRootBase0x08 {
public:
	PeridotTraceRoot0x108();
	void VTable0x00() override;                              // vtable+0x00
	LegoU32 VTable0x04() override;                           // vtable+0x04
	PeridotTraceRootEntry0x10* VTable0x08(LegoU32) override; // vtable+0x08
	virtual ~PeridotTraceRoot0x108();                        // vtable+0x0c

	// SYNTHETIC: LEGORACERS 0x00450ef0
	// PeridotTraceRoot0x108::`scalar deleting destructor'

private:
	PeridotTraceRootEntry0x10 m_unk0x08[16]; // 0x08
};

#endif // PERIDOTTRACEROOT0X108_H
