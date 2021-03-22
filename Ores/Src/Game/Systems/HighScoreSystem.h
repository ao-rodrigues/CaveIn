#pragma once

#include "../../Engine/ECS/ECS.h"

class HighScoreSystem : public System
{
public:
	using System::System;

	void init() override;
	virtual void update() override;

private:
	//std::fstream* _file;
	//std::ifstream* _fileIn;
	//std::ofstream* _fileOut;
	int _highScore = 0;
};