#pragma once
#include <stdint.h>

enum class RendererAPI {
	OpenGL = 0
};

class Renderer {
	inline static RendererAPI GetRendererAPI() { return mRendererAPI; };

private:
	static RendererAPI mRendererAPI;

	uint32_t mRednererID = 0;
};
