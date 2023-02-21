#pragma once

#include <vector>
#include "MyGameObject.h"
#include "GLib.h"
#include "Player.h"
#include "SmartPtr.h"

const int monsterNumber = 2;

int MonsterPositionX[4];
int MonsterPositionY[4];

Engine::Point2D playerPos;

std::vector<SmartPtr<MyGameObject>> demons;
SmartPtr<MyGameObject> playerObject;
SmartPtr<MyGameObject> finishObject;

GLib::Sprite* demon;
GLib::Sprite* player;
GLib::Sprite* finish;
GLib::Sprite* gameover;
GLib::Sprite* winner;

//Interval interval;

void InitializePlayer();

void InitializeGoal();

void InitializeDemons(int demonCount);

void DrawGameObjects();

void UpdateDemons();

void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown);

void LoadGameobjectsFromJson(const std::string& i_JSONfileName);