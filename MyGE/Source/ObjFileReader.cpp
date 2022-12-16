#include "pch.h"
#include "ObjFileReader.h"

std::pair<std::vector<Vertex>, std::vector<uint32_t>> ObjFileReader::GetMesh(std::string filePath)
{
    std::ifstream file;
    file.open(filePath, std::ifstream::in);
    if (!file) {
        Logger::Log("Could not open file " + filePath);
    }
    ////check if obj file
    std::string copypath = filePath;
    if (copypath.substr(copypath.size() - 4, 4) != ".obj") {
        return std::pair<std::vector<Vertex>, std::vector<uint32_t>>();
    }

    ////check if file is not  open
    //if (!file.is_open()){
    //    return; // return if file cant be opened
    //}
    std::vector<Vertex> mVertices;
    std::vector<uint32_t> mIndices;

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
    file.close();
   
	return std::pair<std::vector<Vertex>, std::vector<uint32_t>>(mVertices, mIndices);
}

std::pair<std::vector<float>, std::vector<uint32_t>> ObjFileReader::GetMeshNoVertex(std::string filePath)
{
    std::ifstream file;
    file.open(filePath, std::ifstream::in);
    if (!file) {
        Logger::Log("Could not open file" + filePath);
    }

    ////check if obj file
    std::string copypath = filePath;
    if (copypath.substr(copypath.size() - 4, 4) != ".obj") {
        return std::pair<std::vector<float>, std::vector<uint32_t>>();
    }

    ////check if file is not  open
    //if (!file.is_open()){
    //    return; // return if file cant be opened
    //}
    std::vector<float> mVertices;
    std::vector<uint32_t> mIndices;

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
                    //mVertices.push_back(tempVert);
                    mVertices.push_back(tempVert.x);
                    mVertices.push_back(tempVert.y);
                    mVertices.push_back(tempVert.z);
                    mVertices.push_back(tempVert.r);
                    mVertices.push_back(tempVert.g);
                    mVertices.push_back(tempVert.b);
                    mVertices.push_back(tempVert.t1);
                    mVertices.push_back(tempVert.t2);

                }
                else {
                    Vertex tempVert(tempVertices[index], tempNormals[normal], std::pair<float, float>(0, 0));
                    mVertices.push_back(tempVert.x);
                    mVertices.push_back(tempVert.y);
                    mVertices.push_back(tempVert.z);
                    mVertices.push_back(tempVert.r);
                    mVertices.push_back(tempVert.g);
                    mVertices.push_back(tempVert.b);
                    mVertices.push_back(0);
                    mVertices.push_back(0);
                }
                mIndices.push_back(temp_index++);

            }
            continue;
        }

    }
    file.close();

    return std::pair<std::vector<float>, std::vector<uint32_t>>(mVertices, mIndices);
}
