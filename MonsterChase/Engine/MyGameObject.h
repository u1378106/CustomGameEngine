#pragma once
#include "Math/Point2D.h"
#include <string>
#include "SmartPtr.h"


class PhysicsComponent;
class CollisionComponent;
using namespace std;
class MyGameObject
{
private:
	static int _counter;

public:
	MyGameObject();
	MyGameObject(Engine::Point2D& velocity, Engine::Point2D& position, string name, string tag);
	void RegisterPhysics(PhysicsComponent* pc);
	void RegisterCollision(CollisionComponent* collisionComponent);
	static SmartPtr<MyGameObject> CreateMyGameObject(Engine::Point2D& velocity, Engine::Point2D& position, string name, string tag);
	

	Engine::Point2D getVelocity()
	{
		return velocity;
	}

	Engine::Point2D getPosition()
	{
		return _position;
	}

	string getName()
	{
		return _name;
	}

	string getTag()
	{
		return _tag;
	}

	int getId()
	{
		return id;
	}

	void setVelocity(Engine::Point2D v)
	{
		velocity = v;
	}

	void setPosition(Engine::Point2D p)
	{
		_position = p;
	}
	void setName(string n)
	{
		_name = n;
	}

	void setTag(string tag)
	{
		_tag = tag;
	}

	void MyUpdate();

protected:
	Engine::Point2D velocity;
	Engine::Point2D _position;
	string _name;
	string _tag;
	int id;
};
