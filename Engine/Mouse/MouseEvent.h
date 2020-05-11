#pragma once
struct MousePoint
{
	int x;
	int y;
};

class MouseEvent
{
public:
	enum class EventType
	{
		LPress,
		LRelease,
		RPress,
		RRelease,
		MPress,
		MRelease,
		WheelUp,
		WheelDown,
		Move,
		RAW_MOVE,
		Invalid
	};
private:
	EventType type;
	int x;
	int y;
public:
	MouseEvent();
	MouseEvent(const EventType type, const int x, const int y);
	bool isValid() const;
	EventType getType() const;
	MousePoint getPos() const;
	int GetPosX() const;
	int GetPosY() const;
};

