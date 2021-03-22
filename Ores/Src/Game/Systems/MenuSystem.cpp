#include "MenuSystem.h"

#include "../../Engine/Engine.h"
#include "../../Engine/AssetManager.h"
#include "../../Engine/InputManager.h"

#include "../../Engine/ECS/Components/Button.h"

#include "../Events/StartGameEvent.h"
#include "../Events/PauseGameEvent.h"
#include "../Events/ResumeGameEvent.h"
#include "../Events/GameOverEvent.h"
#include "../Events/ShowHighScoreEvent.h"

void MenuSystem::init()
{
	// Load all GUI assets
	AssetManager::instance().loadTexture("UIPanel", "Assets/Textures/ui_panel.png");
	AssetManager::instance().loadTexture("UIBanner", "Assets/Textures/ui_header.png");
	AssetManager::instance().loadTexture("ButtonDefault", "Assets/Textures/button.png");
	AssetManager::instance().loadTexture("ButtonHover", "Assets/Textures/button_hover.png");
	AssetManager::instance().loadTexture("ButtonDown", "Assets/Textures/button_down.png");

	AssetManager::instance().loadFont("TitleFont", "Assets/Fonts/Alagard.ttf", 86);
	AssetManager::instance().loadFont("ButtonFont", "Assets/Fonts/Alagard.ttf", 24);
	AssetManager::instance().loadFont("UIBannerFont", "Assets/Fonts/Alagard.ttf", 32);
	AssetManager::instance().loadFont("UITextFont", "Assets/Fonts/Alagard.ttf", 20);

	Engine& engine = Engine::instance();

	// Create entities, set references

	// Title
	SDL_Color titleTextColor = { 255, 255, 255, 255 };
	_title = &engine.createEntity().addComponent<Text>("TitleFont", 1, "CAVE-IN", titleTextColor, 500);
	float titleX = (engine.getWorldDimensions().x / 2.f) - (_title->dstRect()->w / 2.f);
	float titleY = (engine.getWorldDimensions().y / 2.f) - (_title->dstRect()->h / 2.f);
	_title->getTransform().position = Vector2(titleX, titleY);

	// Start Game button
	_startGameButton = &engine.createEntity();
	Sprite& startGameBtnSprite = _startGameButton->addComponent<Sprite>(RenderLayer::UI, 0, "ButtonDefault", 0, 0, 300, 87);
	_startGameButton->addComponent<Button>("ButtonDefault", "ButtonHover", "ButtonDown");
	SDL_Color buttonTextColor = { 255, 255, 255, 255 };
	Text& startGameLabel = _startGameButton->addComponent<Text>("ButtonFont", 1, "Start Game", buttonTextColor, 200);

	float startBtnX = (engine.getWorldDimensions().x / 2.f) - (_startGameButton->getComponent<Sprite>().dstRect()->w / 2.f);
	float startBtnY = _title->getTransform().position.y + _title->dstRect()->h + 20.f;
	_startGameButton->getComponent<Transform>().position = Vector2(startBtnX, startBtnY);

	float labelX = startGameBtnSprite.dstRect()->w / 2.f - startGameLabel.dstRect()->w / 2.f;
	float labelY = startGameBtnSprite.dstRect()->h / 2.f - startGameLabel.dstRect()->h / 2.f;
	startGameLabel.setRelativePosition(Vector2(labelX, labelY));

	
	// Tutorial panel and banner
	_tutorialPanel = &engine.createEntity();
	Sprite& tutorialPanelSprite = _tutorialPanel->addComponent<Sprite>(RenderLayer::UI, 0, "UIPanel", 0, 0, 818, 504, 400, 160, 0.f, 0.f);

	SDL_Color textColor = { 0, 0, 0, 255 };
	std::string tutorialDisplayText = "The dungeon is caving in\nand your heroes are in danger!\nDestroy the ores before they're crushed!";
	Text& tutorialText = _tutorialPanel->addComponent<Text>("UITextFont", 1, tutorialDisplayText, textColor, 300);

	float panelSpriteX = (engine.getWorldDimensions().x / 2.f) - (tutorialPanelSprite.dstRect()->w / 2.f);
	float panelSpriteY = (engine.getWorldDimensions().y / 2.f) - (tutorialPanelSprite.dstRect()->h / 2.f);
	Transform& tutorialPanelTransform = _tutorialPanel->getComponent<Transform>();
	tutorialPanelTransform.position = Vector2(panelSpriteX, panelSpriteY);

	float tutorialTextRelX = (tutorialPanelSprite.dstRect()->w / 2.f) - (tutorialText.dstRect()->w / 2.f);
	float tutorialTextRelY = (tutorialPanelSprite.dstRect()->h / 2.f) - (tutorialText.dstRect()->h / 2.f);
	tutorialText.setRelativePosition(Vector2(tutorialTextRelX, tutorialTextRelY));

	_tutorialBanner = &engine.createEntity();
	Sprite& tutorialBannerSprite = _tutorialBanner->addComponent<Sprite>(RenderLayer::UI, 1, "UIBanner", 0, 0, 830, 188, 400, 100, 0.f, 0.f);
	Text& tutorialBannerText = _tutorialBanner->addComponent<Text>("UIBannerFont", 2, "Tutorial", textColor, 300);

	float bannerSpriteX = panelSpriteX;
	float bannerSpriteY = panelSpriteY - 110.f;
	Transform& tutorialBannerTransform = _tutorialBanner->getComponent<Transform>();
	tutorialBannerTransform.position = Vector2(bannerSpriteX, bannerSpriteY);

	float bannerTextRelX = (tutorialBannerSprite.dstRect()->w / 2.f) - (tutorialBannerText.dstRect()->w / 2.f);
	float bannerTextRelY = (tutorialBannerSprite.dstRect()->h / 2.f) - (tutorialBannerText.dstRect()->h / 2.f);
	tutorialBannerText.setRelativePosition(Vector2(bannerTextRelX, bannerTextRelY));

	// Paused banner
	_pausedBanner = &engine.createEntity();
	Sprite& pausedBannerSprite = _pausedBanner->addComponent<Sprite>(RenderLayer::UI, 1, "UIBanner", 0, 0, 830, 188, 400, 100, 0.f, 0.f);
	Text& pausedBannerText = _pausedBanner->addComponent<Text>("UIBannerFont", 2, "Paused", textColor, 300);

	float pausedBannerSpriteX = (engine.getWorldDimensions().x / 2.f) - (pausedBannerSprite.dstRect()->w / 2.f);
	float pausedBannerSpriteY = (engine.getWorldDimensions().y / 2.f) - (pausedBannerSprite.dstRect()->h / 2.f);
	Transform& pausedBannerTransform = _pausedBanner->getComponent<Transform>();
	pausedBannerTransform.position = Vector2(pausedBannerSpriteX, pausedBannerSpriteY);

	float pausedBannerTextRelX = (pausedBannerSprite.dstRect()->w / 2.f) - (pausedBannerText.dstRect()->w / 2.f);
	float pausedBannerTextRelY = (pausedBannerSprite.dstRect()->h / 2.f) - (pausedBannerText.dstRect()->h / 2.f);
	pausedBannerText.setRelativePosition(Vector2(pausedBannerTextRelX, pausedBannerTextRelY));

	// Resume button
	_resumeButton = &engine.createEntity();
	Sprite& resumeBtnSprite = _resumeButton->addComponent<Sprite>(RenderLayer::UI, 0, "ButtonDefault", 0, 0, 300, 87);
	_resumeButton->addComponent<Button>("ButtonDefault", "ButtonHover", "ButtonDown");
	Text& resumeLabel = _resumeButton->addComponent<Text>("ButtonFont", 1, "Resume", buttonTextColor, 200);

	float resumeBtnX = (engine.getWorldDimensions().x / 2.f) - (_resumeButton->getComponent<Sprite>().dstRect()->w / 2.f);
	float resumeBtnY = tutorialPanelTransform.position.y + tutorialPanelSprite.dstRect()->h + 20.f;
	_resumeButton->getComponent<Transform>().position = Vector2(resumeBtnX, resumeBtnY);

	float resumeLabelX = resumeBtnSprite.dstRect()->w / 2.f - resumeLabel.dstRect()->w / 2.f;
	float resumeLabelY = resumeBtnSprite.dstRect()->h / 2.f - resumeLabel.dstRect()->h / 2.f;
	resumeLabel.setRelativePosition(Vector2(resumeLabelX, resumeLabelY));

	// Game Over panel and banner
	_gameOverPanel = &engine.createEntity();
	Sprite& gameOverPanelSprite = _gameOverPanel->addComponent<Sprite>(RenderLayer::UI, 0, "UIPanel", 0, 0, 818, 504, 400, 160, 0.f, 0.f);

	float gameOverPanelSpriteX = (engine.getWorldDimensions().x / 2.f) - (gameOverPanelSprite.dstRect()->w / 2.f);
	float gameOverPanelSpriteY = (engine.getWorldDimensions().y / 2.f) - (gameOverPanelSprite.dstRect()->h / 2.f);
	Transform& gameOverPanelTransform = _gameOverPanel->getComponent<Transform>();
	gameOverPanelTransform.position = Vector2(gameOverPanelSpriteX, gameOverPanelSpriteY);

	SDL_Color scoreTextColor = { 0, 0, 0, 255 };
	_finalScoreDisplay = &engine.createEntity().addComponent<Text>("UITextFont", 1, "Final Score: 0", scoreTextColor, 500);
	float finalScoreX = gameOverPanelTransform.position.x + (gameOverPanelSprite.dstRect()->w / 2.f) - (_finalScoreDisplay->dstRect()->w / 2.f);
	float finalScoreY = gameOverPanelSpriteY + 50.f;
	_finalScoreDisplay->getTransform().position = Vector2(finalScoreX, finalScoreY);

	_highScoreDisplay = &engine.createEntity().addComponent<Text>("UITextFont", 1, "High Score: 0", scoreTextColor, 500);
	float highScoreX = finalScoreX;
	float highScoreY = finalScoreY + 30.f;
	_highScoreDisplay->getTransform().position = Vector2(highScoreX, highScoreY);

	_gameOverBanner = &engine.createEntity();
	Sprite& gameOverBannerSprite = _gameOverBanner->addComponent<Sprite>(RenderLayer::UI, 1, "UIBanner", 0, 0, 830, 188, 400, 100, 0.f, 0.f);
	Text& gameOverBannerText = _gameOverBanner->addComponent<Text>("UIBannerFont", 2, "Game Over", textColor, 300);

	float gameOverBannerSpriteX = gameOverPanelSpriteX;
	float gameOverBannerSpriteY = gameOverPanelSpriteY - 110.f;
	Transform& gameOverBannerTransform = _gameOverBanner->getComponent<Transform>();
	gameOverBannerTransform.position = Vector2(gameOverBannerSpriteX, gameOverBannerSpriteY);

	float gameOverBannerTextRelX = (gameOverBannerSprite.dstRect()->w / 2.f) - (gameOverBannerText.dstRect()->w / 2.f);
	float gameOverBannerTextRelY = (gameOverBannerSprite.dstRect()->h / 2.f) - (gameOverBannerText.dstRect()->h / 2.f);
	gameOverBannerText.setRelativePosition(Vector2(gameOverBannerTextRelX, gameOverBannerTextRelY));


	// Retry button
	_retryButton = &engine.createEntity();
	Sprite& retryBtnSprite = _retryButton->addComponent<Sprite>(RenderLayer::UI, 0, "ButtonDefault", 0, 0, 300, 87);
	_retryButton->addComponent<Button>("ButtonDefault", "ButtonHover", "ButtonDown");
	Text& retryLabel = _retryButton->addComponent<Text>("ButtonFont", 1, "Try Again", buttonTextColor, 200);

	float retryBtnX = (engine.getWorldDimensions().x / 2.f) - (_retryButton->getComponent<Sprite>().dstRect()->w / 2.f);
	float retryBtnY = tutorialPanelTransform.position.y + tutorialPanelSprite.dstRect()->h + 20.f;
	_retryButton->getComponent<Transform>().position = Vector2(retryBtnX, retryBtnY);

	float retryLabelX = retryBtnSprite.dstRect()->w / 2.f - retryLabel.dstRect()->w / 2.f;
	float retryLabelY = retryBtnSprite.dstRect()->h / 2.f - retryLabel.dstRect()->h / 2.f;
	retryLabel.setRelativePosition(Vector2(retryLabelX, retryLabelY));

	// Put game in initial state
	setState(GameState::MainMenu);
}

