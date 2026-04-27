#include "audio/sounddata.h"

#include "audio/audiohelpers.h"
#include "decomp.h"
#include "golfile.h"
#include "golstream.h"

#include <string.h>

DECOMP_SIZE_ASSERT(SoundData, 0x14)
DECOMP_SIZE_ASSERT(SoundData::Header, 0x18)

// FUNCTION: LEGORACERS 0x0041aa00
SoundData::SoundData()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0041aa10
SoundData::~SoundData()
{
	Release();
}

// FUNCTION: LEGORACERS 0x0041aa20
void SoundData::Reset()
{
	m_bitsPerSample = c_defaultBitsPerSample;
	m_loaded = FALSE;
	m_channelCount = c_defaultChannelCount;
	m_sampleRate = c_defaultSampleRate;
	m_shift = 0;
	m_decodedSize = 0;
	m_data = NULL;
	m_dataSize = 0;
}

// FUNCTION: LEGORACERS 0x0041aa40
void SoundData::Release()
{
	if (m_data) {
		operator delete(m_data);
	}

	Reset();
}

// FUNCTION: LEGORACERS 0x0041aa60
LegoBool32 SoundData::Load(const LegoChar* p_path)
{
	LegoS32 bytesRead;
	LegoBool32 loaded = FALSE;
	GolFile file;

	Release();

	if (file.BufferedOpen(p_path, GolStream::c_modeRead, c_fileBufferSize)) {
		return FALSE;
	}

	LegoU32 fileSize = file.GetSize();
	Header header;
	LegoS32 dataOffset;
	file.BufferedRead(0, &header, sizeof(header), &bytesRead);

	if (bytesRead < sizeof(header)) {
		memset((LegoU8*) &header + bytesRead, 0, sizeof(header) - bytesRead);
	}

	m_loaded = TRUE;

	if (header.m_magic == c_magic && header.m_formatMagic == c_formatAdpc) {
		m_channelCount = header.m_channelCount;
		dataOffset = header.m_dataOffset + 8;

		if (dataOffset > c_legacyAdpcmHeaderSize) {
			m_sampleRate = header.m_sampleRate;
			if (header.m_sampleRate <= c_defaultSampleRate) {
				m_shift = 1;
			}
			else {
				m_shift = 0;
			}
		}
		else {
			m_sampleRate = c_defaultSampleRate;
			if (m_channelCount != c_defaultChannelCount) {
				m_shift = 0;
			}
			else {
				m_shift = 1;
			}
		}
	}
	else {
		dataOffset = 0;
		m_channelCount = c_defaultChannelCount;
		m_shift = 1;
		m_sampleRate = c_defaultSampleRate;
	}

	m_dataSize = (fileSize - dataOffset) & ~3;
	m_data = new LegoU8[m_dataSize];

	if (m_data) {
		file.BufferedRead(dataOffset, m_data, m_dataSize, &bytesRead);
		loaded = m_dataSize == (LegoU32) bytesRead;
	}
	else {
		m_dataSize = 0;
	}

	m_decodedSize = 4 * m_dataSize;
	file.Dispose();

	if (m_channelCount < 1 || m_channelCount > 2) {
		loaded = FALSE;
	}

	if (!loaded) {
		Release();
	}

	return loaded;
}

// FUNCTION: LEGORACERS 0x0041ac20
void SoundData::Decode(LegoS16* p_destination)
{
	LegoU8* data = m_data;
	LegoS32 leftState[2] = {0, 0};

	if (data && m_loaded == TRUE) {
		if (m_channelCount == 1) {
			LegoU8 shift = m_shift;
			if (shift) {
				DecodeMonoPcmToStereoInterpolated((LegoChar*) data, p_destination, m_dataSize, leftState);
				return;
			}

			DecodeMonoPcmToMono(data, p_destination, m_dataSize, leftState);
			return;
		}
		else if (m_channelCount == 2) {
			LegoS32 rightState[2] = {0, 0};
			DecodeStereoPcmToStereo(data, p_destination, m_dataSize, leftState, rightState);
		}
	}
}
