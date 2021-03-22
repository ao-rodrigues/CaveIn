#include "ScoreSystem.h"

#include <cmath>

#include "../../Engine/Engine.h"
#include "../Events/OreDestroyedEvent.h"
#include "../Events/LevelUpEvent.h"
#include "../Events/StartGameEvent.h"

void ScoreSystem::init()
{
	AssetManager::instance().loadFont("ScoreFont", "Assets/Fonts/Alagard.ttf", 18);

	AssetManager::instance().loadTexture("ProgressBarBg", "Assets/Textures/progress_bar_bg_2.png");
	AssetManager::instance().loadTexture("ProgressBarFg", "Assets/Textures/progress_bar_fg_2.png");

	SDL_Color textColor = { 255, 255, 255, 255 };
	std::string scoreDisplayText = "Score: " + std::to_string(_score);

	_scoreDisplayText = &Engine::instance().createEntity().addComponent<Text>("ScoreFont", 0, scoreDisplayText, textColor, 500);
	_scoreDisplayText->getTransform().position = Vector2(10.f, 10.f);
	_scoreDisplayText->entity->setEnabled(false);

	std::string levelDisplayText = "Level: " + std::to_string(_level);
	_levelDisplayText = &Engine::instance().createEntity().addComponent<Text>("ScoreFont", 0, levelDisplayText, textColor, 500);
	_levelDisplayText->getTransform().position = Vector2(150.f, 10.f);
	_levelDisplayText->entity->setEnabled(false);

	_levelProgressBarBg = &Engine::instance().createEntity().addComponent<Sprite>(RenderLayer::UI, 0, "ProgressBarBg", 0, 0, 569, 81);
	_levelProgressBarBg->getTransform().scale = Vector2(0.3f, 0.3f);
	_levelProgressBarBg->getTransform().position.x = 230.f;
	_levelProgressBarBg->getTransform().position.y = 5.f;
	_levelProgressBarBg->entity->setEnabled(false);

	_levelProgressBarFg = &Engine::instance().createEntity().addComponent<Sprite>(RenderLayer::UI, 1, "ProgressBarFg", 0, 0, 529, 40);
	_levelProgressBarFg->getTransform().scale = Vector2(0.3f, 0.3f);
	_levelProgressBarFg->getTransform().position.x = 230.f + 0.3f * (569.f - 531.f) / 2.f;
	_levelProgressBarFg->getTransform().position.y = 5.f + 0.3f * (81.f - 40.f) / 2.f;
	_levelProgressBarFg->setSrcWidth(0);
	_levelProgressBarFg->setDstWidth(0);
	_levelProgressBarFg->entity->setEnabled(false);
}

void ScoreSystem::update()
{
	auto startGameEvents = _entityManager->getEntitiesWithComponentAll<StartGameEvent>();
	if (startGameEvents.size() > 0)
	{
		_scoreDisplayText->entity->setEnabled(true);
		_levelDisplayText->entity->setEnabled(true);
		_levelProgressBarBg->entity->setEnabled(true);
		_levelProgressBarFg->entity->setEnabled(true);

		_score = 0;
		_scoreInLevel = 0;
		_level = 1;
		_levelUpScore = STARTER_LEVEL_UP_SCORE;
		updateScoreDisplay(_score);
		updateLevel(_scoreInLevel);
	}

	auto oreDestroyedEvents = _entityManager->getEntitiesWithComponentAll<OreDestroyedEvent>();
	for (auto& event : oreDestroyedEvents)
	{
		OreDestroyedEvent& oreDestroyedEvent = event->getComponent<OreDestroyedEvent>();
		OreData oreData = oreDestroyedEvent.oreData;
		_score += oreData.destructionPoints;
		_scoreInLevel += oreData.destructionPoints;
		updateScoreDisplay(_score);
		updateLevel(_scoreInLevel);
	}
}

void ScoreSystem::updateScoreDisplay(int newScore)
{
	std::string text = "Score: " + std::to_string(newScore);
	_scoreDisplayText->setText("ScoreFont", text);
}

void ScoreSystem::updateLevel(int newScore)
{
	_levelProgressBarFg->setSrcWidth(529 * newScore / _levelUpScore);
	_levelProgressBarFg->setDstWidth(529 * newScore / _levelUpScore);

	if (newScore >= _levelUpScore)
	{
		_entityManager->createEntity().addComponent<LevelUpEvent>().entity->setDestroyNextFrame(true);

		_level++;
		_scoreInLevel = 0;
		_levelUpScore += round(_levelUpScore * _levelUpScoreIncreaseRate);
		_levelProgressBarFg->setSrcWidth(0);
		_levelProgressBarFg->setDstWidth(0);
	}

	std::string text = "Level: " + std::to_string(_level);
	_levelDisplayText->setText("ScoreFont", text);
}
