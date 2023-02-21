#pragma once
#include "Math/Point2D.h"
#include "MyGameObject.h"
#include <map>
#include "PhysicsComponent.h"


class PS 
{
private:
	static std::map<int, PhysicsComponent*> physicsRegistryMap;

public:
	static void Update();
	static void RegisterPhysics(int gameObjectId, PhysicsComponent* physicsComp);
	static PhysicsComponent* getComponent(int id);
};
