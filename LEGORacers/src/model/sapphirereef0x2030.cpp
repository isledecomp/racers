#include "model/sapphirereef0x2030.h"

#include "core/gol.h"
#include "golerror.h"
#include "mesh/golmodelbase.h"
#include "model/verdanttide0x38.h"
#include "render/gold3drenderdevice.h"

#include <string.h>

DECOMP_SIZE_ASSERT(SapphireReef0x2030, 0x2030)
DECOMP_SIZE_ASSERT(SapphireReef0x2030::Placement0x30, 0x30)
DECOMP_SIZE_ASSERT(SapphireReef0x2030::Field0xa4, 0x14)
DECOMP_SIZE_ASSERT(SapphireReef0x2030::Field0xa4::Entry0x1c, 0x1c)
DECOMP_SIZE_ASSERT(SapphireReef0x2030::Field0xbc, 0x14)
DECOMP_SIZE_ASSERT(SapphireReef0x2030::Field0xbc::Entry0x0c, 0x0c)
DECOMP_SIZE_ASSERT(SapphireReef0x2030::Field0x1e30Entry0x28, 0x28)

// FUNCTION: LEGORACERS 0x00499530
void SapphireReef0x2030::Placement0x30::Reset()
{
	m_unk0x00 = 0;
	m_unk0x0c = 0;
	m_unk0x28 = 0;
	m_unk0x2c = 0;
}

// FUNCTION: LEGORACERS 0x00499540
SapphireReef0x2030::Placement0x30::Placement0x30()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00499550
SapphireReef0x2030::Placement0x30::~Placement0x30()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00499560
void SapphireReef0x2030::Placement0x30::Destroy()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void SapphireReef0x2030::Placement0x30::FUN_004513d0(SapphireReef0x2030*)
{
}

// STUB: LEGORACERS 0x00499890
void SapphireReef0x2030::Placement0x30::FUN_00499890(LegoPieceLibrary::PieceRecord*, LegoS32, LegoS32)
{
	STUB(0x00499890);
}

// STUB: LEGORACERS 0x00499a60
void SapphireReef0x2030::Placement0x30::FUN_00499a60()
{
	STUB(0x00499a60);
}

// FUNCTION: LEGORACERS 0x00499b00
void SapphireReef0x2030::Placement0x30::FUN_00499b00()
{
	if (m_unk0x28 & 1) {
		if (m_unk0x24 > 6 || m_unk0x20 > 10) {
			m_unk0x28++;
		}
	}
	else if (m_unk0x20 > 6 || m_unk0x24 > 10) {
		m_unk0x28++;
	}

	m_unk0x28 = (m_unk0x28 + 1) & 3;
	FUN_00499a60();
}

// FUNCTION: LEGORACERS 0x00499ca0
void SapphireReef0x2030::Placement0x30::FUN_00499ca0(LegoS32* p_x, LegoS32* p_y, LegoS32* p_rotation)
{
	*p_x = m_unk0x18;
	*p_y = m_unk0x1c;
	*p_rotation = m_unk0x28;
}

// FUNCTION: LEGORACERS 0x00415f40 FOLDED
void SapphireReef0x2030::Field0xbc::Clear()
{
	if (m_entries != NULL) {
		delete[] m_entries;
		m_entries = NULL;
	}
}

// FUNCTION: LEGORACERS 0x00499d00
void SapphireReef0x2030::Reset()
{
	m_pieceLibrary = NULL;
	m_golExport = NULL;
	m_renderer = NULL;
	m_model = NULL;
	m_unk0x1efc = 0;
	m_unk0x1f00 = 0;
	m_unk0xd0 = 0;
	m_unk0xd4 = 0;
	m_unk0xde = 0;
	m_auxModel = NULL;
	m_unk0x2028 = 0;
	m_unk0x202c = 0;
	m_verdantTide = NULL;
	FUN_0049b740(NULL);
	m_hasHighBasePiece = FALSE;
	m_unk0xda = TRUE;
	m_highBasePiece = NULL;
}

// STUB: LEGORACERS 0x00499d70
SapphireReef0x2030::SapphireReef0x2030()
{
	STUB(0x00499d70);

	m_unk0xa4.m_unk0x10 = &m_unk0xbc;
	m_unk0xbc.m_unk0x0c = &m_unk0xa4;
	m_unk0x1e30 = NULL;
	m_unk0x1e34 = NULL;
	m_unk0x1e38 = NULL;
	::memset(m_unk0xe4, 0, sizeof(m_unk0xe4));
	Reset();
}

