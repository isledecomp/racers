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
DECOMP_SIZE_ASSERT(CarBuildModel::PieceGrid, 0x14)
DECOMP_SIZE_ASSERT(CarBuildModel::PieceGrid::Entry0x0c, 0x0c)
DECOMP_SIZE_ASSERT(CarBuildModel::Field0x1e30Entry0x28, 0x28)

extern LegoU16 g_unk0x004befec[1024];
extern LegoU32 g_unk0x004c6ee4;

static const LegoS32 g_highPieceTypeBase = 0x800;

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
void CarBuildModel::PieceGrid::Clear()
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

	m_pieceList.m_pieceGrid = &m_pieceGrid;
	m_pieceGrid.m_pieceList = &m_pieceList;
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
	m_unk0x0c.SetPrimaryMaterialTable(p_verdantTide != NULL ? p_verdantTide->GetMaterialTable() : NULL);
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
	m_pieceGrid.Initialize(10, 6);
	m_pieceList.Initialize(64);
}

// FUNCTION: LEGORACERS 0x0049a0e0
LegoBool32 CarBuildModel::IsInitialized()
{
	return m_golExport != NULL;
}

// FUNCTION: LEGORACERS 0x0049a0f0
void CarBuildModel::Destroy()
{
	m_pieceGrid.Clear();
	m_pieceList.Clear();
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

// FUNCTION: LEGORACERS 0x0049a160
LegoBool32 CarBuildModel::FUN_0049a160(
	LegoPieceLibrary::PieceRecord* p_pieceRecord,
	LegoS32 p_x,
	LegoS32 p_y,
	LegoS32 p_rotation,
	LegoS32 p_colorRecordIndex,
	LegoS32 p_partType
)
{
	LegoBool32 allowEmpty;
	LegoS32 colorRecordIndex;

	if (p_pieceRecord->m_pieceType < g_highPieceTypeBase) {
		g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & 0x3ff;
		allowEmpty = TRUE;
		colorRecordIndex = static_cast<LegoS32>(g_unk0x004befec[g_unk0x004c6ee4]) % 10;
	}
	else {
		colorRecordIndex = p_colorRecordIndex;
		allowEmpty = FALSE;
	}

	LegoBool32 result =
		m_pieceGrid.AddPiece(p_pieceRecord, p_x, p_y, p_rotation, colorRecordIndex, p_partType, allowEmpty);
	if (result) {
		m_placedPieceCount++;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0049a1e0
LegoS32 CarBuildModel::FUN_0049a1e0(
	LegoPieceLibrary::PieceRecord* p_pieceRecord,
	LegoS32 p_x,
	LegoS32 p_y,
	LegoS32 p_rotation
)
{
	if (p_pieceRecord == NULL) {
		return -1;
	}

	LegoBool32 allowEmpty = p_pieceRecord->m_pieceType < g_highPieceTypeBase;

	LegoS32 height = m_pieceGrid.FUN_0049e2d0(p_pieceRecord, p_x, p_y, p_rotation, allowEmpty);
	if (height >= 0) {
		if (m_pieceGrid.FUN_0049e450(p_pieceRecord, p_x, p_y, p_rotation, height)) {
			return -5;
		}

		if (height + p_pieceRecord->GetMaxCellValue() > 15) {
			return -6;
		}

		if (m_placedPieceCount >= 64) {
			return -7;
		}
	}

	return height;
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

// FUNCTION: LEGORACERS 0x0049bce0
void CarBuildModel::FUN_0049bce0(
	LegoS32 p_index,
	LegoPieceLibrary::PieceRecord** p_pieceRecord,
	LegoS32* p_x,
	LegoS32* p_y,
	LegoS32* p_height,
	LegoS32* p_rotation,
	LegoS32* p_colorRecordIndex,
	LegoS32* p_partType
)
{
	*p_pieceRecord = m_pieceList.m_entries[p_index].m_pieceRecord;
	m_pieceList.m_entries[p_index].GetPlacement(p_x, p_y, p_height, p_rotation);
	*p_colorRecordIndex = m_pieceList.m_entries[p_index].m_colorRecordIndex;
	*p_partType = m_pieceList.m_entries[p_index].m_partType;
}

// FUNCTION: LEGORACERS 0x0049bd50
LegoS32 CarBuildModel::FUN_0049bd50(LegoS32 p_index) const
{
	return m_pieceList.m_entries[p_index].m_partType;
}

// FUNCTION: LEGORACERS 0x0049bd70
LegoPieceLibrary::PieceRecord* CarBuildModel::FUN_0049bd70(LegoS32 p_index)
{
	if (p_index >= 0 && p_index < m_placedPieceCount && m_pieceGrid.FUN_0049e8e0(p_index)) {
		LegoPieceLibrary::PieceRecord* result = m_pieceGrid.FUN_0049e9e0(p_index);
		m_placedPieceCount = m_pieceList.m_entryCount;

		return result;
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x0049bdc0
void CarBuildModel::FUN_0049bdc0()
{
	FUN_0049bd70(m_placedPieceCount - 1);
}

// STUB: LEGORACERS 0x0049bdd0
void CarBuildModel::FUN_0049bdd0(GolD3DRenderDevice*, LegoFloat)
{
	STUB(0x0049bdd0);
}

// FUNCTION: LEGORACERS 0x0049be50
void CarBuildModel::FUN_0049be50(LegoS32 p_x, LegoS32 p_y)
{
	if (m_unk0x1fd1[p_y + (p_x * 8)] & 0x10) {
		m_unk0x1fd1[p_y + (p_x * 8)] |= 0x20;
	}
}

// STUB: LEGORACERS 0x0049c230
void CarBuildModel::FUN_0049c230(Placement*, GolModelEntity*)
{
	STUB(0x0049c230);
}

// STUB: LEGORACERS 0x0049c6a0
LegoS32 CarBuildModel::FUN_0049c6a0(LegoFloat*, LegoFloat*, LegoFloat*)
{
	STUB(0x0049c6a0);
	return 0;
}

// FUNCTION: LEGORACERS 0x0049c7f0
LegoBool32 CarBuildModel::FUN_0049c7f0(LegoU8* p_source)
{
	LegoBool32 result = m_pieceList.Deserialize(p_source, m_pieceLibrary, 15);
	m_placedPieceCount = m_pieceList.m_entryCount;

	return result;
}

// FUNCTION: LEGORACERS 0x0049c820
void CarBuildModel::FUN_0049c820(LegoU8* p_dest)
{
	m_pieceList.Serialize(p_dest);
}

// STUB: LEGORACERS 0x0049c840
void CarBuildModel::FUN_0049c840(GolModelBase*, GolMaterialLibrary*, GolTextureList*)
{
	STUB(0x0049c840);
}

// FUNCTION: LEGORACERS 0x0049df20
void CarBuildModel::PieceGrid::Entry0x0c::Reset()
{
	m_entryIndex = -1;
	m_height = 0;
	m_occupied = FALSE;
	m_unk0x09 = 0;
}

// FUNCTION: LEGORACERS 0x0049df40
void CarBuildModel::PieceGrid::FUN_0049df40(
	LegoPieceLibrary::PieceRecord* p_pieceRecord,
	LegoS32 p_x,
	LegoS32 p_y,
	LegoS32 p_rotation,
	LegoS32 p_height,
	LegoS32 p_entryIndex
)
{
	LegoS32 width;
	LegoPieceLibrary::ShapeCell* cell;
	LegoS32 height;
	if (p_rotation & 1) {
		width = p_pieceRecord->GetHeight();
		height = p_pieceRecord->GetWidth();
	}
	else {
		width = p_pieceRecord->GetWidth();
		height = p_pieceRecord->GetHeight();
	}

	if (m_cellCallback) {
		for (LegoS32 x = 0; x < width; x++) {
			for (LegoS32 y = 0; y < height; y++) {
				cell = p_pieceRecord->GetCell(x, y, static_cast<LegoU8>(p_rotation));
				if (!((cell->m_first | cell->m_second) & 0x3f)) {
					continue;
				}

				LegoS32 index = m_height * (p_x + x) + y + p_y;
				if (m_entries[index].m_occupied) {
					LegoS32 oldHeight = m_entries[index].m_height;

					if (oldHeight != p_height + cell->GetClampedLower() ||
						(oldHeight == p_height + cell->GetClampedLower() && (cell->m_second & 0x40))) {
						PieceList::Entry0x1c& oldEntry = m_pieceList->m_entries[m_entries[index].m_entryIndex];
						LegoS32 colorRecordIndex = oldEntry.m_colorRecordIndex;
						LegoPieceLibrary::PieceRecord* oldRecord = oldEntry.m_pieceRecord;
						LegoS32 delta = 0;

						if (oldRecord->m_pieceType < g_highPieceTypeBase) {
							LegoS32 oldX;
							LegoS32 oldY;
							LegoS32 oldEntryHeight;
							LegoS32 oldRotation;
							oldEntry.GetPlacement(&oldX, &oldY, &oldEntryHeight, &oldRotation);

							oldX = p_x + x - oldX;
							oldY = p_y + y - oldY;
							delta = oldRecord->GetCell(oldX, oldY, static_cast<LegoU8>(oldRotation))->FUN_0049ea40();
						}

						m_cellCallback(p_x + x, p_y + y, oldHeight, colorRecordIndex, delta);
					}
				}

				m_entries[index].SetOccupied(cell->m_first);

				m_entries[index].m_height = p_height + (cell->m_first & 0x3f);
				m_entries[index].m_entryIndex = p_entryIndex;
			}
		}
	}
	else {
		for (LegoS32 x = 0; x < width; x++) {
			for (LegoS32 y = 0; y < height; y++) {
				cell = p_pieceRecord->GetCell(x, y, static_cast<LegoU8>(p_rotation));
				if (!((cell->m_first | cell->m_second) & 0x3f)) {
					continue;
				}

				LegoS32 index = (p_x + x) * m_height + y + p_y;
				m_entries[index].SetOccupied(cell->m_first);

				m_entries[index].m_height = p_height + (cell->m_first & 0x3f);
				m_entries[index].m_entryIndex = p_entryIndex;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x0049e210
CarBuildModel::PieceGrid::PieceGrid()
{
	m_cellCallback = NULL;
	m_pieceList = NULL;
	m_entries = NULL;
}

// FUNCTION: LEGORACERS 0x0049e220
CarBuildModel::PieceGrid::~PieceGrid()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x0049e230
LegoBool32 CarBuildModel::PieceGrid::Initialize(LegoS32 p_width, LegoS32 p_height)
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
void CarBuildModel::PieceGrid::ResetEntries()
{
	if (m_entries != NULL) {
		for (LegoS32 x = 0; x < m_width; x++) {
			for (LegoS32 y = 0; y < m_height; y++) {
				m_entries[y + (x * m_height)].Reset();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x0049e2d0
LegoS32 CarBuildModel::PieceGrid::FUN_0049e2d0(
	LegoPieceLibrary::PieceRecord* p_pieceRecord,
	LegoS32 p_x,
	LegoS32 p_y,
	LegoS32 p_rotation,
	LegoBool32 p_allowEmpty
)
{
	LegoS32 result = -1;

	if (p_x < 0 || p_y < 0) {
		return -2;
	}

	LegoS32 width;
	LegoS32 height;
	if (p_rotation & 1) {
		width = p_pieceRecord->GetHeight();
		height = p_pieceRecord->GetWidth();
	}
	else {
		width = p_pieceRecord->GetWidth();
		height = p_pieceRecord->GetHeight();
	}

	if (width + p_x > m_width) {
		return -3;
	}
	if (height + p_y > m_height) {
		return -4;
	}

	for (LegoS32 x = 0; x < width; x++) {
		for (LegoS32 y = 0; y < height; y++) {
			Entry0x0c& gridEntry = m_entries[m_height * (p_x + x) + y + p_y];
			if (gridEntry.m_occupied) {
				LegoS32 candidate = gridEntry.m_height;
				LegoPieceLibrary::ShapeCell* cell = p_pieceRecord->GetCell(x, y, static_cast<LegoU8>(p_rotation));
				if (cell->m_second & 0x80) {
					LegoS32 lower = cell->m_second & 0x3f;
					if (lower > (cell->m_first & 0x3f)) {
						lower = 0;
					}

					candidate -= lower;
					if (result < candidate) {
						result = candidate;
					}
				}
			}
			else if (p_allowEmpty && !gridEntry.m_height) {
				LegoPieceLibrary::ShapeCell* cell = p_pieceRecord->GetCell(x, y, static_cast<LegoU8>(p_rotation));
				LegoS32 lower = cell->m_second & 0x3f;
				if (lower > (cell->m_first & 0x3f)) {
					lower = 0;
				}

				if (result < -lower) {
					result = -lower;
				}
			}
		}
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0049e450
LegoS32 CarBuildModel::PieceGrid::FUN_0049e450(
	LegoPieceLibrary::PieceRecord* p_pieceRecord,
	LegoS32 p_x,
	LegoS32 p_y,
	LegoS32 p_rotation,
	LegoS32 p_height
)
{
	LegoS32 result = 0;

	LegoS32 width;
	LegoS32 height;
	if (p_rotation & 1) {
		width = p_pieceRecord->GetHeight();
		height = p_pieceRecord->GetWidth();
	}
	else {
		width = p_pieceRecord->GetWidth();
		height = p_pieceRecord->GetHeight();
	}

	if (p_height < 0) {
		return (p_pieceRecord->GetHeight() * p_pieceRecord->GetWidth()) + 1;
	}

	for (LegoS32 x = 0; x < width; x++) {
		for (LegoS32 y = 0; y < height; y++) {
			LegoS32 index = (x + p_x) * m_height + y + p_y;
			LegoS32 entryHeight = m_entries[index].m_height - p_height;
			LegoPieceLibrary::ShapeCell* cell = p_pieceRecord->GetCell(x, y, static_cast<LegoU8>(p_rotation));
			if (!((cell->m_first | cell->m_second) & 0x3f)) {
				continue;
			}

			LegoS32 lower = cell->m_second & 0x3f;
			if (lower > (cell->m_first & 0x3f)) {
				lower = 0;
			}

			if (entryHeight > lower ||
				(entryHeight == lower && m_entries[index].m_occupied && !(cell->m_second & 0xc0))) {
				result++;
			}
		}
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0049e590
void CarBuildModel::PieceGrid::FUN_0049e590(
	CarBuildModel* p_model,
	LegoPieceLibrary::PieceRecord* p_pieceRecord,
	LegoS32 p_x,
	LegoS32 p_y,
	LegoS32 p_rotation,
	LegoS32 p_height
)
{
	LegoS32 width;
	LegoS32 height;
	if (p_rotation & 1) {
		width = p_pieceRecord->GetHeight();
		height = p_pieceRecord->GetWidth();
	}
	else {
		width = p_pieceRecord->GetWidth();
		height = p_pieceRecord->GetHeight();
	}

	LegoS32 x;
	LegoS32 y;
	if (p_height < 0) {
		for (x = 0; x < width; x++) {
			for (y = 0; y < height; y++) {
				p_model->FUN_0049be50(p_x + x, p_y + y);
			}
		}
	}
	else {
		for (x = 0; x < width; x++) {
			for (y = 0; y < height; y++) {
				LegoS32 index = m_height * (p_x + x) + y + p_y;
				LegoS32 entryHeight = m_entries[index].m_height;
				LegoPieceLibrary::ShapeCell* cell = p_pieceRecord->GetCell(x, y, static_cast<LegoU8>(p_rotation));
				LegoS32 lower = cell->m_second & 0x3f;
				if (lower > (cell->m_first & 0x3f)) {
					lower = 0;
				}

				lower += p_height;
				if ((cell->m_first | cell->m_second) & 0x3f) {
					if (entryHeight > lower ||
						(entryHeight == lower && m_entries[index].m_occupied && !(cell->m_second & 0xc0))) {
						p_model->FUN_0049be50(p_x + x, p_y + y);
					}
				}
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x0049e710
LegoBool32 CarBuildModel::PieceGrid::AddPiece(
	LegoPieceLibrary::PieceRecord* p_pieceRecord,
	LegoS32 p_x,
	LegoS32 p_y,
	LegoS32 p_rotation,
	LegoS32 p_colorRecordIndex,
	LegoS32 p_partType,
	LegoBool32 p_allowEmpty
)
{
	LegoS32 height = FUN_0049e2d0(p_pieceRecord, p_x, p_y, p_rotation, p_allowEmpty);
	if (height < 0) {
		return FALSE;
	}

	if (FUN_0049e450(p_pieceRecord, p_x, p_y, p_rotation, height)) {
		return FALSE;
	}

	LegoS32 entryIndex =
		m_pieceList->AddEntry(p_pieceRecord, p_x, p_y, p_rotation, p_colorRecordIndex, p_partType, height);
	if (entryIndex == -1) {
		return FALSE;
	}

	FUN_0049df40(p_pieceRecord, p_x, p_y, p_rotation, height, entryIndex);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0049e7c0
void CarBuildModel::PieceGrid::FUN_0049e7c0(CellCallback p_callback)
{
	for (LegoS32 x = 0; x < m_width; x++) {
		for (LegoS32 y = 0; y < m_height; y++) {
			LegoS32 index = m_height * x + y;
			if (m_entries[index].m_occupied) {
				PieceList::Entry0x1c& oldEntry = m_pieceList->m_entries[m_entries[index].m_entryIndex];
				LegoS32 colorRecordIndex = oldEntry.m_colorRecordIndex;
				LegoPieceLibrary::PieceRecord* oldRecord = oldEntry.m_pieceRecord;
				LegoS32 delta = 0;

				if (oldRecord->m_pieceType < g_highPieceTypeBase) {
					LegoS32 oldX;
					LegoS32 oldY;
					LegoS32 oldEntryHeight;
					LegoS32 oldRotation;
					oldEntry.GetPlacement(&oldX, &oldY, &oldEntryHeight, &oldRotation);

					oldX = x - oldX;
					oldY = y - oldY;
					delta = oldRecord->GetCell(oldX, oldY, static_cast<LegoU8>(oldRotation))->FUN_0049ea40();
				}

				p_callback(x, y, m_entries[index].m_height, colorRecordIndex, delta);
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x0049e8c0
void CarBuildModel::PieceGrid::FUN_0049e8c0(CellCallback p_callback)
{
	m_cellCallback = p_callback;
	m_pieceList->FUN_0049f930();
	m_cellCallback = NULL;
}

// FUNCTION: LEGORACERS 0x0049e8e0
LegoPieceLibrary::PieceRecord* CarBuildModel::PieceGrid::FUN_0049e8e0(LegoS32 p_index)
{
	if (p_index < 0) {
		return NULL;
	}

	LegoPieceLibrary::PieceRecord* pieceRecord = m_pieceList->m_entries[p_index].m_pieceRecord;
	LegoPieceLibrary::PieceRecord* result = pieceRecord;

	LegoS32 x;
	LegoS32 y;
	LegoS32 entryHeight;
	LegoS32 rotation;
	m_pieceList->m_entries[p_index].GetPlacement(&x, &y, &entryHeight, &rotation);

	LegoS32 width;
	LegoS32 height;
	if (rotation & 1) {
		width = pieceRecord->GetHeight();
		height = pieceRecord->GetWidth();
	}
	else {
		width = pieceRecord->GetWidth();
		height = pieceRecord->GetHeight();
	}

	for (LegoS32 i = 0; i < width; i++) {
		for (LegoS32 j = 0; j < height; j++) {
			LegoPieceLibrary::ShapeCell* cell = pieceRecord->GetCell(i, j, static_cast<LegoU8>(rotation));
			if ((cell->m_first | cell->m_second) & 0x3f) {
				if (m_entries[y + j + ((x + i) * m_height)].m_entryIndex != p_index) {
					result = NULL;
				}
			}
		}
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0049e9e0
LegoPieceLibrary::PieceRecord* CarBuildModel::PieceGrid::FUN_0049e9e0(LegoS32 p_index)
{
	LegoPieceLibrary::PieceRecord* result = FUN_0049e8e0(p_index);
	if (result != NULL) {
		m_pieceList->RemoveEntry(p_index);
	}

	return result;
}
