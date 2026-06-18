#include "decomp.h"
#include "golbinparser.h"
#include "golerror.h"
#include "race/racesession.h"

DECOMP_SIZE_ASSERT(RaceSession::Field0x213c, 0x0c)
DECOMP_SIZE_ASSERT(RaceSession::Field0x213c::Resource, 0x24)
DECOMP_SIZE_ASSERT(RaceSession::Field0x213c::TibTxtParser, 0x1fc)

extern LegoU16 g_unk0x004befec[1024];
extern LegoU32 g_unk0x004c6ee4;

// FUNCTION: LEGORACERS 0x00464700
LegoU32 RaceSession::Field0x213c::FUN_00464700()
{
	return 8;
}

// FUNCTION: LEGORACERS 0x00464710
RaceSession::Field0x213c::Resource::Resource()
{
	m_unk0x08 = NULL;
	m_unk0x04 = NULL;
	m_unk0x0c = NULL;
	m_unk0x20 = 0;
	m_unk0x10 = 0;
	m_unk0x14 = 0;
	m_unk0x18 = 0;
	m_unk0x1c = 0;
}

// FUNCTION: LEGORACERS 0x00464740
RaceSession::Field0x213c::Resource::~Resource()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00464750
void RaceSession::Field0x213c::Resource::FUN_00464750(
	LegoEventQueue* p_eventQueue,
	RaceEventTable0x90* p_eventTable,
	LegoU32 p_unk0x0c,
	LegoU32 p_unk0x10,
	LegoU32 p_unk0x14,
	LegoS32 p_unk0x18,
	LegoU32 p_flags
)
{
	LegoU32 flags = p_flags;
	m_unk0x08 = p_eventTable;
	m_unk0x10 = p_unk0x0c;
	m_unk0x20 = p_unk0x18;
	m_unk0x0c = p_eventQueue;
	m_unk0x14 = p_unk0x10;
	m_unk0x18 = p_unk0x14;
	flags &= ~c_flags0x1cBit0;
	m_unk0x1c = flags;

	LegoU32 duration = p_unk0x10;
	if (flags & c_flags0x1cBit2) {
		if (p_unk0x10 > c_randomTableMask) {
			g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
			duration = g_unk0x004befec[g_unk0x004c6ee4] * (p_unk0x10 / c_randomTableMask);
		}
		else {
			g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
			duration = g_unk0x004befec[g_unk0x004c6ee4] % p_unk0x10;
		}
	}

	if (!m_unk0x18) {
		FUN_00464a40(duration);
	}
}

// FUNCTION: LEGORACERS 0x00464800
void RaceSession::Field0x213c::Resource::Reset()
{
	if (m_unk0x04) {
		m_unk0x04->m_active = FALSE;
		m_unk0x04 = NULL;
	}

	m_unk0x08 = NULL;
	m_unk0x0c = NULL;
	m_unk0x20 = 0;
	m_unk0x10 = 0;
	m_unk0x14 = 0;
	m_unk0x18 = 0;
	m_unk0x1c = 0;
}

// FUNCTION: LEGORACERS 0x00464830
void RaceSession::Field0x213c::Resource::FUN_00464830(LegoU32 p_elapsedMs)
{
	LegoU32 remaining = m_unk0x18;
	if (0 < remaining) {
		if (p_elapsedMs >= remaining) {
			LegoU32 duration = m_unk0x10;
			m_unk0x18 = 0;

			if (m_unk0x1c & c_flags0x1cBit1) {
				if (duration > c_randomTableMask) {
					g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
					duration = g_unk0x004befec[g_unk0x004c6ee4] * (duration / c_randomTableMask);
				}
				else {
					g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
					duration = g_unk0x004befec[g_unk0x004c6ee4] % duration;
				}
			}

			FUN_00464a40(duration);
			return;
		}

		remaining -= p_elapsedMs;
		m_unk0x18 = remaining;
	}
}

// FUNCTION: LEGORACERS 0x004648d0
void RaceSession::Field0x213c::Resource::VTable0x00(LegoEventQueue::CallbackData* p_data)
{
	m_unk0x04 = NULL;

	if (m_unk0x1c & c_flags0x1cBit0) {
		if (m_unk0x20 != -1) {
			m_unk0x08->FUN_00462140(m_unk0x20, NULL);
		}

		LegoU32 duration = m_unk0x14;
		LegoU32 elapsed = p_data->m_unk0x14 - m_unk0x10;
		if (elapsed < duration) {
			duration -= elapsed;
		}

		if (m_unk0x1c & c_flags0x1cBit2) {
			if (duration > c_randomTableMask) {
				g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
				FUN_00464a40(g_unk0x004befec[g_unk0x004c6ee4] * (duration / c_randomTableMask));
				m_unk0x1c &= ~c_flags0x1cBit0;
				return;
			}

			g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
			duration = g_unk0x004befec[g_unk0x004c6ee4] % duration;
		}

		FUN_00464a40(duration);
		m_unk0x1c &= ~c_flags0x1cBit0;
		return;
	}

	if (m_unk0x20 != -1) {
		m_unk0x08->FUN_00461ef0(m_unk0x20, NULL);
	}

	LegoU32 duration = m_unk0x10;
	LegoU32 elapsed = p_data->m_unk0x14 - m_unk0x14;
	if (elapsed < duration) {
		duration -= elapsed;
	}

	if (m_unk0x1c & c_flags0x1cBit1) {
		if (duration > c_randomTableMask) {
			g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
			duration = g_unk0x004befec[g_unk0x004c6ee4] * (duration / c_randomTableMask);
		}
		else {
			g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
			duration = g_unk0x004befec[g_unk0x004c6ee4] % duration;
		}
	}

	FUN_00464a40(duration);
	m_unk0x1c |= c_flags0x1cBit0;
}

