#pragma once
#include "GameObject.h"
#include "Text.h"

class Score : public GameObject
{

public:

	Score();
	~Score();

	int GetScore();
	void SetScore(int score);
	virtual void Render(Screen& screen);

private:

	int m_score;
	Text m_text;
};

