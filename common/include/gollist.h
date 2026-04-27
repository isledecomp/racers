#ifndef GOLLIST_H
#define GOLLIST_H

#include "types.h"

// SIZE 0x08
struct GolListLink {
	GolListLink()
	{
		m_prev = this;
		m_next = this;
	}

	void Remove()
	{
		m_next->m_prev = m_prev;
		m_prev->m_next = m_next;
	}

	GolListLink* InsertBefore(GolListLink* p_link);
	GolListLink* NextValid();

	GolListLink* m_prev; // 0x00
	GolListLink* m_next; // 0x04
};

template <class T>
struct GolListBaseLinkTraits {
	static GolListLink* GetLink(T& p_item) { return (GolListLink*) &p_item; }

	static T& GetItem(GolListLink& p_link) { return *(T*) &p_link; }
};

// SIZE 0x0c
template <class T, class TListTraits = GolListBaseLinkTraits<T> >
struct GolList {
	GolList()
	{
		m_sentinel.m_next = (GolListLink*) &m_first;
		m_first = (GolListLink*) &m_sentinel;
		m_sentinel.m_prev = NULL;
	}

	static GolListLink* GetLink(T& p_item) { return TListTraits::GetLink(p_item); }
	static T& GetItem(GolListLink& p_link) { return TListTraits::GetItem(p_link); }

	void Append(T& p_item) { Append(GetLink(p_item)); }
	void Prepend(T& p_item) { Prepend(GetLink(p_item)); }
	GolListLink* LastLink() { return m_first; }
	GolListLink* FirstLink() { return m_sentinel.m_next; }
	GolListLink* FirstValidLink();
	LegoBool32 IsEmpty() { return m_sentinel.m_next == (GolListLink*) &m_first; }
	LegoBool32 IsValidLink(GolListLink* p_link) { return p_link->m_next && p_link; }
	LegoBool32 IsValidLastLink(GolListLink* p_link) { return p_link->m_prev && p_link; }

	GolListLink* NextLink(GolListLink* p_link)
	{
		p_link = p_link->m_next;
		return p_link->m_next ? p_link : NULL;
	}

	GolListLink* PrevLink(GolListLink* p_link)
	{
		p_link = p_link->m_prev;
		return p_link->m_prev ? p_link : NULL;
	}

	void Swap(GolList& p_list)
	{
		p_list.m_first->m_next = (GolListLink*) &m_first;
		p_list.m_sentinel.m_next->m_prev = (GolListLink*) &m_sentinel;
		m_first->m_next = (GolListLink*) &p_list.m_first;
		m_sentinel.m_next->m_prev = (GolListLink*) &p_list.m_sentinel;

		GolListLink* first = m_first;
		GolListLink* firstLink = m_sentinel.m_next;
		m_first = p_list.m_first;
		m_sentinel.m_next = p_list.m_sentinel.m_next;
		p_list.m_first = first;
		p_list.m_sentinel.m_next = firstLink;
	}

	void Append(GolListLink* p_link)
	{
		p_link->m_prev = m_first;
		p_link->m_next = (GolListLink*) &m_first;
		m_first->m_next = p_link;
		m_first = p_link;
	}

	void Prepend(GolListLink* p_link)
	{
		p_link->m_next = m_sentinel.m_next;
		p_link->m_prev = (GolListLink*) &m_sentinel;
		m_sentinel.m_next->m_prev = p_link;
		m_sentinel.m_next = p_link;
	}

private:
	struct Sentinel {
		GolListLink* m_prev; // 0x00
		GolListLink* m_next; // 0x04
	};

	GolListLink* m_first; // 0x00
	Sentinel m_sentinel;  // 0x04
};

#endif // GOLLIST_H
