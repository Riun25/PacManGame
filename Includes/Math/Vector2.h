#pragma once
#include "Core.h"

class ENGINE_API Vector2
{
public:
	Vector2();
	Vector2(int _x, int _y);
	~Vector2() = default;

	//������ �����ε�
	// ��
	Vector2 operator+(const Vector2& _other);
	Vector2 operator-(const Vector2& _other);
	bool operator==(const Vector2& _other) const;
	bool operator!=(const Vector2& _other) const;

public:
	// x��ǥ, y��ǥ
	int x = 0;
	int y = 0;
};