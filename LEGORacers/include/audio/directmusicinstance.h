#ifndef DIRECTMUSICINSTANCE_H
#define DIRECTMUSICINSTANCE_H

#include "audio/directmusicstream.h"

// VTABLE: LEGORACERS 0x004afb34
// SIZE 0x417c
class DirectMusicInstance : public DirectMusicStream {
public:
	enum {
		c_pathLength = 260,
		c_streamScratchSize = 0x4000,
		c_adpcmMagic = 0x20504c41,
		c_adpcmFormat = 0x43504441,
		c_adpcmHeaderSize = 0x10,
		c_readChunkSize = 0x4000,
		c_prefillBlockSize = 2048,
		c_invalidFileHandle = -1,
		c_lostBuffer = DSERR_BUFFERLOST
	};

	// SIZE 0x10
	struct AdpcmHeader {
		LegoU32 m_magic;               // 0x00
		LegoU32 m_dataOffset;          // 0x04
		LegoU32 m_format;              // 0x08
		LegoU8 m_padding[0x0f - 0x0c]; // 0x0c
		LegoU8 m_channelCount;         // 0x0f
	};

	DirectMusicInstance();
	~DirectMusicInstance() override;               // vtable+0x00
	LegoBool32 Play(LegoBool32 p_loop) override;   // vtable+0x04
	void Stop() override;                          // vtable+0x08
	void Pause() override;                         // vtable+0x0c
	void Resume() override;                        // vtable+0x10
	LegoBool32 IsPlaying() override;               // vtable+0x14
	void VTable0x1c(undefined4 p_arg) override;    // vtable+0x1c
	void VTable0x20(undefined4 p_arg) override;    // vtable+0x20
	void ReleaseResources() override;              // vtable+0x24
	LegoS32 FillBuffer(LegoS32 p_blocks) override; // vtable+0x2c
	void Service() override;                       // vtable+0x30

	LegoBool32 SetPath(const LegoChar* p_path);

	// SYNTHETIC: LEGORACERS 0x00419720
	// DirectMusicInstance::`scalar deleting destructor'

private:
	void StopBuffer();
	void CloseFile();
	LegoBool32 OpenFileAndPlay(LegoBool p_play);
	void PauseDirectSoundBuffer();
	void ResumeDirectSoundBuffer();

	HANDLE m_file;                 // 0x44
	LegoS32 m_fileSize;            // 0x48
	LegoChar m_path[c_pathLength]; // 0x4c
	LegoBool32 m_restartRequested; // 0x150
	LegoU32 m_sourceChannelCount;  // 0x154
	LegoU32 m_dataStart;           // 0x158
	LegoS32 m_loopCount;           // 0x15c
	LegoS32 m_remainingBytes;      // 0x160
	LegoS32 m_writeCursor;         // 0x164
	LegoS32 m_silenceBytes;        // 0x168
	LegoS32 m_leftState[2];        // 0x16c
	LegoS32 m_rightState[2];       // 0x174
	union {
		AdpcmHeader m_adpcmHeader;                  // 0x17c
		LegoU8 m_streamBuffer[c_streamScratchSize]; // 0x17c
	};
};

#endif // DIRECTMUSICINSTANCE_H
