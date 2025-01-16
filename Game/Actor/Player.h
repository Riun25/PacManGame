#pragma once

#include "Actor/DrawableActor.h"

// 게임 레벨 전방 선언
class GameLevel;
class Player : public DrawableActor
{
	RTTI_DECLARATIONS(Player, DrawableActor)
public:
	Player(const Vector2& _pos, GameLevel* _level);

	virtual void Update(float _dTime) override;

	void PlayerMove();

private:
	// 게임 레벨을 참조하는 변수
	GameLevel* refLevel = nullptr;

	// 아이템을 먹어서 반전 상태인지를 나타내는 변수
	// Todo : 아이템 기능 추가할 때 구현할 것
	bool mIsGhostEatable = false;
};