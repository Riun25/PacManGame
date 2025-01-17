#pragma once

#include "Level/Level.h"
#include "Math/Vector2.h"
#include <vector>
#include <string>

// �� ���� �̳�
enum class MAPDATA
{
	CTEST,	// �浹 �׽�Ʈ
	CITEST,	// ������ �� �浹 �׽�Ʈ
	ETEST,	// ���� ������ �׽�Ʈ
	STATGE1,
	STATGE2,
	STATGE3,
	LENGTH,
};

// �Ѹ� ���� ����
class DrawableActor;
class Player;
class Enemy;
class Item;
class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel, Level)
public:
	GameLevel(int _mapNum = 0, int _score = 0);

	// ���������� �ε��ϴ� �Լ�
	void LoadMap(const int _stageNum);

	// ������Ʈ �Լ�
	virtual void Update(float _dTime) override;

	virtual void Finalize() override;


	// ������ �׸��� �Լ�
	virtual void Draw() override;

	// �÷��̾ �̵��� �������� Ȯ���ϴ� �Լ�
	bool CanPlayerMove(const Vector2& _pos);
	// ������ �̵��� �������� Ȯ���ϴ� �Լ�
	bool CanEnemyMove(const Vector2& _pos);
	
	// �÷��̾�� ������ �浹�ϴ��� Ȯ���ϴ� �Լ�
	void ProcessCollisionPlayerAndEnemy();

private:
	// �ڽ��� �ű� �� ������ Ŭ�����ߴ��� Ȯ���ϴ� �Լ�
	bool CheckGameClear();

private:
	// ��/�� ���� �迭
	List<DrawableActor*> mMapVec;
	// ���� ����
	List<Enemy*> mEnemyVec;
	// ������ ����
	List<Item*> mItemVec;
	// �÷��̾� ����
	DrawableActor* player = nullptr;

	// ���� Ŭ���� ����
	bool mIsGameClear = false;
	// ���� ���� ����
	int mScore = 0;

	// ���� ����
	int mPrayNum = 0;
	// ��ȯ�� ����
	int mChangingNum = 0;

	// �������� ������
	std::vector<std::pair<int, std::string>> mStageData;
	// ���� ���μ��� ����
	Vector2 mapXY = Vector2();
	// �� ������
	std::vector<std::vector<int>> mMapData = {};

	// �ִ� Ŭ���� ������ �����ϴ� ����
	int mClearLevel = 0;
};