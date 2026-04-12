#ifndef GOLFILESOURCE_H
#define GOLFILESOURCE_H

#include "azureclip0x24.h"
#include "decomp.h"
#include "types.h"

class GolStream;

// VTABLE: LEGORACERS 0x4b0f70
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

	// SYNTHETIC: LEGORACERS 0x44d840
	// GolFileSource::`scalar deleting destructor'

	void Reset();

private:
	GolStream* m_stream;     // 0x04
	LegoU32 m_state;         // 0x08
	AzureClip0x24 m_unk0x0c; // 0x0c
	LegoU32 m_unk0x30;       // 0x30
};

#endif // GOLFILESOURCE_H
