#pragma once
#include <string>
#include <SDL_ttf.h>
#include "Screen.h"
#include "Vector2D.h"

class Text
{

public:

	Text();

	static bool Initialize();

	bool Load(const std::string& filename, int fontSize);

	static void Shutdown();

	void SetText(const std::string text);
	void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void SetDimension(int width, int height);
	void Render(int xPos, int yPos, Screen& screen);
	void Unload();

private:

	bool m_isDirty;
	std::string m_text;

	TTF_Font* m_font;
	SDL_Color m_color;
	Vector2D m_dimension;
	SDL_Texture* m_texture;
};

