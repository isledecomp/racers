#ifndef GOLDIRENTRY_H
#define GOLDIRENTRY_H

#include "decomp.h"
#include "types.h"

#define GOL_NAME_LENGTH 12

class GolStream;

// SIZE 0x24
class GolDirEntry {
public:
	// SIZE 0x14
	struct FileEntry {
		LegoChar m_name[GOL_NAME_LENGTH]; // 0x00
		LegoS32 m_position;               // 0x0c
		LegoS32 m_size;                   // 0x10
	};

	GolDirEntry();

	void DeleteChildren();
	GolDirEntry* FindDir(LegoChar* p_name, GolStream* p_stream);
	FileEntry* FindFile(LegoChar* p_name, GolStream* p_stream);
	void Load(GolStream* p_stream);

	LegoChar m_name[GOL_NAME_LENGTH]; // 0x00
	undefined m_loaded;               // 0x0c
	undefined m_unk0x0d[0x10 - 0x0d]; // 0x0d
	LegoU32 m_unk0x10;                // 0x10
	LegoU32 m_fileCount;              // 0x14
	FileEntry* m_files;               // 0x18
	LegoU32 m_dirCount;               // 0x1c
	GolDirEntry* m_dirs;              // 0x20
};

#endif // GOLDIRENTRY_H
