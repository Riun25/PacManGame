#include "GameLevel.h"
#include "Engine/InputManager.h"
#include "Engine/Timer.h"
#include "Engine/Engine.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Box.h"
#include "Actor/Player.h"
#include "Actor/Target.h"

GameLevel::GameLevel()
{
	// 커서 감추기
	InputManager::Get().SetCursorType(CURSOR_TYPE::NONE);

	// 맵 파일 불러와 레벨 로드.
		// 파일 읽기
	FILE* file = nullptr;
	fopen_s(&file, "../Assets/Maps/Map.txt", "rb");
	//fopen_s(&file, "../Assets/Maps/Stage2.txt", "rb");

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
		}

		// 맵 문자가 b이면 박스 액터 생성
		else if (mapChar == 'b')
		{
			Ground* ground = new Ground(Vector2(posX, posY));
			mActorVec.PushBack(ground);
			mMapVec.PushBack(ground);

			Box* box = new Box(Vector2(posX, posY));
			mActorVec.PushBack(box);
			mBoxVec.PushBack(box);
		}

		// 맵 문자가 b이면 박스 액터 생성
		else if (mapChar == 't')
		{

			Target* target = new Target(Vector2(posX, posY));
			mActorVec.PushBack(target);
			mMapVec.PushBack(target);
			mTargetVec.PushBack(target);
		}

		// 맵 문자가 b이면 박스 액터 생성
		else if (mapChar == 'p')
		{
			Ground* ground = new Ground(Vector2(posX, posY));
			mActorVec.PushBack(ground);
			mMapVec.PushBack(ground);

			player = new Player(Vector2(posX, posY), this);
			mActorVec.PushBack(player);
		}

		++posX;
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
		// 대략 한 프레임의 정도의 시간 대기
		static float elapsedTime = 0.0f;
		elapsedTime += _dTime;
		if (elapsedTime < 0.1f)
		{
			return;
		}

		// 타이머
		static Timer timer(0.1f);
		timer.Update(_dTime);
		if (!timer.IsTimeOut())
		{
			return;
		}

		InputManager::Get().SetCursorPosition(0, Engine::Get().ScreenSize().y);

		// 메세지 출력
		Log("Game Clear!");

		// 쓰레드 정지
		Sleep(2000);

		// 게임 종료 처리
		Engine::Get().QuitGame();
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
		for (auto* pBox : mBoxVec)
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
	for (auto* pTarget : mTargetVec)
	{
		// 플레이어 위치 확인
		if (pTarget->Position() == player->Position())
		{
			continue;
		}

		// 박스 위치 확인
		bool shouldDraw = true;
		for (auto* pBox : mBoxVec)
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
	for (auto* pActor : mBoxVec)
	{
		// 박스 액터 그리기
		pActor->Draw();
	}

	// 플레이어 그리기
	player->Draw();
}

bool GameLevel::CanPlayerMove(const Vector2& _pos)
{
	// 게임이 클리어 된 경우 바로 종료
	if (mIsGameClear)
	{
		return false;
	}

	// 박스 검색
	Box* searchedBox = nullptr;
	for (auto* box : mBoxVec)
	{
		if (box->Position() == _pos)
		{
			searchedBox = box;
			break;
		}
	}

	// 박스가 있을 때 처리
	if (searchedBox)
	{
		// 이동 방향
		int dirX = static_cast<int>(_pos.x - player->Position().x);
		int dirY = static_cast<int>(_pos.y - player->Position().y);

		// 박스가 이동할 새 위치
		Vector2 newPos = searchedBox->Position() + Vector2(dirX, dirY);

		// 추가 검색(박스)
		for (auto* pBox : mBoxVec)
		{
			// 예외처리
			if (pBox == searchedBox)
			{
				continue;
			}
			// 이동할 위치에 다른 박스가 있다면 이동 불가
			if (pBox->Position() == newPos)
			{
				return false;
			}
		}

		// 추가 검색(맵)
		for (auto* pActor : mMapVec)
		{
			// 이동하려는 위치에 있는 액터 검색
			if (pActor->Position() == newPos)
			{
				// 형변환을 통해 물체의 타입 확인

				// 이동하려는 위치에 벽이 있으면 이동 불가
				if (pActor->As<Wall>())
				{
					return false;
				}

				// 땅이나 타겟이면 이동 가능
				if (pActor->As<Ground>() || pActor->As<Target>())
				{
					// 박스 이동 처리
					searchedBox->SetPosition(newPos);

					//게임 클리어 여부 확인
					mIsGameClear = CheckGameClear();

					return true;
				}
			}
		}
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
	if (searchedActor->As<Ground>() || searchedActor->As<Target>())
	{
		return true;
	}

	return false;
}

bool GameLevel::CheckGameClear()
{
	// 점수 확인을 위한 변수
	int currentScore = 0;
	int targetScore = mTargetVec.Size();

	//타겟 위치에 배치된 박스 개수 세기
	for (auto* pBox : mBoxVec)
	{
		for (auto* pTarget : mTargetVec)
		{
			// 점수 확인
			if (pBox->Position() == pTarget->Position())
			{
				++currentScore;
				continue;
			}
		}
	}

	// 획득한 점수가 목표 점수와 같은지 비교
	return currentScore == targetScore;
}
