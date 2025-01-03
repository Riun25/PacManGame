#pragma once
class TimeManager;
class InputManager;
class Level;

// 엔진 클래스
class Engine
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

	// 엔진 종료 함수
	void QuitGame();

	bool const GetIsQuit();

	// 싱글톤 객체 접근 함수
	static Engine& Get();

	// 매니저 접근 함수
	TimeManager* GetTimeManager();
	InputManager* GetInputManager();
protected:
	void Update(float _dTime);			// Tick();
	void Draw();						// Render();
	void HandleGameLoop();
	void ProcessFrame();

private:
	// ID/이름 값


	// 종료할 때 설정할 변수
	bool mIsQuit;

	TimeManager* mpTimeManager;
	InputManager* mpInputManager;

	// 싱글톤 구현을 위한 전역 변수 선언
	static Engine* instance;

	// 메인 레벨 변수
	Level* mMainLevel;
};

