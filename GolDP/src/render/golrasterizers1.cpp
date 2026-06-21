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

// STUB: GOLDP 0x1003b930
void FUN_1003b930()
{
	STUB(0x1003b930);
}

// STUB: GOLDP 0x1003ba30
void FUN_1003ba30(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x1003ba30);
}

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
