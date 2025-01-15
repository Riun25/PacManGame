#include "Target.h"

Target::Target(const Vector2& _pos)
	:DrawableActor("T")
{
	// 위치 설정
	pos = _pos;

	// 색상 설정
	color = COLOR::RED;
}
