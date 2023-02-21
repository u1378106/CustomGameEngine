#include "JsonManager.h"
#include "PhysicsComponent.h";
#include "CollisionComponent.h"

std::vector<uint8_t> LoadFile(const std::string& fileName)
{

	if (!fileName.empty())
	{
		FILE* pFile = nullptr;

		errno_t fopenError = fopen_s(&pFile, fileName.c_str(), "rb");
		if (fopenError == 0)
		{
			assert(pFile != nullptr);

			int FileIOError = fseek(pFile, 0, SEEK_END);
			assert(FileIOError == 0);

			long FileSize = ftell(pFile);
			assert(FileSize > 0);

			FileIOError = fseek(pFile, 0, SEEK_SET);
			assert(FileIOError == 0);

			Contents.reserve(FileSize);
			Contents.resize(FileSize);

			size_t FileRead = fread(&Contents[0], 1, FileSize, pFile);
			assert(FileRead == FileSize);

			fclose(pFile);
		}
	}
	return Contents;
}

SmartPtr<MyGameObject> CreateGameobject(nlohmann::json& goJson)
{

	if (goJson.contains("name"))
	{
		nlohmann::json Name = goJson.at("name");
		assert(Name.is_string());

		goName = Name;
	}

	if (goJson.contains("tag"))
	{
		nlohmann::json Tag = goJson.at("tag");
		assert(Tag.is_string());

		goTag = Tag;
	}

	if (goJson.contains("initial_position"))
	{

		nlohmann::json Position = goJson.at("initial_position");
		assert(Position.is_array());
		assert(Position.size() == 2);
		assert(Position[0].is_number() && Position[1].is_number());

		goPos = Engine::Point2D(Position[0], Position[1]);
	}

	if (goJson.contains("initial_velocity"))
	{

		nlohmann::json Velocity = goJson.at("initial_velocity");
		assert(Velocity.is_array());
		assert(Velocity.size() == 2);
		assert(Velocity[0].is_number() && Velocity[1].is_number());

		goVel = Engine::Point2D(Velocity[0], Velocity[1]);
	}

	
		SmartPtr<MyGameObject> NewGameObject = MyGameObject::CreateMyGameObject(goVel, goPos, goName, goTag);
				

	if (goJson.contains("components"))
	{
		assert(goJson["components"].is_object());

		for (nlohmann::json::iterator it = goJson["components"].begin(); it != goJson["components"].end(); ++it)
		{
			if (it.key() == "physics")
			{
				PhysicsComponent* pc = PhysicsComponent::createFromJson((*it));
				NewGameObject->RegisterPhysics(pc);
			}

			if (it.key() == "collision")
			{
				CollisionComponent* collisionComponent = CollisionComponent::createFromJson((*it));
				NewGameObject->RegisterCollision(collisionComponent);
			}
		}
	}
	return NewGameObject;
}

void LoadGameobjectsFromJson(const std::string& i_JSONfileName)
{
	

	Engine::JobSystem::Init();

	Engine::JobSystem::JobStatus JobStatus;

	Engine::JobSystem::RunJob(
		Engine::JobSystem::GetDefaultQueueName(),
		[&]()
		{
			std::vector<uint8_t> Contents = LoadFile(i_JSONfileName);
			if (!Contents.empty())
			{
				nlohmann::json JSON = nlohmann::json::parse(Contents);

				auto gameObjects = JSON["gameobjects"];
				auto player = gameObjects["player"];
				auto goal = gameObjects["Goal"];
				auto monsters = gameObjects["monsters"];

				
						CreateGameobject(player);
						CreateGameobject(goal);
						for (auto monster : monsters)
						{
							CreateGameobject(monster);
						}


			}
		}, &JobStatus);


	

	JobStatus.WaitForZeroJobsLeft();

	Engine::JobSystem::RequestShutdown();
}
