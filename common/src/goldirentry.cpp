#include "goldirentry.h"

#include <string.h>

DECOMP_SIZE_ASSERT(GolDirEntry, 0x24)
DECOMP_SIZE_ASSERT(GolDirEntry::FileEntry, 0x14)

// FUNCTION: LEGORACERS 0x0044dbe0
GolDirEntry::GolDirEntry()
{
	m_name[0] = '\0';
	m_loaded = 0;
	m_unk0x10 = 4;
	m_fileCount = 0;
	m_files = NULL;
	m_dirCount = 0;
	m_dirs = NULL;
}

// FUNCTION: LEGORACERS 0x0044dc00
void GolDirEntry::DeleteChildren()
{
	m_loaded = 0;

	if (m_dirs) {
		for (LegoU32 i = 0; i < m_dirCount; i++) {
			m_dirs[i].DeleteChildren();
		}

		delete m_dirs;
		m_dirs = NULL;
		m_dirCount = 0;
	}

	if (m_files) {
		delete m_files;
		m_files = NULL;
		m_fileCount = 0;
	}
}

// FUNCTION: LEGORACERS 0x0044dc60
GolDirEntry* GolDirEntry::FindDir(LegoChar* p_name, GolStream* p_stream)
{
	if (!m_loaded) {
		Load(p_stream);
	}

	for (LegoU32 i = 0; i < m_dirCount; i++) {
		if (!strncmp(m_dirs[i].m_name, p_name, GOL_NAME_LENGTH)) {
			return &m_dirs[i];
		}
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x0044dcc0
GolDirEntry::FileEntry* GolDirEntry::FindFile(LegoChar* p_name, GolStream* p_stream)
{
	if (!m_loaded) {
		Load(p_stream);
	}

	for (LegoU32 i = 0; i < m_fileCount; i++) {
		if (!strncmp(m_files[i].m_name, p_name, GOL_NAME_LENGTH)) {
			return &m_files[i];
		}
	}

	return NULL;
}

// STUB: LEGORACERS 0x0044dd20
void GolDirEntry::Load(GolStream*)
{
	// TODO: load directory/file entries from stream
	STUB(0x44dd20);
}
