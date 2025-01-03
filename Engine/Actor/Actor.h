#pragma once

// 레벨의 기본 물체
class Actor
{
public:
	Actor();
	virtual ~Actor();

	// 루프 처리 함수
	virtual void Update(float _dTime);
	virtual void Draw();
protected:
	// 활성화 상태인지를 나타내는 변수
	bool mIsActive;

	// 엑터의 제거 요청이 됐는지 여부를 나타내는 변수
	bool mIsExpired;
};

