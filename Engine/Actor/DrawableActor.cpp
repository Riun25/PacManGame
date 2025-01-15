#include "PreCompiledHeader.h"
#include "DrawableActor.h"
#include "Engine/InputManager.h"

DrawableActor::DrawableActor(const char* _img)
	:Actor()/*, image(_img)*/
{
	auto length = strlen(_img) + 1;
	this->image = new char[length];
	strcpy_s(this->image, length, _img);

	//너비 설정
	width = static_cast<int>(strlen(image));
}

DrawableActor::~DrawableActor()
{
	delete[] image;
}

void DrawableActor::Draw()
{
	Super::Draw();

	// 색상 설정
	SetColor(color);

	// 그리기
	// 1단계 : 콘솔 좌표 옮기기
	InputManager::Get().SetCursorPosition(pos);

	// 2단계 : 그리기(콘솔 출력)
	Log(image);

	// 색상 복구
	SetColor(COLOR::WHITE);
}

void DrawableActor::SetPosition(const Vector2& _newPos)
{
	// 위치를 새로 옮기기
	Super::SetPosition(_newPos);
}

bool DrawableActor::Intersect(const DrawableActor& _other)
{
	// AABB(Axis Aligned Bounding Box)

	// 내 x 좌표 최소/최대
	int min = pos.x;
	int max = pos.x + width;

	// 다른 액터의 x좌표 최소/최대
	int otherMin = _other.pos.x;
	int otherMax = _other.pos.x + _other.width;

	// 다른 엑터의 왼쪽 끝 위치가 내 오른쪽 끝 위치를 벗어나면 충돌 안함
	if (otherMin > max)
	{
		return false;
	}

	// 다른 엑터의 오른쪽 끝 위치가 내 왼쪽 끝 위치를 벗어나면 충돌 안함
	if (otherMax < min)
	{
		return false;
	}

	// 위의 두 경우가 아니라면 x좌표는 겹치므로 y 좌표 비교
	return pos.y == _other.pos.y;
}
