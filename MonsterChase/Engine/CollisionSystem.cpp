#include "CollisionSystem.h"
#include"Log.h"

std::map<int, CollisionComponent*> CollisionSystem::collisionMap;
bool seperationX, seperationY;
bool isGameOver = 0;
bool isWinner = 0;

Matrix4 CollisionSystem::ObjecttoWorld(SmartPtr<MyGameObject> go)
{
    Matrix4 translationMatrix = Matrix4::MakeTranslate(Vector3(go->getPosition().X(), go->getPosition().Y(), 1));
    Matrix4 rotation = Matrix4::Identity;

    Matrix4 result = translationMatrix * rotation;

    return result;
}

Matrix4 CollisionSystem::WorldtoObject(SmartPtr<MyGameObject> go)
{
    Matrix4 inverse = Matrix4::Inverse(ObjecttoWorld(go));

    return inverse;
}

//Separation Check
bool CollisionSystem::Separation(SmartPtr<MyGameObject> goA, SmartPtr<MyGameObject> goB, CollisionComponent* collisionCompA, CollisionComponent* collisionCompB)
{
    
    Matrix4 worldtoObj2 = Matrix4::Inverse(ObjecttoWorld(goB)); //World to object Matrix calculation for Object 2
    Matrix4 worldtoObj1 = Matrix4::Inverse(ObjecttoWorld(goA)); //World to object Matrix calculation for Object 1

    Matrix4 obj1toobj2 = worldtoObj2 * ObjecttoWorld(goA); //Object2 relative to Object1
    Matrix4 obj2toobj1 = worldtoObj1 * ObjecttoWorld(goB); //Object1 relative to Object2

    Vector4 obj1BBCenterinObj2 = obj1toobj2 * Vector4(collisionCompA->getCenter().X(), collisionCompA->getCenter().Y(), 0, 1); //Object1 Bounding Box Center in Object2 in terms of X axis
    Vector4 obj2BBCenterinObj1 = obj1toobj2 * Vector4(collisionCompA->getCenter().X(), collisionCompA->getCenter().Y(), 0, 1); //Object2 Bounding Box Center in Object1 in terms of X axis

    Vector4 obj1ExtentXinObj2 = obj1toobj2 * Vector4(collisionCompA->getExtent().X(), collisionCompA->getExtent().Y(), 0, 0); //Object1 Extent of X in Object2
    Vector4 obj1ExtentYinObj2 = obj1toobj2 * Vector4(collisionCompA->getExtent().X(), collisionCompA->getExtent().Y(), 0, 0); //Object1 Extent of Y in Object2

    Vector4 obj2ExtentXinObj1 = obj2toobj1 * Vector4(collisionCompA->getExtent().X(), collisionCompA->getExtent().Y(), 0, 0); //Object2 Extent of X in Object1
    Vector4 obj2ExtentYinObj1 = obj2toobj1 * Vector4(collisionCompA->getExtent().X(), collisionCompA->getExtent().Y(), 0, 0); //Object2 Extent of Y in Object1

    float temp1X = fabs(obj1BBCenterinObj2.x - 0);
    float temp1Y = fabs(obj1BBCenterinObj2.y - 50);

    seperationX = temp1X > fabs(obj1ExtentXinObj2.x + collisionCompB->getExtent().X()); // Seperation around X axis
    seperationY = temp1Y > fabs(obj1ExtentYinObj2.y + collisionCompB->getExtent().Y()); // Separation around Y axis


    float velXDiff = goA->getVelocity().X() - goB->getVelocity().X(); // Difference in velocity for X axis
    float velYDiff = goA->getVelocity().Y() - goB->getVelocity().Y(); // Difference in velocity for Y axis

    //relative velocity
    Vector3 relativeVel = Vector3(velXDiff, velYDiff, 0);
    float mag = relativeVel.GetLength();

    //object relative velocity
    Vector4 Obj1VelRelToObj2InObj2 = worldtoObj2 * Vector4(relativeVel.Normalize(), 0.0f);
    Obj1VelRelToObj2InObj2 *= mag;

    Vector4 Obj2VelRelToObj1InObj1 = worldtoObj1 * Vector4(relativeVel.Normalize(), 0.0f);
    Obj2VelRelToObj1InObj1 *= mag;

    //Left and Right Calculation for Obj1 in terms of Obj2
    float Object1projtoObject2_X = fabs(obj1ExtentXinObj2.x) + fabs(obj1ExtentYinObj2.x);
    float Obj1CenterX = obj1BBCenterinObj2.x;
    float Obj2ExtentX = collisionCompB->getExtent().X() + Object1projtoObject2_X;

    float Obj2Left = collisionCompB->getCenter().X() - Obj2ExtentX;
    float Obj2Right = collisionCompB->getCenter().X() + Obj2ExtentX;

    //Up and Down Calculation for Obj1 in terms of Obj2
    float Object1projtoObject2_Y = fabs(obj1ExtentXinObj2.y) + fabs(obj1ExtentYinObj2.y);
    float Obj1CenterY = obj1BBCenterinObj2.y;
    float Obj2ExtentY = collisionCompB->getExtent().Y() + Object1projtoObject2_Y;

    float Obj2Up = collisionCompB->getCenter().Y() + Obj2ExtentY;
    float Obj2Down = collisionCompB->getCenter().Y() - Obj2ExtentY;

    //Left and Right Calculation for Obj2 in terms of Obj1
    float Object2projtoObject1_X = fabs(obj2ExtentXinObj1.x) + fabs(obj2ExtentYinObj1.x);
    float Obj2CenterX = obj2BBCenterinObj1.x;
    float Obj1ExtentX = collisionCompA->getExtent().X() + Object2projtoObject1_X;

    float Obj1Left = collisionCompA->getCenter().X() - Obj1ExtentX;
    float Obj1Right = collisionCompA->getCenter().X() + Obj1ExtentX;

    //Up and Down Calculation for Obj2 in terms of Obj1
    float Object2projtoObject1_Y = fabs(obj2ExtentXinObj1.y) + fabs(obj2ExtentYinObj1.y);
    float Obj2CenterY = obj2BBCenterinObj1.y;
    float Obj1ExtentY = collisionCompA->getExtent().Y() + Object2projtoObject1_Y;

    float Obj1Up = collisionCompA->getCenter().Y() + Obj1ExtentY;
    float Obj1Down = collisionCompA->getCenter().Y() - Obj1ExtentY;

    Vector4 Object1BBCenterInObject2 = obj1toobj2 * Vector4(collisionCompA->getCenter().X(), collisionCompA->getCenter().Y(), 0, 0); //Object1 Bounding Box Center in Object2 in terms of Y axis
    Vector4 Object2BBCenterInObject1 = obj2toobj1 * Vector4(collisionCompB->getCenter().X(), collisionCompB->getCenter().Y(), 0, 0); //Object2 Bounding Box Center in Object1 in terms of Y axis

    float dLeftB = Obj2Left - Obj1CenterX;
    float dRightB = Obj2Right - Obj1CenterX;

    float dUpB = Obj2Up - Obj1CenterY;
    float dDownB = Obj2Down - Obj1CenterY;

    float dLeftA = Obj2Left - Obj1CenterX;
    float dRightA = Obj2Right - Obj1CenterX;

    float dUpA = Obj2Up - Obj1CenterY;
    float dDownA = Obj2Down - Obj1CenterY;

    float tLeft = 0;
    float tRight = gameTime; // time factor

    if (Obj1VelRelToObj2InObj2.x == 0) {
        if (Obj1CenterX < Obj2Left || Obj1CenterX > Obj2Right)
        {
            Engine::Log::I("Sepearation exists 1....");
            return false;
        }
    }
    else
    {
        float leftCal = dLeftB / Obj1VelRelToObj2InObj2.x;
        float rightCal = dRightB / Obj1VelRelToObj2InObj2.x;

        if (leftCal > rightCal)
            swap(rightCal, leftCal);

        tLeft = max(tLeft, leftCal);
        tRight = min(tRight, rightCal);
    }

    if (Obj1VelRelToObj2InObj2.y == 0)
    {
        if (Obj1CenterY < Obj2Down || Obj1CenterY > Obj2Up)
        {
            Engine::Log::I("Sepearation exists 2....");
            return false;
        }
    }
    else
    {
        float upCal = dUpB / Obj1VelRelToObj2InObj2.y;
        float downCal = dDownB / Obj1VelRelToObj2InObj2.y;

        if (downCal > upCal)
            swap(upCal, downCal);

        tLeft = max(tLeft, downCal);
        tRight = min(tRight, upCal);
    }




    if (Obj2VelRelToObj1InObj1.x == 0)
    {
        if (Obj2CenterX < Obj1Left || Obj2CenterX > Obj1Right)
        {
            Engine::Log::I("Sepearation exists 3....");
            return false;
        }
    }
    else
    {
        float leftCal = dLeftA / Obj2VelRelToObj1InObj1.x;
        float rightCal = dRightA / Obj2VelRelToObj1InObj1.x;

        if (leftCal > rightCal)
            swap(rightCal, leftCal);

        tLeft = max(tLeft, leftCal);
        tRight = min(tRight, rightCal);
    }

    if (Obj2VelRelToObj1InObj1.y == 0)
    {
        if (Obj2CenterY < Obj1Down || Obj2CenterY > Obj1Up)
        {
            Engine::Log::I("Sepearation exists 4....");
            return false;
        }
    }
    else
    {
        float upCal = dUpA / Obj2VelRelToObj1InObj1.y;
        float downCal = dDownA / Obj2VelRelToObj1InObj1.y;

        if (downCal > upCal)
            swap(upCal, downCal);

        tLeft = max(tLeft, downCal);
        tRight = min(tRight, upCal);
    }

    if (tRight <= 0 || tLeft >= gameTime)

        return false;

    return tLeft < tRight;
}

