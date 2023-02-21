#include<iostream>

#include<string.h>

#include "DemonHunter.h"

#include "Initialization.h"

#include "Math/Point2D.h"

#include "Demon.h"

#include "Player.h"

#include "GLib.h"

#include <DirectXColors.h>

#include "Timer.h"

#include "PhysicsSystem.h"

#include"MasterList.h"

#include "Matrix4Test.h"

#include "CollisionSystem.h"

bool isQuit = false;

int RunDemonHunter()
{
    Engine::Initialize();
    InitializePlayer();
    InitializeGoal();
    InitializeDemons(monsterNumber);
   
    GLib::SetKeyStateChangeCallback(TestKeyCallback);
    Timer t;
    t.Init();
    CollisionSystem CollisionSystem;
 
    while (!isQuit)
    {        
        DrawGameObjects();
        t.TimeDiff();

        PS::Update();
        CollisionSystem.Update();     
    }
    
    //GLib::Shutdown();   

    return 0;
}


void InitializePlayer()
{      
        LoadGameobjectsFromJson("data\\GameObjects.json");
        playerObject = MasterList::GetObjectFromMasterMap("Player");
        Matrix4Test mat4;
        mat4.StartTest();
}

void InitializeGoal()
{
    LoadGameobjectsFromJson("data\\GameObjects.json");
    finishObject = MasterList::GetObjectFromMasterMap("finish");
}

void InitializeDemons(int demonCount)
{   
    //Load all monsters
        SmartPtr<MyGameObject> demon1 = MasterList::GetObjectFromMasterMap("monster1");
        SmartPtr<MyGameObject> demon2 = MasterList::GetObjectFromMasterMap("monster2");
        SmartPtr<MyGameObject> demon3 = MasterList::GetObjectFromMasterMap("monster3");
        demons.push_back(demon1);
        demons.push_back(demon2);
        demons.push_back(demon3);
}

void DrawGameObjects()
{
    bool bQuit = false;
    // IMPORTANT: We need to let GLib do it's thing. 
    GLib::Service(bQuit);

               
    // IMPORTANT: Tell GLib that we want to start rendering
    GLib::BeginRendering(DirectX::Colors::AliceBlue);
    // Tell GLib that we want to render some sprites
    GLib::Sprites::BeginRendering();

    GLib::Point2D	Offset = { 0, 0 };

    Offset.x += playerObject->getPosition().X();
    Offset.y += playerObject->getPosition().Y();

    // Tell GLib to render this sprite at our calculated location
    GLib::Render(*player, Offset, 0.0f, 0.0f);
    

    GLib::Point2D	FinishOffset = { 0, 0 };
    FinishOffset.x += finishObject->getPosition().X();
    FinishOffset.y += finishObject->getPosition().Y();
    // Tell GLib to render this sprite at our calculated location
    GLib::Render(*finish, FinishOffset, 0.0f, 0.0f);

    for (unsigned int i = 0; i < demons.size(); i++)
    {
        GLib::Point2D	Offset = { 0, 0 };

        Offset.x += demons[i]->getPosition().X();
        Offset.y += demons[i]->getPosition().Y();

        // Tell GLib to render this sprite at our calculated location
        GLib::Render(*demon, Offset, 0.0f, 0.0f);
    }       

    //Render Game-Over screen if the condition is true for isGameOver
    if (isGameOver)
    {
        GLib::Point2D	GameOverOffset = { 0, -200 };
        GLib::Render(*gameover, GameOverOffset, 0.0f, 0.0f);
    }

    //Render Win screen if the condition is true for isWinner
    if (isWinner)
    {
        GLib::Point2D	WinnerOffset = { 0, -250 };
        GLib::Render(*winner, WinnerOffset, 0.0f, 0.0f);
    }
    // 
    // Tell GLib we're done rendering sprites
    GLib::Sprites::EndRendering();
    // IMPORTANT: Tell GLib we're done rendering
    GLib::EndRendering();     
}

void UpdateDemons()
{   
    for (unsigned int monsterIndex = 0; monsterIndex < demons.size(); monsterIndex++)
    {
        if (playerPos == demons[monsterIndex]->getPosition())
        {
            break;
        }
    }
}

