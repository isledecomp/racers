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

private:
	undefined m_unk0x00[0x248 - 0x00]; // 0x00
};

#endif // ONYXBREEZE0X248_H
