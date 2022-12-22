#include "pch.h"
#include "SceneViewSystem.h"

#include "../ObjMeshSystem.h"
#include "../../ObjFileReader.h"
#include "../../Textures/Texture.h"
SceneViewSystem::SceneViewSystem()
{
}

void SceneViewSystem::Init()
{
	//This should maybe deal with it?
	///find all render components
	auto renders = Registry::Instance().GetComponents<RenderComponent>();
	Logger::Log("RednerSystem : Init renderers = " + renders.size(), INFO);
	for (auto render : renders) {

		Logger::Log("RednerSystem : Init starting init on renderer", INFO);
		//Check if we want to render
		if (!render->bRender) {
			Logger::Log("RednerSystem : Init should not render = " + renders.size(), INFO);
			continue;
		}
		//Check for material, the material should have a shader and a texture, 
		auto material = Registry::Instance().GetComponent<MaterialComponent>((uint32_t)render->mGO);
		if (material) {
			if (!material->mShader) {
				Logger::Log("RednerSystem : Init on shader", INFO);
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

			Logger::Log("RednerSystem : Init no material", INFO);
		}

		//Check for mesh
		auto mesh = Registry::Instance().GetComponent<MeshComponent>((uint32_t)render->mGO);
		if (mesh) {
			Logger::Log("RenderSystem : Now initing mesh ", INFO);
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
			render->mVAO = vao;
		}
		else {
			render->bRenderMesh = false;
			Logger::Log("RenderSystem : Found no mesh", INFO);
		}
		//Check if we should render

	}
}

void SceneViewSystem::OnUpdate(float deltaTime)
{
	///find all render components
	auto renders = Registry::Instance().GetComponents<RenderComponent>();
	if (renders.size() == 0) {
		Logger::Log("RenderSystem : Found no rendercomponents!", WARNING);
		return;
	}
	for (auto render : renders) {
		//Check if we want to render
		if (!render->bRender) {
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
				Logger::Log("RednerSystem : No Shader", INFO);
			}

			auto texture = material->mTexture;
			if (texture) {
				//This activates the 0'th texture unit
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, texture->id());
				if (shader) {
					//The diffuse sampler is using the 0'th texture unit
					shader->SetUniform1i(0, "diffuseSampler");
				}
			}
			else {
				Logger::Log("RenderSystem : No Texture", INFO);
			}
		}
		else {
			Logger::Log("RenderSystem : No material, cannot render!", ERROR, true);
		}


		auto mesh = Registry::Instance().GetComponent<MeshComponent>((uint32_t)render->mGO);
		if (!mesh) {
			Logger::Log("RenderSystem : No MeshComponent", INFO);
		}

		if (render->bRenderMesh) {
			//This should be replaced by calling Renderer functions from Renderer.cpp
			auto vao = render->mVAO;
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
}
