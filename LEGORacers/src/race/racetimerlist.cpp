#include "race/racetimerlist.h"

#include "decomp.h"
#include "golbinparser.h"
#include "golerror.h"
#include "race/raceeventtable.h"

DECOMP_SIZE_ASSERT(RaceTimerList, 0x0c)
DECOMP_SIZE_ASSERT(RaceTimerList::Resource, 0x24)
DECOMP_SIZE_ASSERT(RaceTimerList::TibTxtParser, 0x1fc)

extern LegoU16 g_randomTable[1024];
extern LegoU32 g_randomTableIndex;

// FUNCTION: LEGORACERS 0x00464710
RaceTimerList::Resource::Resource()
{
	m_eventTable = NULL;
	m_event = NULL;
	m_eventQueue = NULL;
	m_eventId = 0;
	m_onDurationMs = 0;
	m_offDurationMs = 0;
	m_delayMs = 0;
	m_flags = 0;
}

// FUNCTION: LEGORACERS 0x00464740
RaceTimerList::Resource::~Resource()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00464750
void RaceTimerList::Resource::Initialize(
	LegoEventQueue* p_eventQueue,
	RaceEventTable* p_eventTable,
	LegoU32 p_onDurationMs,
	LegoU32 p_offDurationMs,
	LegoU32 p_delayMs,
	LegoS32 p_eventId,
	LegoU32 p_flags
)
{
	LegoU32 flags = p_flags;
	m_eventTable = p_eventTable;
	m_onDurationMs = p_onDurationMs;
	m_eventId = p_eventId;
	m_eventQueue = p_eventQueue;
	m_offDurationMs = p_offDurationMs;
	m_delayMs = p_delayMs;
	flags &= ~c_active;
	m_flags = flags;

	LegoU32 duration = p_offDurationMs;
	if (flags & c_randomizeOffDuration) {
		if (p_offDurationMs > c_randomTableMask) {
			g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
			duration = g_randomTable[g_randomTableIndex] * (p_offDurationMs / c_randomTableMask);
		}
		else {
			g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
			duration = g_randomTable[g_randomTableIndex] % p_offDurationMs;
		}
	}

	if (!m_delayMs) {
		Schedule(duration);
	}
}

// FUNCTION: LEGORACERS 0x00464800
void RaceTimerList::Resource::Reset()
{
	if (m_event) {
		m_event->m_active = FALSE;
		m_event = NULL;
	}

	m_eventTable = NULL;
	m_eventQueue = NULL;
	m_eventId = 0;
	m_onDurationMs = 0;
	m_offDurationMs = 0;
	m_delayMs = 0;
	m_flags = 0;
}

// FUNCTION: LEGORACERS 0x00464830
void RaceTimerList::Resource::Update(LegoU32 p_elapsedMs)
{
	LegoU32 remaining = m_delayMs;
	if (0 < remaining) {
		if (p_elapsedMs >= remaining) {
			LegoU32 duration = m_onDurationMs;
			m_delayMs = 0;

			if (m_flags & c_randomizeOnDuration) {
				if (duration > c_randomTableMask) {
					g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
					duration = g_randomTable[g_randomTableIndex] * (duration / c_randomTableMask);
				}
				else {
					g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
					duration = g_randomTable[g_randomTableIndex] % duration;
				}
			}

			Schedule(duration);
			return;
		}

		remaining -= p_elapsedMs;
		m_delayMs = remaining;
	}
}

// FUNCTION: LEGORACERS 0x004648d0
void RaceTimerList::Resource::OnEvent(LegoEventQueue::CallbackData* p_data)
{
	m_event = NULL;

	if (m_flags & c_active) {
		if (m_eventId != -1) {
			m_eventTable->EndEventsAt(m_eventId, NULL);
		}

		LegoU32 duration = m_offDurationMs;
		LegoU32 elapsed = p_data->m_elapsedMs - m_onDurationMs;
		if (elapsed < duration) {
			duration -= elapsed;
		}

		if (m_flags & c_randomizeOffDuration) {
			if (duration > c_randomTableMask) {
				g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
				Schedule(g_randomTable[g_randomTableIndex] * (duration / c_randomTableMask));
				m_flags &= ~c_active;
				return;
			}

			g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
			duration = g_randomTable[g_randomTableIndex] % duration;
		}

		Schedule(duration);
		m_flags &= ~c_active;
		return;
	}

	if (m_eventId != -1) {
		m_eventTable->StartEventsAt(m_eventId, NULL);
	}

	LegoU32 duration = m_onDurationMs;
	LegoU32 elapsed = p_data->m_elapsedMs - m_offDurationMs;
	if (elapsed < duration) {
		duration -= elapsed;
	}

	if (m_flags & c_randomizeOnDuration) {
		if (duration > c_randomTableMask) {
			g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
			duration = g_randomTable[g_randomTableIndex] * (duration / c_randomTableMask);
		}
		else {
			g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
			duration = g_randomTable[g_randomTableIndex] % duration;
		}
	}

	Schedule(duration);
	m_flags |= c_active;
}

