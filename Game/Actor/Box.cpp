#include "Box.h"

Box::Box(const Vector2& _pos)
	:DrawableActor("b")

{
	// 위치 설정
	pos = _pos;

	// 색상 설정
	color = COLOR::YELLOW;
}
