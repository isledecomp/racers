#include "race/hazards/grabberhazard.h"

#include "decomp.h"
#include "golfileparser.h"
#include "golmath.h"
#include "golmodelbase.h"
#include "golscenenode.h"
#include "goltransformbase.h"
#include "race/hazardmanager.h"
#include "race/hazards/hazardcontext.h"
#include "race/racer/racer.h"
#include "types.h"
#include "world/golworlddatabase.h"

#include <string.h>

DECOMP_SIZE_ASSERT(GrabberHazard, 0x60)

// GLOBAL: LEGORACERS 0x004b4514
extern const LegoFloat g_grabberTriggerRadius = 45.0f;

// FUNCTION: LEGORACERS 0x0048dd20
GrabberHazard::GrabberHazard()
{
	ClearFields();
}

// FUNCTION: LEGORACERS 0x0048dda0
GrabberHazard::~GrabberHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048ddf0
LegoS32 GrabberHazard::ClearFields()
{
	m_entity = NULL;
	m_racer = NULL;
	m_grabFrameLow = 0.0f;
	m_grabFrameHigh = 0.0f;
	m_pullStrength = 0.0f;
	m_collisionEvent = NULL;
	m_grabState = 0;
	m_grabTimerMs = 0;

	return 0;
}

// FUNCTION: LEGORACERS 0x0048de10
void GrabberHazard::Load(HazardContext* p_context, GolFileParser* p_parser)
{
	if (m_state) {
		Reset();
	}

	GolName entityName;
	entityName[0] = '\0';
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token;
	while ((token = p_parser->GetNextToken()) != GolFileParser::e_rightCurly) {
		switch (token) {
		case HazardManager::HzbTxtParser::e_trigger:
			m_triggerId = p_parser->ReadInteger();
			break;
		case HazardManager::HzbTxtParser::e_entity:
			::strncpy(entityName, p_parser->ReadStringWithMaxLength(sizeof(entityName)), sizeof(entityName));
			m_pullStrength = p_parser->ReadFloat();
			m_grabFrameLow = p_parser->ReadFloat();
			m_grabFrameHigh = p_parser->ReadFloat();
			break;
		default:
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}
	}

	m_eventQueue = p_context->GetEventQueue();
	m_entity = p_context->GetTrackDatabase()->FindAnimatedEntity(entityName);
	m_trigger.SetBoundsRadius(g_grabberTriggerRadius);
	m_state = c_stateLoaded;
}

// FUNCTION: LEGORACERS 0x0048df00
LegoS32 GrabberHazard::Reset()
{
	OnDeactivate(NULL);
	ClearFields();
	return Hazard::Reset();
}

// FUNCTION: LEGORACERS 0x0048df20
void GrabberHazard::OnActivate(void*)
{
	LegoEventQueue::Descriptor descriptor;
	descriptor.m_type = LegoEventQueue::Descriptor::c_typeRacerTrigger;
	descriptor.m_flags = 1;
	descriptor.m_maxFireCount = 0;
	descriptor.m_hitThreshold = 0;
	descriptor.m_worldEntity = &m_trigger;

	m_collisionEvent = m_eventQueue->AllocateEvent(this, &descriptor);
	m_grabState = 0;
	m_grabTimerMs = 0;
	m_state = c_stateActive;
}

// FUNCTION: LEGORACERS 0x0048df70
void GrabberHazard::OnDeactivate(void*)
{
	ReleaseRacer();
	if (m_collisionEvent) {
		m_collisionEvent->m_active = 0;
		m_collisionEvent = NULL;
	}

	m_state = c_stateLoaded;
	m_grabState = 0;
	m_grabTimerMs = 0;
}

