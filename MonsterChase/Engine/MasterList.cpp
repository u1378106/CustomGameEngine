#include "MasterList.h"
#include "Windows.h"

std::map<int, SmartPtr<MyGameObject>> MasterList::masterMap = std::map<int, SmartPtr<MyGameObject>>();

void MasterList::UpdateMasterList(int gameObjectId, SmartPtr<MyGameObject> go)
{
	char ml_buffer[100];

	//masterMap.empty(); // empty map when required

	masterMap.insert({ gameObjectId, SmartPtr<MyGameObject>(go) });

	sprintf_s(ml_buffer, "count is %d\t", masterMap.size());
	OutputDebugStringA(ml_buffer);
}

SmartPtr<MyGameObject> MasterList::GetObjectFromMasterMap(int goId)
{
	return masterMap[goId];
}

SmartPtr<MyGameObject> MasterList::GetObjectFromMasterMap(string goName)
{
	for (auto i = masterMap.begin(); i != masterMap.end(); i++)
	{
		
		//if ((*i).second->getName() == goName)
		if ((*i).second->getName().find(goName) != string::npos)
			return (*i).second;
	}
}
