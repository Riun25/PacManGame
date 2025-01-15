#include "Wall.h"

Wall::Wall(const Vector2& _pos)
	: DrawableActor("1")
{
	// 위치 설정
	pos = _pos;

	// 색상 설정
	color = COLOR::CYAN;


}
