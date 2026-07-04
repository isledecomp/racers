#include "race/hazards/launcherhazard.h"

#include "decomp.h"
#include "golfileparser.h"
#include "golmath.h"
#include "race/hazardmanager.h"
#include "race/hazards/hazardcontext.h"
#include "race/powerups/powerupprojectile.h"
#include "race/powerups/racepowerupmanager.h"
#include "race/raceeventtable.h"
#include "render/gold3drenderdevice.h"
#include "types.h"

#include <float.h>

DECOMP_SIZE_ASSERT(LauncherHazard, 0x124)

// GLOBAL: LEGORACERS 0x004b46b4
extern const LegoFloat g_launcherMaxDistanceSquared = FLT_MAX;

// GLOBAL: LEGORACERS 0x004c22fc
extern const ColorRGBA g_launcherTrailColor = {0x32, 0x32, 0x32, 0x64};

// FUNCTION: LEGORACERS 0x0048f6e0
LauncherHazard::LauncherHazard()
{
	ClearFields();
}

// FUNCTION: LEGORACERS 0x0048f760
LauncherHazard::~LauncherHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048f7c0
void LauncherHazard::ClearFields()
{
	m_triggerEventId = -1;
	m_triggerWorld = 0;
	m_golExport = 0;
	m_billboard = 0;
	m_powerupManager = 0;
	m_trailManager = 0;
	m_trail = 0;
	m_launchPosition.Clear();
	m_targetPosition.Clear();
	m_triggerPosition.Clear();
	m_triggerRadiusSquared = 0.0f;
}

// FUNCTION: LEGORACERS 0x0048f830
void LauncherHazard::Load(HazardContext* p_context, GolFileParser* p_parser)
{
	if (m_state) {
		Reset();
	}

	m_triggerId = -1;
	m_eventTable = p_context->GetEventTable();
	m_triggerWorld = p_context->GetTriggerWorld();
	m_golExport = p_context->GetGolExport();
	m_powerupManager = p_context->GetPowerupManager();
	m_trailManager = p_context->GetTrailManager();

	m_billboard = static_cast<GolBillboard*>(m_golExport->CreateBillboard());
	GolMaterial* material = p_context->GetRenderer()->FindMaterialByName("cannonb");
	m_billboard->Configure(material, 5.0f, 5.0f, g_launcherMaxDistanceSquared);

	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token;
	while ((token = p_parser->GetNextToken()) != GolFileParser::e_rightCurly) {
		switch (token) {
		case HazardManager::HzbTxtParser::e_source:
			m_launchPosition.m_x = p_parser->ReadFloat();
			m_launchPosition.m_y = p_parser->ReadFloat();
			m_launchPosition.m_z = p_parser->ReadFloat();
			break;
		case HazardManager::HzbTxtParser::e_target:
			m_targetPosition.m_x = p_parser->ReadFloat();
			m_targetPosition.m_y = p_parser->ReadFloat();
			m_targetPosition.m_z = p_parser->ReadFloat();
			break;
		case HazardManager::HzbTxtParser::e_triggerPosition:
			m_triggerPosition.m_x = p_parser->ReadFloat();
			m_triggerPosition.m_y = p_parser->ReadFloat();
			m_triggerPosition.m_z = p_parser->ReadFloat();
			break;
		case HazardManager::HzbTxtParser::e_triggerRadius: {
			LegoFloat radius = p_parser->ReadFloat();
			m_triggerRadiusSquared = radius * radius;
			break;
		}
		case HazardManager::HzbTxtParser::e_trigger:
			m_triggerEventId = p_parser->ReadInteger();
			break;
		default:
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}
	}

	if (p_context->GetMirror()) {
		m_launchPosition.m_y = -m_launchPosition.m_y;
		m_targetPosition.m_y = -m_targetPosition.m_y;
		m_triggerPosition.m_y = -m_triggerPosition.m_y;
	}

	m_state = c_stateLoaded;
}

// FUNCTION: LEGORACERS 0x0048f9f0
void LauncherHazard::Reset()
{
	OnDeactivate(NULL);
	if (m_billboard != NULL) {
		m_golExport->DestroyBillboard(m_billboard);
		m_billboard = NULL;
	}

	ClearFields();
	Hazard::Reset();
}

// FUNCTION: LEGORACERS 0x0048fa30
void LauncherHazard::OnEventStart(LegoS32 p_eventId, void* p_context)
{
	if (m_triggerEventId == -1 || p_eventId != m_triggerEventId || m_state != c_stateLoaded) {
		return;
	}

	GolVec3* position = static_cast<GolVec3*>(p_context);
	if (position != NULL) {
		LegoFloat dx = m_triggerPosition.m_x - position->m_x;
		LegoFloat dy = m_triggerPosition.m_y - position->m_y;
		LegoFloat dz = m_triggerPosition.m_z - position->m_z;
		if (dx * dx + dy * dy + dz * dz >= m_triggerRadiusSquared) {
			return;
		}
	}

	OnActivate(NULL);
}

