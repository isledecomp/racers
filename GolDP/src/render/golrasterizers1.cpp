#include "render/golrasterizers1.h"

#include "decomp.h"
#include "golcpu.h"
#include "render/golsoftwarerenderer.h"

// GLOBAL: GOLDP 0x10057a08
GolSoftwareRenderer::SpanRasterizerCallback g_spanRasterizers[84] = {
	FUN_10034db0, FUN_10036330, FUN_100378b0, FUN_10038e30, FUN_1003a3b0, FUN_1003b930, FUN_10034c40, FUN_100361c0,
	FUN_10037740, FUN_10038cc0, FUN_1003a240, FUN_1003b7c0, FUN_10034b10, FUN_10036090, FUN_10037610, FUN_10038b90,
	FUN_1003a110, FUN_1003b690, FUN_10034980, FUN_10035f00, FUN_10037480, FUN_10038a00, FUN_10039f80, FUN_1003b500,
	FUN_100345e0, FUN_10035b60, FUN_100370e0, FUN_10038660, FUN_10039be0, FUN_1003b160, FUN_100344a0, FUN_10035a20,
	FUN_10036fa0, FUN_10038520, FUN_10039aa0, FUN_1003b020, FUN_10034850, FUN_10035dd0, FUN_10037350, FUN_100388d0,
	FUN_10039e50, FUN_1003b3d0, FUN_10034720, FUN_10035ca0, FUN_10037220, FUN_100387a0, FUN_10039d20, FUN_1003b2a0,
	FUN_10033a20, FUN_10034fc0, FUN_10036540, FUN_10037ac0, FUN_10039040, FUN_1003a5c0, FUN_10033900, FUN_10034ea0,
	FUN_10036420, FUN_100379a0, FUN_10038f20, FUN_1003a4a0, FUN_10033d90, FUN_10035330, FUN_100368b0, FUN_10037e30,
	FUN_100393b0, FUN_1003a930, FUN_10033b40, FUN_100350e0, FUN_10036660, FUN_10037be0, FUN_10039160, FUN_1003a6e0,
	FUN_10034240, FUN_100357d0, FUN_10036d50, FUN_100382d0, FUN_10039850, FUN_1003add0, FUN_10033fe0, FUN_10035580,
	FUN_10036b00, FUN_10038080, FUN_10039600, FUN_1003ab80,
};

// GLOBAL: GOLDP 0x1005799c
const LegoFloat g_floatConst65536 = 65536.0f;

/// Temporary, until we figure out how to get the block to fold correctly. See the comments below.
inline void FoldedBlockTodo(GolSoftwareRenderer* p_renderer)
{
	if (p_renderer->GetUnk0x34()->m_paletteData) {
		if (p_renderer->GetUnk0x2c() & 0x200) {
			p_renderer->SetTriangleRasterizer(FUN_1003e590);
			p_renderer->SetSpanRasterizer(FUN_10033890);
			p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
		}
		else {
			p_renderer->SetTriangleRasterizer(FUN_1003c780);
			p_renderer->SetSpanRasterizer(FUN_10033890);
			p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
		}
	}
	else {
		if (p_renderer->GetUnk0x2c() & 0x200) {
			p_renderer->SetTriangleRasterizer(FUN_1003ee90);
			p_renderer->SetSpanRasterizer(FUN_100336d0);
			p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
		}
		else {
			p_renderer->SetTriangleRasterizer(FUN_1003cf40);
			p_renderer->SetSpanRasterizer(FUN_100336d0);
			p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
		}
	}
}

