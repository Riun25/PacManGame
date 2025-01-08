#include "Player.h"
#include "Engine/InputManager.h"

//Todo : 화면의 최대넓이를 현재 40으로 지정했는데 ScreenMax 변수를 어디에 처리할지 생각해보기
Player::Player(char _img)
	: Super(_img)
{
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
		if (newPos.x > 40)
		{
			newPos.x = 40;
		}

		SetPosition(newPos);
	}
}
