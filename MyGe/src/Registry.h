#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include "Shader.h"
#include "Components.h"
#include "GameObject.h"

//Uses this abstration to keep a ComponentHolder as refrence without declaring tempalte at compile
class IUnitHolder
{
public:
	virtual ~IUnitHolder() {

	};
	virtual void EntityDestroyed(int id) {

	};
};

//Store components of a certain type
template<typename T>
class UnitHolder : public IUnitHolder {
public:
	UnitHolder() {
		std::cout << "UnitHolder for " << typeid(T).name() << std::endl;
		return;
	}
	template<typename T>
	void Insert(int objectID, T& t) {
		mUnits.insert({ objectID, t });
		std::cout << "UnitHolder : Inserted unit of type " << typeid(T).name() << ", " << objectID << std::endl;
	};

	void Pop(int id) {
		mUnits.erase(id);
		std::cout << "UnitHolder : Ereased unit" << std::endl;
	}

	T* GetUnit(int objectID) {
		if (mUnits.find(objectID) != mUnits.end()) {
			return &mUnits[objectID];
		}
		return nullptr;
	}

	std::vector<T*> GetAllUnits() {
		std::vector<T*> units;

		for (auto it = mUnits.begin(); it != mUnits.end(); it++)
		{
			units.push_back(&it->second);
		}
		return units;
	}
private:
	std::unordered_map<int, T> mUnits;
};


class Registry
{
public:
	Registry() {
		//Reset the ID keeper
		mID = 0;
		std::cout << "Registry : " << std::endl;
	};
	static Registry& Instance()
	{
		static Registry Instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return Instance;
	}

	void SetInstance(Registry& r) {
		mInstance = &r;
	}

	//Always returns a new not in-use ID
	static const int GetNewID() {
		Registry::Instance().mID = Registry::Instance().mID + 1;
		//std::cout << "Registry :: GetNewID returned " << Registry::Instance().mID << std::endl;
		return Registry::Instance().mID;
	}

	template<typename T>
	void RegisterComponent() {
		//We know we want to register
		const char* typeName = typeid(T).name();
		//Check if there already is a array containging this type of component
		if (mComponentTypes.find(typeName) != mComponentTypes.end()) {
			//Already exists 
			std::cout << "Registry : RegisterComponent() : mComponentTypes already contains this component!" << std::endl;
			return;
		}
		int componentTypeID = GetNewID();
		mComponentTypes.insert({ typeName, componentTypeID });
		mComponentsHolder.insert({ typeName, std::make_shared<UnitHolder<T>>() });

		std::cout << "Registry : RegisterComponent : Registered a " << typeName << std::endl;
	}

	
	//Tell the registry this component type exists
	template<typename T>
	void RegisterComponent(T item, int objectID) {
		//We know we want to register
		const char* typeName = typeid(T).name();
		if (mComponentTypes.find(typeName) != mComponentTypes.end()) {
			//If the components is already registered, return
			//No need to create a new UnitHolder
			//Now add the compnent
			std::cout << "Registry : There already is a component of this type, adding to UnitHolder<T>" << std::endl;
			//Now add the compnent
			//if (!GetUnitHolder<T>()) {
			//	//There is no unit holder for this component
			//	std::cout << "Registry : RegisterComponent : Got nullptr form UnitHolder, returning without adding it" << std::endl;
			//	return;
			//}
			//GetUnitHolder<T>()->Insert(objectID, item);
			std::cout << "Registry : Added a new component : " << " a " << typeName << ", " << objectID << std::endl;
			item.mGameObjectID = objectID;
			std::cout << "Registry : Completed" << std::endl;
			return;
		}

		//This type of component have not been seen before, so we have to create an array of component types
		//Register it by inserting it into mComponentTypes
		//This component 
		int componentTypeID = GetNewID();
		int componentID = GetNewID();

		//This now stores a the int compID as "TransformComponent" for example
		mComponentTypes.insert({ typeName, componentTypeID });
		//This may now be for example an element of "TransformComponent" and "1"
		//Now we want to create a holder for these types of components
		mComponentsHolder.insert({ typeName, std::make_shared<UnitHolder<T>>() });
		//This may now be "1"(the key for the array that holds TRansformHolders) and a UnitHolder<TransformComponent>,
		//Now add the compnent
		std::cout << "Registry : RegisterCompnent : Inserted component "  << typeName << ", " << objectID << std::endl;
		item.mGameObjectID = objectID;
		std::cout << "Registry : RegisterComponent : Completed" << std::endl;
		if (!GetUnitHolder<T>()) {
			std::cout << "Registry : RegisterComponent : GetUnitHolder on existing item returned nullptr" << std::endl;
			return;
		};
		GetUnitHolder<T>()->Insert(objectID, item);
		return;
	};

	
	void RegisterGameObject(GameObject& object) {
		//Check there is no gameobejc with this identity already
		if (mGameObjects.find(object.mID) != mGameObjects.end()) {
			std::cout << "Registry : RegisterGameObject mGameObjects does already contain an GameObject with this ID" << std::endl;
			return;
		}
		
		mGameObjects.insert({ object.mID, object });
		std::cout << "Registry : RegisterGameObject the GameObject" << object.mID << "was added to mGameObjects" << std::endl;
	}

