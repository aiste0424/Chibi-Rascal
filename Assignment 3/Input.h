#pragma once
#include <SDL.h>
#include "Vector2D.h"

class Input
{

public:

	void Update();

	char GetKeyUp();
	char GetKeyDown();

	bool IsMouseClicked();
	bool IsWindowClosed();

	Vector2D& GetMousePosition();

private:

	char m_keyUp = '\0';
	char m_keyDown = '\0';

	bool m_isMouseClicked = false;
	bool m_isWindowClosed = false;

	int m_mouseButtonUp = 0;
	int m_mouseButtonDown = 0;

	Vector2D m_mousePosition;
};

