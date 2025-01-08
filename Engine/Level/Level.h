#pragma once
#include "Core.h"
#include "RTTI.h"
#include "Container/List.h"

// 전방 선언
class Actor;
class ENGINE_API Level : public RTTI
{
	// RTTI 정의
	RTTI_DECLARATIONS(Level, RTTI)

public:
	Level();
	virtual ~Level();

	//액터 추가 함수
	void AddActor(Actor* _newActor);

	// 루프 처리 함수
	virtual void Update(float _dTime);
	virtual void Draw();

protected:
	// 게임 공간에 배치되는 물체(엑터) 배열
	List<Actor*> mActorVec;
};

