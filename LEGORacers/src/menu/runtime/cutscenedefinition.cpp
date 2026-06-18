#include "menu/runtime/cutscenedefinition.h"

#include "camera/golcamera.h"
#include "camera/golcamerabase.h"
#include "core/gol.h"
#include "golanimatedentity.h"
#include "golbinparser.h"
#include "golcollidableentity.h"
#include "golerror.h"
#include "golfileparser.h"
#include "golmodelbase.h"
#include "golmodelentity.h"
#include "golworldentity.h"
#include "mabmaterialanimation0x14.h"
#include "mabmaterialanimationitem0x18.h"
#include "render/gold3drenderdevice.h"
#include "util/bluebellfog0x4.h"
#include "world/golworlddatabase.h"

#include <stdlib.h>
#include <string.h>

DECOMP_SIZE_ASSERT(CutsceneDefinition, 0x2c)
DECOMP_SIZE_ASSERT(CutsceneDefinition::CdbTxtParser, 0x1fc)
DECOMP_SIZE_ASSERT(CutsceneDefinition::Frame, 0xb8)
DECOMP_SIZE_ASSERT(CutsceneDefinition::Frame::Event, 0x20)
DECOMP_SIZE_ASSERT(CutsceneDefinition::Frame::ModelEvent, 0x68)
DECOMP_SIZE_ASSERT(CutsceneDefinition::Frame::ModelEvent::ModelIndexRef, 0x08)
DECOMP_SIZE_ASSERT(CutsceneDefinition::Frame::ModelEvent::ModelRef, 0x08)
DECOMP_SIZE_ASSERT(CutsceneDefinition::Frame::ModelEvent::Animation, 0x1c)
DECOMP_SIZE_ASSERT(CutsceneDefinition::Frame::CameraEvent, 0x34)
DECOMP_SIZE_ASSERT(CutsceneDefinition::Frame::AmbientLightEvent, 0x38)
DECOMP_SIZE_ASSERT(CutsceneDefinition::Frame::DirectionalLightEvent, 0x44)
DECOMP_SIZE_ASSERT(CutsceneDefinition::Frame::TransformEvent, 0x44)

// FUNCTION: LEGORACERS 0x00404920
CutsceneDefinition::Frame::ModelEvent::ModelEvent()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00404970
CutsceneDefinition::Frame::ModelEvent::~ModelEvent()
{
	FUN_00404e80();
}

// FUNCTION: LEGORACERS 0x004049c0
LegoU32 CutsceneDefinition::Frame::ModelEvent::Reset()
{
	LegoU32 result = 0;

	m_unk0x2c.m_name[0] = '\0';
	m_modelRefType = c_modelRefNone;
	m_unk0x2c.m_indexedRef.m_resourceIndex = 0;
	m_unk0x2c.m_indexedRef.m_modelIndex = 0;
	m_unk0x28 = NULL;
	m_unk0x24 = NULL;
	m_unk0x34.m_x = 0.0f;
	m_unk0x34.m_y = 0.0f;
	m_unk0x34.m_z = 0.0f;
	m_unk0x40.m_x = 1.0f;
	m_unk0x40.m_y = 0.0f;
	m_unk0x40.m_z = 0.0f;
	m_unk0x4c.m_x = 0.0f;
	m_unk0x4c.m_y = 0.0f;
	m_unk0x4c.m_z = 1.0f;
	m_unk0x58 = -1;
	m_unk0x5c = 0;
	m_unk0x60 = NULL;
	m_unk0x64 = 0;

	return result;
}

// FUNCTION: LEGORACERS 0x00404a10
LegoU32 CutsceneDefinition::Frame::ModelEvent::FUN_00404a10(CutsceneDefinition* p_parent, GolFileParser* p_parser)
{
	LegoU32 duration = 0;
	m_unk0x28 = p_parent;

	p_parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(CutsceneDefinition::c_tokenModelBlock));
	::strncpy(m_name, p_parser->ReadStringWithMaxLength(8), sizeof(m_name));
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		switch (token) {
		case CutsceneDefinition::c_tokenStaticModelName:
			::strncpy(m_unk0x2c.m_name, p_parser->ReadStringWithMaxLength(8), sizeof(m_unk0x2c.m_name));
			m_modelRefType = c_modelRefStaticModel;
			break;
		case CutsceneDefinition::c_tokenJointedModelName:
			::strncpy(m_unk0x2c.m_name, p_parser->ReadStringWithMaxLength(8), sizeof(m_unk0x2c.m_name));
			m_modelRefType = c_modelRefJointedModel;
			break;
		case CutsceneDefinition::c_tokenBspModelName:
			::strncpy(m_unk0x2c.m_name, p_parser->ReadStringWithMaxLength(8), sizeof(m_unk0x2c.m_name));
			m_modelRefType = c_modelRefBspModel;
			break;
		case CutsceneDefinition::c_tokenIndexedModelRef:
			m_unk0x2c.m_indexedRef.m_resourceIndex = p_parser->ReadInteger();
			m_unk0x2c.m_indexedRef.m_modelIndex = p_parser->ReadInteger();
			m_modelRefType = c_modelRefIndexedModel;
			break;
		case CutsceneDefinition::c_tokenStartFrame:
			m_unk0x0c = p_parser->ReadInteger();
			break;
		case CutsceneDefinition::c_tokenDuration:
			duration = p_parser->ReadInteger();
			break;
		case CutsceneDefinition::c_tokenAnimationSequence:
			m_unk0x58 = p_parser->ReadInteger();
			break;

		case CutsceneDefinition::c_tokenMaterialAnimationRefs: {
			m_unk0x5c = p_parser->ReadBracketedCountAndLeftCurly();
			if (!m_unk0x5c) {
				p_parser->HandleUnexpectedToken(GolFileParser::e_int);
			}

			m_unk0x60 = new Animation[m_unk0x5c];
			if (!m_unk0x60) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}

			for (LegoU32 i = 0; i < m_unk0x5c; i++) {
				m_unk0x60[i].m_unk0x08 = p_parser->ReadInteger();
				m_unk0x60[i].m_unk0x0c = p_parser->ReadInteger();
				m_unk0x60[i].m_unk0x10 = p_parser->ReadInteger();
				m_unk0x60[i].m_unk0x14 = p_parser->ReadInteger();
				m_unk0x60[i].m_unk0x18 = p_parser->ReadInteger();
			}

			p_parser->ReadRightCurly();
			break;
		}
		case CutsceneDefinition::c_tokenLocation:
			m_unk0x34.m_x = p_parser->ReadFloat();
			m_unk0x34.m_y = p_parser->ReadFloat();
			m_unk0x34.m_z = p_parser->ReadFloat();
			break;
		case CutsceneDefinition::c_tokenOrientation:
			m_unk0x40.m_x = p_parser->ReadFloat();
			m_unk0x40.m_y = p_parser->ReadFloat();
			m_unk0x40.m_z = p_parser->ReadFloat();
			m_unk0x4c.m_x = p_parser->ReadFloat();
			m_unk0x4c.m_y = p_parser->ReadFloat();
			m_unk0x4c.m_z = p_parser->ReadFloat();
			break;
		default:
			break;
		}

		token = p_parser->GetNextToken();
	}

	// duration += m_unk0x0c;
	m_unk0x10 = m_unk0x0c + duration;
	return duration;
}

