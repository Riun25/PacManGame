#include "Wall.h"

Wall::Wall(const Vector2& _pos)
	: DrawableActor("1")
{
	// ��ġ ����
	pos = _pos;

	// ���� ����
	color = COLOR::CYAN;


}
