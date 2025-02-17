#include "PreCompiledHeader.h"
#include "Vector2.h"

Vector2::Vector2(int _x, int _y)
    :x(_x), y(_y)
{
}

Vector2 Vector2::operator+(const Vector2& _other)
{
    return Vector2(x + _other.x, y + _other.y);
}

Vector2 Vector2::operator-(const Vector2& _other)
{
    return Vector2(x - _other.x, y - _other.y);
}

bool Vector2::operator==(const Vector2& _other)
{
    return x == _other.x && y == _other.y;
}

bool Vector2::operator!=(const Vector2& _other)
{
    return x != _other.x || y != _other.y;
}
