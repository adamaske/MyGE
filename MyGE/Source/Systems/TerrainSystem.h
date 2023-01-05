#pragma once
#include "System.h"

class TerrainSystem : public System {
public:
	TerrainSystem();
	virtual void Init() override;
	virtual void OnUpdate(float deltaSeconds) override;

	void LoadPerlinNoiseTerrain(std::shared_ptr<TerrainComponent> terrain);
	void LoadLAZFileTerrain(std::shared_ptr<TerrainComponent> terrain);

	float PerlinNoise(float x, float y);
private:


};