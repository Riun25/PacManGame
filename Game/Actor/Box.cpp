#include "Box.h"

Box::Box(const Vector2& _pos)
	:DrawableActor("b")

{
	// ��ġ ����
	pos = _pos;

	// ���� ����
	color = COLOR::YELLOW;
}
