#include "audio/soundgroupbinding.h"
#include "camera/golcamera.h"
#include "core/gol.h"
#include "decomp.h"
#include "golerror.h"
#include "golscenenode.h"
#include "menu/menugamecontext.h"
#include "menu/screens/carmodelscreenbase.h"
#include "mesh/golmodelbase.h"
#include "racer/drivercosmetics.h"

#include <float.h>
#include <math.h>
#include <string.h>

extern const LegoFloat g_violetShoalTwo;

DECOMP_SIZE_ASSERT(CarModelScreenBase::CarPartPlacement, 0x2d0)
DECOMP_SIZE_ASSERT(CarModelScreenBase::CarPartPlacement::CreateParams, 0x30)

// GLOBAL: LEGORACERS 0x004b2e68
LegoFloat g_unk0x4b2e68 = FLT_MAX;

// GLOBAL: LEGORACERS 0x004b2ed8
LegoFloat g_unk0x4b2ed8 = 1.0f;

// GLOBAL: LEGORACERS 0x004c7668
LegoFloat g_fieldAt0x2308AngleStep = 0.0f;

extern const LegoFloat g_unk0x4b2160;

// FUNCTION: LEGORACERS 0x004778f0
CarModelScreenBase::CarPartPlacement::CarPartPlacement()
{
	LegoFloat angle = 1.57f;

	for (LegoS32 i = 0; i < 8; i++) {
		m_unk0x2a8[i] = angle;
		angle += g_fieldAt0x2308AngleStep;
		if (angle >= g_twoPi) {
			angle -= g_twoPi;
		}
	}

	Reset();
}

// FUNCTION: LEGORACERS 0x004779d0
CarModelScreenBase::CarPartPlacement::~CarPartPlacement()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x00477a40
void CarModelScreenBase::CarPartPlacement::Reset()
{
	m_unk0x244 = 1;
	m_unk0x250.m_z = 0.0f;
	m_unk0x250.m_y = 0.0f;
	m_unk0x250.m_x = 0.0f;
	m_unk0x24 = NULL;
	m_unk0x238 = NULL;
	m_unk0x19c = NULL;
	m_unk0x1c = NULL;
	m_unk0x240 = 0;
	m_unk0x248 = 0;
	m_unk0x298 = 0;
	m_unk0x264 = 0;
	m_unk0x268 = 0;
	m_unk0x278 = FALSE;
	m_unk0x26c = 0;
	m_unk0x270 = 0;
	m_unk0x274 = 0;
	m_unk0x290 = FALSE;
	m_unk0x28c = 0;
	m_unk0x29c = 0;
	m_unk0x2a0 = 0;
	m_unk0x2a4 = 0;
	m_unk0x288 = 0;
	m_unk0x2c8 = 0;
	m_unk0x294 = 0;
	m_unk0x2cc = 0;
}

// FUNCTION: LEGORACERS 0x00477ae0
LegoBool32 CarModelScreenBase::CarPartPlacement::FUN_00477ae0(CreateParams* p_createParams)
{
	VTable0x08();

	m_unk0x1c = p_createParams->m_screen;
	m_unk0x20 = p_createParams->m_soundGroupBinding;
	m_unk0x24 = p_createParams->m_context;
	m_unk0x250.m_x = p_createParams->m_unk0x1c.m_x;
	m_unk0x250.m_y = p_createParams->m_unk0x1c.m_y;
	m_unk0x250.m_z = p_createParams->m_unk0x1c.m_z;

	if (MenuSceneElement::FUN_0046b300(p_createParams)) {
		FUN_00477cc0(p_createParams->m_unk0x2c);
		FUN_00477dc0();
		FUN_00477bf0();
		FUN_00477c50();
		m_unk0x28.FUN_004513d0(&m_unk0x24->m_unk0x21f4);
		FUN_00477f00(TRUE);
		FUN_004784d0(FALSE);
	}

	return m_unk0x18;
}

// FUNCTION: LEGORACERS 0x00477b80
LegoBool32 CarModelScreenBase::CarPartPlacement::VTable0x08()
{
	if (!m_unk0x18) {
		return TRUE;
	}

	if (m_unk0x1a4.HasModel()) {
		m_unk0x0c->VTable0x48(m_unk0x234);
	}

	m_unk0xa8.VTable0x54();

	if (m_unk0x19c) {
		m_unk0x0c->VTable0x4c(m_unk0x19c);
	}

	if (m_unk0x238) {
		m_unk0x0c->VTable0x48(m_unk0x238);
	}

	return MenuSceneElement::VTable0x08();
}

// FUNCTION: LEGORACERS 0x00477bf0
void CarModelScreenBase::CarPartPlacement::FUN_00477bf0()
{
	GolVec3 targetPosition;
	FUN_00479330(&m_unk0x27c, 0);
	LegoFloat targetZ = m_unk0x250.m_z + 4.0f;
	targetPosition.m_x = m_unk0x250.m_x;
	targetPosition.m_y = m_unk0x250.m_y;
	targetPosition.m_z = targetZ;
	m_unk0x290 = 0;
	m_unk0x288 = 0;
	m_unk0x14->FUN_00465ab0(&m_unk0x27c, &targetPosition);
}

