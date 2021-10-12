#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "Player.h"
#include "BoxCollider.h"
#include "Score.h"
#include "Enemy.h"
#include "PlayButton.h"

class Soul : public GameObject
{

public:

	Soul(Screen& screen);
	~Soul();

	int GetState();
	void Update(Player& player, Score& score, Enemy& enemy);
	virtual void Render(Screen& screen);

private:

	Sprite m_image;
	BoxCollider m_collider;
	int m_score;
	int m_state;
};

