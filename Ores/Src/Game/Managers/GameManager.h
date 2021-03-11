#pragma once

#include "Engine.h"
#include "Singleton.h"

class GameManager : public Singleton<GameManager>
{
public:
	void init();
	void update();

private:

};