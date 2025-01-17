#include "GameLevel.h"
#include "Engine/InputManager.h"
#include "Engine/Timer.h"
#include "Engine/Engine.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Enemy.h"
#include "Actor/Player.h"
#include "Actor/Item.h"

GameLevel::GameLevel(int _mapNum, int _score)
{
	// 커서 감추기
	InputManager::Get().SetCursorType(CURSOR_TYPE::NONE);

	// 파일 저장 @Todo : enum class 제작해서 그 개수로 할당
	mStageData.emplace_back(0, "../Assets/Maps/colisionTest.txt");
	mStageData.emplace_back(1, "../Assets/Maps/colisionItem.txt");
	mStageData.emplace_back(2, "../Assets/Maps/Stage1.txt");
	mStageData.emplace_back(3, "../Assets/Maps/Map.txt");
	mStageData.emplace_back(4, "../Assets/Maps/Stage2.txt");
	mStageData.emplace_back(5, "../Assets/Maps/Stage3.txt");

	mClearLevel = _mapNum;
	mScore = _score;
	LoadMap(_mapNum);
}

void GameLevel::LoadMap(const int _stageNum)
{
	std::string filePath = "";
	for (auto& e : mStageData)
	{
		if (e.first == _stageNum)
		{
			filePath = e.second;
			break;
		}
	}

	if (filePath == "")
	{
		std::cout << "존재하지 않는 파일입니다.\n";
		__debugbreak();
		return;
	}

	// 맵 파일 불러와 레벨 로드.
	// 파일 읽기
	FILE* file = nullptr;
	fopen_s(&file, filePath.c_str(), "rb");

	// 파일 처리
	if (file == nullptr)
	{
		std::cout << "파일 열기 실패.\n";
		__debugbreak();
		return;
	}

	// 파일 읽기
	// 끝위치로 이동
	fseek(file, 0, SEEK_END);

	// 이동한 위치의 FP 가져오기
	size_t readSize = ftell(file);

	// FP 원위치
	fseek(file, 0, SEEK_SET);
	// rewind(file); 같은 역할임

	// 파일 읽어서 버퍼에 담기
	char* buffer = new char[readSize + 1];
	size_t bytesRead = fread(buffer, 1, readSize, file);

	if (readSize != bytesRead)
	{
		std::cout << "읽어온 크기가 다름\n";
		__debugbreak();
		return;
	}

	buffer[readSize] = '\0';

	// 파일 읽을 때 사용할 인덱스
	int index = 0;

	// 좌표 계산을 위한 변수 선언
	int posX = 0;
	int posY = 0;

	while (index < static_cast<int>(bytesRead))
	{
		// 한 문자씩 읽기
		char mapChar = buffer[index++];

		// 개행 문자인 경우 처리
		if (mapChar == '\n')
		{
			++posY;
			mapXY.y = max(posY, mapXY.y);
			posX = 0;
			continue;
		}

		if (mapChar == '1')
		{
			//AddActor(new Wall(Vector2(posX, posY)));
			Wall* wall = new Wall(Vector2(posX, posY));
			mActorVec.PushBack(wall);
			mMapVec.PushBack(wall);
		}

		// 맵 문자가 .이면 그라운드 액터 생성
		else if (mapChar == '.')
		{
			Ground* ground = new Ground(Vector2(posX, posY));
			mActorVec.PushBack(ground);
			mMapVec.PushBack(ground);
			++mPrayNum;
		}

		// 맵 문자가 b이면 박스 액터 생성
		else if (mapChar == 'b')
		{
			Ground* ground = new Ground(Vector2(posX, posY));
			mActorVec.PushBack(ground);
			mMapVec.PushBack(ground);

			Enemy* enemy = new Enemy(Vector2(posX, posY), this);
			mActorVec.PushBack(enemy);
			mEnemyVec.PushBack(enemy);
		}

		// 맵 문자가 t이면 아이템 액터 생성
		else if (mapChar == 't')
		{

			Item* target = new Item(Vector2(posX, posY));
			mActorVec.PushBack(target);
			mMapVec.PushBack(target);
			mItemVec.PushBack(target);
		}

		// 맵 문자가 p이면 플레이어 액터 생성
		else if (mapChar == 'p')
		{
			Ground* ground = new Ground(Vector2(posX, posY));
			ground->SetImage(" "); // 처음 시작하는 곳은 먹이가 없다.
			mActorVec.PushBack(ground);
			mMapVec.PushBack(ground);

			player = new Player(Vector2(posX, posY), this);
			mActorVec.PushBack(player);
		}

		++posX;
		mapXY.x = max(posX, mapXY.x);
	}

	mMapData.resize(mapXY.y + 1);
	for (auto& e : mMapData)
	{
		e.resize(mapXY.x);
	}

	index = 0;
	posX = 0;
	posY = 0;

	while (index < static_cast<int>(bytesRead))
	{
		// 한 문자씩 읽기
		char mapChar = buffer[index++];

		// 개행 문자인 경우 처리
		if (mapChar == '\n')
		{
			++posY;
			posX = 0;
			continue;
		}

		if (mapChar == '1')
		{
			mMapData[posY][posX] = 1;
		}
		else
		{
			mMapData[posY][posX] = 0;
		}
		++posX;
	}

	// 여기서 Enemy에 전부 map을 전달해준다.
	for (auto& enemy : mEnemyVec)
	{
		enemy->mMapData = &mMapData;
		enemy->mMapXY = mapXY;
		enemy->player = player;
	}
	
	// 버퍼 삭제
	delete[] buffer;

	// 파일 닫기
	fclose(file);
}

