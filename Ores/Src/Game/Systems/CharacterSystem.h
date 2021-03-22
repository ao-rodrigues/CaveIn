#pragma once

#include "../../Engine/ECS/ECS.h"

class CharacterSystem : public System
{
public:
	using System::System;

	void init() override;
	virtual void update() override;

private:
	Entity* _king = nullptr;
	Entity* _huntress = nullptr;
	Entity* _heroKnight = nullptr;
	Entity* _knight = nullptr;
};
