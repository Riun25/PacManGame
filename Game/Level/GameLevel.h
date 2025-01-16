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

	// ������Ʈ �Լ�
	virtual void Update(float _dTime) override;

	// ������ �׸��� �Լ�
	virtual void Draw() override;

	// �÷��̾ �̵��� �������� Ȯ���ϴ� �Լ�
	bool CanPlayerMove(const Vector2& _pos);

private:
	// �ڽ��� �ű� �� ������ Ŭ�����ߴ��� Ȯ���ϴ� �Լ�
	bool CheckGameClear();

private:
	// ��/�� ���� �迭
	List<DrawableActor*> mMapVec;

	// �ڽ� ����
	List<Box*> mBoxVec;

	// Ÿ�� ����
	List<Target*> mTargetVec;

	// �÷��̾� ����
	DrawableActor* player = nullptr;

	// ���� Ŭ���� ����
	bool mIsGameClear = false;
};