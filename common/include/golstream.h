#ifndef GOLSTREAM_H
#define GOLSTREAM_H

#include "decomp.h"
#include "types.h"

#include <ctype.h>

class GolHashTable;
class GolFileSource;

extern LegoChar g_pathBuffer[256];
extern LegoChar* g_searchPaths[4];
extern GolFileSource* g_fileSources;
extern LegoU32 g_fileSourceCount;
extern LegoU32 g_searchPathCount;
extern GolHashTable* g_hashTable;

// VTABLE: GOLDP 0x10057884
// VTABLE: LEGORACERS 0x004b0f38
// SIZE 0x30
class GolStream {
public:
	enum {
		c_dosEof = 0x1a,
		c_lineReadChunkSize = 0x40,
		c_maxReadChunkSize = 0x100000
	};

	enum {
		c_modeCreate = 0x01,
		c_modeRead = 0x02,
		c_modeWrite = 0x04,
		c_modeTextAppend = 0x08,
		c_modeExclusive = 0x10,
		c_modeKeepBuffer = 0x20,
		c_unk0x40 = 0x40
	};

	enum {
		c_flagOpen = 0x01,
		c_flagMapped = 0x02,
		c_flagCached = 0x04,
		c_flagDirty = 0x08
	};

	enum {
		e_ioSuccess = 0,
		e_ioGenericError = 1,
		e_ioBadParameter = 3,
		e_ioOutOfMemory = 4,
		e_ioNameTooLong = 6,
		e_ioNotOpen = 7,
		e_ioFileNotFound = 8,
		e_ioAccessDenied = 9,
		e_ioFileExists = 10,
		e_ioTooManyFiles = 11,
		e_ioReadError = 13,
		e_ioWriteError = 14,
		e_ioSeekError = 15,
		e_ioEndOfFile = 16
	};

	GolStream();

	virtual LegoS32 Open(LegoChar* p_fileName) = 0;                                                  // vtable+0x00
	virtual LegoS32 Close() = 0;                                                                     // vtable+0x04
	virtual LegoS32 Seek(LegoS32 p_offset) = 0;                                                      // vtable+0x08
	virtual LegoS32 Read(void* p_buf, LegoU32 p_size, LegoS32* p_lenRead) = 0;                       // vtable+0x0c
	virtual LegoS32 Write(void* p_buf, LegoU32 p_size);                                              // vtable+0x10
	virtual LegoS32 Flush();                                                                         // vtable+0x14
	virtual ~GolStream();                                                                            // vtable+0x18
	virtual LegoS32 BufferedOpen(const LegoChar* p_fileName, LegoS32 p_mode, LegoU32 p_bufferSize);  // vtable+0x1c
	virtual LegoS32 Dispose();                                                                       // vtable+0x20
	virtual LegoS32 BufferedRead(LegoU32 p_offset, void* p_buf, LegoU32 p_size, LegoS32* p_lenRead); // vtable+0x24
	virtual LegoS32 ReadLine(void* p_buf, LegoU32 p_size);                                           // vtable+0x28
	virtual LegoS32 BufferedWrite(LegoS32 p_offset, const void* p_buf, LegoU32 p_size);              // vtable+0x2c
	virtual LegoS32 WriteLine(const void* p_buf, LegoU32 p_size);                                    // vtable+0x30
	virtual LegoS32 FlushWriteBuffer();                                                              // vtable+0x34

	// SYNTHETIC: GOLDP 0x100314d0
	// SYNTHETIC: LEGORACERS 0x0044c940
	// GolStream::`scalar deleting destructor'

	void Initialize();
	LegoS32 OpenFileSource();

	static LegoS32 FindFile(const LegoChar* p_fileName);
#ifdef BUILDING_GOL
	static void FUN_100320d0();
	static void FUN_10032110(const LegoChar* p_arg1);
#endif

	static const LegoChar* ErrorCodeToString(LegoS32 p_code);
	static void TransformToUpper(LegoChar* p_str);
	static LegoS32 IsAbsolutePath(const LegoChar* p_path);
	static void BuildPathname(const LegoChar* p_prefix, const LegoChar* p_path);
	LegoU32 GetFlags() const { return m_flags; }
	LegoS32 GetSize() { return m_size; }

	LegoBool IsOpen() const { return m_flags & c_flagOpen; }

protected:
	LegoU32 m_mode;           // 0x04
	LegoU32 m_flags;          // 0x08
	LegoS32 m_position;       // 0x0c
	LegoU32 m_unk0x10;        // 0x10
	LegoS32 m_size;           // 0x14
	LegoU32 m_bufferCapacity; // 0x18
	LegoU32 m_bufferStart;    // 0x1c
	LegoU32 m_bufferEnd;      // 0x20
	LegoU8* m_buffer;         // 0x24
	LegoS32 m_handle;         // 0x28
	LegoS32 m_fd;             // 0x2c
};

#endif // GOLSTREAM_H
