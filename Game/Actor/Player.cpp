#include "Player.h"
#include "Engine/Engine.h"
#include "Engine/InputManager.h"
#include "Level/GameLevel.h"

Player::Player(const Vector2& _pos, GameLevel* _level)
	:DrawableActor("P"), refLevel(_level)
{
	// ��ġ ����
	pos = _pos;

	// ���� ����
	color = COLOR::MAGENTA;
}

void Player::Update(float _dTime)
{
	Super::Update(_dTime);

	// ESC ����
	if (InputManager::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
	}

	// �����¿�
	if (InputManager::Get().GetKeyDown(VK_LEFT))
	{
		// �̵� �������� Ȯ��
		if (refLevel->CanPlayerMove(Vector2(pos.x - 1, pos.y)))
		{
			pos.x -= 1;
		}
		//pos.x -= 1;
		//pos.x = pos.x < 0 ? 0 : pos.x;
	}

	if (InputManager::Get().GetKeyDown(VK_RIGHT))
	{
		// �̵� �������� Ȯ��
		if (refLevel->CanPlayerMove(Vector2(pos.x + 1, pos.y)))
		{
			pos.x += 1;
		}
		//pos.x += 1;
		//pos.x = pos.x <= Engine::Get().ScreenSize().x ? pos.x : Engine::Get().ScreenSize().x;
	}

	if (InputManager::Get().GetKeyDown(VK_UP))
	{
		// �̵� �������� Ȯ��
		if (refLevel->CanPlayerMove(Vector2(pos.x, pos.y - 1)))
		{
			pos.y -= 1;
		}
		//pos.y -= 1;
		//pos.y = pos.y < 0 ? 0 : pos.y;
	}

	if (InputManager::Get().GetKeyDown(VK_DOWN))
	{
		// �̵� �������� Ȯ��
		if (refLevel->CanPlayerMove(Vector2(pos.x, pos.y + 1)))
		{
			pos.y += 1;
		}
		//pos.y += 1;
		//pos.y = pos.y <= Engine::Get().ScreenSize().y ? pos.y : Engine::Get().ScreenSize().y;
	}
}