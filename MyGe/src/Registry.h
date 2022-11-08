#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include "Shader.h"
#include "Components.h"

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

	template<typename T>
	void Insert(int id, T t) {
		mUnits.insert({id, t});
		std::cout << "UnitHolder : Added unit" << std::endl;
	};

	void Pop(int id) {
		mUnits.erase(id);
		std::cout << "UnitHolder : Ereased unit" << std::endl;
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

	//This should add whatever is sent to the registry
	template<class T>
	void Register(const T item) {
		//Turns the type into a string
		const char* typeName = typeid(T).name();
		//If all types already contains something on this key, the class has already been registered
		//if (mAllTypes.find(typeName)) {
		//	//This type was already found, no need to re-register it
		//	return;
		//}
		
	}

	//Always returns a new not in-use ID
	static const int GetNewID() {
		return Registry::Instance().mID++;
	}

	//Tell the registry this component type exists
	template<typename T>
	void RegisterComponent() {
		//We know we want to register
		const char* typeName = typeid(T).name();
		if (mComponentTypes.find(typeName)) {
			//If the components is already registered, return
			return;
		}
		//Register it by inserting it into mComponentTypes
		mComponentTypes.insert({ typeName, GetNewID() });
		mComponents.insert({ typeName, UnitHolder<T>() });
		std::cout << "Registry : Regsitered a new component";
	};

	template<typename T>
	void RegisterGameObject(T object, int id) {
		const char* typeName = typeid(T).name();
		if (mGameObjects.find(id)) {
			//This id is already registered
			return;
		}
		
		mGameObjects.insert({ id, object });
	}

	//Adding a component must also have a entity
	template<typename T>
	void AddComponent(int objectID, T component) {
		//We know we want to register
		GetUnitHolder<T>().Insert(objectID, component);
	}
	
	template<typename T>
	T& GetComponent(int id) {

	}
	template<typename T>
	int GetComponentType() {
		const char* typeName = typeid(T).name();


		return mComponentTypes[typeName];
	}
private:
	//We want a unorerd map which holds the string for which type has come in
	// when that type is stored, 
	//I want a map which holds component types, these types each has a map with actual component refrences	
 	//GameObjects
	std::unordered_map<int, int> mGameObjects;

	//Components
	//This holds a string which is the type of the component to a string, 
	//IUnitHolder is a virtual interface, subclass is only a container of a specific type
	std::unordered_map < const char*, std::shared_ptr<IUnitHolder>> mComponents;
	std::unordered_map<const char*, int> mComponentTypes;

	//Static instance of this regisrty
	Registry* mInstance;

	int mID;

	template<typename T>
	std::shared_ptr<UnitHolder<T>> GetUnitHolder() {
		//Gets the type of the component
		const char* typeName = typeid(T).name();
		
		if (1) {
			//No component of this type found 
			//return std::static_pointer_cast<UnitHolder<T>>(mComponents[typeName]);
		}
		//This returns correct array of components for the type
		//typeName is the type of the component
		//Casting a IComponentHolder to a ComponentHolder, casts down from IComponent to Component
		//return std::static_pointer_cast<UnitHolder<T>>(mComponents[typeName]);
		return std::static_pointer_cast<UnitHolder<T>>(mComponents[typeName]);
	}
};

