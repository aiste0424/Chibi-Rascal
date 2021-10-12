#pragma once
#include <string>
#include <SDL.h>
#include "Screen.h"
#include "Vector2D.h"

class Sprite
{
public:

	enum Flip
	{
		NO_FLIP = SDL_FLIP_NONE,
		HORZ_FLIP = SDL_FLIP_HORIZONTAL,
	};

	Sprite();

	void IsAnimated(bool flag);
	void IsAnimationLooping(bool flag);
	void SetAnimationVelocity(float velocity);
	void SetImageCel(int column, int row);
	void SetSpriteDimension(float width, float height);
	void SetImageDimension(int columns, int rows, int width, int height);

	Vector2D GetSpriteDimension();
	Vector2D GetImageDimension();
	
	bool Load(const std::string& filename, Screen& screen);

	void Unload();
	void Update();
	void Render(int xPos, int yPos, double angle, Screen& screen, Flip flip = NO_FLIP);

private:

	int m_imageCel;
	float m_animationVelocity;

	bool m_isAnimated;
	bool m_isAnimationDead;
	bool m_isAnimationLooping;

	SDL_Texture* m_image;
	Vector2D m_celDimension;
	Vector2D m_imageDimension;
	Vector2D m_spriteDimension;
};

