#ifndef WORKHORSE0X58_H
#define WORKHORSE0X58_H

#include "decomp.h"
#include "types.h"

// SIZE 0x58
class WorkHorse0x58 {
public:
	enum Pixelformat {
		e_format555 = 0,
		e_format565 = 1,
		e_formatIndex8 = 2,
	};

	WorkHorse0x58();
	~WorkHorse0x58();

	LegoBool Initialize(Pixelformat, undefined4);

	void SetUnk0x4c(undefined* p_arg) { m_unk0x4c = p_arg; }

private:
	undefined m_unk0x00[0x44 - 0x00]; // 0x00
	undefined* m_unk0x44;             // 0x44
	undefined m_unk0x48[0x4c - 0x48]; // 0x48
	undefined* m_unk0x4c;             // 0x4c
	undefined m_unk0x50[0x54 - 0x50]; // 0x50
	undefined4 m_unk0x54;             // 0x54
};

#endif // WORKHORSE0X58_H
