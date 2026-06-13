#ifndef MENUSCREENCREATEPARAMS_H
#define MENUSCREENCREATEPARAMS_H

#include "decomp.h"
#include "menu/menuinputdispatcher.h"
#include "types.h"

class GolD3DRenderDevice;
class MenuDialog;
class GolExport;
class GolStringTable;
class InputManager;
class InputEventQueue;
class SharedMenuStyleTable;
class SoundGroupBinding;

// SIZE 0x30
class MenuScreenCreateParams {
public:
	GolExport* m_golExport;                 // 0x00
	GolD3DRenderDevice* m_renderer;         // 0x04
	GolStringTable* m_menuNameStrings;      // 0x08
	GolStringTable* m_menuTextStrings;      // 0x0c
	InputManager* m_inputManager;           // 0x10
	InputEventQueue* m_inputEvents;         // 0x14
	SharedMenuStyleTable* m_menuStyles;     // 0x18
	SoundGroupBinding* m_soundGroupBinding; // 0x1c
	MenuDialog* m_unk0x20;                  // 0x20
	MenuInputDispatcher::Cursor* m_cursor;  // 0x24
	LegoU16 m_menuId;                       // 0x28
	undefined2 m_unk0x2a;                   // 0x2a
	undefined4 m_unk0x2c;                   // 0x2c
};

#endif // MENUSCREENCREATEPARAMS_H
