#pragma once
static class TextureManager* TextureManagerInstance;
class TextureManager {
public:
	TextureManager();
	void InsertTexture(std::string fileName, std::string name);
	static std::shared_ptr<Texture> GetTexture(std::string name);
	std::shared_ptr<Texture> GetTextureImpl(std::string name);
private:
	std::unordered_map<std::string, std::shared_ptr<Texture>> mTextures;

};
