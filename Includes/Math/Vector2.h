#pragma once
#include "Core.h"

class ENGINE_API Vector2
{
public:
	Vector2();
	Vector2(int _x, int _y);
	~Vector2() = default;

	//연산자 오버로딩
	// 비교
	Vector2 operator+(const Vector2& _other);
	Vector2 operator-(const Vector2& _other);
	bool operator==(const Vector2& _other) const;
	bool operator!=(const Vector2& _other) const;

public:
	// x좌표, y좌표
	int x = 0;
	int y = 0;
};