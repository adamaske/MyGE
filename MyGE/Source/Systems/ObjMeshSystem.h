#pragma once

#include "System.h"
#include "../Shader.h"
#include "../ShaderManager.h"
class ObjMeshSystem : public System {
public:// Set up vertex data (and buffer(s)) and attribute pointers

    
    virtual void Init() override {
        return;
        if (!Registry::Instance().Has<MeshComponent>()) {
            std::cout << "The registry does not have a MeshComponent array" << std::endl;
            return;
        }

        auto meshes = Registry::Instance().GetComponents<MeshComponent>();

        for (auto mesh : meshes) {

            auto go = mesh->mGO;

            if (!Registry::Instance().Has<RenderComponent>(go)) {
                //The game object of this NeshComponet has no render component
                std::cout << "ObjMeshSystem : Init : The game object of this MeshComponent has no RenderComponent" << std::endl;
                break;
            }

           
            //Find the renderer for this component
            auto render = Registry::Instance().GetComponent<RenderComponent>((uint32_t)mesh->mGO);

            //We want vertices and indicies from the mesh
            std::pair<std::vector<float>, std::vector<uint32_t>> meshData = LoadMesh(mesh->mObjFilePath);
            std::cout << "ObjMesh : Init : size of meshData.first = " << meshData.first.size() << std::endl;
            std::cout << "ObjMesh : Init : size of meshData.second = " << meshData.second.size() << std::endl;
            //mesh->mVertices = meshData.first;
            for (int i = 0; i < 100; i += 8) {
                std::cout << "v1(" << meshData.first[i] << "), " << "v2(" << meshData.first[i + 1] << ")," << "v3(" << meshData.first[i + 2] << ")" << std::endl;

                std::cout << "n1(" << meshData.first[i + 3] << "), " << "n2(" << meshData.first[i + 4] << ")," << "n3(" << meshData.first[i + 5] << ")" << std::endl;

                std::cout << "t1(" << meshData.first[6] << "), " << "t2(" << meshData.first[i + 7] << ")" << std::endl;
            }
            //Vertex array object-VAO
            auto vao = std::make_shared<VertexArray>();
            //Bind VAO

            //Vertex buffer object to hold vertices - VBO
            auto vbo = std::make_shared<VertexBuffer>(meshData.first.data(), sizeof(meshData.first));

            vao->AddVertexBuffer(vbo);

            // Element array buffer - EAB - ibo
            auto ibo = std::make_shared<IndexBuffer>(meshData.second.data(), sizeof(meshData.second));
            vao->AddIndexBuffer(ibo);

            auto material = Registry::Instance().GetComponent<MaterialComponent>((uint32_t)mesh->mGO);
            if (material) {
                if (material->bUseTexture && material->mTexture) {
                    //material->mTexture->useTexture();
                }
            }
           //glGenVertexArrays(1, &render->m_VAO);
           //glBindVertexArray(render->m_VAO);
           //
           ////Vertex buffer object to hold vertices - VBO
           //glGenBuffers(1, &render->m_VBO);
           //glBindBuffer(GL_ARRAY_BUFFER, render->m_VBO);
           //
           //glBufferData(GL_ARRAY_BUFFER, mesh->mVertices.size() * sizeof(Vertex), &mesh->mVertices[0], GL_STATIC_DRAW);
           //
           ////Verts
           //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
           //glEnableVertexAttribArray(0);
           ////Colors
           //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
           //glEnableVertexAttribArray(1);
           ////uvs
           //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));
           //glEnableVertexAttribArray(2);
           //
           //// Element array buffer - EAB
           //glGenBuffers(1, &render->m_IBO);
           //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render->m_IBO);
           //glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->mIndices.size() * sizeof(GLuint), mesh->mIndices.data(), GL_STATIC_DRAW);
           //
            //Add them to the vertex array
            render->mVAO = vao;


        }
    }

    virtual void OnUpdate(float deltaTime) override {
        return;
        auto meshes = Registry::Instance().GetComponents<MeshComponent>();

        for (auto mesh : meshes)
        {
            auto go = (uint32_t)(*mesh).mGO;
            //Get a render component from this meshcomponent
            auto renderComponent = Registry::Instance().GetComponent<RenderComponent>(go);
            //Get a shader component from this mesh component
            auto shader = ShaderManager::Instance()->GetShader("PlainShader");

            //If we found th ehsdaer "Plainshader
            if (!shader) {
                std::cout << "Did not find shader, returning" << std::endl;
                return;
            }
            //Use the shader

            if (!Registry::Instance().Has<TransformComponent>(mesh->mGO)) {
                //There is no transform connected with this scene
            }
            auto transform = Registry::Instance().GetComponent<TransformComponent>(mesh->mGO);

            shader->SetUniformMatrix4(transform->mMatrix, "mMatrix");
            //We want from this vao
            if (!renderComponent->mVAO) {
                std::cout << "ObjMeshSystem : RenderComponent dosent have a VAO" << std::endl;
                return;
            }
            auto vao = renderComponent->mVAO;
            vao->Bind();
            //Draws from the bound vao
            glDrawElements(GL_TRIANGLES, vao->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
            vao->Unbind();
        }
    }
    std::pair<std::vector<float>, std::vector<uint32_t>>LoadMesh(std::string filePath) {
        //Kopier obj mesh kode her
        std::ifstream file;
        file.open(filePath, std::ifstream::in);
        if (!file.is_open()) {
            std::cout << "ObjMeshSystem : LoadMesh : Could not open file " << filePath << std::endl;

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
        std::vector<float> verts;
        std::vector<uint32_t> inds;
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
                        verts.push_back(tempVertices[index].x);
                        verts.push_back(tempVertices[index].y);
                        verts.push_back(tempVertices[index].z);
                        verts.push_back(tempNormals[normal].r);
                        verts.push_back(tempNormals[normal].g);
                        verts.push_back(tempNormals[normal].b);
                        verts.push_back(tempUVs[uv].first);
                        verts.push_back(tempUVs[uv].second);

                    }
                    else {
                        Vertex tempVert(tempVertices[index], tempNormals[normal], std::pair<float, float>(0, 0));
                        mVertices.push_back(tempVert);
                        verts.push_back(tempVertices[index].x);
                        verts.push_back(tempVertices[index].y);
                        verts.push_back(tempVertices[index].z);
                        verts.push_back(tempNormals[normal].r);
                        verts.push_back(tempNormals[normal].g);
                        verts.push_back(tempNormals[normal].b);
                        verts.push_back(0);
                        verts.push_back(0);
                    }
                    //Put in ++ when mIndecies is removed
                    inds.push_back(temp_index++);

                }
                continue;
            }

        }
        file.close();
        writeFile(copypath + ".txt");
        std::cout << "ObjMesh: loadMesh : size of verts = " << verts.size() << std::endl;;
        return std::pair<std::vector<float>, std::vector<uint32_t>>({ verts, inds });
    }

    void writeFile(std::string filePath) {
        //std::ofstream ut;
        //ut.open(filePath);
        //
        //if (ut.is_open())
        //{
        //    auto n = mVertices.size();
        //    Vertex vertex;
        //    ut << n << std::endl;
        //    for (auto it = mVertices.begin(); it != mVertices.end(); it++)
        //    {
        //        vertex = *it;
        //        ut << vertex << std::endl;
        //    }
        //    ut.close();
        //}
    }

};

