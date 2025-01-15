#pragma once

#include "Level/Level.h"
#include "Math/Vector2.h"

// ���ڹ� ���� ����
class DrawableActor;
class Player;
class Box;
class Target;
class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel, Level)
public:
	GameLevel();

	// ������ �׸��� �Լ�
	virtual void Draw() override;

	// �÷��̾ �̵��� �������� Ȯ���ϴ� �Լ�
	bool CanPlayerMove(const Vector2& _pos);

private:
	// ��/�� ���� �迭
	List<DrawableActor*> mMapVec;

	// �ڽ� ����
	List<Box*> mBoxVec;

	// Ÿ�� ����
	List<Target*> mTargetVec;

	// �÷��̾� ����
	DrawableActor* player = nullptr;
};