//Update function for Collision System to check for any collision occurence
void CollisionSystem::Update()
{
    for (auto i = collisionMap.begin(); i != collisionMap.end(); i++)
    {
        if(!isGameOver || isWinner)
        { 
        SmartPtr<MyGameObject> goA = MasterList::masterMap[(*i).first];
        CollisionComponent* collisionCompA = (*i).second;
        for (auto j = std::next(i); j != collisionMap.end(); j++)
        {
            SmartPtr<MyGameObject> goB = MasterList::masterMap[(*j).first];
            CollisionComponent* collisionCompB = (*j).second;
            if (goA->getTag() == "player" && goB->getTag() == "enemy")
            {
                bool collisionStatus = Separation(goA, goB, collisionCompA, collisionCompB);
                if (!isGameOver && collisionStatus)
                {
                    isGameOver = true;
                    Engine::Log::I("collision occured : " + std::to_string(collisionStatus));
                    /*break;*/
                }
            }
            else if (goA->getTag() == "player" && goB->getTag() == "goal")
            {
                bool collisionStatus = Separation(goA, goB, collisionCompA, collisionCompB);
                if (!isWinner && collisionStatus)
                {
                    isWinner = true;
                    Engine::Log::I("Game Won : " + std::to_string(collisionStatus));
                }
            }
        }
    }
    }
}

void CollisionSystem::RegisterCollision(int gameObjectId, CollisionComponent* collisionComponent)
{
    //collisionMap.empty(); empty map when required
    collisionMap.insert({ gameObjectId, collisionComponent });
}

CollisionComponent* CollisionSystem::GetComponent(int id)
{
    return collisionMap[id];
}
