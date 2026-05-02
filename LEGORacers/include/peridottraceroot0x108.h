#ifndef PERIDOTTRACEROOT0X108_H
#define PERIDOTTRACEROOT0X108_H

#include "compat.h"
#include "decomp.h"
#include "types.h"

class PeridotTraceRoot0x108;

// SIZE 0x10
class PeridotTraceRootEntry0x10 {
public:
	PeridotTraceRootEntry0x10();
	~PeridotTraceRootEntry0x10();

	void Reset();

private:
	undefined m_unk0x00[0x08 - 0x00]; // 0x00
	PeridotTraceRoot0x108* m_root;    // 0x08
	LegoU32 m_index;                  // 0x0c
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

	// SYNTHETIC: LEGORACERS 0x00450ef0
	// PeridotTraceRoot0x108::`scalar deleting destructor'

private:
	PeridotTraceRootEntry0x10 m_entries[16]; // 0x08
};

#endif // PERIDOTTRACEROOT0X108_H
