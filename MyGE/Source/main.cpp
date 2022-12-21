#include "pch.h"
#include "Core/MyGE.h"

int main() {
	std::unique_ptr<MyGE> myGe = std::make_unique<MyGE>();
	return myGe->Run();
}