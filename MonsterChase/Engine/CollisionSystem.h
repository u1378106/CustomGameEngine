#include "Math/Point2D.h"
#include "Matrix4.h"
#include "MasterList.h"
#include "Timer.h"
#include <json.hpp>
#include "CollisionComponent.h"

extern bool isGameOver;
extern bool isWinner;

#pragma once
class CollisionSystem
{
private:
	static std::map<int, CollisionComponent*> collisionMap;

public:
	static void Update();
	static void RegisterCollision(int gameObjectId, CollisionComponent* collisionComponent);
	static CollisionComponent* GetComponent(int id);

	static Matrix4 ObjecttoWorld(SmartPtr<MyGameObject> go);

	static Matrix4 WorldtoObject(SmartPtr<MyGameObject> go);

	static bool Separation(SmartPtr<MyGameObject> goA, SmartPtr<MyGameObject> goB, CollisionComponent* collisionCompA, CollisionComponent* collisionCompB);
};