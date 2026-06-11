#include "model/carbuildmodel.h"

#include "core/gol.h"
#include "golanimatedentity.h"
#include "golerror.h"
#include "mesh/golmodelbase.h"
#include "model/legocolortable.h"
#include "render/gold3drenderdevice.h"

#include <string.h>

DECOMP_SIZE_ASSERT(CarBuildModel, 0x2030)
DECOMP_SIZE_ASSERT(CarBuildModel::Placement, 0x30)
DECOMP_SIZE_ASSERT(CarBuildModel::Field0xa4, 0x14)
DECOMP_SIZE_ASSERT(CarBuildModel::Field0xa4::Entry0x1c, 0x1c)
DECOMP_SIZE_ASSERT(CarBuildModel::Field0xbc, 0x14)
DECOMP_SIZE_ASSERT(CarBuildModel::Field0xbc::Entry0x0c, 0x0c)
DECOMP_SIZE_ASSERT(CarBuildModel::Field0x1e30Entry0x28, 0x28)

// FUNCTION: LEGORACERS 0x00499530
void CarBuildModel::Placement::Reset()
{
	m_unk0x00 = 0;
	m_pieceRecord = NULL;
	m_rotation = 0;
	m_anchor = 0;
}

// FUNCTION: LEGORACERS 0x00499540
CarBuildModel::Placement::Placement()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00499550
CarBuildModel::Placement::~Placement()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00499560
void CarBuildModel::Placement::Destroy()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void CarBuildModel::Placement::FUN_004513d0(CarBuildModel*)
{
}

// FUNCTION: LEGORACERS 0x00499570
void CarBuildModel::Placement::FUN_00499570()
{
	if (m_rotation & 1) {
		switch (m_anchor) {
		case 0:
			m_gridX = m_x;
			m_gridY = m_y;
			return;
		case 1:
			m_gridX = m_x;
			m_gridY = m_y - m_width;
			return;
		case 2:
			m_gridX = m_x - m_height;
			m_gridY = m_y;
			return;
		case 3:
			m_gridX = m_x - m_height;
			m_gridY = m_y - m_width;
			return;
		}
	}
	else {
		switch (m_anchor) {
		case 0:
			m_gridX = m_x;
			m_gridY = m_y;
			return;
		case 1:
			m_gridX = m_x;
			m_gridY = m_y - m_height;
			return;
		case 2:
			m_gridX = m_x - m_width;
			m_gridY = m_y;
			return;
		case 3:
			m_gridX = m_x - m_width;
			m_gridY = m_y - m_height;
			return;
		}
	}
}

// FUNCTION: LEGORACERS 0x00499640
void CarBuildModel::Placement::FUN_00499640()
{
	if (m_rotation & 1) {
		switch (m_anchor) {
		case 0:
			m_x = m_gridX;
			m_y = m_gridY;
			return;
		case 1:
			m_x = m_gridX;
			m_y = m_gridY + m_width;
			return;
		case 2:
			m_x = m_gridX + m_height;
			m_y = m_gridY;
			return;
		case 3:
			m_x = m_gridX + m_height;
			m_y = m_gridY + m_width;
			return;
		}
	}
	else {
		switch (m_anchor) {
		case 0:
			m_x = m_gridX;
			m_y = m_gridY;
			return;
		case 1:
			m_x = m_gridX;
			m_y = m_gridY + m_height;
			return;
		case 2:
			m_x = m_gridX + m_width;
			m_y = m_gridY;
			return;
		case 3:
			m_x = m_gridX + m_width;
			m_y = m_gridY + m_height;
			return;
		}
	}
}

// FUNCTION: LEGORACERS 0x00499710
void CarBuildModel::Placement::SetAnchor(LegoS32 p_anchor)
{
	LegoS32 isRotated = m_rotation & 1;

	if (isRotated) {
		switch (m_anchor) {
		case 1:
			m_y -= m_width;
			break;
		case 2:
			m_x -= m_height;
			break;
		case 3:
			m_x -= m_height;
			m_y -= m_width;
			break;
		}
	}
	else {
		switch (m_anchor) {
		case 1:
			m_y -= m_height;
			break;
		case 2:
			m_x -= m_width;
			break;
		case 3:
			m_x -= m_width;
			m_y -= m_height;
			break;
		}
	}

	m_anchor = p_anchor;

	if (isRotated) {
		switch (p_anchor) {
		case 3:
			m_x += m_height;
			// fall through
		case 1:
			m_y = m_y + m_width;
			return;
		case 2:
			m_x += m_height;
			return;
		}
	}
	else {
		switch (p_anchor) {
		case 3:
			m_x += m_width;
			// fall through
		case 1:
			m_y = m_y + m_height;
			return;
		case 2:
			m_x += m_width;
			return;
		}
	}
}

