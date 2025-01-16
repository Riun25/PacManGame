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
	// Ŀ�� ���߱�
	InputManager::Get().SetCursorType(CURSOR_TYPE::NONE);

	// ���� ���� @Todo : enum class �����ؼ� �� ������ �Ҵ�
	mMapData.emplace_back(0, "../Assets/Maps/colisionTest.txt");
	mMapData.emplace_back(1, "../Assets/Maps/colisionItem.txt");
	mMapData.emplace_back(2, "../Assets/Maps/Stage1.txt");
	mMapData.emplace_back(3, "../Assets/Maps/Map.txt");
	mMapData.emplace_back(4, "../Assets/Maps/Stage2.txt");
	mMapData.emplace_back(5, "../Assets/Maps/Stage3.txt");

	mClearLevel = _mapNum;
	mScore = _score;
	LoadMap(_mapNum);
}

void GameLevel::LoadMap(const int _stageNum)
{
	std::string filePath = "";
	for (auto& e : mMapData)
	{
		if (e.first == _stageNum)
		{
			filePath = e.second;
			break;
		}
	}

	if (filePath == "")
	{
		std::cout << "�������� �ʴ� �����Դϴ�.\n";
		__debugbreak();
		return;
	}

	// �� ���� �ҷ��� ���� �ε�.
	// ���� �б�
	FILE* file = nullptr;
	fopen_s(&file, filePath.c_str(), "rb");

	// ���� ó��
	if (file == nullptr)
	{
		std::cout << "���� ���� ����.\n";
		__debugbreak();
		return;
	}

	// ���� �б�
	// ����ġ�� �̵�
	fseek(file, 0, SEEK_END);

	// �̵��� ��ġ�� FP ��������
	size_t readSize = ftell(file);

	// FP ����ġ
	fseek(file, 0, SEEK_SET);
	// rewind(file); ���� ������

	// ���� �о ���ۿ� ���
	char* buffer = new char[readSize + 1];
	size_t bytesRead = fread(buffer, 1, readSize, file);

	if (readSize != bytesRead)
	{
		std::cout << "�о�� ũ�Ⱑ �ٸ�\n";
		__debugbreak();
		return;
	}

	buffer[readSize] = '\0';

	// ���� ���� �� ����� �ε���
	int index = 0;

	// ��ǥ ����� ���� ���� ����
	int posX = 0;
	int posY = 0;

	while (index < static_cast<int>(bytesRead))
	{
		// �� ���ھ� �б�
		char mapChar = buffer[index++];

		// ���� ������ ��� ó��
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

		// �� ���ڰ� .�̸� �׶��� ���� ����
		else if (mapChar == '.')
		{
			Ground* ground = new Ground(Vector2(posX, posY));
			mActorVec.PushBack(ground);
			mMapVec.PushBack(ground);
			++mPrayNum;
		}

		// �� ���ڰ� b�̸� �ڽ� ���� ����
		else if (mapChar == 'b')
		{
			Ground* ground = new Ground(Vector2(posX, posY));
			mActorVec.PushBack(ground);
			mMapVec.PushBack(ground);

			Enemy* box = new Enemy(Vector2(posX, posY));
			mActorVec.PushBack(box);
			mEnemyVec.PushBack(box);
		}

		// �� ���ڰ� t�̸� ������ ���� ����
		else if (mapChar == 't')
		{

			Item* target = new Item(Vector2(posX, posY));
			mActorVec.PushBack(target);
			mMapVec.PushBack(target);
			mItemVec.PushBack(target);
		}

		// �� ���ڰ� p�̸� �÷��̾� ���� ����
		else if (mapChar == 'p')
		{
			Ground* ground = new Ground(Vector2(posX, posY));
			ground->SetImage(" "); // ó�� �����ϴ� ���� ���̰� ����.
			mActorVec.PushBack(ground);
			mMapVec.PushBack(ground);

			player = new Player(Vector2(posX, posY), this);
			mActorVec.PushBack(player);
		}

		++posX;
	}

	// ���� ����
	delete[] buffer;

	// ���� �ݱ�
	fclose(file);
}

void GameLevel::Update(float _dTime)
{
	Super::Update(_dTime);

	// ������ Ŭ���������, ���� ���� ó��
	if (mIsGameClear)
	{
		// Ÿ�̸�
		static Timer timer(0.1f);
		timer.Update(_dTime);
		if (timer.IsTimeOut() == false)
		{
			return;
		}

		InputManager::Get().SetCursorPosition(0, Engine::Get().ScreenSize().y);

		// �޼��� ���
		Log("Game Clear!");

		// ������ ����
		Sleep(2000);
	}

	// �÷��̾�� ������ �浹 ó��
	ProcessCollisionPlayerAndEnemy();
}

