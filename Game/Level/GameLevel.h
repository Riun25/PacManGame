#pragma once

#include "Level/Level.h"
#include "Math/Vector2.h"

// 소코반 게임 레벨
class DrawableActor;
class Player;
class Box;
class Target;
class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel, Level)
public:
	GameLevel();

	// 업데이트 함수
	virtual void Update(float _dTime) override;

	// 레벨의 그리기 함수
	virtual void Draw() override;

	// 플레이어가 이동이 가능한지 확인하는 함수
	bool CanPlayerMove(const Vector2& _pos);

private:
	// 박스를 옮긴 뒤 게임을 클리어했는지 확인하는 함수
	bool CheckGameClear();

private:
	// 벽/땅 액터 배열
	List<DrawableActor*> mMapVec;

	// 박스 액터
	List<Box*> mBoxVec;

	// 타겟 액터
	List<Target*> mTargetVec;

	// 플레이어 엑터
	DrawableActor* player = nullptr;

	// 게임 클리어 변수
	bool mIsGameClear = false;
};