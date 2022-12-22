#pragma once
class MyGEMode {
public:
	MyGEMode();
	~MyGEMode();
	virtual void Init() = 0;

	virtual void OnUpdate(float deltaTime) = 0;

private:

protected:
	std::shared_ptr<class Scene> mActiveScene;
	std::shared_ptr<class MyGEEditor> mEditor;
	std::shared_ptr<class MyGERuntime> mRuntime;

	//The systems the modes is using,
	//Should maybe be a vector instead
	std::unordered_map<const char*, std::shared_ptr<class System>> mSystems;

	//We can have different scenes and orderes we want to load them in
	//since we dont serialize scenes or asset yet, I use subclasses of the scene class
	//This will replaced by a file name or scene name or something like that
	
};