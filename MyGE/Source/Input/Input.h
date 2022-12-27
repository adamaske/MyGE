#pragma once

class Input {
public:
	Input();

	static void Init();
	// Check if a specific key is currently being pressed
	static bool IsKeyDown(int key);

	//// Check if a specific key was just released (i.e. went from being pressed to not being pressed)
	static bool IsKeyReleased(int key);
	
	static bool IsMouseButtonDown(int button);

	static bool IsMouseButtonPressed(int button);
	//// Check if a specific mouse button is currently being pressed
	//bool IsMouseButtonDown(int button) const;
	//
	//// Check if a specific mouse button was just pressed (i.e. went from not being pressed to being pressed)
	//bool IsMouseButtonPressed(int button) const;
	//
	//// Check if a specific mouse button was just released (i.e. went from being pressed to not being pressed)
	//bool IsMouseButtonReleased(int button) const;
	//
	//// Get the current position of the mouse cursor
	//glm::vec2 GetMousePosition() const;
	//
	//// Update the state of the input class
	//void Update();
	static float MouseX();
	static float MouseY();
	static float DeltaMouseX();
	static float DeltaMouseY();
	//Change this 350 to the amount of keys, GLFW_LAST_KEY + 1, 
	//then it goes from 0 to 349 still but updates with opengl updates
	//Each bool represents if the key is down or not
	std::array<bool, 350> mKeys;



private:
	// Callback functions for GLFW input events.
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);

	//Mouse position
	float mMouseX = 0;
	float mMouseY = 0;
	float mDeltaMouseX = 0;
	float mDeltaMouseY = 0;
	bool bMouseClick = false;
	static Input& GetInstance() {
		static Input instance;
		return instance;
	};

};