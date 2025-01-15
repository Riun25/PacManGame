#pragma once
#include "Core.h"
#include "RTTI.h"
#include "Math/Vector2.h"

// ������ �⺻ ��ü
class ENGINE_API Actor :public RTTI
{
	// RTTI ����
	// ��Ÿ�ӿ� ������ Ÿ���� Ȯ���ϱ� ���� �۾�
	// dynamic_cast �����ڸ� Ȱ���ؾ� �ϴµ� ������ ���� Ŀ���� ���� ���
	RTTI_DECLARATIONS(Actor, RTTI)

	// Level Ŭ������ friend�� ����
	// private�� ������ �����ϵ���
	friend class Level;

public:
	Actor();
	virtual ~Actor();

	// ���� ó�� �Լ�
	virtual void Update(float _dTime);
	virtual void Draw();

	// Getter/Setter
	virtual void SetPosition(const Vector2& _newPos);
	inline Vector2 Position() const;

	inline bool IsActive() const { return isActive && !isExpired; }
	inline void SetActive(bool _active) { isActive = _active; }
	inline void Destroy() { isExpired = true; }

protected:
	// ������ ��ġ
	Vector2 pos;

	// Ȱ��ȭ ���������� ��Ÿ���� ����
	bool isActive;

	// ������ ���� ��û�� �ƴ��� ���θ� ��Ÿ���� ����
	bool isExpired;
};

