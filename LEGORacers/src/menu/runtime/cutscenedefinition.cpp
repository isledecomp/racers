#include "menu/runtime/cutscenedefinition.h"

#include "camera/golcamera.h"
#include "core/gol.h"
#include "golanimatedentity.h"
#include "golbinparser.h"
#include "golcamerabase.h"
#include "golcollidableentity.h"
#include "golerror.h"
#include "golfileparser.h"
#include "golmodelbase.h"
#include "golmodelentity.h"
#include "golworldentity.h"
#include "mabmaterialanimation.h"
#include "mabmaterialtrack.h"
#include "render/gold3drenderdevice.h"
#include "util/cutsceneeventsink.h"
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
	Destroy();
}

// FUNCTION: LEGORACERS 0x004049c0
LegoU32 CutsceneDefinition::Frame::ModelEvent::Reset()
{
	LegoU32 result = 0;

	m_modelRef.m_name[0] = '\0';
	m_modelRefType = c_modelRefNone;
	m_modelRef.m_indexedRef.m_resourceIndex = 0;
	m_modelRef.m_indexedRef.m_modelIndex = 0;
	m_definition = NULL;
	m_entity = NULL;
	m_location.m_x = 0.0f;
	m_location.m_y = 0.0f;
	m_location.m_z = 0.0f;
	m_direction.m_x = 1.0f;
	m_direction.m_y = 0.0f;
	m_direction.m_z = 0.0f;
	m_up.m_x = 0.0f;
	m_up.m_y = 0.0f;
	m_up.m_z = 1.0f;
	m_animationIndex = -1;
	m_animationCount = 0;
	m_animations = NULL;
	m_transparent = 0;

	return result;
}

// FUNCTION: LEGORACERS 0x00404a10
LegoU32 CutsceneDefinition::Frame::ModelEvent::Parse(CutsceneDefinition* p_parent, GolFileParser* p_parser)
{
	LegoU32 duration = 0;
	m_definition = p_parent;

	p_parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(CutsceneDefinition::c_tokenModelBlock));
	::strncpy(m_name, p_parser->ReadStringWithMaxLength(8), sizeof(m_name));
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token;
	while ((token = p_parser->GetNextToken()) != GolFileParser::e_rightCurly) {
		switch (token) {
		case CutsceneDefinition::c_tokenStaticModelName:
			::strncpy(m_modelRef.m_name, p_parser->ReadStringWithMaxLength(8), sizeof(m_modelRef.m_name));
			m_modelRefType = c_modelRefStaticModel;
			break;
		case CutsceneDefinition::c_tokenJointedModelName:
			::strncpy(m_modelRef.m_name, p_parser->ReadStringWithMaxLength(8), sizeof(m_modelRef.m_name));
			m_modelRefType = c_modelRefJointedModel;
			break;
		case CutsceneDefinition::c_tokenBspModelName:
			::strncpy(m_modelRef.m_name, p_parser->ReadStringWithMaxLength(8), sizeof(m_modelRef.m_name));
			m_modelRefType = c_modelRefBspModel;
			break;
		case CutsceneDefinition::c_tokenIndexedModelRef:
			m_modelRef.m_indexedRef.m_resourceIndex = p_parser->ReadInteger();
			m_modelRef.m_indexedRef.m_modelIndex = p_parser->ReadInteger();
			m_modelRefType = c_modelRefIndexedModel;
			break;
		case CutsceneDefinition::c_tokenStartFrame:
			m_startFrame = p_parser->ReadInteger();
			break;
		case CutsceneDefinition::c_tokenDuration:
			duration = p_parser->ReadInteger();
			break;
		case CutsceneDefinition::c_tokenAnimationSequence:
			m_animationIndex = p_parser->ReadInteger();
			break;

		case CutsceneDefinition::c_tokenMaterialAnimationRefs: {
			m_animationCount = p_parser->ReadBracketedCountAndLeftCurly();
			if (!m_animationCount) {
				p_parser->HandleUnexpectedToken(GolFileParser::e_int);
			}

			m_animations = new Animation[m_animationCount];
			if (!m_animations) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}

			for (LegoU32 i = 0; i < m_animationCount; i++) {
				m_animations[i].m_resourceIndex = p_parser->ReadInteger();
				m_animations[i].m_animationIndex = p_parser->ReadInteger();
				m_animations[i].m_itemIndex = p_parser->ReadInteger();
				m_animations[i].m_startParam0x14 = p_parser->ReadInteger();
				m_animations[i].m_materialTableIndex = p_parser->ReadInteger();
			}

			p_parser->ReadRightCurly();
			break;
		}
		case CutsceneDefinition::c_tokenLocation:
			m_location.m_x = p_parser->ReadFloat();
			m_location.m_y = p_parser->ReadFloat();
			m_location.m_z = p_parser->ReadFloat();
			break;
		case CutsceneDefinition::c_tokenOrientation:
			m_direction.m_x = p_parser->ReadFloat();
			m_direction.m_y = p_parser->ReadFloat();
			m_direction.m_z = p_parser->ReadFloat();
			m_up.m_x = p_parser->ReadFloat();
			m_up.m_y = p_parser->ReadFloat();
			m_up.m_z = p_parser->ReadFloat();
			break;
		default:
			break;
		}
	}

	// duration += m_startFrame;
	m_endFrame = m_startFrame + duration;
	return duration;
}

