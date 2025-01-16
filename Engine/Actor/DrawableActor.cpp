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
	// �Ѹ� ������ x, y�� ������ ��ĥ ���� �浹�� ��������.
	return (pos.x == _other.pos.x && pos.y == _other.pos.y);
}

void DrawableActor::SetImage(const char* _img)
{
	// ���� �޸� ����
	delete[] image;

	// �� �̹��� �Ҵ�
	auto length = strlen(_img) + 1;
	this->image = new char[length];
	strcpy_s(this->image, length, _img);

	// �ʺ� ������Ʈ : �����ؼ� �����൵ ������ �ϴ� �д�.
	width = static_cast<int>(strlen(image));
}