// FUNCTION: LEGORACERS 0x004997e0
void CarBuildModel::Placement::FUN_004997e0()
{
	switch (m_anchor) {
	case 0:
		if (m_x >= 5) {
			if (m_y >= 3) {
				SetAnchor(3);
			}
			else {
				SetAnchor(2);
			}
		}
		else if (m_y >= 3) {
			SetAnchor(1);
		}
		break;
	case 1:
		if (m_x >= 5) {
			if (m_y >= 3) {
				SetAnchor(3);
			}
			else {
				SetAnchor(2);
			}
		}
		else if (m_y < 3) {
			SetAnchor(0);
		}
		break;
	case 2:
		if (m_x < 5) {
			if (m_y >= 3) {
				SetAnchor(1);
			}
			else {
				SetAnchor(0);
			}
		}
		else if (m_y >= 3) {
			SetAnchor(3);
		}
		break;
	case 3:
		if (m_x < 5) {
			if (m_y >= 3) {
				SetAnchor(1);
			}
			else {
				SetAnchor(0);
			}
		}
		else if (m_y < 3) {
			SetAnchor(2);
		}
		break;
	}
}

// FUNCTION: LEGORACERS 0x00499890
void CarBuildModel::Placement::SetPiece(
	LegoPieceLibrary::PieceRecord* p_pieceRecord,
	LegoS32 p_unk0x08,
	LegoS32 p_unk0x0c
)
{
	m_width = p_pieceRecord->GetWidth();
	m_height = p_pieceRecord->GetHeight();
	m_colorRecordIndex = p_unk0x08;
	m_unk0x14 = p_unk0x0c;

	if (m_pieceRecord == NULL) {
		m_anchor = 0;
		m_rotation = 0;
		m_gridX = (10 - m_width) >> 1;
		m_gridY = (6 - m_height) >> 1;
		if (m_gridX < 0 || m_gridY < 0) {
			m_rotation = 1;
			m_gridX = (10 - m_height) >> 1;
			m_gridY = (6 - m_width) >> 1;
		}
	}
	else {
		if (m_rotation & 1) {
			if (m_width > 6 || m_height > 10) {
				m_rotation++;
			}
		}
		else if (m_width > 10 || m_height > 6) {
			m_rotation++;
		}

		m_rotation &= 3;

		if (m_rotation & 1) {
			switch (m_anchor) {
			case 0:
				m_gridX = m_x;
				m_gridY = m_y;
				break;
			case 1:
				m_gridX = m_x;
				m_gridY = m_y - m_width;
				break;
			case 2:
				m_gridX = m_x - m_height;
				m_gridY = m_y;
				break;
			case 3:
				m_gridX = m_x - m_height;
				m_gridY = m_y - m_width;
				break;
			}

			if (m_gridX + m_height > 10) {
				m_gridX = 10 - m_height;
			}
			if (m_gridY + m_width > 6) {
				m_gridY = 6 - m_width;
			}
		}
		else {
			switch (m_anchor) {
			case 0:
				m_gridX = m_x;
				m_gridY = m_y;
				break;
			case 1:
				m_gridX = m_x;
				m_gridY = m_y - m_height;
				break;
			case 2:
				m_gridX = m_x - m_width;
				m_gridY = m_y;
				break;
			case 3:
				m_gridX = m_x - m_width;
				m_gridY = m_y - m_height;
				break;
			}

			if (m_gridX + m_width > 10) {
				m_gridX = 10 - m_width;
			}
			if (m_gridY + m_height > 6) {
				m_gridY = 6 - m_height;
			}
		}
	}

	if (m_gridX < 0) {
		m_gridX = 0;
	}
	if (m_gridY < 0) {
		m_gridY = 0;
	}

	m_pieceRecord = p_pieceRecord;
	FUN_00499640();
	FUN_004997e0();
}