// FUNCTION: LEGORACERS 0x00404c90
LegoU32 CutsceneDefinition::Frame::ModelEvent::FUN_00404c90()
{
	if (!m_unk0x24) {
		LegoChar message[64];

		switch (m_modelRefType) {
		case c_modelRefStaticModel:
			m_unk0x24 = m_unk0x28->FUN_00406e30(m_unk0x2c.m_name);
			if (!m_unk0x24) {
				::strncpy(message, m_unk0x2c.m_name, sizeof(m_unk0x2c.m_name));
				message[8] = '\0';
				::strcat(message, ": Unable to find model");
				GOL_FATALERROR_MESSAGE(message);
			}
			break;
		case c_modelRefJointedModel:
			m_unk0x24 = m_unk0x28->FUN_00406e80(m_unk0x2c.m_name);
			if (!m_unk0x24) {
				::strncpy(message, m_unk0x2c.m_name, sizeof(m_unk0x2c.m_name));
				message[8] = '\0';
				::strcat(message, ": Unable to find jointed model");
				GOL_FATALERROR_MESSAGE(message);
			}
			break;
		case c_modelRefBspModel:
			m_unk0x24 = m_unk0x28->FUN_00406ed0(m_unk0x2c.m_name);
			if (!m_unk0x24) {
				::strncpy(message, m_unk0x2c.m_name, sizeof(m_unk0x2c.m_name));
				message[8] = '\0';
				::strcat(message, ": Unable to find bsp model");
				GOL_FATALERROR_MESSAGE(message);
			}
			break;
		case c_modelRefIndexedModel:
			m_unk0x24 =
				m_unk0x28->FUN_00406f20(m_unk0x2c.m_indexedRef.m_resourceIndex, m_unk0x2c.m_indexedRef.m_modelIndex);
			break;
		default:
			return m_modelRefType - 1;
		}
	}

	if (m_unk0x5c && (m_modelRefType == c_modelRefJointedModel || m_modelRefType == c_modelRefStaticModel ||
					  m_modelRefType == c_modelRefBspModel)) {
		Animation* animation = m_unk0x60;
		Animation* end = animation + m_unk0x5c;

		for (; animation < end; animation++) {
			animation->m_unk0x00 = m_unk0x28->FUN_00406f40(animation->m_unk0x08, animation->m_unk0x0c);
			animation->m_unk0x04 =
				m_unk0x28->FUN_00406f60(animation->m_unk0x08, animation->m_unk0x0c, animation->m_unk0x10);
		}
	}
}

// FUNCTION: LEGORACERS 0x00404e80
void CutsceneDefinition::Frame::ModelEvent::FUN_00404e80()
{
	if (m_unk0x60) {
		delete[] m_unk0x60;
	}

	Reset();
}

// FUNCTION: LEGORACERS 0x00404ea0
void CutsceneDefinition::Frame::ModelEvent::VTable0x04(undefined4 p_elapsedMs)
{
	if (m_unk0x14) {
		m_unk0x24->VTable0x10(p_elapsedMs);

		for (LegoU32 i = 0; i < m_unk0x5c; i++) {
			m_unk0x60[i].m_unk0x04->FUN_004104c0(
				p_elapsedMs,
				m_unk0x60[i].m_unk0x00->GetUnk0x04(),
				m_unk0x60[i].m_unk0x00->GetUnk0x08()
			);
		}
	}
}

// FUNCTION: LEGORACERS 0x00404f00
void CutsceneDefinition::Frame::ModelEvent::VTable0x08(GolD3DRenderDevice* p_renderer)
{
	if (m_unk0x14 && !m_unk0x64) {
		m_unk0x24->VTable0x1c(*p_renderer);
	}
}

// FUNCTION: LEGORACERS 0x00404f20
void CutsceneDefinition::Frame::ModelEvent::VTable0x0c(GolD3DRenderDevice* p_renderer)
{
	if (m_unk0x14 && m_unk0x64) {
		m_unk0x24->VTable0x1c(*p_renderer);
	}
}

// FUNCTION: LEGORACERS 0x00404f40
void CutsceneDefinition::Frame::ModelEvent::VTable0x10(Frame* p_frame, BluebellFog0x4* p_event)
{
	if (m_unk0x24) {
		m_unk0x64 = m_unk0x24->VTable0x20();
		m_unk0x24->VTable0x08(m_unk0x34);
		m_unk0x24->VTable0x40(m_unk0x40, m_unk0x4c);

		if (m_unk0x5c && (m_modelRefType == c_modelRefJointedModel || m_modelRefType == c_modelRefStaticModel ||
						  m_modelRefType == c_modelRefBspModel)) {
			Animation* animation = m_unk0x60;
			Animation* end = animation + m_unk0x5c;

			for (; animation < end; animation++) {
				MaterialTable0x0c* materialTarget =
					static_cast<GolModelEntity*>(m_unk0x24)->GetMaterialTable(animation->m_unk0x18);
				if (materialTarget == NULL) {
					materialTarget =
						static_cast<GolModelEntity*>(m_unk0x24)->GetModel(animation->m_unk0x18)->GetMaterialTable();
				}

				animation->m_unk0x04->FUN_10025da0(materialTarget, animation->m_unk0x14, TRUE);
			}
		}

		if (m_modelRefType == c_modelRefJointedModel && m_unk0x58 >= 0) {
			static_cast<GolAnimatedEntity*>(m_unk0x24)->FUN_0040dad0(m_unk0x58);
			static_cast<GolAnimatedEntity*>(m_unk0x24)->SetPartAnimationEnabled(TRUE);
		}

		Event::VTable0x10(p_frame, p_event);
		if (p_event) {
			p_event->VTable0x10(p_frame, m_name, this);
		}
	}
}

// FUNCTION: LEGORACERS 0x00405020
void CutsceneDefinition::Frame::ModelEvent::VTable0x14(Frame* p_frame, BluebellFog0x4* p_event)
{
	if (m_unk0x24) {
		if (m_modelRefType == c_modelRefJointedModel && m_unk0x58 >= 0) {
			static_cast<GolAnimatedEntity*>(m_unk0x24)->SetPartAnimationEnabled(FALSE);
		}

		Event::VTable0x14(p_frame, p_event);
		if (p_event) {
			p_event->VTable0x14(p_frame, m_name, this);
		}
	}
}

// FUNCTION: LEGORACERS 0x00405070
CutsceneDefinition::Frame::CameraEvent::CameraEvent()
{
	m_unk0x20 = NULL;
	m_unk0x24[0] = '\0';
	m_unk0x2c = NULL;
	m_unk0x30 = -1;
}

