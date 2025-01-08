#pragma once
#include "Core.h"

class ENGINE_API TimeManager
{
public:
	TimeManager();
	~TimeManager();

	void Initialize();

	void Update();

	float GetDeltaTime();
	void SaveCurrentTime();

	void LimitFrame(float _limit);
	bool IsLimitFrame();
	bool CheckOverTargetFrame();

private:
	// CPU 시계 사용 : 시스템 시계 -> 고해상도 카운터(10000000)
	LARGE_INTEGER mFrequency;
	// 시작 시간 및 이전 시간을 위한 변수
	LARGE_INTEGER mTime;

	__int64 mCurrentTime;
	__int64 mPreviousTime;
	float mDeltaTime;

	// 프레임 제한을 위해 사용하는 변수
	// 타겟 프레임
	float mTargetFrameRate;
	// 한 프레임 시간 값(단위 : 초)
	float mTargetOneFrameTime;
	bool mIsLimitFrame;
};

