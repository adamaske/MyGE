#pragma once
#include <stdint.h>
#include <iostream>
static class Renderer* mRendererInstance;

class Renderer {
	
public:
	static int ID() { 
		int id = RendererInstance().GetID();
		std::cout << "Renderer returning ID " << id << std::endl;
		return	id;
	};

	int GetID() {
		mIDs++;
		return mIDs;
	}

	//Instance 
	static	Renderer& RendererInstance() {
		if (mRendererInstance == nullptr) {
			mRendererInstance = new Renderer();
		}
		return *mRendererInstance;
	}


private:
	int mIDs = 0;
	int mRednererID = 0;
};
