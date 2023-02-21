#include "Demon.h"
#include "MyGameObject.h"

Demon::Demon()
{

}

Demon::Demon(Engine::Point2D& velocity, Engine::Point2D& position, string name)
{
	setVelocity(velocity);
	setPosition(position);
	setName(name);
}
