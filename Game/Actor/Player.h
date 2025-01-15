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

private:
	// 게임 레벨을 참조하는 변수
	GameLevel* refLevel = nullptr;
};