void GameLevel::Finalize()
{
	if (mIsGameClear)
	{
		// �� �̻� Ŭ������ ������ ���ٸ� ���� ó��
		++mClearLevel;
		if (mClearLevel == static_cast<int>(MAPDATA::STATGE1)) // @TODO: LENGTH�� ����
		{
			// ���� ���� ó��
			Engine::Get().QuitGame();
			return;
		}

		mIsGameClear = false;
		Engine::Get().LoadLevel(new GameLevel(mClearLevel, mScore));
	}
}

void GameLevel::Draw()
{
	// �� �׸���
	for (auto* pActor : mMapVec)
	{
		// �÷��̾� ��ġ Ȯ��
		if (pActor->Position() == player->Position())
		{
			continue;
		}

		// �ڽ� ��ġ Ȯ��
		bool shouldDraw = true;
		for (auto* pBox : mEnemyVec)
		{
			if (pActor->Position() == pBox->Position())
			{
				shouldDraw = false;
				break;
			}
		}
		// �� ���� �׸���
		if (shouldDraw)
		{
			pActor->Draw();
		}
	}

	// Ÿ�� �׸���
	for (auto* pTarget : mItemVec)
	{
		// �÷��̾� ��ġ Ȯ��
		if (pTarget->Position() == player->Position())
		{
			continue;
		}

		// �ڽ� ��ġ Ȯ��
		bool shouldDraw = true;
		for (auto* pBox : mEnemyVec)
		{
			if (pTarget->Position() == pBox->Position())
			{
				shouldDraw = false;
				break;
			}
		}
		// �� ���� �׸���
		if (shouldDraw)
		{
			pTarget->Draw();
		}
	}

	// �ڽ� �׸���
	for (auto* pActor : mEnemyVec)
	{
		// �ڽ� ���� �׸���
		pActor->Draw();
	}

	// �÷��̾� �׸���
	player->Draw();

	// ���� ���
	SetColor(COLOR::YELLOW);
	InputManager::Get().SetCursorPosition(0, Engine::Get().ScreenSize().y + 1);
	Log("Score: %d", mScore);
	SetColor(COLOR::WHITE);
}

bool GameLevel::CanPlayerMove(const Vector2& _pos)
{
	// ������ Ŭ���� �� ��� �ٷ� ����
	if (mIsGameClear)
	{
		return false;
	}

	// �ڽ� �˻�
	Enemy* searchedBox = nullptr;
	for (auto* box : mEnemyVec)
	{
		if (box->Position() == _pos)
		{
			searchedBox = box;
			break;
		}
	}

	// �̵��Ϸ��� ��ġ�� ���� �ִ��� Ȯ��
	DrawableActor* searchedActor = nullptr;

	// ���� �̵��Ϸ��� ��ġ�� ���� ã��
	for (auto* pActor : mMapVec)
	{
		if (pActor->Position() == _pos)
		{
			searchedActor = pActor;
			break;
		}
	}

	// �˻��� ���Ͱ� ������ Ȯ��
	if (searchedActor->As<Wall>())
	{
		return false;
	}
	// �˻��� ���Ͱ� �̵� ������ ����(��/Ÿ��)���� Ȯ��
	if (searchedActor->As<Ground>())
	{
		if (searchedActor && strcmp(searchedActor->Image(), "��") == 0)
		{
			searchedActor->SetImage(" ");
			// @Todo : �� �ٲ� �� �ʱ�ȭ
			++mChangingNum;
			mScore += 20;

			//���� Ŭ���� ���� Ȯ��
			mIsGameClear = CheckGameClear();
		}
		return true;
	}

	if (searchedActor->As<Item>())
	{
		if (searchedActor && strcmp(searchedActor->Image(), "��") == 0)
		{
			searchedActor->SetImage(" ");
			mScore += 100;
			// @Todo : �÷��̾� �� ���� �� ��Ƹ����� ���� ����

		}
		return true;
	}
	return false;
}

void GameLevel::ProcessCollisionPlayerAndEnemy()
{
	// ����ó��
	if (player == nullptr || mEnemyVec.Size() == 0)
	{
		return;
	}
	
	// ������ ��ȸ�ϸ鼭 �浹 ó��
	for (auto& e : mEnemyVec)
	{
		// �÷��̾ ��Ȱ��ȭ ���¶�� ����
		if (!player->IsActive())
		{
			return;
		}

		// ���� ��Ȱ��ȭ ���¶�� ��ŵ
		if (!e->IsActive())
		{
			continue;
		}

		// �浹 ó��
		if (player->Intersect(*e))
		{
			// �浹������ �÷��̾� ����
			player->Destroy();

			InputManager::Get().SetCursorPosition(0, Engine::Get().ScreenSize().y - 1);
			Log("GameOver!\n");

			// �� 2�ʰ� ����
			Sleep(2000);

			// ���� ����
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
	// @Todo : ������� ���� �ڵ带 ����. ���߿��� �Ʒ��� �ٲ� ��
	// return mPrayNum <= mChangingNum
}
