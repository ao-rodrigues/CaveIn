#include "ScoreSystem.h"

#include <cmath>

#include "../../Engine/Engine.h"
#include "../Events/OreDestroyedEvent.h"
#include "../Events/LevelUpEvent.h"

void ScoreSystem::init()
{
	AssetManager::instance().loadFont("ScoreFont", "Assets/Fonts/Alagard.ttf", 18);

	AssetManager::instance().loadTexture("ProgressBarBg", "Assets/Textures/progress_bar_bg.png");
	AssetManager::instance().loadTexture("ProgressBarFg", "Assets/Textures/progress_bar_fg.png");

	SDL_Color textColor = { 255, 255, 255, 255 };
	std::string scoreDisplayText = "Score: " + std::to_string(_score);

	_scoreDisplayText = &Engine::instance().createEntity().addComponent<Text>("ScoreFont", 0, scoreDisplayText, textColor);
	_scoreDisplayText->setPosition(Vector2(10.f, 10.f));

	std::string levelDisplayText = "Level: " + std::to_string(_level);
	_levelDisplayText = &Engine::instance().createEntity().addComponent<Text>("ScoreFont", 0, levelDisplayText, textColor);
	_levelDisplayText->setPosition(Vector2(150.f, 10.f));

	_levelProgressBarBg = &Engine::instance().createEntity().addComponent<Sprite>(RenderLayer::UI, 0, "ProgressBarBg", 0, 0, 125, 25);
	_levelProgressBarBg->transform->position.x = 230.f;
	_levelProgressBarBg->transform->position.y = 5.f;

	_levelProgressBarFg = &Engine::instance().createEntity().addComponent<Sprite>(RenderLayer::UI, 1, "ProgressBarFg", 0, 0, 113, 16);
	_levelProgressBarFg->transform->position.x = 230.f + (125.f - 113.f) / 2.f;
	_levelProgressBarFg->transform->position.y = 5.f + (25.f - 16.f) / 2.f;
	_levelProgressBarFg->srcWidth = 0;
	_levelProgressBarFg->dstWidth = 0;
}

void ScoreSystem::update()
{
	auto oreDestroyedEvents = _entityManager->getEntitiesWithComponentAll<OreDestroyedEvent>();
	for (auto& event : oreDestroyedEvents)
	{
		OreData oreData = event->getComponent<OreDestroyedEvent>().oreData;
		_score += oreData.destructionPoints;
		_scoreInLevel += oreData.destructionPoints;
		updateScoreDisplay(_score);
		updateLevel(_scoreInLevel);
		//event->destroy();
	}
}

void ScoreSystem::updateScoreDisplay(int newScore)
{
	std::string text = "Score: " + std::to_string(newScore);
	_scoreDisplayText->setText("ScoreFont", text);
}

void ScoreSystem::updateLevel(int newScore)
{
	_levelProgressBarFg->srcWidth = 113 * newScore / _levelUpScore;
	_levelProgressBarFg->dstWidth = 113 * newScore / _levelUpScore;

	if (newScore >= _levelUpScore)
	{
		_entityManager->createEntity().addComponent<LevelUpEvent>();

		_level++;
		_scoreInLevel = 0;
		_levelUpScore += round(_levelUpScore * _levelUpScoreIncreaseRate);
		_levelProgressBarFg->srcWidth = 0;
		_levelProgressBarFg->dstWidth = 0;
	}

	std::string text = "Level: " + std::to_string(_level);
	_levelDisplayText->setText("ScoreFont", text);
}
