#include "ironflame0x944.h"

#include "../../GolDP/include/gol.h"
#include "../../GolDP/include/golcommondrawstate.h"
#include "cactusinterface0x4.h"
#include "gol.h"
#include "golerror.h"
#include "golfsutil.h"
#include "golstream.h"
#include "opalvault0xf0.h"

#include <mmsystem.h>
#include <stdio.h>
#include <string.h>

extern HINSTANCE g_hInstance;
extern HINSTANCE g_hPrevInstance;

DECOMP_SIZE_ASSERT(IronFlame0x944, 0x944)

// FUNCTION: LEGORACERS 0x004164d0
IronFlame0x944::IronFlame0x944()
{
	m_golLibrary = NULL;
	m_golExport = NULL;
	m_hWnd = 0;
	m_golBackendType = c_golBackendDP;
	m_unk0x92c = 0;
	m_unk0x934 = 0;
	m_unk0x93c = 0;
	m_unk0x940 = 0;
	m_unk0x930 = 0;
	m_unk0x938 = 1;
}

// FUNCTION: LEGORACERS 0x00416580
IronFlame0x944::~IronFlame0x944()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004165e0
void IronFlame0x944::Init(const LegoChar* p_windowName, const LegoChar* p_fileName)
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

	g_unk0x4c73a0 = (undefined4*) &m_hashTable;

	if (p_fileName) {
		FUN_00416860(p_fileName);
	}

	m_unk0x93c = WS_POPUP | WS_CLIPCHILDREN;
	m_unk0x940 = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;
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
	m_unk0x92c = 0;
	m_flags |= c_flagInitialized;
}

// FUNCTION: LEGORACERS 0x004167b0
void IronFlame0x944::VTable0x2c()
{
	GolDrawState* drawState = m_golDrawState;
	m_unk0x808 = 0;
	m_unk0x80c = 0;

	if (drawState && (drawState->GetFlags() & GolDrawState::c_flagBit0)) {
		drawState->VTable0x48();
	}

	m_flags &= ~c_flagDisplayActive;
}

// FUNCTION: LEGORACERS 0x004167e0
void IronFlame0x944::Destroy()
{
	m_golBackendType = c_golBackendDP;
	VTable0x2c();

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

	m_unk0x834.Shutdown();
	UnloadGolLibrary();

	m_unk0x92c = 0;
	m_flags = 0;
}