	//Adding a component must also have a entity
	template<typename T>
	void AddComponent(int objectID, T& component) {
		//We know we want to register

		//auto a = GetUnitHolder<T>();

		std::cout << "Registry : Added a new component";
	}

	template<typename T>
	T* GetComponent(int objectID) {
		const char* typeName = typeid(T).name();
		//Find if theres is an array of this item
		if (mComponentsHolder.find(typeName) == mComponentsHolder.end()) {
			//There is no unit holder with this Type of Component
			std::cout << "GetComponent returned nullptr" << std::endl;
			return nullptr;
			
		}
		auto t = GetUnitHolder<T>()->GetUnit(objectID);
		if (!t) {
			//N
			std::cout << "Registry : GetComponent<T>(objectID) get unit holer got nullptr" << std::endl;
			return nullptr;
		}
		//mComponentTypes has a Holder for this Type of component
		std::cout << "Registry : GetComponent<T>(objectID) returned a component of this type with this component id" << std::endl;
		return GetUnitHolder<T>()->GetUnit(objectID);
	}

	template<typename T>
	std::vector<T*> GetComponents() {
		const char* typeName = typeid(T).name();
		//Find if theres is an array of this item
		if (mComponentsHolder.find(typeName) != mComponentsHolder.end()) {
			//mComponentTypes has a Holder for this Type of component
			std::cout << "Registry : GetComponents<T>() returning UnitHolder " << std::endl;
			return GetUnitHolder<T>()->GetAllUnits();
		}
		////std::cout << "Registry : GetComponents<T>() return empty vector" << std::endl;
		std::vector<T*> v{};
		return v;
	}
	template<typename T>
	std::vector<T&> GetComponents(int objectID) {

		const char* typeName = typeid(T).name();
		std::cout << "Registry : GetComponents<T>(objectID) type " << typeName << std::endl;

		//Find if theres is an array of this item
		if (mComponentsHolder.find(typeName) == mComponentsHolder.end()) {
			//There is no unit holder with this Type of Component
			std::cout << "Regsitry : GetComponents<" << typeName << ">(" << objectID << ") there is no array of this kind" << std::endl;
			return std::vector<T&>{};
		}
		//auto t = GetComponents<T&>;
		//std::vector<T&> units;
		//for (int i = 0; i < t.size(); i++)
		//{
		//	if (t.mGameObjectID == objectID) {
		//		units.push_back(units[i]);
		//	}
		//}
		//return units;
	}

	std::vector<GameObject> GetGameObjects() {
		std::vector<GameObject> objects;
		for (auto it = mGameObjects.begin(); it != mGameObjects.end(); it++)
		{
			objects.push_back((*it).second);
		}
		return objects;
	}

private:
	//We want a unorerd map which holds the string for which type has come in
	// when that type is stored, 
	//I want a map which holds component types, these types each has a map with actual component refrences	
	//GameObjects
	std::unordered_map<int, GameObject> mGameObjects;

	//Components
	//This holds a string which is the type of the component to a string, 
	//IUnitHolder is a virtual interface, subclass is only a container of a specific type
	std::unordered_map<const char*, int> mComponentTypes;
	std::unordered_map <const char*, std::shared_ptr<IUnitHolder>> mComponentsHolder;
	//Static instance of this regisrty
	Registry* mInstance;

	int mID;
	//This is the type of array we want to accsess
	template<typename T>
	std::shared_ptr<UnitHolder<T>> GetUnitHolder() {
		//Gets the type of the component, for
		const char* typeName = typeid(T).name();
		//mComponentTypes has a Value with this T as a Key, 
		//If the theres is no unit holder with this type
		if (mComponentsHolder.find(typeName) == mComponentsHolder.end()) {

			//No component of this type found 
			//return std::static_pointer_cast<UnitHolder<T>>(mComponents[typeName]);
			std::cout << "Registry : GetUnitHolder<" << typeName << "> does not have an array! Returning from here!" << std::endl;
			return nullptr;
		}
		//This returns correct array of components for the type
		//typeName is the type of the component
		//Casting a IComponentHolder to a ComponentHolder, casts down from IComponent to Component
		return std::static_pointer_cast<UnitHolder<T>>(mComponentsHolder[typeName]);
	}

};

