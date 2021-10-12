#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "Screen.h"
#include "Input.h"
#include "Player.h"


class PlayButton : public GameObject
{ 
public:

	enum class State
	{
		MainMenu,
		Gameplay,
		Loss,
		Win
	};

	PlayButton(Screen& screen);
	~PlayButton();

	virtual void Render(Screen& screen);
	void Update(Input& input);
	State GetState();

private:

	Sprite m_image;
	State m_state;
};

