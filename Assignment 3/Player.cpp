#include "Player.h"
#include <iostream>

Player::Player(Screen& screen)
{
	m_velocity = 5;
	m_emptySpace = {60, 30};
	m_facingDirection = Direction::Right;
	m_state = State::Idle;

	m_images[static_cast<unsigned long long>(State::Idle)].Load("Assets/Images/Demon_Idle.png", screen);
	m_images[static_cast<unsigned long long>(State::Walk)].Load("Assets/Images/Demon_Walk.png", screen);
	m_images[static_cast<unsigned long long>(State::Death)].Load("Assets/Images/Demon_Death.png", screen);
	m_images[static_cast<unsigned long long>(State::Attack)].Load("Assets/Images/Demon_Attack.png", screen);
	m_images[static_cast<unsigned long long>(State::Up)].Load("Assets/Images/Demon_Walk_Top.png", screen);

	for (int i = 0; i < static_cast<int>(State::TotalStates); i++)
	{
		m_images[i].SetAnimationVelocity(0.3f);
		m_images[i].IsAnimationLooping(true);
		m_images[i].IsAnimated(true);
		m_collider[i].SetDimension(m_images[i].GetSpriteDimension().x, m_images[i].GetSpriteDimension().y);
	}

	m_images[static_cast<unsigned long long>(State::Idle)].SetSpriteDimension(100 * 1.5, 84 * 1.5);
	m_images[static_cast<unsigned long long>(State::Idle)].SetImageDimension(5, 1, 500, 84);
	
	m_images[static_cast<unsigned long long>(State::Death)].SetSpriteDimension(70 * 1.5, 140 * 1.5);
	m_images[static_cast<unsigned long long>(State::Death)].SetImageDimension(20, 1, 1400, 140);

	m_images[static_cast<unsigned long long>(State::Walk)].SetSpriteDimension(100 * 1.5, 84 * 1.5);
	m_images[static_cast<unsigned long long>(State::Walk)].SetImageDimension(8, 1, 800, 84);

	m_images[static_cast<unsigned long long>(State::Up)].SetSpriteDimension(74 * 1.5, 80 * 1.5);
	m_images[static_cast<unsigned long long>(State::Up)].SetImageDimension(8, 1, 592, 80);

	m_images[static_cast<unsigned long long>(State::Attack)].SetSpriteDimension(120 * 1.5, 100 * 1.5);
	m_images[static_cast<unsigned long long>(State::Attack)].SetImageDimension(11, 1, 1320, 100);
	m_images[static_cast<unsigned long long>(State::Attack)].SetAnimationVelocity(1.0f);
}

Player::~Player()
{
	m_images[static_cast<unsigned long long>(m_state)].Unload();
}

Player::State Player::GetState()
{
	return m_state;
}

BoxCollider& Player::GetCollider()
{
	return m_collider[static_cast<unsigned long long>(m_state)];
}

void Player::Update(Input& input)
{
	//walking in all 4 directions and checking screen bounds, so the player wouldn't leave the screen
	if (input.GetKeyDown() == SDL_SCANCODE_LEFT && m_position.x > 0)
	{
		m_direction.x = -1;
		m_direction.y = 0;
		m_facingDirection = Direction::Left;
		m_state = State::Walk;
	}
	else if (input.GetKeyDown() == SDL_SCANCODE_RIGHT && m_position.x + m_images[static_cast<unsigned long long>(m_state)].GetSpriteDimension().x < 1280)
	{
		m_direction.x = 1;
		m_direction.y = 0;
		m_facingDirection = Direction::Right;
		m_state = State::Walk;
	}
	else if (input.GetKeyDown() == SDL_SCANCODE_UP && m_position.y > 0)
	{
		m_direction.x = 0;
		m_direction.y = -1;
		m_state = State::Up;
	}
	else if (input.GetKeyDown() == SDL_SCANCODE_DOWN && m_position.y + m_images[static_cast<unsigned long long>(m_state)].GetSpriteDimension().y < 720)
	{
		m_direction.x = 0;
		m_direction.y = 1;
		m_state = State::Walk;
	}
	//idle
	else
	{
		m_direction.x = 0;
		m_direction.y = 0;
		m_state = State::Idle;
		
	}

	//attack
	if (input.GetKeyDown() == SDLK_SPACE)
	{
		m_state = State::Attack;
	}

	m_direction = m_direction.Scale(m_velocity);
	m_position = m_position.Add(m_direction);
	m_images[static_cast<unsigned long long>(m_state)].Update();

	//there's a lot of white space surrounding the actual colored sprite in the image
	//and taking it out from the calculation makes the collider more accurate
	m_collider[static_cast<unsigned long long>(m_state)].SetDimension(m_images[static_cast<unsigned long long>(m_state)].GetSpriteDimension().x - m_emptySpace.x, m_images[static_cast<unsigned long long>(m_state)].GetSpriteDimension().y - m_emptySpace.y);
	m_collider[static_cast<unsigned long long>(m_state)].SetPosition(m_position.x + m_emptySpace.x, m_position.y + m_emptySpace.y);
	m_collider[static_cast<unsigned long long>(m_state)].Update();
}

void Player::Render(Screen& screen)
{
	//renders the image and flips it left or right
	if (m_facingDirection == Direction::Right)
	{
		m_images[static_cast<unsigned long long>(m_state)].Render(m_position.x, m_position.y, 0, screen, Sprite::HORZ_FLIP);
	}
	else
	{
		m_images[static_cast<unsigned long long>(m_state)].Render(m_position.x, m_position.y, 0, screen, Sprite::NO_FLIP);
	}	
}
