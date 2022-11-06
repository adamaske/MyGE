#pragma once

class MyGE
{
public:

	MyGE() {

	};

	int run();

	void ProcessInput();

private:
	class RenderWindow* mWindow{nullptr};
};

