#pragma once
#include "Score.h"
#include "Sprite.h"
#include "Player.h"
#include "GameObject.h"
#include "BoxCollider.h"

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

	int GetStun();
	State GetState();
	bool GetHasStun();
	const BoxCollider& GetCollider() const;

	void SetState(State state);
	
	virtual void Render(Screen& screen);
	void Update(Player& player, Score& score);
	
private:

	State m_state;
	Direction m_facingDirection;
	Sprite m_images[static_cast<unsigned long long>(State::TotalStates)];
	BoxCollider m_collider[static_cast<unsigned long long>(State::TotalStates)];
	
	int m_stun;
	int m_frames;
	int m_collidingFrames;
	
	bool m_hasStun;

	Vector2D m_direction;
	Vector2D m_emptySpace;
};

