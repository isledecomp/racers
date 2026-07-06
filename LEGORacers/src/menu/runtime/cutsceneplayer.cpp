#include "menu/runtime/cutsceneplayer.h"

#include "audio/soundgroup.h"
#include "audio/soundinstance.h"
#include "audio/soundmanager.h"
#include "audio/spatialsoundinstance.h"
#include "audio/streamingsoundinstance.h"
#include "camera/golcamera.h"
#include "core/gol.h"
#include "font/golfont.h"
#include "font/golfonttable.h"
#include "golanimatedentity.h"
#include "golbinparser.h"
#include "golconstants.h"
#include "golerror.h"
#include "golfileparser.h"
#include "golmodelbase.h"
#include "golname.h"
#include "golscenenode.h"
#include "golstream.h"
#include "goltxtparser.h"
#include "golworldentity.h"
#include "image/golimage.h"
#include "mabmaterialanimation.h"
#include "mabmaterialtrack.h"
#include "material/golimagedefinitionlist.h"
#include "menu/menuanimationlist.h"
#include "menu/runtime/cutscenedefinition.h"
#include "menu/runtime/cutsceneparticle.h"
#include "render/gold3drenderdevice.h"
#include "render/golrenderdevice.h"
#include "render/rectangle.h"

#include <string.h>

DECOMP_SIZE_ASSERT(CutscenePlayer, 0x228)
DECOMP_SIZE_ASSERT(CutscenePlayer::CebTxtParser, 0x1fc)
DECOMP_SIZE_ASSERT(CutsceneEventSink, 0x04)
DECOMP_SIZE_ASSERT(CutsceneEvent, 0x14)
DECOMP_SIZE_ASSERT(CutsceneEventLink, 0x0c)
DECOMP_SIZE_ASSERT(CutsceneVisual, 0x58)
DECOMP_SIZE_ASSERT(CutsceneTextVisual, 0x70)

// FUNCTION: LEGORACERS 0x0049fd70
CutsceneEvent::CutsceneEvent()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0049fdb0
CutsceneEvent::~CutsceneEvent()
{
	// empty
}

// FUNCTION: LEGORACERS 0x0049fdc0
void CutsceneEvent::Reset()
{
	m_parsedEntity = 0;
	m_entity = 0;
	m_animatedEntity = 0;
	m_disabled = 0;
}

// FUNCTION: LEGORACERS 0x0049fdd0
void CutsceneEvent::StartAt(const GolVec3*, const GolVec3*, const GolVec3*)
{
	if (m_disabled == 0) {
		Start();
	}
}

// FUNCTION: LEGORACERS 0x0049fde0
void CutsceneEvent::StartOnBsp(GolWorldEntity*)
{
	if (m_disabled == 0) {
		Start();
	}
}

// FUNCTION: LEGORACERS 0x0049fdf0
void CutsceneEvent::StartOnModel(GolWorldEntity* p_arg)
{
	if (m_disabled == 0) {
		StartOnBsp(p_arg);
	}
}

// FUNCTION: LEGORACERS 0x0049fe10
void CutsceneEvent::StartOnJointed(GolWorldEntity* p_arg)
{
	if (m_disabled == 0) {
		StartOnModel(p_arg);
	}
}

// FUNCTION: LEGORACERS 0x0049fe30
void CutsceneEvent::GetJointPosition(undefined4 p_param1, GolVec3* p_param2)
{
	m_animatedEntity->ApplyPartAnimation(0);
	GolSceneNode* falconNode = m_animatedEntity->GetSceneNode(0);

	GolVec3 vec1;
	GolVec3 vec2;
	vec1.m_x = 0.0f;
	vec1.m_y = 0.0f;
	vec1.m_z = 0.0f;

	falconNode->TransformPointToWorld(p_param1, &vec1, &vec2);

	LegoFloat scale = m_animatedEntity->GetModel(0)->GetScale() * m_animatedEntity->GetScale();
	vec2.m_x *= scale;
	vec2.m_y *= scale;
	vec2.m_z *= scale;
	m_animatedEntity->LocalToWorld(vec2, p_param2);
}

// FUNCTION: LEGORACERS 0x0049fec0
void CutsceneEvent::GetJointAxes(undefined4 p_param1, GolVec3* p_param2, GolVec3* p_param3)
{
	m_animatedEntity->ApplyPartAnimation(0);
	GolSceneNode* falconNode = m_animatedEntity->GetSceneNode(0);

	GolVec3 vec1;
	GolVec3 vec2;
	vec1.m_x = 1.0f;
	vec1.m_y = 0.0f;
	vec1.m_z = 0.0f;

	falconNode->TransformVectorToWorld(p_param1, &vec1, &vec2);
	m_animatedEntity->RotateToWorld(vec2, p_param2);

	vec1.m_x = 0.0f;
	vec1.m_y = 0.0f;
	vec1.m_z = 1.0f;
	falconNode->TransformVectorToWorld(p_param1, &vec1, &vec2);
	m_animatedEntity->RotateToWorld(vec2, p_param3);
}

