#include "Mouse.h"

void Mouse::leftPressed(int x, int y)
{
	this->leftDown = true;
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::LPress, x, y));
}

void Mouse::leftreleased(int x, int y)
{
	this->leftDown = false;
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::LRelease, x, y));
}

void Mouse::rightPressed(int x, int y)
{
	this->rightDown = true;
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::RPress, x, y));
}

void Mouse::rightReleased(int x, int y)
{
	this->rightDown = false;
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::RRelease, x, y));
}

void Mouse::middlePressed(int x, int y)
{
	this->middleDown = true;
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::MPress, x, y));
}

void Mouse::middleReleased(int x, int y)
{
	this->leftDown = false;
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::MRelease, x, y));
}

void Mouse::wheelUp(int x, int y)
{
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::WheelUp, x, y));
}

void Mouse::wheelDown(int x, int y)
{
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::WheelDown, x, y));
}

void Mouse::mouseMove(int x, int y)
{
	this->x = x;
	this->y = y;
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::Move, x, y));
}

void Mouse::mousemoveRaw(int x, int y)
{
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::RAW_MOVE, x, y));
}

bool Mouse::isleftDown()
{
	return this->leftDown;
}

bool Mouse::ismiddleDown()
{
	return this->middleDown;
}

bool Mouse::isrightDown()
{
	return rightDown;
}

int Mouse::getPosX()
{
	return this->x;
}

int Mouse::getPosY()
{
	return this->y;
}

MousePoint Mouse::getPos()
{
	return { this->x, this->y };
}

bool Mouse::eventbufferisEmpty()
{
	return this->eventBuffer.empty();
}

MouseEvent Mouse::readEvent()
{
	if (this->eventBuffer.empty())
	{
		return MouseEvent();
	}
	else
	{
		MouseEvent e = this->eventBuffer.front(); // get first event from buffer
		this->eventBuffer.pop(); // remove first event from buffer
		return e;
	}
}
