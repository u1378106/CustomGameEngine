#pragma once

#include <map>
#include "SmartPtr.h"
#include "MyGameObject.h"

class MasterList
{	

public:
	static std::map<int, SmartPtr<MyGameObject>> masterMap;
	static void UpdateMasterList(int gameObjectId, SmartPtr<MyGameObject> go);
	static SmartPtr<MyGameObject> GetObjectFromMasterMap(int index);
	static SmartPtr<MyGameObject> GetObjectFromMasterMap(string goName);
};