// FUNCTION: LEGORACERS 0x00404c90
void CutsceneDefinition::Frame::ModelEvent::ResolveEntity()
{
	if (!m_entity) {
		LegoChar message[64];

		switch (m_modelRefType) {
		case c_modelRefStaticModel:
			m_entity = m_definition->FindModelEntity(m_modelRef.m_name);
			if (!m_entity) {
				::strncpy(message, m_modelRef.m_name, sizeof(m_modelRef.m_name));
				message[8] = '\0';
				::strcat(message, ": Unable to find model");
				GOL_FATALERROR_MESSAGE(message);
			}
			break;
		case c_modelRefJointedModel:
			m_entity = m_definition->FindJointedEntity(m_modelRef.m_name);
			if (!m_entity) {
				::strncpy(message, m_modelRef.m_name, sizeof(m_modelRef.m_name));
				message[8] = '\0';
				::strcat(message, ": Unable to find jointed model");
				GOL_FATALERROR_MESSAGE(message);
			}
			break;
		case c_modelRefBspModel:
			m_entity = m_definition->FindBspEntity(m_modelRef.m_name);
			if (!m_entity) {
				::strncpy(message, m_modelRef.m_name, sizeof(m_modelRef.m_name));
				message[8] = '\0';
				::strcat(message, ": Unable to find bsp model");
				GOL_FATALERROR_MESSAGE(message);
			}
			break;
		case c_modelRefIndexedModel:
			m_entity = m_definition->GetIndexedEntity(
				m_modelRef.m_indexedRef.m_resourceIndex,
				m_modelRef.m_indexedRef.m_modelIndex
			);
			break;
		default:
			return;
		}
	}

	if (m_animationCount && (m_modelRefType == c_modelRefJointedModel || m_modelRefType == c_modelRefStaticModel ||
							 m_modelRefType == c_modelRefBspModel)) {
		Animation* animation = m_animations;
		Animation* end = animation + m_animationCount;

		for (; animation < end; animation++) {
			animation->m_materialAnimation =
				m_definition->GetMaterialAnimation(animation->m_resourceIndex, animation->m_animationIndex);
			animation->m_item = m_definition->GetMaterialAnimationItem(
				animation->m_resourceIndex,
				animation->m_animationIndex,
				animation->m_itemIndex
			);
		}
	}
}

// FUNCTION: LEGORACERS 0x00404e80
void CutsceneDefinition::Frame::ModelEvent::Destroy()
{
	if (m_animations) {
		delete[] m_animations;
	}

	Reset();
}

// FUNCTION: LEGORACERS 0x00404ea0
void CutsceneDefinition::Frame::ModelEvent::Update(undefined4 p_elapsedMs)
{
	if (m_active) {
		m_entity->Update(p_elapsedMs);

		for (LegoU32 i = 0; i < m_animationCount; i++) {
			m_animations[i].m_item->Update(
				p_elapsedMs,
				m_animations[i].m_materialAnimation->GetFrames(),
				m_animations[i].m_materialAnimation->GetFrameCount()
			);
		}
	}
}

// FUNCTION: LEGORACERS 0x00404f00
void CutsceneDefinition::Frame::ModelEvent::Draw(GolD3DRenderDevice* p_renderer)
{
	if (m_active && !m_transparent) {
		m_entity->Draw(*p_renderer);
	}
}

// FUNCTION: LEGORACERS 0x00404f20
void CutsceneDefinition::Frame::ModelEvent::DrawTransparent(GolD3DRenderDevice* p_renderer)
{
	if (m_active && m_transparent) {
		m_entity->Draw(*p_renderer);
	}
}

// FUNCTION: LEGORACERS 0x00404f40
void CutsceneDefinition::Frame::ModelEvent::Begin(Frame* p_frame, CutsceneEventSink* p_event)
{
	if (m_entity) {
		m_transparent = m_entity->GetKind();
		m_entity->SetPosition(m_location);
		m_entity->SetDirectionUp(m_direction, m_up);

		if (m_animationCount && (m_modelRefType == c_modelRefJointedModel || m_modelRefType == c_modelRefStaticModel ||
								 m_modelRefType == c_modelRefBspModel)) {
			Animation* animation = m_animations;
			Animation* end = animation + m_animationCount;

			for (; animation < end; animation++) {
				MaterialTable* materialTarget =
					static_cast<GolModelEntity*>(m_entity)->GetMaterialTable(animation->m_materialTableIndex);
				if (materialTarget == NULL) {
					materialTarget = static_cast<GolModelEntity*>(m_entity)
										 ->GetModel(animation->m_materialTableIndex)
										 ->GetMaterialTable();
				}

				animation->m_item->Assign(materialTarget, animation->m_startParam0x14, TRUE);
			}
		}

		if (m_modelRefType == c_modelRefJointedModel && m_animationIndex >= 0) {
			static_cast<GolAnimatedEntity*>(m_entity)->PlayPart(m_animationIndex);
			static_cast<GolAnimatedEntity*>(m_entity)->SetPartAnimationEnabled(TRUE);
		}

		Event::Begin(p_frame, p_event);
		if (p_event) {
			p_event->OnModelStarted(p_frame, m_name, this);
		}
	}
}

// FUNCTION: LEGORACERS 0x00405020
void CutsceneDefinition::Frame::ModelEvent::End(Frame* p_frame, CutsceneEventSink* p_event)
{
	if (m_entity) {
		if (m_modelRefType == c_modelRefJointedModel && m_animationIndex >= 0) {
			static_cast<GolAnimatedEntity*>(m_entity)->SetPartAnimationEnabled(FALSE);
		}

		Event::End(p_frame, p_event);
		if (p_event) {
			p_event->OnModelEnded(p_frame, m_name, this);
		}
	}
}

// FUNCTION: LEGORACERS 0x00405070
CutsceneDefinition::Frame::CameraEvent::CameraEvent()
{
	m_camera = NULL;
	m_cameraName[0] = '\0';
	m_definition = NULL;
	m_animationIndex = -1;
}

// FUNCTION: LEGORACERS 0x004050a0
LegoU32 CutsceneDefinition::Frame::CameraEvent::Parse(CutsceneDefinition* p_parent, GolFileParser* p_parser)
{
	LegoU32 duration = 0;
	m_definition = p_parent;

	p_parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(CutsceneDefinition::c_tokenCameraBlock));
	::strncpy(m_name, p_parser->ReadStringWithMaxLength(8), sizeof(m_name));
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token;
	while ((token = p_parser->GetNextToken()) != GolFileParser::e_rightCurly) {
		switch (token) {
		case CutsceneDefinition::c_tokenCameraName:
			::strncpy(m_cameraName, p_parser->ReadStringWithMaxLength(8), sizeof(m_cameraName));
			break;
		case CutsceneDefinition::c_tokenStartFrame:
			m_startFrame = p_parser->ReadInteger();
			break;
		case CutsceneDefinition::c_tokenDuration:
			duration = p_parser->ReadInteger();
			break;
		case CutsceneDefinition::c_tokenAnimationSequence:
			m_animationIndex = p_parser->ReadInteger();
			break;
		default:
			break;
		}
	}

	m_endFrame = duration + m_startFrame;
	return m_endFrame;
}

