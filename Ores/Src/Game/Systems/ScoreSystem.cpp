#include "ScoreSystem.h"

#include <cmath>

#include "../Events/OreDestroyedEvent.h"
#include "../../Engine/Engine.h"

void ScoreSystem::init()
{
	AssetManager::instance().loadFont("Alagard", "Assets/Fonts/Alagard.ttf", 18);

	SDL_Color textColor = { 255, 255, 255, 255 };
	std::string displayText = "Score: " + std::to_string(_score);

	_scoreDisplayText = &Engine::instance().createEntity().addComponent<Text>("Alagard", 0, displayText, textColor);
	_scoreDisplayText->setPosition(Vector2(10.f, 10.f));
}

void ScoreSystem::update()
{
	auto oreDestroyedEvents = _entityManager->getEntitiesWithComponent<OreDestroyedEvent>();
	for (auto& event : oreDestroyedEvents)
	{
		OreData oreData = event->getComponent<OreDestroyedEvent>().oreData;
		_score += oreData.destructionPoints;
		updateScoreDisplay(_score);

		//event->destroy();
	}
}

void ScoreSystem::updateScoreDisplay(int newScore)
{
	std::string text = "Score: " + std::to_string(newScore);
	_scoreDisplayText->setText("Alagard", text);
}

void ScoreSystem::updateLevel(int newScore)
{
	if (newScore >= _levelUpScore)
	{
		_level++;
		_levelUpScore += round(_levelUpScore * _levelUpScoreIncreaseRate);
	}
}
