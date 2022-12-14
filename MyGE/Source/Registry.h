#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>

//Needs only to know about all the components and the GameObject 
#include "Components/Components.h"

using GameObject = uint32_t;
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
	void Insert(uint32_t objectID, std::shared_ptr<T> t) {
		mUnits.insert({ objectID, t });
	};

	void Pop(uint32_t id) {
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
	bool Has(uint32_t objectID) {
		if (mUnits.find(objectID) != mUnits.end()) {
			return true;
		}
		else {
			return false;
		}
	}

	//Get a specific unit, should be lighting fast because it just returns a map position 
	std::shared_ptr<T> GetUnit(uint32_t objectID) {
		//We can safely return this becase Has should be called before
		return mUnits[objectID];
	}

	//Get all objects in this holder
	std::vector<std::shared_ptr<T>> GetAllUnits() {
		std::vector<std::shared_ptr<T>> vals;
		for (auto kv : mUnits) {
			vals.push_back(kv.second);
		}
		
		return vals;
	}
	
	//Get all the units which has this component
	std::vector<uint32_t> GeAllUnitsKeys() {
		std::vector<uint32_t> keys;
		
		for (auto kv : mUnits) {
			keys.push_back(kv.first);
		}

		return keys;
	}

private:
	std::unordered_map<uint32_t, std::shared_ptr<T>> mUnits;
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
		//delete mInstance;
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

	uint32_t NewGameObject() {
		GameObject go = GetNewID();
		//All new gameobjects wants a transform
		RegisterGameObject(go);
		RegisterComponent<struct TransformComponent>(TransformComponent(), go);
		RegisterComponent<struct MaterialComponent>(MaterialComponent(), go);
		return go;
	}

	//Only register a component
	template<typename T>
	void RegisterComponent() {
		const char* typeName = typeid(T).name();
		if (mComponentsHolder.find(typeName) == mComponentsHolder.end()) {
			mComponentsHolder.insert({ typeName, new UnitHolder<T>() });

			std::cout << "Registered new component " << typeName << std::endl;
		}
	}

	//Register a specific component to a gameobject
	template<typename T>
	std::shared_ptr<T> RegisterComponent(T i, GameObject go) {
		auto item = std::make_shared<T>();
		//this function returns nomatter what
		//We know we want to register
		const char* typeName = typeid(T).name();
		std::cout << "Got order to register a " << typeName << " to object " << go << std::endl;
		if (mComponentsHolder.find(typeName) != mComponentsHolder.end()) {
			//If the components is already registered, return
			//No need to create a new UnitHolder
			//Now add the compnent
		
			if (Has<T>(go)) {
				//Since there already is a component of this type on this object, return
				return GetUnitHolder<T>()->GetUnit(go);
			}

			//Insert the component into the unitholder
			GetUnitHolder<T>()->Insert(go, item);
			GetUnitHolder<T>()->GetUnit(go)->mGO = go;
			return GetUnitHolder<T>()->GetUnit(go);
		}
		else {
			//There was no component of this type yet, register it
			RegisterComponent<T>();
			
			//We must set the
			GetUnitHolder<T>()->Insert(go, item);
			GetUnitHolder<T>()->GetUnit(go)->mGO = go;
			return GetUnitHolder<T>()->GetUnit(go);
		}
		
	};

	void RegisterGameObject(uint32_t go) {
		//Check there is no gameobejc with this identity already
		for (auto g : mGameObjects) {
			if (go == g) {
				return;
			}
		}
		mGameObjects.push_back(go);
		std::cout << "Registry : RegisterGameObject the GameObject " << go << " was added to mGameObjects" << std::endl;
	}

	//Adding a component must also have a entity
	template<typename T>
	void AddComponent(uint32_t objectID, T& component) {
		GetUnitHolder<T>()->Insert(objectID, component);
	}

	//If the gameobject has this type of component, return it
	template<typename T>
	std::shared_ptr<T> GetComponent(uint32_t objectID){
		//Has has been called on this so we know we can return the unit holder
		return GetUnitHolder<T>()->GetUnit(objectID);
	}

	//This should return all components of type T
	template<typename T>
	std::vector<std::shared_ptr<T>> GetComponents() {
		return GetUnitHolder<T>()->GetAllUnits();
	}

	//template<typename T>
	//std::vector<T> GetComponents(uint32_t objectID) {
	//	//Return all components from this item
	//	const char* typeName = typeid(T).name();
	//	std::cout << "Registry : GetComponents<T>(objectID) type " << typeName << std::endl;
	//
	//	//Find if theres is an array of this item
	//	if (mComponentsHolder.find(typeName) == mComponentsHolder.end()) {
	//		//There is no unit holder with this Type of Component
	//		std::cout << "Regsitry : GetComponents<" << typeName << ">(" << objectID << ") there is no array of this kind" << std::endl;
	//		return std::vector<T>{};
	//	}
	//	auto t = GetComponents<T>;
	//	std::vector<T> units;
	//	for (int i = 0; i < t.size(); i++)
	//	{
	//		if (t.mGO == objectID) {
	//			units.push_back(units[i]);
	//		}
	//	}
	//	return units;
	//}

	//Gets all the gameobjects
	std::vector<GameObject> GetGameObjects() {
		return mGameObjects;
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
	bool Has(uint32_t objectID)
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
	
private:
	//We want a unorerd map which holds the string for which type has come in
	// when that type is stored, 
	//I want a map which holds component types, these types each has a map with actual component refrences	
	//GameObjects
	std::vector<GameObject> mGameObjects;

	//Components
	//This holds a string which is the type of the component to a string, 
	//IUnitHolder is a virtual interface, subclass is only a container of a specific type
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

