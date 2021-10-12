#pragma once
#include "Vector2D.h"

class BoxCollider
{

public:

	Vector2D GetMin();
	Vector2D GetMax();

	void SetPosition(int x, int y);
	void SetDimension(int width, int height);

	void Update();
	bool IsColliding(BoxCollider& secondBox);

private:

	Vector2D m_min;
	Vector2D m_max;
	Vector2D m_position;
	Vector2D m_dimension;
};
