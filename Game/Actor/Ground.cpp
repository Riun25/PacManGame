#include "Ground.h"

Ground::Ground(const Vector2& _pos)
	:DrawableActor(".")
{
	// ��ġ ����
	pos = _pos;

	// ���� ����
	color = COLOR::GREEN;
}
