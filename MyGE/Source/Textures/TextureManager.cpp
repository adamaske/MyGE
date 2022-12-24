#include "pch.h"
#include "TextureManager.h"
#include "Texture.h"

#include "../stb/stb_image.h"
TextureManager::TextureManager()
{
	auto texture = std::make_shared<Texture>();

	mTextures["DummyTexture"] = texture;
}

void TextureManager::LoadTextures()
{
	//TEsting
	//fs::path path = fs::path("../Resources/Textures/");
	//if (!fs::is_directory(path)) {
	//	Logger::Log("This is not a directory!");
	//	return;
	//}
	//Open some directory
	//auto dir = Directory::Open("../Resources/Textures");
	//for(auto file : dir), if(file = jpg)->
	// float width;
	// float height;
	// int channels;
	//unsigned char* image = stbi_load(fileName.c_str(), &width, &height, &channels, STBI_rgb);

	// Generate a texture object
	//unsinged int texture;
	//glGenTextures(1, &texture);

	// Bind the texture object to the GL_TEXTURE_2D target
	//glBindTexture(GL_TEXTURE_2D, texture);
	//
	//// Set the texture parameters
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//
	//// Upload the texture data to the GPU
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	//
	//// Free the image data, since it is now stored on the GPU
	//stbi_image_free(image);
	//
	//// Add the texture to the texture map
	//m_textures[textureName] = texture;
}

void TextureManager::InsertTexture(std::string fileName, std::string name)
{
	auto texture = std::make_shared<Texture>(fileName);
	unsigned int t;
	glGenTextures(1, &t);

	GetInstance().mTextures2[name] = t;

	GetInstance().mTextures[name] = texture;

	Logger::Log("TextureManager : InsertTexture " + name + " made");
}

std::shared_ptr<Texture> TextureManager::GetTexture(std::string name)
{
	return GetInstance().GetTextureImpl(name);
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

std::vector<int> TextureManager::GetTexturesInt()
{
	std::vector<int> textures;
	
	auto ts = GetInstance().mTextures2;
	for (auto t : ts) {
		textures.push_back(t.second);
	}
	return textures;
}



