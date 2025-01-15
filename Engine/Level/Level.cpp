#include "PreCompiledHeader.h"
#include "Level.h"
#include "../Actor/Actor.h"
Level::Level()
{
}

Level::~Level()
{
	// �޸� ����
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
	// ���� ��ȸ �� ���� ��û�� ���͸� ó��
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

	// �߰� ��û�� ���� ó��
	if (mAddRequestedActor)
	{
		mActorVec.PushBack(mAddRequestedActor);
		mAddRequestedActor = nullptr;
	}
}

//void Level::DestroyActor()
//{
//	// ���� ��ȸ �� ���� ��û�� ���͸� ó��
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
	// ������ ���Ե� ���͸� ��ȸ�ϸ鼭 Update �Լ� ȣ��
	for (Actor* pActor : mActorVec)
	{
		// ���Ͱ� ��Ȱ��ȭ �����̰ų�, ���� ��û�� ��� �ǳʶٱ�
		if (!pActor->isActive || pActor->isExpired)
		{
			continue;
		}
		pActor->Update(_dTime);
	}
}

void Level::Draw()
{
	// ������ ���Ե� ���͸� ��ȸ�ϸ鼭 Draw �Լ� ȣ��
	for (Actor* pActor : mActorVec)
	{
		// ���Ͱ� ��Ȱ��ȭ �����̰ų�, ���� ��û�� ��� �ǳʶٱ�
		if (!pActor->isActive || pActor->isExpired)
		{
			continue;
		}
		pActor->Draw();
	}
}