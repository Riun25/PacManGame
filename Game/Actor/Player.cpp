#include "Player.h"
#include "Engine/Engine.h"
#include "Engine/InputManager.h"
#include "Level/GameLevel.h"

Player::Player(const Vector2& _pos, GameLevel* _level)
	:DrawableActor("P"), refLevel(_level)
{
	// 위치 설정
	pos = _pos;

	// 색상 설정
	color = COLOR::MAGENTA;
}

void Player::Update(float _dTime)
{
	Super::Update(_dTime);

	// ESC 종료
	if (InputManager::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
	}

	// 상하좌우
	if (InputManager::Get().GetKeyDown(VK_LEFT))
	{
		// 이동 가능한지 확인
		if (refLevel->CanPlayerMove(Vector2(pos.x - 1, pos.y)))
		{
			pos.x -= 1;
		}
		//pos.x -= 1;
		//pos.x = pos.x < 0 ? 0 : pos.x;
	}

	if (InputManager::Get().GetKeyDown(VK_RIGHT))
	{
		// 이동 가능한지 확인
		if (refLevel->CanPlayerMove(Vector2(pos.x + 1, pos.y)))
		{
			pos.x += 1;
		}
		//pos.x += 1;
		//pos.x = pos.x <= Engine::Get().ScreenSize().x ? pos.x : Engine::Get().ScreenSize().x;
	}

	if (InputManager::Get().GetKeyDown(VK_UP))
	{
		// 이동 가능한지 확인
		if (refLevel->CanPlayerMove(Vector2(pos.x, pos.y - 1)))
		{
			pos.y -= 1;
		}
		//pos.y -= 1;
		//pos.y = pos.y < 0 ? 0 : pos.y;
	}

	if (InputManager::Get().GetKeyDown(VK_DOWN))
	{
		// 이동 가능한지 확인
		if (refLevel->CanPlayerMove(Vector2(pos.x, pos.y + 1)))
		{
			pos.y += 1;
		}
		//pos.y += 1;
		//pos.y = pos.y <= Engine::Get().ScreenSize().y ? pos.y : Engine::Get().ScreenSize().y;
	}
}