#pragma once
#include "MouseEvent.h"
#include <queue>
class Mouse
{
public:
	void leftPressed(int x, int y);
	void leftreleased(int x, int y);
	void rightPressed(int x, int y);
	void rightReleased(int x, int y);
	void middlePressed(int x, int y);
	void middleReleased(int x, int y);
	void wheelUp(int x, int y);
	void wheelDown(int x, int y);
	void mouseMove(int x, int y);
	void mousemoveRaw(int x, int y);

	bool isleftDown();
	bool ismiddleDown();
	bool isrightDown();

	int getPosX();
	int getPosY();
	MousePoint getPos();

	bool eventbufferisEmpty();
	MouseEvent readEvent();
private:
	std::queue<MouseEvent> eventBuffer;
	bool leftDown = false;
	bool rightDown = false;
	bool middleDown = false;
	int x = 0;
	int y = 0;
};