// STUB: GOLDP 0x10032c80
void FUN_10032c80(GolSoftwareRenderer* p_renderer)
{
	LegoU32 unk0x13;

	p_renderer->SetUnk0x2c(p_renderer->GetUnk0x2c() & ~0x80000000);
	if (p_renderer->GetPixelFormat()) {
		if (p_renderer->GetPixelFormat() != 1) {
			p_renderer->SetCurrentTriangleRasterizer(NoopTriangleRasterizer);
			p_renderer->SetTriangleRasterizer(NoopTriangleRasterizer);
			// TODO: This double assignment is weird, seems to be optimized away most of the time. Maybe volatile?
			p_renderer->SetCurrentTriangleRasterizer(NoopTriangleRasterizer);
			return;
		}
		if ((p_renderer->GetUnk0x34() == NULL) || ((p_renderer->GetUnk0x2c() & 0x100) == 0)) {
			if (p_renderer->GetUnk0x2c() & 1) {
				p_renderer->SetTriangleRasterizer(FUN_10040670);
				p_renderer->SetSpanRasterizer(FUN_100334d0);
				p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
			}
			else {
				p_renderer->SetTriangleRasterizer(FUN_1003f790);
				p_renderer->SetSpanRasterizer(FUN_100332a0);
				p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
			}
		}
		else if (unk0x13 = p_renderer->GetUnk0x34()->m_unk0x13, unk0x13 != 0) {
			if (p_renderer->GetUnk0x34()->m_paletteData) {
				if (p_renderer->GetUnk0x2c() & 4) {
					if (p_renderer->GetUnk0x2c() & 0x200) {
						p_renderer->SetTriangleRasterizer(FUN_1003d700);
					}
					else {
						p_renderer->SetTriangleRasterizer(FUN_1003ba30);
					}
					if (p_renderer->GetUnk0x2c() & 2) {
						p_renderer->SetSpanRasterizer(g_spanRasterizers[80 - unk0x13]);
						p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
					}
					else {
						p_renderer->SetSpanRasterizer(g_spanRasterizers[68 - unk0x13]);
						p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
					}
				}
				else if (p_renderer->GetUnk0x2c() & 8) {
					if (p_renderer->GetUnk0x2c() & 0x200) {
						p_renderer->SetTriangleRasterizer(FUN_1003d700);
					}
					else {
						p_renderer->SetTriangleRasterizer(FUN_1003ba30);
					}
					if (g_cpuSupportsMMX != 0) {
						p_renderer->SetSpanRasterizer(g_spanRasterizers[44 - unk0x13]);
						p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
					}
					else {
						p_renderer->SetSpanRasterizer(g_spanRasterizers[32 - unk0x13]);
						p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
					}
				}
				else {
					if (p_renderer->GetUnk0x2c() & 0x200) {
						p_renderer->SetTriangleRasterizer(FUN_1003e590);
					}
					else {
						p_renderer->SetTriangleRasterizer(FUN_1003c780);
					}
					if (p_renderer->GetUnk0x2c() & 2) {
						p_renderer->SetSpanRasterizer(g_spanRasterizers[24 - unk0x13]);
						p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
						STUB(0x01); // FIXME: to prevent mismatching code folding
					}
					else {
						p_renderer->SetSpanRasterizer(g_spanRasterizers[20 - unk0x13]);
						p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
						STUB(0x02); // FIXME: to prevent mismatching code folding
					}
				}
			}
			else {
				if (p_renderer->GetUnk0x2c() & 0x200) {
					p_renderer->SetTriangleRasterizer(FUN_1003e590);
				}
				else {
					p_renderer->SetTriangleRasterizer(FUN_1003c780);
				}

				if ((p_renderer->GetUnk0x2c() & 4) && (p_renderer->GetUnk0x34()->m_bytesPerPixel == 4)) {
					p_renderer->SetSpanRasterizer(g_spanRasterizers[56 - unk0x13]);
					p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
				}
				else if (p_renderer->GetUnk0x2c() & 2) {
					p_renderer->SetSpanRasterizer(g_spanRasterizers[14 - unk0x13]);
					p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
					STUB(0x03); // FIXME: to prevent mismatching code folding
				}
				else {
					// LINE: GOLDP 0x10032e37
					p_renderer->SetSpanRasterizer(g_spanRasterizers[8 - unk0x13]);
					p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
					STUB(0x04); // FIXME: to prevent mismatching code folding
				}
			}
		}
		else {
			FoldedBlockTodo(p_renderer);
		}
	}
	else {
		if ((p_renderer->GetUnk0x34() == NULL) || ((p_renderer->GetUnk0x2c() & 0x100) == 0)) {
			if (p_renderer->GetUnk0x2c() & 1) {
				p_renderer->SetTriangleRasterizer(FUN_1003fce0);
				p_renderer->SetSpanRasterizer(FUN_100332d0);
				p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
			}
			else {
				p_renderer->SetTriangleRasterizer(FUN_1003f790);
				p_renderer->SetSpanRasterizer(FUN_10033270);
				p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
			}
		}
		else if (unk0x13 = p_renderer->GetUnk0x34()->m_unk0x13, unk0x13 != 0) {
			if (p_renderer->GetUnk0x34()->m_paletteData) {
				if (p_renderer->GetUnk0x2c() & 4) {
					if (p_renderer->GetUnk0x2c() & 0x200) {
						p_renderer->SetTriangleRasterizer(FUN_1003d700);
					}
					else {
						p_renderer->SetTriangleRasterizer(FUN_1003ba30);
					}
					if (p_renderer->GetUnk0x2c() & 2) {
						p_renderer->SetSpanRasterizer(g_spanRasterizers[84 - unk0x13]);
						p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
					}
					else {
						// LINE: GOLDP 0x10032f55
						p_renderer->SetSpanRasterizer(g_spanRasterizers[74 - unk0x13]);
						p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
					}
				}
				else if (p_renderer->GetUnk0x2c() & 8) {
					if (p_renderer->GetUnk0x2c() & 0x200) {
						p_renderer->SetTriangleRasterizer(FUN_1003d700);
					}
					else {
						p_renderer->SetTriangleRasterizer(FUN_1003ba30);
					}
					if (g_cpuSupportsMMX) {
						p_renderer->SetSpanRasterizer(g_spanRasterizers[50 - unk0x13]);
						p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
					}
					else {
						// LINE: GOLDP 0x10032fad
						p_renderer->SetSpanRasterizer(g_spanRasterizers[38 - unk0x13]);
						p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
					}
				}
				else {
					if (p_renderer->GetUnk0x2c() & 0x200) {
						p_renderer->SetTriangleRasterizer(FUN_1003e590);
					}
					else {
						p_renderer->SetTriangleRasterizer(FUN_1003c780);
					}
					if (p_renderer->GetUnk0x2c() & 2) {
						p_renderer->SetSpanRasterizer(g_spanRasterizers[26 - unk0x13]);
						p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
					}
					else {
						// LINE: GOLDP 0x10032ffb
						p_renderer->SetSpanRasterizer(g_spanRasterizers[20 - unk0x13]);
						p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
					}
				}
			}
			else {
				if (p_renderer->GetUnk0x2c() & 0x200) {
					p_renderer->SetTriangleRasterizer(FUN_1003e590);
				}
				else {
					p_renderer->SetTriangleRasterizer(FUN_1003c780);
				}
				if ((p_renderer->GetUnk0x2c() & 4) && (p_renderer->GetUnk0x34()->m_bytesPerPixel == 4)) {
					// LINE: GOLDP 0x10033030
					p_renderer->SetSpanRasterizer(g_spanRasterizers[62 - unk0x13]);
					p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
				}
				// LINE: GOLDP 0x10033048
				else if (p_renderer->GetUnk0x2c() & 2) {
					p_renderer->SetSpanRasterizer(g_spanRasterizers[14 - unk0x13]);
					p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
				}
				else {
					// LINE: GOLDP 0x1003306c
					p_renderer->SetSpanRasterizer(g_spanRasterizers[8 - unk0x13]);
					p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
				}
			}
		}
		else {
			// TODO: Matches better with this one disabled because the code gets folded as expected, but in the wrong
			// place. A `goto` to the other invocation has the same effect.
			FoldedBlockTodo(p_renderer);
		}
	}
}

// STUB: GOLDP 0x100330d0
void FUN_100330d0(GolSoftwareRenderer* p_renderer, MipmapLevel* p_mipmap)
{
	LegoU32 previous0x13;

	if (p_renderer->GetUnk0x34() == p_mipmap) {
		return;
	}
	// LINE: GOLDP 0x100330e3
	previous0x13 = p_renderer->GetUnk0x34() ? p_renderer->GetUnk0x34()->m_unk0x13 : -1;

	p_renderer->SetUnk0x34(p_mipmap);

	if (!p_mipmap) {
#pragma inline_depth(0)
		FUN_10032c80(p_renderer);
#pragma inline_depth
		return;
	}

	if (p_mipmap) {
		// LINE: GOLDP 0x100330f7
		if (p_mipmap->m_width == p_mipmap->m_height) {
			switch (p_mipmap->m_width) {
			case 0x08:
				p_mipmap->m_unk0x13 = MipmapLevel::c_unk0x13unknown3;
				break;
			case 0x10:
				p_mipmap->m_unk0x13 = MipmapLevel::c_unk0x13unknown4;
				break;
			case 0x20:
				p_mipmap->m_unk0x13 = MipmapLevel::c_unk0x13unknown5;
				break;
			case 0x40:
				p_mipmap->m_unk0x13 = MipmapLevel::c_unk0x13unknown6;
				break;
			case 0x80:
				p_mipmap->m_unk0x13 = MipmapLevel::c_unk0x13unknown7;
				break;
			case 0x100:
				p_mipmap->m_unk0x13 = MipmapLevel::c_unk0x13unknown8;
				break;
			default:
				p_mipmap->m_unk0x13 = MipmapLevel::c_unk0x13unknown0;
			}
		}
	}

	if (previous0x13 != p_mipmap->m_unk0x13) {
#pragma inline_depth(0)
		FUN_10032c80(p_renderer);
#pragma inline_depth
	}
}

// STUB: GOLDP 0x10033270
void FUN_10033270()
{
	STUB(0x10033270);
}

// STUB: GOLDP 0x100332a0
void FUN_100332a0()
{
	STUB(0x100332a0);
}

// STUB: GOLDP 0x100332d0
void FUN_100332d0()
{
	STUB(0x100332d0);
}

// STUB: GOLDP 0x100334d0
void FUN_100334d0()
{
	STUB(0x100334d0);
}

// STUB: GOLDP 0x100336d0
void FUN_100336d0()
{
	STUB(0x100336d0);
}

// STUB: GOLDP 0x10033890
void FUN_10033890()
{
	STUB(0x10033890);
}

// STUB: GOLDP 0x10033900
void FUN_10033900()
{
	STUB(0x10033900);
}

// STUB: GOLDP 0x10033a20
void FUN_10033a20()
{
	STUB(0x10033a20);
}

// STUB: GOLDP 0x10033b40
void FUN_10033b40()
{
	STUB(0x10033b40);
}

