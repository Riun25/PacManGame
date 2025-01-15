#include "PreCompiledHeader.h"
#include "DrawableActor.h"
#include "Engine/InputManager.h"

DrawableActor::DrawableActor(const char* _img)
	:Actor()/*, image(_img)*/
{
	auto length = strlen(_img) + 1;
	this->image = new char[length];
	strcpy_s(this->image, length, _img);

	//�ʺ� ����
	width = static_cast<int>(strlen(image));
}

DrawableActor::~DrawableActor()
{
	delete[] image;
}

void DrawableActor::Draw()
{
	Super::Draw();

	// ���� ����
	SetColor(color);

	// �׸���
	// 1�ܰ� : �ܼ� ��ǥ �ű��
	InputManager::Get().SetCursorPosition(pos);

	// 2�ܰ� : �׸���(�ܼ� ���)
	Log(image);

	// ���� ����
	SetColor(COLOR::WHITE);
}

void DrawableActor::SetPosition(const Vector2& _newPos)
{
	// ��ġ�� ���� �ű��
	Super::SetPosition(_newPos);
}

bool DrawableActor::Intersect(const DrawableActor& _other)
{
	// AABB(Axis Aligned Bounding Box)

	// �� x ��ǥ �ּ�/�ִ�
	int min = pos.x;
	int max = pos.x + width;

	// �ٸ� ������ x��ǥ �ּ�/�ִ�
	int otherMin = _other.pos.x;
	int otherMax = _other.pos.x + _other.width;

	// �ٸ� ������ ���� �� ��ġ�� �� ������ �� ��ġ�� ����� �浹 ����
	if (otherMin > max)
	{
		return false;
	}

	// �ٸ� ������ ������ �� ��ġ�� �� ���� �� ��ġ�� ����� �浹 ����
	if (otherMax < min)
	{
		return false;
	}

	// ���� �� ��찡 �ƴ϶�� x��ǥ�� ��ġ�Ƿ� y ��ǥ ��
	return pos.y == _other.pos.y;
}
