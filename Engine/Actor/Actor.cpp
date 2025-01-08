#include "PreCompiledHeader.h"
#include "Actor.h"

Actor::Actor()
	:pos(0,0), isActive(true), isExpired(false)
{

}

Actor::~Actor()
{

}

void Actor::Update(float _dTime)
{
}

void Actor::Draw()
{
}

void Actor::SetPosition(const Vector2& _newPos)
{
	pos = _newPos;
}

Vector2 Actor::Position() const
{
	return pos;
}
