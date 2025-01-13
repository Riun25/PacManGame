#include "Game.h"
#include "Engine/InputManager.h"

Game::Game()
{
	// 커서 안보이게 설정
	InputManager::Get().SetCursorType(CURSOR_TYPE::NONE);
}

Game::~Game()
{
}
