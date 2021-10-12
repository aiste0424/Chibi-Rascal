#pragma once
#include <SDL.h>
#include "Vector2D.h"
#include "Screen.h"
#include "Input.h"

//Abstract base class - any class with at least 1 pure virtual function
//A virtual function is a member function that you expect to be redefined in derived classes.

class GameObject
{

public:

	const Vector2D& GetPosition() const;
	void SetPosition(const Vector2D& position);
	virtual void Render(Screen& screen) = 0;

protected:

	Vector2D m_position;
};

