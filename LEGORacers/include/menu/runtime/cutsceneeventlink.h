#ifndef CUTSCENEEVENTLINK_H
#define CUTSCENEEVENTLINK_H

#include "menu/runtime/cutscenedefinition.h"
#include "menu/runtime/cutsceneevent.h"

// SIZE 0x0c
class CutsceneEventLink {
public:
	CutsceneEventLink();

	void Bind(undefined4 p_isStart, CutsceneEvent* p_event);
	void Fire();
	void Fire(CutsceneDefinition::Frame::CameraEvent* p_payload);
	void Fire(CutsceneDefinition::Frame::ModelEvent* p_payload);
	void Fire(CutsceneDefinition::Frame::TransformEvent* p_payload);
	void Fire(void*);

	CutsceneEventLink* GetNext() const { return m_next; }
	void SetNext(CutsceneEventLink* p_next) { m_next = p_next; }

private:
	undefined4 m_isStart;      // 0x00
	CutsceneEvent* m_event;    // 0x04
	CutsceneEventLink* m_next; // 0x08
};

#endif // CUTSCENEEVENTLINK_H
