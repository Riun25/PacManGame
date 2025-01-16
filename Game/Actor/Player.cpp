#include "Player.h"
#include "Engine/Engine.h"
#include "Engine/InputManager.h"
#include "Level/GameLevel.h"
#include "Game/Game.h"
#include "Enemy.h"

Player::Player(const Vector2& _pos, GameLevel* _level)
	:DrawableActor("��"), refLevel(_level)
{
	// ��ġ ����
	pos = _pos;

	// ���� ����
	color = COLOR::YELLOW;
}

void Player::Update(float _dTime)
{
	Super::Update(_dTime);

	// ESC ����
	if (InputManager::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().ToggleMenu();
	}

	// �÷��̾� �Է� ó��
	PlayerMove();
}

void Player::PlayerMove()
{
	// �����¿�
	if (InputManager::Get().GetKeyDown(VK_LEFT))
	{
		// �̵� �������� Ȯ��
		if (refLevel->CanPlayerMove(Vector2(pos.x - 1, pos.y)))
		{
			pos.x -= 1;
		}
	}

	if (InputManager::Get().GetKeyDown(VK_RIGHT))
	{
		// �̵� �������� Ȯ��
		if (refLevel->CanPlayerMove(Vector2(pos.x + 1, pos.y)))
		{
			pos.x += 1;
		}
	}

	if (InputManager::Get().GetKeyDown(VK_UP))
	{
		// �̵� �������� Ȯ��
		if (refLevel->CanPlayerMove(Vector2(pos.x, pos.y - 1)))
		{
			pos.y -= 1;
		}
	}

	if (InputManager::Get().GetKeyDown(VK_DOWN))
	{
		// �̵� �������� Ȯ��
		if (refLevel->CanPlayerMove(Vector2(pos.x, pos.y + 1)))
		{
			pos.y += 1;
		}
	}
}
