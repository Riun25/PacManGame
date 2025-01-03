#pragma once
#include "PreCompiledHeader.h"

// 전방 선언
class Actor;

class ENGINE_API Level
{
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
	Actor** mActors;
	// 저장할 수 있는 공간의 크기
	int mCapacity;
	// 액터의 수
	int mCount;
};

