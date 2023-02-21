#pragma once
#include "MyGameObject.h"

class Player : public MyGameObject
{
public:
	Player() = default;
	Player(Engine::Point2D& velocity, Engine::Point2D& position, string name);
};
