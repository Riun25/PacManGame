#include "PreCompiledHeader.h"
#include "Level.h"
#include "../Actor/Actor.h"
Level::Level()
{
}

Level::~Level()
{
	// 메모리 해제
	for (Actor* pActor : mActorVec)
	{
		delete pActor;
	}
}

void Level::AddActor(Actor* _newActor)
{
	//mActorVec.PushBack(_newActor);
	mAddRequestedActor = _newActor;
}

void Level::ProcessAddedAndDestroyedActor()
{
	// 엑터 순회 후 삭제 요청된 엑터를 처리
	for (int idx = 0; idx < mActorVec.Size();)
	{
		if (mActorVec[idx]->isExpired)
		{
   			delete mActorVec[idx];
			mActorVec[idx] = nullptr;
			mActorVec.Erase(idx);
			continue;
		}
		++idx;
	}

	// 추가 요청된 엑터 처리
	if (mAddRequestedActor)
	{
		mActorVec.PushBack(mAddRequestedActor);
		mAddRequestedActor = nullptr;
	}
}

//void Level::DestroyActor()
//{
//	// 엑터 순회 후 삭제 요청된 엑터를 처리
//	for (int idx = 0; idx < mActorVec.Size(); idx++)
//	{
//		if (mActorVec[idx]->isExpired)
//		{
//			delete mActorVec[idx];
//			mActorVec[idx] = nullptr;
//			mActorVec.Erase(idx);
//		}
//	}
//}

void Level::Update(float _dTime)
{
	// 레벨에 포함된 엑터를 순회하면서 Update 함수 호출
	for (Actor* pActor : mActorVec)
	{
		// 엑터가 비활성화 상태이거나, 삭제 요청된 경우 건너뛰기
		if (!pActor->isActive || pActor->isExpired)
		{
			continue;
		}
		pActor->Update(_dTime);
	}
}

void Level::Draw()
{
	// 레벨에 포함된 엑터를 순회하면서 Draw 함수 호출
	for (Actor* pActor : mActorVec)
	{
		// 엑터가 비활성화 상태이거나, 삭제 요청된 경우 건너뛰기
		if (!pActor->isActive || pActor->isExpired)
		{
			continue;
		}
		pActor->Draw();
	}
}