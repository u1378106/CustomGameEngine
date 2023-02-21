#pragma once

#include "json.hpp"
#include "SmartPtr.h"
#include "MyGameObject.h"
#include <vector>

#include "JobSystem/JobSystem.h";
#include "Syncronization/Events.h";
#include "HashedString/HashedString.h";
//#include "Syncronization/ScopeLock.h";
//#include "Syncronization/Mutex.h";
#include <iostream>


Engine::Point2D goPos;
Engine::Point2D goVel;
string goName;
string goTag;
std::vector<uint8_t> Contents;
std::vector<uint8_t> LoadFile(const std::string& fileName);
SmartPtr<MyGameObject> CreateGameobject(nlohmann::json& goJson);

std::map<int, SmartPtr<MyGameObject>> tempMasterMap;
//Engine::Mutex NewGameObjectMutex;

// Public - being used in the Game
void LoadGameobjectsFromJson(const std::string& i_JSONfileName);