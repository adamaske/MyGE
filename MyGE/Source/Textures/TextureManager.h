#pragma once
class TextureManager {
public:
	TextureManager();
	//Go thourgh Resources/Textures and find jpgs, bmps etc
	static void LoadTextures();
	static void InsertTexture(std::string fileName, std::string name);
	static std::shared_ptr<Texture> GetTexture(std::string name);
	std::shared_ptr<Texture> GetTextureImpl(std::string name);

	//Return array of textures
	std::vector<int> GetTextures();
private:
	std::unordered_map<std::string, std::shared_ptr<Texture>> mTextures;

	// todo here
	//Remove texture class, textures only need an int to be regonized

	std::unordered_map<std::string, unsinged int> mTextures2;
	

	static TextureManager& GetInstance() {
		static TextureManager instance;
		return instance;
	}
};