// FUNCTION: LEGORACERS 0x0048dfa0
void GrabberHazard::Update(undefined4 p_elapsedMs)
{
	if (m_state == c_stateLoaded) {
		return;
	}

	LegoU32 elapsedMs = p_elapsedMs;
	Hazard::Update(p_elapsedMs);

	GolVec3 position;
	GetGrabPosition(&position);
	m_trigger.SetBoundsCenter(position);

	if (m_stateMs) {
		if (elapsedMs >= m_stateMs) {
			m_stateMs = 0;
			ReleaseRacer();
			m_grabState = 0;
			m_grabTimerMs = 0;
		}
		else {
			m_stateMs -= elapsedMs;
		}
	}

	if (m_grabTimerMs) {
		if (elapsedMs >= m_grabTimerMs) {
			m_grabTimerMs = 0;
			switch (m_grabState) {
			case c_stateOne:
				ReleaseRacer();
				m_stateMs = 0;
				m_grabState = c_stateTwo;
				m_grabTimerMs = c_timerMs;
				break;
			case c_stateTwo:
				m_grabState = 0;
				return;
			default:
				return;
			}
		}
		else {
			m_grabTimerMs -= elapsedMs;
		}
	}
}

// FUNCTION: LEGORACERS 0x0048e050
void GrabberHazard::OnEvent(LegoEventQueue::CallbackData* p_data)
{
	LegoFloat frame = m_entity->GetActiveValue();
	if (m_grabState == c_stateTwo) {
		return;
	}

	Racer* racer = static_cast<Racer*>(p_data->m_data);
	RacerPhysics* physics = &racer->m_physics;
	if ((frame <= m_grabFrameLow || frame >= m_grabFrameHigh) && !(racer->m_flags & Racer::c_flagShielded)) {
		if (m_racer == NULL || m_racer == racer) {
			if (m_racer == NULL) {
				m_grabState = c_stateOne;
				m_grabTimerMs = c_timerMs;
			}
		}
		else {
			return;
		}

		m_racer = racer;
		racer->m_flags |= Racer::c_flagGrabbed;

		Racer* currentRacer = m_racer;
		if (currentRacer->m_physics.m_routeMode) {
			LegoU32 flags = currentRacer->m_physics.m_flags;
			currentRacer->m_physics.m_routeBaseSpeed = -0.4f;
			if (!(flags & RacerPhysics::c_flagRoutePushed)) {
				currentRacer->m_physics.m_routeTargetSpeed = -0.4f;
				m_stateMs = c_restoreTimerMs;
				return;
			}
		}
		else {
			GolVec3 position;
			GetGrabPosition(&position);

			GolVec3 racerPosition;
			CarVisuals* racerField = &m_racer->m_visuals;
			racerField->m_carEntity->GetPosition(&racerPosition);

			GolVec3 force;
			force.m_x = position.m_x - racerPosition.m_x;
			force.m_y = position.m_y - racerPosition.m_y;
			force.m_z = 0.0f;
			GolMath::NormalizeVector3(force, &force);
			LegoFloat scale = m_pullStrength;
			force.m_x = scale * force.m_x;
			force.m_y = force.m_y * scale;
			force.m_z = force.m_z * scale;
			physics->StartExternalForce1(&force);
		}

		m_stateMs = c_restoreTimerMs;
	}
}

// FUNCTION: LEGORACERS 0x0048e1c0
void GrabberHazard::GetGrabPosition(GolVec3* p_position)
{
	LegoFloat scale = m_entity->GetModel(0)->GetScale() * m_entity->GetScale();
	GolSceneNode* node = m_entity->GetSceneNode(0);
	GolTransformBase* transform = node->GetTransform(0);

	GolVec3 localPosition;
	transform->GetPosition(&localPosition);
	localPosition.m_x *= scale;
	localPosition.m_y *= scale;
	localPosition.m_z *= scale;

	m_entity->LocalToWorld(localPosition, p_position);
}

// FUNCTION: LEGORACERS 0x0048e230
void GrabberHazard::ReleaseRacer()
{
	if (m_racer) {
		m_racer->m_physics.EndExternalForce1();
		m_racer->m_flags &= ~Racer::c_flagGrabbed;

		Racer* racer = m_racer;
		if (racer->m_physics.m_routeMode) {
			LegoU32 flags = racer->m_physics.m_flags;
			LegoFloat value = 1.0f;
			racer->m_physics.m_routeBaseSpeed = value;
			if (!(flags & RacerPhysics::c_flagRoutePushed)) {
				racer->m_physics.m_routeTargetSpeed = value;
			}
		}

		m_racer = NULL;
	}
}
