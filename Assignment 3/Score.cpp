#include "Score.h"

Score::Score()
{
	m_score = 0;
	m_text.Load("Assets/Fonts/font.ttf", 100);
	m_text.SetColor(9, 11, 71, 250);
	m_text.SetDimension(70, 70);
}

Score::~Score()
{
	m_text.Unload();
}

int Score::GetScore()
{
	return m_score;
}

void Score::SetScore(int score)
{
	m_score = score;
	m_text.SetText(std::to_string(m_score));
}

void Score::Render(Screen& screen)
{
	m_text.Render(10, 10, screen);
}
