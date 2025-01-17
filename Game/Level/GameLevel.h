#pragma once

#include "Level/Level.h"
#include "Math/Vector2.h"
#include <vector>
#include <string>

// 맵 정보 이넘
enum class MAPDATA
{
	CTEST,	// 충돌 테스트
	CITEST,	// 아이템 및 충돌 테스트
	ETEST,	// 적군 움직임 테스트
	STATGE1,
	STATGE2,
	STATGE3,
	LENGTH,
};

// 팩맨 게임 레벨
class DrawableActor;
class Player;
class Enemy;
class Item;
class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel, Level)
public:
	GameLevel(int _mapNum = 0, int _score = 0);

	// 스테이지를 로드하는 함수
	void LoadMap(const int _stageNum);

	// 업데이트 함수
	virtual void Update(float _dTime) override;

	virtual void Finalize() override;


	// 레벨의 그리기 함수
	virtual void Draw() override;

	// 플레이어가 이동이 가능한지 확인하는 함수
	bool CanPlayerMove(const Vector2& _pos);
	// 유령이 이동이 가능한지 확인하는 함수
	bool CanEnemyMove(const Vector2& _pos);
	
	// 플레이어와 유령이 충돌하는지 확인하는 함수
	void ProcessCollisionPlayerAndEnemy();

private:
	// 박스를 옮긴 뒤 게임을 클리어했는지 확인하는 함수
	bool CheckGameClear();

private:
	// 벽/땅 액터 배열
	List<DrawableActor*> mMapVec;
	// 적군 액터
	List<Enemy*> mEnemyVec;
	// 아이템 액터
	List<Item*> mItemVec;
	// 플레이어 엑터
	DrawableActor* player = nullptr;

	// 게임 클리어 변수
	bool mIsGameClear = false;
	// 게임 점수 변수
	int mScore = 0;

	// 먹이 개수
	int mPrayNum = 0;
	// 변환된 개수
	int mChangingNum = 0;

	// 스테이지 데이터
	std::vector<std::pair<int, std::string>> mStageData;
	// 맵의 가로세로 저장
	Vector2 mapXY = Vector2();
	// 맵 데이터
	std::vector<std::vector<int>> mMapData = {};

	// 최대 클리어 레벨을 저장하는 변수
	int mClearLevel = 0;
};