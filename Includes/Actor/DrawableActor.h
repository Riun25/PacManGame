#pragma once

#include "Actor.h"

class ENGINE_API DrawableActor : public Actor
{
	// RTTI
	RTTI_DECLARATIONS(DrawableActor, Actor)

public:
	DrawableActor(const char* _img = "");
	//virtual ~DrawableActor() = default;
	virtual ~DrawableActor();

	virtual void Draw() override;
	virtual void SetPosition(const Vector2& _newPos) override;

	// �浹 Ȯ�� �Լ�
	bool Intersect(const DrawableActor& _other);

	// Getter
	inline int Width() const { return width; }
	inline char* Image() const { return image; }
	void SetImage(const char* _img);

protected:
	// ȭ�鿡 �׸� ���� ��
	char* image;

	// �ʺ�(���ڿ� ����)
	int width = 0;

	// ���� ��
	COLOR color = COLOR::WHITE;
};