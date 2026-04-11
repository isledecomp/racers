#ifndef OPALSTAR0X20_H
#define OPALSTAR0X20_H

#include "decomp.h"
#include "rubyhaze0x08.h"
#include "types.h"
#include "util/list.h"

class CobaltMist0x30;

// SIZE 0x20
class OpalStar0x20 : public RubyHaze0x08, public ListLink {
public:
	OpalStar0x20()
	{
		ListLink* self = (ListLink*) &m_prev;
		self->m_prev = self;
		self->m_next = self;

		ListHead* head = &m_unk0x14;
		head->m_sentinel.m_next = (ListLink*) &head->m_first;
		head->m_first = &head->m_sentinel;
		head->m_sentinel.m_prev = NULL;
	}

	void SetUnk0x10(CobaltMist0x30* p_unk0x10) { m_unk0x10 = p_unk0x10; }

protected:
	CobaltMist0x30* m_unk0x10; // 0x10
	ListHead m_unk0x14;        // 0x14
};

#endif // OPALSTAR0X20_H