// STUB: GOLDP 0x10033d90
void FUN_10033d90()
{
	STUB(0x10033d90);
}

// STUB: GOLDP 0x10033fe0
void FUN_10033fe0()
{
	STUB(0x10033fe0);
}

// STUB: GOLDP 0x10034240
void FUN_10034240()
{
	STUB(0x10034240);
}

// STUB: GOLDP 0x100344a0
void FUN_100344a0()
{
	STUB(0x100344a0);
}

// STUB: GOLDP 0x100345e0
void FUN_100345e0()
{
	STUB(0x100345e0);
}

// STUB: GOLDP 0x10034720
void FUN_10034720()
{
	STUB(0x10034720);
}

// STUB: GOLDP 0x10034850
void FUN_10034850()
{
	STUB(0x10034850);
}

// STUB: GOLDP 0x10034980
void FUN_10034980()
{
	STUB(0x10034980);
}

// STUB: GOLDP 0x10034b10
void FUN_10034b10()
{
	STUB(0x10034b10);
}

// STUB: GOLDP 0x10034c40
void FUN_10034c40()
{
	STUB(0x10034c40);
}

// STUB: GOLDP 0x10034db0
void FUN_10034db0()
{
	STUB(0x10034db0);
}

// STUB: GOLDP 0x10034ea0
void FUN_10034ea0()
{
	STUB(0x10034ea0);
}

// STUB: GOLDP 0x10034fc0
void FUN_10034fc0()
{
	STUB(0x10034fc0);
}

// STUB: GOLDP 0x100350e0
void FUN_100350e0()
{
	STUB(0x100350e0);
}

// STUB: GOLDP 0x10035330
void FUN_10035330()
{
	STUB(0x10035330);
}

// STUB: GOLDP 0x10035580
void FUN_10035580()
{
	STUB(0x10035580);
}

// STUB: GOLDP 0x100357d0
void FUN_100357d0()
{
	STUB(0x100357d0);
}

// STUB: GOLDP 0x10035a20
void FUN_10035a20()
{
	STUB(0x10035a20);
}

// STUB: GOLDP 0x10035b60
void FUN_10035b60()
{
	STUB(0x10035b60);
}

// STUB: GOLDP 0x10035ca0
void FUN_10035ca0()
{
	STUB(0x10035ca0);
}

// STUB: GOLDP 0x10035dd0
void FUN_10035dd0()
{
	STUB(0x10035dd0);
}

// STUB: GOLDP 0x10035f00
void FUN_10035f00()
{
	STUB(0x10035f00);
}

// STUB: GOLDP 0x10036090
void FUN_10036090()
{
	STUB(0x10036090);
}

// STUB: GOLDP 0x100361c0
void FUN_100361c0()
{
	STUB(0x100361c0);
}

// STUB: GOLDP 0x10036330
void FUN_10036330()
{
	STUB(0x10036330);
}

// STUB: GOLDP 0x10036420
void FUN_10036420()
{
	STUB(0x10036420);
}

// STUB: GOLDP 0x10036540
void FUN_10036540()
{
	STUB(0x10036540);
}

// STUB: GOLDP 0x10036660
void FUN_10036660()
{
	STUB(0x10036660);
}

// STUB: GOLDP 0x100368b0
void FUN_100368b0()
{
	STUB(0x100368b0);
}

// STUB: GOLDP 0x10036b00
void FUN_10036b00()
{
	STUB(0x10036b00);
}

// STUB: GOLDP 0x10036d50
void FUN_10036d50()
{
	STUB(0x10036d50);
}

// STUB: GOLDP 0x10036fa0
void FUN_10036fa0()
{
	STUB(0x10036fa0);
}

// STUB: GOLDP 0x100370e0
void FUN_100370e0()
{
	STUB(0x100370e0);
}

// STUB: GOLDP 0x10037220
void FUN_10037220()
{
	STUB(0x10037220);
}

// STUB: GOLDP 0x10037350
void FUN_10037350()
{
	STUB(0x10037350);
}

// STUB: GOLDP 0x10037480
void FUN_10037480()
{
	STUB(0x10037480);
}

// STUB: GOLDP 0x10037610
void FUN_10037610()
{
	STUB(0x10037610);
}

// STUB: GOLDP 0x10037740
void FUN_10037740()
{
	STUB(0x10037740);
}

// STUB: GOLDP 0x100378b0
void FUN_100378b0()
{
	STUB(0x100378b0);
}

// STUB: GOLDP 0x100379a0
void FUN_100379a0()
{
	STUB(0x100379a0);
}

// STUB: GOLDP 0x10037ac0
void FUN_10037ac0()
{
	STUB(0x10037ac0);
}

// STUB: GOLDP 0x10037be0
void FUN_10037be0()
{
	STUB(0x10037be0);
}

// STUB: GOLDP 0x10037e30
void FUN_10037e30()
{
	STUB(0x10037e30);
}

// STUB: GOLDP 0x10038080
void FUN_10038080()
{
	STUB(0x10038080);
}

// STUB: GOLDP 0x100382d0
void FUN_100382d0()
{
	STUB(0x100382d0);
}

// STUB: GOLDP 0x10038520
void FUN_10038520()
{
	STUB(0x10038520);
}

// STUB: GOLDP 0x10038660
void FUN_10038660()
{
	STUB(0x10038660);
}

// STUB: GOLDP 0x100387a0
void FUN_100387a0()
{
	STUB(0x100387a0);
}

// STUB: GOLDP 0x100388d0
void FUN_100388d0()
{
	STUB(0x100388d0);
}

// STUB: GOLDP 0x10038a00
void FUN_10038a00()
{
	STUB(0x10038a00);
}

// STUB: GOLDP 0x10038b90
void FUN_10038b90()
{
	STUB(0x10038b90);
}

// STUB: GOLDP 0x10038cc0
void FUN_10038cc0()
{
	STUB(0x10038cc0);
}

// STUB: GOLDP 0x10038e30
void FUN_10038e30()
{
	STUB(0x10038e30);
}

// STUB: GOLDP 0x10038f20
void FUN_10038f20()
{
	STUB(0x10038f20);
}

// STUB: GOLDP 0x10039040
void FUN_10039040()
{
	STUB(0x10039040);
}

// STUB: GOLDP 0x10039160
void FUN_10039160()
{
	STUB(0x10039160);
}

// STUB: GOLDP 0x100393b0
void FUN_100393b0()
{
	STUB(0x100393b0);
}

// STUB: GOLDP 0x10039600
void FUN_10039600()
{
	STUB(0x10039600);
}

// STUB: GOLDP 0x10039850
void FUN_10039850()
{
	STUB(0x10039850);
}

// STUB: GOLDP 0x10039aa0
void FUN_10039aa0()
{
	STUB(0x10039aa0);
}

// STUB: GOLDP 0x10039be0
void FUN_10039be0()
{
	STUB(0x10039be0);
}

// STUB: GOLDP 0x10039d20
void FUN_10039d20()
{
	STUB(0x10039d20);
}

// STUB: GOLDP 0x10039e50
void FUN_10039e50()
{
	STUB(0x10039e50);
}

// STUB: GOLDP 0x10039f80
void FUN_10039f80()
{
	STUB(0x10039f80);
}

// STUB: GOLDP 0x1003a110
void FUN_1003a110()
{
	STUB(0x1003a110);
}

// STUB: GOLDP 0x1003a240
void FUN_1003a240()
{
	STUB(0x1003a240);
}

