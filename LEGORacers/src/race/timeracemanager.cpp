#include "race/timeracemanager.h"

#include "core/gol.h"
#include "golbinparser.h"
#include "golerror.h"
#include "golfileparser.h"
#include "golstream.h"
#include "world/golworlddatabase.h"

#include <math.h>
#include <string.h>

DECOMP_SIZE_ASSERT(TimeRaceManager, 0x3b8)
DECOMP_SIZE_ASSERT(TimeRaceManager::GhbTxtParser, 0x1fc)
DECOMP_SIZE_ASSERT(TimeRaceManager::GhostRunData, 0x25c0)
DECOMP_SIZE_ASSERT(TimeRaceManager::GhostRunData::Sample, 0x0a)

// GLOBAL: LEGORACERS 0x004af674
extern const LegoFloat g_ghostSpeedScale = 4.0f;

// GLOBAL: LEGORACERS 0x004b01a4
extern const LegoFloat g_ghostAnimationRateScale = 1.8f;

// GLOBAL: LEGORACERS 0x004b01a8
extern const LegoFloat g_ghostSampleFractionScale = 0.004f;

// FUNCTION: LEGORACERS 0x00422350
TimeRaceManager::TimeRaceManager()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004223b0
TimeRaceManager::~TimeRaceManager()
{
	Shutdown();
}

// FUNCTION: LEGORACERS 0x004223c0
void TimeRaceManager::Reset()
{
	m_worldDatabase = NULL;
	m_golExport = NULL;
	m_racer = NULL;
	m_recordGhostMarker = NULL;
	m_recordGhostCarModel = NULL;
	m_recordGhostDriver = NULL;
	m_recordRun = NULL;
	m_bestRun = NULL;
	m_scratchRun = NULL;
	m_elapsedTotalMs = 0;
	m_flags = 0;
	m_bestDriverMountOffset.m_x = 0.0f;
	m_bestDriverMountOffset.m_y = 0.0f;
	m_bestDriverMountOffset.m_z = 0.0f;
	m_recordDriverMountOffset.m_x = 0.0f;
	m_recordDriverMountOffset.m_y = 0.0f;
	m_recordDriverMountOffset.m_z = 0.0f;
}

