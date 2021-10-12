#include "Vector2D.h"
#include <math.h>

//magnitude - the size/length of the vector
//direction
//scalar - a mere number without a direction

Vector2D::Vector2D(int x, int y)
{
	this->x = x;
	this->y = y;
}

//adding two vectors gives a total length from the start of the first vector
//to the end of the second one
Vector2D Vector2D::Add(const Vector2D& second)
{
	Vector2D result;

	result.x = x + second.x;
	result.y = y + second.y;

	return result;
}

//the same as adding two vectors, but the second vector will have the opposite direction
//than compared to when adding
Vector2D Vector2D::Subtract(const Vector2D& second)
{
	Vector2D result;

	result.x = x - second.x;
	result.y = y - second.y;

	return result;
}

//simple scaling
Vector2D Vector2D::Scale(int second)
{
	Vector2D result;

	result.x = x * second;
	result.y = y * second;

	return result;
}

//size
int Vector2D::Magnitude()
{
	double x = static_cast<double>(this->x);
	double y = static_cast<double>(this->y);

	return static_cast<int>(sqrt((x * x) + (y * y)));
}

int Vector2D::Distance(const Vector2D& second)
{
	Vector2D temp = Subtract(second);
	return static_cast<int>(temp.Magnitude());
}
