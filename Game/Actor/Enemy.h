#pragma once

#include "Actor/DrawableActor.h"

// Enemy ������ 4���� �����ϸ鼭 ��� ������ ����� ������ ����غ���.
class Enemy : public DrawableActor
{
	RTTI_DECLARATIONS(Enemy, DrawableActor)
public:
	Enemy(const Vector2& _pos);
};