// FUNCTION: LEGORACERS 0x00499a60
void CarBuildModel::Placement::FUN_00499a60()
{
	FUN_00499570();

	if (m_gridX < 0) {
		m_gridX = 0;
	}
	if (m_gridY < 0) {
		m_gridY = 0;
	}

	if (m_rotation & 1) {
		if (m_gridX + m_height > 10) {
			m_gridX = 10 - m_height;
		}
		if (m_gridY + m_width > 6) {
			m_gridY = 6 - m_width;
		}
	}
	else {
		if (m_gridX + m_width > 10) {
			m_gridX = 10 - m_width;
		}
		if (m_gridY + m_height > 6) {
			m_gridY = 6 - m_height;
		}
	}

	FUN_00499640();
}

// FUNCTION: LEGORACERS 0x00499b00
void CarBuildModel::Placement::Rotate()
{
	if (m_rotation & 1) {
		if (m_height > 6 || m_width > 10) {
			m_rotation++;
		}
	}
	else if (m_width > 6 || m_height > 10) {
		m_rotation++;
	}

	m_rotation = (m_rotation + 1) & 3;
	FUN_00499a60();
}

// FUNCTION: LEGORACERS 0x00499b40
void CarBuildModel::Placement::FUN_00499b40()
{
	if (m_rotation & 1) {
		if (m_gridX + m_height < 10) {
			m_gridX++;
			FUN_00499640();
			FUN_004997e0();
			return;
		}
	}
	else if (m_gridX + m_width < 10) {
		m_gridX++;
		FUN_00499640();
		FUN_004997e0();
	}
}

// FUNCTION: LEGORACERS 0x00499b90
void CarBuildModel::Placement::FUN_00499b90()
{
	if (m_gridX > 0) {
		m_gridX--;
		FUN_00499640();
		FUN_004997e0();
	}
}

// FUNCTION: LEGORACERS 0x00499bb0
void CarBuildModel::Placement::FUN_00499bb0()
{
	if (m_rotation & 1) {
		if (m_gridY + m_width < 6) {
			m_gridY++;
			FUN_00499640();
			FUN_004997e0();
			return;
		}
	}
	else if (m_gridY + m_height < 6) {
		m_gridY++;
		FUN_00499640();
		FUN_004997e0();
	}
}

// FUNCTION: LEGORACERS 0x00499c00
void CarBuildModel::Placement::FUN_00499c00()
{
	if (m_gridY > 0) {
		m_gridY--;
		FUN_00499640();
		FUN_004997e0();
	}
}

// FUNCTION: LEGORACERS 0x00499c20
void CarBuildModel::Placement::FUN_00499c20(LegoS32 p_delta)
{
	if (p_delta > 0) {
		for (LegoS32 i = p_delta; i != 0; i--) {
			FUN_00499b40();
		}
	}
	else if (p_delta < 0) {
		LegoS32 i = -p_delta;
		do {
			FUN_00499b90();
		} while (--i != 0);
	}
}

// FUNCTION: LEGORACERS 0x00499c60
void CarBuildModel::Placement::FUN_00499c60(LegoS32 p_delta)
{
	if (p_delta > 0) {
		for (LegoS32 i = p_delta; i != 0; i--) {
			FUN_00499bb0();
		}
	}
	else if (p_delta < 0) {
		LegoS32 i = -p_delta;
		do {
			FUN_00499c00();
		} while (--i != 0);
	}
}

// FUNCTION: LEGORACERS 0x00499ca0
void CarBuildModel::Placement::GetPlacement(LegoS32* p_x, LegoS32* p_y, LegoS32* p_rotation)
{
	*p_x = m_gridX;
	*p_y = m_gridY;
	*p_rotation = m_rotation;
}

// FUNCTION: LEGORACERS 0x00499cc0
void CarBuildModel::Placement::SetPlacement(LegoS32 p_x, LegoS32 p_y, LegoS32 p_rotation, LegoS32 p_anchor)
{
	m_x = p_x;
	m_y = p_y;
	m_rotation = p_rotation & 3;
	m_anchor = p_anchor & 3;
	SetPiece(m_pieceRecord, m_colorRecordIndex, m_unk0x14);
}

