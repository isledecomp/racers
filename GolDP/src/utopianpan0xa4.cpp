#include "utopianpan0xa4.h"

#include "bronzefalcon0xc8770.h"
#include "duskwindbananarelic0x30.h"
#include "golbmpfile.h"
#include "golerror.h"
#include "golimgfile.h"
#include "golsurfaceformat.h"
#include "goltgafile.h"
#include "purpledune0x7c.h"
#include "rectangle.h"

DECOMP_SIZE_ASSERT(UtopianPan0xa4, 0xa4)

// GLOBAL: GOLDP 0x10063ca0
static GolTgaFile g_unk0x10063ca0;

// GLOBAL: GOLDP 0x10064280
static GolBmpFile g_unk0x10064280;

// FUNCTION: GOLDP 0x10004fd0
UtopianPan0xa4::UtopianPan0xa4()
{
	m_unk0x04 = 0;
	m_unk0x08 = 0;
	m_unk0x50 = 0;
}

// FUNCTION: GOLDP 0x10005040
UtopianPan0xa4::~UtopianPan0xa4()
{
	FUN_100051c0();
	m_unk0x58.VTable0x38();
	WhiteBaffoon0x50::Reset();
}

// FUNCTION: GOLDP 0x100050b0
void UtopianPan0xa4::VTable0x10()
{
	GolSurfaceFormat imageFormat;
	UtopianPanImageName imageName;
	imageName.m_name[0] = m_name[0];
	imageName.m_name[1] = m_name[1];
	imageName.m_chars[8] = 0;

	GolImgFile* imageFile = &g_unk0x10063ca0;
	if (!(m_flags & c_flagBit4)) {
		imageFile = &g_unk0x10064280;
	}

	m_unk0x3c = (m_unk0x3c & ~(c_flagBit1 | c_flagBit2)) | c_flagBit3;
	if (!(m_unk0x3c & (c_flagBit4 | c_flagBit5))) {
		m_unk0x3c |= c_flagBit4;
	}

	imageFile->VTable0x08(imageName.m_chars);
	imageFormat = imageFile->GetTextureFormat();
	m_width = imageFile->GetWidth();
	m_height = imageFile->GetHeight();

	m_unk0x58.VTable0x34(*m_renderer, imageFormat, m_width, m_height);
	imageFile->SetUnk0x5a8(TRUE);
	imageFile->SetUnk0x5ac(FALSE);
	imageFile->VTable0x20(&m_unk0x58, m_flags & c_flagBit2, NULL);
	imageFile->SetUnk0x5a8(FALSE);
	imageFile->Destroy();

	GolSurfaceFormat textureFormat = m_unk0x58.GetTextureFormat();
	m_renderer->SelectTextureFormat(textureFormat, &m_unk0x0c, m_flags & c_flagBit5);
	FUN_1001f430();
	FUN_10005b00();
}

// FUNCTION: GOLDP 0x100051c0
void UtopianPan0xa4::FUN_100051c0()
{
	if (m_unk0x54 != NULL) {
		delete[] m_unk0x54;
		m_unk0x54 = NULL;
	}
	if (m_unk0x50 != NULL) {
		delete[] m_unk0x50;
		m_unk0x50 = NULL;
	}
	if (m_unk0x08 != NULL) {
		delete[] m_unk0x08;
		m_unk0x08 = NULL;
	}
	if (m_unk0x04 != NULL) {
		delete[] m_unk0x04;
		m_unk0x04 = NULL;
	}
}

// FUNCTION: GOLDP 0x10005210
void UtopianPan0xa4::FUN_10005210()
{
	GolSurfaceFormat textureFormat = m_unk0x58.GetTextureFormat();

	m_renderer->SelectTextureFormat(textureFormat, &m_unk0x0c, m_flags & c_flagBit5);
	FUN_1001f430();
	FUN_10005b00();
}

// FUNCTION: GOLDP 0x10005260
void UtopianPan0xa4::Reset()
{
	FUN_100051c0();
	m_unk0x58.VTable0x38();
	WhiteBaffoon0x50::Reset();
}

