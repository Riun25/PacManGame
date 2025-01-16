#pragma once

#include "Actor/DrawableActor.h"

// Enemy 종류를 4개로 변경하면서 상속 구조를 사용할 것인지 고민해본다.
class Enemy : public DrawableActor
{
	RTTI_DECLARATIONS(Enemy, DrawableActor)
public:
	Enemy(const Vector2& _pos);
};