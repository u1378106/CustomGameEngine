#pragma once
#include "Math/Point2D.h"
#include <json.hpp>

class PhysicsComponent
{
private:
	Engine::Point2D accl = { 0, 0 };
	Engine::Point2D force = { 0, 0 };
	float mass = 1;
	float kDrag = 0.001f;

public:
	static PhysicsComponent* createFromJson(nlohmann::json physicsJson) {

		auto component = new PhysicsComponent();
		auto mass = physicsJson.at("mass");
		component->mass = mass;

		auto kDrag = physicsJson.at("kDrag");
		component->kDrag = kDrag;

		return component;
	}

	Engine::Point2D getAccl()
	{
		return accl;
	}

	void SetAccl(Engine::Point2D a)
	{
		accl = a;
	}

	Engine::Point2D getForce()
	{
		return force;
	}

	void SetForce(Engine::Point2D f)
	{
		force = f;
	}

	float getMass()
	{
		return mass;
	}

	void setMass(float m)
	{
		mass = m;
	}

	float getKdrag()
	{
		return kDrag;
	}

	void setKdrag(float k)
	{
		kDrag = k;
	}

};
