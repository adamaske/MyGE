




#include <iostream>
#include <fstream>
#include "glm/glm.hpp"
#include "Components.h"
#include "Vertex.h"'

using GameObject = uint32_t;

GameObject CreateGameObject(){
	return GetNewID();
}

mGameObjects.insert( {"Cube", Registry::Instance().CreateGameObject()});
std::unordered_map<const char*, GameObject> mGameObjects;

class System{
public:
	System();
	
	virutal void Init();
	
	virutal void OnUpdate(float deltaTime);
	
}


class ObjMeshSystem : public System{
public:
	virtual void Init(){
		mMeshes = Regisrty::Instance().GetComponents<MeshComponent>();
		for(int i = 0; i < mMeshes; i++){
			//We want vertices and indicies from the mesh
			std::pair<int, int> couple = LoadMesh(mMeshes[i].mMeshFilePath);
			mMeshes[i].mVertices = couple.first;
			mMeshes[i].mIndices = couple.second;
			//Get the render component on this
			mRender = Registry::Instance().GetComponent<RenderComponent>(mMeshes[i].mGameObjectID);
			
			
		}
	}
	
	virtual void OnUpdate(float deltaTime){
		mMeshes = Regisrty::Instance().GetComponents<MeshComponent>();
		for(int i = 0; i < mMeshes; i++){
			mRender = Registry::Instance().GetComponent<RenderComponent>(mMeshes[i].mGameObjectID);
			if(!mRender.bRender){
				
			}
			//We want vertices and indicies from the mesh
			std::pair<int, int> couple = LoadMesh(mMeshes[i].mMeshFilePath);
			mMeshes[i].mVertices = couple.first;
			mMeshes[i].mIndices = couple.second,
		}
	}
	
	std::pair<int, int>LoadMesh(const char* fileName){
		//Kopier obj mesh kode her
		std::ifstream file;
    file.open(filePath, std::ifstream::in);
    if(!file){
        qDebug() << "Didnt open file" << QString::fromStdString(filePath);
    }else{
        qDebug() << "Did open file" << QString::fromStdString(filePath);
    }
  ////check if obj file
  std::string copypath = filePath;
  if (copypath.substr(copypath.size() - 4, 4) != ".obj"){
      return;
  }

  ////check if file is not  open
  //if (!file.is_open()){
  //    return; // return if file cant be opened
  //}

    std::vector<glm::vec3> tempVertices;
    std::vector<glm::vec3> tempNormals;
    std::vector<std::pair<float,float>> tempUVs;

    std::string tmp{};
    std::string type;

    std::string oneLine;
    std::string oneWord;

    unsigned int temp_index = 0;

    while(std::getline(file, oneLine, '\n')){
        //Store one word at a time
        std::stringstream sstream;
        sstream << oneLine;
        //Reset the word
        oneWord = "";
        //Put the sstream word into oneWord
        sstream >> oneWord;

        if(oneWord == "#"){
            //This is a comment, do nothing
            continue;
        }
       //if(type == "m"){
       //    continue;
       //}
       //if(type == "s"){
       //    continue;
       //}
        if(oneWord == ""){
            //Ignores this line
            continue;
        }

        if(oneWord == "v"){
            //Line for vertex positions
            Vector3D tempVertex;
            sstream >> tmp;
            tempVertex.mX = std::stof(tmp);
            sstream >> tmp;
            tempVertex.mY = std::stof(tmp);
            sstream >> tmp;
            tempVertex.mZ = std::stof(tmp);

            tempVertices.push_back(tempVertex);
            continue;
        }
        if(oneWord == "vt"){
            std::pair<float, float> tempUV;
            sstream >> tmp;
            tempUV.first = std::stof(tmp);
            sstream >> tmp;
            tempUV.second = std::stof(tmp);

            tempUVs.push_back(tempUV);
            continue;
        }
        if(oneWord == "vn"){
            //Line for vertex positions
            Vector3D tempNormal;
            sstream >> tmp;
            tempNormal.mX = std::stof(tmp);
            sstream >> tmp;
            tempNormal.mY = std::stof(tmp);
            sstream >> tmp;
            tempNormal.mZ = std::stof(tmp);

            tempNormals.push_back(tempNormal);
            continue;
        }
        if(oneWord == "f"){
            int index, normal, uv;
            //behind f there is 3 words divided by /
            for(int i = 0; i < 3; i++){
                sstream >> oneWord;

                std::stringstream tempWord(oneWord);
                std::string segment;
                std::vector<std::string> segmentArray;
                //Get each number, add them as a string to segment array
                while(std::getline(tempWord, segment, '/')){
                    segmentArray.push_back(segment);
                }
                index = std::stoi(segmentArray[0]);

                //If the uv is blank, set it to 0
                if(segmentArray[1] != ""){
                    uv = std::stoi(segmentArray[1]);
                }else{
                    uv = 0;
                }
                //The normal is the third number, index 2 of the array
                normal = std::stoi(segmentArray[2]);

                //Obj f starts at 1 index, c++ array uses 0 as the starting index
                --index;
                --uv;
                --normal;
                //Check if it has a uv or not
                if(uv > -1){
                    Vertex tempVert(tempVertices[index], tempNormals[normal], tempUVs[uv]);
                    mVertices.push_back(tempVert);

                }else{
                    Vertex tempVert(tempVertices[index], tempNormals[normal], std::pair<float,float>(0,0));
                    mVertices.push_back(tempVert);
                }
                mIndices.push_back(temp_index++);

            }
            continue;
        }

    }
		qDebug() << "Finished reading file" << QString::fromStdString(filePath);
		file.close();
		writeFile(copypath + ".txt");
		return std::pair<int,int>({verts, indicies});
	}
	
	void writeFile(const char* fileName){
		std::ofstream ut;
       ut.open(filePath.c_str());

       if (ut.is_open())
       {
           auto n = mVertices.size();
           Vertex vertex;
           ut << n << std::endl;
           for (auto it=mVertices.begin(); it != mVertices.end(); it++)
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
	std::vector<int> mIndicies;
}
struct BoxCollider{

}

struct SphereCollider{
	int mGameObjectID;
	int mComponentID;
	
	

}
