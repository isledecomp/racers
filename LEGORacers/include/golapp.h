#ifndef GOLAPP_H
#define GOLAPP_H

#include "decomp.h"
#include "golfile.h"
#include "golfilesource.h"
#include "golhashtable.h"
#include "types.h"

class CactusInterface0x4;
class BronzeFalcon0xc8770;
class GolDrawState;
class GolExport;
class InputManager;

// VTABLE: LEGORACERS 0x004af9a8
// SIZE 0x830
class GolApp {
public:
	enum {
		c_flagInitialized = 1 << 0,
		c_flagDisplayActive = 1 << 1,
		c_flagBit2 = 1 << 2,
		c_flagFullscreen = 1 << 3,
		c_flagBit4 = 1 << 4,
		c_flagBit5 = 1 << 5,
		c_flagBit6 = 1 << 6,
		c_flagPrimaryDriver = 1 << 7,
		c_flagBit8 = 1 << 8,
		c_flagSelect3DDevice = 1 << 9,
		c_flagBit10 = 1 << 10,
		c_flagBit12 = 1 << 12,
		c_flagBit13 = 1 << 13,
		c_flagAlphaTransparency = 1 << 15,
		c_flagBit17 = 1 << 17,
	};

	GolApp();
	virtual LegoU32 BuildDrawStateFlags(LegoU32) = 0;              // vtable+0x00
	virtual ~GolApp();                                             // vtable+0x04
	virtual void PresentFrame();                                   // vtable+0x08
	virtual void Initialize(const LegoChar*, const LegoChar*) = 0; // vtable+0x0c
	virtual void Destroy() = 0;                                    // vtable+0x10
	virtual void LoadGolLibrary() = 0;                             // vtable+0x14
	virtual void UnloadGolLibrary() = 0;                           // vtable+0x18
	virtual void InitializeInput() = 0;                            // vtable+0x1c
	virtual void ShutdownInput() = 0;                              // vtable+0x20
	virtual LegoS32 InitializeDisplay(
		LegoU32 p_width,
		LegoU32 p_height,
		LegoU32 p_bpp,
		LegoU32 p_flags
	) = 0; // vtable+0x24
	virtual void InitializeDisplayWithDevice(
		LegoU32 p_width,
		LegoU32 p_height,
		LegoU32 p_bpp,
		LegoU32 p_flags,
		const LegoChar* p_driverName,
		const LegoChar* p_deviceName
	);                                                            // vtable+0x28
	virtual void ShutdownDisplay() = 0;                           // vtable+0x2c
	virtual void ToggleFullscreen() = 0;                          // vtable+0x30
	virtual LegoS32 Tick(CactusInterface0x4* p_eventHandler) = 0; // vtable+0x34
	virtual InputManager* GetInputManager() = 0;                  // vtable+0x38

	// SYNTHETIC: LEGORACERS 0x004163b0
	// GolApp::`scalar deleting destructor'

	LegoU32 GetFlags() { return m_flags; }
	LegoU32 GetFrameDeltaMs() { return m_frameDeltaMs; }
	GolHashTable& GetHashTable() { return m_hashTable; }
	GolDrawState* GetDrawState() { return m_golDrawState; }

	void ResetRuntimeState();
	void NotifyCloseRequested();
	void ClearFileSourceDirectoryCaches();

protected:
	LegoU32 m_flags;                    // 0x04
	GolFile m_files[20];                // 0x08
	GolFileSource m_fileSources[20];    // 0x3c8
	LegoU32 m_fileSourceCount;          // 0x7d8
	GolHashTable m_hashTable;           // 0x7dc
	GolExport* m_golExport;             // 0x800
	GolDrawState* m_golDrawState;       // 0x804
	undefined4 m_unk0x808;              // 0x808
	BronzeFalcon0xc8770* m_renderer;    // 0x80c
	LegoU32 m_width;                    // 0x810
	LegoU32 m_height;                   // 0x814
	LegoU32 m_bpp;                      // 0x818
	CactusInterface0x4* m_eventHandler; // 0x81c
	LegoU32 m_lastFrameTimeMs;          // 0x820
	LegoU32 m_frameDeltaMs;             // 0x824
	LegoU32 m_maxFrameDeltaMs;          // 0x828
	LegoBool32 m_disabled;              // 0x82c
};

#endif // GOLAPP_H
