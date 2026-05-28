#ifndef MENUTOOLCREATEPARAMS0X30_H
#define MENUTOOLCREATEPARAMS0X30_H

#include "decomp.h"
#include "text/coppercrest0x40.h"
#include "types.h"

class GolD3DRenderDevice;
class CrimsonSun0xa4;
class GolExport;
class GolStringTable;
class InputManager;
class InputEventQueue;
class PorcelainVeil0x50;
class SoundGroupBinding;

// SIZE 0x30
class MenuToolCreateParams0x30 {
public:
	GolExport* m_golExport;                      // 0x00
	GolD3DRenderDevice* m_renderer;              // 0x04
	GolStringTable* m_menuNameStrings;           // 0x08
	GolStringTable* m_menuTextStrings;           // 0x0c
	InputManager* m_inputManager;                // 0x10
	InputEventQueue* m_inputEvents;              // 0x14
	PorcelainVeil0x50* m_menuStyles;             // 0x18
	SoundGroupBinding* m_soundGroupBinding;      // 0x1c
	CrimsonSun0xa4* m_unk0x20;                   // 0x20
	CopperCrest0x40::Helper0x44* m_cursorHelper; // 0x24
	LegoU16 m_menuId;                            // 0x28
	undefined2 m_unk0x2a;                        // 0x2a
	undefined4 m_unk0x2c;                        // 0x2c
};

#endif // MENUTOOLCREATEPARAMS0X30_H
