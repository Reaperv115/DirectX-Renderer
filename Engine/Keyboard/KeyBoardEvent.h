#pragma once

class keyboardEvent
{
public:
	enum class EventType
	{
		Press,
		Release,
		Invalid
	};

	keyboardEvent();
	keyboardEvent(const EventType type, const unsigned char key);
	bool IsPress() const;
	bool IsRelease() const;
	bool IsValid() const;
	unsigned char GetkeyCode() const;

private:
	EventType type;
	unsigned char key;
};