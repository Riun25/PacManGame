#pragma once
#include "PreCompiledHeader.h"
#include "TimeManager.h"
TimeManager::TimeManager()
	:mFrequency({0}), mTime({0}), mCurrentTime(0), mPreviousTime(0), mDeltaTime(0.0f)
	, mTargetFrameRate(60.0f), mTargetOneFrameTime(0), mIsLimitFrame(false)
{
}

TimeManager::~TimeManager()
{
}

void TimeManager::Initialize()
{
	QueryPerformanceFrequency(&mFrequency);
	QueryPerformanceCounter(&mTime);
	mCurrentTime = mTime.QuadPart;
}

void TimeManager::Update()
{
	// 현재 프레임 시간 저장
	QueryPerformanceCounter(&mTime);
	mCurrentTime = mTime.QuadPart;

	// 프레임 시간 계산
	mDeltaTime = static_cast<float>(mCurrentTime - mPreviousTime) / static_cast<float>(mFrequency.QuadPart);
}

float TimeManager::GetDeltaTime()
{
	return mDeltaTime;
}

void TimeManager::SaveCurrentTime()
{
	mPreviousTime = mCurrentTime;
}

void TimeManager::LimitFrame(float _limit)
{
	assert(_limit >= 30 && _limit <= 240 && "Frame limit must be between 30 and 240.");

	mTargetFrameRate = _limit;
	mIsLimitFrame = true;
	mTargetOneFrameTime = 1.0f / mTargetFrameRate;
}

bool TimeManager::IsLimitFrame()
{
	return mIsLimitFrame;
}

bool TimeManager::CheckOverTargetFrame()
{
	return mDeltaTime >= mTargetOneFrameTime;
}


