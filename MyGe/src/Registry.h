#pragma once
#include <vector>
#include <unordered_map>
#include <string>

#include "Shader.h"

class Registry
{
public:
	static Registry& Instance() {
		if (&mInstance) {
			return mInstance;
		}
		else {
			mInstance = Registry();
			//this.Register<TransformComponent>(TransformComponent());
			
			return mInstance;
		}
		
	};

	static void SetInstance(const Registry& r) {
		mInstance = r;
	}
	template<class T>
	void Register(const T& item) {
		
	}

	static const int GetNewID() {
		return mID++;
	}

	const GameObject& GetGameObject(int id) {
		return mGameObjects[std::to_string(id)];
	}

	const Component& GetComponent(int id) {
		
	}

	template <typename T>
	static T& GetObject(int objectID) {
		//We want a component T from the object 
		if (std::is_same(T, RenderComponent)::value == 1) {
			//T and a RenderComponent is the saame
		}
		return mGameObjects[std::to_string(objectID)];
	}

	template<typename T>
	std::vector<T&> GetObjects() {
		//Returns all objects of this type in this whole registry
		return mRenderComponents;
	}
	template<typename T>
	std::vector<T&> GetObjects(int id) {
		//Returns all objects of this type on the object with this id
		return mRenderComponents;
	}

	template<typename T>
	void RegisterComponent() {
		const char* typeName = typeid(T).name();

		mComponentTypes.insert({typeName, })
	}
private:
	std::vector<int> mIDs;
	std::unordered_map<std::string, class GameObject&> mGameObjects;
	std::unordered_map<std::string, class Component&> mComponentIDs;

	//I want a map which holds component types, these types each has a map with actual component refrences

	std::unordered_map<const char*, std::unordered_map<int, Component>> mComponentTypes;
	std::vector<class RenderComponent&> mRenderComponents;

	static Registry& mInstance;
	std::vector<Shader&> mShaders;

	static int mID = 0;
};

