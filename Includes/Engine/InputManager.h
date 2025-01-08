#pragma once
#include "Core.h"
#include "Math/Vector2.h"

// 입력 처리를 위한 구조체
struct KeyState
{
	// 현재 프레임에 키가 눌렸는지 확인
	bool isKeyDown = false;

	// 이전 프레임에 키가 눌렸었는지 확인
	bool wasKeyDown = false;
};

// 커서의 종류를 설정할 때 사용할 열거형
enum class CURSOR_TYPE
{
	NONE,
	SOLID,
	NORMAL,
};

class ENGINE_API InputManager
{
public:
	InputManager();
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;
	~InputManager();

	// 싱글톤 객체 접근 함수
	static InputManager& Get();

	// 입력 처리 (현재 키의 눌림 상태 확인)
	void Update();

	// 입력 관련 함수
	bool GetKey(int _key);
	bool GetKeyDown(int _key);
	bool GetKeyUp(int _key);
	void SavePreviousKeyStates();

	// 화면 좌표 관련 함수
	void SetCursorType(CURSOR_TYPE _type);
	void SetCursorPosition(const Vector2& _pos);
	void SetCursorPosition(int _x, int _y);

private:
	// 싱글톤 구현을 위한 전역 변수 선언
	static InputManager* gInstance;

	// 키 상태를 저장하는 배열
	KeyState mKeyStateArr[255];
};

