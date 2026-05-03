#ifndef MENUTOOLCREATEPARAMS0X30_H
#define MENUTOOLCREATEPARAMS0X30_H

#include "decomp.h"
#include "types.h"

class BronzeFalcon0xc8770;
class CrimsonSun0xa4;
class GolExport;
class GolStringTable;
class InputManager;
class OnyxCircularBuffer0x1c;
class PorcelainVeil0x50;
class SoundGroupBinding;

// SIZE 0x30
class MenuToolCreateParams0x30 {
public:
	GolExport* m_golExport;                          // 0x00
	BronzeFalcon0xc8770* m_renderer;                 // 0x04
	GolStringTable* m_menuNameStrings;               // 0x08
	GolStringTable* m_menuTextStrings;               // 0x0c
	InputManager* m_inputManager;                    // 0x10
	OnyxCircularBuffer0x1c* m_inputBindingContainer; // 0x14
	PorcelainVeil0x50* m_menuStyles;                 // 0x18
	SoundGroupBinding* m_soundGroupBinding;          // 0x1c
	CrimsonSun0xa4* m_unk0x20;                       // 0x20
	undefined4* m_unk0x24;                           // 0x24
	LegoU16 m_menuId;                                // 0x28
	undefined2 m_unk0x2a;                            // 0x2a
	undefined4 m_unk0x2c;                            // 0x2c
};

#endif // MENUTOOLCREATEPARAMS0X30_H
