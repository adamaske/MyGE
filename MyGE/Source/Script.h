#pragma once
#include <iostream>
#include <string>
class Script
{
public:
	Script(int id, std::string fileName) {
		mID = id;
	}
	int ScriptID() { return mID; };

private:
	int mID;
};

