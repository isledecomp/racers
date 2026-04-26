#include "win32golapp.h"

#include "../../GolDP/include/gol.h"
#include "../../GolDP/include/golcommondrawstate.h"
#include "cactusinterface0x4.h"
#include "gol.h"
#include "golerror.h"
#include "golfsutil.h"
#include "golstream.h"
#include "input/directinputmanager.h"
#include "input/mousedevice.h"

#include <mmsystem.h>
#include <stdio.h>
#include <string.h>

extern HINSTANCE g_hInstance;
extern HINSTANCE g_hPrevInstance;

DECOMP_SIZE_ASSERT(Win32GolApp, 0x944)

// FUNCTION: LEGORACERS 0x004164d0
Win32GolApp::Win32GolApp()
{
	m_golLibrary = NULL;
	m_golExport = NULL;
	m_hWnd = 0;
	m_golBackendType = c_golBackendDP;
	m_windowMode = c_windowModeNone;
	m_hCursor = 0;
	m_fullscreenStyle = 0;
	m_windowedStyle = 0;
	m_windowStateChanging = FALSE;
	m_pollInput = 1;
}

// FUNCTION: LEGORACERS 0x00416580
Win32GolApp::~Win32GolApp()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004165e0
void Win32GolApp::Init(const LegoChar* p_windowName, const LegoChar* p_fileName)
{
	LegoChar buffer[64];

	if (m_flags & c_flagInitialized) {
		Destroy();
	}

	if (!g_hPrevInstance) {
		WNDCLASS wndClass;
		wndClass.style = CS_HREDRAW | CS_VREDRAW;
		wndClass.lpfnWndProc = AppWndProc;
		wndClass.cbClsExtra = 0;
		wndClass.cbWndExtra = 4;
		wndClass.hInstance = g_hInstance;
		wndClass.hIcon = LoadIcon(g_hInstance, MAKEINTRESOURCE(ICON_RACERS));

		if (!wndClass.hIcon) {
			::sprintf(buffer, "Unable to load app icon\nError = 0x%x", GetLastError());
			GOL_FATALERROR_MESSAGE(buffer);
		}

		wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndClass.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
		wndClass.lpszMenuName = NULL;
		wndClass.lpszClassName = "AolAppWinClass";

		if (!RegisterClass(&wndClass)) {
			::sprintf(buffer, "Unable to register app window class\nError = 0x%x", GetLastError());
			GOL_FATALERROR_MESSAGE(buffer);
		}

		g_hPrevInstance = g_hInstance;
	}

	g_hashTable = &GolApp::GetHashTable();

	if (p_fileName) {
		AddFileSourcesFromList(p_fileName);
	}

	m_fullscreenStyle = WS_POPUP | WS_CLIPCHILDREN;
	m_windowedStyle = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;
	m_hWnd = CreateWindowEx(
		0,
		"AolAppWinClass",
		p_windowName,
		WS_POPUP | WS_CLIPCHILDREN,
		0,
		0,
		0,
		0,
		NULL,
		NULL,
		g_hInstance,
		NULL
	);

	if (!m_hWnd) {
		GOL_FATALERROR_MESSAGE("Unable to create application window");
	}

	LoadGolLibrary();
	InitInput();
	m_golDrawState->VTable0x08(m_hWnd);
	SetWindowLong(m_hWnd, 0, (LONG) this);
	ShowWindow(m_hWnd, SW_SHOW);
	m_lastFrameTimeMs = timeGetTime();
	m_windowMode = c_windowModeNone;
	m_flags |= c_flagInitialized;
}

// FUNCTION: LEGORACERS 0x004167b0
void Win32GolApp::ShutdownDisplay()
{
	m_unk0x808 = 0;
	m_renderer = NULL;

	if (m_golDrawState && (m_golDrawState->GetFlags() & GolDrawState::c_flagBit0)) {
		m_golDrawState->VTable0x48();
	}

	m_flags &= ~c_flagDisplayActive;
}

