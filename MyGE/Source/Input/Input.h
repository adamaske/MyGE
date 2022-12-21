#pragma once

class Input {
public:
	Input();
	// Check if a specific key is currently being pressed
	static bool IsKeyDown(int key);
	bool IsKeyDownImplentation(int key);
	
	//// Check if a specific key was just released (i.e. went from being pressed to not being pressed)
	static bool IsKeyReleased(int key);
	bool IsKeyReleasedImplentation(int key);
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

	std::array<bool, GLFW_KEY_LAST + 1> mKeys;
private:
	// Callback functions for GLFW input events.
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
	
	//To accsess the input as fast as possible i create an array for every key
	//with length of the last key index + 1, 

	//Mouse position
	float mouseX = 0;
	float mouseY = 0;
	std::pair<float, float> mMouse;
	static Input& GetInstance() {
		static Input instance;
		return instance;
	};

};