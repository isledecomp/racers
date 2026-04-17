#ifndef GOLFILESOURCE_H
#define GOLFILESOURCE_H

#include "decomp.h"
#include "goldirentry.h"
#include "types.h"

class GolStream;

// VTABLE: LEGORACERS 0x004b0f70
// SIZE 0x34
class GolFileSource {
public:
	GolFileSource();

	virtual LegoS32 Open(LegoChar* p_fileName, LegoS32* p_position, LegoS32* p_size); // vtable+0x00
	virtual LegoS32 Close();                                                          // vtable+0x04
	virtual LegoS32 Read(
		LegoU32 p_offset,
		void* p_buf,
		LegoU32 p_size,
		LegoU32 p_maxSize,
		LegoS32* p_lenRead
	);                                                                                              // vtable+0x08
	virtual LegoS32 ForwardRead(LegoU32 p_offset, void* p_buf, LegoU32 p_size, LegoS32* p_lenRead); // vtable+0x0c
	virtual ~GolFileSource();                                                                       // vtable+0x10
	virtual LegoS32 Find(LegoChar* p_fileName);                                                     // vtable+0x14

	// SYNTHETIC: LEGORACERS 0x0044d840
	// GolFileSource::`scalar deleting destructor'

	GolStream* GetStream() { return m_stream; }

	void FUN_0044d870(GolStream* p_unk0x04);
	void Reset();

private:
	GolStream* m_stream;                  // 0x04
	LegoU32 m_state;                      // 0x08
	GolDirEntry m_rootDir;                // 0x0c
	GolDirEntry::FileEntry* m_foundEntry; // 0x30
};

#endif // GOLFILESOURCE_H
