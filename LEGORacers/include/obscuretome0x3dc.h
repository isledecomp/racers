#ifndef OBSCURETOME0X3DC
#define OBSCURETOME0X3DC

#include "compat.h"
#include "decomp.h"
#include "obscureanchor0x5c.h"
#include "obscureanthem0x58.h"
#include "obscurezebra0xa4.h"

// VTABLE: LEGORACERS 0x004b267c
// SIZE 0x3dc
class ObscureTome0x3dc : public ObscureAnthem0x58 {
public:
	ObscureTome0x3dc();
	~ObscureTome0x3dc() override;         // vtable+0x04
	void VTable0x10(undefined4) override; // vtable+0x10

	// SYNTHETIC: LEGORACERS 0x0046ec30
	// ObscureTome0x3dc::`scalar deleting destructor'

protected:
	ObscureZebra0xa4 m_unk0x58;     // 0x058
	ObscureAnchor0x5c m_unk0xfc[8]; // 0x0fc
};

#endif // OBSCURETOME0X3DC
