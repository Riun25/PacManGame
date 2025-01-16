#pragma once
#include "Core.h"
#include "RTTI.h"
#include "Container/List.h"

// ���� ����
class Actor;
class ENGINE_API Level : public RTTI
{
	// RTTI ����
	RTTI_DECLARATIONS(Level, RTTI)

public:
	Level();
	virtual ~Level();

	//���� �߰� �Լ�
	void AddActor(Actor* _newActor);

	// ���� ��û�� �� ���͸� �����ϴ� �Լ�
	//void DestroyActor();
	void ProcessAddedAndDestroyedActor();

	// ���� ó�� �Լ�
	virtual void Update(float _dTime);
	virtual void Draw();
	virtual void Finalize();

protected:
	// ���� ������ ��ġ�Ǵ� ��ü(����) �迭
	List<Actor*> mActorVec;

	// �߰� ��û�� ����
	Actor* mAddRequestedActor = nullptr;
};

