#include "PreCompiledHeader.h"
#include "DrawableActor.h"
#include "Engine/InputManager.h"

DrawableActor::DrawableActor(const char* _img)
	:Actor()/*, image(_img)*/
{
	auto length = strlen(_img) + 1;
	this->image = new char[length];
		strcpy_s(this->image, length, _img);
}

DrawableActor::~DrawableActor()
{
	delete[] image;
}

void DrawableActor::Draw()
{
	Super::Draw();

	// 그리기
	// 1단계 : 콘솔 좌표 옮기기
	InputManager::Get().SetCursorPosition(pos);

	// 2단계 : 그리기(콘솔 출력)
	Log(image);
}

void DrawableActor::SetPosition(const Vector2& _newPos)
{
	/*InputManager::Get().SetCursorPosition(pos);
	Log(" ");*/

	// 위치를 새로 옮기기
	Super::SetPosition(_newPos);
}
