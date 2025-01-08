#pragma once

#include "Actor/DrawableActor.h"

class Player : public DrawableActor
{
	RTTI_DECLARATIONS(Player, DrawableActor)

public:
	Player(char _img = 'P');

	virtual void Update(float _dTime) override;
};