// FUNCTION: GOLDP 0x10005280
void UtopianPan0xa4::VTable0x00()
{
	m_unk0x04 = new LegoS32[m_unk0x2c];
	if (m_unk0x04 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
}

// FUNCTION: GOLDP 0x100052b0
void UtopianPan0xa4::VTable0x04()
{
	m_unk0x08 = new LegoS32[m_unk0x30];
	if (m_unk0x08 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
}

// FUNCTION: GOLDP 0x100052e0
void UtopianPan0xa4::VTable0x08()
{
	LegoU32 count = m_unk0x30 * m_unk0x2c;

	m_unk0x50 = new PurpleDune0x7c[count];
	if (m_unk0x50 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x54 = new DuskwindBananaRelic0x30[count];
	if (m_unk0x54 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
}

// FUNCTION: GOLDP 0x100053d0
void UtopianPan0xa4::VTable0x0c(LegoU32 p_row, LegoU32 p_column, GolSurfaceFormat* p_textureFormat)
{
	LegoU32 index = p_row * m_unk0x30 + p_column;

	m_unk0x50[index].FUN_10015d00(
		static_cast<BronzeFalcon0xc8770&>(*m_renderer),
		*p_textureFormat,
		m_unk0x04[p_row],
		m_unk0x08[p_column]
	);
	FUN_10005440(m_renderer, &m_unk0x54[index], &m_unk0x50[index]);
}

// FUNCTION: GOLDP 0x10005440
void UtopianPan0xa4::FUN_10005440(
	WhiteFalcon0x140* p_renderer,
	DuskwindBananaRelic0x30* p_material,
	GoldDune0x38* p_texture
)
{
	LegoU32 flags = (m_unk0x3c & c_flagBit1) ? 0x92a8a : 0x92a8c;
	if (m_unk0x3c & c_flagBit4) {
		flags |= c_flagBit4;
	}
	else {
		flags |= c_flagBit5;
	}

	DuskWindBananaRelicParams params;
	params.m_unk0x04 = p_texture;
	params.m_unk0x08.m_unk0x0 = 0xff;
	params.m_unk0x08.m_unk0x1 = 0xff;
	params.m_unk0x08.m_unk0x2 = 0xff;
	params.m_unk0x08.m_unk0x3 = 0xff;
	params.m_unk0x0c.m_unk0x0 = 0xff;
	params.m_unk0x0c.m_unk0x1 = 0xff;
	params.m_unk0x0c.m_unk0x2 = 0xff;
	params.m_unk0x0c.m_unk0x3 = 0xff;
	params.m_unk0x11 = 0;
	params.m_unk0x13 = 0;
	params.m_unk0x00 = flags;
	params.m_unk0x10 = 2;
	params.m_unk0x12 = 1;

	p_material->FUN_100257e0(p_renderer, params);
	p_material->FUN_10006320(*p_renderer);
}

// FUNCTION: GOLDP 0x100054d0
void UtopianPan0xa4::FUN_100054d0(
	BronzeFalcon0xc8770* p_renderer,
	undefined4 p_unk0x08,
	Rect* p_destRect,
	undefined4 p_unk0x14
)
{
	Rect sourceRect;
	sourceRect.m_left = 0;
	sourceRect.m_top = 0;
	sourceRect.m_right = m_width;
	sourceRect.m_bottom = m_height;

	FUN_10005510(p_renderer, p_unk0x08, p_destRect, &sourceRect, p_unk0x14);
}

// STUB: GOLDP 0x10005510
undefined4 UtopianPan0xa4::FUN_10005510(BronzeFalcon0xc8770*, undefined4, Rect*, Rect*, undefined4)
{
	// TODO
	STUB(0x10005510);
	return 0;
}

// FUNCTION: GOLDP 0x10005ae0
PurpleDune0x7c* UtopianPan0xa4::VTable0x1c(LegoU32 p_row, LegoU32 p_column)
{
	return &m_unk0x50[p_row * m_unk0x30 + p_column];
}

// STUB: GOLDP 0x10005b00
void UtopianPan0xa4::FUN_10005b00()
{
	// TODO
	STUB(0x10005b00);
}
