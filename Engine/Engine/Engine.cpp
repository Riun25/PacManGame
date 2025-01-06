#include "PreCompiledHeader.h"
#include "Engine.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "Level/Level.h"

// 스태틱 변수 초기화
Engine* Engine::instance = nullptr;

Engine::Engine()
	: mIsQuit(false), mMainLevel(nullptr)
{
	// 싱글톤 객체 설정
	instance = this;
	mpTimeManager = new TimeManager();
	mpInputManager = new InputManager();
}

Engine::~Engine()
{
	delete mpInputManager;
	delete mpTimeManager;

	// 메인 레벨 메모리 해제
	if (mMainLevel != nullptr)
	{
		delete mMainLevel;
	}
}

void Engine::Run()
{
	mpTimeManager->Initialize();
	mpTimeManager->LimitFrame(60.0f);

	// Game-Loop
	while (true)
	{
		// 종료 조건
		if (mIsQuit)
		{
			break;
		}

		mpTimeManager->Update();
		ProcessFrame();
		Draw();
	}
}

void Engine::LoadLevel(Level* _newLevel)
{
	// 기존 레벨이 있다면 삭제 후 교체
	

	// 메인 레벨 설정
	mMainLevel = _newLevel;
}

void Engine::QuitGame()
{
	// 종료 플래그 설정
	mIsQuit = true;
}


bool const Engine::GetIsQuit()
{
	return mIsQuit;
}

Engine& Engine::Get()
{
	if (!instance)
	{
		instance = new Engine();
	}
	return *instance;
}

TimeManager* Engine::GetTimeManager()
{
	return mpTimeManager;
}

InputManager* Engine::GetInputManager()
{
	return mpInputManager;
}

void Engine::Update(float _dTime)
{
	// 레벨 업데이트
	if (mMainLevel != nullptr)
	{
		mMainLevel->Update(_dTime);
	}

	std::cout << "FPS: " << _dTime << "\n";
}

void Engine::Draw()
{
	if (mMainLevel != nullptr)
	{
		mMainLevel->Draw();
	}
}

void Engine::HandleGameLoop()
{
	mpInputManager->Update();
	Update(mpTimeManager->GetDeltaTime());

	// 키 상태 저장
	mpInputManager->SavePreviousKeyStates();
	// 이전 프레임 시간 저장
	mpTimeManager->SaveCurrentTime();
}

void Engine::ProcessFrame()
{
	if (mpTimeManager->IsLimitFrame())
	{
		// 프레임 확인
		if (mpTimeManager->CheckOverTargetFrame())
		{
			HandleGameLoop();
		}
	}
	else
	{
		HandleGameLoop();
	}
}
