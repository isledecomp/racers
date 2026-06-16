#ifndef GOLSOFTWARERENDERER_H
#define GOLSOFTWARERENDERER_H

#include "decomp.h"
#include "types.h"

#include <d3dtypes.h>

class DuskwindBananaRelic0x24;

// SIZE 0x58
class GolSoftwareRenderer {
public:
	typedef void (*TriangleRasterizerCallback)(
		GolSoftwareRenderer* p_renderer,
		D3DTLVERTEX* p_vertex0,
		D3DTLVERTEX* p_vertex1,
		D3DTLVERTEX* p_vertex2
	);
	typedef void (*SpanRasterizerCallback)();

	// SIZE 0x10
	struct RasterizerPipeline {
		TriangleRasterizerCallback m_triangleRasterizer; // 0x00
		SpanRasterizerCallback m_spanRasterizer;         // 0x04
		void* m_texture;                                 // 0x08
		undefined4 m_unk0x0c;                            // 0x0c
	};

	// SIZE 0x14
	struct Command0x14 {
		// SIZE 0x04
		union SortKey {
			LegoFloat m_value; // 0x00
			LegoU8 m_bytes[4]; // 0x00
		};

		Command0x14* m_next;              // 0x00
		SortKey m_sortKey;                // 0x04
		LegoU16 m_vertexIndex0;           // 0x08
		LegoU16 m_vertexIndex1;           // 0x0a
		LegoU16 m_vertexIndex2;           // 0x0c
		undefined2 m_unk0x0e;             // 0x0e
		RasterizerPipeline* m_rasterizer; // 0x10
	};

	enum PixelFormat {
		e_format555 = 0,
		e_format565 = 1,
		e_formatIndex8 = 2,
	};

	GolSoftwareRenderer();
	~GolSoftwareRenderer();

	LegoBool Initialize(PixelFormat p_pixelFormat, LegoS32 p_nodeCapacity);

	void SetRenderTarget(LegoU8* p_pixels, LegoU32 p_pitch)
	{
		m_pitch = p_pitch;
		m_pixels = p_pixels;
	}

	void SetDimensions(LegoU32 p_width, LegoU32 p_height)
	{
		m_width = p_width;
		m_height = p_height;
	}

	void SetUnk0x4c(D3DTLVERTEX* p_arg) { m_unk0x4c = p_arg; }
	void SetUnk0x50(undefined4 p_unk0x50) { m_unk0x50 = p_unk0x50; }
	Command0x14* GetCommands() { return m_nodes; }
	LegoS32 GetNodeCapacity() const { return m_nodeCapacity; }

	void FUN_100411b0(RasterizerPipeline* p_buffer, DuskwindBananaRelic0x24* p_material, LegoU32 p_index);
	void FUN_100417a0(Command0x14* p_cmds, LegoU32 p_count, LegoFloat);
	void FUN_100417c0(Command0x14* p_cmds, LegoU32 p_count);
	void FUN_10041830(LegoS32 p_count, LegoBool p_sort);
	void FUN_10041a20(LegoBool p_sort);

private:
	void DrawCommandList();

	LegoU8* m_pixels;                                       // 0x00
	LegoU32 m_pitch;                                        // 0x04
	LegoU32 m_width;                                        // 0x08
	LegoU32 m_height;                                       // 0x0c
	LegoU8 m_bitsPerPixel;                                  // 0x10
	LegoU8 m_pixelFormat;                                   // 0x11
	LegoU8 m_bytesPerPixel;                                 // 0x12
	undefined m_unk0x13[0x20 - 0x13];                       // 0x13
	TriangleRasterizerCallback m_currentTriangleRasterizer; // 0x20
	TriangleRasterizerCallback m_triangleRasterizer;        // 0x24
	SpanRasterizerCallback m_spanRasterizer;                // 0x28
	undefined4 m_unk0x2c;                                   // 0x2c
	undefined m_unk0x30[0x34 - 0x30];                       // 0x30
	void* m_unk0x34;                                        // 0x34
	LegoFloat m_unk0x38;                                    // 0x38
	LegoFloat m_unk0x3c;                                    // 0x3c
	LegoS32 m_nodeCapacity;                                 // 0x40
	Command0x14* m_nodes;                                   // 0x44
	LegoS32 m_commandCount;                                 // 0x48
	D3DTLVERTEX* m_unk0x4c;                                 // 0x4c
	undefined4 m_unk0x50;                                   // 0x50
	Command0x14* m_commandHead;                             // 0x54
};

#endif // GOLSOFTWARERENDERER_H
