#include "Event.h"

// base
Event::Event(EventType type)
:mType(type)
{
}
Event::~Event()
{
}

// add unit
AddUnitEvent::AddUnitEvent(const Vector2D& pos)
	:Event(EventType::ADD_UNIT)
	, mPos(pos)
{
}
AddUnitEvent::~AddUnitEvent()
{
}

// remove unit
DeleteUnitEvent::DeleteUnitEvent(const Vector2D& pos)
	:Event(EventType::DELETE_UNIT)
	, mPos(pos)
{
}
DeleteUnitEvent::~DeleteUnitEvent()
{
}

// freeze animation
AnimationFreezeEvent::AnimationFreezeEvent(const bool& frozen)
	:Event(EventType::TOGGLE_FREEZE_ANIMATIONS)
	, mFrozen(frozen)
{
}
AnimationFreezeEvent::~AnimationFreezeEvent()
{
}