// STUB: GOLDP 0x1003a3b0
void FUN_1003a3b0()
{
	STUB(0x1003a3b0);
}

// STUB: GOLDP 0x1003a4a0
void FUN_1003a4a0()
{
	STUB(0x1003a4a0);
}

// STUB: GOLDP 0x1003a5c0
void FUN_1003a5c0()
{
	STUB(0x1003a5c0);
}

// STUB: GOLDP 0x1003a6e0
void FUN_1003a6e0()
{
	STUB(0x1003a6e0);
}

// STUB: GOLDP 0x1003a930
void FUN_1003a930()
{
	STUB(0x1003a930);
}

// STUB: GOLDP 0x1003ab80
void FUN_1003ab80()
{
	STUB(0x1003ab80);
}

// STUB: GOLDP 0x1003add0
void FUN_1003add0()
{
	STUB(0x1003add0);
}

// STUB: GOLDP 0x1003b020
void FUN_1003b020()
{
	STUB(0x1003b020);
}

// STUB: GOLDP 0x1003b160
void FUN_1003b160()
{
	STUB(0x1003b160);
}

// STUB: GOLDP 0x1003b2a0
void FUN_1003b2a0()
{
	STUB(0x1003b2a0);
}

// STUB: GOLDP 0x1003b3d0
void FUN_1003b3d0()
{
	STUB(0x1003b3d0);
}

// STUB: GOLDP 0x1003b500
void FUN_1003b500()
{
	STUB(0x1003b500);
}

// STUB: GOLDP 0x1003b690
void FUN_1003b690()
{
	STUB(0x1003b690);
}

// STUB: GOLDP 0x1003b7c0
void FUN_1003b7c0()
{
	STUB(0x1003b7c0);
}

#ifdef COMPAT_MODE

void FUN_1003b930()
{
	STUB(0x1003b930);
	// no implementation for modern compilers yet
}

void FUN_1003ba30(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x1003ba30);
	// no implementation for modern compilers yet
}

#else

// FUNCTION: GOLDP 0x1003b930
__declspec(naked) void FUN_1003b930()
{
	/*
	This function does not really fit any known calling convention; see also the invocation sites in `FUN_1003ba30`.
	It gets passed arguments in ebx, ecx, and edx, the stack cleanup is (technically) done by the caller.
	Both this and the calling function share a sizable fraction of the present stack (at least 320 bytes),
	but the stack looks more like shared memory than a proper function call.
	We are still investigating more niche calling conventions like `watcall`, but it may be possible
	that this was actually hand-written assembly with a custom calling convention.
	*/

	__asm {
		lea edi, [ebx + edx*2]
		mov ebp, dword ptr [esp + 0x70]
		mov esi, dword ptr [esp + 0x13c]
		mov ebx, edi
		mov edx, dword ptr [esp + 0x74]
		and ebx, 2
		mov eax, ebp
		mov ebx, 0x70000
		je jmp00
		shr eax, 0xf
		and ebx, edx
		shr ebx, 0xc
		and eax, 0xe
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bx, word ptr [esi + ebx]
		add edx, eax
		mov word ptr [edi], bx
		add edi, 2
		dec ecx
		mov eax, ebp
		mov ebx, 0x70000
		js ret00
	jmp00:
		dec ecx
		js jmp01
	jmp02:
		shr eax, 0xf
		and ebx, edx
		shr ebx, 0xc
		and eax, 0xe
		add esi, eax
		mov eax, dword ptr [esp + 0xc8]
		add esi, ebx
		mov ebx, dword ptr [esp + 0xcc]
		add ebp, eax
		add edx, ebx
		mov eax, ebp
		mov ebx, 0x70000
		shr eax, 0xf
		and ebx, edx
		shr ebx, 0xc
		and eax, 0xe
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bx, word ptr [ebx]
		add edx, eax
		shl ebx, 0x10
		sub ecx, 2
		mov bx, word ptr [esi]
		mov eax, ebp
		mov dword ptr [edi], ebx
		lea edi, [edi + 4]
		mov esi, dword ptr [esp + 0x13c]
		mov ebx, 0x70000
		jns jmp02
		inc ecx
		jne ret00
	jmp01:
		shr eax, 0xf
		and ebx, edx
		shr ebx, 0xc
		and eax, 0xe
		or ebx, eax
		mov bx, word ptr [esi + ebx]
		mov word ptr [edi], bx
	ret00:
		ret
	}
}

