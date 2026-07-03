#include "golimgfilewriter.h"

#include "golerror.h"

#include <stdio.h>
#include <string.h>

DECOMP_SIZE_ASSERT(GolImgFileWriter, 0x5b4)

// FUNCTION: LEGORACERS 0x0040d2a0
GolImgFileWriter::GolImgFileWriter()
{
	m_filePath = NULL;
}

// FUNCTION: LEGORACERS 0x0040d2e0
GolImgFileWriter::~GolImgFileWriter()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0040d330
void GolImgFileWriter::Open(const LegoChar* p_fileName)
{
	LegoChar buffer[256];
	LegoS32 dotIndex = -1;
	LegoU32 lenFileName = 0;

	while (p_fileName[lenFileName]) {
		if (p_fileName[lenFileName] == '.') {
			dotIndex = lenFileName;
		}

		lenFileName++;
	}

	if (dotIndex < 0) {
		const LegoChar* suffix = GetSuffix();

		lenFileName += strlen(suffix);
		m_filePath = new LegoChar[lenFileName + 1];
		if (!m_filePath) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		strcpy(m_filePath, p_fileName);
		strcat(m_filePath, suffix);
	}
	else {
		m_filePath = new LegoChar[lenFileName + 1];
		if (!m_filePath) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		strcpy(m_filePath, p_fileName);
	}

	LegoS32 result = m_file.BufferedOpen(m_filePath, GolStream::c_modeCreate | GolStream::c_modeWrite, 0x1000);
	if (result != GolStream::e_ioSuccess) {
		strcpy(buffer, GolStream::ErrorCodeToString(result));
		strcat(buffer, "\nFile: ");
		strcat(buffer, m_filePath);
		GOL_FATALERROR_MESSAGE(buffer);
	}
}

// FUNCTION: LEGORACERS 0x0040d4f0
void GolImgFileWriter::Destroy()
{
	if (m_filePath) {
		delete[] m_filePath;
		m_filePath = NULL;
	}

	if (m_file.IsOpen()) {
		m_file.Dispose();
	}
}