// FUNCTION: LEGORACERS 0x00422420
void TimeRaceManager::Initialize(
	GolD3DRenderDevice* p_renderer,
	GolExport* p_golExport,
	LegoBool32 p_binary,
	LegoBool32 p_mirror
)
{
	if (m_scratchRun != NULL) {
		Shutdown();
	}

	m_golExport = p_golExport;
	m_scratchRun = new GhostRunData;
	if (m_scratchRun == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_bestRun = new GhostRunData;
	if (m_bestRun == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_recordRun = new GhostRunData;
	if (m_recordRun == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < c_lapCount; i++) {
		m_scratchRun->m_lapTimes[i] = 0;
		m_bestRun->m_lapTimes[i] = 0;
		m_recordRun->m_lapTimes[i] = 0;
	}

	m_scratchRun->m_sampleCount = 0;
	m_scratchRun->m_unk0x259c = 0;
	m_scratchRun->m_finished = 0;
	m_scratchRun->m_initialPosition.m_x = 0.0f;
	m_scratchRun->m_initialPosition.m_y = 0.0f;
	m_scratchRun->m_initialPosition.m_z = 0.0f;
	m_scratchRun->m_initialRotation.m_x = 0.0f;
	m_scratchRun->m_initialRotation.m_y = 0.0f;
	m_scratchRun->m_initialRotation.m_z = 0.0f;
	m_scratchRun->m_initialRotation.m_w = 0.0f;

	m_bestRun->m_sampleCount = 0;
	m_bestRun->m_unk0x259c = 0;
	m_bestRun->m_finished = 0;
	m_bestRun->m_initialPosition.m_x = 0.0f;
	m_bestRun->m_initialPosition.m_y = 0.0f;
	m_bestRun->m_initialPosition.m_z = 0.0f;
	m_bestRun->m_initialRotation.m_x = 0.0f;
	m_bestRun->m_initialRotation.m_y = 0.0f;
	m_bestRun->m_initialRotation.m_z = 0.0f;
	m_bestRun->m_initialRotation.m_w = 0.0f;

	m_recordRun->m_sampleCount = 0;
	m_recordRun->m_unk0x259c = 0;
	m_recordRun->m_finished = 0;
	m_recordRun->m_initialPosition.m_x = 0.0f;
	m_recordRun->m_initialPosition.m_y = 0.0f;
	m_recordRun->m_initialPosition.m_z = 0.0f;
	m_recordRun->m_initialRotation.m_x = 0.0f;
	m_recordRun->m_initialRotation.m_y = 0.0f;
	m_recordRun->m_initialRotation.m_z = 0.0f;
	m_recordRun->m_initialRotation.m_w = 0.0f;

	m_worldDatabase = m_golExport->CreateWorldDatabase();
	m_worldDatabase->Load(p_renderer, "ghost", p_binary, 1.0f);

	m_recordGhostMarker = m_worldDatabase->GetAnimatedEntities();
	m_recordGhostDriver = m_worldDatabase->GetAnimatedEntities() + 1;
	m_recordGhostCarModel = m_worldDatabase->GetModelEntities();
	m_recordGhostDriver->PlayPart(12);

	m_recordDriverMountOffset.m_x = -2.131681f;
	m_recordDriverMountOffset.m_y = 0.01123f;
	m_recordDriverMountOffset.m_z = 1.608f;

	if (p_binary) {
		m_flags |= c_flagBinaryGhosts;
	}

	if (p_mirror) {
		m_flags |= c_flagMirror;
	}

	m_sampleCountdownMs = 0;
}

// FUNCTION: LEGORACERS 0x00422670
void TimeRaceManager::Shutdown()
{
	m_bestGhostSecondary.ResetModelState();
	m_bestGhostDriver.ResetModelState();
	m_bestGhostMarker.ResetModelState();
	m_bestGhostCarModel.ResetModelState();

	if (m_worldDatabase) {
		m_golExport->DestroyWorldDatabase(m_worldDatabase);
		m_worldDatabase = NULL;
	}
	if (m_recordRun) {
		delete m_recordRun;
		m_recordRun = NULL;
	}
	if (m_bestRun) {
		delete m_bestRun;
		m_bestRun = NULL;
	}
	if (m_scratchRun) {
		delete m_scratchRun;
		m_scratchRun = NULL;
	}

	Reset();
}

// FUNCTION: LEGORACERS 0x00422710
void TimeRaceManager::Update(LegoU32 p_elapsedMs)
{
	LegoU8 flags = m_flags;
	if (!(flags & c_flagRunning)) {
		return;
	}

	m_elapsedTotalMs += p_elapsedMs;

	if (flags & c_flagBestRunValid) {
		m_bestGhostCarModel.Update(p_elapsedMs);
		m_bestGhostMarker.Update(p_elapsedMs);
		m_bestGhostDriver.Update(p_elapsedMs);
		if (m_bestGhostSecondary.HasModel()) {
			m_bestGhostSecondary.Update(p_elapsedMs);
		}
	}

	if (m_flags & c_flagRecordRunValid) {
		m_recordGhostMarker->Update(p_elapsedMs);
		m_recordGhostCarModel->Update(p_elapsedMs);
		m_recordGhostDriver->Update(p_elapsedMs);
	}

	if (p_elapsedMs >= m_sampleCountdownMs) {
		m_sampleCountdownMs += c_ghostSampleIntervalMs - p_elapsedMs;
		if (m_scratchRun->m_sampleCount < GhostRunData::c_sampleCapacity) {
			CarVisuals* racerField = &m_racer->m_visuals;
			GolVec3 position;
			racerField->m_carEntity->GetPosition(&position);

			m_scratchRun->m_samples[m_scratchRun->m_sampleCount].m_positionX =
				static_cast<LegoS16>(32.0f * position.m_x);
			m_scratchRun->m_samples[m_scratchRun->m_sampleCount].m_positionY =
				static_cast<LegoS16>(32.0f * position.m_y);
			m_scratchRun->m_samples[m_scratchRun->m_sampleCount].m_positionZ =
				static_cast<LegoS16>(32.0f * position.m_z);

			GolQuat rotation;
			GolMath::Matrix3ToQuat(m_racer->m_visuals.m_carEntity->GetOrientation(), &rotation);
			m_scratchRun->m_samples[m_scratchRun->m_sampleCount].m_rotationX =
				static_cast<LegoS8>(127.0f * rotation.m_x);
			m_scratchRun->m_samples[m_scratchRun->m_sampleCount].m_rotationY =
				static_cast<LegoS8>(127.0f * rotation.m_y);
			m_scratchRun->m_samples[m_scratchRun->m_sampleCount].m_rotationZ =
				static_cast<LegoS8>(127.0f * rotation.m_z);
			m_scratchRun->m_samples[m_scratchRun->m_sampleCount].m_rotationW =
				static_cast<LegoS8>(127.0f * rotation.m_w);

			if (m_scratchRun->m_sampleCount == 0) {
				m_scratchRun->m_initialPosition = position;
				m_scratchRun->m_initialRotation = rotation;
			}

			GhostRunData* scratchRun = m_scratchRun;
			LegoU32 sampleCount = scratchRun->m_sampleCount;
			sampleCount++;
			scratchRun->m_sampleCount = sampleCount;
		}
	}
	else {
		m_sampleCountdownMs -= p_elapsedMs;
	}
}

// STUB: LEGORACERS 0x00422960
void TimeRaceManager::Draw(GolD3DRenderDevice* p_renderer)
{
	GolAnimatedEntity* optionalEntity = NULL;

	if (m_elapsedTotalMs >= c_ghostRaceDurationLimitMs) {
		return;
	}

	p_renderer->SetAlphaOverride(127, 0);

	for (LegoU32 i = 0; i < 2; i++) {
		LegoU8 flags;
		GhostRunData* ghostRun;
		GolAnimatedEntity* animatedEntity;
		GolAnimatedEntity* attachedEntity;
		GolModelEntity* modelEntity;
		GolVec3* attachedOffset;

		if (i == 0) {
			flags = m_flags;
			if (!(flags & c_flagBestRunValid)) {
				continue;
			}

			ghostRun = m_bestRun;
			if (ghostRun->m_finished) {
				continue;
			}

			animatedEntity = &m_bestGhostMarker;
			attachedEntity = &m_bestGhostDriver;
			if (m_bestGhostSecondary.HasModel()) {
				optionalEntity = &m_bestGhostSecondary;
			}
			modelEntity = &m_bestGhostCarModel;
			attachedOffset = &m_bestDriverMountOffset;
		}
		else {
			flags = m_flags;
			if (!(flags & c_flagRecordRunValid)) {
				continue;
			}

			ghostRun = m_recordRun;
			if (ghostRun->m_finished) {
				continue;
			}

			attachedEntity = m_recordGhostDriver;
			animatedEntity = m_recordGhostMarker;
			modelEntity = m_recordGhostCarModel;
			attachedOffset = &m_recordDriverMountOffset;
		}

		if (!(flags & c_flagRunning)) {
			GolVec3* position = &ghostRun->m_initialPosition;
			GolQuat* rotation = &ghostRun->m_initialRotation;

			animatedEntity->SetPosition(*position);
			animatedEntity->SetOrientationFromQuaternion(*rotation);
			modelEntity->SetPosition(*position);
			modelEntity->SetOrientationFromQuaternion(*rotation);
			if (optionalEntity) {
				optionalEntity->SetPosition(*position);
				optionalEntity->SetOrientationFromQuaternion(*rotation);
			}

			GolVec3 attachedPosition;
			animatedEntity->LocalToWorld(*attachedOffset, &attachedPosition);
			attachedEntity->SetPosition(attachedPosition);
			attachedEntity->SetOrientationFromQuaternion(*rotation);
		}
		else {
			LegoU32 sampleIndex = m_elapsedTotalMs / c_ghostSampleIntervalMs;
			LegoU32 sampleRemainder = m_elapsedTotalMs - sampleIndex * c_ghostSampleIntervalMs;
			LegoFloat amount =
				static_cast<LegoFloat>(static_cast<LegoS32>(sampleRemainder)) * g_ghostSampleFractionScale;

			if (sampleIndex + 1 >= ghostRun->m_sampleCount) {
				ghostRun->m_finished = TRUE;
				continue;
			}

			GhostRunData::Sample* sample = &ghostRun->m_samples[sampleIndex];
			GhostRunData::Sample* nextSample = sample + 1;

			GolVec3 position;
			position.m_x = static_cast<LegoFloat>(sample->m_positionX) / 32.0f;
			position.m_y = static_cast<LegoFloat>(sample->m_positionY) / 32.0f;
			position.m_z = static_cast<LegoFloat>(sample->m_positionZ) / 32.0f;

			LegoFloat nextPositionX = static_cast<LegoFloat>(nextSample->m_positionX) / 32.0f;
			LegoFloat nextPositionY = static_cast<LegoFloat>(nextSample->m_positionY) / 32.0f;
			LegoFloat nextPositionZ = static_cast<LegoFloat>(nextSample->m_positionZ) / 32.0f;

			GolVec3 delta;
			delta.m_x = nextPositionX - position.m_x;
			delta.m_y = nextPositionY - position.m_y;
			delta.m_z = nextPositionZ - position.m_z;

			position.m_x += delta.m_x * amount;
			position.m_y += delta.m_y * amount;
			position.m_z += delta.m_z * amount;

			GolQuat rotation;
			rotation.m_x = static_cast<LegoFloat>(sample->m_rotationX) / 127.0f;
			rotation.m_y = static_cast<LegoFloat>(sample->m_rotationY) / 127.0f;
			rotation.m_z = static_cast<LegoFloat>(sample->m_rotationZ) / 127.0f;
			rotation.m_w = static_cast<LegoFloat>(sample->m_rotationW) / 127.0f;

			GolQuat nextRotation;
			nextRotation.m_x = static_cast<LegoFloat>(nextSample->m_rotationX) / 127.0f;
			nextRotation.m_y = static_cast<LegoFloat>(nextSample->m_rotationY) / 127.0f;
			nextRotation.m_z = static_cast<LegoFloat>(nextSample->m_rotationZ) / 127.0f;
			nextRotation.m_w = static_cast<LegoFloat>(nextSample->m_rotationW) / 127.0f;

			GolQuat interpolatedRotation;
			GolMath::LerpQuat(rotation, nextRotation, amount, &interpolatedRotation);

			LegoFloat distanceSquared = delta.m_z * delta.m_z + delta.m_y * delta.m_y + delta.m_x * delta.m_x;
			LegoFloat speed = static_cast<LegoFloat>(sqrt(distanceSquared));
			speed *= g_ghostSpeedScale;
			speed *= g_ghostAnimationRateScale;
			animatedEntity->SetMsPerFrame(speed);

			animatedEntity->SetPosition(position);
			animatedEntity->SetOrientationFromQuaternion(interpolatedRotation);
			modelEntity->SetPosition(position);
			modelEntity->SetOrientationFromQuaternion(interpolatedRotation);
			if (optionalEntity) {
				optionalEntity->SetPosition(position);
				optionalEntity->SetOrientationFromQuaternion(interpolatedRotation);
			}

			GolVec3 attachedPosition;
			animatedEntity->LocalToWorld(*attachedOffset, &attachedPosition);
			attachedEntity->SetPosition(attachedPosition);
			attachedEntity->SetOrientationFromQuaternion(interpolatedRotation);
		}

		p_renderer->DrawModelEntity(animatedEntity);
		p_renderer->DrawModelEntity(modelEntity);
		if (optionalEntity) {
			p_renderer->DrawModelEntity(optionalEntity);
		}
		p_renderer->DrawModelEntity(attachedEntity);
	}

	p_renderer->ClearAlphaOverride();
}

// FUNCTION: LEGORACERS 0x00422de0
void TimeRaceManager::PrepareRun()
{
	m_flags &= ~c_flagRecordRunValid;
	LoadGhostRun(m_recordRun, "ghost");
	if (0 < m_recordRun->m_sampleCount) {
		m_flags |= c_flagRecordRunValid;
	}

	m_elapsedTotalMs = 0;
	m_flags &= ~c_flagRunning;

	for (LegoU32 i = 0; i < c_lapCount; i++) {
		m_scratchRun->m_lapTimes[i] = 0;
	}

	m_scratchRun->m_sampleCount = 0;
	m_scratchRun->m_initialPosition.m_x = 0.0f;
	m_scratchRun->m_initialPosition.m_y = 0.0f;
	m_scratchRun->m_initialPosition.m_z = 0.0f;
	m_scratchRun->m_initialRotation.m_x = 0.0f;
	m_scratchRun->m_initialRotation.m_y = 0.0f;
	m_scratchRun->m_initialRotation.m_z = 0.0f;
	m_scratchRun->m_initialRotation.m_w = 0.0f;
	m_scratchRun->m_unk0x259c = 0;
	m_scratchRun->m_finished = 0;
	m_recordRun->m_finished = 0;
	m_bestRun->m_finished = 0;
}

// FUNCTION: LEGORACERS 0x00422eb0
void TimeRaceManager::AttachRacer(Racer* p_racer)
{
	m_racer = p_racer;
	m_flags |= c_flagRunning;
	if (m_flags & c_flagBit4) {
		m_flags |= c_flagBestRunValid;
	}

	if (m_flags & c_flagBestRunValid) {
		GolModelEntity* sourceModel = p_racer->m_visuals.m_bodyModelEntity;
		m_bestGhostCarModel.SetPrimaryModel(sourceModel->GetModel(0), sourceModel->GetModelDistance(0));
		LegoU32 i;
		for (i = 1; i < 3; i++) {
			if (sourceModel->GetModel(i)) {
				m_bestGhostCarModel.AddModel(sourceModel->GetModel(i), sourceModel->GetModelDistance(i));
			}
		}

		GolAnimatedEntity* sourceAnimated = p_racer->m_visuals.m_carEntity;
		m_bestGhostMarker.SetModel(
			sourceAnimated->GetModel(0),
			sourceAnimated->GetSceneNode(0),
			sourceAnimated->GetModelPart(0),
			sourceAnimated->GetModelDistance(0)
		);
		for (i = 1; i < 3; i++) {
			if (sourceAnimated->GetModel(i)) {
				m_bestGhostMarker.AddModel(
					sourceAnimated->GetModel(i),
					sourceAnimated->GetSceneNode(i),
					sourceAnimated->GetModelPart(i),
					sourceAnimated->GetModelDistance(i)
				);
			}
		}

		sourceAnimated = p_racer->m_visuals.m_driverEntity;
		m_bestGhostDriver.SetModel(
			sourceAnimated->GetModel(0),
			sourceAnimated->GetSceneNode(0),
			sourceAnimated->GetModelPart(0),
			sourceAnimated->GetModelDistance(0)
		);
		for (i = 1; i < 3; i++) {
			if (sourceAnimated->GetModel(i)) {
				m_bestGhostDriver.AddModel(
					sourceAnimated->GetModel(i),
					sourceAnimated->GetSceneNode(i),
					sourceAnimated->GetModelPart(i),
					sourceAnimated->GetModelDistance(i)
				);
			}
		}

		sourceAnimated = p_racer->m_visuals.m_secondaryEntity;
		if (sourceAnimated) {
			m_bestGhostSecondary.SetModel(
				sourceAnimated->GetModel(0),
				sourceAnimated->GetSceneNode(0),
				sourceAnimated->GetModelPart(0),
				sourceAnimated->GetModelDistance(0)
			);
			for (i = 1; i < 3; i++) {
				if (sourceAnimated->GetModel(i)) {
					m_bestGhostSecondary.AddModel(
						sourceAnimated->GetModel(i),
						sourceAnimated->GetSceneNode(i),
						sourceAnimated->GetModelPart(i),
						sourceAnimated->GetModelDistance(i)
					);
				}
			}
		}

		m_bestDriverMountOffset = p_racer->m_visuals.m_driverMountOffset;
		m_bestGhostDriver.PlayPart(13);
	}
}

// FUNCTION: LEGORACERS 0x004230e0
void TimeRaceManager::UpdateBestRun()
{
	LegoU32 i;
	LegoU32 bestSum = 0;
	LegoU32 latestSum = 0;

	for (i = 0; i < 3; i++) {
		m_scratchRun->m_lapTimes[i] = m_racer->m_lapTimes[i];
	}

	for (i = 0; i < 3; i++) {
		bestSum += m_bestRun->m_lapTimes[i];
		latestSum += m_scratchRun->m_lapTimes[i];
	}

	if (latestSum < bestSum || bestSum == 0) {
		GhostRunData* previousBest = m_bestRun;
		m_bestRun = m_scratchRun;
		m_scratchRun = previousBest;
	}

	m_flags = (m_flags & 0xfc) | c_flagBit4;

	m_racer = NULL;
}

// FUNCTION: LEGORACERS 0x00423160
void TimeRaceManager::LoadGhostRun(GhostRunData* p_ghostRun, const LegoChar* p_name)
{
	GolFileParser* parser;
	LegoU8 flags = m_flags;
	if (flags & c_flagBinaryGhosts) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".ghb");
	}
	else {
		parser = new GhbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	LegoChar fileName[c_ghostFileNameBufferSize];
	strncpy(fileName, p_name, c_ghostFileNameLimit);
	strncat(fileName, parser->GetSuffix(), c_ghostFileSuffixLimit);
	fileName[c_ghostFileNameLimit + c_ghostFileSuffixLimit] = '\0';

	if (GolStream::FindFile(fileName) == GolStream::e_ioFileNotFound) {
		delete parser;
		p_ghostRun->m_sampleCount = 0;
		return;
	}

	parser->OpenFileForRead(p_name);
	parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(c_ghostPathToken));
	parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token;
	while ((token = parser->GetNextToken()) != GolFileParser::e_rightCurly) {
		switch (token) {
		case c_ghostPathLapTimesToken: {
			for (LegoU32 i = 0; i < c_lapCount; i++) {
				p_ghostRun->m_lapTimes[i] = parser->ReadInteger();
			}
			break;
		}
		case c_ghostPathPositionToken:
			p_ghostRun->m_initialPosition.m_x = parser->ReadFloat();
			p_ghostRun->m_initialPosition.m_y = parser->ReadFloat();
			p_ghostRun->m_initialPosition.m_z = parser->ReadFloat();
			if (m_flags & c_flagMirror) {
				p_ghostRun->m_initialPosition.m_y = -p_ghostRun->m_initialPosition.m_y;
			}
			break;
		case c_ghostPathRotationToken:
			p_ghostRun->m_initialRotation.m_x = parser->ReadFloat();
			p_ghostRun->m_initialRotation.m_y = parser->ReadFloat();
			p_ghostRun->m_initialRotation.m_z = parser->ReadFloat();
			p_ghostRun->m_initialRotation.m_w = parser->ReadFloat();
			if (m_flags & c_flagMirror) {
				p_ghostRun->m_initialRotation.m_y = -p_ghostRun->m_initialRotation.m_y;
				p_ghostRun->m_initialRotation.m_w = -p_ghostRun->m_initialRotation.m_w;
			}
			break;
		case c_ghostPathUnknownToken:
			p_ghostRun->m_unk0x259c = parser->ReadInteger();
			break;
		case c_ghostPathNodesToken: {
			p_ghostRun->m_sampleCount = parser->ReadBracketedCountAndLeftCurly();
			for (LegoU32 i = 0; i < p_ghostRun->m_sampleCount; i++) {
				GhostRunData::Sample* sample = &p_ghostRun->m_samples[i];
				sample->m_positionX = static_cast<LegoS16>(parser->ReadInteger());
				sample->m_positionY = static_cast<LegoS16>(parser->ReadInteger());
				sample->m_positionZ = static_cast<LegoS16>(parser->ReadInteger());
				sample->m_rotationX = static_cast<LegoS8>(parser->ReadInteger());
				sample->m_rotationY = static_cast<LegoS8>(parser->ReadInteger());
				sample->m_rotationZ = static_cast<LegoS8>(parser->ReadInteger());
				sample->m_rotationW = static_cast<LegoS8>(parser->ReadInteger());

				if (m_flags & c_flagMirror) {
					sample->m_positionY = -sample->m_positionY;
					sample->m_rotationY = -sample->m_rotationY;
					sample->m_rotationW = -sample->m_rotationW;
				}
			}
			parser->ReadRightCurly();
			break;
		}
		default:
			parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}
	}

	p_ghostRun->m_finished = 0;
	parser->Dispose();
	delete parser;
}

