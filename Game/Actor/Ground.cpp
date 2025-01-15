#include "Ground.h"

Ground::Ground(const Vector2& _pos)
	:DrawableActor(".")
{
	// 위치 설정
	pos = _pos;

	// 색상 지정
	color = COLOR::GREEN;
}