// FUNCTION: LEGORACERS 0x004167e0
void Win32GolApp::Destroy()
{
	m_golBackendType = c_golBackendDP;
	ShutdownDisplay();

	if (m_hWnd) {
		DestroyWindow(m_hWnd);
		m_hWnd = 0;
	}

	for (LegoU32 i = 0; i < sizeOfArray(m_fileSources); i++) {
		if (m_fileSources[i].GetStream()) {
			m_fileSources[i].Reset();
			m_files[i].Dispose();
		}
	}

	m_inputManager.Shutdown();
	UnloadGolLibrary();

	m_windowMode = c_windowModeNone;
	m_flags = 0;
}

// FUNCTION: LEGORACERS 0x00416860
void Win32GolApp::AddFileSourcesFromList(const LegoChar* p_fileList)
{
	if (!p_fileList) {
		return;
	}

	LegoChar* buffer = new LegoChar[strlen(p_fileList) + 1];
	LegoChar* saved = buffer;

	if (buffer) {
		strcpy(buffer, p_fileList);

		while (buffer) {
			if (m_fileSourceCount >= sizeOfArray(m_fileSources)) {
				break;
			}

			LegoChar* newline = strchr(buffer, '\n');
			if (newline) {
				*newline = '\0';
			}

			if (!m_files[m_fileSourceCount].BufferedOpen(buffer, GolStream::c_modeRead, 0x8000)) {
				m_fileSources[m_fileSourceCount].AttachStream(&m_files[m_fileSourceCount]);
				m_fileSourceCount++;
			}

			if (!newline) {
				break;
			}
			buffer = newline + 1;
		}

		if (m_fileSourceCount > 0) {
			g_fileSourceCount = m_fileSourceCount;
			g_fileSources = m_fileSources;
		}

		delete[] saved;
	}
}

// FUNCTION: LEGORACERS 0x00416960
void Win32GolApp::LoadGolLibrary()
{
	LegoChar buffer[100];
	GolImport golImport;

	if (m_golBackendType & c_golBackendGlide) {
		m_golLibrary = LoadLibrary("GolGlide.DLL");
	}
	else if (m_golBackendType & c_golBackendSoft) {
		m_golLibrary = LoadLibrary("GolSoft.DLL");
	}
	else if (m_golBackendType & c_golBackendD3D) {
		m_golLibrary = LoadLibrary("GolD3D.DLL");
	}
	else {
		m_golLibrary = LoadLibrary("GolDP.DLL");
	}
	if (m_golLibrary == NULL) {
		::sprintf(buffer, "Unable to find a valid Gol DLL\nError Code = %d", GetLastError());
		GOL_FATALERROR_MESSAGE(buffer);
	}
	GolEntryCBFN* golEntry = (GolEntryCBFN*) GetProcAddress(m_golLibrary, "GolEntry");
	if (golEntry == NULL) {
		GOL_FATALERROR_MESSAGE("Invalid Gol DLL - cannot call entry procedure");
	}
	CreateGolImport(&golImport);
	golImport.m_fatalErrorMessage = GolFatalErrorMessage;
	m_golExport = golEntry(&golImport);
	m_golDrawState = m_golExport->VTable0x04();
}

// FUNCTION: LEGORACERS 0x00416a30
void Win32GolApp::UnloadGolLibrary()
{
	m_golDrawState = NULL;

	if (m_golLibrary) {
		GolExitCBFN* golExit = (GolExitCBFN*) GetProcAddress(m_golLibrary, "GolExit");

		if (golExit == NULL) {
			GOL_FATALERROR_MESSAGE("Invalid Gol DLL - cannot call exit procedure");
		}

		golExit();
		FreeLibrary(m_golLibrary);
		m_golLibrary = NULL;
	}
}

// FUNCTION: LEGORACERS 0x00416a90
void Win32GolApp::InitInput()
{
	m_inputManager.Initialize(g_hInstance, m_hWnd);
}

// FUNCTION: LEGORACERS 0x00416ab0
void Win32GolApp::ShutdownInput()
{
	m_inputManager.Shutdown();
}

