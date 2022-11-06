#include "Components.h"

Component::Component(GameObject* parent)
{
	mParent = parent;
}

Component::~Component()
{
}

void Component::Init()
{
}

void Component::OnUpdate(float ts)
{
}
