#ifndef IRONFLAME0X944_H
#define IRONFLAME0X944_H

#include "compat.h"
#include "crimsonforge0x800.h"
#include "decomp.h"
#include "gol.h"
#include "opalvault0xf0.h"
#include "racers_resource.h"
#include "types.h"

#include <windows.h>

class CactusInterface0x4;

// VTABLE: LEGORACERS 0x004af9f4
// SIZE 0x944
class IronFlame0x944 : public CrimsonForge0x800 {
public:
	IronFlame0x944();
	LegoU32 VTable0x00(LegoU32 p_flags) override;         // vtable+0x00
	~IronFlame0x944() override;                           // vtable+0x04
	void Init(const LegoChar*, const LegoChar*) override; // vtable+0x0c
	void Destroy() override;                              // vtable+0x10
	void LoadGolLibrary() override;                       // vtable+0x14
	void UnloadGolLibrary() override;                     // vtable+0x18
	void InitInput() override;                            // vtable+0x1c
	void VTable0x20() override;                           // vtable+0x20
	LegoS32 VTable0x24(LegoU32 p_width, LegoU32 p_height, LegoU32 p_bpp,
					   LegoU32 p_flags) override; // vtable+0x24
	void VTable0x28(
		LegoU32 p_width,
		LegoU32 p_height,
		LegoU32 p_bpp,
		LegoU32 p_flags,
		const LegoChar* p_driverName,
		const LegoChar* p_deviceName
	) override;                                            // vtable+0x28
	void VTable0x2c() override;                            // vtable+0x2c
	void VTable0x30() override;                            // vtable+0x30
	LegoS32 Tick(CactusInterface0x4* p_unk0x81c) override; // vtable+0x34
	OpalVault0xf0* VTable0x38() override;                  // vtable+0x38
	virtual void VTable0x3c();                             // vtable+0x3c
	virtual void VTable0x40();                             // vtable+0x40

	enum {
		c_golBackendDP = 0x0,
		c_golBackendSoft = 0x1,
		c_golBackendGlide = 0x2,
		c_golBackendD3D = 0x4,
	};

	enum {
		c_minFrameDeltaMs = 12, // Tick caps frame rate at ~83 FPS
	};

	enum {
		c_windowModeNone = 0,
		c_windowModeFullscreen = 1,
		c_windowModeWindowed = 2,
		c_windowModeMinimized = 3,
	};

	// SYNTHETIC: LEGORACERS 0x00416560
	// IronFlame0x944::`scalar deleting destructor'

	LegoU32 GetGolBackendType() { return m_golBackendType; }
	void SetGolBackendType(LegoU32 p_golBackendType) { m_golBackendType = p_golBackendType; }

	void FUN_00416460();
	void FUN_00416860(const LegoChar* p_unk0x04);
	LegoBool32 FUN_00416d20(HWND p_hWnd);

private:
	static LRESULT CALLBACK AppWndProc(HWND p_hWnd, UINT p_msg, WPARAM p_wParam, LPARAM p_lParam);

	void FUN_00416db0();
	void ChangeWindowState(LegoU32 p_mode);

	GolExport* m_golExport;         // 0x800
	GolDrawState* m_golDrawState;   // 0x804
	undefined4 m_unk0x808;          // 0x808
	GolHashTable* m_hashTable;      // 0x80c
	LegoU32 m_width;                // 0x810
	LegoU32 m_height;               // 0x814
	LegoU32 m_bpp;                  // 0x818
	CactusInterface0x4* m_unk0x81c; // 0x81c
	DWORD m_lastFrameTimeMs;        // 0x820
	LegoU32 m_frameDeltaMs;         // 0x824
	LegoU32 m_maxFrameDeltaMs;      // 0x828
	LegoBool32 m_disabled;          // 0x82c
	HMODULE m_golLibrary;           // 0x830
	OpalVault0xf0 m_unk0x834;       // 0x834
	HWND m_hWnd;                    // 0x924
	LegoU32 m_golBackendType;       // 0x928
	LegoU32 m_windowMode;           // 0x92c
	undefined4 m_unk0x930;          // 0x930
	HCURSOR m_hCursor;              // 0x934
	undefined4 m_unk0x938;          // 0x938
	DWORD m_fullscreenStyle;        // 0x93c
	DWORD m_windowedStyle;          // 0x940
};

#endif // IRONFLAME0X944_H