// FUNCTION: LEGORACERS 0x00477c50
void CarModelScreenBase::CarPartPlacement::FUN_00477c50()
{
	m_unk0x234 = m_unk0x0c->VTable0x14();
	if (m_unk0x234 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoS32 maxHighPieceOffset = m_unk0x24->m_pieceLibrary.GetMaxHighPieceOffset();
	m_unk0x234->VTable0x18(m_unk0x10, 2, maxHighPieceOffset * 3, maxHighPieceOffset, 100, 5);
	m_unk0x1a4.VTable0x50(m_unk0x234, g_unk0x4b2e68);
}

// FUNCTION: LEGORACERS 0x00477cc0
void CarModelScreenBase::CarPartPlacement::FUN_00477cc0(undefined4)
{
	DriverCosmetics cosmetics;
	m_unk0x24->m_modelBuilder.SetExpressionMask(0xffff);
	m_unk0x24->m_saveSystem.GetActiveRecord().GetCosmetics(&cosmetics);

	m_unk0x238 = m_unk0x24->m_modelBuilder.BuildDriverModel(&cosmetics, NULL, 0);
	if (m_unk0x238 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x24->m_modelBuilder.ApplyFaceExpression(m_unk0x238, &cosmetics);

	m_unk0x19c = m_unk0x0c->VTable0x18();
	m_unk0x19c->VTable0x10(m_unk0x24->m_modelBuilder.GetBodySceneNode(&cosmetics));
	if (m_unk0x19c == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x1a0 = m_unk0x24->m_modelBuilder.GetBodyModelPart(&cosmetics);
	m_unk0xa8.FUN_0040d550(m_unk0x238, m_unk0x19c, m_unk0x1a0, g_unk0x4b2e68);
}

// FUNCTION: LEGORACERS 0x00477dc0
void CarModelScreenBase::CarPartPlacement::FUN_00477dc0()
{
	AwardCinematicScreen::SceneEntityGroup::CreateParams createParams;
	::memset(&createParams, 0, sizeof(createParams));
	createParams.m_chassisModels = &m_unk0x24->m_chassisModels;
	createParams.m_unk0x04 = &m_unk0x24->m_unk0x21f4;
	createParams.m_unk0x08 = m_unk0x24->m_unk0x21f4.GetUnk0x0c();
	createParams.m_unk0x0c = &m_unk0xa8;
	m_unk0x24->m_saveSystem.GetActiveRecord().GetChassisName(createParams.m_chassisName);

	m_unk0x58.FUN_00479510(&createParams);
	m_unk0x58.VTable0x08(m_unk0x250);
	m_unk0x58.VTable0x00();
}

// FUNCTION: LEGORACERS 0x00477e40
void CarModelScreenBase::CarPartPlacement::FUN_00477e40(LegoS32 p_unk0x04)
{
	CarPartSet::Entry* entry = m_unk0x24->m_unk0x21a4.GetSelectedEntry();
	LegoS32 colorRecordIndex;
	m_unk0x25c = p_unk0x04;
	entry->GetChoice(p_unk0x04, &p_unk0x04, &colorRecordIndex);

	LegoPieceLibrary::PieceRecord* pieceRecord = m_unk0x24->m_pieceLibrary.FindPieceRecord(p_unk0x04, TRUE);
	m_unk0x28.SetPiece(pieceRecord, colorRecordIndex, entry->GetPieceType());

	LegoS32 x;
	LegoS32 y;
	LegoS32 rotation;
	m_unk0x28.GetPlacement(&x, &y, &rotation);

	m_unk0x24->m_unk0x21f4.FUN_0049b740(TRUE);
	m_unk0x24->m_unk0x21f4.FUN_0049c230(&m_unk0x28, &m_unk0x1a4);
	m_unk0x1a4.VTable0x08(m_unk0x250);
	m_unk0x240 = 1;
}

// FUNCTION: LEGORACERS 0x00477f00
void CarModelScreenBase::CarPartPlacement::FUN_00477f00(LegoS32 p_unk0x04)
{
	m_unk0x298 = static_cast<LegoS8>(p_unk0x04);
	m_unk0x2c8 = static_cast<LegoFloat>(p_unk0x04);
	FUN_00477f30(m_unk0x2a8[m_unk0x298]);
}

// FUNCTION: LEGORACERS 0x00477f30
void CarModelScreenBase::CarPartPlacement::FUN_00477f30(LegoFloat p_unk0x04)
{
	GolVec3 direction;
	GolVec3 up;

	direction.m_x = 1.0f;
	direction.m_y = 0.0f;
	direction.m_z = 0.0f;
	up.m_x = 0.0f;
	up.m_y = 0.0f;
	up.m_z = 1.0f;

	GolMath::FUN_004496a0(&direction, &direction, &up, p_unk0x04);
	m_unk0x58.VTable0x40(direction, up);
	m_unk0x1a4.VTable0x40(direction, up);
}

// FUNCTION: LEGORACERS 0x00477fc0
LegoBool32 CarModelScreenBase::CarPartPlacement::FUN_00477fc0(LegoFloat p_delta)
{
	if ((m_unk0x248 & c_flagRotatingAroundCar) || p_delta == 0.0f) {
		return FALSE;
	}

	m_unk0x2c8 += p_delta;
	if (m_unk0x2c8 < 0.0f) {
		m_unk0x2c8 += 8.0f;
	}
	else if (m_unk0x2c8 >= 8.0f) {
		m_unk0x2c8 -= 8.0f;
	}

	LegoS32 index = static_cast<LegoS32>(m_unk0x2c8);
	m_unk0x29c = m_unk0x2a8[index] + ((m_unk0x2c8 - index) * g_fieldAt0x2308AngleStep);
	FUN_00477f30(m_unk0x29c);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00478080
LegoBool32 CarModelScreenBase::CarPartPlacement::FUN_00478080(LegoS32 p_delta, LegoBool32 p_setCurrentAngle)
{
	if (m_unk0x248 & c_flagRotatingAroundCar) {
		return FALSE;
	}

	m_unk0x248 |= c_flagRotatingAroundCar;
	m_unk0x2a0 = 150;
	m_unk0x2a4 = 150;

	if (p_setCurrentAngle) {
		m_unk0x29c = m_unk0x2a8[m_unk0x298];
	}

	m_unk0x298 += static_cast<LegoS8>(p_delta);
	if (m_unk0x298 >= 0) {
		m_unk0x298 %= 8;
	}
	else {
		m_unk0x298 += 8;
	}

	m_unk0x2c8 = m_unk0x298;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00478120
void CarModelScreenBase::CarPartPlacement::FUN_00478120()
{
	if (m_unk0x248 & c_flagRotatingAroundCar) {
		return;
	}

	LegoS32 index = static_cast<LegoS32>(m_unk0x2c8 + 0.5f);
	if (index == 8) {
		index = 0;
	}

	if (index != m_unk0x298 || static_cast<LegoFloat>(index) != m_unk0x2c8) {
		FUN_00478080(index - m_unk0x298, FALSE);
	}
}

// FUNCTION: LEGORACERS 0x00478180
LegoBool32 CarModelScreenBase::CarPartPlacement::FUN_00478180(LegoFloat p_delta)
{
	if ((m_unk0x248 & c_flagPitchChanging) || p_delta == 0.0f) {
		return FALSE;
	}

	if (p_delta > 0.0f) {
		if (m_unk0x288 >= g_violetShoalTwo) {
			return FALSE;
		}
	}
	else if (m_unk0x288 <= 0.0f) {
		return FALSE;
	}

	m_unk0x288 += p_delta;
	if (m_unk0x288 < 0.0f) {
		m_unk0x288 = 0.0f;
	}
	else if (m_unk0x288 > g_violetShoalTwo) {
		m_unk0x288 = 2.0f;
	}

	LegoS32 index = static_cast<LegoS32>(m_unk0x288);
	if (index == 2) {
		index = 1;
	}

	LegoFloat interpolation = m_unk0x288 - static_cast<LegoFloat>(index);
	GolVec3 minPosition;
	GolVec3 maxPosition;
	FUN_00479330(&minPosition, index);
	FUN_00479330(&maxPosition, index + 1);

	GolVec3 targetPosition;
	LegoFloat targetZ = m_unk0x250.m_z;
	targetZ += 4.0f;
	m_unk0x27c.m_x = ((maxPosition.m_x - minPosition.m_x) * interpolation) + minPosition.m_x;
	targetPosition.m_x = m_unk0x250.m_x;
	targetPosition.m_y = m_unk0x250.m_y;
	m_unk0x27c.m_y = ((maxPosition.m_y - minPosition.m_y) * interpolation) + minPosition.m_y;
	m_unk0x27c.m_z = ((maxPosition.m_z - minPosition.m_z) * interpolation) + minPosition.m_z;
	targetPosition.m_z = targetZ;
	m_unk0x14->FUN_00465ab0(&m_unk0x27c, &targetPosition);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x004782f0
LegoBool32 CarModelScreenBase::CarPartPlacement::FUN_004782f0(LegoS32 p_delta, LegoBool32 p_setCurrentPosition)
{
	if (m_unk0x248 & c_flagPitchChanging) {
		return FALSE;
	}

	if ((p_delta < 0 && m_unk0x290 == 0) || (p_delta > 0 && m_unk0x290 == 2)) {
		return FALSE;
	}

	if (p_setCurrentPosition) {
		FUN_00479330(&m_unk0x27c, m_unk0x290);
	}

	if (p_delta < 0) {
		if (-p_delta > m_unk0x290) {
			m_unk0x290 = 0;
		}
		else {
			m_unk0x290 += static_cast<LegoS8>(p_delta);
		}
	}
	else {
		m_unk0x290 += static_cast<LegoU8>(p_delta);
		if (m_unk0x290 >= 2) {
			m_unk0x290 = 2;
		}
	}

	LegoU32 flags = m_unk0x248;
	flags |= c_flagPitchChanging;
	LegoS32 pitchIndex = m_unk0x290;
	m_unk0x28c = 300;
	m_unk0x248 = flags;
	m_unk0x288 = static_cast<LegoFloat>(pitchIndex);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x004783d0
void CarModelScreenBase::CarPartPlacement::FUN_004783d0()
{
	if (m_unk0x248 & c_flagPitchChanging) {
		return;
	}

	GolVec3 cameraPosition;
	m_unk0x14->GetUnk0x64()->GetTransform()->GetPosition(&cameraPosition);

	LegoU32 closestIndex = 0;
	GolVec3 position;
	FUN_00479330(&position, 0);
	LegoFloat closestDistance = GOL_SQUARED(cameraPosition.m_z - position.m_z) +
								GOL_SQUARED(cameraPosition.m_y - position.m_y) +
								GOL_SQUARED(cameraPosition.m_x - position.m_x);

	for (LegoU32 i = 1; i < 3; i++) {
		FUN_00479330(&position, i);
		LegoFloat distance = GOL_SQUARED(cameraPosition.m_z - position.m_z) +
							 GOL_SQUARED(cameraPosition.m_y - position.m_y) +
							 GOL_SQUARED(cameraPosition.m_x - position.m_x);
		if (distance < closestDistance) {
			closestDistance = distance;
			closestIndex = i;
		}
	}

	if (closestDistance == 0.0f) {
		m_unk0x290 = static_cast<LegoU8>(closestIndex);
	}
	else {
		FUN_004782f0(closestIndex - m_unk0x290, FALSE);
	}
}

// FUNCTION: LEGORACERS 0x004784d0
LegoBool32 CarModelScreenBase::CarPartPlacement::FUN_004784d0(LegoBool32 p_rotateFirst)
{
	if (m_unk0x248 & c_flagPitchChanging) {
		return FALSE;
	}

	if (p_rotateFirst) {
		if (!FUN_00478080(9 - m_unk0x298, TRUE)) {
			return FALSE;
		}

		FUN_00479330(&m_unk0x27c, m_unk0x290);
		m_unk0x28c = 300;
	}
	else {
		m_unk0x28c = 1;
	}

	m_unk0x290 = 1;
	m_unk0x248 |= c_flagPitchChanging;
	m_unk0x288 = 1.0f;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00478560
void CarModelScreenBase::CarPartPlacement::FUN_00478560()
{
	m_unk0x28.Rotate();
	m_unk0x24->m_unk0x21f4.FUN_0049b740(TRUE);
	m_unk0x24->m_unk0x21f4.FUN_0049c230(&m_unk0x28, &m_unk0x1a4);
	m_unk0x1a4.VTable0x08(m_unk0x250);
}

// FUNCTION: LEGORACERS 0x004785b0
LegoBool32 CarModelScreenBase::CarPartPlacement::FUN_004785b0(LegoS32 p_delta)
{
	LegoS32 oldX;
	LegoS32 newX;
	LegoS32 oldY;
	LegoS32 newY;
	LegoS32 oldRotation;
	LegoS32 newRotation;

	m_unk0x28.GetPlacement(&oldX, &oldY, &oldRotation);
	m_unk0x28.FUN_00499c20(p_delta);
	m_unk0x28.GetPlacement(&newX, &newY, &newRotation);
	if (oldX == newX && oldY == newY && oldRotation == newRotation) {
		return FALSE;
	}

	m_unk0x24->m_unk0x21f4.FUN_0049b740(TRUE);
	m_unk0x24->m_unk0x21f4.FUN_0049c230(&m_unk0x28, &m_unk0x1a4);
	m_unk0x1a4.VTable0x08(m_unk0x250);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00478670
LegoBool32 CarModelScreenBase::CarPartPlacement::FUN_00478670(LegoS32 p_delta)
{
	LegoS32 oldX;
	LegoS32 newX;
	LegoS32 oldY;
	LegoS32 newY;
	LegoS32 oldRotation;
	LegoS32 newRotation;

	m_unk0x28.GetPlacement(&oldX, &oldY, &oldRotation);
	m_unk0x28.FUN_00499c60(p_delta);
	m_unk0x28.GetPlacement(&newX, &newY, &newRotation);
	if (oldX == newX && oldY == newY && oldRotation == newRotation) {
		return FALSE;
	}

	m_unk0x24->m_unk0x21f4.FUN_0049b740(TRUE);
	m_unk0x24->m_unk0x21f4.FUN_0049c230(&m_unk0x28, &m_unk0x1a4);
	m_unk0x1a4.VTable0x08(m_unk0x250);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00478730
LegoBool32 CarModelScreenBase::CarPartPlacement::FUN_00478730()
{
	LegoS32 x;
	LegoS32 y;
	LegoS32 rotation;
	LegoPieceLibrary::PieceRecord* pieceRecord = m_unk0x28.GetPieceRecord();
	m_unk0x28.GetPlacement(&x, &y, &rotation);

	LegoS32 result = m_unk0x24->m_unk0x21f4.FUN_0049a1e0(pieceRecord, x, y, rotation);
	if (result < 0) {
		if (result != -7) {
			m_unk0x20->FUN_0046e970(18);
		}
		else {
			m_unk0x1c->VTable0xc4();
		}

		return FALSE;
	}

	m_unk0x24->m_saveSystem.GetActiveRecord().MarkCarModified();
	m_unk0x248 |= c_flagCommittingPart;
	m_unk0x274 = g_unk0x4b2ed8;
	m_unk0x24c = 2500;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x004787e0
LegoBool32 CarModelScreenBase::CarPartPlacement::FUN_004787e0(
	LegoS32* p_unk0x04,
	LegoS32* p_unk0x08,
	LegoS32* p_unk0x0c
)
{
	CarBuildModel* carModel = &m_unk0x24->m_unk0x21f4;
	LegoS32 count = carModel->GetPlacedPieceCount();

	if (count == 1) {
		m_unk0x20->FUN_0046e970(18);
		*p_unk0x0c = 0;
		*p_unk0x08 = 0;
		*p_unk0x04 = 0;
		return FALSE;
	}

	LegoPieceLibrary::PieceRecord* pieceRecord;
	LegoS32 x;
	LegoS32 y;
	LegoS32 anchor;
	LegoS32 rotation;
	carModel->FUN_0049bce0(count - 1, &pieceRecord, &x, &y, &anchor, &rotation, p_unk0x0c, p_unk0x04);
	carModel->FUN_0049bdc0();
	carModel->FUN_0049b740(TRUE);
	carModel->FUN_0049b920(1, 127);
	m_unk0x28.SetPiece(pieceRecord, *p_unk0x0c, 0);
	m_unk0x28.SetPlacement(x, y, rotation, 0);
	carModel->FUN_0049c230(&m_unk0x28, &m_unk0x1a4);
	*p_unk0x08 = pieceRecord->m_pieceType;
	m_unk0x24->m_saveSystem.GetActiveRecord().MarkCarModified();
	m_unk0x20->FUN_0046e970(13);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x004788f0
LegoBool32 CarModelScreenBase::CarPartPlacement::VTable0x0c()
{
	ColorRGBA originalColor = {0x78, 0x78, 0x78, 0xff};
	ColorRGBA highlightColor = {0xb4, 0xb4, 0xb4, 0xff};
	GolRenderDevice::MaterialColor* material = m_unk0x10->GetCurrentMaterialColor();

	if (material == NULL) {
		m_unk0x23c.SetColor(originalColor);
		m_unk0x10->VTable0x2c(&m_unk0x23c);
		material = &m_unk0x23c;
	}

	originalColor = material->GetColor();
	if (m_unk0x294 == 2) {
		material->SetColor(highlightColor);
		m_unk0x10->VTable0x60();
	}

	m_unk0x58.VTable0x1c(*m_unk0x10);

	if (m_unk0x294 == 2) {
		material->SetColor(originalColor);
		m_unk0x10->VTable0x60();
	}

	if (m_unk0x240) {
		if (m_unk0x244) {
			m_unk0x24->m_unk0x21f4.FUN_0049bdd0(m_unk0x10, 0.1f);
		}

		GolModelEntity* entity = &m_unk0x1a4;
		GolVec3 position;
		position.m_x = m_unk0x250.m_x;
		position.m_y = m_unk0x250.m_y;
		position.m_z = m_unk0x26c;
		entity->VTable0x08(position);

		if (m_unk0x294 == 1) {
			material->SetColor(highlightColor);
			m_unk0x10->VTable0x60();
		}

		if (!(m_unk0x248 & (c_flagCommittingPart | c_flagResettingView))) {
			if ((m_unk0x278 & c_placementFeedbackMask) && m_unk0x290 != 2) {
				m_unk0x10->SetAlphaOverride(0x40, 0);
				m_unk0x10->VTable0x94(entity);
				m_unk0x10->ClearAlphaOverride();
			}
		}

		LegoU32 alpha;
		if (m_unk0x278 & c_placementFeedbackMask) {
			alpha = 0x96;
			LegoFloat value = m_unk0x26c - m_unk0x270 - 1.2f;

			if (value < 1.2f && m_unk0x290 != 2) {
				if (value < 0.0f) {
					alpha = 0;
				}
				else {
					LegoFloat alphaValue = value;
					alphaValue /= 1.2f;
					alphaValue *= 150.0f;
					alpha = static_cast<LegoU32>(alphaValue);
				}
			}
		}
		else {
			LegoFloat scaledTime = static_cast<LegoFloat>(static_cast<LegoS32>(m_unk0x268));
			scaledTime *= 0.001f;
			scaledTime *= g_twoPi;
			scaledTime *= -162.97466f;
			LegoS32 index = (0xffffff00 - static_cast<LegoS32>(scaledTime)) & 0x3ff;
			LegoFloat interpolation = static_cast<LegoFloat>(::cos((g_twoPi * index) / 1024.0f));
			interpolation *= 50.0f;
			alpha = static_cast<LegoU32>(interpolation) + 0x64;
		}

		position.m_z = m_unk0x270;
		entity->VTable0x08(position);

		if (!(m_unk0x248 & (c_flagCommittingPart | c_flagResettingView)) && alpha > 0) {
			m_unk0x10->SetAlphaOverride(alpha, 0);
			m_unk0x10->VTable0x94(entity);
			m_unk0x10->ClearAlphaOverride();
		}

		if (m_unk0x248 & (c_flagCommittingPart | c_flagResettingView)) {
			position.m_z = m_unk0x274;
		}
		else {
			position.m_z = g_unk0x4b2ed8;
		}

		entity->VTable0x08(position);

		if (m_unk0x290 != 2 || (m_unk0x248 & (c_flagCommittingPart | c_flagResettingView))) {
			m_unk0x10->VTable0x94(entity);
		}

		entity->VTable0x08(m_unk0x250);

		if (m_unk0x294 == 1) {
			material->SetColor(originalColor);
			m_unk0x10->VTable0x60();
		}
	}

	if (!(m_unk0x248 & (c_flagCommittingPart | c_flagResettingView))) {
		m_unk0x244 = TRUE;
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00478be0
LegoBool32 CarModelScreenBase::CarPartPlacement::VTable0x10(undefined4 p_elapsed)
{
	FUN_00478c70(p_elapsed);

	if (p_elapsed >= m_unk0x268) {
		m_unk0x268 = m_unk0x268 - p_elapsed + 1000;
	}
	else {
		m_unk0x268 -= p_elapsed;
	}

	m_unk0xa8.VTable0x10(p_elapsed);

	if (m_unk0x248) {
		if (m_unk0x248 & c_flagRotatingAroundCar) {
			FUN_00478ef0(p_elapsed);
		}
		if (m_unk0x248 & c_flagPitchChanging) {
			FUN_00478fd0(p_elapsed);
		}
		if (m_unk0x248 & c_flagCommittingPart) {
			FUN_004790f0(p_elapsed);
		}
		if (m_unk0x248 & c_flagResettingView) {
			FUN_00479250(p_elapsed);
		}
	}

	return TRUE;
}

// STUB: LEGORACERS 0x00478c70
void CarModelScreenBase::CarPartPlacement::FUN_00478c70(LegoS32 p_elapsed)
{
	if (m_unk0x248 & (c_flagCommittingPart | c_flagResettingView)) {
		return;
	}

	LegoS32 x;
	LegoS32 y;
	LegoS32 rotation;
	m_unk0x28.GetPlacement(&x, &y, &rotation);

	LegoS32 result = m_unk0x24->m_unk0x21f4.FUN_0049a1e0(m_unk0x28.GetPieceRecord(), x, y, rotation);
	LegoU8 feedbackFlags = m_unk0x278;
	if (result < 0) {
		m_unk0x278 = feedbackFlags & ~c_placementFeedbackMask;
		m_unk0x26c = m_unk0x270;
	}
	else if (!feedbackFlags) {
		FUN_00478ec0(0);
	}

	feedbackFlags = m_unk0x278;
	if (feedbackFlags & c_placementFeedbackMask) {
		if (p_elapsed >= m_unk0x264) {
			if (feedbackFlags & c_placementFeedbackLowering) {
				m_unk0x264 = 0;
				m_unk0x278 = (feedbackFlags & ~c_placementFeedbackLowering) | c_placementFeedbackHold;
			}
			else if (feedbackFlags & c_placementFeedbackHold) {
				FUN_00478e90(p_elapsed - m_unk0x264);
			}
			else if (feedbackFlags & c_placementFeedbackRaising) {
				FUN_00478ec0(p_elapsed - m_unk0x264);
			}
		}
		else {
			m_unk0x264 -= p_elapsed;
		}
	}

	m_unk0x270 = (m_unk0x24->m_unk0x21f4.GetUnk0x2028() * 0.4f) + (1.0f - 8.4f);

	feedbackFlags = m_unk0x278;
	if (feedbackFlags & c_placementFeedbackMask) {
		if (feedbackFlags & c_placementFeedbackLowering) {
			LegoFloat delta = static_cast<LegoFloat>(static_cast<LegoS32>(m_unk0x26c - m_unk0x270));
			delta *= 0.33333334f;
			if (delta > g_unk0x4b2ed8) {
				delta = g_unk0x4b2ed8;
			}
			else if (delta < 0.3f) {
				delta = 0.3f;
			}

			m_unk0x26c -= delta * 0.01f * p_elapsed;
			if (m_unk0x26c <= m_unk0x270) {
				m_unk0x264 = 0;
				m_unk0x26c = m_unk0x270;
			}
		}
		else if (feedbackFlags & c_placementFeedbackRaising) {
			m_unk0x26c += p_elapsed * 0.01f;
			LegoFloat limit = 1.0f - (1.2f * 2.0f);
			if (m_unk0x26c >= limit) {
				m_unk0x264 = 0;
				m_unk0x26c = limit;
			}
		}
	}
	else {
		m_unk0x264 = 2500;
		m_unk0x26c = m_unk0x270;
	}
}

// FUNCTION: LEGORACERS 0x00478e90
void CarModelScreenBase::CarPartPlacement::FUN_00478e90(LegoS32 p_elapsed)
{
	m_unk0x264 = 2500 - p_elapsed;
	m_unk0x278 = (m_unk0x278 & ~(c_placementFeedbackLowering | c_placementFeedbackHold)) | c_placementFeedbackRaising;
}

// FUNCTION: LEGORACERS 0x00478ec0
void CarModelScreenBase::CarPartPlacement::FUN_00478ec0(LegoS32 p_elapsed)
{
	m_unk0x264 = 2500 - p_elapsed;
	m_unk0x278 = (m_unk0x278 & ~(c_placementFeedbackHold | c_placementFeedbackRaising)) | c_placementFeedbackLowering;
}

// STUB: LEGORACERS 0x00478ef0
void CarModelScreenBase::CarPartPlacement::FUN_00478ef0(LegoS32 p_elapsed)
{
	if (m_unk0x2a0 == 0) {
		return;
	}

	if (p_elapsed >= m_unk0x2a0) {
		m_unk0x2a0 = 0;
		m_unk0x248 &= ~c_flagRotatingAroundCar;
	}
	else {
		m_unk0x2a0 -= p_elapsed;
	}

	LegoFloat scaledTime = static_cast<LegoFloat>(m_unk0x2a0);
	scaledTime /= static_cast<LegoFloat>(m_unk0x2a4);
	scaledTime *= 1.5707964f;
	scaledTime *= -162.97466f;
	LegoS32 index = (0xffffff00 - static_cast<LegoS32>(scaledTime)) & 0x3ff;
	LegoFloat interpolation = static_cast<LegoFloat>(::cos((g_twoPi * index) / 1024.0f));
	LegoFloat targetAngle = m_unk0x2a8[m_unk0x298];

	if (targetAngle > m_unk0x29c + 1.5707964f) {
		targetAngle -= g_twoPi;
	}
	else if (targetAngle < m_unk0x29c - 1.5707964f) {
		targetAngle += g_twoPi;
	}

	FUN_00477f30(targetAngle + ((m_unk0x29c - targetAngle) * interpolation));
}

// STUB: LEGORACERS 0x00478fd0
void CarModelScreenBase::CarPartPlacement::FUN_00478fd0(LegoS32 p_elapsed)
{
	if (m_unk0x28c == 0) {
		return;
	}

	if (p_elapsed >= m_unk0x28c) {
		m_unk0x28c = 0;
		m_unk0x248 &= ~c_flagPitchChanging;
	}
	else {
		m_unk0x28c -= p_elapsed;
	}

	LegoFloat scaledTime = static_cast<LegoFloat>(m_unk0x28c);
	scaledTime *= g_unk0x4b2160;
	scaledTime *= 1.5707964f;
	scaledTime *= -162.97466f;
	LegoS32 index = (0xffffff00 - static_cast<LegoS32>(scaledTime)) & 0x3ff;
	LegoFloat interpolation = static_cast<LegoFloat>(::cos((g_twoPi * index) / 1024.0f));

	GolVec3 targetPosition;
	FUN_00479330(&targetPosition, m_unk0x290);

	GolVec3 position;
	position.m_x = targetPosition.m_x + ((m_unk0x27c.m_x - targetPosition.m_x) * interpolation);
	position.m_y = targetPosition.m_y + ((m_unk0x27c.m_y - targetPosition.m_y) * interpolation);
	position.m_z = targetPosition.m_z + ((m_unk0x27c.m_z - targetPosition.m_z) * interpolation);

	GolVec3 lookAt;
	lookAt.m_x = m_unk0x250.m_x;
	lookAt.m_y = m_unk0x250.m_y;
	lookAt.m_z = m_unk0x250.m_z + 4.0f;
	m_unk0x14->FUN_00465ab0(&position, &lookAt);
}

// FUNCTION: LEGORACERS 0x004790f0
void CarModelScreenBase::CarPartPlacement::FUN_004790f0(LegoS32 p_elapsed)
{
	if (p_elapsed >= m_unk0x24c) {
		LegoPieceLibrary::PieceRecord* pieceRecord = m_unk0x28.GetPieceRecord();
		LegoS32 x;
		LegoS32 y;
		LegoS32 rotation;
		m_unk0x28.GetPlacement(&x, &y, &rotation);

		m_unk0x248 &= ~c_flagCommittingPart;
		m_unk0x24c = 0;
		m_unk0x58.FUN_10026fa0(-1.0f);
		m_unk0x58.VTable0x00();

		m_unk0x24->m_unk0x21f4.FUN_0049a160(
			pieceRecord,
			x,
			y,
			rotation,
			m_unk0x28.GetColorRecordIndex(),
			m_unk0x24->m_unk0x21a4.GetSelectedEntry()->GetPieceType()
		);
		m_unk0x24->m_unk0x21f4.FUN_0049b740(TRUE);
		m_unk0x24->m_unk0x21f4.FUN_0049b920(1, 127);
		m_unk0x1c->VTable0x10(m_unk0x14);

		if (m_unk0x24->m_unk0x21f4.GetUnk0xdc()) {
			m_unk0x1c->VTable0xc4();
			m_unk0x24->m_unk0x21f4.FUN_0049bdc0();
			m_unk0x24->m_unk0x21f4.FUN_0049b740(TRUE);
			m_unk0x24->m_unk0x21f4.FUN_0049b920(1, 127);
		}
		else {
			m_unk0x20->FUN_0046e970(10);
		}
	}
	else {
		m_unk0x24c -= p_elapsed;
	}

	m_unk0x274 -= p_elapsed * 0.01f;
	if (m_unk0x274 < m_unk0x270) {
		m_unk0x24c = 0;
		m_unk0x274 = m_unk0x270;
	}
}

// FUNCTION: LEGORACERS 0x00479250
void CarModelScreenBase::CarPartPlacement::FUN_00479250(LegoS32 p_elapsed)
{
	if (p_elapsed >= m_unk0x24c) {
		LegoU32 flags = m_unk0x248 & ~c_flagResettingView;
		m_unk0x24c = 0;
		m_unk0x248 = flags;
		m_unk0x1c->VTable0x10(m_unk0x14);
	}
	else {
		m_unk0x24c -= p_elapsed;
	}

	m_unk0x274 += p_elapsed * 0.006f;
	if (m_unk0x274 > g_unk0x4b2ed8) {
		m_unk0x24c = 0;
		m_unk0x274 = g_unk0x4b2ed8;
	}
}

// FUNCTION: LEGORACERS 0x004792d0
void CarModelScreenBase::CarPartPlacement::FUN_004792d0()
{
	m_unk0x24c = 2000;
	m_unk0x244 = 0;
	m_unk0x248 |= 8;
	m_unk0x274 = m_unk0x270;
}

// FUNCTION: LEGORACERS 0x00479300
void CarModelScreenBase::CarPartPlacement::FUN_00479300()
{
	m_unk0x294 = 2;
}

// FUNCTION: LEGORACERS 0x00479310
void CarModelScreenBase::CarPartPlacement::FUN_00479310()
{
	m_unk0x294 = 1;
}

// FUNCTION: LEGORACERS 0x00479320
void CarModelScreenBase::CarPartPlacement::FUN_00479320()
{
	m_unk0x294 = 0;
}

// STUB: LEGORACERS 0x00479330
void CarModelScreenBase::CarPartPlacement::FUN_00479330(GolVec3* p_dest, LegoS32 p_index)
{
	GolVec3 minPosition;
	GolVec3 maxPosition;

	switch (p_index) {
	case 1:
		minPosition.m_x = 0.0f;
		minPosition.m_y = -10.0f;
		minPosition.m_z = 14.0f;
		maxPosition.m_x = 0.0f;
		maxPosition.m_y = -12.0f;
		maxPosition.m_z = 17.0f;
		break;
	case 2:
		minPosition.m_x = 0.0f;
		minPosition.m_y = -0.3f;
		minPosition.m_z = 17.0f;
		maxPosition.m_x = 0.0f;
		maxPosition.m_y = -0.3f;
		maxPosition.m_z = 20.0f;
		break;
	default:
		minPosition.m_x = 0.0f;
		minPosition.m_y = -14.0f;
		minPosition.m_z = 9.0f;
		maxPosition.m_x = 0.0f;
		maxPosition.m_y = -18.0f;
		maxPosition.m_z = 10.0f;
		break;
	}

	m_unk0x2cc = (m_unk0x58.FUN_10028710() - 5.9f) / (8.5f - 5.9f);
	if (m_unk0x2cc > 1.0f) {
		m_unk0x2cc = 1.0f;
	}
	else if (m_unk0x2cc < 0.0f) {
		m_unk0x2cc = 0.0f;
	}

	LegoFloat value = minPosition.m_x;
	value *= 1.0f - m_unk0x2cc;
	value += maxPosition.m_x * m_unk0x2cc;
	p_dest->m_x = value;

	value = minPosition.m_y;
	value *= 1.0f - m_unk0x2cc;
	value += maxPosition.m_y * m_unk0x2cc;
	p_dest->m_y = value;

	value = minPosition.m_z;
	value *= 1.0f - m_unk0x2cc;
	value += maxPosition.m_z * m_unk0x2cc;
	p_dest->m_z = value;
}
