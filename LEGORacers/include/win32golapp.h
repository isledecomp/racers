#ifndef WIN32GOLAPP_H
#define WIN32GOLAPP_H

#include "bronzefalcon0xc8770.h"
#include "compat.h"
#include "decomp.h"
#include "gol.h"
#include "golapp.h"
#include "input/directinputmanager.h"
#include "racers_resource.h"
#include "types.h"

#include <windows.h>

class CactusInterface0x4;

// VTABLE: LEGORACERS 0x004af9f4
// SIZE 0x944
class Win32GolApp : public GolApp {
public:
	Win32GolApp();
	LegoU32 BuildDrawStateFlags(LegoU32 p_flags) override; // vtable+0x00
	~Win32GolApp() override;                               // vtable+0x04
	void Init(const LegoChar*, const LegoChar*) override;  // vtable+0x0c
	void Destroy() override;                               // vtable+0x10
	void LoadGolLibrary() override;                        // vtable+0x14
	void UnloadGolLibrary() override;                      // vtable+0x18
	void InitInput() override;                             // vtable+0x1c
	void ShutdownInput() override;                         // vtable+0x20
	LegoS32 InitializeDisplay(
		LegoU32 p_width,
		LegoU32 p_height,
		LegoU32 p_bpp,
		LegoU32 p_flags
	) override; // vtable+0x24
	void InitializeDisplayWithDevice(
		LegoU32 p_width,
		LegoU32 p_height,
		LegoU32 p_bpp,
		LegoU32 p_flags,
		const LegoChar* p_driverName,
		const LegoChar* p_deviceName
	) override;                                                // vtable+0x28
	void ShutdownDisplay() override;                           // vtable+0x2c
	void ToggleFullscreen() override;                          // vtable+0x30
	LegoS32 Tick(CactusInterface0x4* p_eventHandler) override; // vtable+0x34
	InputManager* GetInputManager() override;                  // vtable+0x38
	virtual void OnAppDeactivated();                           // vtable+0x3c
	virtual void OnAppActivated();                             // vtable+0x40

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
	// Win32GolApp::`scalar deleting destructor'

	LegoU32 GetGolBackendType() { return m_golBackendType; }
	void SetGolBackendType(LegoU32 p_golBackendType) { m_golBackendType = p_golBackendType; }
	GolExport* GetGolExport() { return m_golExport; }
	BronzeFalcon0xc8770* GetRenderer() { return m_renderer; }
	HWND GetHwnd() { return m_hWnd; }
	LegoU32 GetWindowMode() { return m_windowMode; }
	LegoBool32 IsDisabled() { return m_disabled; }

	void AddFileSourcesFromList(const LegoChar* p_fileList);
	LegoBool32 IsCursorInClientArea(HWND p_hWnd);
	void ChangeWindowState(LegoU32 p_mode);

private:
	static LRESULT CALLBACK AppWndProc(HWND p_hWnd, UINT p_msg, WPARAM p_wParam, LPARAM p_lParam);

	void UpdateMousePosition();

	HMODULE m_golLibrary;              // 0x830
	DirectInputManager m_inputManager; // 0x834
	HWND m_hWnd;                       // 0x924
	LegoU32 m_golBackendType;          // 0x928
	LegoU32 m_windowMode;              // 0x92c
	LegoBool32 m_windowStateChanging;  // 0x930
	HCURSOR m_hCursor;                 // 0x934
	undefined4 m_pollInput;            // 0x938
	DWORD m_fullscreenStyle;           // 0x93c
	DWORD m_windowedStyle;             // 0x940
};

#endif // WIN32GOLAPP_H
