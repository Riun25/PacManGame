#include "TestLevel.h"
#include "Actor/Actor.h"
#include "Engine/Engine.h"
#include "Engine/InputManager.h"
#include <Windows.h>
#include <iostream>


TestLevel::TestLevel()
{
	// 테스트로 엑터 추가
	AddActor(new Actor());
	AddActor(new Actor());
	AddActor(new Actor());
	AddActor(new Actor());
	AddActor(new Actor());
	AddActor(new Actor());
	AddActor(new Actor());
	AddActor(new Actor());
}

TestLevel::~TestLevel()
{

}

void TestLevel::Update(float _dTime)
{
	// 입력 확인
	if (Engine::Get().GetInputManager()->GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().GetIsQuit();
	}

	std::cout << "DeltaTime: " << _dTime << ", FPS: " << 1.0f/ _dTime << "\n";
}
