#include "PhysicsSystem.h"
#include "Timer.h"
#include "Windows.h"
#include "MasterList.h"

std::map<int, PhysicsComponent*> PS::physicsRegistryMap;


//Calculating physics calculation based on Verlet variation
void PS::Update()
{
	    for (auto i = physicsRegistryMap.begin(); i != physicsRegistryMap.end(); i++)
		{
			SmartPtr<MyGameObject> go = MasterList::masterMap[(*i).first];
			PhysicsComponent* pc = (*i).second;
					
				auto pos = go->getPosition();
				auto vel = go->getVelocity();

				auto accl = pc->getForce() / pc->getMass();
				Engine::Point2D tempVel = { vel.X() + (accl.X() * (gameTime / 2))  , vel.Y() + (accl.Y() * (gameTime / 2)) };
				pos = { pos.X() + (tempVel.X() * (gameTime)), pos.Y() + (tempVel.Y() * (gameTime)) };
				
				vel = { tempVel.X() + (accl.X() * (gameTime / 2)), tempVel.Y() + (accl.Y() * (gameTime / 2)) };
				vel = { (vel.X() * (1 - (*i).second->getKdrag() * gameTime)), (vel.Y() * (1 - (*i).second->getKdrag() * gameTime)) }; // friction coefficient

				//Check if enemy
				if (go->getTag() == "enemy")
				{
					if (go->getPosition().Y() >= 245.0) // Up position bound for enemy movement
					{
						vel = { 0, -0.50 };
					}
					if (go->getPosition().Y() <= -245.0) // Down position bound for enemy movement
					{
						vel = { 0, 0.50 };
					}
				}

				MasterList::masterMap[(*i).first]->setPosition(pos);
				MasterList::masterMap[(*i).first]->setVelocity(vel);
			
		}
}

void PS::RegisterPhysics(int gameObjectId, PhysicsComponent* physicsComponent)
{
	//registryMap.empty(); empty map when required
	physicsRegistryMap.insert({ gameObjectId, physicsComponent});
}

PhysicsComponent* PS::getComponent(int id)
{
	return physicsRegistryMap[id];
}
