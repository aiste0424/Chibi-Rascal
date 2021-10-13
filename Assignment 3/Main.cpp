#include <iostream>
#include <SDL.h>
#include "Screen.h"
#include "Input.h"
#include "Sprite.h"
#include "Player.h"
#include "Vector2D.h"
#include "Enemy.h"
#include "Soul.h"
#include "Score.h"
#include "PlayButton.h"

bool isGameRunning = true;

int main(int argc, char* argv[])
{
	Input input;
	Sprite rules;
	Screen screen;
	Sprite gameOver;
	Sprite mainMenu;
	Sprite background;
	
	Text::Initialize();
	if (!screen.Initialize("Chibi Rascal"))
	{
		return 0;
	}

	background.IsAnimated(false);
	background.SetSpriteDimension(1280, 720);
	background.SetImageDimension(1, 1, 1280, 720);
	background.Load("Assets/Images/Background.png", screen);

	rules.IsAnimated(false);
	rules.SetSpriteDimension(1280, 720);
	rules.SetImageDimension(1, 1, 1280, 720);
	rules.Load("Assets/Images/rules.png", screen);

	gameOver.Load("Assets/Images/Game_Over.png", screen);
	gameOver.SetSpriteDimension(1280, 720);
	gameOver.SetImageDimension(1, 1, 1280, 720);
	gameOver.IsAnimated(false);

	Player player(screen);
	Enemy enemy(screen);
	Soul soul(screen);
	Score* score = new Score;
	PlayButton button(screen);
	button.SetPosition({ 565, 285 });
	player.SetPosition({50, 400});
	enemy.SetPosition({ 100, 100 });
	soul.SetPosition({ 500, 500 });

	//GAMEPLAY LOOP
	
	
	int GameState = 0;
	while (isGameRunning == true)
	{
		screen.Clear();
		input.Update();

		if (input.IsWindowClosed())
		{
			isGameRunning = false;
		}
		if (input.GetKeyDown() == SDLK_ESCAPE)
		{
			isGameRunning = false;
		}
		
		switch (GameState)
		{
			//main menu
		case 0:


			player.SetPosition({ 50, 400 });

			rules.Render(0, 0, 0.0, screen);
			button.Render(screen);
			button.SetPosition({ 1000, 400 });
			button.Update(input);
			if (button.GetState() == PlayButton::State::Gameplay)
			{
				GameState = 1;
			}
			break;
		//gameplay
		case 1:

			background.Render(0, 0, 0.0, screen);
			player.Render(screen);
			enemy.Render(screen);
			soul.Render(screen);
			score->Render(screen);
			player.Update(input);
			enemy.Update(player, *score);
			soul.Update(player, *score, enemy);
			if (soul.GetState() == static_cast<int>(PlayButton::State::Loss))
			{
				GameState = 2;
			}
			
			break;
		//game over
		case 2:

			gameOver.Render(0, 0, 0.0, screen);
			
			break;
		}


		
		input.Update();
		
		screen.Present();
	}
	delete score;
	
	Text::Shutdown();
	background.Unload();
	screen.Shutdown();

	return 0;
}