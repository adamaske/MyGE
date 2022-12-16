#include "pch.h"
#include "RenderSystem.h"
#include "ObjMeshSystem.h"

#include "../Textures/Texture.h"
#include "../ObjFileReader.h"
RenderSystem::RenderSystem() {


}

void RenderSystem::Init() {
	///find all render components
	auto renders = Registry::Instance().GetComponents<RenderComponent>();
	std::cout << "RednerSystem : Init renderers = " << renders.size() << std::endl;
	for (auto render : renders) {

		std::cout << "RednerSystem : Init starting init on renderer" << std::endl;
		//Check if we want to render
		if (!render->bRender) {
			std::cout << "RednerSystem : Init should not render = " << renders.size() << std::endl;
			continue;
		}
		//Check for material, the material should have a shader and a texture, 
		auto material = Registry::Instance().GetComponent<MaterialComponent>((uint32_t)render->mGO);
		if (material) {
			if (!material->mShader) {
				std::cout << "RednerSystem : Init on shader" << std::endl;
				continue;
			}
			auto shader = material->mShader;
			shader->Use();

			auto transform = Registry::Instance().GetComponent<TransformComponent>((uint32_t)render->mGO);
			

			if (material->mTexture) {
				//I maybe think we dont have to do anything here???	
			}

		
			
		}
		else {

			std::cout << "RednerSystem : Init no material" << std::endl;
		}

		//Check for mesh
		auto mesh = Registry::Instance().GetComponent<MeshComponent>((uint32_t)render->mGO);
		if (mesh) {
			std::cout << "RenderSystem : Now initing mesh " << mesh->mMeshName << std::endl;;
			//Vertex array object-VAO
			auto vao = std::make_shared<VertexArray>();
			//Bind VAO
			auto meshData = ObjFileReader::GetMeshNoVertex(mesh->mObjFilePath);
			//Vertex buffer object to hold vertices - VBO
			auto vbo = std::make_shared<VertexBuffer>(meshData.first.data(), sizeof(meshData.first));

			vao->AddVertexBuffer(vbo);

			// Element array buffer - EAB - ibo
			auto ibo = std::make_shared<IndexBuffer>(meshData.second.data(), sizeof(meshData.second));
			vao->AddIndexBuffer(ibo);

			//vao->Init();
			render->mVAO = vao;
		}
		else {

			std::cout << "RednerSystem : Init no mesh" << std::endl;
		}
		//Check if we should render


		std::cout << "RednerSystem : Init completed one render init" << std::endl;

	}
}

void RenderSystem::OnUpdate(float deltaTime) {
	///find all render components
	auto renders = Registry::Instance().GetComponents<RenderComponent>();

	std::cout << "RenderSystem : found renderers " << renders.size() << std::endl;;
	for (auto render : renders) {
		//Check if we want to render
		if (!render->bRender) {
			std::cout << "RenderSystem : this render component should not render" << std::endl;;
			continue;
		}

		//Transform component
		auto transform = Registry::Instance().GetComponent<TransformComponent>((uint32_t)render->mGO);

		//Check for material, the material should have a shader and a texture
		auto material = Registry::Instance().GetComponent<MaterialComponent>((uint32_t)render->mGO);
		if (material) {

			auto shader = material->mShader;
			if (shader) {
				shader->Use();
				shader->SetUniformMatrix4(transform->mMatrix, "mMatrix");
			}
			else {
				std::cout << "RednerSystem : No Shader" << std::endl;
			}

			auto texture = material->mTexture;
			if (texture) {
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, texture->id());
				if(shader) {
					shader->SetUniform1i(0, "textureSampler");
				}
			}
			else {
				std::cout << "RenderSystem : No Texture" << std::endl;
			}
		}
		else {
			std::cout << "RenderSystem : No material";
		}

		auto mesh = Registry::Instance().GetComponent<MeshComponent>((uint32_t)render->mGO);
		if (!mesh) {
			std::cout << "RenderSystem : No MeshComponent" << std::endl;
		}

		std::cout << "RenderSystem : Now updating mesh " << mesh->mMeshName << std::endl;;
		//std::cout << "RenderSystem : Size of mesh vertices = " << mesh->mVertices.size() << std::endl;
		//for (int i = 0; i < mesh->mVertices.size(); i += 8) {
		//	std::cout << "v1(" << mesh->mVertices[i] << "), " << "v2(" << mesh->mVertices[i + 1] << ")," << "v3(" << mesh->mVertices[i + 2] << ")" << std::endl;
		//
		//	std::cout << "n1(" << mesh->mVertices[i+3] << "), " << "n2(" << mesh->mVertices[i + 4] << ")," << "n3(" << mesh->mVertices[i + 5] << ")" << std::endl;
		//	
		//	std::cout << "t1(" << mesh->mVertices[6] << "), " << "t2(" << mesh->mVertices[i + 7] << ")"<< std::endl;
		//}


		auto vao = render->mVAO;
		if (!vao) {
			std::cout << "RenderSystem : RenderComponent dosent have a VAO" << std::endl;
			continue;
		}
		vao->Bind();
		vao->Print();
		//Draws from the bound vao
		glDrawElements(GL_TRIANGLES, vao->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

		vao->Unbind();

		std::cout << "RenderSystem : Completed Rendering!" << std::endl;
	}
}