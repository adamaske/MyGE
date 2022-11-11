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
	virtual ~IUnitHolder(){

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

	T& GetUnit(int objectID) {
		//We can safely return this becase Has should be called before
		std::cout << "Unit holder returning mUnits[ObjectID" << std::endl;
		return mUnits[objectID];
	}
	//Is there a component of this type with this object id?
	bool Contains(int objectID) {
		if (mUnits.find(objectID) != mUnits.end()) {
			return true;
		}
		else {
			return false;
		}
	}

	std::vector<T&> GetAllUnits() {
		std::vector<int> keys;
		keys.reserve(mUnits.size());
		std::vector<T&> vals;
		vals.reserve(mUnits.size());

		for (auto kv : mUnits) {
			keys.push_back(kv.first);
			vals.push_back(kv.second);
		}
		
		return vals;
	}
private:
	std::unordered_map<int, T> mUnits;
};
//Static instance of this regisrty
static class Registry* mInstance;
class Registry
{
public:
	Registry()   {
		//Reset the ID keeper
		mID = 0;
		std::cout << "Registry : Created" << std::endl;
	};
	//Instance 
	static Registry& Instance() {
		if (mInstance == nullptr) {
			mInstance = new Registry();
		}
		return *mInstance;
	}


	//Always returns a new not in-use ID
	static const int GetNewID() {
		Registry::Instance().mID = Registry::Instance().mID + 1;
		std::cout << "Registry :: GetNewID returned " << Registry::Instance().mID << std::endl;
		return Registry::Instance().mID;
	}

	//Tell the registry this component type exists
	template<typename T>
	void RegisterComponent(T& item, int objectID) {
		std::cout << std::endl << std::endl << "Registry : Starting To Register Component" << std::endl;
		//We know we want to register
		const char* typeName = typeid(T).name();
		if (mComponentTypes.find(typeName) != mComponentTypes.end()) {
			//If the components is already registered, return
			//No need to create a new UnitHolder
			//Now add the compnent
			std::cout << "Registry : There already is a component of this type, adding to UnitHolder<T>" << std::endl;
			if (Has<T>(objectID)) {
				std::cout << "Registry : There is a gameobject which has this type of component" << std::endl;
				//Since there already is a component of this type on this object, return
				std::cout << std::endl << std::endl << "Registry : Finished Register Component" << std::endl;
				return;
			}
			else {
				std::cout << "Registry : There is no gameobject with this ID that has this component" << std::endl;
				item.mGameObjectID = objectID;
				GetUnitHolder<T>()->Insert(objectID, item);
				std::cout << "Registry : Added a new component : " << " a " << typeName << ", " << objectID << std::endl;
				
				std::cout << std::endl << std::endl << "This component type already exists" << std::endl;
				std::cout << "The gameobject did have a component of this type yet" << std::endl;
				std::cout <<  "Registry : Finished Register Component" << std::endl;
				
				return;
			}
			
		}
		else {
			std::cout << "Registry : RegsiterComponent, there is no component of this type yet" << std::endl;

			mComponentTypes.insert({typeName, GetNewID()});
			std::cout << "Created a Component Type for this with key" << mComponentTypes[typeName] << std::endl;
			mComponentsHolder.insert({ typeName, new UnitHolder<T>()});
			item.mGameObjectID = objectID;
			
			//We must set the
			GetUnitHolder<T>()->Insert(objectID, item);
			std::cout <<"Registry : Finished Register Component" << std::endl;
			return;
		}
		
	};


	void RegisterGameObject(GameObject& object) {
		//Check there is no gameobejc with this identity already
		if (mGameObjects.find(object.mID) != mGameObjects.end()) {
			std::cout << "Registry : RegisterGameObject mGameObjects does already contain an GameObject with this ID" << std::endl;
			return;
		}

		mGameObjects.insert({ object.mID, object });
		std::cout << "Registry : RegisterGameObject the GameObject " << object.mID << " was added to mGameObjects" << std::endl;
	}

	//Adding a component must also have a entity
	template<typename T>
	void AddComponent(int objectID, T& component) {
		//We know we want to register

		//auto a = GetUnitHolder<T>();

		std::cout << "Registry : Added a new component";
	}

	template<typename T>
	T& GetComponent(int objectID){ 
		//Has has been called on this so we know we can return the unit holder
		return GetUnitHolder<T>()->GetUnit(objectID);
	}

	template<typename T>
	std::vector<T*> GetComponents() {
		std::vector<T*> vals;
		//This has been checked with Has so can safely return
		for (auto it = mGameObjects.begin(); it != mGameObjects.end(); it++)
		{
			vals.push_back(&GetUnitHolder<T>()->GetUnit((*it).first));
		}
		return vals;
	}
	template<typename T>
	std::vector<T> GetComponents(int objectID) {
		//Return all components from this item
		const char* typeName = typeid(T).name();
		std::cout << "Registry : GetComponents<T>(objectID) type " << typeName << std::endl;

		//Find if theres is an array of this item
		if (mComponentsHolder.find(typeName) == mComponentsHolder.end()) {
			//There is no unit holder with this Type of Component
			std::cout << "Regsitry : GetComponents<" << typeName << ">(" << objectID << ") there is no array of this kind" << std::endl;
			return std::vector<T>{};
		}
		auto t = GetComponents<T>;
		std::vector<T> units;
		for (int i = 0; i < t.size(); i++)
		{
			if (t.mGameObjectID == objectID) {
				units.push_back(units[i]);
			}
		}
		return units;
	}

	std::vector<GameObject> GetGameObjects() {
		std::vector<GameObject> objects;
		for (auto it = mGameObjects.begin(); it != mGameObjects.end(); it++)
		{
			objects.push_back((*it).second);
		}
		return objects;
	}

	template<typename T>
	bool Has(int objectID) 
	{
		const char* typeName = typeid(T).name();
		
		//We first need to know if there is a unit holder of this type
		if (mComponentTypes.find(typeName) != mComponentTypes.end()) {
			//There is a unit holder fo this type
			return GetUnitHolder<T>()->Contains(objectID);
		}
		else {
			//There is no unit holder of this type, so return false
			return false;
		}
	}

	//Does this registry have a component of this type
	template<typename T>
	bool Has() {
		const char* typeName = typeid(T).name();
		if (mComponentsHolder.find(typeName) == mComponentsHolder.end()) {
			//There is a unit holder with this type
			return false;
		}
		else {
			return true;
		}
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
	std::unordered_map <const char*, IUnitHolder*> mComponentsHolder;
	

	int mID;
	//This is the type of array we want to accsess
	template<typename T>
	UnitHolder<T>* GetUnitHolder() {
		//Gets the type of the component, for
		const char* typeName = typeid(T).name();
		std::cout << "GetUnitHolder : Getting Unit Holder for " << typeName << std::endl;
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
		return static_cast<UnitHolder<T>*>(mComponentsHolder[typeName]);
		//return std::static_pointer_cast<UnitHolder<T>>(mComponentsHolder[typeName]);
	}

};