// FUNCTION: LEGORACERS 0x00415f40 FOLDED
void CarBuildModel::Field0xbc::Clear()
{
	if (m_entries != NULL) {
		delete[] m_entries;
		m_entries = NULL;
	}
}

// FUNCTION: LEGORACERS 0x00499d00
void CarBuildModel::Reset()
{
	m_pieceLibrary = NULL;
	m_golExport = NULL;
	m_renderer = NULL;
	m_model = NULL;
	m_unk0x1efc = 0;
	m_unk0x1f00 = 0;
	m_unk0xd0 = 0;
	m_placedPieceCount = 0;
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
CarBuildModel::CarBuildModel()
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
CarBuildModel::~CarBuildModel()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00499eb0
void CarBuildModel::FUN_00499eb0(GolModelBase* p_model)
{
	p_model->VTable0x18(m_renderer, 2, 7500, 2500, 1610, 0);
}

// FUNCTION: LEGORACERS 0x00499ee0
void CarBuildModel::FUN_00499ee0()
{
	FUN_00499eb0(m_model);
	AllocateBuffers();
}

// FUNCTION: LEGORACERS 0x00499f00
void CarBuildModel::FUN_00499f00()
{
	m_model->VTable0x24();
	FreeBuffers();
}

// FUNCTION: LEGORACERS 0x00499f20
void CarBuildModel::AllocateBuffers()
{
	m_unk0x1e30 = new Field0x1e30Entry0x28[7500];
	m_unk0x1e34 = new LegoU8[40000];
	m_unk0x1e38 = new LegoU8[10000];

	for (LegoS32 i = 0; i < 7500; i++) {
		m_unk0x1e30[i].m_index = static_cast<LegoU16>(i);
	}
}

// FUNCTION: LEGORACERS 0x00499f80
void CarBuildModel::FreeBuffers()
{
	delete[] m_unk0x1e30;
	delete[] m_unk0x1e34;
	delete[] m_unk0x1e38;
	m_unk0x1e30 = NULL;
	m_unk0x1e34 = NULL;
	m_unk0x1e38 = NULL;
}

// STUB: LEGORACERS 0x00499fc0
void CarBuildModel::Initialize(
	GolExport* p_golExport,
	GolD3DRenderDevice* p_renderer,
	LegoPieceLibrary* p_pieceLibrary,
	LegoColorTable* p_verdantTide
)
{
	STUB(0x00499fc0);

	if (IsInitialized()) {
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
LegoBool32 CarBuildModel::IsInitialized()
{
	return m_golExport != NULL;
}

// FUNCTION: LEGORACERS 0x0049a0f0
void CarBuildModel::Destroy()
{
	m_unk0xbc.Clear();
	m_unk0xa4.Clear();
	GetUnk0x0c()->VTable0x54();
	GetUnk0x1f34()->VTable0x54();

	if (m_golExport != NULL) {
		if (m_model != NULL) {
			m_golExport->VTable0x48(m_model);
		}
		if (m_auxModel != NULL) {
			m_golExport->VTable0x48(m_auxModel);
		}
	}

	FreeBuffers();
	Reset();
}

// STUB: LEGORACERS 0x0049a160
void CarBuildModel::FUN_0049a160(
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

// STUB: LEGORACERS 0x0049a1e0
LegoS32 CarBuildModel::FUN_0049a1e0(LegoPieceLibrary::PieceRecord*, LegoS32, LegoS32, LegoS32)
{
	STUB(0x0049a1e0);
	return 0;
}

// FUNCTION: LEGORACERS 0x0049ad00
void CarBuildModel::FindHighBasePiece()
{
	if (m_pieceLibrary != NULL) {
		m_highBasePiece = m_pieceLibrary->FindPieceRecord(0x800, 1);
		if (m_highBasePiece != NULL) {
			m_hasHighBasePiece = TRUE;
		}
	}
}

// STUB: LEGORACERS 0x0049b170
void CarBuildModel::FUN_0049b170(
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
void CarBuildModel::FUN_0049b720()
{
	m_unk0x1f04 = -5.0f;
	m_unk0x1f08 = -3.0f;
	m_unk0x1f0c = 0.0f;
}

// STUB: LEGORACERS 0x0049b740
void CarBuildModel::FUN_0049b740(undefined4 p_unk0x04)
{
	STUB(0x0049b740);

	if (p_unk0x04 != NULL) {
		m_unk0x1f10 = m_unk0x1f04;
		m_unk0x1f14 = m_unk0x1f08;
		m_unk0x1f18 = m_unk0x1f0c;
		return;
	}

	if (!m_placedPieceCount) {
		FUN_0049b720();
	}

	m_unk0x1f10 = m_unk0x1f04;
	m_unk0x1f14 = m_unk0x1f08;
	m_unk0x1f18 = m_unk0x1f0c;
}

// STUB: LEGORACERS 0x0049b8b0
void CarBuildModel::FUN_0049b8b0(LegoPieceLibrary::PieceRecord*, undefined4)
{
	STUB(0x0049b8b0);
}

// STUB: LEGORACERS 0x0049b920
void CarBuildModel::FUN_0049b920(undefined4, undefined4)
{
	STUB(0x0049b920);
}

// STUB: LEGORACERS 0x0049bce0
void CarBuildModel::FUN_0049bce0(
	LegoS32,
	LegoPieceLibrary::PieceRecord**,
	LegoS32*,
	LegoS32*,
	LegoS32*,
	LegoS32*,
	LegoS32*,
	LegoS32*
)
{
	STUB(0x0049bce0);
}

// FUNCTION: LEGORACERS 0x0049bd50
LegoS32 CarBuildModel::FUN_0049bd50(LegoS32 p_index) const
{
	return m_unk0xa4.m_entries[p_index].m_unk0x08;
}

// STUB: LEGORACERS 0x0049bdc0
void CarBuildModel::FUN_0049bdc0()
{
	STUB(0x0049bdc0);
}

// STUB: LEGORACERS 0x0049bdd0
void CarBuildModel::FUN_0049bdd0(GolD3DRenderDevice*, LegoFloat)
{
	STUB(0x0049bdd0);
}

// STUB: LEGORACERS 0x0049c230
void CarBuildModel::FUN_0049c230(Placement*, GolModelEntity*)
{
	STUB(0x0049c230);
}

// STUB: LEGORACERS 0x0049c7f0
void CarBuildModel::FUN_0049c7f0(LegoU8*)
{
	STUB(0x0049c7f0);
}

// FUNCTION: LEGORACERS 0x0049c820
void CarBuildModel::FUN_0049c820(LegoU8* p_dest)
{
	m_unk0xa4.FUN_0049fca0(p_dest);
}

// FUNCTION: LEGORACERS 0x0049df20
void CarBuildModel::Field0xbc::Entry0x0c::Reset()
{
	m_unk0x00 = -1;
	m_unk0x04 = 0;
	m_unk0x08 = 0;
	m_unk0x09 = 0;
}

// FUNCTION: LEGORACERS 0x0049e210
CarBuildModel::Field0xbc::Field0xbc()
{
	m_unk0x10 = 0;
	m_unk0x0c = NULL;
	m_entries = NULL;
}

// FUNCTION: LEGORACERS 0x0049e220
CarBuildModel::Field0xbc::~Field0xbc()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x0049e230
LegoBool32 CarBuildModel::Field0xbc::Initialize(LegoS32 p_width, LegoS32 p_height)
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
void CarBuildModel::Field0xbc::ResetEntries()
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
CarBuildModel::Field0xa4::Field0xa4()
{
	m_unk0x10 = NULL;
	m_entries = NULL;
	m_unk0x08 = 0;
	m_count = 0;
	m_unk0x00 = 0;
}

// FUNCTION: LEGORACERS 0x0049f8a0
CarBuildModel::Field0xa4::~Field0xa4()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x0049f8b0
void CarBuildModel::Field0xa4::Clear()
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
LegoBool32 CarBuildModel::Field0xa4::Initialize(LegoS32 p_count)
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
void CarBuildModel::Field0xa4::FUN_0049fca0(LegoU8*)
{
	STUB(0x0049fca0);
}

// STUB: LEGORACERS 0x0049fd60
void CarBuildModel::Field0xa4::FUN_0049fd60()
{
	STUB(0x0049fd60);
}