// FUNCTION: LEGORACERS 0x00416ac0
void Win32GolApp::InitializeDisplayWithDevice(
	LegoU32 p_width,
	LegoU32 p_height,
	LegoU32 p_bpp,
	LegoU32 p_flags,
	const LegoChar* p_driverName,
	const LegoChar* p_deviceName
)
{
	m_golDrawState->VTable0x0c(p_driverName, p_deviceName);
	InitializeDisplay(p_width, p_height, p_bpp, p_flags | c_flagBit2);
}

// FUNCTION: LEGORACERS 0x00416b00
LegoS32 Win32GolApp::InitializeDisplay(LegoU32 p_width, LegoU32 p_height, LegoU32 p_bpp, LegoU32 p_flags)
{
	if (m_flags & c_flagDisplayActive) {
		ShutdownDisplay();
	}

	m_width = p_width;
	m_height = p_height;
	m_bpp = p_bpp;
	m_flags = p_flags;
	m_windowStateChanging = TRUE;

	LegoU32 drawFlags = BuildDrawStateFlags(p_flags);
	LegoS32 result = m_golDrawState->VTable0x44(p_width, p_height, p_bpp, drawFlags);
	if (result) {
		return result;
	}

	GolCommonDrawState* commonState = static_cast<GolCommonDrawState*>(m_golDrawState);
	Win32GolApp::m_renderer = commonState->m_unk0x1c;
	m_unk0x808 = (undefined4) m_golDrawState->m_unk0x14;

	if (m_golDrawState->m_flags & GolDrawState::c_flagBit9) {
		m_flags |= c_flagFullscreen;
	}

	if (!(m_flags & c_flagFullscreen)) {
		m_windowMode = c_windowModeWindowed;
		SetWindowLong(m_hWnd, GWL_STYLE, (LONG) m_windowedStyle);

		RECT rect;
		rect.left = 0;
		rect.right = p_width;
		rect.top = 0;
		rect.bottom = p_height;
		AdjustWindowRect(&rect, m_windowedStyle, FALSE);

		LegoS32 w = rect.right - rect.left;
		LegoS32 h = rect.bottom - rect.top;
		LegoS32 screenW = GetSystemMetrics(SM_CXSCREEN);
		LegoS32 screenH = GetSystemMetrics(SM_CYSCREEN);
		if (w > screenW) {
			w = screenW;
		}
		if (h > screenH) {
			h = screenH;
		}
		SetWindowPos(m_hWnd, NULL, 0, 0, w, h, SWP_SHOWWINDOW);
	}
	else {
		m_windowMode = c_windowModeFullscreen;
		SetWindowLong(m_hWnd, GWL_STYLE, (LONG) m_fullscreenStyle);

		if (m_flags & c_flagBit8) {
			SetWindowPos(m_hWnd, NULL, 0, 0, 0, 0, SWP_SHOWWINDOW);
		}
		else {
			GetInputManager()->GetMouse()->SetNonExclusiveMode();
			SetWindowPos(
				m_hWnd,
				NULL,
				0,
				0,
				GetSystemMetrics(SM_CXSCREEN),
				GetSystemMetrics(SM_CYSCREEN),
				SWP_SHOWWINDOW
			);
		}
	}

	SetWindowLong(m_hWnd, 0, (LONG) this);
	UpdateWindow(m_hWnd);
	SetFocus(m_hWnd);

	m_windowStateChanging = FALSE;
	m_flags |= c_flagDisplayActive;
	return 0;
}

// FUNCTION: LEGORACERS 0x00416cd0
void Win32GolApp::ToggleFullscreen()
{
	if (m_golDrawState->GetFlags() & GolDrawState::c_flagBit0) {
		OutputDebugString("Toggling full-screen mode\n");

		if (m_flags & c_flagFullscreen) {
			OutputDebugString("--to windowed\n");
			ChangeWindowState(c_windowModeWindowed);
		}
		else {
			OutputDebugString("--to full screen\n");
			ChangeWindowState(c_windowModeFullscreen);
		}
	}
}

