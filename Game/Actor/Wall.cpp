#include "Wall.h"

Wall::Wall(const Vector2& _pos)
	: DrawableActor("��")
{
	// ��ġ ����
	pos = _pos;

	// ���� ����
	color = COLOR::MAGENTA;


}
