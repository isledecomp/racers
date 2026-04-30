#ifndef GOLFILE_H
#define GOLFILE_H

#include "compat.h"
#include "decomp.h"
#include "golstream.h"

// VTABLE: GOLDP 0x10057934
// VTABLE: LEGORACERS 0x004b1250
// SIZE 0x30
class GolFile : public GolStream {
public:
	GolFile();
	~GolFile() override; // vtable+0x18

	static LegoS32 Exists(const LegoChar* p_fileName);

	LegoS32 Open(LegoChar* p_fileName) override;                            // vtable+0x00
	LegoS32 Close() override;                                               // vtable+0x04
	LegoS32 Seek(LegoS32 p_offset) override;                                // vtable+0x08
	LegoS32 Read(void* p_buf, LegoU32 p_size, LegoS32* p_lenRead) override; // vtable+0x0c
	LegoS32 Write(void* p_buf, LegoU32 p_size) override;                    // vtable+0x10
	LegoS32 Flush() override;                                               // vtable+0x14

	// SYNTHETIC: GOLDP 0x100328e0
	// SYNTHETIC: LEGORACERS 0x00450ab0
	// GolFile::`scalar deleting destructor'
};

#endif // GOLFILE_H
