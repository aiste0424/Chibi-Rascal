#include <iostream>
#include "Sprite.h"
#include <SDL_image.h>
#include "Player.h"

Sprite::Sprite()
{
	m_image = nullptr;
	m_animationVelocity = 0.0f;
	m_imageCel = 0;
	m_isAnimated = false;
	m_isAnimationDead = false;
	m_isAnimationLooping = false;

	m_celDimension = { 0, 0 };
	m_imageDimension = { 0, 0 };
	m_spriteDimension = { 0, 0 };
}


void Sprite::IsAnimated(bool flag)
{
	m_isAnimated = flag;
}

void Sprite::IsAnimationLooping(bool flag)
{
	m_isAnimationLooping = flag;
}

//gives a number of the frame/placement the right image is in
void Sprite::SetImageCel(int column, int row)
{
	m_imageCel = ((row - 1) * m_imageDimension.x) + (column - 1);
}
//speed
void Sprite::SetAnimationVelocity(float velocity)
{
	m_animationVelocity = velocity;
}

//This is the resolution of the sprite image as it will appear on-screen
void Sprite::SetSpriteDimension(float width, float height)
{
	m_spriteDimension.x = width;
	m_spriteDimension.y = height;
}

Vector2D Sprite::GetSpriteDimension()
{
	return m_spriteDimension;
}

//This is the resolution and col/row dimensions of the sprite image as it is stored in the Assets folder
void Sprite::SetImageDimension(int columns, int rows, int width, int height)
{
	m_imageDimension.x = columns;
	m_imageDimension.y = rows;

	m_celDimension.x = width / columns;
	m_celDimension.y = height / rows;
}

Vector2D Sprite::GetImageDimension()
{
	return m_imageDimension;
}

bool Sprite::Load(const std::string& filename, Screen& screen)
{
	SDL_Surface* rawImageData = IMG_Load(filename.c_str());

	if (!rawImageData)
	{
		std::cout << "Error loading image file." << std::endl;
		return false;
	}

	m_image = SDL_CreateTextureFromSurface(screen.GetRenderer(), rawImageData);

	return true;
}

void Sprite::Unload()
{
	SDL_DestroyTexture(m_image);
}

void Sprite::Update()
{

	if (m_isAnimated)
	{

		static float total = 0.0f;
		total += 0.1f;

		m_imageCel = static_cast<int>(total * m_animationVelocity) % (m_imageDimension.x * m_imageDimension.y);

		if (!m_isAnimationLooping && m_imageCel == (m_imageDimension.x * m_imageDimension.y - 1))
		{
			m_isAnimationDead = true;
		}
		
	}
}

void Sprite::Render(int xPos, int yPos, double angle, Screen& screen, Flip flip)
{
	if (!m_isAnimationDead)
	{
		SDL_Rect sourceRect;
		SDL_Rect targetRect;

		sourceRect.x = (m_imageCel % m_imageDimension.x) * m_celDimension.x;
		sourceRect.y = (m_imageCel / m_imageDimension.x) * m_celDimension.y;
		sourceRect.w = m_celDimension.x;
		sourceRect.h = m_celDimension.y;

		targetRect.x = xPos;
		targetRect.y = yPos;
		targetRect.w = m_spriteDimension.x;
		targetRect.h = m_spriteDimension.y;

		SDL_Point centre{ m_spriteDimension.x, m_spriteDimension.y};

		SDL_RenderCopyEx(screen.GetRenderer(), m_image, &sourceRect, &targetRect, angle, &centre, static_cast<SDL_RendererFlip>(flip));
	}
}
