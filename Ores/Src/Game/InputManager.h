#pragma once

class InputManager
{
public:
	InputManager();
	~InputManager();

	inline static InputManager& instance()
	{
		if (s_instance == nullptr)
		{
			s_instance = new InputManager();
		}

		return *s_instance;
	}

	void handleEvents();

private:
	static InputManager* s_instance;
};