void MenuSystem::update()
{
	auto showHighScoreEvents = _entityManager->getEntitiesWithComponentAll<ShowHighScoreEvent>(true);
	if (showHighScoreEvents.size() > 0)
	{
		ShowHighScoreEvent& event = showHighScoreEvents[0]->getComponent<ShowHighScoreEvent>();
		_finalScoreDisplay->setText("UITextFont", "Final Score: " + std::to_string(event.finalScore));
		_highScoreDisplay->setText("UITextFont", "High Score: " + std::to_string(event.highScore));
	}

	auto gameOverEvents = _entityManager->getEntitiesWithComponentAll<GameOverEvent>(true);
	if (gameOverEvents.size() > 0)
	{
		setState(GameState::GameOver);
	}

	// Check GUI events

	switch (_currentState)
	{
	case GameState::MainMenu:
		updateMainMenu();
		break;

	case GameState::Tutorial:
		updateTutorialMenu();
		break;

	case GameState::Playing:
		handlePlayingEvents();
		break;

	case GameState::Paused:
		updatePausedMenu();
		break;

	case GameState::GameOver:
		updateGameOverMenu();
		break;

	default:
		break;
	}

	// Change game state accordingly
}

void MenuSystem::updateMainMenu()
{
	Button& startGameBtn = _startGameButton->getComponent<Button>();
	if (startGameBtn.buttonReleased() && startGameBtn.wasPressed())
	{
		setState(GameState::Tutorial);
		_entityManager->createEntity().addComponent<StartGameEvent>();
		_entityManager->createEntity().addComponent<PauseGameEvent>();
	}
}