// FUNCTION: LEGORACERS 0x00405160
void CutsceneDefinition::Frame::CameraEvent::Begin(Frame* p_frame, CutsceneEventSink* p_event)
{
	if (m_definition) {
		if (!m_camera) {
			m_camera = m_definition->FindCamera(m_cameraName);
			if (!m_camera) {
				LegoChar message[64];
				::strncpy(message, m_cameraName, sizeof(m_cameraName));
				message[8] = '\0';
				::strcat(message, ": Unable to find named camera");
				GOL_FATALERROR_MESSAGE(message);
			}
		}

		p_frame->PushCamera(m_camera);
		if (m_animationIndex >= 0 && m_camera->m_trackedEntity) {
			m_camera->m_trackedEntity->PlayPart(m_animationIndex);
		}

		Event::Begin(p_frame, p_event);
		if (p_event) {
			p_event->OnCameraStarted(p_frame, m_name, this);
		}
	}
}

// FUNCTION: LEGORACERS 0x00405230
void CutsceneDefinition::Frame::CameraEvent::End(Frame* p_frame, CutsceneEventSink* p_event)
{
	if (m_camera) {
		p_frame->RemoveCamera(m_camera);
		Event::End(p_frame, p_event);
		if (p_event) {
			p_event->OnCameraEnded(p_frame, m_name, this);
		}
	}
}

// FUNCTION: LEGORACERS 0x00405270
void CutsceneDefinition::Frame::CameraEvent::Update(undefined4)
{
	m_camera->UpdateFromTrackedEntity();
}

// FUNCTION: LEGORACERS 0x00405280
LegoU32 CutsceneDefinition::Frame::DirectionalLightEvent::Parse(GolFileParser* p_parser)
{
	LegoU32 duration = 0;
	m_frame = NULL;
	m_blinkOnMs = 0;
	m_blinkOffMs = 0;
	m_blinkTimerMs = 0;
	m_blinkFlags = 0;

	p_parser->AssertNextTokenIs(
		static_cast<GolFileParser::ParserTokenType>(CutsceneDefinition::c_tokenDirectionalLightBlock)
	);
	::strncpy(m_name, p_parser->ReadStringWithMaxLength(8), sizeof(m_name));
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token;
	while ((token = p_parser->GetNextToken()) != GolFileParser::e_rightCurly) {
		switch (token) {
		case CutsceneDefinition::c_tokenStartFrame:
			m_startFrame = p_parser->ReadInteger();
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
			m_light.SetColor(color);
			break;
		}
		case CutsceneDefinition::c_tokenLightDirection: {
			GolVec3 direction;
			direction.m_x = p_parser->ReadFloat();
			direction.m_y = p_parser->ReadFloat();
			direction.m_z = p_parser->ReadFloat();
			m_light.SetDirection(direction);
			break;
		}
		case CutsceneDefinition::c_tokenBlinkTiming:
			m_blinkOnMs = static_cast<LegoU32>(static_cast<LegoFloat>(p_parser->ReadInteger()) * 33.333328f);
			m_blinkOffMs = static_cast<LegoU32>(static_cast<LegoFloat>(p_parser->ReadInteger()) * 33.333328f);
			m_blinkFlags |= 1;
			break;
		default:
			break;
		}
	}

	LegoU32 end = m_startFrame;
	end += duration;
	m_endFrame = end;
	return m_endFrame;
}

// FUNCTION: LEGORACERS 0x00405410
void CutsceneDefinition::Frame::DirectionalLightEvent::Begin(Frame* p_frame, CutsceneEventSink* p_event)
{
	m_blinkFlags |= 2;
	m_blinkTimerMs = m_blinkOnMs;
	p_frame->AddLight(&m_light);

	Event::Begin(p_frame, p_event);
	if (p_event) {
		p_event->OnDirectionalLightStarted(p_frame, m_name, this);
	}

	m_frame = p_frame;
}

// FUNCTION: LEGORACERS 0x00405460
void CutsceneDefinition::Frame::DirectionalLightEvent::End(Frame* p_frame, CutsceneEventSink* p_event)
{
	p_frame->RemoveLight(&m_light);
	Event::End(p_frame, p_event);
	if (p_event) {
		p_event->OnDirectionalLightEnded(p_frame, m_name, this);
	}

	m_frame = NULL;
}

