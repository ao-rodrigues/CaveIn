#pragma once

#include "../../Engine/ECS/ECS.h"
#include "../../Engine/ECS/Components/Audio.h"

class SoundSystem : public System
{
public:
	using System::System;

	void init() override;
	virtual void update() override;

private:
	Audio* _oreDestroyedSound = nullptr;
	Audio* _levelUpSound = nullptr;
};