void GameLevel::Update(float _dTime)
{
	Super::Update(_dTime);

	// 게임이 클리어됐으면, 게임 종료 처리
	if (mIsGameClear)
	{
		// 타이머
		static Timer timer(0.1f);
		timer.Update(_dTime);
		if (timer.IsTimeOut() == false)
		{
			return;
		}

		InputManager::Get().SetCursorPosition(0, Engine::Get().ScreenSize().y);

		// 메세지 출력
		Log("Game Clear!");

		// 쓰레드 정지
		Sleep(2000);
	}

	// 플레이어와 적들의 충돌 처리
	ProcessCollisionPlayerAndEnemy();
}

void GameLevel::Finalize()
{
	if (mIsGameClear)
	{
		// 더 이상 클리어할 레벨이 없다면 종료 처리
		++mClearLevel;
		if (mClearLevel == static_cast<int>(MAPDATA::STATGE1)) // @TODO: LENGTH로 변경
		{
			// 게임 종료 처리
			Engine::Get().QuitGame();
			return;
		}

		mIsGameClear = false;
		Engine::Get().LoadLevel(new GameLevel(mClearLevel, mScore));
	}
}

void GameLevel::Draw()
{
	// 맵 그리기
	for (auto* pActor : mMapVec)
	{
		// 플레이어 위치 확인
		if (pActor->Position() == player->Position())
		{
			continue;
		}

		// 박스 위치 확인
		bool shouldDraw = true;
		for (auto* pBox : mEnemyVec)
		{
			if (pActor->Position() == pBox->Position())
			{
				shouldDraw = false;
				break;
			}
		}
		// 맵 액터 그리기
		if (shouldDraw)
		{
			pActor->Draw();
		}
	}

	// 타겟 그리기
	for (auto* pTarget : mItemVec)
	{
		// 플레이어 위치 확인
		if (pTarget->Position() == player->Position())
		{
			continue;
		}

		// 박스 위치 확인
		bool shouldDraw = true;
		for (auto* pBox : mEnemyVec)
		{
			if (pTarget->Position() == pBox->Position())
			{
				shouldDraw = false;
				break;
			}
		}
		// 맵 액터 그리기
		if (shouldDraw)
		{
			pTarget->Draw();
		}
	}

	// 박스 그리기
	for (auto* pActor : mEnemyVec)
	{
		// 박스 액터 그리기
		pActor->Draw();
	}

	// 플레이어 그리기
	player->Draw();

	// 점수 출력
	SetColor(COLOR::YELLOW);
	InputManager::Get().SetCursorPosition(0, Engine::Get().ScreenSize().y + 1);
	Log("Score: %d", mScore);
	SetColor(COLOR::WHITE);
}

