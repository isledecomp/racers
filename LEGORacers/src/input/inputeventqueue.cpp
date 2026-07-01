#include "input/inputeventqueue.h"

#include "golerror.h"

#include <string.h>

DECOMP_SIZE_ASSERT(InputEventQueue, 0x1c)
DECOMP_SIZE_ASSERT(InputEventQueue::Event, 0x10)

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
	m_events = NULL;
	m_capacity = 0;
}

// FUNCTION: LEGORACERS 0x0044b760
LegoBool32 InputEventQueue::Allocate(LegoS32 p_capacity)
{
	Reset();

	m_events = new Event[p_capacity];
	if (m_events == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	::memset(m_events, 0, sizeof(Event) * p_capacity);
	m_capacity = p_capacity;
	m_allocated = TRUE;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0044b7c0
LegoBool32 InputEventQueue::Reset()
{
	if (m_allocated) {
		if (m_events != NULL) {
			delete[] m_events;
		}

		Initialize();
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0044b7f0
InputEventQueue::Event* InputEventQueue::Dequeue()
{
	Event* event = &m_events[m_readPos];
	if (m_size == 0) {
		return NULL;
	}

	m_readPos += 1;
	m_readPos %= m_capacity;
	m_size -= 1;
	return event;
}

// FUNCTION: LEGORACERS 0x0044b820
InputEventQueue::Event* InputEventQueue::Enqueue(InputDevice* p_device, LegoU32 p_keyCode, LegoU32 p_time)
{
	Event* event = &m_events[m_writePos];
	if (m_size == m_capacity) {
		return NULL;
	}

	event->m_device = p_device;
	event->m_keyCode = p_keyCode;
	event->m_timeMs = p_time;
	event->m_isRepeat = FALSE;
	event->m_isPressed = FALSE;
	m_writePos += 1;
	m_writePos %= m_capacity;
	m_size += 1;
	return event;
}

// FUNCTION: LEGORACERS 0x0044b870
InputDevice::Callback::ResultValue InputEventQueue::OnKeyDown(
	InputDevice* p_device,
	undefined4 p_keyCode,
	undefined4 p_time
)
{
	Event* event = Enqueue(p_device, p_keyCode, p_time);
	if (event != NULL) {
		event->m_isPressed = TRUE;
	}

	InputDevice::Callback::Result result;
	result.m_pointer = event;
	return result.m_value;
}

// FUNCTION: LEGORACERS 0x0044b890
InputDevice::Callback::ResultValue InputEventQueue::OnKeyUp(
	InputDevice* p_device,
	undefined4 p_keyCode,
	undefined4 p_time
)
{
	Event* event = Enqueue(p_device, p_keyCode, p_time);

	InputDevice::Callback::Result result;
	result.m_pointer = event;
	return result.m_value;
}

// FUNCTION: LEGORACERS 0x0044b8b0
InputDevice::Callback::ResultValue InputEventQueue::OnKeyRepeat(
	InputDevice* p_device,
	undefined4 p_keyCode,
	undefined4 p_time
)
{
	Event* event = Enqueue(p_device, p_keyCode, p_time);
	if (event != NULL) {
		event->m_isPressed = TRUE;
		event->m_isRepeat = TRUE;
	}

	InputDevice::Callback::Result result;
	result.m_pointer = event;
	return result.m_value;
}

// FUNCTION: LEGORACERS 0x0044b8e0
void InputEventQueue::ClearQueue()
{
	m_writePos = 0;
	m_readPos = 0;
	m_size = 0;
}