//Move player using key input and button press status
void MovePlayer(unsigned int keyID, bool isPressed)
{
    using namespace Engine;
    Point2D force = PS::getComponent(playerObject->getId())->getForce();

    if (keyID == 0x0057 && isPressed)
    {
        OutputDebugStringA("W pressed");
        force += Point2D(0, 0.00009f);
    }
    if (keyID == 0x0057 && !isPressed)
    {
        OutputDebugStringA("W released");
        force -= Point2D(0, 0.00009f);
    }
    if (keyID == 0x0053 && isPressed)
    {
        OutputDebugStringA("S pressed");
        force += Point2D(0, -0.00009f);
    }
    if (keyID == 0x0053 && !isPressed)
    {
        OutputDebugStringA("S released");
        force -= Point2D(0, -0.00009f);
    }
    if (keyID == 0x0041 && isPressed)
    {
        OutputDebugStringA("A pressed");
        force += Point2D(-0.00009f, 0);
    }
    if (keyID == 0x0041 && !isPressed)
    {
        OutputDebugStringA("A released");
        force -= Point2D(-0.00009f, 0);
    }
    if (keyID == 0x0044 && isPressed)
    {
        OutputDebugStringA("D pressed");
        force += Point2D(0.00009f, 0);
    }
    if (keyID == 0x0044 && !isPressed)
    {
        OutputDebugStringA("D released");
        force -= Point2D(0.00009f, 0);
    }
  
    PS::getComponent(playerObject->getId())->SetForce(force);
}



void* LoadFile(const char* i_pFilename, size_t& o_sizeFile);
GLib::Sprite* CreateSprite(const char* i_pFilename);


void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
{
    MovePlayer(i_VKeyID, bWentDown);
    if (i_VKeyID == 0x0051)
    {
        isQuit = true;
    }
   
#ifdef _DEBUG
    const size_t	lenBuffer = 65;
    char			Buffer[lenBuffer];

    sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
    OutputDebugStringA(Buffer);
#endif // __DEBUG
}


int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
    _CrtSetBreakAlloc(237);
    // IMPORTANT: first we need to initialize GLib
    bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "MonsterChase", -1, 800, 600, true);

    if (bSuccess)
    {

        // Create sprites using our own helper routine CreateSprite
        demon = CreateSprite("data\\monster1.dds");
        player = CreateSprite("data\\GoodGuy.dds");
        finish = CreateSprite("data\\finish.dds");
        gameover = CreateSprite("data\\game_over.dds");
        winner = CreateSprite("data\\winner.dds");

        bool bQuit = false;

        RunDemonHunter();

        if (demon) {
            GLib::Sprite* d = demon;
            GLib::Release(d);
        }


        // IMPORTANT:  Tell GLib to shutdown, releasing resources.
        GLib::Release(player);
        GLib::Release(demon);
        //GLib::Shutdown();
    }

#if defined _DEBUG
    _CrtDumpMemoryLeaks();
#endif // _DEBUG
    return 0;
}

GLib::Sprite* CreateSprite(const char* i_pFilename)
{
    assert(i_pFilename);

    size_t sizeTextureFile = 0;

    // Load the source file (texture data)
    void* pTextureFile = LoadFile(i_pFilename, sizeTextureFile);

    // Ask GLib to create a texture out of the data (assuming it was loaded successfully)
    GLib::Texture* pTexture = pTextureFile ? GLib::CreateTexture(pTextureFile, sizeTextureFile) : nullptr;

    // exit if something didn't work
    // probably need some debug logging in here!!!!
    if (pTextureFile)
        delete[] pTextureFile;

    if (pTexture == nullptr)
        return nullptr;

    unsigned int width = 0;
    unsigned int height = 0;
    unsigned int depth = 0;

    // Get the dimensions of the texture. We'll use this to determine how big it is on screen
    bool result = GLib::GetDimensions(*pTexture, width, height, depth);
    assert(result == true);
    assert((width > 0) && (height > 0));

    // Define the sprite edges
    GLib::SpriteEdges	Edges = { -float(width / 2.0f), float(height), float(width / 2.0f), 0.0f };
    GLib::SpriteUVs	UVs = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f } };
    GLib::RGBA							Color = { 255, 255, 255, 255 };

    // Create the sprite
    GLib::Sprite* pSprite = GLib::CreateSprite(Edges, 0.1f, Color, UVs, pTexture);

    // release our reference on the Texture
    GLib::Release(pTexture);

    return pSprite;
}

void* LoadFile(const char* i_pFilename, size_t& o_sizeFile)
{
    assert(i_pFilename != NULL);

    FILE* pFile = NULL;

    errno_t fopenError = fopen_s(&pFile, i_pFilename, "rb");
    if (fopenError != 0)
        return NULL;

    assert(pFile != NULL);

    int FileIOError = fseek(pFile, 0, SEEK_END);
    assert(FileIOError == 0);

    long FileSize = ftell(pFile);
    assert(FileSize >= 0);

    FileIOError = fseek(pFile, 0, SEEK_SET);
    assert(FileIOError == 0);

    uint8_t* pBuffer = new uint8_t[FileSize];
    assert(pBuffer);

    size_t FileRead = fread(pBuffer, 1, FileSize, pFile);
    assert(FileRead == FileSize);

    fclose(pFile);

    o_sizeFile = FileSize;

    return pBuffer;
}



