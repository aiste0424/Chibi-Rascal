#pragma once

class Vector2D
{

public:

	Vector2D(int x = 0, int y = 0);

	Vector2D Add(const Vector2D& second);
	Vector2D Subtract(const Vector2D& second);
	Vector2D Scale(int second);

	int Magnitude();
	int Distance(const Vector2D& second);

	int x;
	int y;
};