// FUNCTION: LEGORACERS 0x00416d20
LegoBool32 Win32GolApp::IsCursorInClientArea(HWND p_hWnd)
{
	RECT rect;
	POINT topLeft;
	POINT bottomRight;
	POINT cursor;

	GetClientRect(p_hWnd, &rect);
	topLeft.x = rect.left;
	topLeft.y = rect.top;
	bottomRight.x = rect.right;
	bottomRight.y = rect.bottom;
	ClientToScreen(p_hWnd, &topLeft);
	ClientToScreen(p_hWnd, &bottomRight);
	GetCursorPos(&cursor);

	return cursor.x >= topLeft.x && cursor.x < bottomRight.x && cursor.y >= topLeft.y && cursor.y < bottomRight.y;
}

// FUNCTION: LEGORACERS 0x00416db0
void Win32GolApp::UpdateMousePosition()
{
	m_eventHandler->VTable0x28();

	if (m_windowMode == c_windowModeWindowed) {
		RECT rect;
		POINT topLeft;
		POINT bottomRight;
		POINT cursorPos;

		GetClientRect(m_hWnd, &rect);
		topLeft.x = rect.left;
		topLeft.y = rect.top;
		bottomRight.x = rect.right;
		bottomRight.y = rect.bottom;
		ClientToScreen(m_hWnd, &topLeft);
		ClientToScreen(m_hWnd, &bottomRight);
		GetCursorPos(&cursorPos);

		if (cursorPos.x < topLeft.x || cursorPos.x >= bottomRight.x || cursorPos.y < topLeft.y ||
			cursorPos.y >= bottomRight.y) {
			m_eventHandler->VTable0x2c();
		}
		else {
			LegoFloat xScale = (LegoFloat) (bottomRight.x - topLeft.x) / m_golDrawState->m_width;
			LegoFloat yScale = (LegoFloat) (bottomRight.y - topLeft.y) / m_golDrawState->m_height;
			cursorPos.x -= topLeft.x;
			cursorPos.y -= topLeft.y;
			cursorPos.x /= xScale;
			cursorPos.y /= yScale;
			m_eventHandler->VTable0x24(cursorPos.x, cursorPos.y);
		}
	}
}

// FUNCTION: LEGORACERS 0x00416ef0
LegoS32 Win32GolApp::Tick(CactusInterface0x4* p_eventHandler)
{
	m_eventHandler = p_eventHandler;
	UpdateMousePosition();

	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		if (msg.message == WM_QUIT) {
			SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);
			return 0;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	DWORD time = timeGetTime();
	m_frameDeltaMs = time - m_lastFrameTimeMs;
	if (m_frameDeltaMs > m_maxFrameDeltaMs) {
		m_frameDeltaMs = m_maxFrameDeltaMs;
	}
	else if (m_frameDeltaMs < c_minFrameDeltaMs) {
		Sleep(c_minFrameDeltaMs - m_frameDeltaMs);
		time = timeGetTime();
		m_frameDeltaMs = time - m_lastFrameTimeMs;
	}
	m_lastFrameTimeMs = time;

	if (m_pollInput) {
		m_inputManager.PollDevices(m_frameDeltaMs);
	}
	m_eventHandler = 0;
	return 1;
}