// FUNCTION: LEGORACERS 0x00499e20
SapphireReef0x2030::~SapphireReef0x2030()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00499eb0
void SapphireReef0x2030::FUN_00499eb0(GolModelBase* p_model)
{
	p_model->VTable0x18(m_renderer, 2, 7500, 2500, 1610, 0);
}

// FUNCTION: LEGORACERS 0x00499ee0
void SapphireReef0x2030::FUN_00499ee0()
{
	FUN_00499eb0(m_model);
	FUN_00499f20();
}

// FUNCTION: LEGORACERS 0x00499f00
void SapphireReef0x2030::FUN_00499f00()
{
	m_model->VTable0x24();
	FUN_00499f80();
}

// FUNCTION: LEGORACERS 0x00499f20
void SapphireReef0x2030::FUN_00499f20()
{
	m_unk0x1e30 = new Field0x1e30Entry0x28[7500];
	m_unk0x1e34 = new LegoU8[40000];
	m_unk0x1e38 = new LegoU8[10000];

	for (LegoS32 i = 0; i < 7500; i++) {
		m_unk0x1e30[i].m_index = static_cast<LegoU16>(i);
	}
}

// FUNCTION: LEGORACERS 0x00499f80
void SapphireReef0x2030::FUN_00499f80()
{
	delete[] m_unk0x1e30;
	delete[] m_unk0x1e34;
	delete[] m_unk0x1e38;
	m_unk0x1e30 = NULL;
	m_unk0x1e34 = NULL;
	m_unk0x1e38 = NULL;
}

