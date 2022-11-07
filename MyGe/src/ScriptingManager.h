#pragma once

#include <vector>

class ScriptingManager
{
public:
	ScriptingManager();
	void Init();
private:
	std::vector<class Script&> mScripts;

};
