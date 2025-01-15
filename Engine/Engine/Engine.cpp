#include "PreCompiledHeader.h"
#include "Engine.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "Level/Level.h"
#include "Actor/Actor.h"

// 스태틱 변수 초기화
Engine* Engine::gInstance = nullptr;

Engine::Engine()
	: mIsQuit(false), mMainLevel(nullptr), mScreenSize(80, 25)
{
	// 랜덤 시드 설정
	srand((unsigned int)time(nullptr));

	// 싱글톤 객체 설정
	gInstance = this;
	mpTimeManager = new TimeManager();
	mpInputManager = &InputManager::Get();

	// 화면 지울 때 사용할 버퍼 초기화
	// 1. 버퍼 크기 할당
	mEmptyStringBuffer = new char[(mScreenSize.x + 1) * mScreenSize.y + 1];// 가로 : \n, 맨 끝 : \0 필요해서 한 칸씩 더 더해줌

	// 버퍼 덮어쓰기
	memset(mEmptyStringBuffer, ' ', (mScreenSize.x + 1) * mScreenSize.y + 1);

	// 2. 값 할당
	for (int y = 0; y < mScreenSize.y; y++)
	{
		//for (int x = 0; x < mScreenSize.x; x++)
		//{
		//	// 인덱스 계산 잘하기
		//	mEmptyStringBuffer[(y * (mScreenSize.x + 1)) + x] = ' ';
		//}
		// 각 줄 끝에 개행 문자 추가
		mEmptyStringBuffer[(y * (mScreenSize.x + 1)) + mScreenSize.x] = '\n';
	}

	// 마지막에 널 문자 추가
	mEmptyStringBuffer[mScreenSize.y * (mScreenSize.x + 1)] = '\0';

	// 디버깅
#if _DEBUG
	char buffer[2048];
	strcpy_s(buffer, 2048, mEmptyStringBuffer);
#endif

}

Engine::~Engine()
{
	delete mpInputManager;
	delete mpTimeManager;

	// 메인 레벨 메모리 해제
	SafeDelete(mMainLevel);

	// 클리어 버퍼 삭제
	delete[] mEmptyStringBuffer;
}

void Engine::Run()
{
	mpTimeManager->Initialize();
	mpTimeManager->LimitFrame(60.0f);

	// Game-Loop
	while (true)
	{
		mpTimeManager->Update();
		ProcessFrame();
		/*if (mShouldUpdate)
		{
			Draw();
		}*/

		// 종료 조건 : 액터 정리 후 종료되어야 함
		if (mIsQuit)
		{
			break;
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
	std::cout << mEmptyStringBuffer;
	/*int height = 25;
	for (int i = 0; i < height; i++)
	{
		std::cout << "                               \n";
	}*/

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
		Draw();
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
