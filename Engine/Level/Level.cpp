#include "Level.h"
#include "../Actor/Actor.h"
#include <iostream>
Level::Level()
	:mActors(nullptr), mCapacity(4), mCount(0)
{
	// 동적 배열 생성
	mActors = new Actor * [mCapacity];

	// 초기화
	memset(mActors, 0, sizeof(size_t) * mCapacity); // 0 : nullptr
}

Level::~Level()
{
	// 동적 배열 메모리 해제
	for (int idx = 0; idx < mCount; idx++)
	{
		// 엑터 삭제
		delete mActors[idx];
	}
	 // 동적 배열 해제
	delete[] mActors;
}

void Level::AddActor(Actor* _newActor)
{
	// 현재 할당된 공간이 충분한지 확인
	if (mCount == mCapacity)
	{
		// 공간 추가 할당
		int newCapacity = mCapacity * 2;

		// 임시 공간
		Actor** temp = new Actor * [newCapacity];

		// 기존 값 복사
		memcpy(temp, mActors, sizeof(size_t) * mCapacity);

		// 기존 배열 삭제
		delete[] mActors;

		// 배열 교체
		mActors = temp;
		temp = nullptr;

		// 크기 변경
		mCapacity = newCapacity;
	}
	// 엑터 추가
	mActors[mCount] = _newActor;
	mCount++;
}

void Level::Update(float _dTime)
{
	// 레벨에 포함된 엑터를 순회하면서 Update 함수 호출
	for (int idx = 0; idx < mCount; idx++)
	{
		mActors[idx]->Update(_dTime);
	}
}

void Level::Draw()
{
	// 레벨에 포함된 엑터를 순회하면서 Draw 함수 호출
	for (int idx = 0; idx < mCount; idx++)
	{
		mActors[idx]->Draw();
	}
}
