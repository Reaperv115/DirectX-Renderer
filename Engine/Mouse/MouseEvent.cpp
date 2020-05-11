#include "MouseEvent.h"

MouseEvent::MouseEvent()
	: type(EventType::Invalid),
	x(0),
	y(0)
{

}

MouseEvent::MouseEvent(const EventType type, const int x, const int y)
	: type(type),
	x(x),
	y(y)
{

}

bool MouseEvent::isValid() const
{
	return this->type != EventType::Invalid;
}

MouseEvent::EventType MouseEvent::getType() const
{
	return this->type;
}

MousePoint MouseEvent::getPos() const
{
	return { this->x, this->y };
}

int MouseEvent::GetPosX() const
{
	return this->x;
}

int MouseEvent::GetPosY() const
{
	return this->y;
}
