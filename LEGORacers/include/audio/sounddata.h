#ifndef SOUNDDATA_H
#define SOUNDDATA_H

#include "types.h"

// SIZE 0x14
class SoundData {
public:
	enum {
		c_magic = 0x20504c41,
		c_formatAdpc = 0x43504441,
		c_headerSize = 0x18,
		c_legacyAdpcmHeaderSize = 0x10,
		c_defaultSampleRate = 11025,
		c_defaultChannelCount = 1,
		c_defaultBitsPerSample = 16,
		c_fileBufferSize = 0x1000
	};

	// SIZE 0x18
	struct Header {
		LegoU32 m_magic;       // 0x00
		LegoS32 m_dataOffset;  // 0x04
		LegoU32 m_formatMagic; // 0x08
		LegoU8 m_unk0x0c[3];   // 0x0c
		LegoU8 m_channelCount; // 0x0f
		LegoS32 m_sampleRate;  // 0x10
		LegoU8 m_unk0x14[4];   // 0x14
	};

	SoundData();
	~SoundData();

	void Reset();
	void Release();
	LegoBool32 Load(const LegoChar* p_path);
	void Decode(LegoS16* p_destination);

	LegoBool IsLoaded() { return m_loaded; }
	LegoU8 GetBitsPerSample() { return m_bitsPerSample; }
	LegoU8 GetChannelCount() { return m_channelCount; }
	LegoU8 GetShift() { return m_shift; }
	LegoU32 GetDecodedSize() { return m_decodedSize; }
	LegoS32 GetSampleRate() { return m_sampleRate; }
	LegoU8* GetData() { return m_data; }

private:
	LegoBool m_loaded;      // 0x00
	LegoU8 m_bitsPerSample; // 0x01
	LegoU8 m_channelCount;  // 0x02
	LegoU8 m_shift;         // 0x03
	LegoU32 m_decodedSize;  // 0x04
	LegoS32 m_sampleRate;   // 0x08
	LegoU8* m_data;         // 0x0c
	LegoU32 m_dataSize;     // 0x10
};

#endif // SOUNDDATA_H