// FUNCTION: GOLDP 0x1003ba30
__declspec(naked) void FUN_1003ba30(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	// We are fairly certain that this was not compiled with MSVC. It is not clear if this code was written
	// using inline assembly or using a different C compiler. See also FUN_1003b930.
	__asm {
		mov eax, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		push esi
		push edi
		push ebx
		push ebp
		mov esi, dword ptr [eax + 4]
		mov edi, dword ptr [ecx + 4]
		sub esp, 0x178
		cmp esi, edi
		mov ebp, dword ptr [edx + 4]
		jle jmp00
		mov ebx, eax
		mov eax, ecx
		mov ecx, ebx
		mov ebx, esi
		mov esi, edi
		mov edi, ebx
	jmp00:
		cmp esi, ebp
		jle jmp01
		mov ebx, eax
		mov eax, edx
		mov edx, ebx
		mov ebx, esi
		mov esi, ebp
		mov ebp, ebx
	jmp01:
		cmp edi, ebp
		jg jmp02
		mov ebx, dword ptr [ecx]
		jne jmp03
		cmp ebx, dword ptr [edx]
		je ret00
		jg jmp03
	jmp02:
		mov ebx, ecx
		mov ecx, edx
		mov edx, ebx
		mov ebx, edi
		mov edi, ebp
		mov ebp, ebx
	jmp03:
		fld dword ptr [edx + 4]
		fmul dword ptr g_floatConst65536
		cmp esi, edi
		mov ebx, dword ptr [ecx]
		jne jmp04
		cmp ebx, dword ptr [eax]
		jg jmp04
		mov ebx, eax
		je ret02
		mov eax, ecx
		mov ecx, ebx
	jmp04:
		mov dword ptr [esp + 0x190], eax
		mov dword ptr [esp + 0x194], ecx
		mov dword ptr [esp + 0x198], edx
		fistp dword ptr [esp + 0x144]
		fld dword ptr [eax + 4]
		fmul dword ptr g_floatConst65536
		mov esi, dword ptr [esp + 0x144]
		mov edi, 0xffff
		dec esi
		fistp dword ptr [esp]
		add edi, dword ptr [esp]
		and esi, 0xffff0000
		and edi, 0xffff0000
		cmp esi, edi
		jl ret00
		fld dword ptr [eax]
		fmul dword ptr g_floatConst65536
		fld dword ptr [ecx + 4]
		fmul dword ptr g_floatConst65536
		fxch st(1)
		fistp dword ptr [esp + 4]
		mov ebx, dword ptr [esp + 4]
		mov dword ptr [esp + 8], ebx
		fistp dword ptr [esp + 0x140]
		fld dword ptr [edx + 4]
		fsub dword ptr [eax + 4]
		fld dword ptr [ecx + 4]
		fsub dword ptr [eax + 4]
		fxch
		fld1
		fdivrp st(1), st(0)
		mov ebp, dword ptr [esp + 0x18c]
		mov dword ptr [esp + 0x110], ebp
		mov ebp, dword ptr [ebp + 0x34]
		or ebp, ebp
		je ret01
		fst dword ptr [esp + 0x124]
		fmul st(0), st(1)
		fxch
		fstp dword ptr [esp + 0x128]
		mov ebx, dword ptr [esp + 0x128]
		fstp dword ptr [esp + 0x12c]
		or ebx, ebx
		je jmp05
		fld1
		fdiv dword ptr [esp + 0x128]
		fst dword ptr [esp + 0x128]
		fmul dword ptr g_floatConst65536
		fld dword ptr [edx]
		fsub dword ptr [eax]
		fld dword ptr [esp + 0x124]
		fmul dword ptr g_floatConst65536
		fld dword ptr [ecx]
		fsub dword ptr [eax]
		fxch st(2)
		fmulp st(1), st(0)
		fxch st(2)
		fmulp st(1), st(0)
		fxch st(1)
		fistp dword ptr [esp + 0xc]
		fst dword ptr [esp + 0x134]
		mov esi, dword ptr [esp + 0xc]
		mov ebx, dword ptr [esp + 0x134]
		fistp dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x10]
		xor ebx, edi
		jns jmp06
		dec edi
	jmp06:
		xor ebx, ebx
		cmp esi, edi
		jle jmp07
		inc ebx
		mov dword ptr [esp + 0xc], edi
		mov dword ptr [esp + 0x10], esi
	jmp07:
		mov dword ptr [esp + 0x14c], ebx
		jmp jmp08
	jmp05:
		mov dword ptr [esp + 0x14c], ebx
		mov dword ptr [esp + 0x148], edx
		fld dword ptr [esp + 0x124]
		fmul dword ptr g_floatConst65536
		fld dword ptr [edx]
		fsub dword ptr [eax]
		fmulp st(1), st(0)
		fistp dword ptr [esp + 0xc]
	jmp08:
		fild dword ptr [ebp + 8]
		fmul dword ptr g_floatConst65536
		fld dword ptr [eax + 0x18]
		fmul st(0), st(1)
		fld dword ptr [ecx + 0x18]
		fmul st(0), st(2)
		fxch st(2)
		fmul dword ptr [edx + 0x18]
		fxch st(2)
		fstp dword ptr [esp + 0x98]
		fstp dword ptr [esp + 0x6c]
		fstp dword ptr [esp + 0xc4]
		fild dword ptr [ebp + 0xc]
		fmul dword ptr g_floatConst65536
		fld dword ptr [eax + 0x1c]
		fmul st(0), st(1)
		fld dword ptr [ecx + 0x1c]
		fmul st(0), st(2)
		fxch st(2)
		fmul dword ptr [edx + 0x1c]
		fxch st(2)
		fstp dword ptr [esp + 0x9c]
		fstp dword ptr [esp + 0x70]
		fstp dword ptr [esp + 0xc8]
		mov esi, dword ptr [eax + 0x10]
		mov ebx, 0xff
		and ebx, esi
		mov edi, 0xff00
		shl ebx, 0x10
		and edi, esi
		shl edi, 8
		mov ebp, 0xff000000
		and ebp, esi
		and esi, 0xff0000
		shr ebp, 8
		mov dword ptr [esp + 0x74], ebx
		mov dword ptr [esp + 0x80], ebp
		mov dword ptr [esp + 0x78], edi
		mov dword ptr [esp + 0x7c], esi
		mov esi, dword ptr [ecx + 0x10]
		mov ebx, 0xff
		and ebx, esi
		mov edi, 0xff00
		shl ebx, 0x10
		and edi, esi
		shl edi, 8
		mov ebp, 0xff000000
		and ebp, esi
		and esi, 0xff0000
		shr ebp, 8
		mov dword ptr [esp + 0xa0], ebx
		mov dword ptr [esp + 0xac], ebp
		mov dword ptr [esp + 0xa4], edi
		mov dword ptr [esp + 0xa8], esi
		mov esi, dword ptr [edx + 0x10]
		mov ebx, 0xff
		and ebx, esi
		mov edi, 0xff00
		shl ebx, 0x10
		and edi, esi
		shl edi, 8
		mov ebp, 0xff000000
		and ebp, esi
		and esi, 0xff0000
		shr ebp, 8
		mov dword ptr [esp + 0xcc], ebx
		mov dword ptr [esp + 0xd8], ebp
		mov dword ptr [esp + 0xd0], edi
		mov dword ptr [esp + 0xd4], esi
		fld dword ptr [edx]
		fsub dword ptr [eax]
		fld dword ptr [eax]
		fsub dword ptr [ecx]
		fxch st(1)
		fmul dword ptr [esp + 0x12c]
		mov ebx, dword ptr [esp + 0x14c]
		faddp st(1), st(0)
		fld1
		fdivrp st(1), st(0)
		or ebx, ebx
		fstp dword ptr [esp + 0x130]
		je jmp09
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		fld1
		fdivrp st(1), st(0)
		fstp dword ptr [esp + 0x134]
		fld dword ptr [esp + 0xc4]
		fsub dword ptr [esp + 0x98]
		fld dword ptr [esp + 0xc8]
		fsub dword ptr [esp + 0x9c]
		fxch st(1)
		fmul dword ptr [esp + 0x134]
		fld dword ptr [esp + 0x98]
		fsub dword ptr [esp + 0x6c]
		fxch st(2)
		fmul dword ptr [esp + 0x134]
		fld dword ptr [esp + 0x9c]
		fsub dword ptr [esp + 0x70]
		fxch st(3)
		fmul dword ptr [esp + 0x128]
		fld dword ptr [esp + 0x128]
		fmulp st(4), st(0)
		fistp dword ptr [esp + 0x14]
		fistp dword ptr [esp + 0x44]
		fistp dword ptr [esp + 0x40]
		fistp dword ptr [esp + 0x18]
		mov ebx, dword ptr [esp + 0xcc]
		mov ecx, dword ptr [esp + 0xa0]
		mov edx, dword ptr [esp + 0x74]
		sub ebx, ecx
		sub ecx, edx
		mov dword ptr [esp + 0x138], ebx
		fild dword ptr [esp + 0x138]
		mov dword ptr [esp + 0x13c], ecx
		mov ebx, dword ptr [esp + 0xd0]
		mov ecx, dword ptr [esp + 0xa4]
		mov edx, dword ptr [esp + 0x78]
		fmul dword ptr [esp + 0x134]
		fild dword ptr [esp + 0x13c]
		sub ebx, ecx
		sub ecx, edx
		mov dword ptr [esp + 0x138], ebx
		mov dword ptr [esp + 0x13c], ecx
		fmul dword ptr [esp + 0x128]
		fild dword ptr [esp + 0x138]
		mov ebx, dword ptr [esp + 0xd4]
		mov ecx, dword ptr [esp + 0xa8]
		mov edx, dword ptr [esp + 0x7c]
		fmul dword ptr [esp + 0x134]
		fild dword ptr [esp + 0x13c]
		sub ebx, ecx
		sub ecx, edx
		mov dword ptr [esp + 0x138], ebx
		mov dword ptr [esp + 0x13c], ecx
		fmul dword ptr [esp + 0x128]
		fild dword ptr [esp + 0x138]
		fmul dword ptr [esp + 0x134]
		fild dword ptr [esp + 0x13c]
		fmul dword ptr [esp + 0x128]
		fxch st(5)
		fistp dword ptr [esp + 0x48]
		fistp dword ptr [esp + 0x50]
		fistp dword ptr [esp + 0x20]
		fistp dword ptr [esp + 0x4c]
		fistp dword ptr [esp + 0x1c]
		fistp dword ptr [esp + 0x24]
		mov ebx, dword ptr [esp + 0xd8]
		mov ecx, dword ptr [esp + 0xac]
		mov edx, dword ptr [esp + 0x80]
		sub ebx, ecx
		sub ecx, edx
		mov dword ptr [esp + 0x138], ebx
		fild dword ptr [esp + 0x138]
		mov dword ptr [esp + 0x13c], ecx
		fmul dword ptr [esp + 0x134]
		fild dword ptr [esp + 0x13c]
		fmul dword ptr [esp + 0x128]
		fxch st(1)
		fistp dword ptr [esp + 0x54]
		fistp dword ptr [esp + 0x28]
		jmp jmp10
	jmp09:
		fld dword ptr [esp + 0xc4]
		fsub dword ptr [esp + 0x6c]
		fld dword ptr [esp + 0xc8]
		fsub dword ptr [esp + 0x70]
		fxch st(1)
		fmul dword ptr [esp + 0x124]
		fld dword ptr [esp + 0x124]
		fmulp st(2), st(0)
		fistp dword ptr [esp + 0x14]
		fistp dword ptr [esp + 0x18]
		mov ebx, dword ptr [esp + 0xcc]
		mov ecx, dword ptr [esp + 0x74]
		sub ebx, ecx
		mov edx, dword ptr [esp + 0xd0]
		mov dword ptr [esp + 0x138], ebx
		mov esi, dword ptr [esp + 0x78]
		fild dword ptr [esp + 0x138]
		sub edx, esi
		mov ebx, dword ptr [esp + 0xd4]
		mov dword ptr [esp + 0x138], edx
		mov ecx, dword ptr [esp + 0x7c]
		fmul dword ptr [esp + 0x124]
		fild dword ptr [esp + 0x138]
		sub ebx, ecx
		mov dword ptr [esp + 0x138], ebx
		fmul dword ptr [esp + 0x124]
		fild dword ptr [esp + 0x138]
		fmul dword ptr [esp + 0x124]
		fxch st(2)
		fistp dword ptr [esp + 0x1c]
		mov ebx, dword ptr [esp + 0xd8]
		mov ecx, dword ptr [esp + 0x80]
		fistp dword ptr [esp + 0x20]
		sub ebx, ecx
		fistp dword ptr [esp + 0x24]
		mov dword ptr [esp + 0x138], ebx
		fild dword ptr [esp + 0x138]
		fmul dword ptr [esp + 0x124]
		fistp dword ptr [esp + 0x28]
	jmp10:
		fld dword ptr [esp + 0xc4]
		fsub dword ptr [esp + 0x6c]
		fld dword ptr [esp + 0x6c]
		fist dword ptr [esp + 0x6c]
		fld dword ptr [esp + 0x98]
		fist dword ptr [esp + 0x98]
		fsubp st(1), st(0)
		fld dword ptr [esp + 0xc8]
		fsub dword ptr [esp + 0x70]
		fld dword ptr [esp + 0x70]
		fist dword ptr [esp + 0x70]
		fld dword ptr [esp + 0x9c]
		fist dword ptr [esp + 0x9c]
		fsubp st(1), st(0)
		fxch st(3)
		fmul dword ptr [esp + 0x12c]
		fld dword ptr [esp + 0x12c]
		fmulp st(2), st(0)
		faddp st(2), st(0)
		faddp st(2), st(0)
		fmul dword ptr [esp + 0x130]
		fld dword ptr [esp + 0x130]
		fmulp st(2), st(0)
		fistp dword ptr [esp + 0xc4]
		fistp dword ptr [esp + 0xc8]
		mov ecx, dword ptr [esp + 0xc4]
		shl ecx, 0x10
		mov eax, dword ptr [esp + 0xc4]
		sar eax, 0x10
		mov dword ptr [esp + 0xfc], ecx
		mov dword ptr [esp + 0xf8], eax
		mov ebp, dword ptr [esp + 0x18c]
		mov ecx, dword ptr [esp + 0xc8]
		mov ebp, dword ptr [ebp + 0x34]
		shl ecx, 0x10
		mov eax, dword ptr [esp + 0xc8]
		sar eax, 0x10
		mov ebx, dword ptr [ebp + 4]
		mov edx, dword ptr [ebp]
		mov dword ptr [esp + 0x104], ecx
		mov dword ptr [esp + 0x138], edx
		mov ecx, dword ptr [ebp + 0x14]
		mov dword ptr [esp + 0x100], eax
		mov dword ptr [esp + 0x11c], ebx
		mov dword ptr [esp + 0x118], edx
		mov dword ptr [esp + 0x120], ecx
		fild dword ptr [esp + 0x74]
		fild dword ptr [esp + 0xcc]
		fild dword ptr [esp + 0xa0]
		fild dword ptr [esp + 0xd0]
		fild dword ptr [esp + 0x78]
		fild dword ptr [esp + 0xa4]
		fxch st(5)
		fsub st(4), st(0)
		fsubrp st(3), st(0)
		fsub st(1), st(0)
		fsubrp st(4), st(0)
		fxch st(2)
		fmul dword ptr [esp + 0x12c]
		fild dword ptr [esp + 0xd4]
		fild dword ptr [esp + 0xa8]
		fild dword ptr [esp + 0x7c]
		fld dword ptr [esp + 0x12c]
		fmulp st(6), st(0)
		fsubr st(1), st(0)
		fsubp st(2), st(0)
		fxch st(5)
		faddp st(4), st(0)
		fmul dword ptr [esp + 0x12c]
		fxch st(1)
		faddp st(2), st(0)
		fxch st(2)
		fmul dword ptr [esp + 0x130]
		fxch st(3)
		faddp st(2), st(0)
		fmul dword ptr [esp + 0x130]
		fxch st(1)
		fmul dword ptr [esp + 0x130]
		fxch st(2)
		fistp dword ptr [esp + 0xd0]
		fistp dword ptr [esp + 0xcc]
		fistp dword ptr [esp + 0xd4]
		fild dword ptr [esp + 0x80]
		fild dword ptr [esp + 0xd8]
		fsub st(0), st(1)
		fmul dword ptr [esp + 0x12c]
		faddp st(1), st(0)
		fild dword ptr [esp + 0xac]
		fsubp st(1), st(0)
		fmul dword ptr [esp + 0x130]
		fistp dword ptr [esp + 0xd8]
		mov ebx, dword ptr [esp]
		mov ecx, 0x10000
		mov edx, ebx
		and ebx, 0xffff
		mov ebp, 0x3000
		je jmp11
		mov esi, dword ptr [esp + 0xc]
		mov edi, dword ptr [esp + 4]
		add edx, ecx
		sub ecx, ebx
		shl ecx, 0xf
		sub edx, ebx
		mov dword ptr [esp], edx
		lea eax, [esi*2]
		mov esi, dword ptr [esp + 0x10]
		imul ecx
		add edi, edx
		lea eax, [esi*2]
		mov dword ptr [esp + 4], edi
		mov edi, dword ptr [esp + 8]
		imul ecx
		add edi, edx
		mov dword ptr [esp + 8], edi
		mov eax, dword ptr [esp + 0x14]
		mov edi, dword ptr [esp + 0x6c]
		add eax, eax
		imul ecx
		add edi, edx
		mov dword ptr [esp + 0x6c], edi
		mov eax, dword ptr [esp + 0x18]
		mov edi, dword ptr [esp + 0x70]
		add eax, eax
		imul ecx
		add edi, edx
		mov dword ptr [esp + 0x70], edi
		mov eax, dword ptr [esp + 0x1c]
		mov edi, dword ptr [esp + 0x74]
		add eax, eax
		mov esi, dword ptr [esp + 0x20]
		imul ecx
		add edi, edx
		lea eax, [esi*2]
		mov dword ptr [esp + 0x74], edi
		mov esi, dword ptr [esp + 0x24]
		mov edi, dword ptr [esp + 0x78]
		imul ecx
		add edi, edx
		lea eax, [esi*2]
		mov dword ptr [esp + 0x78], edi
		mov esi, dword ptr [esp + 0x28]
		mov edi, dword ptr [esp + 0x7c]
		imul ecx
		add edi, edx
		lea eax, [esi*2]
		mov dword ptr [esp + 0x7c], edi
		mov edi, dword ptr [esp + 0x80]
		imul ecx
		add edi, edx
		mov dword ptr [esp + 0x80], edi
		jmp jmp12
	jmp11:
		mov ebx, dword ptr [esp + 0x74]
		mov ecx, dword ptr [esp + 0x7c]
		mov esi, dword ptr [esp + 0x78]
		mov edi, dword ptr [esp + 0x80]
		add ebx, ebp
		add ecx, ebp
		mov dword ptr [esp + 0x74], ebx
		mov dword ptr [esp + 0x7c], ecx
		add esi, ebp
		add edi, ebp
		mov dword ptr [esp + 0x78], esi
		mov dword ptr [esp + 0x80], edi
	jmp12:
		mov eax, dword ptr [esp]
		mov ebp, dword ptr [esp + 0x18c]
		sar eax, 0x10
		mov esi, dword ptr [esp]
		mov ebx, dword ptr [ebp]
		mov ecx, dword ptr [ebp + 4]
		imul ecx
		mov edi, dword ptr [ebp + 0x30]
		add ebx, eax
		mov dword ptr [esp + 0x154], edi
	jmp15:
		mov edx, dword ptr [esp + 4]
		mov eax, dword ptr [esp + 0x140]
		add edx, 0xffff
		cmp esi, eax
		mov ecx, dword ptr [esp + 8]
		jge jmp13
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		mov ebp, dword ptr [ebp + 0x28]
		sub ecx, edx
		mov dword ptr [esp + 0x150], ebx
		jl jmp14
		; See the explanation in FUN_1003b930
		call ebp
	jmp14:
		mov esi, dword ptr [esp + 0x6c]
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x14]
		mov ebx, dword ptr [esp + 0x18]
		add esi, eax
		add edi, ebx
		mov dword ptr [esp + 0x6c], esi
		mov dword ptr [esp + 0x70], edi
		mov esi, dword ptr [esp + 0x74]
		mov edi, dword ptr [esp + 0x78]
		mov ebp, dword ptr [esp + 0x7c]
		mov eax, dword ptr [esp + 0x1c]
		mov ebx, dword ptr [esp + 0x20]
		mov ecx, dword ptr [esp + 0x24]
		add esi, eax
		add edi, ebx
		add ebp, ecx
		mov dword ptr [esp + 0x74], esi
		mov edx, dword ptr [esp + 0x80]
		mov ebx, dword ptr [esp + 0x28]
		mov dword ptr [esp + 0x78], edi
		add edx, ebx
		mov dword ptr [esp + 0x7c], ebp
		mov dword ptr [esp + 0x80], edx
		mov ebp, dword ptr [esp + 0x18c]
		mov ebx, dword ptr [esp + 0x150]
		mov esi, dword ptr [esp + 4]
		mov edi, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		mov eax, dword ptr [ebp + 4]
		add esi, ecx
		add edi, edx
		mov dword ptr [esp + 4], esi
		mov dword ptr [esp + 8], edi
		mov esi, dword ptr [esp]
		add ebx, eax
		add esi, 0x10000
		mov dword ptr [esp + 0x150], ebx
		mov dword ptr [esp], esi
		jmp jmp15
	jmp13:
		mov dword ptr [esp + 0x150], ebx
		mov ecx, dword ptr [esp + 0x144]
		mov ebx, dword ptr [esp + 0x14c]
		cmp esi, ecx
		jge ret00
		or ebx, ebx
		je jmp16
		mov ecx, dword ptr [esp + 0x194]
		mov edx, dword ptr [esp + 0x198]
		fld dword ptr [esp + 0x134]
		fmul dword ptr g_floatConst65536
		fld dword ptr [edx]
		fsub dword ptr [ecx]
		fld dword ptr [ecx]
		fmul dword ptr g_floatConst65536
		fxch st(2)
		fmulp st(1), st(0)
		fxch st(1)
		fistp dword ptr [esp + 4]
		mov ecx, dword ptr [esp]
		mov edx, dword ptr [esp + 0x140]
		sub ecx, edx
		fistp dword ptr [esp + 0xc]
		mov ebp, 0x3000
		je jmp17
		mov eax, dword ptr [esp + 0xc]
		mov ebx, dword ptr [esp + 4]
		shl ecx, 0xf
		add eax, eax
		imul ecx
		add ebx, edx
		mov dword ptr [esp + 4], ebx
		mov eax, dword ptr [esp + 0x40]
		mov ebx, dword ptr [esp + 0x98]
		add eax, eax
		imul ecx
		add edx, ebx
		mov dword ptr [esp + 0x6c], edx
		mov eax, dword ptr [esp + 0x44]
		mov ebx, dword ptr [esp + 0x9c]
		add eax, eax
		imul ecx
		add edx, ebx
		mov dword ptr [esp + 0x70], edx
		mov esi, dword ptr [esp + 0x48]
		mov ebx, dword ptr [esp + 0xa0]
		mov edi, dword ptr [esp + 0x4c]
		add ebx, ebp
		lea eax, [esi*2]
		imul ecx
		add edx, ebx
		mov ebx, dword ptr [esp + 0xa4]
		lea eax, [edi*2]
		mov dword ptr [esp + 0x74], edx
		add ebx, ebp
		mov edi, dword ptr [esp + 0x50]
		imul ecx
		add edx, ebx
		mov ebx, dword ptr [esp + 0xa8]
		lea eax, [edi*2]
		mov dword ptr [esp + 0x78], edx
		add ebx, ebp
		mov edi, dword ptr [esp + 0x54]
		imul ecx
		add edx, ebx
		mov ebx, dword ptr [esp + 0xac]
		lea eax, [edi*2]
		mov dword ptr [esp + 0x7c], edx
		add ebx, ebp
		imul ecx
		add edx, ebx
		mov dword ptr [esp + 0x80], edx
		jmp jmp18
	jmp17:
		mov ebx, dword ptr [esp + 0x98]
		mov ecx, dword ptr [esp + 0x9c]
		mov dword ptr [esp + 0x6c], ebx
		mov dword ptr [esp + 0x70], ecx
		mov eax, dword ptr [esp + 0xa0]
		mov ebx, dword ptr [esp + 0xa4]
		mov ecx, dword ptr [esp + 0xa8]
		add eax, ebp
		add ebx, ebp
		add ecx, ebp
		mov dword ptr [esp + 0x74], eax
		mov edx, dword ptr [esp + 0xac]
		mov dword ptr [esp + 0x78], ebx
		add edx, ebp
		mov dword ptr [esp + 0x7c], ecx
		mov dword ptr [esp + 0x80], edx
	jmp18:
		mov ebp, dword ptr [esp + 0x18c]
		mov esi, dword ptr [esp]
		mov ebx, dword ptr [esp + 0x150]
	jmp21:
		mov edx, dword ptr [esp + 4]
		mov eax, dword ptr [esp + 0x144]
		add edx, 0xffff
		cmp esi, eax
		mov ecx, dword ptr [esp + 8]
		jge jmp20 ; this jump to a `jmp` instruction is quite untypical for hand-written assembly I think
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		mov ebp, dword ptr [ebp + 0x28]
		sub ecx, edx
		mov dword ptr [esp + 0x150], ebx
		jl jmp19
		call ebp
	jmp19:
		mov esi, dword ptr [esp + 0x6c]
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x40]
		mov ebx, dword ptr [esp + 0x44]
		add esi, eax
		add edi, ebx
		mov dword ptr [esp + 0x6c], esi
		mov dword ptr [esp + 0x70], edi
		mov esi, dword ptr [esp + 0x74]
		mov edi, dword ptr [esp + 0x78]
		mov ebp, dword ptr [esp + 0x7c]
		mov eax, dword ptr [esp + 0x48]
		mov ebx, dword ptr [esp + 0x4c]
		mov ecx, dword ptr [esp + 0x50]
		add esi, eax
		add edi, ebx
		add ebp, ecx
		mov dword ptr [esp + 0x74], esi
		mov edx, dword ptr [esp + 0x80]
		mov ebx, dword ptr [esp + 0x54]
		mov dword ptr [esp + 0x78], edi
		add edx, ebx
		mov dword ptr [esp + 0x7c], ebp
		mov dword ptr [esp + 0x80], edx
		mov ebp, dword ptr [esp + 0x18c]
		mov ebp, dword ptr [esp + 0x18c]
		mov ebx, dword ptr [esp + 0x150]
		mov esi, dword ptr [esp + 4]
		mov edi, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		mov eax, dword ptr [ebp + 4]
		add esi, ecx
		add edi, edx
		mov dword ptr [esp + 4], esi
		mov dword ptr [esp + 8], edi
		mov esi, dword ptr [esp]
		add ebx, eax
		add esi, 0x10000
		mov dword ptr [esp + 0x150], ebx
		mov dword ptr [esp], esi
		jmp jmp21
	jmp20:
		jmp ret00
	jmp16:
		mov ecx, dword ptr [esp + 0x194]
		mov edx, dword ptr [esp + 0x198]
		mov ebp, dword ptr [esp + 0x18c]
		mov esi, dword ptr [esp]
		mov ebx, dword ptr [esp + 0x150]
		fld dword ptr [ecx]
		fmul dword ptr g_floatConst65536
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		fld dword ptr [edx]
		fsub dword ptr [ecx]
		fxch st(2)
		fistp dword ptr [esp + 8]
		fdivr dword ptr g_floatConst65536
		mov edx, esi
		mov ecx, dword ptr [esp + 0x140]
		sub edx, ecx
		shl edx, 0xf
		fmulp st(1), st(0)
		mov ecx, dword ptr [esp + 8]
		fistp dword ptr [esp + 0x10]
		mov eax, dword ptr [esp + 0x10]
		je jmp22
		add eax, eax
		imul edx
		add ecx, edx
		mov dword ptr [esp + 8], ecx
	jmp22:
		mov edx, dword ptr [esp + 4]
		mov eax, dword ptr [esp + 0x144]
		add edx, 0xffff
		cmp esi, eax
		mov ecx, dword ptr [esp + 8]
		jge ret00
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		mov ebp, dword ptr [ebp + 0x28]
		sub ecx, edx
		mov dword ptr [esp + 0x150], ebx
		jl jmp23
		call ebp
	jmp23:
		mov esi, dword ptr [esp + 0x6c]
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x14]
		mov ebx, dword ptr [esp + 0x18]
		add esi, eax
		add edi, ebx
		mov dword ptr [esp + 0x6c], esi
		mov dword ptr [esp + 0x70], edi
		mov esi, dword ptr [esp + 0x74]
		mov edi, dword ptr [esp + 0x78]
		mov ebp, dword ptr [esp + 0x7c]
		mov eax, dword ptr [esp + 0x1c]
		mov ebx, dword ptr [esp + 0x20]
		mov ecx, dword ptr [esp + 0x24]
		add esi, eax
		add edi, ebx
		add ebp, ecx
		mov dword ptr [esp + 0x74], esi
		mov edx, dword ptr [esp + 0x80]
		mov ebx, dword ptr [esp + 0x28]
		mov dword ptr [esp + 0x78], edi
		add edx, ebx
		mov dword ptr [esp + 0x7c], ebp
		mov dword ptr [esp + 0x80], edx
		mov esi, dword ptr [esp + 0x84]
		mov edi, dword ptr [esp + 0x88]
		mov ebp, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x2c]
		mov ebx, dword ptr [esp + 0x30]
		mov ecx, dword ptr [esp + 0x34]
		add esi, eax
		add edi, ebx
		add ebp, ecx
		mov dword ptr [esp + 0x84], esi
		mov edx, dword ptr [esp + 0x90]
		mov ebx, dword ptr [esp + 0x38]
		mov dword ptr [esp + 0x88], edi
		add edx, ebx
		mov dword ptr [esp + 0x8c], ebp
		mov dword ptr [esp + 0x90], edx
		mov ebp, dword ptr [esp + 0x18c]
		mov ebp, dword ptr [esp + 0x18c]
		mov ebx, dword ptr [esp + 0x150]
		mov esi, dword ptr [esp + 4]
		mov edi, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		mov eax, dword ptr [ebp + 4]
		add esi, ecx
		add edi, edx
		mov dword ptr [esp + 4], esi
		mov dword ptr [esp + 8], edi
		mov esi, dword ptr [esp]
		add ebx, eax
		add esi, 0x10000
		mov dword ptr [esp + 0x150], ebx
		mov dword ptr [esp], esi
		jmp jmp22
	ret00:
		add esp, 0x178
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
	ret01:
		fstp dword ptr [esp + 4]
	ret02:
		fstp dword ptr [esp]
		add esp, 0x178
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
	}
}

#endif

// STUB: GOLDP 0x1003c780
void FUN_1003c780(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x1003c780);
}

// STUB: GOLDP 0x1003cf40
void FUN_1003cf40(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x1003cf40);
}

// STUB: GOLDP 0x1003d700
void FUN_1003d700(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x1003d700);
}

// STUB: GOLDP 0x1003e590
void FUN_1003e590(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x1003e590);
}

// STUB: GOLDP 0x1003ee90
void FUN_1003ee90(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x1003ee90);
}

// STUB: GOLDP 0x1003f790
void FUN_1003f790(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x1003f790);
}

// STUB: GOLDP 0x1003fce0
void FUN_1003fce0(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x1003fce0);
}

// STUB: GOLDP 0x10040670
void FUN_10040670(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x10040670);
}
