#include "Enemy.h"
#include <iostream>
#include "Player.h"

Enemy::Enemy(Screen& screen)
{
    m_frames = 0;
    m_collidingFrames = 0;
    m_emptySpace = {15, 10};
    m_stun = -1;
    m_hasStun = false;

    m_state = State::Idle;
    m_facingDirection = Direction::Left;
    
    m_images[static_cast<int>(State::Attack)].Load("Assets/Images/Reaper_Attack.png", screen);
    m_images[static_cast<int>(State::Idle)].Load("Assets/Images/Reaper_Idle.png", screen);
    m_images[static_cast<int>(State::Walk)].Load("Assets/Images/Reaper_Run.png", screen);

    m_images[static_cast<int>(State::Attack)].SetImageDimension(10, 1, 480, 48);
    m_images[static_cast<int>(State::Idle)].SetImageDimension(5, 1, 240, 48);
    m_images[static_cast<int>(State::Walk)].SetImageDimension(8, 1, 384, 48);

    for (int i = 0; i < static_cast<int>(State::TotalStates); i++)
    {
        m_images[i].SetSpriteDimension(48 * 3, 48 * 3);
        m_images[i].IsAnimated(true);
        m_images[i].IsAnimationLooping(true);
        m_images[i].SetAnimationVelocity(0.2f);
    }
}

Enemy::~Enemy()
{
    m_images[static_cast<int>(m_state)].Unload();
}

State Enemy::GetState()
{
    return m_state;
}

void Enemy::SetState(State state)
{
    m_state = state;
}

const BoxCollider& Enemy::GetCollider() const
{
    return m_collider[static_cast<int>(m_state)];
}

int Enemy::GetStun()
{
    return m_stun;
}

bool Enemy::GetHasStun()
{
    return m_hasStun;
}

void Enemy::Update(Player& player, Score& score)
{
    //if player collides with the enemy, enemy stops following and gets stunned
    if (m_collider[static_cast<int>(m_state)].IsColliding(player.GetCollider()))
    {
        m_collidingFrames++;
        if (m_collidingFrames >= 100)
        {
            m_collidingFrames = 0;
            m_stun += 1;
        }
        else if (m_collidingFrames <= 100 && player.GetState() == Player::State::Attack)
        {
            m_collidingFrames = 0;
            m_state = State::Idle;
            m_hasStun = true;
        }
    }
    
    //if stunned and the timer isn't finished yet, stay stunned
    if (m_state == State::Idle && m_frames <= 500)
    {
        if (m_frames == 1)
        {
            m_stun += 1;
            
        }
        m_direction = { 0, 0 };
        m_frames++;
    }
    //else move and follow player
    else
    {
        //counter for how many frames the enemy needs to wait until it can move again
        m_frames = 0;
        m_hasStun = false;
        //left and right
        if (m_position.x < player.GetPosition().x)
        {
            m_position.x += 1;
            m_facingDirection = Direction::Left;
            m_state = State::Walk;
        }
        else if (m_position.x > player.GetPosition().x)
        {
            m_position.x -= 1;
            m_facingDirection = Direction::Right;
            m_state = State::Walk;
        }
        //up and down
        if (m_position.y < player.GetPosition().y)
        {
            m_position.y += 1;
            m_state = State::Walk;
        }
        else if (m_position.y > player.GetPosition().y)
        {
            m_position.y -= 1;
            m_state = State::Walk;
        }
    }

    m_images[static_cast<int>(m_state)].Update();
    //there's a lot of white space surrounding the actual colored sprite in the image
    //and taking it out from the calculation makes the collider more accurate
    m_collider[static_cast<int>(m_state)].SetDimension(m_images[static_cast<int>(m_state)].GetSpriteDimension().x - m_emptySpace.x, m_images[static_cast<int>(m_state)].GetSpriteDimension().y - m_emptySpace.y);
    m_collider[static_cast<int>(m_state)].SetPosition(m_position.x + m_emptySpace.x, m_position.y + m_emptySpace.y);
    m_collider[static_cast<int>(m_state)].Update();
}
//renders and flips the image in the right direction
void Enemy::Render(Screen& screen)
{
    if (m_facingDirection == Direction::Right)
    {
        m_images[static_cast<int>(m_state)].Render(m_position.x, m_position.y, 0, screen, Sprite::Flip::HORZ_FLIP);
    }
    else
    {
        m_images[static_cast<int>(m_state)].Render(m_position.x, m_position.y, 0, screen, Sprite::Flip::NO_FLIP);
    }
}
