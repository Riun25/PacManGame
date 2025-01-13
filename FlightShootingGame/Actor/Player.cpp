#include "Player.h"
#include "Engine/InputManager.h"

//Todo : 화면의 최대넓이를 현재 40으로 지정했는데 ScreenMax 변수를 어디에 처리할지 생각해보기
Player::Player(const char* _img)
	: Super(_img)
{
	// 플레이어 시작 위치
	pos = Vector2(0, 18);
}

void Player::Update(float _dTime)
{
	// 부모 함수 호출
	Super::Update(_dTime);

	// 키 입력 처리
	if (InputManager::Get().GetKey(VK_LEFT))
	{
		// 새 위치 계산
		Vector2 newPos = pos;
		--newPos.x;
		if (newPos.x < 0)
		{
			newPos.x = 0;
		}

		SetPosition(newPos);
	}

	if (InputManager::Get().GetKey(VK_RIGHT))
	{
		// 새 위치 계산
		Vector2 newPos = pos;
		++newPos.x;
		if (newPos.x > 28)
		{
			newPos.x = 28;
		}

		SetPosition(newPos);
	}

	if (InputManager::Get().GetKey(VK_UP))
	{
		// 새 위치 계산
		Vector2 newPos = pos;
		--newPos.y;
		if (newPos.y < 0)
		{
			newPos.y = 0;
		}

		SetPosition(newPos);
	}

	if (InputManager::Get().GetKey(VK_DOWN))
	{
		// 새 위치 계산
		Vector2 newPos = pos;
		++newPos.y;
		if (newPos.y > 25)
		{
			newPos.y = 25;
		}

		SetPosition(newPos);
	}
}
