#include "HighScoreSystem.h"

#include "../Events/WriteScoreEvent.h"
#include "../Events/ShowHighScoreEvent.h"

#include <fstream>

void HighScoreSystem::init()
{
	std::ifstream fileIn("high_score.txt");
	fileIn >> _highScore;
	fileIn.close();
}

void HighScoreSystem::update()
{
	auto writeScoreEvents = _entityManager->getEntitiesWithComponentAll<WriteScoreEvent>();
	if (writeScoreEvents.size() > 0)
	{
		WriteScoreEvent& event = writeScoreEvents[0]->getComponent<WriteScoreEvent>();
		if (event.score > _highScore)
		{
			std::ofstream fileOut("high_score.txt");
			fileOut << event.score;
			fileOut.close();

			_highScore = event.score;
		}

		_entityManager->createEntity().addComponent<ShowHighScoreEvent>(_highScore, event.score).entity->setDestroyNextFrame(true);
	}
}
