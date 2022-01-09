#pragma once

#include <Vector2D.h>

#include <string>
#include <trackable.h>

using namespace std;

enum class EventType
{
	INVALID_EVENT_TYPE = -1,
	ADD_UNIT,
	DELETE_UNIT,
	TOGGLE_FREEZE_ANIMATIONS,
	QUIT_GAME,
	NUM_EVENT_TYPES
};

class Event:public Trackable
{
public:
	Event( EventType type );
	virtual ~Event();

	EventType getType() const { return mType; };

private:
	EventType mType;

};

class AddUnitEvent : public Event
{
public:
	AddUnitEvent(const Vector2D& pos);
	~AddUnitEvent();

	inline Vector2D getPos() const { return mPos; };

private:
	Vector2D mPos;
};

class DeleteUnitEvent : public Event
{
public:
	DeleteUnitEvent(const Vector2D& pos);
	~DeleteUnitEvent();

	inline Vector2D getPos() const { return mPos; };

private:
	Vector2D mPos;
};

class AnimationFreezeEvent : public Event
{
public:
	AnimationFreezeEvent(const bool& frozen);
	~AnimationFreezeEvent();

	inline bool getFrozen() const { return mFrozen; };

private:
	bool mFrozen;
};