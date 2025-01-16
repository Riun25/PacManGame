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
	// 팩맨 구조상 x, y가 완전히 겹칠 때만 충돌이 벌어진다.
	return (pos.x == _other.pos.x && pos.y == _other.pos.y);
}

void DrawableActor::SetImage(const char* _img)
{
	// 기존 메모리 해제
	delete[] image;

	// 새 이미지 할당
	auto length = strlen(_img) + 1;
	this->image = new char[length];
	strcpy_s(this->image, length, _img);

	// 너비 업데이트 : 동일해서 안해줘도 되지만 일단 둔다.
	width = static_cast<int>(strlen(image));
}