// FUNCTION: LEGORACERS 0x0048faa0
void LauncherHazard::OnActivate(void*)
{
	m_state = c_stateActive;
	m_trigger.SetBoundsCenter(m_launchPosition);

	PowerupProjectile::Params projectileParams;
	projectileParams.m_collisionWorld = m_triggerWorld;
	projectileParams.m_gravity = -32.176f;
	projectileParams.m_eventQueue = NULL;
	projectileParams.m_targetOffset.m_x = 0.0f;
	projectileParams.m_targetOffset.m_y = 0.0f;
	projectileParams.m_targetOffset.m_z = 0.0f;
	projectileParams.m_speed = 180.0f;
	projectileParams.m_lifetimeMs = 3000;
	projectileParams.m_launchHeight = 0.0f;
	projectileParams.m_worldEntity = &m_trigger;

	m_projectile.LaunchAtPosition(&projectileParams, &m_targetPosition);

	RaceTrailManager::Trail::Params trailParams;
	trailParams.m_durationMs = 0x12c;
	trailParams.m_sampleCount = 4;
	trailParams.m_unk0x0c = 1;
	trailParams.m_unk0x10 = 0;
	trailParams.m_endScale = 0.1f;
	trailParams.m_endAlpha = 0.0f;
	trailParams.m_pointCount = 4;

	RaceTrailManager::Trail::Params* trailParamsPtr = &trailParams;
	m_trail = m_trailManager->AcquireTrail(trailParamsPtr);
	if (m_trail != NULL) {
		RaceTrailManager::Trail* item = m_trail;
		item->SetColor(&g_launcherTrailColor);
	}

	m_eventTable->FireEventsAt(6, 6, &m_launchPosition);
}

// FUNCTION: LEGORACERS 0x0048fba0
void LauncherHazard::OnDeactivate(void*)
{
	m_projectile.Deactivate();

	if (m_trail != NULL) {
		RaceTrailManager* manager = static_cast<RaceTrailManager*>(m_trailManager);
		RaceTrailManager::Trail* item = m_trail;
		manager->ReleaseTrail(item);
		m_trail = NULL;
	}

	m_state = c_stateLoaded;
}

// FUNCTION: LEGORACERS 0x0048fbe0
void LauncherHazard::Update(undefined4 p_elapsedMs)
{
	if (m_state == c_stateLoaded) {
		return;
	}

	Hazard::Update(p_elapsedMs);

	PowerupProjectile* projectile = &m_projectile;
	if (projectile->GetState() != 0) {
		if (projectile->Update(p_elapsedMs) == 3) {
			GolVec3 position = projectile->GetHitPosition();
			m_powerupManager->SpawnExplosion(&position, 0, 0);
			projectile->Deactivate();
			m_eventTable->FireEventsAt(7, 7, &position);

			if (m_trail != NULL) {
				RaceTrailManager* manager = static_cast<RaceTrailManager*>(m_trailManager);
				RaceTrailManager::Trail* item = m_trail;
				manager->ReleaseTrail(item);
				m_trail = NULL;
			}
		}
	}

	if (projectile->GetState() == 0) {
		OnDeactivate(NULL);
	}

	if (m_trail == NULL) {
		return;
	}

	GolVec3 center;
	projectile->GetWorldEntity()->GetBoundsCenter(&center);

	GolVec3 velocity;
	projectile->GetVelocity(&velocity);

	GolVec2 perpendicular;
	perpendicular.m_x = velocity.m_y;
	perpendicular.m_y = -velocity.m_x;
	if (perpendicular.m_x == 0.0f && perpendicular.m_y == 0.0f) {
		return;
	}

	GolMath::NormalizeVector2(perpendicular, &perpendicular);
	LegoFloat widthX = perpendicular.m_x * 3.0f;
	LegoFloat widthY = perpendicular.m_y * 3.0f;

	GolVec3 positions[4];
	positions[0].m_x = center.m_x - widthX * 0.5f;
	positions[0].m_y = center.m_y - widthY * 0.5f;
	positions[0].m_z = center.m_z + 3.0f * 0.5f;
	positions[1].m_x = positions[0].m_x;
	positions[1].m_y = positions[0].m_y;
	positions[1].m_z = positions[0].m_z - 3.0f;
	positions[2].m_x = positions[0].m_x + widthX;
	positions[2].m_y = positions[0].m_y + widthY;
	positions[2].m_z = positions[1].m_z;
	positions[3].m_x = positions[2].m_x;
	positions[3].m_y = positions[2].m_y;
	positions[3].m_z = positions[1].m_z + 3.0f;

	RaceTrailManager::Trail* item = m_trail;
	item->AddSampleWithCenter(p_elapsedMs, positions, center);
}

// FUNCTION: LEGORACERS 0x0048fde0
void LauncherHazard::Draw(GolD3DRenderDevice* p_renderer)
{
	if (m_state != c_stateLoaded && m_projectile.GetState() == PowerupProjectile::c_stateFlying) {
		GolVec3 position;
		m_trigger.GetBoundsCenter(&position);
		m_billboard->SetPosition(position);
		p_renderer->DrawBillboard(*m_billboard);
	}
}
