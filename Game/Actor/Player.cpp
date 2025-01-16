#include "Player.h"
#include "Engine/Engine.h"
#include "Engine/InputManager.h"
#include "Level/GameLevel.h"
#include "Game/Game.h"
#include "Enemy.h"

Player::Player(const Vector2& _pos, GameLevel* _level)
	:DrawableActor("●"), refLevel(_level)
{
	// 위치 설정
	pos = _pos;

	// 색상 설정
	color = COLOR::YELLOW;
}

void Player::Update(float _dTime)
{
	Super::Update(_dTime);

	// ESC 종료
	if (InputManager::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().ToggleMenu();
	}

	// 플레이어 입력 처리
	PlayerMove();
}

void Player::PlayerMove()
{
	// 상하좌우
	if (InputManager::Get().GetKeyDown(VK_LEFT))
	{
		// 이동 가능한지 확인
		if (refLevel->CanPlayerMove(Vector2(pos.x - 1, pos.y)))
		{
			pos.x -= 1;
		}
	}

	if (InputManager::Get().GetKeyDown(VK_RIGHT))
	{
		// 이동 가능한지 확인
		if (refLevel->CanPlayerMove(Vector2(pos.x + 1, pos.y)))
		{
			pos.x += 1;
		}
	}

	if (InputManager::Get().GetKeyDown(VK_UP))
	{
		// 이동 가능한지 확인
		if (refLevel->CanPlayerMove(Vector2(pos.x, pos.y - 1)))
		{
			pos.y -= 1;
		}
	}

	if (InputManager::Get().GetKeyDown(VK_DOWN))
	{
		// 이동 가능한지 확인
		if (refLevel->CanPlayerMove(Vector2(pos.x, pos.y + 1)))
		{
			pos.y += 1;
		}
	}
}
