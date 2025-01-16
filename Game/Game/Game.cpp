#include "Game.h"

#include "Level/MenuLevel.h"

Game* Game::instance = nullptr;

Game::Game()
	: Engine()
{
	instance = this;

	menuLevel = new MenuLevel();
}

Game::~Game()
{
	if (showMenu)
	{
		delete backLevel;
		backLevel = nullptr;
		mMainLevel = nullptr;
	}
	else
	{
		delete mMainLevel;
		mMainLevel = nullptr;
	}

	delete menuLevel;
	menuLevel = nullptr;
}

void Game::ToggleMenu()
{
	system("cls");
	//Clear();
	showMenu = !showMenu;
	if (showMenu)
	{
		backLevel = mMainLevel;
		mMainLevel = menuLevel;
	}
	else
	{
		mMainLevel = backLevel;
	}
}