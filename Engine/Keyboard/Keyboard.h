#pragma once
#include "KeyBoardEvent.h"
#include <queue>
class Keyboard
{
public:
	Keyboard();
	bool keyisPressed(const unsigned char keycode);
	bool keybufferisEmpty();
	bool charbufferisEmpty();
	keyboardEvent readKey();
	unsigned char readChar();
	void onkeyPressed(const unsigned char key);
	void onkeyReleased(const unsigned char key);
	void onChar(const unsigned char key);
	void enableautorepeatKeys();
	void disableautorepeatKeys();
	void enableautorepeatChars();
	void disableautorepeatChars();
	bool iskeyautoRepeat();
	bool ischarsautoRepeat();
private:
	bool autoRepeatkeys = false;
	bool autoRepeatchars = false;
	bool keyStates[256];
	std::queue<keyboardEvent> keyBuffer;
	std::queue<unsigned char> charBuffer;
};

