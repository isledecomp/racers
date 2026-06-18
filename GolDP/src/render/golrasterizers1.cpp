#include "render/golrasterizers1.h"

#include "decomp.h"
#include "render/golsoftwarerenderer.h"

// STUB: GOLDP 0x10032c80
void FUN_10032c80(GolSoftwareRenderer* p_renderer)
{
	STUB(0x10032c80);
	// p_renderer->m_unk0x2c &= 0x7fffffff;
	// p_renderer->m_currentTriangleRasterizer = NoopTriangleRasterizer;
	// p_renderer->m_triangleRasterizer = NoopTriangleRasterizer;

	// if (p_renderer->m_pixelFormat != e_formatIndex8) {
	// 	p_renderer->m_spanRasterizer = NoopSpanRasterizer;
	// }
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

// STUB: GOLDP 0x10034db0
void FUN_10034db0()
{
	STUB(0x10034db0);
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

// STUB: GOLDP 0x10036330
void FUN_10036330()
{
	STUB(0x10036330);
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

// STUB: GOLDP 0x100378b0
void FUN_100378b0()
{
	STUB(0x100378b0);
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

// STUB: GOLDP 0x10038e30
void FUN_10038e30()
{
	STUB(0x10038e30);
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

// STUB: GOLDP 0x1003a3b0
void FUN_1003a3b0()
{
	STUB(0x1003a3b0);
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

// STUB: GOLDP 0x1003b930
void FUN_1003b930()
{
	STUB(0x1003b930);
}
