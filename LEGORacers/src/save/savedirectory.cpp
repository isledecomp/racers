#include "save/savedirectory.h"

#include "golerror.h"
#include "golstream.h"

#include <direct.h>
#include <errno.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DECOMP_SIZE_ASSERT(SaveSlot, 0x10)
DECOMP_SIZE_ASSERT(SaveDirectorySlot, 0x10)
DECOMP_SIZE_ASSERT(SaveDirectoryBase, 0x08)
DECOMP_SIZE_ASSERT(SaveDirectory, 0x108)

// GLOBAL: LEGORACERS 0x004c73f4
LegoChar g_saveCurrentDirectory[256];

// GLOBAL: LEGORACERS 0x004c74f4
LegoChar g_saveFileName[256];

// FUNCTION: LEGORACERS 0x00450eb0
SaveDirectory::SaveDirectory()
{
	m_directoryPath = NULL;
}

// FUNCTION: LEGORACERS 0x00450f10
SaveDirectorySlot::SaveDirectorySlot()
{
}

// FUNCTION: LEGORACERS 0x00450f60
SaveDirectory::~SaveDirectory()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x00450fc0
void SaveDirectory::Initialize(const LegoChar* p_path)
{
	if (m_directoryPath) {
		Clear();
	}

	m_directoryPath = new LegoChar[::strlen(p_path) + 1];
	if (!m_directoryPath) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	::strcpy(m_directoryPath, p_path);

	LegoU32 i = 0;
	for (; i < sizeOfArray(m_entries); i++) {
		m_entries[i].Initialize(this, i);
	}
}

// FUNCTION: LEGORACERS 0x00451040
void SaveDirectory::Clear()
{
	if (m_directoryPath) {
		delete[] m_directoryPath;
		m_directoryPath = NULL;
	}

	SaveSlot* entry = m_entries;
	for (LegoS32 i = 0; i < sizeOfArray(m_entries); i++, entry++) {
		entry->Reset();
	}
}

// FUNCTION: LEGORACERS 0x00451080 FOLDED
LegoU32 SaveDirectory::GetEntryCount()
{
	return 16;
}

// FUNCTION: LEGORACERS 0x00451090
SaveSlot* SaveDirectory::GetEntry(LegoU32 p_index)
{
	return &m_entries[p_index];
}

// FUNCTION: LEGORACERS 0x004510a0
SaveSlot::SaveSlot()
{
	m_directory = NULL;
	m_index = 0;
}

// FUNCTION: LEGORACERS 0x004510e0
SaveSlot::~SaveSlot()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00451130
void SaveSlot::Initialize(SaveDirectory* p_directory, LegoU32 p_index)
{
	m_directory = p_directory;
	m_index = p_index;
	EnsureDirectoryExists();
}

// FUNCTION: LEGORACERS 0x00451150
void SaveSlot::Reset()
{
	m_directory = NULL;
	m_index = 0;
}

// FUNCTION: LEGORACERS 0x00451160
LegoS32 SaveSlot::EnsureDirectoryExists()
{
	_getcwd(g_saveCurrentDirectory, sizeof(g_saveCurrentDirectory));
	BuildDirectoryPath(g_saveFileName);

	if (_chdir(g_saveFileName)) {
		CreateDirectories();
	}
	else {
		_chdir(g_saveCurrentDirectory);
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x004511c0
LegoS32 SaveSlot::CreateDirectories()
{
	_mkdir(m_directory->GetDirectoryPath());
	BuildDirectoryPath(g_saveFileName);
	_mkdir(g_saveFileName);

	return 0;
}

// FUNCTION: LEGORACERS 0x00451200
LegoS32 SaveSlot::CheckFileExists(const LegoChar* p_fileName)
{
	BuildFilePath(p_fileName, g_saveFileName);
	if (_access(g_saveFileName, 0) < 0 && errno == ENOENT) {
		return GolStream::e_ioFileNotFound;
	}

	return GolStream::e_ioSuccess;
}

// FUNCTION: LEGORACERS 0x00451240
LegoS32 SaveSlot::RemoveFile(const LegoChar* p_fileName)
{
	BuildFilePath(p_fileName, g_saveFileName);
	if (::remove(g_saveFileName) < 0) {
		if (errno == ENOENT) {
			return GolStream::e_ioFileNotFound;
		}

		return errno != EACCES ? GolStream::e_ioGenericError : GolStream::e_ioAccessDenied;
	}

	return GolStream::e_ioSuccess;
}

// FUNCTION: LEGORACERS 0x004512a0
LegoS32 SaveSlot::BuildFilePath(const LegoChar* p_fileName, LegoChar* p_buffer)
{
	BuildDirectoryPath(p_buffer);
	::strcat(p_buffer, p_fileName);

	return 0;
}

// FUNCTION: LEGORACERS 0x004512e0
LegoS32 SaveSlot::BuildDirectoryPath(LegoChar* p_buffer)
{
	::strcpy(p_buffer, m_directory->GetDirectoryPath());

	LegoU32 offset = ::strlen(p_buffer);
	if (p_buffer[offset - 1] != '\\') {
		p_buffer[offset] = '\\';
		offset++;
	}

	::itoa(m_index, &p_buffer[offset], 10);
	LegoU32 pathLength = ::strlen(p_buffer);
	p_buffer[pathLength] = '\\';
	p_buffer[pathLength + 1] = 0;

	return 0;
}