// FUNCTION: LEGORACERS 0x004050a0
LegoU32 CutsceneDefinition::Frame::CameraEvent::FUN_004050a0(CutsceneDefinition* p_parent, GolFileParser* p_parser)
{
	LegoU32 duration = 0;
	m_unk0x2c = p_parent;

	p_parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(CutsceneDefinition::c_tokenCameraBlock));
	::strncpy(m_name, p_parser->ReadStringWithMaxLength(8), sizeof(m_name));
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		switch (token) {
		case CutsceneDefinition::c_tokenCameraName:
			::strncpy(m_unk0x24, p_parser->ReadStringWithMaxLength(8), sizeof(m_unk0x24));
			break;
		case CutsceneDefinition::c_tokenStartFrame:
			m_unk0x0c = p_parser->ReadInteger();
			break;
		case CutsceneDefinition::c_tokenDuration:
			duration = p_parser->ReadInteger();
			break;
		case CutsceneDefinition::c_tokenAnimationSequence:
			m_unk0x30 = p_parser->ReadInteger();
			break;
		default:
			break;
		}

		token = p_parser->GetNextToken();
	}

	m_unk0x10 = duration + m_unk0x0c;
	return m_unk0x10;
}

// FUNCTION: LEGORACERS 0x00405160
void CutsceneDefinition::Frame::CameraEvent::VTable0x10(Frame* p_frame, BluebellFog0x4* p_event)
{
	if (m_unk0x2c) {
		if (!m_unk0x20) {
			m_unk0x20 = m_unk0x2c->FUN_00406de0(m_unk0x24);
			if (!m_unk0x20) {
				LegoChar message[64];
				::strncpy(message, m_unk0x24, sizeof(m_unk0x24));
				message[8] = '\0';
				::strcat(message, ": Unable to find named camera");
				GOL_FATALERROR_MESSAGE(message);
			}
		}

		p_frame->FUN_004066d0(m_unk0x20);
		if (m_unk0x30 >= 0 && m_unk0x20->m_trackedEntity) {
			m_unk0x20->m_trackedEntity->FUN_0040dad0(m_unk0x30);
		}

		Event::VTable0x10(p_frame, p_event);
		if (p_event) {
			p_event->VTable0x08(p_frame, m_name, this);
		}
	}
}

// FUNCTION: LEGORACERS 0x00405230
void CutsceneDefinition::Frame::CameraEvent::VTable0x14(Frame* p_frame, BluebellFog0x4* p_event)
{
	if (m_unk0x20) {
		p_frame->FUN_00406710(m_unk0x20);
		Event::VTable0x14(p_frame, p_event);
		if (p_event) {
			p_event->VTable0x0c(p_frame, m_name, this);
		}
	}
}

// FUNCTION: LEGORACERS 0x00405270
void CutsceneDefinition::Frame::CameraEvent::VTable0x04(undefined4)
{
	m_unk0x20->UpdateFromTrackedEntity();
}

// FUNCTION: LEGORACERS 0x00405280
LegoU32 CutsceneDefinition::Frame::DirectionalLightEvent::FUN_00405280(GolFileParser* p_parser)
{
	LegoU32 duration = 0;
	m_unk0x40 = NULL;
	m_unk0x30 = 0;
	m_unk0x34 = 0;
	m_unk0x38 = 0;
	m_unk0x3c = 0;

	p_parser->AssertNextTokenIs(
		static_cast<GolFileParser::ParserTokenType>(CutsceneDefinition::c_tokenDirectionalLightBlock)
	);
	::strncpy(m_name, p_parser->ReadStringWithMaxLength(8), sizeof(m_name));
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		switch (token) {
		case CutsceneDefinition::c_tokenStartFrame:
			m_unk0x0c = p_parser->ReadInteger();
			break;
		case CutsceneDefinition::c_tokenDuration:
			duration = p_parser->ReadInteger();
			break;
		case CutsceneDefinition::c_tokenLightColor: {
			ColorRGBA color;
			color.m_red = static_cast<LegoU8>(p_parser->ReadInteger());
			color.m_grn = static_cast<LegoU8>(p_parser->ReadInteger());
			color.m_blu = static_cast<LegoU8>(p_parser->ReadInteger());
			color.m_alp = 0xff;
			m_unk0x20.SetColor(color);
			break;
		}
		case CutsceneDefinition::c_tokenLightDirection: {
			GolVec3 direction;
			direction.m_x = p_parser->ReadFloat();
			direction.m_y = p_parser->ReadFloat();
			direction.m_z = p_parser->ReadFloat();
			m_unk0x20.SetDirection(direction);
			break;
		}
		case CutsceneDefinition::c_tokenBlinkTiming:
			m_unk0x30 = static_cast<LegoU32>(static_cast<LegoFloat>(p_parser->ReadInteger()) * 33.333328f);
			m_unk0x34 = static_cast<LegoU32>(static_cast<LegoFloat>(p_parser->ReadInteger()) * 33.333328f);
			m_unk0x3c |= 1;
			break;
		default:
			break;
		}

		token = p_parser->GetNextToken();
	}

	LegoU32 end = m_unk0x0c;
	end += duration;
	m_unk0x10 = end;
	return m_unk0x10;
}

// FUNCTION: LEGORACERS 0x00405410
void CutsceneDefinition::Frame::DirectionalLightEvent::VTable0x10(Frame* p_frame, BluebellFog0x4* p_event)
{
	m_unk0x3c |= 2;
	m_unk0x38 = m_unk0x30;
	p_frame->FUN_00406790(&m_unk0x20);

	Event::VTable0x10(p_frame, p_event);
	if (p_event) {
		p_event->VTable0x28(p_frame, m_name, this);
	}

	m_unk0x40 = p_frame;
}

// FUNCTION: LEGORACERS 0x00405460
void CutsceneDefinition::Frame::DirectionalLightEvent::VTable0x14(Frame* p_frame, BluebellFog0x4* p_event)
{
	p_frame->FUN_004067f0(&m_unk0x20);
	Event::VTable0x14(p_frame, p_event);
	if (p_event) {
		p_event->VTable0x2c(p_frame, m_name, this);
	}

	m_unk0x40 = NULL;
}

// FUNCTION: LEGORACERS 0x004054a0
void CutsceneDefinition::Frame::DirectionalLightEvent::VTable0x04(undefined4 p_elapsedMs)
{
	LegoU32 elapsedMs = p_elapsedMs;

	if (m_unk0x3c & 1) {
		if (elapsedMs > m_unk0x38) {
			if (m_unk0x3c & 2) {
				m_unk0x3c &= ~2;
				m_unk0x38 = m_unk0x34;
				m_unk0x40->FUN_004067f0(&m_unk0x20);
			}
			else {
				m_unk0x38 = m_unk0x30;
				m_unk0x3c |= 2;
				m_unk0x40->FUN_00406790(&m_unk0x20);
			}
		}
		else {
			m_unk0x38 -= elapsedMs;
		}
	}

	Event::VTable0x04(elapsedMs);
}

