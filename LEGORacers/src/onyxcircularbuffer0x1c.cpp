#include "onyxcircularbuffer0x1c.h"

#include "golerror.h"

#include <string.h>

DECOMP_SIZE_ASSERT(OnyxCircularBuffer0x1c, 0x1c)
DECOMP_SIZE_ASSERT(OnyxCircularBuffer0x1c::Item, 0x10)

// FUNCTION: LEGORACERS 0x0044b6f0
OnyxCircularBuffer0x1c::OnyxCircularBuffer0x1c()
{
	FUN_0044b740();
}

// FUNCTION: LEGORACERS 0x0044b730
OnyxCircularBuffer0x1c::~OnyxCircularBuffer0x1c()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0044b740
void OnyxCircularBuffer0x1c::FUN_0044b740()
{
	FUN_0044b8e0();
	m_allocated = FALSE;
	m_items = NULL;
	m_capacity = 0;
}

// FUNCTION: LEGORACERS 0x0044b760
LegoBool32 OnyxCircularBuffer0x1c::Allocate(LegoS32 p_capacity)
{
	Reset();

	m_items = new Item[p_capacity];
	if (m_items == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	::memset(m_items, 0, sizeof(Item) * p_capacity);
	m_capacity = p_capacity;
	m_allocated = TRUE;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0044b7c0
LegoBool32 OnyxCircularBuffer0x1c::Reset()
{
	if (m_allocated) {
		if (m_items != NULL) {
			delete[] m_items;
		}

		FUN_0044b740();
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0044b7f0
OnyxCircularBuffer0x1c::Item* OnyxCircularBuffer0x1c::FUN_0044b7f0()
{
	Item* item = &m_items[m_readPos];
	if (m_size == 0) {
		return NULL;
	}

	m_readPos += 1;
	m_readPos %= m_capacity;
	m_size -= 1;
	return item;
}

// FUNCTION: LEGORACERS 0x0044b820
OnyxCircularBuffer0x1c::Item* OnyxCircularBuffer0x1c::FUN_0044b820(
	InputDevice* p_device,
	undefined4 p_keyCode,
	undefined4 p_arg3
)
{
	Item* item = &m_items[m_writePos];
	if (m_size == m_capacity) {
		return NULL;
	}

	item->m_device = p_device;
	item->m_keyCode = p_keyCode;
	item->m_unk0x08 = p_arg3;
	item->m_unk0x0d = 0;
	item->m_unk0x0c = FALSE;
	m_writePos += 1;
	m_writePos %= m_capacity;
	m_size += 1;
	// m_writePos = (m_writePos + 1) % m_capacity;
	return item;
}

// FUNCTION: LEGORACERS 0x0044b870
void OnyxCircularBuffer0x1c::OnKeyDown(InputDevice* p_device, undefined4 p_keyCode, undefined4 p_arg3)
{
	Item* item = FUN_0044b820(p_device, p_keyCode, p_arg3);
	if (item != NULL) {
		item->m_unk0x0c = TRUE;
	}
}

// FUNCTION: LEGORACERS 0x0044b890
void OnyxCircularBuffer0x1c::OnKeyUp(InputDevice* p_device, undefined4 p_keyCode, undefined4 p_arg3)
{
	Item* item = FUN_0044b820(p_device, p_keyCode, p_arg3);
}

// FUNCTION: LEGORACERS 0x0044b8b0
void OnyxCircularBuffer0x1c::OnKeyRepeat(InputDevice* p_device, undefined4 p_keyCode, undefined4 p_arg3)
{
	Item* item = FUN_0044b820(p_device, p_keyCode, p_arg3);
	if (item != NULL) {
		item->m_unk0x0c = TRUE;
		item->m_unk0x0d = TRUE;
	}
}

// FUNCTION: LEGORACERS 0x0044b8e0
void OnyxCircularBuffer0x1c::FUN_0044b8e0()
{
	m_writePos = 0;
	m_readPos = 0;
	m_size = 0;
}