void MenuSystem::updateTutorialMenu()
{
	Button& resumeBtn = _resumeButton->getComponent<Button>();
	if (resumeBtn.buttonReleased() && resumeBtn.wasPressed())
	{
		setState(GameState::Playing);
		_entityManager->createEntity().addComponent<ResumeGameEvent>();
	}
}

void MenuSystem::handlePlayingEvents()
{
	if (_currentState == GameState::Playing && InputManager::keyPressed(SDLK_ESCAPE))
	{
		setState(GameState::Paused);
		_entityManager->createEntity().addComponent<PauseGameEvent>();
	}
}

void MenuSystem::updatePausedMenu()
{
	Button& resumeBtn = _resumeButton->getComponent<Button>();
	if (InputManager::keyPressed(SDLK_ESCAPE) || (resumeBtn.buttonReleased() && resumeBtn.wasPressed()))
	{
		setState(GameState::Playing);
		_entityManager->createEntity().addComponent<ResumeGameEvent>();
	}
}

void MenuSystem::updateGameOverMenu()
{
	Button& retryBtn = _retryButton->getComponent<Button>();
	if (retryBtn.buttonReleased() && retryBtn.wasPressed())
	{
		setState(GameState::Playing);
		_entityManager->createEntity().addComponent<StartGameEvent>();
	}
}

