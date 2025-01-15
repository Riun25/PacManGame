#include "PreCompiledHeader.h"
#include "Engine.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "Level/Level.h"
#include "Actor/Actor.h"

// ����ƽ ���� �ʱ�ȭ
Engine* Engine::gInstance = nullptr;

Engine::Engine()
	: mIsQuit(false), mMainLevel(nullptr), mScreenSize(80, 25)
{
	// ���� �õ� ����
	srand((unsigned int)time(nullptr));

	// �̱��� ��ü ����
	gInstance = this;
	mpTimeManager = new TimeManager();
	mpInputManager = &InputManager::Get();

	// ȭ�� ���� �� ����� ���� �ʱ�ȭ
	// 1. ���� ũ�� �Ҵ�
	mEmptyStringBuffer = new char[(mScreenSize.x + 1) * mScreenSize.y + 1];// ���� : \n, �� �� : \0 �ʿ��ؼ� �� ĭ�� �� ������

	// ���� �����
	memset(mEmptyStringBuffer, ' ', (mScreenSize.x + 1) * mScreenSize.y + 1);

	// 2. �� �Ҵ�
	for (int y = 0; y < mScreenSize.y; y++)
	{
		//for (int x = 0; x < mScreenSize.x; x++)
		//{
		//	// �ε��� ��� ���ϱ�
		//	mEmptyStringBuffer[(y * (mScreenSize.x + 1)) + x] = ' ';
		//}
		// �� �� ���� ���� ���� �߰�
		mEmptyStringBuffer[(y * (mScreenSize.x + 1)) + mScreenSize.x] = '\n';
	}

	// �������� �� ���� �߰�
	mEmptyStringBuffer[mScreenSize.y * (mScreenSize.x + 1)] = '\0';

	// �����
#if _DEBUG
	char buffer[2048];
	strcpy_s(buffer, 2048, mEmptyStringBuffer);
#endif

}

Engine::~Engine()
{
	delete mpInputManager;
	delete mpTimeManager;

	// ���� ���� �޸� ����
	SafeDelete(mMainLevel);

	// Ŭ���� ���� ����
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

		// ���� ���� : ���� ���� �� ����Ǿ�� ��
		if (mIsQuit)
		{
			break;
		}
	}
}

void Engine::LoadLevel(Level* _newLevel)
{
	// ���� ������ �ִٸ� ���� �� ��ü
	

	// ���� ���� ����
	mMainLevel = _newLevel;
}

void Engine::AddActor(Actor* _newActor)
{
	// ���� ó��
	if (mMainLevel == nullptr)
	{
		return;
	}

	// ������ ���� �߰�
	mShouldUpdate = false;
	mMainLevel->AddActor(_newActor);
}

void Engine::DestroyActor(Actor* _targetActor)
{
	// ���� ó��
	if (mMainLevel == nullptr)
	{
		return;
	}

	// ������ ���� �߰�
	mShouldUpdate = false;
	_targetActor->Destroy();
}

void Engine::QuitGame()
{
	// ���� �÷��� ����
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
	// ���� ������Ʈ
	if (mMainLevel != nullptr)
	{
		mMainLevel->Update(_dTime);
	}

	//std::cout << "FPS: " << _dTime << "\n";
}

void Engine::Clear()
{
	// ȭ���� 0,0���� �̵�
	mpInputManager->SetCursorPosition(0, 0);

	// ȭ�� �����
	std::cout << mEmptyStringBuffer;
	/*int height = 25;
	for (int i = 0; i < height; i++)
	{
		std::cout << "                               \n";
	}*/

	// ȭ���� 0,0���� �̵�
	mpInputManager->SetCursorPosition(0, 0);
}

void Engine::Draw()
{
	// ȭ�� �����.
	Clear();

	if (mMainLevel != nullptr)
	{
		mMainLevel->Draw();
	}
}

void Engine::HandleGameLoop()
{
	mpInputManager->Update();

	// ������Ʈ ������ ���¿����� ������ ������Ʈ ó��
	if (mShouldUpdate)
	{
		Update(mpTimeManager->GetDeltaTime());
		Draw();
	}

	// Ű ���� ����
	mpInputManager->SavePreviousKeyStates();
	// ���� ������ �ð� ����
	mpTimeManager->SaveCurrentTime();

	// ���� ���� (���� ��û�� ���͵� ����)
	if (mMainLevel)
	{
		//mMainLevel->DestroyActor();
		mMainLevel->ProcessAddedAndDestroyedActor();
	}

	// ������ Ȱ��ȭ
	mShouldUpdate = true;
}

void Engine::ProcessFrame()
{
	if (mpTimeManager->IsLimitFrame())
	{
		// ������ Ȯ��
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