// FUNCTION: LEGORACERS 0x00405520
CutsceneDefinition::Frame::Event::Event()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00405560
CutsceneDefinition::Frame::Event::~Event()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00405570
void CutsceneDefinition::Frame::Event::Reset()
{
	m_name[0] = '\0';
	m_unk0x0c = 0;
	m_unk0x10 = 0;
	m_unk0x18 = NULL;
	m_unk0x1c = NULL;
	m_unk0x14 = 0;
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void CutsceneDefinition::Frame::Event::VTable0x04(undefined4)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void CutsceneDefinition::Frame::Event::VTable0x08(GolD3DRenderDevice*)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void CutsceneDefinition::Frame::Event::VTable0x0c(GolD3DRenderDevice*)
{
}

// FUNCTION: LEGORACERS 0x00405590
void CutsceneDefinition::Frame::Event::VTable0x10(Frame* p_frame, BluebellFog0x4* p_event)
{
	m_unk0x14 = 1;
	if (p_event) {
		p_event->VTable0x00(p_frame, m_name, this);
	}
}

// FUNCTION: LEGORACERS 0x004055c0
void CutsceneDefinition::Frame::Event::VTable0x14(Frame* p_frame, BluebellFog0x4* p_event)
{
	m_unk0x14 = 0;
	if (p_event) {
		p_event->VTable0x04(p_frame, m_name, this);
	}
}

// FUNCTION: LEGORACERS 0x004055f0
static LegoS32 __cdecl CompareEventStart(const void* p_left, const void* p_right)
{
	CutsceneDefinition::Frame::Event* left = *static_cast<CutsceneDefinition::Frame::Event* const*>(p_left);
	CutsceneDefinition::Frame::Event* right = *static_cast<CutsceneDefinition::Frame::Event* const*>(p_right);

	if (left->m_unk0x0c > right->m_unk0x0c) {
		return 1;
	}

	if (left->m_unk0x0c < right->m_unk0x0c) {
		return -1;
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x00405610
static LegoS32 __cdecl CompareEventEnd(const void* p_left, const void* p_right)
{
	CutsceneDefinition::Frame::Event* left = *static_cast<CutsceneDefinition::Frame::Event* const*>(p_left);
	CutsceneDefinition::Frame::Event* right = *static_cast<CutsceneDefinition::Frame::Event* const*>(p_right);

	if (left->m_unk0x10 > right->m_unk0x10) {
		return 1;
	}

	if (left->m_unk0x10 < right->m_unk0x10) {
		return -1;
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x00405630
void CutsceneDefinition::Frame::AmbientLightEvent::FUN_00405630(GolFileParser* p_parser)
{
	LegoU32 duration = 0;
	m_unk0x34 = NULL;
	m_unk0x24 = 0;
	m_unk0x28 = 0;
	m_unk0x2c = 0;
	m_unk0x30 = 0;

	p_parser->AssertNextTokenIs(
		static_cast<GolFileParser::ParserTokenType>(CutsceneDefinition::c_tokenAmbientLightBlock)
	);
	::strncpy(m_name, p_parser->ReadStringWithMaxLength(8), sizeof(m_name));
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		switch (token) {
		case CutsceneDefinition::c_tokenStartFrame:
			m_unk0x0c = p_parser->ReadInteger();
			break;
		case CutsceneDefinition::c_tokenDuration:
			duration = p_parser->ReadInteger();
			break;
		case CutsceneDefinition::c_tokenLightColor: {
			ColorRGBA color;
			color.m_red = static_cast<LegoU8>(p_parser->ReadInteger());
			color.m_grn = static_cast<LegoU8>(p_parser->ReadInteger());
			color.m_blu = static_cast<LegoU8>(p_parser->ReadInteger());
			color.m_alp = 0xff;
			m_unk0x20.SetColor(color);
			break;
		}
		case CutsceneDefinition::c_tokenBlinkTiming:
			m_unk0x24 = static_cast<LegoU32>(static_cast<LegoFloat>(p_parser->ReadInteger()) * 33.333328f);
			m_unk0x28 = static_cast<LegoU32>(static_cast<LegoFloat>(p_parser->ReadInteger()) * 33.333328f);
			m_unk0x30 |= 1;
			break;
		default:
			break;
		}

		token = p_parser->GetNextToken();
	}

	LegoU32 end = m_unk0x0c;
	end += duration;
	m_unk0x10 = end;
}

// FUNCTION: LEGORACERS 0x00405780
void CutsceneDefinition::Frame::AmbientLightEvent::VTable0x10(Frame* p_frame, BluebellFog0x4* p_event)
{
	m_unk0x30 |= 2;
	m_unk0x2c = m_unk0x24;
	p_frame->FUN_00406760(&m_unk0x20);

	Event::VTable0x10(p_frame, p_event);
	if (p_event) {
		p_event->VTable0x20(p_frame, m_name, this);
	}

	m_unk0x34 = p_frame;
}

// FUNCTION: LEGORACERS 0x004057d0
void CutsceneDefinition::Frame::AmbientLightEvent::VTable0x14(Frame* p_frame, BluebellFog0x4* p_event)
{
	p_frame->FUN_00406770(&m_unk0x20);
	Event::VTable0x14(p_frame, p_event);
	if (p_event) {
		p_event->VTable0x24(p_frame, m_name, this);
	}

	m_unk0x34 = NULL;
}

// FUNCTION: LEGORACERS 0x00405810
void CutsceneDefinition::Frame::AmbientLightEvent::VTable0x04(undefined4 p_elapsedMs)
{
	LegoU32 elapsedMs = p_elapsedMs;

	if (m_unk0x30 & 1) {
		if (elapsedMs > m_unk0x2c) {
			if (m_unk0x30 & 2) {
				m_unk0x30 &= ~2;
				m_unk0x2c = m_unk0x28;
				m_unk0x34->FUN_00406770(&m_unk0x20);
			}
			else {
				m_unk0x2c = m_unk0x24;
				m_unk0x30 |= 2;
				m_unk0x34->FUN_00406760(&m_unk0x20);
			}
		}
		else {
			m_unk0x2c -= elapsedMs;
		}
	}

	Event::VTable0x04(elapsedMs);
}

// FUNCTION: LEGORACERS 0x00405890
CutsceneDefinition::Frame::Frame()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004058a0
CutsceneDefinition::Frame::~Frame()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004058b0
void CutsceneDefinition::Frame::Reset()
{
	m_unk0x00 = NULL;
	m_unk0x54 = 30;
	m_unk0x58 = 30;
	m_unk0x04 = 0;
	m_unk0x08 = NULL;
	m_unk0x0c = 0;
	m_unk0x10 = NULL;
	m_unk0x14 = 0;
	m_unk0x18 = NULL;
	m_unk0x1c = 0;
	m_unk0x20 = NULL;
	m_unk0x24 = 0;
	m_unk0x28 = NULL;
	m_unk0x2c = 0;
	m_unk0x30 = NULL;
	m_unk0x34 = 0;
	m_unk0x38 = NULL;
	m_unk0x3c = 0;
	m_unk0x40 = NULL;
	m_unk0x44 = 0;
	m_unk0x4c = 0;
	m_unk0x48 = 0;
	m_unk0x50 = 0;
	m_unk0xa4 = 0.0f;
	m_unk0x5c = 0;
	::memset(m_unk0x60, 0, sizeof(m_unk0x60));
	m_unk0x80 = NULL;
	m_unk0x84 = 0;
	::memset(m_unk0x88, 0, sizeof(m_unk0x88));
	m_unk0xa8.m_bottom = 0;
	m_unk0xa8.m_top = 0;
	m_unk0xa8.m_left = 0;
	m_unk0xa8.m_right = 0;
}

// STUB: LEGORACERS 0x00405950
void CutsceneDefinition::Frame::FUN_00405950(CutsceneDefinition* p_parent, GolFileParser* p_parser)
{
	STUB(0x00405950);

	if (m_unk0x00) {
		Destroy();
	}

	m_unk0x00 = p_parent;
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		switch (token) {
		case CutsceneDefinition::c_tokenCameraBlock:
			FUN_00405bd0(p_parser);
			break;
		case CutsceneDefinition::c_tokenModelBlock:
			FUN_00405d10(p_parser);
			break;
		case CutsceneDefinition::c_tokenTransformBlock:
			FUN_00405e50(p_parser);
			break;
		case CutsceneDefinition::c_tokenAmbientLightBlock:
			FUN_00405f80(p_parser);
			break;
		case CutsceneDefinition::c_tokenDirectionalLightBlock:
			FUN_00406110(p_parser);
			break;
		case CutsceneDefinition::c_tokenSpeed:
			m_unk0x54 = p_parser->ReadInteger();
			m_unk0x58 = m_unk0x54;
			break;
		case CutsceneDefinition::c_tokenDuration:
			m_unk0x4c = p_parser->ReadInteger();
			break;
		default:
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}

		token = p_parser->GetNextToken();
	}

	if (!m_unk0x4c && m_unk0x04) {
		for (LegoU32 i = 0; i < m_unk0x04; i++) {
			CameraEvent* camera = &m_unk0x08[i];
			if (camera->m_unk0x10 > m_unk0x4c) {
				m_unk0x4c = camera->m_unk0x10;
			}
		}
	}

	LegoU32 eventCount = m_unk0x24;
	eventCount += m_unk0x14;
	eventCount += m_unk0x0c;
	eventCount += m_unk0x1c;
	eventCount += m_unk0x04;
	m_unk0x2c = eventCount;
	m_unk0x30 = new Event*[m_unk0x2c];
	if (!m_unk0x30) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x38 = new Event*[m_unk0x2c];
	if (!m_unk0x38) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoU32 eventIndex = 0;
	LegoU32 i;
	for (i = 0; i < m_unk0x04; i++) {
		Event* event = &m_unk0x08[i];
		m_unk0x30[eventIndex] = event;
		m_unk0x38[eventIndex] = event;
		eventIndex++;
	}

	for (i = 0; i < m_unk0x0c; i++) {
		Event* event = &m_unk0x10[i];
		m_unk0x30[eventIndex] = event;
		m_unk0x38[eventIndex] = event;
		eventIndex++;
	}

	for (i = 0; i < m_unk0x14; i++) {
		Event* event = &m_unk0x18[i];
		m_unk0x30[eventIndex] = event;
		m_unk0x38[eventIndex] = event;
		eventIndex++;
	}

	for (i = 0; i < m_unk0x1c; i++) {
		Event* event = &m_unk0x20[i];
		m_unk0x30[eventIndex] = event;
		m_unk0x38[eventIndex] = event;
		eventIndex++;
	}

	for (i = 0; i < m_unk0x24; i++) {
		Event* event = &m_unk0x28[i];
		m_unk0x30[eventIndex] = event;
		m_unk0x38[eventIndex] = event;
		eventIndex++;
	}

	::qsort(m_unk0x30, m_unk0x2c, sizeof(Event*), CompareEventStart);
	::qsort(m_unk0x38, m_unk0x2c, sizeof(Event*), CompareEventEnd);
}

// FUNCTION: LEGORACERS 0x00405bd0
void CutsceneDefinition::Frame::FUN_00405bd0(GolFileParser* p_parser)
{
	m_unk0x04 = p_parser->ReadBracketedCountAndLeftCurly();
	if (!m_unk0x04) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	m_unk0x08 = new CameraEvent[m_unk0x04];

	if (!m_unk0x08) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_unk0x04; i++) {
		m_unk0x08[i].FUN_004050a0(m_unk0x00, p_parser);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00405d10
void CutsceneDefinition::Frame::FUN_00405d10(GolFileParser* p_parser)
{
	m_unk0x0c = p_parser->ReadBracketedCountAndLeftCurly();
	if (!m_unk0x0c) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	m_unk0x10 = new ModelEvent[m_unk0x0c];

	if (!m_unk0x10) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_unk0x0c; i++) {
		m_unk0x10[i].FUN_00404a10(m_unk0x00, p_parser);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00405e50
void CutsceneDefinition::Frame::FUN_00405e50(GolFileParser* p_parser)
{
	m_unk0x14 = p_parser->ReadBracketedCountAndLeftCurly();
	if (!m_unk0x14) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	m_unk0x18 = new TransformEvent[m_unk0x14];

	if (!m_unk0x18) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_unk0x14; i++) {
		m_unk0x18[i].FUN_00407090(p_parser);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00405f80
void CutsceneDefinition::Frame::FUN_00405f80(GolFileParser* p_parser)
{
	m_unk0x1c = p_parser->ReadBracketedCountAndLeftCurly();
	if (!m_unk0x1c) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	m_unk0x20 = new AmbientLightEvent[m_unk0x1c];

	if (!m_unk0x20) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_unk0x1c; i++) {
		m_unk0x20[i].FUN_00405630(p_parser);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004060c0
CutsceneDefinition::Frame::AmbientLightEvent::AmbientLightEvent()
{
}

// FUNCTION: LEGORACERS 0x00406110
void CutsceneDefinition::Frame::FUN_00406110(GolFileParser* p_parser)
{
	m_unk0x24 = p_parser->ReadBracketedCountAndLeftCurly();
	if (!m_unk0x24) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	m_unk0x28 = new DirectionalLightEvent[m_unk0x24];

	if (!m_unk0x28) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_unk0x24; i++) {
		m_unk0x28[i].FUN_00405280(p_parser);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00406240
CutsceneDefinition::Frame::DirectionalLightEvent::DirectionalLightEvent()
{
}

// FUNCTION: LEGORACERS 0x004062a0
void CutsceneDefinition::Frame::Destroy()
{
	if (m_unk0x30) {
		delete[] m_unk0x30;
	}

	if (m_unk0x38) {
		delete[] m_unk0x38;
	}

	if (m_unk0x08) {
		delete[] m_unk0x08;
	}

	if (m_unk0x10) {
		delete[] m_unk0x10;
	}

	if (m_unk0x18) {
		delete[] m_unk0x18;
	}

	if (m_unk0x20) {
		delete[] m_unk0x20;
	}

	if (m_unk0x28) {
		delete[] m_unk0x28;
	}

	Reset();
}

// FUNCTION: LEGORACERS 0x00406310
void CutsceneDefinition::Frame::FUN_00406310()
{
	if (m_unk0x44 & c_flagComplete) {
		FUN_00406330();
	}

	m_unk0x44 &= ~c_flagComplete;
	m_unk0x44 |= c_flagPlaying;
}

// FUNCTION: LEGORACERS 0x00406330
void CutsceneDefinition::Frame::FUN_00406330()
{
	m_unk0x48 = 0;
	m_unk0x50 = 0;
	m_unk0x34 = 0;
	m_unk0x3c = 0;
	m_unk0xa4 = 0.0f;

	while (m_unk0x40) {
		m_unk0x40->VTable0x14(this, m_unk0x00->GetUnk0x0c());
		FUN_004066b0(m_unk0x40);
	}

	m_unk0x44 &= ~(c_flagComplete | c_flagLooped);
}

// FUNCTION: LEGORACERS 0x00406380
void CutsceneDefinition::Frame::FUN_00406380()
{
	m_unk0x44 &= ~(c_flagPlaying | c_flagComplete | c_flagLooped);
}

// FUNCTION: LEGORACERS 0x00406390
void CutsceneDefinition::Frame::FUN_00406390(LegoS32 p_elapsedMs)
{
	if (m_unk0x44 & c_flagPlaying) {
		LegoU32 elapsed = m_unk0x50 + p_elapsedMs * m_unk0x58;
		LegoU32 frame = elapsed / 1000;

		if (frame >= m_unk0x4c) {
			FUN_004065d0(m_unk0x48, frame);
			if (m_unk0x44 & c_flagLoop) {
				FUN_00406330();
				frame = 0;
				m_unk0x44 |= c_flagLooped;
				elapsed = 0;
				m_unk0xa4 = 0.0f;
			}
			else {
				m_unk0x44 &= ~(c_flagPlaying | c_flagLooped);
				m_unk0x44 |= c_flagComplete;
				return;
			}
		}
		else {
			m_unk0x44 &= ~(c_flagComplete | c_flagLooped);
		}

		FUN_004065d0(m_unk0x48, frame);

		if (m_unk0x58 == m_unk0x54) {
			m_unk0xa4 = static_cast<LegoFloat>(static_cast<double>(p_elapsedMs) + m_unk0xa4);
		}
		else {
			double frameElapsed = static_cast<double>(static_cast<LegoS32>(elapsed - m_unk0x50));
			double frameDivisor = static_cast<double>(static_cast<LegoS32>(m_unk0x54));
			frameElapsed = frameElapsed / frameDivisor;
			m_unk0xa4 = static_cast<LegoFloat>(frameElapsed + m_unk0xa4);
		}

		if (m_unk0xa4 >= 1.0f) {
			LegoS32 ticks = static_cast<LegoS32>(m_unk0xa4);
			FUN_004065a0(ticks);
			m_unk0xa4 = m_unk0xa4 - static_cast<LegoFloat>(ticks);
		}

		m_unk0x50 = elapsed;
		m_unk0x48 = frame;
	}
}

// FUNCTION: LEGORACERS 0x00406490
void CutsceneDefinition::Frame::FUN_00406490(Rect* p_rect)
{
	m_unk0xa8 = *p_rect;
	m_unk0x44 |= c_flagHasRect;
}

// FUNCTION: LEGORACERS 0x004064c0
void CutsceneDefinition::Frame::FUN_004064c0(GolD3DRenderDevice* p_renderer, LegoU32 p_lensIndex)
{
	if (m_unk0x5c) {
		LegoU32 lensIndex = p_lensIndex;
		if (p_lensIndex >= m_unk0x5c) {
			lensIndex = m_unk0x5c - 1;
		}

		if (m_unk0x44 & c_flagHasRect) {
			m_unk0x60[lensIndex]->VTable0x0c(&m_unk0xa8);
		}

		p_renderer->VTable0x20(m_unk0x60[lensIndex]);
		p_renderer->VTable0x5c();
		p_renderer->VTable0xec(4);
	}

	p_renderer->VTable0x28();
	if (m_unk0x80 || m_unk0x84) {
		if (m_unk0x80) {
			p_renderer->VTable0x2c(m_unk0x80);
		}

		for (LegoU32 i = 0; i < m_unk0x84; i++) {
			p_renderer->VTable0x30(m_unk0x88[i]);
		}
	}

	for (Event* event3 = m_unk0x40; event3; event3 = event3->m_unk0x1c) {
		event3->VTable0x08(p_renderer);
	}

	for (Event* event4 = m_unk0x40; event4; event4 = event4->m_unk0x1c) {
		event4->VTable0x0c(p_renderer);
	}
}

// FUNCTION: LEGORACERS 0x004065a0
void CutsceneDefinition::Frame::FUN_004065a0(undefined4 p_unk0x04)
{
	for (Event* event = m_unk0x40; event; event = event->m_unk0x1c) {
		event->VTable0x04(p_unk0x04);
	}
}

// FUNCTION: LEGORACERS 0x004065d0
LegoU32 CutsceneDefinition::Frame::FUN_004065d0(LegoU32 p_startFrame, LegoU32 p_endFrame)
{
	LegoU32 result;
	LegoU32 total;

	for (;;) {
		while (TRUE) {
			result = m_unk0x34;
			total = m_unk0x2c;

			if (result >= total) {
				break;
			}

			Event* event = m_unk0x30[result];
			result = event->m_unk0x0c;

			if (result > m_unk0x38[m_unk0x3c]->m_unk0x10) {
				break;
			}

			if (p_startFrame > result || p_endFrame < result) {
				return result;
			}

			if (!event->m_unk0x14) {
				event->VTable0x10(this, m_unk0x00->GetUnk0x0c());
				FUN_00406680(m_unk0x30[m_unk0x34]);
			}

			m_unk0x34++;
		}

		result = m_unk0x3c;
		if (result >= total) {
			break;
		}

		Event* event = m_unk0x38[result];
		result = event->m_unk0x10;

		if (p_startFrame > result || p_endFrame < result) {
			break;
		}

		if (event->m_unk0x14) {
			event->VTable0x14(this, m_unk0x00->GetUnk0x0c());
			FUN_004066b0(m_unk0x38[m_unk0x3c]);
		}

		m_unk0x3c++;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00406680
void CutsceneDefinition::Frame::FUN_00406680(Event* p_event)
{
	p_event->m_unk0x18 = NULL;

	if (m_unk0x40) {
		m_unk0x40->m_unk0x18 = p_event;
		p_event->m_unk0x1c = m_unk0x40;
	}
	else {
		p_event->m_unk0x1c = NULL;
	}

	m_unk0x40 = p_event;
}

// FUNCTION: LEGORACERS 0x004066b0
void CutsceneDefinition::Frame::FUN_004066b0(Event* p_event)
{
	Event* previous = p_event->m_unk0x18;
	Event* next = p_event->m_unk0x1c;

	if (previous) {
		previous->m_unk0x1c = next;
	}
	else {
		m_unk0x40 = next;
	}

	if (next) {
		next->m_unk0x18 = previous;
	}
}

// FUNCTION: LEGORACERS 0x004066d0
LegoU32 CutsceneDefinition::Frame::FUN_004066d0(GolCamera* p_lens)
{
	LegoU32 count = m_unk0x5c;
	for (LegoU32 i = 0; i < count; i++) {
		if (m_unk0x60[i] == p_lens) {
			return i;
		}
	}

	m_unk0x5c = count + 1;
	m_unk0x60[count] = p_lens;

	return count;
}

// FUNCTION: LEGORACERS 0x00406710
void CutsceneDefinition::Frame::FUN_00406710(GolCamera* p_lens)
{
	if (m_unk0x5c) {
		LegoU32 i = 0;
		while (i < m_unk0x5c && m_unk0x60[i] != p_lens) {
			i++;
		}

		while (i < m_unk0x5c - 1) {
			m_unk0x60[i] = m_unk0x60[i + 1];
			i++;
		}

		m_unk0x5c--;
		m_unk0x60[m_unk0x5c] = NULL;
	}
}

// FUNCTION: LEGORACERS 0x00406760
void CutsceneDefinition::Frame::FUN_00406760(const GolRenderDevice::MaterialColor* p_material)
{
	m_unk0x80 = p_material;
}

// FUNCTION: LEGORACERS 0x00406770
void CutsceneDefinition::Frame::FUN_00406770(const GolRenderDevice::MaterialColor* p_material)
{
	if (m_unk0x80 == p_material) {
		m_unk0x80 = NULL;
	}
}

// FUNCTION: LEGORACERS 0x00406790
LegoU32 CutsceneDefinition::Frame::FUN_00406790(const GolRenderDevice::Light* p_light)
{
	LegoU32 count = m_unk0x84;
	for (LegoU32 i = 0; i < count; i++) {
		if (m_unk0x88[i] == p_light) {
			return i;
		}
	}

	if (count >= sizeOfArray(m_unk0x88)) {
		FUN_004067f0(m_unk0x88[0]);
	}

	m_unk0x88[m_unk0x84] = p_light;
	m_unk0x84++;

	return m_unk0x84;
}

// FUNCTION: LEGORACERS 0x004067f0
void CutsceneDefinition::Frame::FUN_004067f0(const GolRenderDevice::Light* p_light)
{
	if (m_unk0x84) {
		LegoU32 i = 0;
		while (i < m_unk0x84 && m_unk0x88[i] != p_light) {
			i++;
		}

		while (i < m_unk0x84 - 1) {
			m_unk0x88[i] = m_unk0x88[i + 1];
			i++;
		}

		m_unk0x84--;
		m_unk0x88[m_unk0x84] = NULL;
	}
}

// FUNCTION: LEGORACERS 0x00406860
void CutsceneDefinition::Frame::FUN_00406860()
{
	for (LegoU32 i = 0; i < m_unk0x0c; i++) {
		m_unk0x10[i].FUN_00404c90();
	}
}

// FUNCTION: LEGORACERS 0x00406890
GolCamera* CutsceneDefinition::Frame::FUN_00406890()
{
	if (m_unk0x5c) {
		return m_unk0x60[m_unk0x5c - 1];
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x004068a0
CutsceneDefinition::CutsceneDefinition()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00406910
CutsceneDefinition::~CutsceneDefinition()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x00406960
void CutsceneDefinition::Reset()
{
	m_unk0x0c = NULL;
	m_golExport = NULL;
	m_renderer = NULL;
	m_unk0x18 = 0;
	m_unk0x1c = NULL;
	m_unk0x20 = NULL;
	m_frameCount = 0;
	m_frames = NULL;
}

// FUNCTION: LEGORACERS 0x00406980
void CutsceneDefinition::FUN_00406980(
	GolExport* p_golExport,
	GolD3DRenderDevice* p_renderer,
	const LegoChar* p_fileName,
	LegoBool32 p_binary
)
{
	if (m_golExport) {
		Clear();
	}

	m_golExport = p_golExport;
	m_renderer = p_renderer;

	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser();

		if (!parser) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		parser->SetSuffix(".cdb");
	}
	else {
		parser = new CdbTxtParser();

		if (!parser) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_fileName);

	GolFileParser::ParserTokenType token = parser->GetNextToken();
	while (token != GolFileParser::e_syntaxerror) {
		switch (token) {
		case GolFileParser::e_unknown0x27:
			FUN_00406cb0(parser);
			break;
		case GolFileParser::e_unknown0x28:
			FUN_00406b90(parser);
			break;
		default:
			parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}

		token = parser->GetNextToken();
	}

	parser->Dispose();
	delete parser;

	FUN_00406c50(p_binary);

	for (LegoU32 i = 0; i < m_frameCount; i++) {
		m_frames[i].FUN_00406860();
	}
}

// FUNCTION: LEGORACERS 0x00406af0
void CutsceneDefinition::Clear()
{
	if (m_unk0x1c) {
		if (m_golExport) {
			LegoU32 i;
			for (i = 0; i < m_unk0x18; i++) {
				if (m_unk0x1c[i]) {
					m_unk0x1c[i]->VTable0x18();
					m_golExport->VTable0x3c(m_unk0x1c[i]);
				}
			}
		}

		delete[] m_unk0x1c;
	}

	if (m_unk0x20) {
		delete[] m_unk0x20;
	}

	if (m_frames) {
		delete[] m_frames;
	}

	GolNameTable::Clear();
	Reset();
}

// FUNCTION: LEGORACERS 0x00406b90
void CutsceneDefinition::FUN_00406b90(GolFileParser* p_parser)
{
	if (m_unk0x1c) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	m_unk0x18 = p_parser->ReadBracketedCountAndLeftCurly();
	if (!m_unk0x18) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	m_unk0x1c = new GolWorldDatabase*[m_unk0x18];
	m_unk0x20 = new LegoChar[m_unk0x18 * 9];

	if (!m_unk0x1c || !m_unk0x20) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_unk0x18; i++) {
		::strncpy(&m_unk0x20[i * 9], p_parser->ReadStringWithMaxLength(8), 8);
		m_unk0x20[i * 9 + 8] = '\0';
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00406c50
void CutsceneDefinition::FUN_00406c50(LegoBool32 p_binary)
{
	if (m_unk0x20) {
		for (LegoU32 i = 0; i < m_unk0x18; i++) {
			m_unk0x1c[i] = m_golExport->VTable0x08();
			m_unk0x1c[i]->VTable0x14(m_renderer, &m_unk0x20[i * 9], p_binary, 1.0f);
		}
	}
}

// FUNCTION: LEGORACERS 0x00406cb0
void CutsceneDefinition::FUN_00406cb0(GolFileParser* p_parser)
{
	if (m_frames) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	m_frameCount = p_parser->ReadBracketedCountAndLeftCurly();
	if (!m_frameCount) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	GolNameTable::Allocate(m_frameCount);
	m_frames = new Frame[m_frameCount];

	if (!m_frames) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_frameCount; i++) {
		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);

		GolName name;
		::strncpy(name, p_parser->ReadStringWithMaxLength(8), sizeof(name));
		AddName(name, &m_frames[i]);
		m_frames[i].FUN_00405950(this, p_parser);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00406de0
GolCamera* CutsceneDefinition::FUN_00406de0(const LegoChar* p_name)
{
	for (LegoU32 i = 0; i < m_unk0x18; i++) {
		GolCamera* result = m_unk0x1c[i]->FindUnk0xe4(p_name);
		if (result) {
			return result;
		}
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00406e30
GolWorldEntity* CutsceneDefinition::FUN_00406e30(const LegoChar* p_name)
{
	for (LegoU32 i = 0; i < m_unk0x18; i++) {
		GolWorldEntity* result = m_unk0x1c[i]->FindUnk0xb4(p_name);
		if (result) {
			return result;
		}
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00406e80
GolWorldEntity* CutsceneDefinition::FUN_00406e80(const LegoChar* p_name)
{
	for (LegoU32 i = 0; i < m_unk0x18; i++) {
		GolWorldEntity* result = m_unk0x1c[i]->FindUnk0xc0(p_name);
		if (result) {
			return result;
		}
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00406ed0
GolWorldEntity* CutsceneDefinition::FUN_00406ed0(const LegoChar* p_name)
{
	for (LegoU32 i = 0; i < m_unk0x18; i++) {
		GolWorldEntity* result = m_unk0x1c[i]->FindUnk0xcc(p_name);
		if (result) {
			return result;
		}
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00406f20
GolWorldEntity* CutsceneDefinition::FUN_00406f20(LegoU32 p_index, LegoU32 p_modelIndex)
{
	return m_unk0x1c[p_index]->VTable0x48(p_modelIndex);
}

// FUNCTION: LEGORACERS 0x00406f40
MabMaterialAnimation0x14* CutsceneDefinition::FUN_00406f40(LegoU32 p_index, LegoU32 p_animationIndex)
{
	return m_unk0x1c[p_index]->VTable0x4c(p_animationIndex);
}

// FUNCTION: LEGORACERS 0x00406f60
MabMaterialAnimationItem0x18* CutsceneDefinition::FUN_00406f60(
	LegoU32 p_index,
	LegoU32 p_animationIndex,
	LegoU32 p_itemIndex
)
{
	MabMaterialAnimation0x14* materialAnimation = m_unk0x1c[p_index]->VTable0x4c(p_animationIndex);
	return &materialAnimation->GetUnk0x0c()[p_itemIndex];
}

// FUNCTION: LEGORACERS 0x00406f90
LegoU32 CutsceneDefinition::FUN_00406f90(LegoFloat p_scale)
{
	LegoU32 i = 0;
	LegoU32 result = m_unk0x18;
	if (result > 0) {
		do {
			m_unk0x1c[i]->FUN_00416290(p_scale);
			result = m_unk0x18;
			i++;
		} while (i < result);
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00406fc0
CutsceneDefinition::Frame::TransformEvent::TransformEvent()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00407010
CutsceneDefinition::Frame::TransformEvent::~TransformEvent()
{
	FUN_004071a0();
}

// FUNCTION: LEGORACERS 0x00407060
void CutsceneDefinition::Frame::TransformEvent::Reset()
{
	m_unk0x20.m_x = 0.0f;
	m_unk0x20.m_y = 0.0f;
	m_unk0x20.m_z = 0.0f;
	m_unk0x2c.m_x = 1.0f;
	m_unk0x2c.m_y = 0.0f;
	m_unk0x2c.m_z = 0.0f;
	m_unk0x38.m_x = 0.0f;
	m_unk0x38.m_y = 0.0f;
	m_unk0x38.m_z = 1.0f;
}

// FUNCTION: LEGORACERS 0x00407090
LegoU32 CutsceneDefinition::Frame::TransformEvent::FUN_00407090(GolFileParser* p_parser)
{
	LegoU32 duration = 0;

	p_parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(CutsceneDefinition::c_tokenTransformBlock));
	::strncpy(m_name, p_parser->ReadStringWithMaxLength(8), sizeof(m_name));
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		switch (token) {
		case CutsceneDefinition::c_tokenStartFrame:
			m_unk0x0c = p_parser->ReadInteger();
			break;
		case CutsceneDefinition::c_tokenDuration:
			duration = p_parser->ReadInteger();
			break;
		case CutsceneDefinition::c_tokenLocation:
			m_unk0x20.m_x = p_parser->ReadFloat();
			m_unk0x20.m_y = p_parser->ReadFloat();
			m_unk0x20.m_z = p_parser->ReadFloat();
			break;
		case CutsceneDefinition::c_tokenOrientation:
			m_unk0x2c.m_x = p_parser->ReadFloat();
			m_unk0x2c.m_y = p_parser->ReadFloat();
			m_unk0x2c.m_z = p_parser->ReadFloat();
			m_unk0x38.m_x = p_parser->ReadFloat();
			m_unk0x38.m_y = p_parser->ReadFloat();
			m_unk0x38.m_z = p_parser->ReadFloat();
			break;
		default:
			break;
		}

		token = p_parser->GetNextToken();
	}

	m_unk0x10 = duration + m_unk0x0c;
	return m_unk0x10;
}

// FUNCTION: LEGORACERS 0x004071a0
void CutsceneDefinition::Frame::TransformEvent::FUN_004071a0()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004071b0
void CutsceneDefinition::Frame::TransformEvent::VTable0x10(Frame* p_frame, BluebellFog0x4* p_event)
{
	Event::VTable0x10(p_frame, p_event);
	if (p_event) {
		p_event->VTable0x18(p_frame, m_name, this);
	}
}

// FUNCTION: LEGORACERS 0x004071e0
void CutsceneDefinition::Frame::TransformEvent::VTable0x14(Frame* p_frame, BluebellFog0x4* p_event)
{
	Event::VTable0x14(p_frame, p_event);
	if (p_event) {
		p_event->VTable0x1c(p_frame, m_name, this);
	}
}
