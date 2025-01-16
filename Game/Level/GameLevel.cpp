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
	// Ŀ�� ���߱�
	InputManager::Get().SetCursorType(CURSOR_TYPE::NONE);

	// �� ���� �ҷ��� ���� �ε�.
		// ���� �б�
	FILE* file = nullptr;
	fopen_s(&file, "../Assets/Maps/Map.txt", "rb");
	//fopen_s(&file, "../Assets/Maps/Stage2.txt", "rb");

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
		}

		// �� ���ڰ� b�̸� �ڽ� ���� ����
		else if (mapChar == 'b')
		{
			Ground* ground = new Ground(Vector2(posX, posY));
			mActorVec.PushBack(ground);
			mMapVec.PushBack(ground);

			Box* box = new Box(Vector2(posX, posY));
			mActorVec.PushBack(box);
			mBoxVec.PushBack(box);
		}

		// �� ���ڰ� b�̸� �ڽ� ���� ����
		else if (mapChar == 't')
		{

			Target* target = new Target(Vector2(posX, posY));
			mActorVec.PushBack(target);
			mMapVec.PushBack(target);
			mTargetVec.PushBack(target);
		}

		// �� ���ڰ� b�̸� �ڽ� ���� ����
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
		// �뷫 �� �������� ������ �ð� ���
		static float elapsedTime = 0.0f;
		elapsedTime += _dTime;
		if (elapsedTime < 0.1f)
		{
			return;
		}

		// Ÿ�̸�
		static Timer timer(0.1f);
		timer.Update(_dTime);
		if (!timer.IsTimeOut())
		{
			return;
		}

		InputManager::Get().SetCursorPosition(0, Engine::Get().ScreenSize().y);

		// �޼��� ���
		Log("Game Clear!");

		// ������ ����
		Sleep(2000);

		// ���� ���� ó��
		Engine::Get().QuitGame();
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
		for (auto* pBox : mBoxVec)
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
	for (auto* pTarget : mTargetVec)
	{
		// �÷��̾� ��ġ Ȯ��
		if (pTarget->Position() == player->Position())
		{
			continue;
		}

		// �ڽ� ��ġ Ȯ��
		bool shouldDraw = true;
		for (auto* pBox : mBoxVec)
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
	for (auto* pActor : mBoxVec)
	{
		// �ڽ� ���� �׸���
		pActor->Draw();
	}

	// �÷��̾� �׸���
	player->Draw();
}

bool GameLevel::CanPlayerMove(const Vector2& _pos)
{
	// ������ Ŭ���� �� ��� �ٷ� ����
	if (mIsGameClear)
	{
		return false;
	}

	// �ڽ� �˻�
	Box* searchedBox = nullptr;
	for (auto* box : mBoxVec)
	{
		if (box->Position() == _pos)
		{
			searchedBox = box;
			break;
		}
	}

	// �ڽ��� ���� �� ó��
	if (searchedBox)
	{
		// �̵� ����
		int dirX = static_cast<int>(_pos.x - player->Position().x);
		int dirY = static_cast<int>(_pos.y - player->Position().y);

		// �ڽ��� �̵��� �� ��ġ
		Vector2 newPos = searchedBox->Position() + Vector2(dirX, dirY);

		// �߰� �˻�(�ڽ�)
		for (auto* pBox : mBoxVec)
		{
			// ����ó��
			if (pBox == searchedBox)
			{
				continue;
			}
			// �̵��� ��ġ�� �ٸ� �ڽ��� �ִٸ� �̵� �Ұ�
			if (pBox->Position() == newPos)
			{
				return false;
			}
		}

		// �߰� �˻�(��)
		for (auto* pActor : mMapVec)
		{
			// �̵��Ϸ��� ��ġ�� �ִ� ���� �˻�
			if (pActor->Position() == newPos)
			{
				// ����ȯ�� ���� ��ü�� Ÿ�� Ȯ��

				// �̵��Ϸ��� ��ġ�� ���� ������ �̵� �Ұ�
				if (pActor->As<Wall>())
				{
					return false;
				}

				// ���̳� Ÿ���̸� �̵� ����
				if (pActor->As<Ground>() || pActor->As<Target>())
				{
					// �ڽ� �̵� ó��
					searchedBox->SetPosition(newPos);

					//���� Ŭ���� ���� Ȯ��
					mIsGameClear = CheckGameClear();

					return true;
				}
			}
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
	if (searchedActor->As<Ground>() || searchedActor->As<Target>())
	{
		return true;
	}

	return false;
}

bool GameLevel::CheckGameClear()
{
	// ���� Ȯ���� ���� ����
	int currentScore = 0;
	int targetScore = mTargetVec.Size();

	//Ÿ�� ��ġ�� ��ġ�� �ڽ� ���� ����
	for (auto* pBox : mBoxVec)
	{
		for (auto* pTarget : mTargetVec)
		{
			// ���� Ȯ��
			if (pBox->Position() == pTarget->Position())
			{
				++currentScore;
				continue;
			}
		}
	}

	// ȹ���� ������ ��ǥ ������ ������ ��
	return currentScore == targetScore;
}
