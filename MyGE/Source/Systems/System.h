#pragma once

#include <iostream>
#include <fstream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "Components.h"
#include "Registry.h"
#include "Vertex.h"'
#include <stdio.h>
#include <fstream>
#include <sstream>

class System {
public:
    virtual void Init() {

    };

    virtual void OnUpdate(float deltaTime) {
        std::cout << "System : OnUpdate" << std::endl;
    };
};

class CameraControllerSystem : public System {
public:
    virtual void Init() override {
        //Create cameras
    }

    virtual void OnUpdate(float deltaTime) {
        //Update cameras
        auto cameras = Registry::Instance().GetComponents<CameraComponent>();
        for (size_t i = 0; i < cameras.size(); i++) {
            if (cameras[i]->bIsMainCamera) {
                std::cout << "Doing Main Camera" << std::endl;
                //Apply rotations

                //Yaw affects both pitch and roll
                //Yaw = Y axis rotaiton
                // Yaw = glm::mod( Yaw + xoffset, 360.0f );


                //Pitch affects roll also
                //Pitch = X axis rotation

                //Roll =  z axis rotation
                cameras[i]->mForward;

                //Sets the right axis
                cameras[i]->mRight = glm::normalize(glm::cross(cameras[i]->mForward, cameras[i]->mGlobalUp));
                //Sets the up axis
                cameras[i]->mUp = glm::normalize(glm::cross(cameras[i]->mForward, -cameras[i]->mRight));

            }
        }
    }

    //Can have other functions than this
};

class ObjMeshSystem : public System {
public:// Set up vertex data (and buffer(s)) and attribute pointers
   
    virtual void Init() override{
        std::cout << "ObjMeshSystem : Init started!" << std::endl;
        if (!Registry::Instance().Has<MeshComponent>()) {
            std::cout << "The registry does not have a MeshComponent array" << std::endl;
            return;
        }
        else {
            std::cout << "The registry has a MeshComponent array" << std::endl;
        }
        auto meshes = Registry::Instance().GetComponents<MeshComponent>();
        std::cout << "ObjMeshSystem : Init got meshes "<< meshes.size() << std::endl;
        for (auto it = meshes.begin(); it != meshes.end(); it++) {
        std::cout << "ObjMeshSystem : Init : Setting up RenderComponent for " << (*it)->mGameObjectID << std::endl;
        if (!Registry::Instance().Has<RenderComponent>((*it)->mGameObjectID)) {
            //The game object of this NeshComponet has no render component
            std::cout << "ObjMeshSystem : Init : The game object of this MeshComponent has no RenderComponent" << std::endl;
            break;
        }
        auto& render = Registry::Instance().GetComponent<RenderComponent>((*it)->mGameObjectID);
        if (!render.bRender) {
            std::cout << "ObjMeshSystem : Init : RenderComponent bRender == false!" << std::endl;
        }
        //We want vertices and indicies from the mesh
        std::pair<std::vector<Vertex>, std::vector<GLuint>> couple = LoadMesh((*it)->mObjFilePath);
        (*it)->mVertices = couple.first;
        (*it)->mIndices = couple.second;
        
        //Instantiate 
        //Vertex array object-VAO
        glGenVertexArrays(1, &render.mVAO);
        //Bind VAO
        glBindVertexArray(render.mVAO);
        //Vertex buffer object to hold vertices - VBO
        glGenBuffers(1, &render.mVBO);
        glBindBuffer(GL_ARRAY_BUFFER, render.mVBO);
        glBufferData(GL_ARRAY_BUFFER, (*it)->mVertices.size() * sizeof(Vertex), (*it)->mVertices.data(), GL_STATIC_DRAW);

        // Element array buffer - EAB
        glGenBuffers(1, &render.mEAB);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render.mEAB);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (*it)->mIndices.size() * sizeof(uint32_t), (*it)->mIndices.data(), GL_STATIC_DRAW);

        //Verts
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        //Normals
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        //uvs
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        std::cout << "ObjMeshSystem : Init : Finished !" << std::endl;
        }
    }

    virtual void OnUpdate(float deltaTime) override{
        std::cout << std::endl << "ObjMeshSystem : OnUpdate" << std::endl;
        if (!Registry::Instance().Has<MeshComponent>()) {
            std::cout << "ObjMeshSystem : Exit update because no MeshComponents in Registry" << std::endl;
            return;
        }
        if (!Registry::Instance().Has<RenderComponent>()) {
            std::cout << "ObjMeshSystem : Exit update because no RenderComponents in Registry" << std::endl;
            return;
        }
        if (!Registry::Instance().Has<ShaderComponent>()) {
            std::cout << "ObjMeshSystem : Exit update because no ShaderComponents in Registry" << std::endl;
            return;
        }
        std::cout << "ObjMeshSystem : OnUpdate cleared checks!" << std::endl;
        auto meshes = Registry::Instance().GetComponents<MeshComponent>();
        for (int i = 0; i < meshes.size(); i++)
        {

            std::cout << "Scene : OnUpdate : MeshComponent OnUpdate!" << std::endl;
            //Get a render component from this meshcomponent
            RenderComponent& renderComponent = Registry::Instance().GetComponent<RenderComponent>(meshes[i]->mGameObjectID);
            //Get a shader component from this mesh component
            auto shader = ShaderManager::Instance()->GetShader("PlainShader");
            //If we found th ehsdaer "Plainshader
            if (!shader) {
                std::cout << "Did not find shader, returning" << std::endl;
                return;
            }
            //Use the shader

            if (!Registry::Instance().Has<TransformComponent>(meshes[i]->mGameObjectID)) {
                //There is no transform connected with this scene
            }
            TransformComponent& transform = Registry::Instance().GetComponent<TransformComponent>(meshes[i]->mGameObjectID);

            shader->SetUniformMatrix4(transform.mMatrix, "mMatrix");

            glBindVertexArray(renderComponent.mVAO);

            glDrawElements(GL_TRIANGLES, meshes[i]->mIndices.size(), GL_UNSIGNED_INT, nullptr);
            glBindVertexArray(0);
            std::cout << "RenderComponent : Render End!" << std::endl;
        }
        std::cout << std::endl << "ObjMeshSystem : OnUpdate Finished!" << std::endl << std::endl;;
    }

