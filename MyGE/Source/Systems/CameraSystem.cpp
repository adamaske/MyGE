#include "CameraSystem.h"

void CameraSystem::Init(){
    //Init cameras
}

void CameraSystem::OnUpdate(float deltaTime) {
    //Update cameras
    auto cameras = Registry::Instance().GetComponents<CameraComponent>();
    for (auto cam : cameras) {
        if (cam->bIsMainCamera) {
            //Apply rotations

            //Yaw affects both pitch and roll
            //Yaw = Y axis rotaiton
            // Yaw = glm::mod( Yaw + xoffset, 360.0f );


            //Pitch affects roll also
            //Pitch = X axis rotation

            //Roll =  z axis rotation
            cam->mForward;

            //Sets the right axis
            cam->mRight = glm::normalize(glm::cross(cam->mForward, cam->mGlobalUp));
            //Sets the up axis
            cam->mUp = glm::normalize(glm::cross(cam->mForward, -cam->mRight));

        }
    }
}