// STUB: LEGORACERS 0x00499fc0
void SapphireReef0x2030::FUN_00499fc0(
	GolExport* p_golExport,
	GolD3DRenderDevice* p_renderer,
	LegoPieceLibrary* p_pieceLibrary,
	VerdantTide0x38* p_verdantTide
)
{
	STUB(0x00499fc0);

	if (FUN_0049a0e0()) {
		Destroy();
	}

	m_verdantTide = p_verdantTide;
	m_materialTable = p_verdantTide != NULL ? p_verdantTide->GetMaterialTable() : NULL;
	m_pieceLibrary = p_pieceLibrary;
	m_golExport = p_golExport;
	m_renderer = p_renderer;

	m_model = m_golExport->VTable0x14();
	if (m_model == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	FUN_00499ee0();

	m_auxModel = m_golExport->VTable0x14();
	if (m_auxModel == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	m_auxModel->VTable0x18(m_renderer, 1, 384, 192, 112, 2);

	if (m_verdantTide != NULL) {
		GolModelMaterialTable* materialTable = m_auxModel->GetMaterialTable();
		materialTable->SetPosition(0, m_verdantTide->GetMaterial(0));
		materialTable->SetPosition(1, m_verdantTide->GetMaterial(1));
	}

	FUN_0049b720();
	m_unk0xbc.Initialize(10, 6);
	m_unk0xa4.Initialize(64);
}

// FUNCTION: LEGORACERS 0x0049a0e0
LegoBool32 SapphireReef0x2030::FUN_0049a0e0()
{
	return m_golExport != NULL;
}

// FUNCTION: LEGORACERS 0x0049a0f0
void SapphireReef0x2030::Destroy()
{
	m_unk0xbc.Clear();
	m_unk0xa4.Clear();

	if (m_golExport != NULL) {
		if (m_model != NULL) {
			m_golExport->VTable0x48(m_model);
		}
		if (m_auxModel != NULL) {
			m_golExport->VTable0x48(m_auxModel);
		}
	}

	FUN_00499f80();
	Reset();
}

// STUB: LEGORACERS 0x0049a160
void SapphireReef0x2030::FUN_0049a160(
	LegoPieceLibrary::PieceRecord*,
	undefined4,
	undefined4,
	undefined4,
	undefined4,
	undefined4
)
{
	STUB(0x0049a160);
}

// FUNCTION: LEGORACERS 0x0049ad00
void SapphireReef0x2030::FUN_0049ad00()
{
	if (m_pieceLibrary != NULL) {
		m_highBasePiece = m_pieceLibrary->FindPieceRecord(0x800, 1);
		if (m_highBasePiece != NULL) {
			m_hasHighBasePiece = TRUE;
		}
	}
}

// STUB: LEGORACERS 0x0049b170
void SapphireReef0x2030::FUN_0049b170(
	GolModelEntity*,
	LegoPieceLibrary::PieceRecord*,
	undefined4,
	undefined4,
	undefined4,
	undefined4,
	undefined4,
	undefined4
)
{
	STUB(0x0049b170);
}

// FUNCTION: LEGORACERS 0x0049b720
void SapphireReef0x2030::FUN_0049b720()
{
	m_unk0x1f04 = -5.0f;
	m_unk0x1f08 = -3.0f;
	m_unk0x1f0c = 0.0f;
}

// STUB: LEGORACERS 0x0049b740
void SapphireReef0x2030::FUN_0049b740(undefined4 p_unk0x04)
{
	STUB(0x0049b740);

	if (p_unk0x04 != NULL) {
		m_unk0x1f10 = m_unk0x1f04;
		m_unk0x1f14 = m_unk0x1f08;
		m_unk0x1f18 = m_unk0x1f0c;
		return;
	}

	if (!m_unk0xd4) {
		FUN_0049b720();
	}

	m_unk0x1f10 = m_unk0x1f04;
	m_unk0x1f14 = m_unk0x1f08;
	m_unk0x1f18 = m_unk0x1f0c;
}

// STUB: LEGORACERS 0x0049b8b0
void SapphireReef0x2030::FUN_0049b8b0(LegoPieceLibrary::PieceRecord*, undefined4)
{
	STUB(0x0049b8b0);
}

// STUB: LEGORACERS 0x0049b920
void SapphireReef0x2030::FUN_0049b920(undefined4, undefined4)
{
	STUB(0x0049b920);
}

// FUNCTION: LEGORACERS 0x0049bd50
LegoS32 SapphireReef0x2030::FUN_0049bd50(LegoS32 p_index) const
{
	return m_unk0xa4.m_entries[p_index].m_unk0x08;
}

// STUB: LEGORACERS 0x0049c230
void SapphireReef0x2030::FUN_0049c230(Placement0x30*, GolModelEntity*)
{
	STUB(0x0049c230);
}

// STUB: LEGORACERS 0x0049c7f0
void SapphireReef0x2030::FUN_0049c7f0(LegoU8*)
{
	STUB(0x0049c7f0);
}

// FUNCTION: LEGORACERS 0x0049c820
void SapphireReef0x2030::FUN_0049c820(LegoU8* p_dest)
{
	m_unk0xa4.FUN_0049fca0(p_dest);
}

// FUNCTION: LEGORACERS 0x0049df20
void SapphireReef0x2030::Field0xbc::Entry0x0c::Reset()
{
	m_unk0x00 = -1;
	m_unk0x04 = 0;
	m_unk0x08 = 0;
	m_unk0x09 = 0;
}

// FUNCTION: LEGORACERS 0x0049e210
SapphireReef0x2030::Field0xbc::Field0xbc()
{
	m_unk0x10 = 0;
	m_unk0x0c = NULL;
	m_entries = NULL;
}

// FUNCTION: LEGORACERS 0x0049e220
SapphireReef0x2030::Field0xbc::~Field0xbc()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x0049e230
LegoBool32 SapphireReef0x2030::Field0xbc::Initialize(LegoS32 p_width, LegoS32 p_height)
{
	Clear();
	m_width = p_width;
	m_height = p_height;
	m_entries = new Entry0x0c[p_width * p_height];
	if (m_entries) {
		ResetEntries();
		return TRUE;
	}
	return FALSE;
}

// FUNCTION: LEGORACERS 0x0049e280
void SapphireReef0x2030::Field0xbc::ResetEntries()
{
	if (m_entries != NULL) {
		for (LegoS32 x = 0; x < m_width; x++) {
			for (LegoS32 y = 0; y < m_height; y++) {
				m_entries[y + (x * m_height)].Reset();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x0049f880
SapphireReef0x2030::Field0xa4::Field0xa4()
{
	m_unk0x10 = NULL;
	m_entries = NULL;
	m_unk0x08 = 0;
	m_count = 0;
	m_unk0x00 = 0;
}

// FUNCTION: LEGORACERS 0x0049f8a0
SapphireReef0x2030::Field0xa4::~Field0xa4()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x0049f8b0
void SapphireReef0x2030::Field0xa4::Clear()
{
	if (m_entries != NULL) {
		delete[] m_entries;
		m_entries = NULL;
	}
	m_unk0x08 = 0;
	m_count = 0;
	m_unk0x00 = 0;
}

// FUNCTION: LEGORACERS 0x0049f8e0
LegoBool32 SapphireReef0x2030::Field0xa4::Initialize(LegoS32 p_count)
{
	Clear();
	m_entries = new Entry0x1c[p_count];
	if (m_entries != NULL) {
		m_count = p_count;
		return TRUE;
	}

	m_count = 0;
	return FALSE;
}

// STUB: LEGORACERS 0x0049fca0
void SapphireReef0x2030::Field0xa4::FUN_0049fca0(LegoU8*)
{
	STUB(0x0049fca0);
}

// STUB: LEGORACERS 0x0049fd60
void SapphireReef0x2030::Field0xa4::FUN_0049fd60()
{
	STUB(0x0049fd60);
}
