#include "pch.h"
#include "CameraSystem.h"

#include "../Shader.h"
#include "../ShaderManager.h"
void CameraSystem::Init(){
    //Init cameras
}

void CameraSystem::OnUpdate(float deltaTime) {

	//We want an array of every camera in the scene
	//If we find a camera whith bisMainCamera  = true, that is the one we want to render the scene view from
	auto cameras = Registry::Instance().GetComponents<CameraComponent>();
	for (auto cam : cameras)
	{
		auto go = (uint32_t)(*cam).mGO;
		//It does find 
		//Check if it is the main camera
		if (cam->bIsMainCamera) {
			//Gets a transform for the camera
			auto transform = Registry::Instance().GetComponent<TransformComponent>(go);
			//Get the shader to apply my view and projection matrix
			auto shader = ShaderManager::Instance()->GetShader("MyGEShader");
			
			//Use this shader
			shader->Use();
			//Get a position
			glm::vec3 pos(transform->mMatrix[3].x, transform->mMatrix[3].y, transform->mMatrix[3].z);
			//Update matrices 
			cam->mProjectionMatrix = glm::perspective(glm::radians(90.f), cam->mAspectRatio, 0.1f, 1000.f);

			cam->mViewMatrix = glm::lookAt(pos, pos + glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));
			
			auto shaders = ShaderManager::Instance()->GetShaders();
			for (auto shader : shaders) {
				//Set the variables in the shaders, every shader should have these variables
				shader->SetUniformMatrix4(cam->mViewMatrix, "vMatrix");
				shader->SetUniformMatrix4(cam->mProjectionMatrix, "pMatrix");

			}
		}
	}

    ////Update cameras
    //auto cameras = Registry::Instance().GetComponents<CameraComponent>();
    //for (auto cam : cameras) {
    //    if (cam->bIsMainCamera) {
    //        //Apply rotations
	//
    //        //Yaw affects both pitch and roll
    //        //Yaw = Y axis rotaiton
    //        // Yaw = glm::mod( Yaw + xoffset, 360.0f );
	//
	//
    //        //Pitch affects roll also
    //        //Pitch = X axis rotation
	//
    //        //Roll =  z axis rotation
    //        cam->mForward;
	//
    //        //Sets the right axis
    //        cam->mRight = glm::normalize(glm::cross(cam->mForward, cam->mGlobalUp));
    //        //Sets the up axis
    //        cam->mUp = glm::normalize(glm::cross(cam->mForward, -cam->mRight));
	//
    //    }
    //}

	
}