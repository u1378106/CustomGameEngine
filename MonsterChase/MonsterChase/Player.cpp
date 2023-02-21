#include "Player.h"
#include "MyGameObject.h"


Player::Player(Engine::Point2D& velocity, Engine::Point2D& position, string name)
{
	setVelocity(velocity);
	setPosition(position);
	setName(name);
}