// FUNCTION: LEGORACERS 0x00464a40
LegoEventQueue::Event* RaceSession::Field0x213c::Resource::FUN_00464a40(LegoU32 p_unk0x04)
{
	LegoEventQueue::Callback* callback = this;
	LegoEventQueue::Descriptor descriptor;
	descriptor.m_unk0x08 = descriptor.m_unk0x00 = 1;
	descriptor.m_unk0x04 = 0;
	descriptor.m_unk0x0c = 0;
	descriptor.m_unk0x10 = p_unk0x04;

	return m_unk0x04 = m_unk0x0c->FUN_0042fb50(callback, &descriptor);
}

// FUNCTION: LEGORACERS 0x00464a80
RaceSession::Field0x213c::Field0x213c()
{
	m_unk0x08 = NULL;
	m_unk0x00 = 0;
	m_unk0x04 = 0;
}

// FUNCTION: LEGORACERS 0x00464a90
RaceSession::Field0x213c::~Field0x213c()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00464aa0
void RaceSession::Field0x213c::FUN_00464aa0(
	LegoEventQueue* p_eventQueue,
	RaceEventTable0x90* p_eventTable,
	const LegoChar* p_name,
	LegoBool32 p_binary
)
{
	if (m_unk0x00) {
		Destroy();
	}

	m_unk0x00 = p_eventTable;

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
	parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
	parser->AssertNextTokenIs(GolFileParser::e_leftBracket);
	m_unk0x04 = parser->ReadInteger();

	if (m_unk0x04) {
		parser->AssertNextTokenIs(GolFileParser::e_rightBracket);
		parser->AssertNextTokenIs(GolFileParser::e_leftCurly);

		m_unk0x08 = new Resource[m_unk0x04];
		if (m_unk0x08 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		for (LegoU32 i = 0; i < m_unk0x04; i++) {
			parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
			parser->AssertNextTokenIs(GolFileParser::e_leftCurly);

			LegoU32 firstDuration = 0;
			LegoU32 secondDuration = 0;
			LegoU32 initialDelay = 0;
			LegoS32 eventIndex = -1;
			LegoU32 flags = 0;

			GolFileParser::ParserTokenType token = parser->GetNextToken();
			while (token != GolFileParser::e_rightCurly) {
				switch (token) {
				case GolFileParser::e_unknown0x28:
					if (parser->GetNextToken() == GolFileParser::e_unknown0x2b) {
						flags |= Resource::c_flags0x1cBit1;
						firstDuration = parser->ReadInteger();
					}
					else {
						firstDuration = parser->GetLastInt();
					}
					break;
				case GolFileParser::e_unknown0x29:
					if (parser->GetNextToken() == GolFileParser::e_unknown0x2b) {
						flags |= Resource::c_flags0x1cBit2;
						secondDuration = parser->ReadInteger();
					}
					else {
						secondDuration = parser->GetLastInt();
					}
					break;
				case GolFileParser::e_unknown0x2a:
					eventIndex = parser->ReadInteger();
					break;
				case GolFileParser::e_unknown0x2d:
					initialDelay = parser->ReadInteger();
					break;
				default:
					parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
					break;
				}

				token = parser->GetNextToken();
			}

			m_unk0x08[i]
				.FUN_00464750(p_eventQueue, m_unk0x00, firstDuration, secondDuration, initialDelay, eventIndex, flags);
		}
	}

	parser->Dispose();
	delete parser;
}

// FUNCTION: LEGORACERS 0x00464dd0
LegoU32 RaceSession::Field0x213c::FUN_00464dd0(LegoU32 p_elapsedMs)
{
	LegoU32 result = m_unk0x04;

	for (LegoU32 i = 0; i < result; i++) {
		m_unk0x08[i].FUN_00464830(p_elapsedMs);
		result = m_unk0x04;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00464e10
void RaceSession::Field0x213c::Destroy()
{
	if (m_unk0x08) {
		delete[] m_unk0x08;
		m_unk0x08 = NULL;
	}

	m_unk0x00 = NULL;
	m_unk0x04 = 0;
}
