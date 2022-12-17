#pragma once

class Input {
public:
	Input() {
		mInstance = this;
	};
	// Check if a specific key is currently being pressed
	static bool IsKeyDown(int key);

	//// Check if a specific key was just pressed (i.e. went from not being pressed to being pressed)
	//bool IsKeyPressed(int key) const;
	//
	//// Check if a specific key was just released (i.e. went from being pressed to not being pressed)
	//bool IsKeyReleased(int key) const;
	//
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

private:
	static Input* mInstance;

};