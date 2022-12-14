#include "pch.h"
#include "TextureManager.h"
#include "Texture.h"



TextureManager::TextureManager()
{
	TextureManagerInstance = this;
	auto texture = std::make_shared<Texture>();

	mTextures["DummyTexture"] = texture;
}

void TextureManager::InsertTexture(std::string fileName, std::string name)
{
	auto texture = std::make_shared<Texture>(fileName);

	mTextures[name] = texture;
}

std::shared_ptr<Texture> TextureManager::GetTexture(std::string name)
{
	return TextureManagerInstance->GetTextureImpl(name);
}

std::shared_ptr<Texture> TextureManager::GetTextureImpl(std::string name)
{
	if (mTextures.find(name) != mTextures.end()) {
		return mTextures[name];
	}
	else {
		return std::shared_ptr<Texture>();
	}
	
}



