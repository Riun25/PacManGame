#include "Enemy.h"

Enemy::Enemy(const Vector2& _pos)
	:DrawableActor("��")

{
	// ��ġ ����
	pos = _pos;

	// ���� ����
	color = COLOR::RED;
}
