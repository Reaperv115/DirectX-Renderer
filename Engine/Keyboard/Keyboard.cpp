#include "Keyboard.h"

Keyboard::Keyboard()
{
	for (int i = 0; i < 256; ++i)
		this->keyStates[i] = false;
}

bool Keyboard::keyisPressed(const unsigned char keycode)
{
	return this->keyStates[keycode];
}

bool Keyboard::keybufferisEmpty()
{
	return this->keyBuffer.empty();
}

bool Keyboard::charbufferisEmpty()
{
	return this->charBuffer.empty();
}

keyboardEvent Keyboard::readKey()
{
	if (this->keyBuffer.empty())
	{
		return keyboardEvent();
	}
	else
	{
		keyboardEvent e = this->keyBuffer.front();
		this->keyBuffer.pop();
		return e;
	}
}

unsigned char Keyboard::readChar()
{
	if (this->charBuffer.empty())
	{
		return 0u;
	}
	else
	{
		unsigned char e = this->charBuffer.front();
		this->charBuffer.pop();
		return e;
	}
}

void Keyboard::onkeyPressed(const unsigned char key)
{
	this->keyStates[key] = true;
	this->keyBuffer.push(keyboardEvent(keyboardEvent::EventType::Press, key));
}

void Keyboard::onkeyReleased(const unsigned char key)
{
	this->keyStates[key] = false;
	this->keyBuffer.push(keyboardEvent(keyboardEvent::EventType::Release, key));
}

void Keyboard::onChar(const unsigned char key)
{
	this->charBuffer.push(key);
}

void Keyboard::enableautorepeatChars()
{
	this->autoRepeatchars = true;
}

void Keyboard::enableautorepeatKeys()
{
	this->autoRepeatkeys = true;
}

void Keyboard::disableautorepeatChars()
{
	this->autoRepeatchars = false;
}

void Keyboard::disableautorepeatKeys()
{
	this->autoRepeatchars = false;
}

bool Keyboard::iskeyautoRepeat()
{
	return this->autoRepeatkeys;
}

bool Keyboard::ischarsautoRepeat()
{
	return this->autoRepeatchars;
}