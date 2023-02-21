#pragma once
#include "Math/Point2D.h"
#include "MyGameObject.h"

class Demon : public MyGameObject
{
public:
	Demon();
	Demon(Engine::Point2D& velocity, Engine::Point2D& position, const string name);
};
