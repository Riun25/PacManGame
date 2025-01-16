#pragma once
#include "Core.h"
#include "../Math/Vector2.h"

// @refector : ������ �̱����� �ʿ�� ����. �Ŵ������� ��ǲ�� Ÿ���� �̱��̾�� �ϴ°� �´�. ���� �����Ѵ�.
class TimeManager;
class InputManager;

// ���� Ŭ����
class Actor;
class Level;
class ENGINE_API Engine
{
public:
	Engine();
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;
	virtual ~Engine();

	// ���� ���� �Լ�
	void Run();

	// ���� �߰� �Լ�
	void LoadLevel(Level* _newLevel);

	// ���� �߰�/���� �Լ� // Todo : ������Ʈ �Ŵ��� ����
	void AddActor(Actor* _newActor);
	void DestroyActor(Actor* _targetActor);

	// ȭ�� ũ�� ��ȯ �Լ�
	inline Vector2 ScreenSize() const { return mScreenSize; }

	// ���� ���� �Լ�
	void QuitGame();

	bool const GetIsQuit();

	// �̱��� ��ü ���� �Լ�
	static Engine& Get();

	// �Ŵ��� ���� �Լ�
	TimeManager* GetTimeManager();
protected:
	void Update(float _dTime);			// Tick();
	void Clear();						// ȭ�� �����
	void Draw();						// Render();
	void HandleGameLoop();
	void ProcessFrame();

protected:
	TimeManager* mpTimeManager;
	InputManager* mpInputManager;

	// ���� ���� ����
	Level* mMainLevel;

private:
	// �̱��� ������ ���� ���� ���� ����
	static Engine* gInstance;

	// ID/�̸� ��
	// ������ �� ������ ����
	bool mIsQuit;


	// �������� ������Ʈ�ؾ� �ϴ��� ���θ� ��Ÿ���� ����
	bool mShouldUpdate = true;

	// ȭ�� ũ��
	Vector2 mScreenSize;

	// ȭ�� ���� �� ����� ����(Buffer/Blob)
	char* mEmptyStringBuffer = nullptr;
};

