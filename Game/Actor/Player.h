#pragma once

#include "Actor/DrawableActor.h"

// ���� ���� ���� ����
class GameLevel;
class Player : public DrawableActor
{
	RTTI_DECLARATIONS(Player, DrawableActor)
public:
	Player(const Vector2& _pos, GameLevel* _level);

	virtual void Update(float _dTime) override;

	void PlayerMove();

private:
	// ���� ������ �����ϴ� ����
	GameLevel* refLevel = nullptr;

	// �������� �Ծ ���� ���������� ��Ÿ���� ����
	// Todo : ������ ��� �߰��� �� ������ ��
	bool mIsGhostEatable = false;
};