#include "PreCompiledHeader.h"
#include "DrawableActor.h"
//#include "Engine/Engine.h"
#include "Engine/InputManager.h"

DrawableActor::DrawableActor(char _img)
	:Actor(), image(_img)
{
}

void DrawableActor::Draw()
{
	Super::Draw();

	// 그리기
	// 1단계 : 콘솔 좌표 옮기기
	InputManager::Get().SetCursorPosition(pos);
	//Engine::Get().GetInputManager()->SetCursorPosition(pos);

	// 2단계 : 그리기(콘솔 출력)
	Log("%c", image);
}

void DrawableActor::SetPosition(const Vector2& _newPos)
{
	InputManager::Get().SetCursorPosition(pos);
	Log(" ");

	// 위치를 새로 옮기기
	Super::SetPosition(_newPos);
}
