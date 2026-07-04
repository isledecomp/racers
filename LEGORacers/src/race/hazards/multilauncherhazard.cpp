#include "race/hazards/multilauncherhazard.h"

#include "decomp.h"
#include "golerror.h"
#include "golfileparser.h"
#include "golmath.h"
#include "race/hazardmanager.h"
#include "race/hazards/hazardcontext.h"
#include "race/raceeventtable.h"
#include "types.h"

DECOMP_SIZE_ASSERT(MultiLauncherHazard, 0x140)

extern LegoU16 g_randomTable[1024];
extern LegoU32 g_randomTableIndex;

// FUNCTION: LEGORACERS 0x0048f200
MultiLauncherHazard::MultiLauncherHazard()
{
	m_launchPositions = NULL;
	m_launchEventIds = NULL;
	m_targetPositions = NULL;
	m_targetEventIds = NULL;
	m_launchPositionCount = 0;
	m_targetPositionCount = 0;
}

// FUNCTION: LEGORACERS 0x0048f260
MultiLauncherHazard::~MultiLauncherHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048f2b0
void MultiLauncherHazard::Load(HazardContext* p_context, GolFileParser* p_parser)
{
	if (m_state) {
		Reset();
	}

	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token;
	while ((token = p_parser->GetNextToken()) != HazardManager::HzbTxtParser::e_launcher) {
		if (token == HazardManager::HzbTxtParser::e_target) {
			p_parser->ReadLeftBracket();
			m_targetPositionCount = p_parser->ReadInteger();
			p_parser->ReadRightBracket();

			m_targetPositions = static_cast<GolVec3*>(::operator new(sizeof(GolVec3) * m_targetPositionCount));
			if (m_targetPositions == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}

			m_targetEventIds = static_cast<LegoS32*>(::operator new(sizeof(LegoS32) * m_targetPositionCount));
			if (m_targetEventIds == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}

			p_parser->ReadLeftCurly();
			for (LegoU32 i = 0; i < m_targetPositionCount; i++) {
				m_targetPositions[i].m_x = p_parser->ReadFloat();
				m_targetPositions[i].m_y = p_parser->ReadFloat();
				m_targetPositions[i].m_z = p_parser->ReadFloat();
				m_targetEventIds[i] = p_parser->ReadInteger();

				if (p_context->GetMirror()) {
					m_targetPositions[i].m_y = -m_targetPositions[i].m_y;
				}
			}

			p_parser->ReadRightCurly();
		}
		else if (token == HazardManager::HzbTxtParser::e_source) {
			p_parser->ReadLeftBracket();
			m_launchPositionCount = p_parser->ReadInteger();
			p_parser->ReadRightBracket();

			m_launchPositions = static_cast<GolVec3*>(::operator new(sizeof(GolVec3) * m_launchPositionCount));
			if (m_launchPositions == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}

			m_launchEventIds = static_cast<LegoS32*>(::operator new(sizeof(LegoS32) * m_launchPositionCount));
			if (m_launchEventIds == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}

			p_parser->ReadLeftCurly();
			for (LegoU32 i = 0; i < m_launchPositionCount; i++) {
				m_launchPositions[i].m_x = p_parser->ReadFloat();
				m_launchPositions[i].m_y = p_parser->ReadFloat();
				m_launchPositions[i].m_z = p_parser->ReadFloat();
				m_launchEventIds[i] = p_parser->ReadInteger();

				if (p_context->GetMirror()) {
					m_launchPositions[i].m_y = -m_launchPositions[i].m_y;
				}
			}

			p_parser->ReadRightCurly();
		}
	}

	LauncherHazard::Load(p_context, p_parser);
	p_parser->ReadRightCurly();

	m_triggerId = -1;
	m_state = c_stateLoaded;
}

// FUNCTION: LEGORACERS 0x0048f520
void MultiLauncherHazard::Reset()
{
	OnDeactivate(NULL);

	if (m_targetEventIds != NULL) {
		::operator delete(m_targetEventIds);
		m_targetEventIds = NULL;
	}
	if (m_targetPositions != NULL) {
		::operator delete(m_targetPositions);
		m_targetPositions = NULL;
	}
	if (m_launchEventIds != NULL) {
		::operator delete(m_launchEventIds);
		m_launchEventIds = NULL;
	}
	if (m_launchPositions != NULL) {
		::operator delete(m_launchPositions);
		m_launchPositions = NULL;
	}

	m_launchPositionCount = 0;
	m_targetPositionCount = 0;
	LauncherHazard::Reset();
}

// FUNCTION: LEGORACERS 0x0048f5b0
void MultiLauncherHazard::OnActivate(void*)
{
	g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
	LegoU32 sourceIndex = static_cast<LegoU32>(g_randomTable[g_randomTableIndex]) % m_launchPositionCount;

	g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
	m_targetIndex = static_cast<LegoU32>(g_randomTable[g_randomTableIndex]) % m_targetPositionCount;

	m_launchPosition = m_launchPositions[sourceIndex];
	m_targetPosition = m_targetPositions[m_targetIndex];

	if (m_eventTable != NULL) {
		LegoS32 eventId = m_launchEventIds[sourceIndex];
		m_eventTable->FireEventsAt(eventId, eventId, &m_launchPosition);
	}

	LauncherHazard::OnActivate(NULL);
}

// FUNCTION: LEGORACERS 0x0048f680
void MultiLauncherHazard::OnDeactivate(void*)
{
	if (m_eventTable != NULL) {
		LegoS32 eventId = m_targetEventIds[m_targetIndex];
		m_eventTable->FireEventsAt(eventId, eventId, &m_targetPosition);
	}

	LauncherHazard::OnDeactivate(NULL);
	m_state = c_stateLoaded;
}

// FUNCTION: LEGORACERS 0x0048f6c0
void MultiLauncherHazard::Update(undefined4 p_elapsedMs)
{
	if (m_state != c_stateLoaded) {
		LauncherHazard::Update(p_elapsedMs);
	}
}
