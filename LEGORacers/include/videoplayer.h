#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include "ironflame0x944.h"
#include "types.h"

#include <strmif.h>
#include <windows.h>

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

	static int FUN_004a60c0(IronFlame0x944* p_unk0x04, DWORD p_width, DWORD p_height);
	static int FUN_004a61c0(IronFlame0x944* p_unk0x04, LPCSTR p_filename, int p_unk0x08, int p_unk0x0c);
	static int FUN_004a61e0(IronFlame0x944* p_unk0x04);

private:
	static LegoS32 PlayImpl(
		IronFlame0x944* p_unk0x04,
		LPCSTR p_filename,
		LegoBool32 p_fullscreen,
		LegoBool32 p_autoRewind
	);
	static void RevertDisplay();
};

#endif // VIDEOPLAYER_H
