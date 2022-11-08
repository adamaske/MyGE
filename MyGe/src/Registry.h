#pragma once
#include <vector>
#include <unordered_map>
#include <string>
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

	template<class T>
	void Register(const T& item) {
		if (dynamic_cast<T>(item)) {

		}

		
	}

	int GetObjectID() { return 0; };
	
	template <class T>
	const T& GetObject(int objectID) {
		if(dynamic_cast<T>())
		return mGameObjects[std::to_string(objectID)];
	}

	const GameObject& GetGameObject(int id) {
		return mGameObjects[std::to_string(id)];
	}

	const Component& GetComponent(int id) {
		//This takes the components id

	}
private:
	std::vector<int> mIDs;
	std::unordered_map<std::string, class GameObject&> mGameObjects;
	std::unordered_map<std::string, class Component&> mComponentIDs;
	static Registry& mInstance;
};