// FUNCTION: LEGORACERS 0x00417000
void Win32GolApp::ChangeWindowState(LegoU32 p_mode)
{
	if (m_windowStateChanging) {
		return;
	}
	if (!m_golDrawState) {
		return;
	}
	if (!(m_golDrawState->GetFlags() & GolDrawState::c_flagBit0)) {
		return;
	}
	if (p_mode == m_windowMode) {
		return;
	}

	m_windowStateChanging = TRUE;

	if (m_eventHandler) {
		m_eventHandler->VTable0x0c();
	}
	m_golDrawState->VTable0x50();
	LegoU32 drawFlags = BuildDrawStateFlags(m_flags) & ~GolDrawState::c_flagBit15;

	OutputDebugString("Changing window state\n");

	if (p_mode == c_windowModeWindowed) {
		OutputDebugString("--to windowed\n");
		m_golDrawState
			->VTable0x54(m_width, m_height, m_bpp, drawFlags & ~(GolDrawState::c_flagBit9 | GolDrawState::c_flagBit10));

		if (m_golDrawState->m_flags & GolDrawState::c_flagBit9) {
			OutputDebugString("--from full screen\n");
			m_flags |= c_flagFullscreen;
			m_windowMode = c_windowModeFullscreen;
			SetWindowLong(m_hWnd, GWL_STYLE, (LONG) m_fullscreenStyle);
			if (m_flags & c_flagBit8) {
				SetWindowPos(m_hWnd, NULL, 0, 0, 0, 0, SWP_SHOWWINDOW);
			}
			else {
				GetInputManager()->GetMouse()->SetNonExclusiveMode();
				SetWindowPos(
					m_hWnd,
					NULL,
					0,
					0,
					GetSystemMetrics(SM_CXSCREEN),
					GetSystemMetrics(SM_CYSCREEN),
					SWP_SHOWWINDOW
				);
			}
		}
		else {
			m_flags &= ~c_flagFullscreen;
			m_windowMode = c_windowModeWindowed;
			SetWindowLong(m_hWnd, GWL_STYLE, (LONG) m_windowedStyle);

			RECT rect;
			rect.left = 0;
			rect.right = m_width;
			rect.top = 0;
			rect.bottom = m_height;
			AdjustWindowRect(&rect, m_windowedStyle, FALSE);

			LegoS32 w = rect.right - rect.left;
			LegoS32 h = rect.bottom - rect.top;
			LegoS32 screenW = GetSystemMetrics(SM_CXSCREEN);
			LegoS32 screenH = GetSystemMetrics(SM_CYSCREEN);
			LegoS32 x, y;
			if (w > screenW) {
				w = screenW;
				x = 0;
			}
			else {
				x = (screenW - w) >> 1;
			}
			if (h > screenH) {
				h = screenH;
				y = 0;
			}
			else {
				y = (screenH - h) >> 1;
			}
			SetWindowPos(m_hWnd, NULL, x, y, w, h, SWP_SHOWWINDOW);
		}

		if (m_eventHandler) {
			m_eventHandler->VTable0x10();
		}
	}
	else if (p_mode == c_windowModeFullscreen) {
		OutputDebugString("--to full screen\n");
		m_flags |= c_flagFullscreen;
		LegoU32 fullscreenFlags = drawFlags | (GolDrawState::c_flagBit9 | GolDrawState::c_flagBit10);
		m_windowMode = c_windowModeFullscreen;
		SetWindowLong(m_hWnd, GWL_STYLE, (LONG) m_fullscreenStyle);
		if (m_flags & c_flagBit8) {
			SetWindowPos(m_hWnd, NULL, 0, 0, 0, 0, SWP_SHOWWINDOW);
		}
		else {
			GetInputManager()->GetMouse()->SetNonExclusiveMode();
			SetWindowPos(
				m_hWnd,
				NULL,
				0,
				0,
				GetSystemMetrics(SM_CXSCREEN),
				GetSystemMetrics(SM_CYSCREEN),
				SWP_SHOWWINDOW
			);
		}
		m_golDrawState->VTable0x54(m_width, m_height, m_bpp, fullscreenFlags);

		if (m_eventHandler) {
			m_eventHandler->VTable0x10();
		}
	}
	else if (p_mode == c_windowModeMinimized) {
		OutputDebugString("--to minimized\n");
		ShowWindow(m_hWnd, SW_SHOWMINNOACTIVE);
		m_windowMode = c_windowModeMinimized;
	}

	UpdateWindow(m_hWnd);
	SetFocus(m_hWnd);
	m_windowStateChanging = FALSE;
}