void MenuSystem::setState(GameState newState)
{
	_currentState = newState;

	switch (newState)
	{
	case GameState::MainMenu:
		_title->entity->setEnabled(true);
		_startGameButton->setEnabled(true);

		_tutorialPanel->setEnabled(false);
		_tutorialBanner->setEnabled(false);
		_resumeButton->setEnabled(false);

		_pausedBanner->setEnabled(false);

		_gameOverBanner->setEnabled(false);
		_gameOverPanel->setEnabled(false);
		_finalScoreDisplay->entity->setEnabled(false);
		_highScoreDisplay->entity->setEnabled(false);
		_retryButton->setEnabled(false);

		break;
	case GameState::Tutorial:
		_title->entity->setEnabled(false);
		_startGameButton->setEnabled(false);

		_tutorialPanel->setEnabled(true);
		_tutorialBanner->setEnabled(true);
		_resumeButton->setEnabled(true);

		_pausedBanner->setEnabled(false);

		_gameOverBanner->setEnabled(false);
		_gameOverPanel->setEnabled(false);
		_finalScoreDisplay->entity->setEnabled(false);
		_highScoreDisplay->entity->setEnabled(false);
		_retryButton->setEnabled(false);
		break;
	case GameState::Playing:
		_title->entity->setEnabled(false);
		_startGameButton->setEnabled(false);

		_tutorialPanel->setEnabled(false);
		_tutorialBanner->setEnabled(false);
		_resumeButton->setEnabled(false);

		_pausedBanner->setEnabled(false);

		_gameOverBanner->setEnabled(false);
		_gameOverPanel->setEnabled(false);
		_finalScoreDisplay->entity->setEnabled(false);
		_highScoreDisplay->entity->setEnabled(false);
		_retryButton->setEnabled(false);
		break;
	case GameState::Paused:
		_title->entity->setEnabled(false);
		_startGameButton->setEnabled(false);

		_tutorialPanel->setEnabled(false);
		_tutorialBanner->setEnabled(false);
		_resumeButton->setEnabled(true);

		_pausedBanner->setEnabled(true);

		_gameOverBanner->setEnabled(false);
		_gameOverPanel->setEnabled(false);
		_finalScoreDisplay->entity->setEnabled(false);
		_highScoreDisplay->entity->setEnabled(false);
		_retryButton->setEnabled(false);
		break;
	case GameState::GameOver:
		_title->entity->setEnabled(false);
		_startGameButton->setEnabled(false);

		_tutorialPanel->setEnabled(false);
		_tutorialBanner->setEnabled(false);
		_resumeButton->setEnabled(false);

		_pausedBanner->setEnabled(false);

		_gameOverBanner->setEnabled(true);
		_gameOverPanel->setEnabled(true);
		_finalScoreDisplay->entity->setEnabled(true);
		_highScoreDisplay->entity->setEnabled(true);
		_retryButton->setEnabled(true);
		break;
	default:
		break;
	}
}
