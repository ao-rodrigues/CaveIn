#pragma once

#include "../../Engine/ECS/ECS.h"

class HoverCursorSystem : public System
{
public:
	using System::System;

	virtual void update() override;

private:
	bool _cursorInUse = false;
};