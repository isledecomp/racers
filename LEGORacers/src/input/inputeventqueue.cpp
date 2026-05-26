#include "input/inputeventqueue.h"

#include "golerror.h"

#include <string.h>

DECOMP_SIZE_ASSERT(InputEventQueue, 0x1c)
DECOMP_SIZE_ASSERT(InputEventQueue::Item, 0x10)

// FUNCTION: LEGORACERS 0x0044b6f0
InputEventQueue::InputEventQueue()
{
	Initialize();
}

// FUNCTION: LEGORACERS 0x0044b730
InputEventQueue::~InputEventQueue()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0044b740
void InputEventQueue::Initialize()
{
	ClearQueue();
	m_allocated = FALSE;
	m_items = NULL;
	m_capacity = 0;
}

// FUNCTION: LEGORACERS 0x0044b760
LegoBool32 InputEventQueue::Allocate(LegoS32 p_capacity)
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
LegoBool32 InputEventQueue::Reset()
{
	if (m_allocated) {
		if (m_items != NULL) {
			delete[] m_items;
		}

		Initialize();
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0044b7f0
InputEventQueue::Item* InputEventQueue::Dequeue()
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
InputEventQueue::Item* InputEventQueue::Enqueue(InputDevice* p_device, LegoU32 p_keyCode, LegoU32 p_arg3)
{
	Item* item = &m_items[m_writePos];
	if (m_size == m_capacity) {
		return NULL;
	}

	item->m_device = p_device;
	item->m_keyCode = p_keyCode;
	item->m_unk0x08 = p_arg3;
	item->m_isRepeat = FALSE;
	item->m_isPressed = FALSE;
	m_writePos += 1;
	m_writePos %= m_capacity;
	m_size += 1;
	return item;
}

// FUNCTION: LEGORACERS 0x0044b870
void InputEventQueue::OnKeyDown(InputDevice* p_device, undefined4 p_keyCode, undefined4 p_arg3)
{
	Item* item = Enqueue(p_device, p_keyCode, p_arg3);
	if (item != NULL) {
		item->m_isPressed = TRUE;
	}
}

// FUNCTION: LEGORACERS 0x0044b890
void InputEventQueue::OnKeyUp(InputDevice* p_device, undefined4 p_keyCode, undefined4 p_arg3)
{
	Item* item = Enqueue(p_device, p_keyCode, p_arg3);
}

// FUNCTION: LEGORACERS 0x0044b8b0
void InputEventQueue::OnKeyRepeat(InputDevice* p_device, undefined4 p_keyCode, undefined4 p_arg3)
{
	Item* item = Enqueue(p_device, p_keyCode, p_arg3);
	if (item != NULL) {
		item->m_isPressed = TRUE;
		item->m_isRepeat = TRUE;
	}
}

// FUNCTION: LEGORACERS 0x0044b8e0
void InputEventQueue::ClearQueue()
{
	m_writePos = 0;
	m_readPos = 0;
	m_size = 0;
}
