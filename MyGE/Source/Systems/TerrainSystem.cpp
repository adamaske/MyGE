#include "TerrainSystem.h"
#include <iostream>
#include <string>
#include <algorithm>
TerrainSystem::TerrainSystem()
{
}
void TerrainSystem::Init()
{
	auto terrains = Registry::Instance().GetComponents<TerrainComponent>();

	for (auto terrain : terrains) {


		//Does the terrain comp�onent hold the mesh data ?  yeah probably
		switch (terrain->mType) {

		case  TerrainComponent::TerrainType::PerlinNoise:

			
				

			break;

		case  TerrainComponent::TerrainType::LAZFile:

			break;


		}
	}
}

void TerrainSystem::OnUpdate(float deltaSeconds)
{

	auto terrains = Registry::Instance().GetComponents<TerrainComponent>();

	for (auto terrain : terrains) {


		//Does the terrain comp�onent hold the mesh data ?  yeah probably
		switch (terrain->mType) {

		case  TerrainComponent::TerrainType::PerlinNoise: 

			LoadPerlinNoiseTerrain(terrain);
			break;

		case  TerrainComponent::TerrainType::LAZFile:

			LoadLAZFileTerrain(terrain);

			break;


		}
	}
}


void TerrainSystem::LoadPerlinNoiseTerrain(std::shared_ptr<TerrainComponent> terrain) {



	std::vector<float> verts;
	terrain->mVertices = verts;

	std::vector<float> inds;
	terrain->mIndicies = inds;
}

void TerrainSystem::TerrainSystem::LoadLAZFileTerrain(std::shared_ptr<TerrainComponent> terrain) {
	//File which contains points
	std::ifstream file(terrain->mFilePath);
	//Lagre alle puntkene som blir lest
	std::vector<float> points;
	if (file.is_open()) {
		//Lagre linjen den er p�
		std::string line;
		//For � bruke substr s� lagrer jeg sist space plass
		int lastSpace = 0;
		//lagrer det i egen string for � gj�re det om til float etterp�
		std::string number;
		while (std::getline(file, line)) {
			lastSpace = 0;
			for (int i = 0; i < line.size(); i++) {
				if (line[i] == ' ') {
					number = line.substr(lastSpace, i - 1);
					points.push_back(std::stod(number));
					lastSpace = i;
				}//G� fra forrige space til siste, for det siste tallet
				else if (i == line.size() - 1) {
					number = line.substr(lastSpace, i);
					points.push_back((std::stof(number)));
				}
			}
		}
	}
	file.close();

	std::vector<float> heights;

	std::vector<float> verts;
	terrain->mVertices = verts;
	for (int i = 0; i < points.size(); i += 3) {
		//Position
		verts.push_back(points[i]);
		verts.push_back(points[i + 1]);
		verts.push_back(points[i + 2]);
		//Color / normals
		verts.push_back(tan(i));
		verts.push_back(sin(i));
		verts.push_back(cos(i));
		//uvs
		verts.push_back(0);
		verts.push_back(0);

	}
	

	std::vector<float> inds;
	

	//Indeksering
	for (int j = 0; j < (terrain->mHeight / terrain->mResolution) - 1; j++) {
		for (int i = 0; i < (terrain->mWidth / terrain->mResolution) - 1; i++) {
			for (int k = 0; k < 2; k++) {
				if (k == 0) {
					//F�rste index
					inds.push_back(i + ((terrain->mWidth / terrain->mResolution) * j));
					////H�yre for f�rste
					inds.push_back(i + ((terrain->mWidth / terrain->mResolution) * j) + 1);
					////Under f�rste
					inds.push_back(i + ((terrain->mWidth / terrain->mResolution) * j) + terrain->mWidth / terrain->mResolution);
				}
				else {
					//H�yre for f�rste
					inds.push_back(i + ((terrain->mWidth / terrain->mResolution) * j) + 1);
					//Under f�rste
					inds.push_back(i + ((terrain->mWidth / terrain->mResolution) * j) + terrain->mWidth / terrain->mResolution);
					//Til h�yre for under f�rste
					inds.push_back(i + ((terrain->mWidth / terrain->mResolution) * j) + terrain->mWidth / terrain->mResolution + 1);
				}
			}
		}
	}
	terrain->mIndicies = inds;
}