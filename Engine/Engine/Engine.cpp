#include "Engine.h"
#include <Windows.h>
#include <iostream>

Engine::Engine()
	: mIsQuit(false)
{
}

Engine::~Engine()
{
}

void Engine::Run()
{
	// 시작 타임 스탬프 저장
	//unsigned long currentTime = timeGetTime();
	//unsigned long previousTime = 0;

	// CPU 시계 사용
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	// 시작 시간 및 이전 시간을 위한 함수
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);

	int64_t currentTime = time.QuadPart;
	int64_t previousTime = 0;

	// 프레임 제한
	float targetFrameRate = 60.0f;

	// 한 프레임 시간 계산
	float targetOneFrameTime = 1.0f / targetFrameRate;


	// Game-Loop
	while (true)
	{
		// 종료 조건
		if (mIsQuit)
		{
			break;
		}

		// 현재 프레임 시간 저장
		//currentTime = timeGetTime();
		QueryPerformanceCounter(&time);
		currentTime = time.QuadPart;

		// 프레임 시간 계산
		float deltaTime = static_cast<float>(currentTime - previousTime) / static_cast<float>(frequency.QuadPart);



		// 프레임 확인
		if (deltaTime >= targetOneFrameTime)
		{
			// 입력 처리 (현재 키의 눌림 상태 확인)
			ProcessInput();

			Update(deltaTime);
			Draw();

			// 키 상태 저장
			SavePreviousKeyStates();

			// 이전 프레임 시간 저장
			previousTime = currentTime;
		}
	}
}

bool Engine::GetKey(int _key)
{
	return mKeyStateArr[_key].isKeyDown;
}

bool Engine::GetKeyDown(int _key)
{
	return mKeyStateArr[_key].isKeyDown && !mKeyStateArr[_key].wasKeyDown;
}

bool Engine::GetKeyUp(int _key)
{
	return !mKeyStateArr[_key].isKeyDown && mKeyStateArr[_key].wasKeyDown;
}

void Engine::QuitGame()
{
	// 종료 플래그 설정
	mIsQuit = true;
}

void Engine::ProcessInput()
{
	for (int idx = 0; idx < 255; idx++)
	{
		mKeyStateArr[idx].isKeyDown = (GetAsyncKeyState(idx) & 0x8000) ? true : false;
	}
}

void Engine::Update(float _dTime)
{
	// ESC키로 게임 종료
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		QuitGame();
	}

	std::cout << "DeltaTime: " << _dTime << ", FPS: " << (1.0f / _dTime) << "\n";
}

void Engine::Draw()
{
}

void Engine::SavePreviousKeyStates()
{
	for (int idx = 0; idx < 255; idx++)
	{
		mKeyStateArr[idx].wasKeyDown = mKeyStateArr[idx].isKeyDown;
	}
}
