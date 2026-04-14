#ifndef AZURETORUS0X0A
#define AZURETORUS0X0A

#include "decomp.h"
#include "types.h"

// SIZE 0x0a
class AzureTorus0x0a {
public:
	AzureTorus0x0a();
	~AzureTorus0x0a();

	static LegoS32 FUN_00449dc0(undefined2* p_string);
	undefined2* FUN_00449e50(undefined4 p_param);
	undefined4 FUN_00449e70(undefined2* p_buf, LegoS32 p_count);
	undefined4 FUN_00449ed0(AzureTorus0x0a* p_torus);
	void FUN_00449f00();
	void FUN_00449f30();
	void FUN_00449f70();
	undefined4 FUN_00449fc0(AzureTorus0x0a* p_torus);
	undefined4 FUN_0044a020(AzureTorus0x0a* p_torus);
	undefined4 FUN_0044a080(undefined2* p_string);
	void ToUpperCase();
	void FUN_0044a130(char* p_string);
	void FUN_0044a160(char* p_buf);
	LegoS32 FUN_0044a1a0();

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