// FUNCTION: LEGORACERS 0x0049ff70
void CutsceneEvent::ParseCommonToken(
	GolFileParser* p_parser,
	CutscenePlayer* p_owner,
	GolFileParser::ParserTokenType p_token
)
{
	GolName name;
	LegoChar text[64];
	::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));

	switch (p_token) {
	case CutscenePlayer::CebTxtParser::e_jointedEntityName:
		m_parsedEntity = p_owner->FindJointedEntity(name);
		m_entity = m_parsedEntity;
		m_animatedEntity = static_cast<GolAnimatedEntity*>(m_parsedEntity);
		if (m_parsedEntity) {
			return;
		}
		::strncpy(text, name, sizeof(GolName));
		text[sizeof(GolName)] = '\0';
		::strcat(text, ": unable to find jointed model");
		GOL_FATALERROR_MESSAGE(text);
		break;
	case CutscenePlayer::CebTxtParser::e_modelEntityName:
		m_parsedEntity = p_owner->FindModelEntity(name);
		m_entity = m_parsedEntity;
		if (m_parsedEntity) {
			return;
		}
		::strncpy(text, name, sizeof(GolName));
		text[sizeof(GolName)] = '\0';
		::strcat(text, ": unable to find model");
		GOL_FATALERROR_MESSAGE(text);
		break;
	case CutscenePlayer::CebTxtParser::e_bspEntityName:
		m_parsedEntity = p_owner->FindBspEntity(name);
		m_entity = m_parsedEntity;
		if (m_parsedEntity) {
			return;
		}
		::strncpy(text, name, sizeof(GolName));
		text[sizeof(GolName)] = '\0';
		::strcat(text, ": unable to find bsp model");
		GOL_FATALERROR_MESSAGE(text);
		break;
	default:
		p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
		break;
	}
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void CutsceneEvent::Start()
{
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void CutsceneEvent::Stop()
{
}

// FUNCTION: LEGORACERS 0x004a00c0
void CutsceneEventLink::Bind(undefined4 p_isStart, CutsceneEvent* p_event)
{
	m_isStart = p_isStart;
	m_event = p_event;
}

// FUNCTION: LEGORACERS 0x004a00d0
void CutsceneEventLink::Fire()
{
	if (m_isStart) {
		m_event->Start();
	}
	else {
		m_event->Stop();
	}
}

// FUNCTION: LEGORACERS 0x004a00f0
void CutsceneEventLink::Fire(CutsceneDefinition::Frame::CameraEvent* p_payload)
{
	GolWorldEntity* value = p_payload->GetCamera()->m_trackedEntity;
	if (value) {
		if (m_isStart) {
			m_event->StartOnJointed(value);
		}
		else {
			m_event->Stop();
		}
	}
	else {
		Fire();
	}
}

// FUNCTION: LEGORACERS 0x004a0120
void CutsceneEventLink::Fire(CutsceneDefinition::Frame::ModelEvent* p_payload)
{
	if (p_payload->GetModelRefType() == 2) {
		if (m_isStart) {
			m_event->StartOnJointed(p_payload->GetEntity());
		}
		else {
			m_event->Stop();
		}
	}
	else if (p_payload->GetModelRefType() == 3 || p_payload->GetModelRefType() == 1) {
		if (m_isStart) {
			m_event->StartOnModel(p_payload->GetEntity());
		}
		else {
			m_event->Stop();
		}
	}
	else {
		if (m_isStart) {
			m_event->StartOnBsp(p_payload->GetEntity());
		}
		else {
			m_event->Stop();
		}
	}
}

// FUNCTION: LEGORACERS 0x004a0180
void CutsceneEventLink::Fire(CutsceneDefinition::Frame::TransformEvent* p_payload)
{
	GolVec3 vector0 = p_payload->GetPosition();
	GolVec3 vector1 = p_payload->GetDirection();
	GolVec3 vector2 = p_payload->GetUp();

	if (m_isStart) {
		m_event->StartAt(&vector0, &vector1, &vector2);
	}
	else {
		m_event->Stop();
	}
}

// FUNCTION: LEGORACERS 0x004a0200
void CutsceneEventLink::Fire(void*)
{
	Fire();
}

// FUNCTION: LEGORACERS 0x004a0210
CutscenePlayer::CutscenePlayer()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a03b0
CutscenePlayer::~CutscenePlayer()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x004a0530
void CutscenePlayer::Reset()
{
	m_golExport = NULL;
	m_renderer = 0;
	m_soundManager = NULL;
	m_definition = 0;
	m_menuAnimations = NULL;
	m_animationCount = 0;
	m_animations = NULL;
	m_materialAnimations = NULL;
	m_animationNames = NULL;
	m_stringTableCount = 0;
	m_stringTables = NULL;
	m_stringTableNames = NULL;
	m_soundGroupCount = 0;
	m_soundGroups = NULL;
	m_soundGroupNames = NULL;
	m_fontTableCount = 0;
	m_fontTables = NULL;
	m_fontTableNames = NULL;
	m_imageListCount = 0;
	m_imageLists = NULL;
	m_imageListNames = NULL;
	m_moveEventCount = 0;
	m_moveEvents = NULL;
	m_soundEventCount = 0;
	m_soundEvents = NULL;
	m_streamEventCount = 0;
	m_streamEvents = NULL;
	m_animEventCount = 0;
	m_animEvents = NULL;
	m_menuAnimEventCount = 0;
	m_menuAnimEvents = NULL;
	m_textVisualCount = 0;
	m_textVisuals = NULL;
	m_imageVisualCount = 0;
	m_imageVisuals = NULL;
	m_eventStartedCount = 0;
	m_eventStartedLinks = NULL;
	m_eventEndedCount = 0;
	m_eventEndedLinks = NULL;
	m_cameraStartedCount = 0;
	m_cameraStartedLinks = NULL;
	m_cameraEndedCount = 0;
	m_cameraEndedLinks = NULL;
	m_modelStartedCount = 0;
	m_modelStartedLinks = NULL;
	m_modelEndedCount = 0;
	m_modelEndedLinks = NULL;
	m_transformStartedCount = 0;
	m_transformStartedLinks = NULL;
	m_transformEndedCount = 0;
	m_transformEndedLinks = NULL;
	m_ambientStartedCount = 0;
	m_ambientStartedLinks = NULL;
	m_ambientEndedCount = 0;
	m_ambientEndedLinks = NULL;
	m_directionalStartedCount = 0;
	m_directionalStartedLinks = NULL;
	m_directionalEndedCount = 0;
	m_directionalEndedLinks = NULL;
	m_stringTable = NULL;
}

// FUNCTION: LEGORACERS 0x004a0680
LegoBool32 CutscenePlayer::HasFileWithSuffix(const LegoChar* p_fileName, const LegoChar* p_suffix)
{
	LegoU32 length = ::strlen(p_fileName) + ::strlen(p_suffix) + 1;
	LegoChar* path = new LegoChar[length];
	if (path == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	::strcpy(path, p_fileName);
	::strcat(path, p_suffix);

	LegoS32 result = GolStream::FindFile(path);
	delete[] path;

	return result == GolStream::e_ioSuccess;
}

// FUNCTION: LEGORACERS 0x004a0730
void CutscenePlayer::Load(
	GolExport* p_golExport,
	GolD3DRenderDevice* p_renderer,
	SoundManager* p_soundManager,
	CutsceneDefinition* p_definition,
	const LegoChar* p_fileName,
	undefined4 p_binary
)
{
	GolFileParser* parser;

	if (m_golExport) {
		Clear();
	}

	if (p_binary) {
		if (!HasFileWithSuffix(p_fileName, ".ceb")) {
			return;
		}
		parser = new GolBinParser();
		if (!parser) {
			GolFatalError(c_golErrorOutOfMemory, NULL, 0);
		}
		parser->SetSuffix(".ceb");
	}
	else {
		parser = new CebTxtParser();
		if (!parser) {
			GolFatalError(c_golErrorOutOfMemory, NULL, 0);
		}
		if (!HasFileWithSuffix(p_fileName, parser->GetSuffix())) {
			delete parser;
			return;
		}
	}

	m_golExport = p_golExport;
	m_renderer = p_renderer;
	m_definition = p_definition;
	m_soundManager = p_soundManager;

	p_soundManager->AddActiveSoundNode(&m_listener);
	parser->OpenFileForRead(p_fileName);
	GolFileParser::ParserTokenType token = parser->GetNextToken();
	while (token != GolFileParser::e_syntaxerror) {
		switch (token) {
		case CebTxtParser::e_animations:
			ParseAnimationNames(parser);
			break;
		case CebTxtParser::e_stringTables:
			ParseStringTableNames(parser);
			break;
		case CebTxtParser::e_soundGroups:
			ParseSoundGroupNames(parser);
			break;
		case CebTxtParser::e_fontTables:
			ParseFontTableNames(parser);
			break;
		case CebTxtParser::e_imageLists:
			ParseImageListNames(parser);
			break;
		case CebTxtParser::e_moveEvents:
			ParseMoveEvents(parser);
			break;
		case CebTxtParser::e_soundEvents:
			ParseSoundEvents(parser);
			break;
		case CebTxtParser::e_streamEvents:
			ParseStreamEvents(parser);
			break;
		case CebTxtParser::e_animationEvents:
			ParseAnimationEvents(parser);
			break;
		case CebTxtParser::e_menuAnimationEvents:
			ParseMenuAnimationEvents(parser);
			break;
		case CebTxtParser::e_textVisuals:
			ParseTextVisuals(parser);
			break;
		case CebTxtParser::e_imageVisuals:
			ParseImageVisuals(parser);
			break;
		case CebTxtParser::e_onEventStarted:
			ParseTriggerChannel(
				parser,
				CebTxtParser::e_onEventStarted,
				m_eventStartedCount,
				m_eventStartedLinks,
				m_eventStartedNames
			);
			break;
		case CebTxtParser::e_onEventEnded:
			ParseTriggerChannel(
				parser,
				CebTxtParser::e_onEventEnded,
				m_eventEndedCount,
				m_eventEndedLinks,
				m_eventEndedNames
			);
			break;
		case CebTxtParser::e_onCameraStarted:
			ParseTriggerChannel(
				parser,
				CebTxtParser::e_onCameraStarted,
				m_cameraStartedCount,
				m_cameraStartedLinks,
				m_cameraStartedNames
			);
			break;
		case CebTxtParser::e_onCameraEnded:
			ParseTriggerChannel(
				parser,
				CebTxtParser::e_onCameraEnded,
				m_cameraEndedCount,
				m_cameraEndedLinks,
				m_cameraEndedNames
			);
			break;
		case CebTxtParser::e_onModelStarted:
			ParseTriggerChannel(
				parser,
				CebTxtParser::e_onModelStarted,
				m_modelStartedCount,
				m_modelStartedLinks,
				m_modelStartedNames
			);
			break;
		case CebTxtParser::e_onModelEnded:
			ParseTriggerChannel(
				parser,
				CebTxtParser::e_onModelEnded,
				m_modelEndedCount,
				m_modelEndedLinks,
				m_modelEndedNames
			);
			break;
		case CebTxtParser::e_onTransformStarted:
			ParseTriggerChannel(
				parser,
				CebTxtParser::e_onTransformStarted,
				m_transformStartedCount,
				m_transformStartedLinks,
				m_transformStartedNames
			);
			break;
		case CebTxtParser::e_onTransformEnded:
			ParseTriggerChannel(
				parser,
				CebTxtParser::e_onTransformEnded,
				m_transformEndedCount,
				m_transformEndedLinks,
				m_transformEndedNames
			);
			break;
		case CebTxtParser::e_onAmbientStarted:
			ParseTriggerChannel(
				parser,
				CebTxtParser::e_onAmbientStarted,
				m_ambientStartedCount,
				m_ambientStartedLinks,
				m_ambientStartedNames
			);
			break;
		case CebTxtParser::e_onAmbientEnded:
			ParseTriggerChannel(
				parser,
				CebTxtParser::e_onAmbientEnded,
				m_ambientEndedCount,
				m_ambientEndedLinks,
				m_ambientEndedNames
			);
			break;
		case CebTxtParser::e_onDirectionalStarted:
			ParseTriggerChannel(
				parser,
				CebTxtParser::e_onDirectionalStarted,
				m_directionalStartedCount,
				m_directionalStartedLinks,
				m_directionalStartedNames
			);
			break;
		case CebTxtParser::e_onDirectionalEnded:
			ParseTriggerChannel(
				parser,
				CebTxtParser::e_onDirectionalEnded,
				m_directionalEndedCount,
				m_directionalEndedLinks,
				m_directionalEndedNames
			);
			break;
		default:
			parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}
		token = parser->GetNextToken();
	}

	parser->Dispose();
	delete parser;

	LoadAnimations(p_binary);
	LoadStringTables();
	LoadSoundGroups();
	LoadFontTables(p_binary);
	LoadImageLists(p_binary);
	RefreshTextVisuals();
	LoadImageVisuals();
}

// FUNCTION: LEGORACERS 0x004a0bf0
void CutscenePlayer::Clear()
{
	LegoU32 i;

	if (m_soundManager) {
		m_soundManager->RemoveActiveSoundNode(&m_listener);
	}

	if (m_soundGroups) {
		for (i = 0; i < m_soundGroupCount; i++) {
			if (m_soundGroups[i]) {
				m_soundManager->DestroySoundGroup(m_soundGroups[i]);
			}
		}
		delete[] m_soundGroups;
	}

	if (m_soundGroupNames) {
		delete m_soundGroupNames;
	}

	if (m_fontTables) {
		for (i = 0; i < m_fontTableCount; i++) {
			if (m_fontTables[i]) {
				m_golExport->DestroyFontTable(m_fontTables[i]);
			}
		}
		delete[] m_fontTables;
	}

	if (m_fontTableNames) {
		delete m_fontTableNames;
	}

	if (m_imageLists) {
		for (i = 0; i < m_imageListCount; i++) {
			if (m_imageLists[i]) {
				m_golExport->DestroyImageList(m_imageLists[i]);
			}
		}
		delete[] m_imageLists;
	}
	if (m_imageListNames) {
		delete[] m_imageListNames;
	}
	if (m_animations) {
		delete[] m_animations;
	}
	if (m_animationNames) {
		delete[] m_animationNames;
	}
	if (m_materialAnimations) {
		delete[] m_materialAnimations;
	}
	if (m_stringTables) {
		delete[] m_stringTables;
	}
	if (m_stringTableNames) {
		delete[] m_stringTableNames;
	}
	if (m_moveEvents) {
		delete[] m_moveEvents;
	}
	if (m_soundEvents) {
		delete[] m_soundEvents;
	}
	if (m_streamEvents) {
		delete[] m_streamEvents;
	}
	if (m_animEvents) {
		delete[] m_animEvents;
	}
	if (m_menuAnimations) {
		delete m_menuAnimations;
	}
	if (m_menuAnimEvents) {
		delete[] m_menuAnimEvents;
	}
	if (m_textVisuals) {
		delete[] m_textVisuals;
	}
	if (m_imageVisuals) {
		delete[] m_imageVisuals;
	}
	if (m_eventStartedLinks) {
		delete m_eventStartedLinks;
	}
	if (m_eventEndedLinks) {
		delete m_eventEndedLinks;
	}
	if (m_cameraStartedLinks) {
		delete m_cameraStartedLinks;
	}
	if (m_cameraEndedLinks) {
		delete m_cameraEndedLinks;
	}
	if (m_modelStartedLinks) {
		delete m_modelStartedLinks;
	}
	if (m_modelEndedLinks) {
		delete m_modelEndedLinks;
	}
	if (m_transformStartedLinks) {
		delete[] m_transformStartedLinks;
	}
	if (m_transformEndedLinks) {
		delete[] m_transformEndedLinks;
	}
	if (m_ambientStartedLinks) {
		delete[] m_ambientStartedLinks;
	}
	if (m_ambientEndedLinks) {
		delete[] m_ambientEndedLinks;
	}
	if (m_directionalStartedLinks) {
		delete[] m_directionalStartedLinks;
	}
	if (m_directionalEndedLinks) {
		delete[] m_directionalEndedLinks;
	}
	m_moveEventNames.Clear();
	m_soundEventNames.Clear();
	m_streamEventNames.Clear();
	m_animEventNames.Clear();
	m_menuAnimEventNames.Clear();
	m_textVisualNames.Clear();
	m_imageVisualNames.Clear();
	m_eventStartedNames.Clear();
	m_eventEndedNames.Clear();
	m_cameraStartedNames.Clear();
	m_cameraEndedNames.Clear();
	m_modelStartedNames.Clear();
	m_modelEndedNames.Clear();
	m_transformStartedNames.Clear();
	m_transformEndedNames.Clear();
	m_ambientStartedNames.Clear();
	m_ambientEndedNames.Clear();
	m_directionalStartedNames.Clear();
	m_directionalEndedNames.Clear();

	Reset();
}

// FUNCTION: LEGORACERS 0x004a0ff0
void CutscenePlayer::ParseAnimationNames(GolFileParser* p_parser)
{
	if (m_animations != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_animationCount = p_parser->ReadInteger();
	if (m_animationCount == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_animations = new CutsceneAnimation[m_animationCount];
	m_materialAnimations = new MabMaterialAnimation[m_animationCount];
	m_animationNames = new LegoChar[m_animationCount * 9];
	if (m_animations == NULL || m_materialAnimations == NULL || m_animationNames == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoU32 i = 0;

	if (i < m_animationCount) {
		LegoU32 offset = 0;

		do {
			::strncpy(&m_animationNames[offset], p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
			i++;
			m_animationNames[offset + sizeof(GolName)] = '\0';
			offset += 9;
		} while (i < m_animationCount);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a1240
void CutscenePlayer::LoadAnimations(undefined4 p_binary)
{
	if (m_animationNames != NULL) {
		for (LegoU32 i = 0; i < m_animationCount; i++) {
			m_materialAnimations[i].Load(m_renderer, &m_animationNames[i * 9], p_binary);
			m_animations[i]
				.Load(3, m_golExport, m_renderer, &m_materialAnimations[i], &m_animationNames[i * 9], p_binary);
		}

		delete[] m_animationNames;
		m_animationNames = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004a12e0
void CutscenePlayer::ParseStringTableNames(GolFileParser* p_parser)
{
	if (m_stringTables != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_stringTableCount = p_parser->ReadInteger();
	if (m_stringTableCount == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_stringTables = new GolStringTable[m_stringTableCount];
	m_stringTableNames = new LegoChar[m_stringTableCount * 13];
	if (m_stringTables == NULL || m_stringTableNames == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_stringTableCount; i++) {
		::strncpy(&m_stringTableNames[i * 13], p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
		m_stringTableNames[i * 13 + sizeof(GolName)] = '\0';
		::strcat(&m_stringTableNames[i * 13], ".srf");

		m_stringTables[i].UseOwnedBuffers();
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a14e0
void CutscenePlayer::LoadStringTables()
{
	if (m_stringTableNames != NULL) {
		LegoU32 i = 0;

		if (i < m_stringTableCount) {
			LegoU32 fileNameOffset = 0;

			do {
				m_stringTables[i].UseOwnedBuffers();

				if (!m_stringTables[i].Load(&m_stringTableNames[fileNameOffset])) {
					LegoChar text[48];
					::strcpy(text, "Unable to open: ");
					::strcat(text, &m_stringTableNames[fileNameOffset]);
					GOL_FATALERROR_MESSAGE(text);
				}

				i++;
				fileNameOffset += 13;
			} while (i < m_stringTableCount);
		}

		delete[] m_stringTableNames;
		m_stringTableNames = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004a15e0
void CutscenePlayer::ParseSoundGroupNames(GolFileParser* p_parser)
{
	if (m_soundGroups != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_soundGroupCount = p_parser->ReadInteger();
	if (m_soundGroupCount == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_soundGroups = new SoundGroup*[m_soundGroupCount];
	if (m_soundGroups == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_soundGroupNames = new LegoChar[m_soundGroupCount * 9];
	if (m_soundGroupNames == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoU32 i = 0;

	if (i < m_soundGroupCount) {
		LegoU32 offset = 0;

		do {
			::strncpy(&m_soundGroupNames[offset], p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
			m_soundGroupNames[offset + sizeof(GolName)] = '\0';

			SoundGroup* soundGroup = m_soundManager->CreateSoundGroup();
			i++;
			offset += 9;
			m_soundGroups[i - 1] = soundGroup;
		} while (i < m_soundGroupCount);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a16f0
void CutscenePlayer::LoadSoundGroups()
{
	if (m_soundGroupNames != NULL) {
		for (LegoU32 i = 0; i < m_soundGroupCount; i++) {
			m_soundGroups[i]->Load(&m_soundGroupNames[i * 9]);
		}

		delete[] m_soundGroupNames;
		m_soundGroupNames = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004a1760
void CutscenePlayer::ParseFontTableNames(GolFileParser* p_parser)
{
	if (m_fontTables != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_fontTableCount = p_parser->ReadInteger();
	if (m_fontTableCount == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_fontTables = new GolFontTable*[m_fontTableCount];
	m_fontTableNames = new LegoChar[m_fontTableCount * 9];
	if (m_fontTables == NULL || m_fontTableNames == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoU32 i = 0;

	if (i < m_fontTableCount) {
		LegoU32 offset = 0;

		do {
			::strncpy(&m_fontTableNames[offset], p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
			i++;
			m_fontTableNames[offset + sizeof(GolName)] = '\0';
			offset += 9;
		} while (i < m_fontTableCount);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a1850
void CutscenePlayer::LoadFontTables(undefined4 p_binary)
{
	if (m_fontTableNames != NULL) {
		for (LegoU32 i = 0; i < m_fontTableCount; i++) {
			m_fontTables[i] = m_golExport->CreateFontTable();
			m_fontTables[i]->LoadFontDefinitions(m_renderer, &m_fontTableNames[i * 9], p_binary);
		}

		delete[] m_fontTableNames;
		m_fontTableNames = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004a18d0
void CutscenePlayer::ParseImageListNames(GolFileParser* p_parser)
{
	if (m_imageLists != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_imageListCount = p_parser->ReadInteger();
	if (m_imageListCount == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_imageLists = new GolImageDefinitionList*[m_imageListCount];
	m_imageListNames = new LegoChar[m_imageListCount * 9];
	if (m_imageLists == NULL || m_imageListNames == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoU32 i = 0;

	if (i < m_imageListCount) {
		LegoU32 offset = 0;

		do {
			::strncpy(&m_imageListNames[offset], p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
			i++;
			m_imageListNames[offset + sizeof(GolName)] = '\0';
			offset += 9;
		} while (i < m_imageListCount);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a19c0
void CutscenePlayer::LoadImageLists(undefined4 p_binary)
{
	if (m_imageListNames != NULL) {
		for (LegoU32 i = 0; i < m_imageListCount; i++) {
			m_imageLists[i] = m_golExport->CreateImageList();
			m_imageLists[i]->LoadImageDefinitions(m_renderer, &m_imageListNames[i * 9], p_binary);
		}

		delete[] m_imageListNames;
		m_imageListNames = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004a1a40
void CutscenePlayer::ParseMoveEvents(GolFileParser* p_parser)
{
	if (m_moveEvents != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_moveEventCount = p_parser->ReadInteger();
	if (m_moveEventCount == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_moveEventNames.Allocate(m_moveEventCount);
	m_moveEvents = new CutsceneColorEvent[m_moveEventCount];
	if (m_moveEvents == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_moveEventCount; i++) {
		GolName name;

		p_parser->AssertNextTokenIs(
			static_cast<GolFileParser::ParserTokenType>(CutscenePlayer::CebTxtParser::e_moveEvents)
		);
		::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
		m_moveEventNames.AddName(name, &m_moveEvents[i]);
		m_moveEvents[i].Parse(p_parser, this);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a1c00
void CutscenePlayer::ParseSoundEvents(GolFileParser* p_parser)
{
	if (m_soundEvents != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_soundEventCount = p_parser->ReadInteger();
	if (m_soundEventCount == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_soundEventNames.Allocate(m_soundEventCount);
	m_soundEvents = new CutsceneSoundEvent[m_soundEventCount];
	if (m_soundEvents == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_soundEventCount; i++) {
		GolName name;

		p_parser->AssertNextTokenIs(
			static_cast<GolFileParser::ParserTokenType>(CutscenePlayer::CebTxtParser::e_soundEvents)
		);
		::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
		m_soundEventNames.AddName(name, &m_soundEvents[i]);
		m_soundEvents[i].Parse(p_parser, this);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a1dc0
void CutscenePlayer::ParseStreamEvents(GolFileParser* p_parser)
{
	if (m_streamEvents != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_streamEventCount = p_parser->ReadInteger();
	if (m_streamEventCount == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_streamEventNames.Allocate(m_streamEventCount);
	m_streamEvents = new CutsceneStreamingSoundEvent[m_streamEventCount];
	if (m_streamEvents == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_streamEventCount; i++) {
		GolName name;

		p_parser->AssertNextTokenIs(
			static_cast<GolFileParser::ParserTokenType>(CutscenePlayer::CebTxtParser::e_streamEvents)
		);
		::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
		m_streamEventNames.AddName(name, &m_streamEvents[i]);
		m_streamEvents[i].Parse(p_parser, this);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a1f80
void CutscenePlayer::ParseAnimationEvents(GolFileParser* p_parser)
{
	if (m_animEvents != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_animEventCount = p_parser->ReadInteger();
	if (m_animEventCount == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_animEventNames.Allocate(m_animEventCount);
	m_animEvents = new CutsceneAnimationEvent[m_animEventCount];
	if (m_animEvents == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_animEventCount; i++) {
		GolName name;

		p_parser->AssertNextTokenIs(
			static_cast<GolFileParser::ParserTokenType>(CutscenePlayer::CebTxtParser::e_animationEvents)
		);
		::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
		m_animEventNames.AddName(name, &m_animEvents[i]);
		m_animEvents[i].Parse(p_parser, this);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a20f0
void CutscenePlayer::ParseMenuAnimationEvents(GolFileParser* p_parser)
{
	if (m_menuAnimEvents != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_menuAnimEventCount = p_parser->ReadInteger();
	if (m_menuAnimEventCount == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_menuAnimEventNames.Allocate(m_menuAnimEventCount);
	m_menuAnimEvents = new CutsceneMenuAnimationEvent[m_menuAnimEventCount];
	m_menuAnimations = new MenuAnimationList();
	if (m_menuAnimEvents == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	if (m_menuAnimations == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_menuAnimations->Allocate(2);

	for (LegoU32 i = 0; i < m_menuAnimEventCount; i++) {
		GolName name;

		p_parser->AssertNextTokenIs(
			static_cast<GolFileParser::ParserTokenType>(CutscenePlayer::CebTxtParser::e_menuAnimationEvents)
		);
		::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
		m_menuAnimEventNames.AddName(name, &m_menuAnimEvents[i]);
		m_menuAnimEvents[i].Parse(p_parser, this, m_menuAnimations, m_renderer);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a2310
void CutscenePlayer::ParseTextVisuals(GolFileParser* p_parser)
{
	if (m_textVisuals != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_textVisualCount = p_parser->ReadInteger();
	if (m_textVisualCount == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_textVisualNames.Allocate(m_textVisualCount);
	m_textVisuals = new CutsceneTextVisual[m_textVisualCount];
	if (m_textVisuals == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_textVisualCount; i++) {
		GolName name;

		p_parser->AssertNextTokenIs(
			static_cast<GolFileParser::ParserTokenType>(CutscenePlayer::CebTxtParser::e_textVisuals)
		);
		::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
		m_textVisualNames.AddName(name, &m_textVisuals[i]);
		m_textVisuals[i].Parse(p_parser, this, m_renderer);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a24e0
void CutscenePlayer::RefreshTextVisuals()
{
	for (LegoU32 i = 0; i < m_textVisualCount; i++) {
		m_textVisuals[i].RefreshString(this, m_renderer);
	}
}

// FUNCTION: LEGORACERS 0x004a2520
void CutscenePlayer::ParseImageVisuals(GolFileParser* p_parser)
{
	if (m_imageVisuals != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_imageVisualCount = p_parser->ReadInteger();
	if (m_imageVisualCount == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_imageVisualNames.Allocate(m_imageVisualCount);
	m_imageVisuals = new CutsceneImageVisual[m_imageVisualCount];
	if (m_imageVisuals == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_imageVisualCount; i++) {
		GolName name;

		p_parser->AssertNextTokenIs(
			static_cast<GolFileParser::ParserTokenType>(CutscenePlayer::CebTxtParser::e_imageVisuals)
		);
		::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
		m_imageVisualNames.AddName(name, &m_imageVisuals[i]);
		m_imageVisuals[i].Parse(p_parser, this, m_renderer);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a26f0
void CutscenePlayer::LoadImageVisuals()
{
	for (LegoU32 i = 0; i < m_imageVisualCount; i++) {
		m_imageVisuals[i].ResolveImage(m_renderer);
	}
}

// FUNCTION: LEGORACERS 0x004a2730
void CutscenePlayer::ParseTriggerChannel(
	GolFileParser* p_parser,
	LegoU32 p_token,
	undefined4& p_count,
	CutsceneEventLink*& p_links,
	GolNameTable& p_names
)
{
	undefined4 mode = 0;
	CutsceneEvent* event = NULL;

	if (p_links != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	LegoU32 count = p_parser->ReadInteger();
	if (count == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	p_count = count;
	p_names.Allocate(count);

	CutsceneEventLink* links = new CutsceneEventLink[count];
	if (links == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	p_links = links;

	CutsceneEventLink* link = links;
	CutsceneEventLink* end = links + count;
	while (link < end) {
		GolName name;

		p_parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(p_token));
		::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));

		CutsceneEventLink* existing = static_cast<CutsceneEventLink*>(p_names.GetName(name));
		if (existing != NULL) {
			link->SetNext(existing->GetNext());
			existing->SetNext(link);
		}
		else {
			p_names.AddName(name, link);
		}

		p_parser->ReadLeftCurly();

		GolFileParser::ParserTokenType targetToken = p_parser->GetNextToken();
		GolFileParser::ParserTokenType modeToken = p_parser->GetNextToken();
		if (modeToken == CutscenePlayer::CebTxtParser::e_imageAttached) {
			mode = 1;
		}
		else if (modeToken == CutscenePlayer::CebTxtParser::e_imageDetached) {
			mode = 0;
		}
		else {
			p_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName targetName;
		::strncpy(targetName, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));

		switch (targetToken) {
		case CebTxtParser::e_moveEvents:
			event = static_cast<CutsceneEvent*>(m_moveEventNames.GetName(targetName));
			break;
		case CebTxtParser::e_soundEvents:
			event = static_cast<CutsceneEvent*>(m_soundEventNames.GetName(targetName));
			break;
		case CebTxtParser::e_streamEvents:
			event = static_cast<CutsceneEvent*>(m_streamEventNames.GetName(targetName));
			break;
		case CebTxtParser::e_animationEvents:
			event = static_cast<CutsceneEvent*>(m_animEventNames.GetName(targetName));
			break;
		case CebTxtParser::e_menuAnimationEvents:
			event = static_cast<CutsceneEvent*>(m_menuAnimEventNames.GetName(targetName));
			break;
		case CebTxtParser::e_textVisuals:
			event = static_cast<CutsceneEvent*>(m_textVisualNames.GetName(targetName));
			break;
		case CebTxtParser::e_imageVisuals:
			event = static_cast<CutsceneEvent*>(m_imageVisualNames.GetName(targetName));
			break;
		default:
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}

		if (event == NULL) {
			LegoChar text[64];
			::strncpy(text, targetName, sizeof(GolName));
			text[sizeof(GolName)] = '\0';
			::strcat(text, ": Unable to find effect");
			GOL_FATALERROR_MESSAGE(text);
		}

		link->Bind(mode, event);
		p_parser->ReadRightCurly();
		link++;
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a2ac0
void CutscenePlayer::OnEventStarted(void*, void* p_name, void*)
{
	if (m_eventStartedNames.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_eventStartedNames.GetName(static_cast<const LegoChar*>(p_name)));
		while (link != NULL) {
			link->Fire();
			link = link->GetNext();
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2b00
void CutscenePlayer::OnEventEnded(void*, void* p_name, void*)
{
	if (m_eventEndedNames.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_eventEndedNames.GetName(static_cast<const LegoChar*>(p_name)));
		while (link != NULL) {
			link->Fire();
			link = link->GetNext();
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2b40
void CutscenePlayer::OnCameraStarted(void*, void* p_name, void* p_payload)
{
	if (m_cameraStartedNames.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_cameraStartedNames.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			CutsceneDefinition::Frame::CameraEvent* payload =
				static_cast<CutsceneDefinition::Frame::CameraEvent*>(p_payload);

			while (link != NULL) {
				link->Fire(payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2b80
void CutscenePlayer::OnCameraEnded(void*, void* p_name, void* p_payload)
{
	if (m_cameraEndedNames.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_cameraEndedNames.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			CutsceneDefinition::Frame::CameraEvent* payload =
				static_cast<CutsceneDefinition::Frame::CameraEvent*>(p_payload);

			while (link != NULL) {
				link->Fire(payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2bc0
void CutscenePlayer::OnModelStarted(void*, void* p_name, void* p_payload)
{
	if (m_modelStartedNames.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_modelStartedNames.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			CutsceneDefinition::Frame::ModelEvent* payload =
				static_cast<CutsceneDefinition::Frame::ModelEvent*>(p_payload);

			while (link != NULL) {
				link->Fire(payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2c00
void CutscenePlayer::OnModelEnded(void*, void* p_name, void* p_payload)
{
	if (m_modelEndedNames.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_modelEndedNames.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			CutsceneDefinition::Frame::ModelEvent* payload =
				static_cast<CutsceneDefinition::Frame::ModelEvent*>(p_payload);

			while (link != NULL) {
				link->Fire(payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2c40
void CutscenePlayer::OnTransformStarted(void*, void* p_name, void* p_payload)
{
	if (m_transformStartedNames.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_transformStartedNames.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			CutsceneDefinition::Frame::TransformEvent* payload =
				static_cast<CutsceneDefinition::Frame::TransformEvent*>(p_payload);

			while (link != NULL) {
				link->Fire(payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2c80
void CutscenePlayer::OnTransformEnded(void*, void* p_name, void* p_payload)
{
	if (m_transformEndedNames.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_transformEndedNames.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			CutsceneDefinition::Frame::TransformEvent* payload =
				static_cast<CutsceneDefinition::Frame::TransformEvent*>(p_payload);

			while (link != NULL) {
				link->Fire(payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2cc0
void CutscenePlayer::OnAmbientLightStarted(void*, void* p_name, void* p_payload)
{
	if (m_ambientStartedNames.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_ambientStartedNames.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			while (link != NULL) {
				link->Fire(p_payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2d00
void CutscenePlayer::OnAmbientLightEnded(void*, void* p_name, void* p_payload)
{
	if (m_ambientEndedNames.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_ambientEndedNames.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			while (link != NULL) {
				link->Fire(p_payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2d40
void CutscenePlayer::OnDirectionalLightStarted(void*, void* p_name, void* p_payload)
{
	if (m_directionalStartedNames.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_directionalStartedNames.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			while (link != NULL) {
				link->Fire(p_payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2d80
void CutscenePlayer::OnDirectionalLightEnded(void*, void* p_name, void* p_payload)
{
	if (m_directionalEndedNames.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_directionalEndedNames.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			while (link != NULL) {
				link->Fire(p_payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2dc0
void CutscenePlayer::Update(LegoU32 p_elapsedMs)
{
	if (m_golExport != NULL) {
		LegoFloat elapsedSeconds = static_cast<LegoS32>(p_elapsedMs) * 0.001f;
		LegoU32 i;

		for (i = 0; i < m_moveEventCount; i++) {
			m_moveEvents[i].Update(elapsedSeconds);
		}

		for (i = 0; i < m_soundEventCount; i++) {
			m_soundEvents[i].Update();
		}

		for (i = 0; i < m_streamEventCount; i++) {
			m_streamEvents[i].Update();
		}

		for (i = 0; i < m_animationCount; i++) {
			CutsceneAnimation* entries = m_animations;
			entries[i].Update(p_elapsedMs);
		}

		for (i = 0; i < m_textVisualCount; i++) {
			m_textVisuals[i].Update(elapsedSeconds);
		}

		for (i = 0; i < m_imageVisualCount; i++) {
			m_imageVisuals[i].Update(elapsedSeconds);
		}

		for (i = 0; i < m_animEventCount; i++) {
			m_animEvents[i].Update(p_elapsedMs);
		}

		if (m_menuAnimations != NULL) {
			m_menuAnimations->Update(p_elapsedMs);
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2f30
void CutscenePlayer::Draw(GolD3DRenderDevice* p_renderer)
{
	if (m_golExport != NULL) {
		UpdateListener(p_renderer->GetCurrentCamera());

		for (LegoU32 i = 0; i < m_animationCount; i++) {
			m_animations[i].Draw(p_renderer);
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2f80
void CutscenePlayer::UpdateListener(GolCamera* p_lens)
{
	GolVec3 position;
	GolVec3 right;
	GolVec3 forward;

	p_lens->GetTransform()->GetPosition(&position);
	p_lens->GetTransform()->GetRight(&right);
	p_lens->GetTransform()->GetForward(&forward);

	SoundNode* node = &m_listener;

	node->m_position.m_x = position.m_x;
	node->m_position.m_y = position.m_y;
	node->m_position.m_z = position.m_z;
	node->m_unk0x44 = 1;

	forward.m_x = -forward.m_x;
	forward.m_y = -forward.m_y;
	forward.m_z = -forward.m_z;

	node->m_right.m_x = right.m_x;
	node->m_right.m_y = right.m_y;
	node->m_right.m_z = right.m_z;
	node->m_forward.m_x = forward.m_x;
	node->m_forward.m_y = forward.m_y;
	node->m_forward.m_z = forward.m_z;

	node->m_orientation.m_x = (node->m_forward.m_y * node->m_right.m_z) - (node->m_forward.m_z * node->m_right.m_y);
	node->m_orientation.m_y = (node->m_forward.m_z * node->m_right.m_x) - (node->m_right.m_z * node->m_forward.m_x);
	node->m_orientation.m_z = (node->m_right.m_y * node->m_forward.m_x) - (node->m_forward.m_y * node->m_right.m_x);

	GolVec3 orientation;
	orientation.m_x = node->m_orientation.m_x;
	orientation.m_y = node->m_orientation.m_y;
	orientation.m_z = node->m_orientation.m_z;
	GolMath::NormalizeVector3(orientation, &orientation);
	node->m_orientation.m_x = orientation.m_x;
	node->m_orientation.m_y = orientation.m_y;
	node->m_orientation.m_z = orientation.m_z;

	node->m_unk0x44 = 1;
}

// FUNCTION: LEGORACERS 0x004a3070
void CutscenePlayer::DrawTransparent(GolD3DRenderDevice* p_renderer)
{
	if (m_golExport != NULL) {
		for (LegoU32 i = 0; i < m_animationCount; i++) {
			m_animations[i].DrawTransparent(p_renderer);
		}
	}
}

// FUNCTION: LEGORACERS 0x004a30b0
void CutscenePlayer::DrawOverlay(GolD3DRenderDevice* p_renderer)
{
	if (m_golExport != NULL) {
		p_renderer->DisableZBuffer(FALSE);

		LegoU32 i;
		for (i = 0; i < m_imageVisualCount; i++) {
			m_imageVisuals[i].Draw(p_renderer);
		}

		for (i = 0; i < m_textVisualCount; i++) {
			m_textVisuals[i].Draw(p_renderer);
		}

		if (m_menuAnimations != NULL) {
			m_menuAnimations->Draw(p_renderer);
		}

		p_renderer->EnableZBuffer();
	}
}

// FUNCTION: LEGORACERS 0x004a3150
void CutscenePlayer::StopAll()
{
	LegoU32 i;

	for (i = 0; i < m_moveEventCount; i++) {
		m_moveEvents[i].Stop();
	}

	for (i = 0; i < m_soundEventCount; i++) {
		m_soundEvents[i].Stop();
	}

	for (i = 0; i < m_streamEventCount; i++) {
		m_streamEvents[i].Stop();
	}

	for (i = 0; i < m_textVisualCount; i++) {
		m_textVisuals[i].Stop();
	}

	for (i = 0; i < m_imageVisualCount; i++) {
		m_imageVisuals[i].Stop();
	}
}

// FUNCTION: LEGORACERS 0x004a3230
GolWorldEntity* CutscenePlayer::FindModelEntity(const LegoChar* p_name)
{
	return m_definition->FindModelEntity(p_name);
}

// FUNCTION: LEGORACERS 0x004a3240
GolWorldEntity* CutscenePlayer::FindJointedEntity(const LegoChar* p_name)
{
	return m_definition->FindJointedEntity(p_name);
}

// FUNCTION: LEGORACERS 0x004a3250
GolWorldEntity* CutscenePlayer::FindBspEntity(const LegoChar* p_name)
{
	return m_definition->FindBspEntity(p_name);
}

// FUNCTION: LEGORACERS 0x004a3260
GolStringTable* CutscenePlayer::GetStringTableByIndex(LegoU32 p_index)
{
	if (p_index == 0 && m_stringTable != NULL) {
		return m_stringTable;
	}

	return &m_stringTables[p_index];
}

// FUNCTION: LEGORACERS 0x004a00b0 FOLDED
CutsceneEventLink::CutsceneEventLink()
{
	m_isStart = 0;
	m_event = NULL;
	m_next = NULL;
}
