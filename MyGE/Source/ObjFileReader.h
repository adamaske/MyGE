#pragma once

class ObjFileReader {

public:
    //Version using Vertex class
	static std::pair<std::vector<Vertex>, std::vector<uint32_t>> GetMesh(std::string filePath);
    //Version using float instead of vertex
    static std::pair<std::vector<float>, std::vector<uint32_t>> GetMeshNoVertex(std::string filePath);
};

