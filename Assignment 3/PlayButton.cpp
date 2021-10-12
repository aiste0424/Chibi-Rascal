#include "PlayButton.h"


PlayButton::PlayButton(Screen& screen)
{
	m_state = State::MainMenu;
	m_image.Load("Assets/Images/play.png", screen);
	m_image.SetSpriteDimension(150, 150);
	m_image.SetImageDimension(1, 1, 300, 300);
	m_image.IsAnimated(false);
}

PlayButton::~PlayButton()
{
	m_image.Unload();
}

void PlayButton::Update(Input& input)
{
	if (abs(input.GetMousePosition().x - ((m_position.x + 75))) <= 75 &&
		abs(input.GetMousePosition().y - ((m_position.y + 75))) <= 75)
	{
		if (input.IsMouseClicked() == true)
		{
			m_state = State::Gameplay;
		}
	}
}

PlayButton::State PlayButton::GetState()
{
	return m_state;
}

void PlayButton::Render(Screen& screen)
{
	m_image.Render(m_position.x, m_position.y, 0, screen, Sprite::Flip::NO_FLIP);
}
