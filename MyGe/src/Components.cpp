#include "Components.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Vertex.h"
Component::Component(GameObject* parent)
{
	mParent = parent;
}

Component::~Component()
{
}

void Component::Init()
{
}

void Component::OnUpdate(float ts)
{
}


void MeshComponent::Readfile(std::string filePath) {

   

    mVertices.push_back( Vertex(glm::vec3(-1,-0.2,1)));
    mVertices.push_back( Vertex(glm::vec3(1, 0.2, 1)));
    mVertices.push_back( Vertex(glm::vec3(-1, 0.3, -1)));
    mVertices.push_back( Vertex(glm::vec3(1, -0.3, -1)));

    mIndices.push_back(0);
    mIndices.push_back(1);
    mIndices.push_back(2);

    mIndices.push_back(3);
    mIndices.push_back(1);
    mIndices.push_back(2);
    return;
    std::cout << "Mesh being created from fiel!!" << std::endl;
    std::ifstream file;
    file.open(filePath, std::ifstream::in);
    if (!file) {
        std::cout << "MeshComponent::Readfile Coulnd not open file!" << std::endl;
    }
    else {
        std::cout << "Did open file!" << std::endl;
    }
    ////check if obj file
    std::string copypath = filePath;
    if (copypath.substr(copypath.size() - 4, 4) != ".obj") {
        std::cout << "This is not a obj file!" << std::endl;
    }

    ////check if file is not  open
    //if (!file.is_open()){
    //    return; // return if file cant be opened
    //}

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
            glm::vec3 tempVertex;
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
            glm::vec3 tempNormal;
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
    std::cout << "Finished reading file!" << std::endl;
    file.close();
    WriteFile(copypath + ".txt");
}

void MeshComponent::WriteFile(std::string filePath) {
    std::ofstream ut;
    ut.open(filePath.c_str());

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