bool GameLevel::CanPlayerMove(const Vector2& _pos)
{
	// 게임이 클리어 된 경우 바로 종료
	if (mIsGameClear)
	{
		return false;
	}

	// 이동하려는 위치에 벽이 있는지 확인
	DrawableActor* searchedActor = nullptr;

	// 먼저 이동하려는 위치의 엑터 찾기
	for (auto* pActor : mMapVec)
	{
		if (pActor->Position() == _pos)
		{
			searchedActor = pActor;
			break;
		}
	}

	// 검색한 액터가 벽인지 확인
	if (searchedActor->As<Wall>())
	{
		return false;
	}
	// 검색한 액터가 이동 가능한 액터(땅/타겟)인지 확인
	if (searchedActor->As<Ground>())
	{
		if (searchedActor && strcmp(searchedActor->Image(), "·") == 0)
		{
			searchedActor->SetImage(" ");
			// @Todo : 맵 바뀔 때 초기화
			++mChangingNum;
			mScore += 20;

			//게임 클리어 여부 확인
			mIsGameClear = CheckGameClear();
		}
		return true;
	}
	// 검색한 액터가 아이템인지 확인
	if (searchedActor->As<Item>())
	{
		if (searchedActor && strcmp(searchedActor->Image(), "◈") == 0)
		{
			searchedActor->SetImage(" ");
			mScore += 100;
			// @Todo : 플레이어 색 변경 및 잡아먹히는 관계 반전

		}
		return true;
	}
	return false;
}


bool GameLevel::CanEnemyMove(const Vector2& _pos)
{
	// 게임이 클리어 된 경우 바로 종료
	if (mIsGameClear)
	{
		return false;
	}

	// 맵 크기를 벗어나면 그냥 종료
	if (_pos.x < 0 || _pos.y < 0 || _pos.x > mapXY.y || _pos.y > mapXY.y)
	{
		return false;
	}

	// 이동하려는 위치에 벽이 있는지 확인
	DrawableActor* searchedActor = nullptr;

	// 먼저 이동하려는 위치의 엑터 찾기
	for (auto* pActor : mMapVec)
	{
		if (pActor->Position() == _pos)
		{
			searchedActor = pActor;
			break;
		}
	}

	// 길 탐색에서는 맵을 넘어서는 위치도 탐색할 가능성이 있다.
	/*if (searchedActor == nullptr)
	{
		return false;
	}*/

	// 검색한 액터가 벽인지 확인
	if (searchedActor->As<Wall>())
	{
		return false;
	}
	// 검색한 액터가 이동 가능한 액터(땅/아이템)인지 확인
	if (searchedActor->As<Ground>() || searchedActor->As<Item>())
	{
		return true;
	}
	return false;
}

void GameLevel::ProcessCollisionPlayerAndEnemy()
{
	// 예외처리
	if (player == nullptr || mEnemyVec.Size() == 0)
	{
		return;
	}
	
	// 적들을 순회하면서 충돌 처리
	for (auto& e : mEnemyVec)
	{
		// 플레이어가 비활성화 상태라면 종료
		if (!player->IsActive())
		{
			return;
		}

		// 적이 비활성화 상태라면 스킵
		if (!e->IsActive())
		{
			continue;
		}

		// 충돌 처리
		if (player->Intersect(*e))
		{
			// 충돌했으면 플레이어 제거
			player->Destroy();

			InputManager::Get().SetCursorPosition(0, Engine::Get().ScreenSize().y - 1);
			Log("GameOver!\n");

			// 약 2초간 정지
			Sleep(2000);

			// 게임 종료
			Engine::Get().QuitGame();
		}
	}
}

bool GameLevel::CheckGameClear()
{
	if (mPrayNum <= mChangingNum)
	{
		return true;
	}
	return false;
	// @Todo : 디버깅을 위해 코드를 뜯어놈. 나중에는 아래로 바꿀 것
	// return mPrayNum <= mChangingNum
}
