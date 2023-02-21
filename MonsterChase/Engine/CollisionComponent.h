#pragma once
#include <json.hpp>

class CollisionComponent
{
private:
	Engine::Point2D extent = { 0, 0 };
	Engine::Point2D center = { 0, 0 };

public:
	static CollisionComponent* createFromJson(nlohmann::json collisionJson) {
		auto component = new CollisionComponent();
		auto extent = collisionJson.at("extent");
		component->extent = Engine::Point2D(extent[0], extent[1]);

		auto center = collisionJson.at("center");
		component->center = Engine::Point2D(center[0], center[1]);

		return component;
	}

	Engine::Point2D getExtent()
	{
		return extent;
	}

	Engine::Point2D getCenter()
	{
		return center;
	}
};