// FUNCTION: LEGORACERS 0x004234b0
LegoBool32 TimeRaceManager::HasBeatenRecord()
{
	LegoU8 flags = m_flags;
	if (!(flags & (c_flagBestRunValid | c_flagBit4))) {
		return FALSE;
	}
	if (!(flags & c_flagRecordRunValid)) {
		return FALSE;
	}

	LegoU32 recordSum = 0;
	LegoU32 bestSum = 0;

	for (LegoU32 i = 0; i < 3; i++) {
		recordSum += m_recordRun->m_lapTimes[i];
		bestSum += m_bestRun->m_lapTimes[i];
	}

	return bestSum < recordSum;
}

// FUNCTION: LEGORACERS 0x004234f0
TimeRaceManager::GhostRunData* TimeRaceManager::ResetRun()
{
	m_flags &= ~c_flagRunning;
	m_elapsedTotalMs = 0;

	for (LegoU32 i = 0; i < c_lapCount; i++) {
		m_scratchRun->m_lapTimes[i] = 0;
	}

	m_scratchRun->m_sampleCount = 0;
	m_scratchRun->m_initialPosition.m_x = 0.0f;
	m_scratchRun->m_initialPosition.m_y = 0.0f;
	m_scratchRun->m_initialPosition.m_z = 0.0f;
	m_scratchRun->m_initialRotation.m_x = 0.0f;
	m_scratchRun->m_initialRotation.m_y = 0.0f;
	m_scratchRun->m_initialRotation.m_z = 0.0f;
	m_scratchRun->m_initialRotation.m_w = 0.0f;
	m_scratchRun->m_unk0x259c = 0;
	m_scratchRun->m_finished = 0;

	GhostRunData* recordRun = m_recordRun;
	recordRun->m_finished = 0;
	m_bestRun->m_finished = 0;

	return recordRun;
}
