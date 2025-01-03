#pragma once
#include "PreCompiledHeader.h"


// 입력 처리를 위한 구조체
struct KeyState
{
	// 현재 프레임에 키가 눌렸는지 확인
	bool isKeyDown = false;

	// 이전 프레임에 키가 눌렸었는지 확인
	bool wasKeyDown = false;
};

class ENGINE_API InputManager
{
public:
	InputManager();
	~InputManager();

	// 입력 처리 (현재 키의 눌림 상태 확인)
	void Update();

	// 입력 관련 함수
	bool GetKey(int _key);
	bool GetKeyDown(int _key);
	bool GetKeyUp(int _key);
	void SavePreviousKeyStates();

private:
	// 키 상태를 저장하는 배열
	KeyState mKeyStateArr[255];
};

