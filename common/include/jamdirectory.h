#ifndef JAMDIRECTORY_H
#define JAMDIRECTORY_H

#include "decomp.h"
#include "types.h"

#define DIR_NAME_LENGHT 12

class GolStream;

// SIZE 0x24
class JamDirectory {
public:
	enum {
		c_jamEntryCountSize = 4,
		c_jamFileRecordSize = 0x14,
		c_jamDirRecordSize = 0x10,
		c_maxJamEntryCount = 100000
	};

	// SIZE 0x14
	struct JamFile {
		LegoChar m_name[DIR_NAME_LENGHT]; // 0x00
		LegoU32 m_position;               // 0x0c
		LegoU32 m_size;                   // 0x10
	};

	JamDirectory();

	void DeleteChildren();
	JamDirectory* FindDir(LegoChar* p_name, GolStream* p_stream);
	JamFile* FindFile(LegoChar* p_name, GolStream* p_stream);
	void Load(GolStream* p_stream);

	LegoChar m_name[DIR_NAME_LENGHT]; // 0x00
	LegoBool m_loaded;                // 0x0c
	undefined pad[0x10 - 0x0d];       // 0x0d
	LegoU32 m_contentsOffset;         // 0x10
	LegoU32 m_fileCount;              // 0x14
	JamFile* m_files;               // 0x18
	LegoU32 m_dirCount;               // 0x1c
	JamDirectory* m_dirs;              // 0x20
};

#endif // JAMDIRECTORY_H
