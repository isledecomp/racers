#ifndef CORALBREEZE0X28_H
#define CORALBREEZE0X28_H

#include "decomp.h"
#include "types.h"
#include "util/list.h"

class CobaltMist0x30;

// SIZE 0x28
class CoralBreeze0x28 : public ListLink {
public:
	CoralBreeze0x28()
	{
		ListLink* self = (ListLink*) &m_prev;
		self->m_prev = self;
		self->m_next = self;

		ListHead* head1 = &m_unk0x10;
		head1->m_sentinel.m_next = (ListLink*) &head1->m_first;
		head1->m_first = &head1->m_sentinel;

		ListHead* head2 = &m_unk0x1c;
		head1->m_sentinel.m_prev = NULL;

		head2->m_sentinel.m_next = (ListLink*) &head2->m_first;
		head2->m_first = &head2->m_sentinel;
		head2->m_sentinel.m_prev = NULL;
	}

	virtual undefined4 VTable0x00(undefined4) = 0; // vtable+0x00
	virtual undefined4 VTable0x04() = 0;           // vtable+0x04

protected:
	CobaltMist0x30* m_unk0x0c; // 0x0c
	ListHead m_unk0x10;        // 0x10
	ListHead m_unk0x1c;        // 0x1c
};

#endif // CORALBREEZE0X28_H
