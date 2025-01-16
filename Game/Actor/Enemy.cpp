#include "Enemy.h"

Enemy::Enemy(const Vector2& _pos)
	:DrawableActor("♠")

{
	// 위치 설정
	pos = _pos;

	// 색상 설정
	color = COLOR::RED;
}
