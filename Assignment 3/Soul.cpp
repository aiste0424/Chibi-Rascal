#include "Soul.h"
#include <iostream>

Soul::Soul(Screen& screen)
{
    m_state = -1;
    m_score = 0;
	m_image.Load("Assets/Images/Soul.png", screen);
    m_image.SetSpriteDimension(static_cast<int>(128 * 0.5), static_cast<int>(128 * 0.5));
    m_image.SetImageDimension(8, 3, 1024, 384);
    m_image.SetAnimationVelocity(0.4f);
    m_image.IsAnimated(true);
    m_image.IsAnimationLooping(true);
}

Soul::~Soul()
{
    m_image.Unload();
}

int Soul::GetState()
{
    return m_state;
}

void Soul::Update(Player& player, Score& score, Enemy& enemy)
{
    //if player attacks the soul while colliding
    if (m_collider.IsColliding(player.GetCollider()) && player.GetState() == Player::State::Attack)
    {
        if (enemy.GetHasStun() == true)
        {
            m_score = m_score - enemy.GetStun();
        }
        else if (enemy.GetHasStun() == false)
        {
            m_score++;
        } 
        m_position.x = 1 + (rand() % (1280 - m_image.GetSpriteDimension().x));
        m_position.y = 1 + (rand() % (720 - m_image.GetSpriteDimension().y));
        score.SetScore(m_score);
        
    }
    
    if (m_score < 0)
    {
        m_state = static_cast<int>(PlayButton::State::Loss);
    }
    //sets the collider, updates the collider and the animation
    m_collider.SetDimension(m_image.GetSpriteDimension().x, m_image.GetSpriteDimension().y);
    m_collider.SetPosition(m_position.x, m_position.y);
    m_collider.Update();
    m_image.Update();    
}

void Soul::Render(Screen& screen)
{
    m_image.Render(m_position.x, m_position.y, 0, screen, Sprite::Flip::NO_FLIP);
}