std::pair<std::vector<Vertex>, std::vector<GLuint>>LoadMesh(std::string filePath) {
        //Kopier obj mesh kode her
        std::ifstream file;
        file.open(filePath, std::ifstream::in);
        if (!file.is_open()) {
            std::cout  << "ObjMeshSystem : LoadMesh : Could not open file " << filePath << std::endl;
         
        }

        ////check if obj file
        std::string copypath = filePath;
        if (copypath.substr(copypath.size() - 4, 4) != ".obj") {
            std::cout << "ObjMeshSystem : LoadMesh : the file is no obj file" << std::endl;
        }

        ////check if file is not  open
        //if (!file.is_open()){
        //    return; // return if file cant be opened
        //}

        std::vector<Vertex> mVertices;
        std::vector<GLuint> mIndices;

        std::vector<glm::vec3> tempVertices;
        std::vector<glm::vec3> tempNormals;
        std::vector<std::pair<float, float>> tempUVs;

        std::string tmp{};
        std::string type;

        std::string oneLine;
        std::string oneWord;

        unsigned int temp_index = 0;

        while (std::getline(file, oneLine, '\n')) {
            //Store one word at a time
            std::stringstream sstream;
            sstream << oneLine;
            //Reset the word
            oneWord = "";
            //Put the sstream word into oneWord
            sstream >> oneWord;

            if (oneWord == "#") {
                //This is a comment, do nothing
                continue;
            }
            //if(type == "m"){
            //    continue;
            //}
            //if(type == "s"){
            //    continue;
            //}
            if (oneWord == "") {
                //Ignores this line
                continue;
            }

            if (oneWord == "v") {
                //Line for vertex positions
                glm::vec3 tempVertex = glm::vec3(1);
                sstream >> tmp;
                tempVertex.x = std::stof(tmp);
                sstream >> tmp;
                tempVertex.y = std::stof(tmp);
                sstream >> tmp;
                tempVertex.z = std::stof(tmp);

                tempVertices.push_back(tempVertex);
                continue;
            }
            if (oneWord == "vt") {
                std::pair<float, float> tempUV;
                sstream >> tmp;
                tempUV.first = std::stof(tmp);
                sstream >> tmp;
                tempUV.second = std::stof(tmp);

                tempUVs.push_back(tempUV);
                continue;
            }
            if (oneWord == "vn") {
                //Line for vertex positions
                glm::vec3 tempNormal = glm::vec3(1);
                sstream >> tmp;
                tempNormal.x = std::stof(tmp);
                sstream >> tmp;
                tempNormal.y = std::stof(tmp);
                sstream >> tmp;
                tempNormal.z = std::stof(tmp);

                tempNormals.push_back(tempNormal);
                continue;
            }
            if (oneWord == "f") {
                int index, normal, uv;
                //behind f there is 3 words divided by /
                for (int i = 0; i < 3; i++) {
                    sstream >> oneWord;

                    std::stringstream tempWord(oneWord);
                    std::string segment;
                    std::vector<std::string> segmentArray;
                    //Get each number, add them as a string to segment array
                    while (std::getline(tempWord, segment, '/')) {
                        segmentArray.push_back(segment);
                    }
                    index = std::stoi(segmentArray[0]);

                    //If the uv is blank, set it to 0
                    if (segmentArray[1] != "") {
                        uv = std::stoi(segmentArray[1]);
                    }
                    else {
                        uv = 0;
                    }
                    //The normal is the third number, index 2 of the array
                    normal = std::stoi(segmentArray[2]);

                    //Obj f starts at 1 index, c++ array uses 0 as the starting index
                    --index;
                    --uv;
                    --normal;
                    //Check if it has a uv or not
                    if (uv > -1) {
                        Vertex tempVert(tempVertices[index], tempNormals[normal], tempUVs[uv]);
                        mVertices.push_back(tempVert);

                    }
                    else {
                        Vertex tempVert(tempVertices[index], tempNormals[normal], std::pair<float, float>(0, 0));
                        mVertices.push_back(tempVert);
                    }
                    mIndices.push_back(temp_index++);

                }
                continue;
            }

        }
        std::cout << "ObjMeshSystem : LoadMesh : Finished reading file" << filePath << std::endl;
        file.close();
        writeFile(copypath + ".txt");
        return std::pair<std::vector<Vertex>, std::vector<GLuint>>({ mVertices, mIndices });
    }

    void writeFile(std::string filePath) {
        std::ofstream ut;
        ut.open(filePath);

        if (ut.is_open())
        {
            auto n = mVertices.size();
            Vertex vertex;
            ut << n << std::endl;
            for (auto it = mVertices.begin(); it != mVertices.end(); it++)
            {
                vertex = *it;
                ut << vertex << std::endl;
            }
            ut.close();
        }
    }
private:
    std::vector<MeshComponent> mMeshes;
    std::vector<Vertex> mVertices;
    std::vector<GLuint> mIndicies;
};

