#pragma once
#include "Astar.h"
#include "Enemy.h"
#include "Engine/Timer.h"
#include "Level/GameLevel.h"
#include "Player.h"

Enemy::Enemy(const Vector2& _pos, GameLevel* _level)
	:DrawableActor("��"), mRefLevel(_level)
{
	// ��ġ ����
	pos = _pos;
	mPos = _pos;
	pos = mPos;

	// ���� ����
	color = COLOR::RED;

	int random = Random(1, 10);
	if (random % 2 == 0)
	{
		// ¦���� ��쿡�� �������� �̵��ϵ��� ����
		mDir = DIRECTION::LEFT;
	}
	else
	{
		// Ȧ���� ��쿡�� ���������� �̵��ϵ��� ����
		mDir = DIRECTION::RIGHT;
	}

	pAstar = new AStar();
}


Enemy::~Enemy()
{
	delete pAstar;
}

void Enemy::Update(float _dTime)
{
	Super::Update(_dTime);

	if (pAstar->GetAstarMap() == nullptr)
	{
		pAstar->Initialize(Vector2(0, 0), Vector2(mMapXY.x, mMapXY.y+1), mMapData);
	}

	if (_dTime > 0.1f)
	{
		return;
	}

	// Ÿ�̸�
	static Timer timer(1.0f);
	timer.Update(_dTime);
	if (timer.IsTimeOut() == false)
	{
		return;
	}
	else
	{
		if (player == nullptr)
		{
			return;
		}

		Vector2 playerPos = player->Position();
		// ��ΰ� ������ ��� ����
		if (mOwnPaths.size() == 0)
		{
			mOwnPaths = *pAstar->Astar(pos, playerPos);
			mPathIdx = 0;
		}

		// ��ΰ� ������ ��� ����
		if (mOwnPaths.size() <= mPathIdx)
		{
			mOwnPaths = *pAstar->Astar(pos, playerPos);
			mPathIdx = 0;
		}

		// �̵��ϱ�?
		pos = mOwnPaths[mPathIdx];
		++mPathIdx;


		// �̵� ���⼭
		//float factor = mDir == DIRECTION::LEFT ? -1.0f : 1.0f;
		//mPos.x += factor;
		//if (mRefLevel->CanEnemyMove(Vector2(mPos.x, pos.y)))
		//{
		//	pos.x += factor;
		//}


		/*float factor = mDir == DIRECTION::LEFT ? -1.0f : 1.0f;
		mPos.y += factor;
		if (mRefLevel->CanEnemyMove(Vector2(pos.x, mPos.y)))
		{
			pos.y += factor;
		}*/

		timer.Reset();
	}

	// ���� �̵� Ž��
}