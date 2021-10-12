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

	char m_keyUp;
	char m_keyDown;

	bool m_isMouseClicked = false;
	bool m_isWindowClosed = false;

	int m_mouseButtonUp;
	int m_mouseButtonDown;

	Vector2D m_mousePosition;
};