// FUNCTION: LEGORACERS 0x00416860
void IronFlame0x944::FUN_00416860(const LegoChar* p_fileList)
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
				m_fileSources[m_fileSourceCount].FUN_0044d870(&m_files[m_fileSourceCount]);
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
void IronFlame0x944::LoadGolLibrary()
{
	LegoChar buffer[100];
	GolImport golImport;

	if (m_golBackendType & c_golBackendGlide) {
		m_golLibrary = LoadLibraryA("GolGlide.DLL");
	}
	else if (m_golBackendType & c_golBackendSoft) {
		m_golLibrary = LoadLibraryA("GolSoft.DLL");
	}
	else if (m_golBackendType & c_golBackendD3D) {
		m_golLibrary = LoadLibraryA("GolD3D.DLL");
	}
	else {
		m_golLibrary = LoadLibraryA("GolDP.DLL");
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
void IronFlame0x944::UnloadGolLibrary()
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
void IronFlame0x944::InitInput()
{
	m_unk0x834.FUN_004503e0(g_hInstance, m_hWnd);
}

// FUNCTION: LEGORACERS 0x00416ab0
void IronFlame0x944::VTable0x20()
{
	m_unk0x834.Shutdown();
}

// FUNCTION: LEGORACERS 0x00416ac0
void IronFlame0x944::VTable0x28(
	LegoU32 p_width,
	LegoU32 p_height,
	LegoU32 p_bpp,
	LegoU32 p_flags,
	const LegoChar* p_driverName,
	const LegoChar* p_deviceName
)
{
	m_golDrawState->VTable0x0c(p_driverName, p_deviceName);
	VTable0x24(p_width, p_height, p_bpp, p_flags | c_flagBit2);
}

// FUNCTION: LEGORACERS 0x00416b00
LegoS32 IronFlame0x944::VTable0x24(LegoU32 p_width, LegoU32 p_height, LegoU32 p_bpp, LegoU32 p_flags)
{
	if (m_flags & c_flagDisplayActive) {
		VTable0x2c();
	}

	m_width = p_width;
	m_height = p_height;
	m_bpp = p_bpp;
	m_flags = p_flags;
	m_unk0x930 = 1;

	LegoU32 drawFlags = VTable0x00(p_flags);
	LegoS32 result = m_golDrawState->VTable0x44(p_width, p_height, p_bpp, drawFlags);
	if (result) {
		return result;
	}

	GolCommonDrawState* commonState = static_cast<GolCommonDrawState*>(m_golDrawState);
	m_unk0x80c = commonState->m_unk0x1c;
	m_unk0x808 = (undefined4) m_golDrawState->m_unk0x14;

	if (m_golDrawState->m_flags & GolDrawState::c_flagBit9) {
		m_flags |= c_flagBit3;
	}

	if (!(m_flags & c_flagBit3)) {
		m_unk0x92c = 2;
		SetWindowLong(m_hWnd, GWL_STYLE, (LONG) m_unk0x940);

		RECT rect;
		rect.left = 0;
		rect.right = p_width;
		rect.top = 0;
		rect.bottom = p_height;
		AdjustWindowRect(&rect, m_unk0x940, FALSE);

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
		m_unk0x92c = 1;
		SetWindowLong(m_hWnd, GWL_STYLE, (LONG) m_unk0x93c);

		if (m_flags & c_flagBit8) {
			SetWindowPos(m_hWnd, NULL, 0, 0, 0, 0, SWP_SHOWWINDOW);
		}
		else {
			VTable0x38()->GetUnk0xa0()->VTable0x44();
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

	m_unk0x930 = 0;
	m_flags |= c_flagDisplayActive;
	return 0;
}

// FUNCTION: LEGORACERS 0x00416cd0
void IronFlame0x944::VTable0x30()
{
	if (m_golDrawState->GetFlags() & GolDrawState::c_flagBit0) {
		OutputDebugString("Toggling full-screen mode\n");

		if (m_flags & c_flagBit3) {
			OutputDebugString("--to windowed\n");
			FUN_00417000(2);
		}
		else {
			OutputDebugString("--to full screen\n");
			FUN_00417000(1);
		}
	}
}

// FUNCTION: LEGORACERS 0x00416db0
void IronFlame0x944::FUN_00416db0()
{
	m_unk0x81c->VTable0x28();

	if (m_unk0x92c == 2) {
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
			m_unk0x81c->VTable0x2c();
		}
		else {
			LegoFloat xScale = (LegoFloat) (bottomRight.x - topLeft.x) / m_golDrawState->m_width;
			LegoFloat yScale = (LegoFloat) (bottomRight.y - topLeft.y) / m_golDrawState->m_height;
			cursorPos.x -= topLeft.x;
			cursorPos.y -= topLeft.y;
			cursorPos.x /= xScale;
			cursorPos.y /= yScale;
			m_unk0x81c->VTable0x24(cursorPos.x, cursorPos.y);
		}
	}
}

// FUNCTION: LEGORACERS 0x00416ef0
LegoS32 IronFlame0x944::Tick(CactusInterface0x4* p_unk0x81c)
{
	m_unk0x81c = p_unk0x81c;
	FUN_00416db0();

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

	if (m_unk0x938) {
		m_unk0x834.VTable0x10(m_frameDeltaMs);
	}
	m_unk0x81c = 0;
	return 1;
}

// STUB: LEGORACERS 0x00417000
void IronFlame0x944::FUN_00417000(LegoU32)
{
	// TODO
	STUB(0x417000);
}

// STUB: LEGORACERS 0x00417330
LRESULT CALLBACK AppWndProc(HWND, UINT, WPARAM, LPARAM)
{
	// TODO
	STUB(0x417330);
	return 0;
}

// FUNCTION: LEGORACERS 0x00417900
LegoU32 IronFlame0x944::VTable0x00(LegoU32 p_flags)
{
	LegoU32 result = 0;
	if (p_flags & c_flagBit3) {
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
	if (p_flags & c_flagBit7) {
		result |= GolDrawState::c_flagBit13;
	}
	if (p_flags & c_flagBit9) {
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
	if (p_flags & c_flagBit15) {
		result |= GolDrawState::c_flagBit21;
	}
	return result;
}

// FUNCTION: LEGORACERS 0x00417980
OpalVault0xf0* IronFlame0x944::VTable0x38()
{
	return &m_unk0x834;
}

// STUB: LEGORACERS 0x00417990 FOLDED
void IronFlame0x944::VTable0x3c()
{
	STUB(0x00417990);
}

// STUB: LEGORACERS 0x00417990 FOLDED
void IronFlame0x944::VTable0x40()
{
	STUB(0x00417990);
}
