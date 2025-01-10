#pragma once
#include "Core.h"

// @refector : 엔진이 싱글톤일 필요는 없다. 매니저에서 인풋과 타임은 싱글이어야 하는게 맞다. 추후 수정한다.
class TimeManager;
class InputManager;

// 엔진 클래스
class Actor;
class Level;
class ENGINE_API Engine
{
public:
	Engine();
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;
	virtual ~Engine();

	// 엔진 실행 함수
	void Run();

	// 레벨 추가 함수
	void LoadLevel(Level* _newLevel);

	// 엑터 추가/삭제 함수 // Todo : 오브젝트 매니저 제작
	void AddActor(Actor* _newActor);
	void DestroyActor(Actor* _targetActor);

	// 엔진 종료 함수
	void QuitGame();

	bool const GetIsQuit();

	// 싱글톤 객체 접근 함수
	static Engine& Get();

	// 매니저 접근 함수
	TimeManager* GetTimeManager();
protected:
	void Update(float _dTime);			// Tick();
	void Clear();						// 화면 지우기
	void Draw();						// Render();
	void HandleGameLoop();
	void ProcessFrame();

private:
	// 싱글톤 구현을 위한 전역 변수 선언
	static Engine* gInstance;

	// ID/이름 값


	// 종료할 때 설정할 변수
	bool mIsQuit;

	TimeManager* mpTimeManager;
	InputManager* mpInputManager;

	// 메인 레벨 변수
	Level* mMainLevel;

	// 프레임을 업데이트해야 하는지 여부를 나타내는 변수
	bool mShouldUpdate = true;
};

