#include "pch.h"
#include "CameraSystem.h"
#include "../Cameras/Camera.h"

#include "../Shaders/Shader.h"
#include "../Shaders/ShaderManager.h"

#include "../Components/Components.h"
void CameraSystem::Init(){
    //Init cameras
	auto cameras = Registry::Instance().GetComponents<CameraComponent>();
	for (auto cam : cameras) {
		cam->mCamera = std::make_shared<Camera>(cam);
	}
}

void CameraSystem::OnUpdate(float deltaTime) {
	//returns here, this must be handled differently based on scene or game view

	//We want an array of every camera in the scene
	//If we find a camera whith bisMainCamera  = true, that is the one we want to render the scene view from
	auto cameras = Registry::Instance().GetComponents<CameraComponent>();
	for (auto cam : cameras)
	{
		//GameObject ID
		GameObject go = cam->mGO;
		//Gets a transform for the camera
		auto transform = Registry::Instance().GetComponent<TransformComponent>(go);
		//Where is the actor with the camera, add some offset to this probably
		glm::vec3 pos(transform->mMatrix[3].x, transform->mMatrix[3].y, transform->mMatrix[3].z);

		//Set p and v matrices
		cam->mViewMatrix = glm::lookAt(pos, pos + glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));	//add near and far to camera
		cam->mProjectionMatrix = glm::perspective(glm::radians(90.f), cam->mAspectRatio, 0.1f, 1000.f);
		
		//We want the shaders to use the bIsMainCamera for game view,
		if (cam->bIsMainCamera) {
			//Get shaders
			auto shaders = ShaderManager::Instance()->GetShaders();
			for (auto shader : shaders) {
				//Use this shader
				shader->Use();
				//Set the variables in the shaders, I currently dont know any scenario where this changes
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

void CameraSystem::SetViewAndProjectionMatrix(std::shared_ptr<CameraComponent> cam)
{
	
}
