#ifndef VERDANTTIDE0X38_H
#define VERDANTTIDE0X38_H

#include "decomp.h"
#include "types.h"

class BronzeFalcon0xc8770;
class GolExport;

// SIZE 0x38
class VerdantTide0x38 {
public:
	VerdantTide0x38();
	~VerdantTide0x38();
	void Destroy();
	void FUN_004978f0(GolExport* p_golExport, BronzeFalcon0xc8770* p_renderer);
	void FUN_00497a10(const LegoChar* p_filename, undefined4 p_binary);
	void FUN_00497c30(const LegoChar* p_filename, undefined4 p_binary, undefined4 p_unk0x0c);

private:
	undefined m_unk0x00[0x38 - 0x00]; // 0x00
};

#endif // VERDANTTIDE0X38_H
