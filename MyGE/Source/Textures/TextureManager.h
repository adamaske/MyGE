#pragma once

//At this point is there even any diffrences between managers and systems
class TextureManager {
public:
	TextureManager();
	//Go thourgh Resources/Textures and find jpgs, bmps etc
	static void LoadTextures();
	static void InsertTexture(std::string fileName, std::string name);
	static std::shared_ptr<Texture> GetTexture(std::string name);
	std::shared_ptr<Texture> GetTextureImpl(std::string name);

	//Return array of textures
	std::vector<int> GetTexturesInt();
private:
	std::unordered_map<std::string, std::shared_ptr<Texture>> mTextures;

	// todo here
	//Remove texture class, textures only need an int to be regonized

	std::unordered_map<std::string,int> mTextures2;
	

	static TextureManager& GetInstance() {
		static TextureManager instance;
		return instance;
	}
};
