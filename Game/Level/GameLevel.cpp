#include "GameLevel.h"
#include "Engine/InputManager.h"
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