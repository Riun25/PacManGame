#pragma once
#include "Actor/DrawableActor.h"

// Enemy ������ 4���� �����ϸ鼭 ��� ������ ����� ������ ����غ���.
class GameLevel;
class AStar;
class Enemy : public DrawableActor
{
	// �� ĳ���Ͱ� �̵��� ����
	enum class DIRECTION
	{
		NONE = -1,
		LEFT,
		RIGHT
	};

	RTTI_DECLARATIONS(Enemy, DrawableActor)
public:
	Enemy(const Vector2& _pos, GameLevel* _level);
	~Enemy(); // ������� �����ϸ� virtual �ٿ��� �Ѵ�.

	virtual void Update(float _dTime) override;

public:
	std::vector<std::vector<int>>* mMapData;
	Vector2 mMapXY = Vector2();
	DrawableActor* player = nullptr;

private:
	// ���� ������ �����ϴ� ����
	GameLevel* mRefLevel = nullptr;

	DIRECTION mDir;

	// �̵��� �ʿ��� ����
	Vector2 mPos = Vector2();
	float mSpeed = 0.01f;

	// ��� ã��� ���� Enemy�鸸 �ʿ��ϹǷ�, Astar Ŭ������ ���⿡ ��ġ
	AStar* pAstar;
	// ���� ���
	std::vector<Vector2> mOwnPaths;
	// ���� ����� �ε���
	int mPathIdx = 0;

	// Enemy���� ������ ��ġ�� Ȯ���� �� �־�� �Ѵ�. 
	// �ڽ��� ��ġ�κ��� 5ĭ �̳��� ������ ������ ���������� ��Ž�� ���Ѽ� �浹�� �� �Ͼ�� �ؾ� �Ѵ�.
	
};