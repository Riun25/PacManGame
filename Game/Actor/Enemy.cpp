#pragma once
#include "Astar.h"
#include "Enemy.h"
#include "Engine/Timer.h"
#include "Level/GameLevel.h"
#include "Player.h"

Enemy::Enemy(const Vector2& _pos, GameLevel* _level)
	:DrawableActor("♠"), mRefLevel(_level)
{
	// 위치 설정
	pos = _pos;
	mPos = _pos;
	pos = mPos;

	// 색상 설정
	color = COLOR::RED;

	int random = Random(1, 10);
	if (random % 2 == 0)
	{
		// 짝수인 경우에는 왼쪽으로 이동하도록 설정
		mDir = DIRECTION::LEFT;
	}
	else
	{
		// 홀수인 경우에는 오른쪽으로 이동하도록 설정
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

	// 타이머
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
		// 경로가 없으면 경로 설정
		if (mOwnPaths.size() == 0)
		{
			mOwnPaths = *pAstar->Astar(pos, playerPos);
			mPathIdx = 0;
		}

		// 경로가 끝나면 경로 설정
		if (mOwnPaths.size() <= mPathIdx)
		{
			mOwnPaths = *pAstar->Astar(pos, playerPos);
			mPathIdx = 0;
		}

		// 이동하기?
		pos = mOwnPaths[mPathIdx];
		++mPathIdx;


		// 이동 여기서
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

	// 적군 이동 탐색
}