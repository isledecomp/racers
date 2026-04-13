#ifndef AZURETORUS0X0A
#define AZURETORUS0X0A

#include "decomp.h"
#include "types.h"

// SIZE 0x0a
class AzureTorus0x0a {
public:
	AzureTorus0x0a();
	~AzureTorus0x0a();

	undefined2* FUN_00449e50(undefined4 p_param);
	undefined4 FUN_00449e70(undefined2* p_1, LegoS32 p_2);
	undefined4 FUN_00449ed0(AzureTorus0x0a* p_torus);
	void FUN_00449f00();
	void FUN_00449f30();
	void FUN_00449f70();
	undefined4 FUN_00449fc0(AzureTorus0x0a* p_torus);

	void Reset()
	{
		m_unk0x00 = NULL;
		m_unk0x08 = 0;
		m_unk0x06 = 0;
		m_unk0x04 = 0;
	}

	undefined2 EightMinusSix() const { return m_unk0x08 - m_unk0x06; }

protected:
	undefined2* m_unk0x00;
	undefined2 m_unk0x04;
	undefined2 m_unk0x06;
	undefined2 m_unk0x08;
};

#endif // AZURETORUS0X0A
