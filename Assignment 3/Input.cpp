#include "Input.h"


void Input::Update()
{
	SDL_Event events;

	while (SDL_PollEvent(&events))
	{

		if (events.type == SDL_QUIT)
		{
			m_isWindowClosed = true;
		}

		else if (events.type == SDL_KEYDOWN)
		{
			m_keyDown = events.key.keysym.sym;
		}

		else if (events.type == SDL_KEYUP)
		{
			m_keyDown = NULL;
			m_keyUp = events.key.keysym.sym;
		}

		else if (events.type == SDL_MOUSEBUTTONDOWN)
		{
			m_isMouseClicked = true;
			m_mouseButtonDown = events.button.button;
		}

		else if (events.type == SDL_MOUSEBUTTONUP)
		{
			m_isMouseClicked = false;
			m_mouseButtonUp = events.button.button;
		}

		else if (events.type == SDL_MOUSEMOTION)
		{
			m_mousePosition.x = events.motion.x;
			m_mousePosition.y = events.motion.y;
		}
	}
}


char Input::GetKeyUp()
{
	return m_keyUp;
}

char Input::GetKeyDown()
{
	return m_keyDown;
}

bool Input::IsMouseClicked()
{
	return m_isMouseClicked;
}

bool Input::IsWindowClosed()
{
	return m_isWindowClosed;
}

Vector2D& Input::GetMousePosition()
{
	return m_mousePosition;
}