// FUNCTION: LEGORACERS 0x00417330
LRESULT CALLBACK Win32GolApp::AppWndProc(HWND p_hWnd, UINT p_msg, WPARAM p_wParam, LPARAM p_lParam)
{
	Win32GolApp* self = (Win32GolApp*) GetWindowLong(p_hWnd, 0);
	if (!self) {
		return DefWindowProc(p_hWnd, p_msg, p_wParam, p_lParam);
	}

	switch (p_msg) {
	case WM_ACTIVATE:
		if (!(self->m_flags & Win32GolApp::c_flagDisplayActive)) {
			break;
		}

		if (LOWORD(p_wParam) == WA_INACTIVE) {
			OutputDebugString("Deactivate Window\n");
			if (!self->m_disabled) {
				OutputDebugString("--App was enabled\n");
				self->OnAppDeactivated();
				if (self->m_eventHandler) {
					self->m_eventHandler->VTable0x04();
				}
			}
		}
		else {
			OutputDebugString("Activate Window\n");
			if (self->m_disabled) {
				OutputDebugString("--App was disabled\n");
			}
			else {
				OutputDebugString("--App was enabled\n");
				if (self->m_flags & Win32GolApp::c_flagFullscreen) {
					OutputDebugString("--Telling the window to maximize\n");
					ShowWindow(self->m_hWnd, SW_MAXIMIZE);
				}
			}
		}
		break;
	case WM_CLOSE:
		self->NotifyCloseRequested();
		break;
	case WM_DESTROY:
		SetWindowLong(p_hWnd, 0, 0);
		self->NotifyCloseRequested();
		SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);
		PostQuitMessage(0);
		break;
	case WM_MOVE:
	case WM_SETFOCUS:
	case WM_KILLFOCUS:
		break;
	case WM_SIZE:
		if (self->m_flags & Win32GolApp::c_flagDisplayActive) {
			if (p_wParam == SIZE_MAXIMIZED || p_wParam == SIZE_RESTORED) {
				OutputDebugString("Maximizing App\n");
				if (self->m_disabled) {
					OutputDebugString("--App was disabled\n");
					self->OnAppActivated();
					self->m_disabled = FALSE;
					self->m_pollInput = 1;
					self->m_inputManager.RestoreSuspendedDevices();
					SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
					if (self->m_flags & Win32GolApp::c_flagFullscreen) {
						OutputDebugString("--Telling the window to maximize\n");
						ShowWindow(self->m_hWnd, SW_MAXIMIZE);
					}
				}

				if (self->m_eventHandler) {
					self->m_eventHandler->VTable0x08();
				}

				if (self->m_windowMode == Win32GolApp::c_windowModeMinimized ||
					self->m_windowMode == Win32GolApp::c_windowModeNone) {
					OutputDebugString("--App was minimized.  Resetting.\n");
					if (self->m_flags & Win32GolApp::c_flagFullscreen) {
						self->ChangeWindowState(Win32GolApp::c_windowModeFullscreen);
					}
					else {
						self->ChangeWindowState(Win32GolApp::c_windowModeWindowed);
					}
				}
			}
			else if (p_wParam == SIZE_MINIMIZED) {
				OutputDebugString("Minimizing App\n");
			}
		}
	case WM_SIZING:
	case WM_MOVING:
		if ((self->m_flags & Win32GolApp::c_flagDisplayActive) &&
			self->m_windowMode == Win32GolApp::c_windowModeFullscreen) {
			if (self->m_flags & Win32GolApp::c_flagBit8) {
				SetWindowPos(p_hWnd, NULL, 0, 0, 0, 0, SWP_SHOWWINDOW);
			}
			else {
				self->GetInputManager()->GetMouse()->SetNonExclusiveMode();
				SetWindowPos(
					p_hWnd,
					NULL,
					0,
					0,
					GetSystemMetrics(SM_CXSCREEN),
					GetSystemMetrics(SM_CYSCREEN),
					SWP_SHOWWINDOW
				);
			}
		}
		break;
	case WM_PAINT: {
		RECT rect;
		PAINTSTRUCT paint;

		if (GetUpdateRect(p_hWnd, &rect, FALSE)) {
			HDC hdc = BeginPaint(p_hWnd, &paint);
			if (!(self->m_golDrawState->GetFlags() & GolDrawState::c_flagBit0)) {
				FillRect(hdc, &rect, (HBRUSH) GetStockObject(BLACK_BRUSH));
			}

			EndPaint(p_hWnd, &paint);
		}

		break;
	}
	case WM_ACTIVATEAPP:
		if (self->m_flags & Win32GolApp::c_flagDisplayActive) {
			if (!p_wParam) {
				OutputDebugString("Deactivate App\n");
				if (!self->m_disabled) {
					OutputDebugString("--App was enabled\n");
					self->OnAppDeactivated();
					if (self->m_eventHandler) {
						self->m_eventHandler->VTable0x04();
					}
					self->ChangeWindowState(Win32GolApp::c_windowModeMinimized);
					self->m_disabled = TRUE;
					self->m_pollInput = 0;
					self->m_inputManager.SuspendActiveDevices();
					SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);
				}
			}
			else {
				OutputDebugString("Activate App\n");
				if (self->m_disabled) {
					OutputDebugString("--App was disabled\n");
				}
			}
		}

		break;
	case WM_CHAR:
		if (self->m_eventHandler) {
			self->m_eventHandler->VTable0x1c(p_wParam);
			self->m_eventHandler->VTable0x20(p_wParam);
		}

		break;
	case WM_SETCURSOR:
		if (self->IsCursorInClientArea(p_hWnd)) {
			SetCursor(self->m_hCursor);
		}

		return 1;
	case WM_SYSCOMMAND:
		if (p_wParam != SC_SCREENSAVE) {
			return DefWindowProc(p_hWnd, WM_SYSCOMMAND, p_wParam, p_lParam);
		}

		break;
	case WM_SYSKEYDOWN:
		break;
	case WM_SYSKEYUP:
		break;
	case WM_COMMAND:
		break;
	case WM_QUERYNEWPALETTE:
		break;
	default:
		return DefWindowProc(p_hWnd, p_msg, p_wParam, p_lParam);
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x00417900
LegoU32 Win32GolApp::BuildDrawStateFlags(LegoU32 p_flags)
{
	LegoU32 result = 0;
	if (p_flags & c_flagFullscreen) {
		result |= GolDrawState::c_flagBit9 | GolDrawState::c_flagBit10;
	}
	if (p_flags & c_flagBit5) {
		result |= GolDrawState::c_flagBit11;
	}
	if (p_flags & c_flagBit4) {
		result |= GolDrawState::c_flagBit12;
	}
	if (p_flags & c_flagBit6) {
		result |= GolDrawState::c_flagBit3;
	}
	if (p_flags & c_flagPrimaryDriver) {
		result |= GolDrawState::c_flagBit13;
	}
	if (p_flags & c_flagSelect3DDevice) {
		result |= GolDrawState::c_flagBit15;
	}
	if (p_flags & c_flagBit10) {
		result |= GolDrawState::c_flagBit16;
	}
	if (p_flags & c_flagBit17) {
		result |= GolDrawState::c_flagBit17;
	}
	if (p_flags & c_flagBit2) {
		result |= GolDrawState::c_flagBit14;
	}
	if (p_flags & c_flagBit12) {
		result |= GolDrawState::c_flagBit18;
	}
	if (p_flags & c_flagBit13) {
		result |= GolDrawState::c_flagBit19;
	}
	if (p_flags & c_flagAlphaTransparency) {
		result |= GolDrawState::c_flagBit21;
	}
	return result;
}

// FUNCTION: LEGORACERS 0x00417980
InputManager* Win32GolApp::GetInputManager()
{
	return &m_inputManager;
}

// STUB: LEGORACERS 0x00417990 FOLDED
void Win32GolApp::OnAppDeactivated()
{
	STUB(0x00417990);
}

// STUB: LEGORACERS 0x00417990 FOLDED
void Win32GolApp::OnAppActivated()
{
	STUB(0x00417990);
}
