#pragma once

#include <SDL.h>
#include "ECS/ECS.h"
#include "Singleton.h"
#include "Renderer.h"
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
		T* system = new T(_entityManager);
		system->init();
		return *system;
	}

	inline bool isRunning() { return _isRunning; }
	inline Renderer* getRenderer() { return _renderer; }
	inline SDL_Rect getCamera() { return _camera; }
	inline Vector2 getWorldDimensions() { return _worldDimensions; }

	float deltaTime = 1.f;

private:
	bool _isRunning = false;

	int _lastFrameTime = 0;
	int _frameCount = 0;

	SDL_Window* _window = nullptr;
	SDL_Rect _camera;
	Vector2 _worldDimensions;
	Renderer* _renderer = nullptr;
	EntityManager* _entityManager = nullptr;

	SpriteSystem* _spriteSystem = nullptr;
	AnimationSystem* _animationSystem = nullptr;
};