#include "Target.h"

Target::Target(const Vector2& _pos)
	:DrawableActor("T")
{
	// ��ġ ����
	pos = _pos;

	// ���� ����
	color = COLOR::RED;
}
