#pragma once
#include "Actor/DrawableActor.h"

// Enemy 종류를 4개로 변경하면서 상속 구조를 사용할 것인지 고민해본다.
class GameLevel;
class AStar;
class Enemy : public DrawableActor
{
	// 적 캐릭터가 이동할 방향
	enum class DIRECTION
	{
		NONE = -1,
		LEFT,
		RIGHT
	};

	RTTI_DECLARATIONS(Enemy, DrawableActor)
public:
	Enemy(const Vector2& _pos, GameLevel* _level);
	~Enemy(); // 상속으로 수정하면 virtual 붙여야 한다.

	virtual void Update(float _dTime) override;

public:
	std::vector<std::vector<int>>* mMapData;
	Vector2 mMapXY = Vector2();
	DrawableActor* player = nullptr;

private:
	// 게임 레벨을 참조하는 변수
	GameLevel* mRefLevel = nullptr;

	DIRECTION mDir;

	// 이동에 필요한 변수
	Vector2 mPos = Vector2();
	float mSpeed = 0.01f;

	// 경로 찾기는 오직 Enemy들만 필요하므로, Astar 클래스는 여기에 위치
	AStar* pAstar;
	// 본인 경로
	std::vector<Vector2> mOwnPaths;
	// 현재 경로의 인덱스
	int mPathIdx = 0;

	// Enemy들은 서로의 위치를 확인할 수 있어야 한다. 
	// 자신의 위치로부터 5칸 이내에 유령이 있으면 지속적으로 재탐색 시켜서 충돌을 안 일어나게 해야 한다.
	
};