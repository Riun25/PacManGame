#include "Item.h"

Item::Item(const Vector2& _pos)
	:DrawableActor("��")
{
	// ��ġ ����
	pos = _pos;

	// ���� ����
	color = COLOR::WHITE;
}
