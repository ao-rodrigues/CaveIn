#pragma once

#include <vector>
#include <memory>

#include "ECS/ECS.h"
#include "Singleton.h"
#include "ECS/Systems/RenderSystem.h"
#include "Math/Vector2.h"
#include "ECS/Systems/SpriteSystem.h"
#include "ECS/Systems/AnimationSystem.h"

class Engine : public Singleton<Engine>
{
public:

	Engine();
	~Engine();

	void init(const char* title, int width, int height, bool fullscreen, bool vsync, int worldWidth, int worldHeight);
	void quit();
	void clear();

	void handleEvents();
	void update();
	void render();

	/// <summary>
	/// Creates an entity with a Transform component pre-applied
	/// </summary>
	/// <returns>A new entity</returns>
	Entity& createEntity();

	/// <summary>
	/// Creates an empty entity with no components pre-applied
	/// </summary>
	/// <returns>A new empty entity</returns>
	Entity& createEmptyEntity();

	template<typename T>
	T& createSystem()
	{
		static_assert(std::is_base_of<System, T>::value, "Type must be derived from System!");
		//T* system = new T(_entityManager);
		//system->init();
		std::unique_ptr<T> systemUniqPtr = std::make_unique<T>(_entityManager);
		systemUniqPtr->init();

		T* system = systemUniqPtr.get();

		_systems.emplace_back(std::move(systemUniqPtr));

		return *system;
	}

	inline bool isRunning() { return _isRunning; }
	inline SDL_Renderer* getRenderer() { return _renderSystem->SDLRenderer(); }
	inline SDL_Rect getCamera() { return _camera; }
	inline Vector2 getWorldDimensions() { return _worldDimensions; }

	float deltaTime = 1.f;

private:
	bool _isRunning = false;

	int _lastFrameTime = 0;
	int _frameCount = 0;

	SDL_Window* _window = nullptr;
	SDL_Rect _camera = { 0, 0, 0, 0 };
	Vector2 _worldDimensions;
	RenderSystem* _renderSystem = nullptr;
	EntityManager* _entityManager = nullptr;

	SpriteSystem* _spriteSystem = nullptr;
	AnimationSystem* _animationSystem = nullptr;

	std::vector<std::unique_ptr<System>> _systems;
};