// FUNCTION: LEGORACERS 0x004054a0
void CutsceneDefinition::Frame::DirectionalLightEvent::Update(undefined4 p_elapsedMs)
{
	LegoU32 elapsedMs = p_elapsedMs;

	if (m_blinkFlags & 1) {
		if (elapsedMs > m_blinkTimerMs) {
			if (m_blinkFlags & 2) {
				m_blinkFlags &= ~2;
				m_blinkTimerMs = m_blinkOffMs;
				m_frame->RemoveLight(&m_light);
			}
			else {
				m_blinkTimerMs = m_blinkOnMs;
				m_blinkFlags |= 2;
				m_frame->AddLight(&m_light);
			}
		}
		else {
			m_blinkTimerMs -= elapsedMs;
		}
	}

	Event::Update(elapsedMs);
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
	m_startFrame = 0;
	m_endFrame = 0;
	m_prev = NULL;
	m_next = NULL;
	m_active = 0;
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void CutsceneDefinition::Frame::Event::Update(undefined4)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void CutsceneDefinition::Frame::Event::Draw(GolD3DRenderDevice*)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void CutsceneDefinition::Frame::Event::DrawTransparent(GolD3DRenderDevice*)
{
}

// FUNCTION: LEGORACERS 0x00405590
void CutsceneDefinition::Frame::Event::Begin(Frame* p_frame, CutsceneEventSink* p_event)
{
	m_active = 1;
	if (p_event) {
		p_event->OnEventStarted(p_frame, m_name, this);
	}
}

// FUNCTION: LEGORACERS 0x004055c0
void CutsceneDefinition::Frame::Event::End(Frame* p_frame, CutsceneEventSink* p_event)
{
	m_active = 0;
	if (p_event) {
		p_event->OnEventEnded(p_frame, m_name, this);
	}
}

// FUNCTION: LEGORACERS 0x004055f0
static LegoS32 __cdecl CompareEventStart(const void* p_left, const void* p_right)
{
	CutsceneDefinition::Frame::Event* left = *static_cast<CutsceneDefinition::Frame::Event* const*>(p_left);
	CutsceneDefinition::Frame::Event* right = *static_cast<CutsceneDefinition::Frame::Event* const*>(p_right);

	if (left->m_startFrame > right->m_startFrame) {
		return 1;
	}

	if (left->m_startFrame < right->m_startFrame) {
		return -1;
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x00405610
static LegoS32 __cdecl CompareEventEnd(const void* p_left, const void* p_right)
{
	CutsceneDefinition::Frame::Event* left = *static_cast<CutsceneDefinition::Frame::Event* const*>(p_left);
	CutsceneDefinition::Frame::Event* right = *static_cast<CutsceneDefinition::Frame::Event* const*>(p_right);

	if (left->m_endFrame > right->m_endFrame) {
		return 1;
	}

	if (left->m_endFrame < right->m_endFrame) {
		return -1;
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x00405630
void CutsceneDefinition::Frame::AmbientLightEvent::Parse(GolFileParser* p_parser)
{
	LegoU32 duration = 0;
	m_frame = NULL;
	m_blinkOnMs = 0;
	m_blinkOffMs = 0;
	m_blinkTimerMs = 0;
	m_blinkFlags = 0;

	p_parser->AssertNextTokenIs(
		static_cast<GolFileParser::ParserTokenType>(CutsceneDefinition::c_tokenAmbientLightBlock)
	);
	::strncpy(m_name, p_parser->ReadStringWithMaxLength(8), sizeof(m_name));
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token;
	while ((token = p_parser->GetNextToken()) != GolFileParser::e_rightCurly) {
		switch (token) {
		case CutsceneDefinition::c_tokenStartFrame:
			m_startFrame = p_parser->ReadInteger();
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
			m_material.SetColor(color);
			break;
		}
		case CutsceneDefinition::c_tokenBlinkTiming:
			m_blinkOnMs = static_cast<LegoU32>(static_cast<LegoFloat>(p_parser->ReadInteger()) * 33.333328f);
			m_blinkOffMs = static_cast<LegoU32>(static_cast<LegoFloat>(p_parser->ReadInteger()) * 33.333328f);
			m_blinkFlags |= 1;
			break;
		default:
			break;
		}
	}

	LegoU32 end = m_startFrame;
	end += duration;
	m_endFrame = end;
}

// FUNCTION: LEGORACERS 0x00405780
void CutsceneDefinition::Frame::AmbientLightEvent::Begin(Frame* p_frame, CutsceneEventSink* p_event)
{
	m_blinkFlags |= 2;
	m_blinkTimerMs = m_blinkOnMs;
	p_frame->SetAmbientMaterial(&m_material);

	Event::Begin(p_frame, p_event);
	if (p_event) {
		p_event->OnAmbientLightStarted(p_frame, m_name, this);
	}

	m_frame = p_frame;
}

// FUNCTION: LEGORACERS 0x004057d0
void CutsceneDefinition::Frame::AmbientLightEvent::End(Frame* p_frame, CutsceneEventSink* p_event)
{
	p_frame->ClearAmbientMaterial(&m_material);
	Event::End(p_frame, p_event);
	if (p_event) {
		p_event->OnAmbientLightEnded(p_frame, m_name, this);
	}

	m_frame = NULL;
}

// FUNCTION: LEGORACERS 0x00405810
void CutsceneDefinition::Frame::AmbientLightEvent::Update(undefined4 p_elapsedMs)
{
	LegoU32 elapsedMs = p_elapsedMs;

	if (m_blinkFlags & 1) {
		if (elapsedMs > m_blinkTimerMs) {
			if (m_blinkFlags & 2) {
				m_blinkFlags &= ~2;
				m_blinkTimerMs = m_blinkOffMs;
				m_frame->ClearAmbientMaterial(&m_material);
			}
			else {
				m_blinkTimerMs = m_blinkOnMs;
				m_blinkFlags |= 2;
				m_frame->SetAmbientMaterial(&m_material);
			}
		}
		else {
			m_blinkTimerMs -= elapsedMs;
		}
	}

	Event::Update(elapsedMs);
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
	m_definition = NULL;
	m_frameRate = 30;
	m_playbackRate = 30;
	m_cameraEventCount = 0;
	m_cameraEvents = NULL;
	m_modelEventCount = 0;
	m_modelEvents = NULL;
	m_transformEventCount = 0;
	m_transformEvents = NULL;
	m_ambientEventCount = 0;
	m_ambientEvents = NULL;
	m_directionalEventCount = 0;
	m_directionalEvents = NULL;
	m_eventCount = 0;
	m_eventsByStart = NULL;
	m_startCursor = 0;
	m_eventsByEnd = NULL;
	m_endCursor = 0;
	m_activeEvents = NULL;
	m_flags = 0;
	m_frameCount = 0;
	m_currentFrame = 0;
	m_elapsedScaled = 0;
	m_tickAccumulator = 0.0f;
	m_cameraCount = 0;
	::memset(m_cameraStack, 0, sizeof(m_cameraStack));
	m_ambientMaterial = NULL;
	m_lightCount = 0;
	::memset(m_lights, 0, sizeof(m_lights));
	m_viewportRect.m_bottom = 0;
	m_viewportRect.m_top = 0;
	m_viewportRect.m_left = 0;
	m_viewportRect.m_right = 0;
}

// FUNCTION: LEGORACERS 0x00405950
void CutsceneDefinition::Frame::Parse(CutsceneDefinition* p_parent, GolFileParser* p_parser)
{
	if (m_definition) {
		Destroy();
	}

	m_definition = p_parent;
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token;
	while ((token = p_parser->GetNextToken()) != GolFileParser::e_rightCurly) {
		switch (token) {
		case CutsceneDefinition::c_tokenCameraBlock:
			ParseCameraEvents(p_parser);
			break;
		case CutsceneDefinition::c_tokenModelBlock:
			ParseModelEvents(p_parser);
			break;
		case CutsceneDefinition::c_tokenTransformBlock:
			ParseTransformEvents(p_parser);
			break;
		case CutsceneDefinition::c_tokenAmbientLightBlock:
			ParseAmbientLightEvents(p_parser);
			break;
		case CutsceneDefinition::c_tokenDirectionalLightBlock:
			ParseDirectionalLightEvents(p_parser);
			break;
		case CutsceneDefinition::c_tokenSpeed:
			m_frameRate = p_parser->ReadInteger();
			m_playbackRate = m_frameRate;
			break;
		case CutsceneDefinition::c_tokenDuration:
			m_frameCount = p_parser->ReadInteger();
			break;
		default:
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}
	}

	if (!m_frameCount && m_cameraEventCount) {
		for (LegoU32 i = 0; i < m_cameraEventCount; i++) {
			CameraEvent* camera = &m_cameraEvents[i];
			if (camera->m_endFrame > m_frameCount) {
				m_frameCount = camera->m_endFrame;
			}
		}
	}

	LegoU32 eventCount = m_directionalEventCount;
	eventCount += m_transformEventCount;
	eventCount += m_modelEventCount;
	eventCount += m_ambientEventCount;
	eventCount += m_cameraEventCount;
	m_eventCount = eventCount;
	m_eventsByStart = new Event*[m_eventCount];
	if (!m_eventsByStart) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_eventsByEnd = new Event*[m_eventCount];
	if (!m_eventsByEnd) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoU32 eventIndex = 0;
	for (; eventIndex < m_cameraEventCount; eventIndex++) {
		m_eventsByStart[eventIndex] = &m_cameraEvents[eventIndex];
		m_eventsByEnd[eventIndex] = &m_cameraEvents[eventIndex];
	}

	LegoU32 i;
	for (i = 0; i < m_modelEventCount; i++) {
		m_eventsByStart[eventIndex] = &m_modelEvents[i];
		m_eventsByEnd[eventIndex] = &m_modelEvents[i];
		eventIndex++;
	}

	for (i = 0; i < m_transformEventCount; i++) {
		m_eventsByStart[eventIndex] = &m_transformEvents[i];
		m_eventsByEnd[eventIndex] = &m_transformEvents[i];
		eventIndex++;
	}

	for (i = 0; i < m_ambientEventCount; i++) {
		m_eventsByStart[eventIndex] = &m_ambientEvents[i];
		m_eventsByEnd[eventIndex] = &m_ambientEvents[i];
		eventIndex++;
	}

	for (i = 0; i < m_directionalEventCount; i++) {
		m_eventsByStart[eventIndex] = &m_directionalEvents[i];
		m_eventsByEnd[eventIndex] = &m_directionalEvents[i];
		eventIndex++;
	}

	::qsort(m_eventsByStart, m_eventCount, sizeof(Event*), CompareEventStart);
	::qsort(m_eventsByEnd, m_eventCount, sizeof(Event*), CompareEventEnd);
}

// FUNCTION: LEGORACERS 0x00405bd0
void CutsceneDefinition::Frame::ParseCameraEvents(GolFileParser* p_parser)
{
	m_cameraEventCount = p_parser->ReadBracketedCountAndLeftCurly();
	if (!m_cameraEventCount) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	m_cameraEvents = new CameraEvent[m_cameraEventCount];

	if (!m_cameraEvents) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_cameraEventCount; i++) {
		m_cameraEvents[i].Parse(m_definition, p_parser);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00405d10
void CutsceneDefinition::Frame::ParseModelEvents(GolFileParser* p_parser)
{
	m_modelEventCount = p_parser->ReadBracketedCountAndLeftCurly();
	if (!m_modelEventCount) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	m_modelEvents = new ModelEvent[m_modelEventCount];

	if (!m_modelEvents) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_modelEventCount; i++) {
		m_modelEvents[i].Parse(m_definition, p_parser);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00405e50
void CutsceneDefinition::Frame::ParseTransformEvents(GolFileParser* p_parser)
{
	m_transformEventCount = p_parser->ReadBracketedCountAndLeftCurly();
	if (!m_transformEventCount) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	m_transformEvents = new TransformEvent[m_transformEventCount];

	if (!m_transformEvents) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_transformEventCount; i++) {
		m_transformEvents[i].Parse(p_parser);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00405f80
void CutsceneDefinition::Frame::ParseAmbientLightEvents(GolFileParser* p_parser)
{
	m_ambientEventCount = p_parser->ReadBracketedCountAndLeftCurly();
	if (!m_ambientEventCount) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	m_ambientEvents = new AmbientLightEvent[m_ambientEventCount];

	if (!m_ambientEvents) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_ambientEventCount; i++) {
		m_ambientEvents[i].Parse(p_parser);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004060c0
CutsceneDefinition::Frame::AmbientLightEvent::AmbientLightEvent()
{
}

// FUNCTION: LEGORACERS 0x00406110
void CutsceneDefinition::Frame::ParseDirectionalLightEvents(GolFileParser* p_parser)
{
	m_directionalEventCount = p_parser->ReadBracketedCountAndLeftCurly();
	if (!m_directionalEventCount) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	m_directionalEvents = new DirectionalLightEvent[m_directionalEventCount];

	if (!m_directionalEvents) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_directionalEventCount; i++) {
		m_directionalEvents[i].Parse(p_parser);
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
	if (m_eventsByStart) {
		delete[] m_eventsByStart;
	}

	if (m_eventsByEnd) {
		delete[] m_eventsByEnd;
	}

	if (m_cameraEvents) {
		delete[] m_cameraEvents;
	}

	if (m_modelEvents) {
		delete[] m_modelEvents;
	}

	if (m_transformEvents) {
		delete[] m_transformEvents;
	}

	if (m_ambientEvents) {
		delete[] m_ambientEvents;
	}

	if (m_directionalEvents) {
		delete[] m_directionalEvents;
	}

	Reset();
}

// FUNCTION: LEGORACERS 0x00406310
void CutsceneDefinition::Frame::Play()
{
	if (m_flags & c_flagComplete) {
		Rewind();
	}

	m_flags &= ~c_flagComplete;
	m_flags |= c_flagPlaying;
}

// FUNCTION: LEGORACERS 0x00406330
void CutsceneDefinition::Frame::Rewind()
{
	m_currentFrame = 0;
	m_elapsedScaled = 0;
	m_startCursor = 0;
	m_endCursor = 0;
	m_tickAccumulator = 0.0f;

	while (m_activeEvents) {
		m_activeEvents->End(this, m_definition->GetEventSink());
		RemoveActiveEvent(m_activeEvents);
	}

	m_flags &= ~(c_flagComplete | c_flagLooped);
}

// FUNCTION: LEGORACERS 0x00406380
void CutsceneDefinition::Frame::Stop()
{
	m_flags &= ~(c_flagPlaying | c_flagComplete | c_flagLooped);
}

// FUNCTION: LEGORACERS 0x00406390
void CutsceneDefinition::Frame::Update(LegoS32 p_elapsedMs)
{
	if (m_flags & c_flagPlaying) {
		LegoU32 elapsed = m_elapsedScaled + p_elapsedMs * m_playbackRate;
		LegoU32 frame = elapsed / 1000;

		if (frame >= m_frameCount) {
			ProcessEvents(m_currentFrame, frame);
			if (m_flags & c_flagLoop) {
				Rewind();
				frame = 0;
				m_flags |= c_flagLooped;
				elapsed = 0;
				m_tickAccumulator = 0.0f;
			}
			else {
				m_flags &= ~(c_flagPlaying | c_flagLooped);
				m_flags |= c_flagComplete;
				return;
			}
		}
		else {
			m_flags &= ~(c_flagComplete | c_flagLooped);
		}

		ProcessEvents(m_currentFrame, frame);

		if (m_playbackRate == m_frameRate) {
			m_tickAccumulator = static_cast<LegoFloat>(static_cast<double>(p_elapsedMs) + m_tickAccumulator);
		}
		else {
			double frameElapsed = static_cast<double>(static_cast<LegoS32>(elapsed - m_elapsedScaled));
			double frameDivisor = static_cast<double>(static_cast<LegoS32>(m_frameRate));
			frameElapsed = frameElapsed / frameDivisor;
			m_tickAccumulator = static_cast<LegoFloat>(frameElapsed + m_tickAccumulator);
		}

		if (m_tickAccumulator >= 1.0f) {
			LegoS32 ticks = static_cast<LegoS32>(m_tickAccumulator);
			UpdateActiveEvents(ticks);
			m_tickAccumulator = m_tickAccumulator - static_cast<LegoFloat>(ticks);
		}

		m_elapsedScaled = elapsed;
		m_currentFrame = frame;
	}
}

// FUNCTION: LEGORACERS 0x00406490
void CutsceneDefinition::Frame::SetViewportRect(Rect* p_rect)
{
	m_viewportRect = *p_rect;
	m_flags |= c_flagHasRect;
}

// FUNCTION: LEGORACERS 0x004064c0
void CutsceneDefinition::Frame::Draw(GolD3DRenderDevice* p_renderer, LegoU32 p_lensIndex)
{
	if (m_cameraCount) {
		LegoU32 lensIndex = p_lensIndex;
		if (p_lensIndex >= m_cameraCount) {
			lensIndex = m_cameraCount - 1;
		}

		if (m_flags & c_flagHasRect) {
			m_cameraStack[lensIndex]->SetViewport(&m_viewportRect);
		}

		p_renderer->SetCamera(m_cameraStack[lensIndex]);
		p_renderer->ApplyCamera();
		p_renderer->SelectViewport(4);
	}

	p_renderer->ClearLights();
	if (m_ambientMaterial || m_lightCount) {
		if (m_ambientMaterial) {
			p_renderer->SetAmbient(m_ambientMaterial);
		}

		for (LegoU32 i = 0; i < m_lightCount; i++) {
			p_renderer->AddLight(m_lights[i]);
		}
	}

	for (Event* event3 = m_activeEvents; event3; event3 = event3->m_next) {
		event3->Draw(p_renderer);
	}

	for (Event* event4 = m_activeEvents; event4; event4 = event4->m_next) {
		event4->DrawTransparent(p_renderer);
	}
}

// FUNCTION: LEGORACERS 0x004065a0
void CutsceneDefinition::Frame::UpdateActiveEvents(undefined4 p_elapsedMs)
{
	for (Event* event = m_activeEvents; event; event = event->m_next) {
		event->Update(p_elapsedMs);
	}
}

// FUNCTION: LEGORACERS 0x004065d0
LegoU32 CutsceneDefinition::Frame::ProcessEvents(LegoU32 p_startFrame, LegoU32 p_endFrame)
{
	LegoU32 result;
	LegoU32 total;

	for (;;) {
		while (TRUE) {
			result = m_startCursor;
			total = m_eventCount;

			if (result >= total) {
				break;
			}

			Event* event = m_eventsByStart[result];
			result = event->m_startFrame;

			if (result > m_eventsByEnd[m_endCursor]->m_endFrame) {
				break;
			}

			if (p_startFrame > result || p_endFrame < result) {
				return result;
			}

			if (!event->m_active) {
				event->Begin(this, m_definition->GetEventSink());
				AddActiveEvent(m_eventsByStart[m_startCursor]);
			}

			m_startCursor++;
		}

		result = m_endCursor;
		if (result >= total) {
			break;
		}

		Event* event = m_eventsByEnd[result];
		result = event->m_endFrame;

		if (p_startFrame > result || p_endFrame < result) {
			break;
		}

		if (event->m_active) {
			event->End(this, m_definition->GetEventSink());
			RemoveActiveEvent(m_eventsByEnd[m_endCursor]);
		}

		m_endCursor++;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00406680
void CutsceneDefinition::Frame::AddActiveEvent(Event* p_event)
{
	p_event->m_prev = NULL;

	if (m_activeEvents) {
		m_activeEvents->m_prev = p_event;
		p_event->m_next = m_activeEvents;
	}
	else {
		p_event->m_next = NULL;
	}

	m_activeEvents = p_event;
}

// FUNCTION: LEGORACERS 0x004066b0
void CutsceneDefinition::Frame::RemoveActiveEvent(Event* p_event)
{
	Event* previous = p_event->m_prev;
	Event* next = p_event->m_next;

	if (previous) {
		previous->m_next = next;
	}
	else {
		m_activeEvents = next;
	}

	if (next) {
		next->m_prev = previous;
	}
}

// FUNCTION: LEGORACERS 0x004066d0
LegoU32 CutsceneDefinition::Frame::PushCamera(GolCamera* p_lens)
{
	LegoU32 count = m_cameraCount;
	for (LegoU32 i = 0; i < count; i++) {
		if (m_cameraStack[i] == p_lens) {
			return i;
		}
	}

	m_cameraCount = count + 1;
	m_cameraStack[count] = p_lens;

	return count;
}

// FUNCTION: LEGORACERS 0x00406710
void CutsceneDefinition::Frame::RemoveCamera(GolCamera* p_lens)
{
	if (m_cameraCount) {
		LegoU32 i = 0;
		while (i < m_cameraCount && m_cameraStack[i] != p_lens) {
			i++;
		}

		while (i < m_cameraCount - 1) {
			m_cameraStack[i] = m_cameraStack[i + 1];
			i++;
		}

		m_cameraCount--;
		m_cameraStack[m_cameraCount] = NULL;
	}
}

// FUNCTION: LEGORACERS 0x00406760
void CutsceneDefinition::Frame::SetAmbientMaterial(const GolRenderDevice::MaterialColor* p_material)
{
	m_ambientMaterial = p_material;
}

// FUNCTION: LEGORACERS 0x00406770
void CutsceneDefinition::Frame::ClearAmbientMaterial(const GolRenderDevice::MaterialColor* p_material)
{
	if (m_ambientMaterial == p_material) {
		m_ambientMaterial = NULL;
	}
}

// FUNCTION: LEGORACERS 0x00406790
LegoU32 CutsceneDefinition::Frame::AddLight(const GolRenderDevice::Light* p_light)
{
	LegoU32 count = m_lightCount;
	for (LegoU32 i = 0; i < count; i++) {
		if (m_lights[i] == p_light) {
			return i;
		}
	}

	if (count >= sizeOfArray(m_lights)) {
		RemoveLight(m_lights[0]);
	}

	m_lights[m_lightCount] = p_light;
	m_lightCount++;

	return m_lightCount;
}

// FUNCTION: LEGORACERS 0x004067f0
void CutsceneDefinition::Frame::RemoveLight(const GolRenderDevice::Light* p_light)
{
	if (m_lightCount) {
		LegoU32 i = 0;
		while (i < m_lightCount && m_lights[i] != p_light) {
			i++;
		}

		while (i < m_lightCount - 1) {
			m_lights[i] = m_lights[i + 1];
			i++;
		}

		m_lightCount--;
		m_lights[m_lightCount] = NULL;
	}
}

// FUNCTION: LEGORACERS 0x00406860
void CutsceneDefinition::Frame::ResolveEntities()
{
	for (LegoU32 i = 0; i < m_modelEventCount; i++) {
		m_modelEvents[i].ResolveEntity();
	}
}

// FUNCTION: LEGORACERS 0x00406890
GolCamera* CutsceneDefinition::Frame::GetActiveCamera()
{
	if (m_cameraCount) {
		return m_cameraStack[m_cameraCount - 1];
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
	m_eventSink = NULL;
	m_golExport = NULL;
	m_renderer = NULL;
	m_worldDatabaseCount = 0;
	m_worldDatabases = NULL;
	m_worldNames = NULL;
	m_frameCount = 0;
	m_frames = NULL;
}

// FUNCTION: LEGORACERS 0x00406980
void CutsceneDefinition::Load(
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
		case CdbTxtParser::e_frames:
			ParseFrames(parser);
			break;
		case CdbTxtParser::e_worlds:
			ParseWorldNames(parser);
			break;
		default:
			parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}

		token = parser->GetNextToken();
	}

	parser->Dispose();
	delete parser;

	LoadWorlds(p_binary);

	for (LegoU32 i = 0; i < m_frameCount; i++) {
		m_frames[i].ResolveEntities();
	}
}

// FUNCTION: LEGORACERS 0x00406af0
void CutsceneDefinition::Clear()
{
	if (m_worldDatabases) {
		if (m_golExport) {
			LegoU32 i;
			for (i = 0; i < m_worldDatabaseCount; i++) {
				if (m_worldDatabases[i]) {
					m_worldDatabases[i]->Destroy();
					m_golExport->DestroyWorldDatabase(m_worldDatabases[i]);
				}
			}
		}

		delete[] m_worldDatabases;
	}

	if (m_worldNames) {
		delete[] m_worldNames;
	}

	if (m_frames) {
		delete[] m_frames;
	}

	GolNameTable::Clear();
	Reset();
}

// FUNCTION: LEGORACERS 0x00406b90
void CutsceneDefinition::ParseWorldNames(GolFileParser* p_parser)
{
	if (m_worldDatabases) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	m_worldDatabaseCount = p_parser->ReadBracketedCountAndLeftCurly();
	if (!m_worldDatabaseCount) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	m_worldDatabases = new GolWorldDatabase*[m_worldDatabaseCount];
	m_worldNames = new LegoChar[m_worldDatabaseCount * 9];

	if (!m_worldDatabases || !m_worldNames) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_worldDatabaseCount; i++) {
		::strncpy(&m_worldNames[i * 9], p_parser->ReadStringWithMaxLength(8), 8);
		m_worldNames[i * 9 + 8] = '\0';
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00406c50
void CutsceneDefinition::LoadWorlds(LegoBool32 p_binary)
{
	if (m_worldNames) {
		for (LegoU32 i = 0; i < m_worldDatabaseCount; i++) {
			m_worldDatabases[i] = m_golExport->CreateWorldDatabase();
			m_worldDatabases[i]->Load(m_renderer, &m_worldNames[i * 9], p_binary, 1.0f);
		}
	}
}

// FUNCTION: LEGORACERS 0x00406cb0
void CutsceneDefinition::ParseFrames(GolFileParser* p_parser)
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
		p_parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(CdbTxtParser::e_frames));

		GolName name;
		::strncpy(name, p_parser->ReadStringWithMaxLength(8), sizeof(name));
		AddName(name, &m_frames[i]);
		m_frames[i].Parse(this, p_parser);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00406de0
GolCamera* CutsceneDefinition::FindCamera(const LegoChar* p_name)
{
	for (LegoU32 i = 0; i < m_worldDatabaseCount; i++) {
		GolCamera* result = m_worldDatabases[i]->FindCamera(p_name);
		if (result) {
			return result;
		}
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00406e30
GolWorldEntity* CutsceneDefinition::FindModelEntity(const LegoChar* p_name)
{
	for (LegoU32 i = 0; i < m_worldDatabaseCount; i++) {
		GolWorldEntity* result = m_worldDatabases[i]->FindModelEntity(p_name);
		if (result) {
			return result;
		}
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00406e80
GolWorldEntity* CutsceneDefinition::FindJointedEntity(const LegoChar* p_name)
{
	for (LegoU32 i = 0; i < m_worldDatabaseCount; i++) {
		GolWorldEntity* result = m_worldDatabases[i]->FindAnimatedEntity(p_name);
		if (result) {
			return result;
		}
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00406ed0
GolWorldEntity* CutsceneDefinition::FindBspEntity(const LegoChar* p_name)
{
	for (LegoU32 i = 0; i < m_worldDatabaseCount; i++) {
		GolWorldEntity* result = m_worldDatabases[i]->FindCollidableEntity(p_name);
		if (result) {
			return result;
		}
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00406f20
GolWorldEntity* CutsceneDefinition::GetIndexedEntity(LegoU32 p_index, LegoU32 p_modelIndex)
{
	return m_worldDatabases[p_index]->GetWorldEntity(p_modelIndex);
}

// FUNCTION: LEGORACERS 0x00406f40
MabMaterialAnimation* CutsceneDefinition::GetMaterialAnimation(LegoU32 p_index, LegoU32 p_animationIndex)
{
	return m_worldDatabases[p_index]->GetMaterialAnimation(p_animationIndex);
}

// FUNCTION: LEGORACERS 0x00406f60
MabMaterialTrack* CutsceneDefinition::GetMaterialAnimationItem(
	LegoU32 p_index,
	LegoU32 p_animationIndex,
	LegoU32 p_itemIndex
)
{
	MabMaterialAnimation* materialAnimation = m_worldDatabases[p_index]->GetMaterialAnimation(p_animationIndex);
	return &materialAnimation->GetTracks()[p_itemIndex];
}

// FUNCTION: LEGORACERS 0x00406f90
LegoU32 CutsceneDefinition::SetCameraAspectRatios(LegoFloat p_scale)
{
	LegoU32 i = 0;
	LegoU32 result = m_worldDatabaseCount;
	if (result > 0) {
		do {
			m_worldDatabases[i]->SetCameraAspectRatios(p_scale);
			result = m_worldDatabaseCount;
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
	Clear();
}

// FUNCTION: LEGORACERS 0x00407060
void CutsceneDefinition::Frame::TransformEvent::Reset()
{
	m_position.m_x = 0.0f;
	m_position.m_y = 0.0f;
	m_position.m_z = 0.0f;
	m_direction.m_x = 1.0f;
	m_direction.m_y = 0.0f;
	m_direction.m_z = 0.0f;
	m_up.m_x = 0.0f;
	m_up.m_y = 0.0f;
	m_up.m_z = 1.0f;
}

// FUNCTION: LEGORACERS 0x00407090
LegoU32 CutsceneDefinition::Frame::TransformEvent::Parse(GolFileParser* p_parser)
{
	LegoU32 duration = 0;

	p_parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(CutsceneDefinition::c_tokenTransformBlock));
	::strncpy(m_name, p_parser->ReadStringWithMaxLength(8), sizeof(m_name));
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token;
	while ((token = p_parser->GetNextToken()) != GolFileParser::e_rightCurly) {
		switch (token) {
		case CutsceneDefinition::c_tokenStartFrame:
			m_startFrame = p_parser->ReadInteger();
			break;
		case CutsceneDefinition::c_tokenDuration:
			duration = p_parser->ReadInteger();
			break;
		case CutsceneDefinition::c_tokenLocation:
			m_position.m_x = p_parser->ReadFloat();
			m_position.m_y = p_parser->ReadFloat();
			m_position.m_z = p_parser->ReadFloat();
			break;
		case CutsceneDefinition::c_tokenOrientation:
			m_direction.m_x = p_parser->ReadFloat();
			m_direction.m_y = p_parser->ReadFloat();
			m_direction.m_z = p_parser->ReadFloat();
			m_up.m_x = p_parser->ReadFloat();
			m_up.m_y = p_parser->ReadFloat();
			m_up.m_z = p_parser->ReadFloat();
			break;
		default:
			break;
		}
	}

	m_endFrame = duration + m_startFrame;
	return m_endFrame;
}

// FUNCTION: LEGORACERS 0x004071a0
void CutsceneDefinition::Frame::TransformEvent::Clear()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004071b0
void CutsceneDefinition::Frame::TransformEvent::Begin(Frame* p_frame, CutsceneEventSink* p_event)
{
	Event::Begin(p_frame, p_event);
	if (p_event) {
		p_event->OnTransformStarted(p_frame, m_name, this);
	}
}

// FUNCTION: LEGORACERS 0x004071e0
void CutsceneDefinition::Frame::TransformEvent::End(Frame* p_frame, CutsceneEventSink* p_event)
{
	Event::End(p_frame, p_event);
	if (p_event) {
		p_event->OnTransformEnded(p_frame, m_name, this);
	}
}
