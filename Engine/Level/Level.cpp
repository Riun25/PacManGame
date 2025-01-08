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
	mActorVec.PushBack(_newActor);
}

void Level::Update(float _dTime)
{
	// 레벨에 포함된 엑터를 순회하면서 Update 함수 호출
	for (Actor* pActor : mActorVec)
	{
		pActor->Update(_dTime);
	}
}

void Level::Draw()
{
	// 레벨에 포함된 엑터를 순회하면서 Draw 함수 호출
	for (Actor* pActor : mActorVec)
	{
		pActor->Draw();
	}
}