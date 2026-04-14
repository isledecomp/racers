#ifndef AZURETORUS0X0A
#define AZURETORUS0X0A

#include "decomp.h"
#include "types.h"

// SIZE 0x0a
class AzureTorus0x0a {
public:
	AzureTorus0x0a();
	~AzureTorus0x0a();

	static LegoS32 AzureStrlen(undefined2* p_string);
	undefined2* FromCursor(undefined4 p_param);
	undefined4 FUN_00449e70(undefined2* p_buf, LegoS32 p_count);
	undefined4 FUN_00449ed0(AzureTorus0x0a* p_torus);
	void ResetCursors();
	void FirstLine();
	void NextLine();
	undefined4 TorusStrcmp(AzureTorus0x0a* p_torus);
	undefined4 TorusStrcpy(AzureTorus0x0a* p_torus);
	undefined4 AzureStrcpy(undefined2* p_string);
	void ToUpperCase();
	void CopyToString(LegoChar* p_string);
	void CopyToBuf8(LegoChar* p_buf);
	LegoS32 CountLines();

	void Reset()
	{
		m_chars = NULL;
		m_cursorEnd = 0;
		m_cursorStart = 0;
		m_maxLen = 0;
	}

	undefined2 SelectionLength() const { return m_cursorEnd - m_cursorStart; }

protected:
	undefined2* m_chars;      // 0x00
	undefined2 m_maxLen;      // 0x04
	undefined2 m_cursorStart; // 0x06
	undefined2 m_cursorEnd;   // 0x08
};

#endif // AZURETORUS0X0A
