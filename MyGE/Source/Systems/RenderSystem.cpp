#include "pch.h"
#include "RenderSystem.h"
#include "ObjMeshSystem.h"

#include "../Textures/Texture.h"
#include "../Textures/TextureManager.h"

#include "../ObjFileReader.h"

RenderSystem::RenderSystem() {


}

void RenderSystem::Init() {
	Logger::Log("RednerSystem : Init started", INFO);
	///find all render components
	auto meshes = Registry::Instance().GetComponents<MeshComponent>();
	for (auto mesh : meshes) {
		Logger::Log("RenderSystem : Initing mesh " + std::to_string(mesh->mGO));

		//Check for material, the material should have a shader and a texture, 
		auto material = Registry::Instance().GetComponent<MaterialComponent>(mesh->mGO);
		if (!material) {
			//This should never happend, all objects gets a material
			Logger::Log("RednerSystem : Init no material, dropping init", INFO);
			mesh->bVisible = false;
			continue;
		}
		//This should prob also be turned to a id instead of pointer to shader
		if (!material->mShader) {
			Logger::Log("RednerSystem : Init no shader, dropping init", INFO);
			mesh->bVisible = false;
			continue;
		}
		auto shader = material->mShader;
		shader->Use();

		auto transform = Registry::Instance().GetComponent<TransformComponent>(mesh->mGO);


		if (material->mTexture) {
			//I maybe think we dont have to do anything here???	
			//the texture manager should have dealt with this
		}

		//Vertex array object-VAO
		auto vao = std::make_shared<VertexArray>();
		//Bind VAO
		auto meshData = ObjFileReader::GetMesh(mesh->mObjFilePath);
		//Vertex buffer object to hold vertices - VBO
		auto vbo = std::make_shared<VertexBuffer>(meshData.first);

		vao->AddVertexBuffer(vbo);

		// Element array buffer - EAB - ibo
		auto ibo = std::make_shared<IndexBuffer>(meshData.second);
		vao->AddIndexBuffer(ibo);

		//vao->Init();
		mesh->mVAO = vao;
		
	}

	Logger::Log("RednerSystem : Init finished", INFO);
}

void RenderSystem::OnUpdate(float deltaTime) {
	///find all render components
	//Todo : remove render system, sending to the renderer should not happend in here
	//the terrainsystem should send the vao to the renderer, not this
	auto meshes = Registry::Instance().GetComponents<MeshComponent>();
	for (auto mesh : meshes) {
		//Check if we want to render
		if (!mesh->bVisible) {
			continue;
		}

		//Transform component
		auto transform = Registry::Instance().GetComponent<TransformComponent>(mesh->mGO);

		//Check for material, the material should have a shader and a texture
		auto material = Registry::Instance().GetComponent<MaterialComponent>(mesh->mGO);
		if (material) {

			auto shader = material->mShader;
			if (shader) {
				shader->Use();
				shader->SetUniformMatrix4(transform->mMatrix, "mMatrix");
			}
			else {
				Logger::Log("RednerSystem : No Shader", INFO);
			}

			auto texture = material->mTexture;
			if (texture != -1) {
				//This activates the 0'th texture unit
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, texture);
				if(shader) {
					//The diffuse sampler is using the 0'th texture unit
					shader->SetUniform1i(0, "diffuseSampler");
				}

			}
			else {
				Logger::Log("RenderSystem : No Texture in the material", INFO);
			}
		}
		else {
			Logger::Log("RenderSystem : No material, cannot render!", ERROR, true);
		}

		//This should be replaced by calling Renderer functions from Renderer.cpp
		auto vao = mesh->mVAO;
		if (!vao) {
			Logger::Log("RenderSystem : RenderComponent dosent have a VAO", INFO);
			continue;
		}
		vao->Bind();
		//Draws from the bound vao
		glDrawElements(GL_TRIANGLES, vao->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		vao->Unbind();
	}
}