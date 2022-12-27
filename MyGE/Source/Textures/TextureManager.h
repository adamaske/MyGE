#pragma once

//At this point is there even any diffrences between managers and systems
class TextureManager {
public:
	TextureManager();
	//Go thourgh Resources/Textures and find jpgs, bmps etc
	static void LoadTextures();
	//Actually create the texture in opengl
	static bool LoadTexture(std::string path, std::string name);
	//Add the id to this instance
	void InsertTexture(std::string name, int id);

	//Return array of textures
	static std::vector<int> GetTextures();
	std::vector<int> GetTexturesImpl();

	static int GetTexture(std::string name);
	int GetTextureImpl(std::string name);
protected:
	std::unordered_map<std::string,int> mTextures;
	

	static TextureManager& GetInstance() {
		static TextureManager instance;
		return instance;
	}
};
