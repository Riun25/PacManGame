#include "PreCompiledHeader.h"
#include "Engine.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "Level/Level.h"
#include "Actor/Actor.h"

// 스태틱 변수 초기화
Engine* Engine::gInstance = nullptr;

Engine::Engine()
	: mIsQuit(false), mMainLevel(nullptr)
{
	// 싱글톤 객체 설정
	gInstance = this;
	mpTimeManager = new TimeManager();
	mpInputManager = &InputManager::Get();
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
		if (mShouldUpdate)
		{
			Draw();
		}
	}
}

void Engine::LoadLevel(Level* _newLevel)
{
	// 기존 레벨이 있다면 삭제 후 교체
	

	// 메인 레벨 설정
	mMainLevel = _newLevel;
}

void Engine::AddActor(Actor* _newActor)
{
	// 예외 처리
	if (mMainLevel == nullptr)
	{
		return;
	}

	// 레벨에 엑터 추가
	mShouldUpdate = false;
	mMainLevel->AddActor(_newActor);
}

void Engine::DestroyActor(Actor* _targetActor)
{
	// 예외 처리
	if (mMainLevel == nullptr)
	{
		return;
	}

	// 레벨에 엑터 추가
	mShouldUpdate = false;
	_targetActor->Destroy();
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
	if (!gInstance)
	{
		gInstance = new Engine();
	}
	return *gInstance;
}

TimeManager* Engine::GetTimeManager()
{
	return mpTimeManager;
}

void Engine::Update(float _dTime)
{
	// 레벨 업데이트
	if (mMainLevel != nullptr)
	{
		mMainLevel->Update(_dTime);
	}

	//std::cout << "FPS: " << _dTime << "\n";
}

void Engine::Clear()
{
	// 화면의 0,0으로 이동
	mpInputManager->SetCursorPosition(0, 0);

	// 화면 지우기
	int height = 30;
	for (int i = 0; i < height; i++)
	{
		Log("                              \n");
	}

	// 화면의 0,0으로 이동
	mpInputManager->SetCursorPosition(0, 0);
}

void Engine::Draw()
{
	// 화면 지우기.
	Clear();

	if (mMainLevel != nullptr)
	{
		mMainLevel->Draw();
	}
}

void Engine::HandleGameLoop()
{
	mpInputManager->Update();

	// 업데이트 가능한 상태에서만 프레임 업데이트 처리
	if (mShouldUpdate)
	{
		Update(mpTimeManager->GetDeltaTime());
	}

	// 키 상태 저장
	mpInputManager->SavePreviousKeyStates();
	// 이전 프레임 시간 저장
	mpTimeManager->SaveCurrentTime();

	// 엑터 정리 (삭제 요청된 엑터들 정리)
	if (mMainLevel)
	{
		//mMainLevel->DestroyActor();
		mMainLevel->ProcessAddedAndDestroyedActor();
	}

	// 프레임 활성화
	mShouldUpdate = true;
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
