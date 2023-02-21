#include <stdio.h>
#include "Math/Point2D.h"
#include <string>
#include "MyGameObject.h"
#include "Timer.h"
#include "windows.h"
#include "PhysicsSystem.h"
#include "CollisionSystem.h"
#include "MasterList.h"

int MyGameObject::_counter = 0;

MyGameObject::MyGameObject()
{
	id = ++_counter;
	MasterList::UpdateMasterList(id, this);
	
}

void MyGameObject::RegisterPhysics(PhysicsComponent* pc)
{
	PS::RegisterPhysics(id, pc);
}

void MyGameObject::RegisterCollision(CollisionComponent* collisionComponent)
{
	CollisionSystem::RegisterCollision(id, collisionComponent);
}

MyGameObject::MyGameObject(Engine::Point2D& velocity, Engine::Point2D& position, string name, string tag): MyGameObject()
{
	setVelocity(velocity);
	setPosition(position);
	setName(name);
	setTag(tag);
}


SmartPtr<MyGameObject> MyGameObject::CreateMyGameObject(Engine::Point2D& velocity, Engine::Point2D& position, string name, string tag)
{
	auto go = new MyGameObject(velocity, position, name, tag);
	return MasterList::masterMap[go->id];
}


void MyGameObject::MyUpdate()
{
	_position = _position + velocity;
}


