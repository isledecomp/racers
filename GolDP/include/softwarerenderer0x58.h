#ifndef SOFTWARERENDERER0X58_H
#define SOFTWARERENDERER0X58_H

#include "decomp.h"
#include "types.h"

#include <d3dtypes.h>

// SIZE 0x58
class SoftwareRenderer0x58 {
public:
	// SIZE 0x14
	struct Command0x14 {
		undefined m_unk0x00[0x04 - 0x00]; // 0x00
		LegoFloat m_unk0x04;              // 0x04
		undefined2 m_unk0x08;             // 0x08
		undefined2 m_unk0x0a;             // 0x0a
		undefined2 m_unk0x0c;             // 0x0c
		undefined4 m_unk0x10;             // 0x10
	};

	enum PixelFormat {
		e_format555 = 0,
		e_format565 = 1,
		e_formatIndex8 = 2,
	};

	SoftwareRenderer0x58();
	~SoftwareRenderer0x58();

	LegoBool Initialize(PixelFormat p_pixelFormat, LegoS32 p_nodeCapacity);

	void SetUnk0x4c(D3DTLVERTEX* p_arg) { m_unk0x4c = p_arg; }
	void FUN_100417a0(Command0x14* p_cmds, LegoU32 p_count, LegoFloat);
	void FUN_100417c0(Command0x14* p_cmds, LegoU32 p_count);

private:
	// SIZE 0x14
	struct RenderNode {
		RenderNode* m_next;               // 0x00
		undefined m_unk0x04[0x14 - 0x04]; // 0x04
	};

	typedef void (*RasterizerCallback)();

	undefined m_unk0x00[0x10 - 0x00];               // 0x00
	LegoU8 m_bitsPerPixel;                          // 0x10
	LegoU8 m_pixelFormat;                           // 0x11
	LegoU8 m_bytesPerPixel;                         // 0x12
	undefined m_unk0x13[0x20 - 0x13];               // 0x13
	RasterizerCallback m_currentTriangleRasterizer; // 0x20
	RasterizerCallback m_triangleRasterizer;        // 0x24
	RasterizerCallback m_spanRasterizer;            // 0x28
	undefined4 m_unk0x2c;                           // 0x2c
	undefined m_unk0x30[0x34 - 0x30];               // 0x30
	undefined4 m_unk0x34;                           // 0x34
	LegoFloat m_unk0x38;                            // 0x38
	LegoFloat m_unk0x3c;                            // 0x3c
	LegoS32 m_nodeCapacity;                         // 0x40
	RenderNode* m_nodes;                            // 0x44
	undefined m_unk0x48[0x4c - 0x48];               // 0x48
	D3DTLVERTEX* m_unk0x4c;                         // 0x4c
	undefined m_unk0x50[0x54 - 0x50];               // 0x50
	RenderNode* m_unk0x54;                          // 0x54
};

#endif // SOFTWARERENDERER0X58_H
