#ifndef CUTSCENEEVENTSINK_H
#define CUTSCENEEVENTSINK_H

#include "decomp.h"

// VTABLE: LEGORACERS 0x004b49a4
// SIZE 0x04
class CutsceneEventSink {
public:
	virtual void OnEventStarted(void*, void*, void*) = 0;            // vtable+0x00
	virtual void OnEventEnded(void*, void*, void*) = 0;              // vtable+0x04
	virtual void OnCameraStarted(void*, void*, void*) = 0;           // vtable+0x08
	virtual void OnCameraEnded(void*, void*, void*) = 0;             // vtable+0x0c
	virtual void OnModelStarted(void*, void*, void*) = 0;            // vtable+0x10
	virtual void OnModelEnded(void*, void*, void*) = 0;              // vtable+0x14
	virtual void OnTransformStarted(void*, void*, void*) = 0;        // vtable+0x18
	virtual void OnTransformEnded(void*, void*, void*) = 0;          // vtable+0x1c
	virtual void OnAmbientLightStarted(void*, void*, void*) = 0;     // vtable+0x20
	virtual void OnAmbientLightEnded(void*, void*, void*) = 0;       // vtable+0x24
	virtual void OnDirectionalLightStarted(void*, void*, void*) = 0; // vtable+0x28
	virtual void OnDirectionalLightEnded(void*, void*, void*) = 0;   // vtable+0x2c
};

#endif // CUTSCENEEVENTSINK_H
