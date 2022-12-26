#include "pch.h"
#include "TextureManager.h"
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"

TextureManager::TextureManager()
{
}

//Take in a path here, dependecy injection?
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
	// 
	//Use string here, this happens to so little it wont make a difference
	std::vector<std::string> texturePaths = { "GrassDiffuse.jpg" };
	for (auto t : texturePaths) {
		std::string path = "../Resources/Textures/";
		path.append(t);
		//	Gets path and name
		if (LoadTexture(path, t)) {
			Logger::Log("TextureManager : Load texture " + t);
		}
		else {
			Logger::Log("TextureManager : Could not load texture" + path, WARNING);
		}
	}
}

bool TextureManager::LoadTexture(std::string path, std::string name) {
	int width;
	int height;
	int channels;

	unsigned char* image = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb);

	// Generate a texture object
	GLuint texture;
	glGenTextures(1, &texture);

	// Bind the texture object to the GL_TEXTURE_2D target
	glBindTexture(GL_TEXTURE_2D, texture);

	//// Set the texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//
	//// Upload the texture data to the GPU
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	//// Free the image data, since it is now stored on the GPU
	stbi_image_free(image);

	// Add the texture to the texture map
	GetInstance().InsertTexture(name, texture);

	return true;
}

void TextureManager::InsertTexture(std::string name, int id)
{
	//auto texture = std::make_shared<Texture>(fileName);
	//unsigned int t;
	//glGenTextures(1, &t);
	//
	//GetInstance().mTextures2[name] = t;
	//
	//GetInstance().mTextures[name] = texture;
	//
	//Logger::Log("TextureManager : InsertTexture " + name + " made");

	mTextures[name] = id;
}

std::vector<int> TextureManager::GetTextures()
{
	return GetInstance().GetTexturesImpl();
}

std::vector<int> TextureManager::GetTexturesImpl()
{
	std::vector<int> textures;
	for (auto t : mTextures) {
		textures.push_back(t.second);
	}
	return textures;
}

int TextureManager::GetTexture(std::string name)
{
	return GetInstance().GetTextureImpl(name);
}

int TextureManager::GetTextureImpl(std::string name)
{
	if (mTextures.find(name) != mTextures.end()) {
		return mTextures[name];
	}
	else {
		return 0;
	}
	
}


