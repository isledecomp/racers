#ifndef ONYXBREEZE0X248_H
#define ONYXBREEZE0X248_H

#include "decomp.h"

class InputManager;

// SIZE 0x248
class OnyxBreeze0x248 {
public:
	OnyxBreeze0x248();
	~OnyxBreeze0x248();

	void Initialize(InputManager* p_inputManager);
	void Shutdown();

	undefined4* GetUnk0x208() { return &m_unk0x208; }

private:
	undefined m_unk0x00[0x208 - 0x00];   // 0x00
	undefined4 m_unk0x208;               // 0x208
	undefined m_unk0x20c[0x248 - 0x20c]; // 0x20c
};

#endif // ONYXBREEZE0X248_H
