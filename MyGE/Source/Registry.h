#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>

//Needs only to know about all the components and the GameObject 
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
	}
	template<typename T>
	void Insert(int objectID, T& t) {
		mUnits.insert({ objectID, t });
	};

	void Pop(int id) {
		mUnits.erase(id);
	}
	//Does this have any at all, this can techinaccly exist without any items in it yet
	bool Has() {
		if (mUnits.size() > 0) {
			return true;
		}
		else {
			return false;
		}
	}
	//Does this item holder have a key equal to that object
	bool Has(int objectID) {
		if (mUnits.find(objectID) != mUnits.end()) {
			return true;
		}
		else {
			return false;
		}
	}

	//Get a specific unit, should be lighting fast because it just returns a map position 
	T& GetUnit(int objectID) {
		//We can safely return this becase Has should be called before
		return mUnits[objectID];
	}

	//Get all objects in this holder
	std::vector<T&> GetAllUnits() {
		std::vector<T&> vals;
		vals.reserve(mUnits.size());

		for (auto kv : mUnits) {
			vals.push_back(kv.second);
		}
		
		return vals;
	}

	//Get all the units which has this component
	std::vector<int> GeAllUnitsKeys() {
		std::vector<int> keys;
		keys.reserve(mUnits.size());

		for (auto kv : mUnits) {
			keys.push_back(kv.first);
		}

		return keys;
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

	~Registry() {
		delete mInstance;
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

	int NewGameObject() {
		GameObject go = GameObject();
		//All new gameobjects wants a transform
		go.mID = GetNewID();
		RegisterGameObject(go);
		RegisterComponent<struct TransformComponent>(TransformComponent(), go.mID);
		return go.mID;
	}

	//Only register a component
	template<typename T>
	void RegisterComponent() {
		const char* typeName = typeid(T).name();
		if (mComponentTypes.find(typeName) == mComponentTypes.end()) {
			mComponentTypes.insert({ typeName, GetNewID() });
			mComponentsHolder.insert({ typeName, new UnitHolder<T>() });
		}
		else {
			return;
		}
	}


	//Register a specific component to a gameobject
	template<typename T>
	T& RegisterComponent(T item, int objectID) {
		//this function returns nomatter what
		//We know we want to register
		const char* typeName = typeid(T).name();
		if (mComponentTypes.find(typeName) != mComponentTypes.end()) {
			//If the components is already registered, return
			//No need to create a new UnitHolder
			//Now add the compnent
		
			if (Has<T>(objectID)) {
				std::cout << "Registry : There is a gameobject which has this type of component" << std::endl;
				//Since there already is a component of this type on this object, return
				std::cout << std::endl << std::endl << "Registry : Returned becuse this object already exists on this object" << std::endl;
				return GetUnitHolder<T>()->GetUnit(objectID);
			}
			
			item.mGameObjectID = objectID;

			//Insert the component into the unitholder
			GetUnitHolder<T>()->Insert(objectID, item);
			return GetUnitHolder<T>()->GetUnit(objectID);
		}
		else {
			//There was no component of this type yet
			RegisterComponent<T>();
			
			item.mGameObjectID = objectID;
			
			//We must set the
			GetUnitHolder<T>()->Insert(objectID, item);
			std::cout <<"Registry : Finished Register Component" << std::endl;
			return GetUnitHolder<T>()->GetUnit(objectID);
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
		GetUnitHolder<T>()->Insert(objectID, component);
	}

	//If the gameobject has this type of component, return it
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

	//Get allt 
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

	template<typename T>
	void GetAllComponentsOfType() {

		//This should always be ok because Has has been called before
		return mComponentsHolder[typeid(T).name()];
	}

	//Gets all the gameobjects
	std::vector<GameObject> GetGameObjects() {
		std::vector<GameObject> objects;
		for (auto it = mGameObjects.begin(); it != mGameObjects.end(); it++)
		{
			objects.push_back((*it).second);
		}
		return objects;
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
			//also check if there is a single component of this type in the holder
			return GetUnitHolder<T>()->Has();
		}
	}
	//Does this specific object have a T component?
	template<typename T>
	bool Has(int objectID) 
	{
		const char* typeName = typeid(T).name();
		if (mComponentsHolder.find(typeName) == mComponentsHolder.end()) {
			//There is a unit holder with this type
			std::cout << "Becuse there is no component holder of this type";
			return false;
		}
		else {
			//also check if there is a single component of this type in the holder
			return GetUnitHolder<T>()->Has(objectID);
		}
	}

	void GetAllObjectsWithComponent(int objectID) {

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
		//mComponentTypes has a Value with this T as a Key, 
		//If the theres is no unit holder with this type
		if (mComponentsHolder.find(typeName) == mComponentsHolder.end()) {

			//No component of this type found 
			//return std::static_pointer_cast<UnitHolder<T>>(mComponents[typeName]);
			return nullptr;
		}
		//This returns correct array of components for the type
		//typeName is the type of the component
		//Casting a IComponentHolder to a ComponentHolder, casts down from IComponent to Component
		return static_cast<UnitHolder<T>*>(mComponentsHolder[typeName]);
		//return std::static_pointer_cast<UnitHolder<T>>(mComponentsHolder[typeName]);
	}

};

