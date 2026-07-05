#ifndef GOLAPPEVENTHANDLER_H
#define GOLAPPEVENTHANDLER_H

#include "decomp.h"

// VTABLE: LEGORACERS 0x004affa4
// SIZE 0x4
class GolAppEventHandler {
public:
	virtual void OnCloseRequested();                            // vtable+0x00
	virtual void OnAppDeactivated();                            // vtable+0x04
	virtual void OnAppActivated();                              // vtable+0x08
	virtual void OnWindowModeChanging();                        // vtable+0x0c
	virtual void OnWindowModeChanged();                         // vtable+0x10
	virtual void VTable0x14();                                  // vtable+0x14
	virtual void VTable0x18();                                  // vtable+0x18
	virtual void OnChar(undefined4 p_char);                     // vtable+0x1c
	virtual void VTable0x20(undefined4);                        // vtable+0x20
	virtual void OnCursorMoved(undefined4 p_x, undefined4 p_y); // vtable+0x24
	virtual void OnCursorInside();                              // vtable+0x28
	virtual void OnCursorOutside();                             // vtable+0x2c
};

#endif // GOLAPPEVENTHANDLER_H
