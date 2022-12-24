#include "pch.h"
#include "TerrainSystem.h"
#include "../Components/Components.h"
#include "../Rendering/VertexArray.h"
#include "../Rendering/Buffer.h"

TerrainSystem::TerrainSystem()
{

}

void TerrainSystem::Init()
{
	auto terrains = Registry::Instance().GetComponents<TerrainComponent>();
	Logger::Log("TerrainSystem : Amount of terrains to init " + std::to_string(terrains.size()));
	for (auto terrain : terrains) {
		std::vector<Vertex> verts;
		std::vector<uint32_t> inds;
	
		for (int i = 0; i < terrain->mHeight; i++) {
			for (int j = 0; j < terrain->mWidth; j++)
			{
				//			200  * (j / mWidth)
				float t1 = (j / terrain->mWidth);
				float t2 =(i / terrain->mHeight);
				verts.push_back(Vertex(glm::vec3(j, (rand() % 100) / 100.f, i), glm::vec3(0, 0, 0), std::pair<float, float>{t1, t2}));
			}
		}
		//Indeksering
		for (int j = 0; j < terrain->mHeight - 1; j++) {
			for (int i = 0; i < (terrain->mWidth  - 1); i++) {
				//Første index
				inds.push_back(i + ((terrain->mWidth * j)));
				////Høyre for første
				inds.push_back(i + ((terrain->mWidth * j) + 1));
				////Under første
				inds.push_back(i + ((terrain->mWidth * j) + terrain->mWidth));

				//Høyre for første
				inds.push_back(i + ((terrain->mWidth * j) + 1));
				//Under første
				inds.push_back(i + ((terrain->mWidth * j) + terrain->mWidth));
				//Til høyre for under første
				inds.push_back(i + ((terrain->mWidth * j) + terrain->mWidth + 1));
			}
		}

		//Vertex array object-VAO
		auto vao = std::make_shared<VertexArray>();
		//Vertex buffer object to hold vertices - VBO
		auto vbo = std::make_shared<VertexBuffer>(verts);

		vao->AddVertexBuffer(vbo);

		// Element array buffer - EAB - ibo
		auto ibo = std::make_shared<IndexBuffer>(inds);
		vao->AddIndexBuffer(ibo);

		terrain->mVAO = vao;
		terrain->mVBO = vbo;
		terrain->mIBO = ibo;


		//Does the terrain compøonent hold the mesh data ?  yeah probably
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
		if (!terrain->mVAO) {
			Logger::Log("TerrainSystem : Terrain has no VAO!", ERROR);
			return;
		}
		terrain->mVAO->Bind();
		//Renderer que (terrain->mVAO)
		glDrawElements(GL_TRIANGLES, terrain->mVAO->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
		//Does the terrain compøonent hold the mesh data ?  yeah probably
		switch (terrain->mType) {

		case  TerrainComponent::TerrainType::PerlinNoise: 

			//LoadPerlinNoiseTerrain(terrain);
			
			break;

		case  TerrainComponent::TerrainType::LAZFile:

			//LoadLAZFileTerrain(terrain);

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
		//Lagre linjen den er på
		std::string line;
		//For å bruke substr så lagrer jeg sist space plass
		int lastSpace = 0;
		//lagrer det i egen string for å gjøre det om til float etterpå
		std::string number;
		while (std::getline(file, line)) {
			lastSpace = 0;
			for (int i = 0; i < line.size(); i++) {
				if (line[i] == ' ') {
					number = line.substr(lastSpace, i - 1);
					points.push_back(std::stod(number));
					lastSpace = i;
				}//Gå fra forrige space til siste, for det siste tallet
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
					//Første index
					inds.push_back(i + ((terrain->mWidth / terrain->mResolution) * j));
					////Høyre for første
					inds.push_back(i + ((terrain->mWidth / terrain->mResolution) * j) + 1);
					////Under første
					inds.push_back(i + ((terrain->mWidth / terrain->mResolution) * j) + terrain->mWidth / terrain->mResolution);
				}
				else {
					//Høyre for første
					inds.push_back(i + ((terrain->mWidth / terrain->mResolution) * j) + 1);
					//Under første
					inds.push_back(i + ((terrain->mWidth / terrain->mResolution) * j) + terrain->mWidth / terrain->mResolution);
					//Til høyre for under første
					inds.push_back(i + ((terrain->mWidth / terrain->mResolution) * j) + terrain->mWidth / terrain->mResolution + 1);
				}
			}
		}
	}
	terrain->mIndicies = inds;
}