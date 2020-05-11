#include "keyboardevent.h"

keyboardEvent::keyboardEvent()
	: type(EventType::Invalid),
	key(0u)
{

}

keyboardEvent::keyboardEvent(const EventType type, const unsigned char key)
	: type(type),
	key(key)
{

}

bool keyboardEvent::IsPress() const
{
	return this->type == EventType::Press;
}

bool keyboardEvent::IsRelease() const
{
	return this->type == EventType::Release;
}

bool keyboardEvent::IsValid() const
{
	return this->type != EventType::Invalid;
}

unsigned char keyboardEvent::GetkeyCode() const
{
	return this->key;
}

