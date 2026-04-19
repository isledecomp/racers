#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include "ironflame0x944.h"
#include "types.h"

#include <windows.h>

// Forward declarations for DirectDraw7 types referenced by modern strmif.h
// (MSVC 6.0's strmif.h doesn't require these)
struct IDirectDraw7;
struct IDirectDrawSurface7;
typedef struct IDirectDraw7* LPDIRECTDRAW7;
typedef struct IDirectDrawSurface7* LPDIRECTDRAWSURFACE7;

#include <strmif.h>

class VideoPlayer {
public:
	// SIZE 0x18
	class Graph {
	public:
		Graph();
		~Graph();

		LegoBool32 CreateGraph();
		HANDLE GetMediaEvent();
		void Release();
		void Destroy();
		LegoBool32 LoadFile(LPCSTR p_filename);
		void StartPlayback(LegoBool32 p_fullscreen, LegoBool32 p_autoRewind);
		void StopPlayback();
		void ResetPosition();
		void RunMessageLoop(LegoBool32 p_abortableOnKey);
		void ProcessEvent();

		IGraphBuilder* m_graph;      // 0x00
		HANDLE m_eventHandle;        // 0x04
		HWND m_hwnd;                 // 0x08
		LegoBool32 m_running;        // 0x0c
		LegoBool32 m_hasVideoWindow; // 0x10
		LegoBool32 m_autoRewind;     // 0x14
	};

	static int Begin(IronFlame0x944* p_unk0x04, DWORD p_width, DWORD p_height);
	static int Play(IronFlame0x944* p_unk0x04, LPCSTR p_filename, int p_abortableOnKey, int p_autoRewind);
	static int End(IronFlame0x944* p_unk0x04);

private:
	static LegoS32 Play(
		IronFlame0x944* p_unk0x04,
		LPCSTR p_filename,
		LegoBool32 p_abortableOnKey,
		LegoBool32 p_autoRewind
	);
	static void RevertDisplay();
};

#endif // VIDEOPLAYER_H
