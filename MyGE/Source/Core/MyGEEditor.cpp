#include "pch.h"
#include "MyGEEditor.h"

#include "MyGEMode.h"
#include "../Scenes/Scene.h"
void MyGEEditor::Init()
{
}

void MyGEEditor::OnUpdate(float deltaTime)
{
}

bool MyGEEditor::LoadScene(std::string fileName)
{
	return false;
}

void MyGEEditor::StartPlay()
{
}

void MyGEEditor::StopPlay()
{
}

std::shared_ptr<Scene> MyGEEditor::GetScene()
{
	return std::shared_ptr<Scene>();
}
