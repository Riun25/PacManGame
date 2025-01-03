#include "PreCompiledHeader.h"
#include "InputManager.h"

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::Update() //ProcessInput()
{
	for (int idx = 0; idx < 255; idx++)
	{
		mKeyStateArr[idx].isKeyDown = (GetAsyncKeyState(idx) & 0x8000) ? true : false;
	}
}

bool InputManager::GetKey(int _key)
{
	return mKeyStateArr[_key].isKeyDown;
}

bool InputManager::GetKeyDown(int _key)
{
	return mKeyStateArr[_key].isKeyDown && !mKeyStateArr[_key].wasKeyDown;
}

bool InputManager::GetKeyUp(int _key)
{
	return !mKeyStateArr[_key].isKeyDown && mKeyStateArr[_key].wasKeyDown;
}

void InputManager::SavePreviousKeyStates()
{
	for (int idx = 0; idx < 255; idx++)
	{
		mKeyStateArr[idx].wasKeyDown = mKeyStateArr[idx].isKeyDown;
	}
}
