#pragma once
#include "BoxCollider.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Player.h"
#include "Score.h"

enum class State
{
	Idle,
	Walk,
	Attack,
	Death,
	TotalStates
};
enum class Direction
{
	Left,
	Right
};
class Enemy : public GameObject
{
public:

	

	Enemy(Screen& screen);
	~Enemy();
	State GetState();
	void SetState(State state);
	const BoxCollider& GetCollider() const;
	int GetStun();
	bool GetHasStun();
	void Update(Player& player, Score& score);
	virtual void Render(Screen& screen);

private:

	State m_state;
	Sprite m_images[static_cast<unsigned long long>(State::TotalStates)];
	BoxCollider m_collider[static_cast<unsigned long long>(State::TotalStates)];
	Direction m_facingDirection;

	int m_collidingFrames;
	int m_frames;
	int m_stun;
	bool m_hasStun;

	Vector2D m_emptySpace;
	Vector2D m_direction;
};