// FUNCTION: LEGORACERS 0x00464a40
LegoEventQueue::Event* RaceTimerList::Resource::Schedule(LegoU32 p_delayMs)
{
	LegoEventQueue::Callback* callback = this;
	LegoEventQueue::Descriptor descriptor;
	descriptor.m_maxFireCount = descriptor.m_type = LegoEventQueue::Descriptor::c_typeTimer;
	descriptor.m_flags = 0;
	descriptor.m_hitThreshold = 0;
	descriptor.m_intervalMs = p_delayMs;

	return m_event = m_eventQueue->AllocateEvent(callback, &descriptor);
}

// FUNCTION: LEGORACERS 0x00464a80
RaceTimerList::RaceTimerList()
{
	m_timers = NULL;
	m_eventTable = 0;
	m_count = 0;
}

// FUNCTION: LEGORACERS 0x00464a90
RaceTimerList::~RaceTimerList()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00464aa0
void RaceTimerList::Load(
	LegoEventQueue* p_eventQueue,
	RaceEventTable* p_eventTable,
	const LegoChar* p_name,
	LegoBool32 p_binary
)
{
	if (m_eventTable) {
		Destroy();
	}

	m_eventTable = p_eventTable;

	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		parser->SetSuffix(".tib");
	}
	else {
		parser = new TibTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_name);
	parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(TibTxtParser::e_timer));
	parser->AssertNextTokenIs(GolFileParser::e_leftBracket);
	m_count = parser->ReadInteger();
	if (!m_count) {
		parser->Dispose();
		delete parser;
		return;
	}

	parser->AssertNextTokenIs(GolFileParser::e_rightBracket);
	parser->AssertNextTokenIs(GolFileParser::e_leftCurly);

	m_timers = new Resource[m_count];
	if (m_timers == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_count; i++) {
		parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(TibTxtParser::e_timer));
		parser->AssertNextTokenIs(GolFileParser::e_leftCurly);

		LegoU32 onDuration = 0;
		LegoU32 offDuration = 0;
		LegoU32 initialDelay = 0;
		LegoS32 eventIndex = -1;
		LegoU32 flags = 0;

		GolFileParser::ParserTokenType token = parser->GetNextToken();
		while (token != GolFileParser::e_rightCurly) {
			switch (token) {
			case TibTxtParser::e_onPhase:
				if (parser->GetNextToken() == TibTxtParser::e_duration) {
					flags |= Resource::c_randomizeOnDuration;
					onDuration = parser->ReadInteger();
				}
				else {
					onDuration = parser->GetLastInt();
				}
				break;
			case TibTxtParser::e_offPhase:
				if (parser->GetNextToken() == TibTxtParser::e_duration) {
					flags |= Resource::c_randomizeOffDuration;
					offDuration = parser->ReadInteger();
				}
				else {
					offDuration = parser->GetLastInt();
				}
				break;
			case TibTxtParser::e_event:
				eventIndex = parser->ReadInteger();
				break;
			case TibTxtParser::e_initialDelay:
				initialDelay = parser->ReadInteger();
				break;
			default:
				parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}

			token = parser->GetNextToken();
		}

		m_timers[i].Initialize(p_eventQueue, m_eventTable, onDuration, offDuration, initialDelay, eventIndex, flags);
	}

	parser->Dispose();
	delete parser;
}

// FUNCTION: LEGORACERS 0x00464dd0
LegoU32 RaceTimerList::Update(LegoU32 p_elapsedMs)
{
	LegoU32 result = m_count;

	for (LegoU32 i = 0; i < result; i++) {
		m_timers[i].Update(p_elapsedMs);
		result = m_count;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00464e10
void RaceTimerList::Destroy()
{
	if (m_timers) {
		delete[] m_timers;
		m_timers = NULL;
	}

	m_eventTable = NULL;
	m_count = 0;
}
