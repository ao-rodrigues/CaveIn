#pragma once

#include "Singleton.h"

class GameManager : public Singleton<GameManager>
{
public:
	void init();
	void update();

private:
	//Entity* player;
};