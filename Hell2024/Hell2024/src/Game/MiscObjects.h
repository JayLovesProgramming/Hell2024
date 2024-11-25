#pragma once

#include "Scene.h"

using Scene::CreateGameObject, Scene::GetGameObjectByIndex, Scene::GetGameObjectCount;

class MiscObjectsManager
{
public:
    inline static glm::vec3 houseOrigin = glm::vec3(2, 0.5, 0);

    inline static void SpawnChristmasTree()
	{
        CreateGameObject();
        GameObject* tree = GetGameObjectByIndex(GetGameObjectCount() - 1);
        tree->SetPosition(-0.1f, 0.5f, 3.8f);
        tree->SetModel("ChristmasTree");
        tree->SetName("ChristmasTree");
        tree->SetMeshMaterial("Tree");
        tree->SetMeshMaterialByMeshName("Balls", "Gold");
	}

    inline static void SpawnChristmasBoxPresents()
    {
        float spacing = 0.3f;
        for (int x = -3; x < 1; x++)
        {
            for (int y = -1; y < 5; y++)
            {
                for (int z = -1; z < 2; z++)
                {
                    CreateGameObject();
                    GameObject* cube = GetGameObjectByIndex(GetGameObjectCount() - 1);
                    float halfExtent = 0.1f;
                    cube->SetPosition(2.6f + x * spacing, 1.5f + y * spacing * 1.25f, 2.1f + z * spacing);
                    cube->SetRotationX(Util::RandomFloat(0, HELL_PI * 2));
                    cube->SetRotationY(Util::RandomFloat(0, HELL_PI * 2));
                    cube->SetRotationZ(Util::RandomFloat(0, HELL_PI * 2));
                    cube->SetWakeOnStart(true);
                    cube->SetModel("ChristmasPresent");
                    cube->SetName("Present");
                    int rand = Util::RandomInt(0, 3);
                    if (rand == 0)
                    {
                        cube->SetMeshMaterial("PresentA");
                    }
                    else if (rand == 1)
                    {
                        cube->SetMeshMaterial("PresentB");
                    }
                    else if (rand == 2)
                    {
                        cube->SetMeshMaterial("PresentC");
                    }
                    else if (rand == 3)
                    {
                        cube->SetMeshMaterial("PresentD");
                    }
                    cube->SetMeshMaterialByMeshName("Bow", "Gold");
                    Transform transform;
                    transform.position = glm::vec3(2.0f, y * halfExtent * 2 + 0.2f, 3.5f);
                    PxShape* collisionShape = Physics::CreateBoxShape(halfExtent, halfExtent, halfExtent);
                    PxShape* raycastShape = Physics::CreateBoxShape(halfExtent, halfExtent, halfExtent);
                    PhysicsFilterData filterData;
                    filterData.raycastGroup = RAYCAST_DISABLED;
                    filterData.collisionGroup = CollisionGroup::GENERIC_BOUNCEABLE;
                    filterData.collidesWith = (CollisionGroup)(ENVIROMENT_OBSTACLE | GENERIC_BOUNCEABLE | RAGDOLL);
                    cube->SetKinematic(false);
                    cube->AddCollisionShape(collisionShape, filterData);
                    cube->SetRaycastShape(raycastShape);
                    cube->SetModelMatrixMode(ModelMatrixMode::PHYSX_TRANSFORM);
                    cube->UpdateRigidBodyMassAndInertia(20.0f);
                    cube->SetCollisionType(CollisionType::BOUNCEABLE);
                }
            }
        }
    }

    inline static void SpawnPictureFrame()
    {
        CreateGameObject();
        GameObject* pictureFrame = GetGameObjectByIndex(GetGameObjectCount() - 1);
        pictureFrame->SetPosition(1.1f, 1.9f, -0.85f);
        pictureFrame->SetScale(0.01f);
        //pictureFrame->SetRotationY(HELL_PI / 2);
        pictureFrame->SetModel("PictureFrame_1");
        pictureFrame->SetMeshMaterial("LongFrame");
        pictureFrame->SetName("PictureFrame");
    }

    inline static void LoadHouseRailings()
    {
        CreateGameObject();
        GameObject* houseRailings = GetGameObjectByIndex(GetGameObjectCount() - 1);
        houseRailings->SetPosition(houseOrigin);
        houseRailings->SetModel("House_Railings");
        houseRailings->SetName("BlenderHouse");
        houseRailings->SetMeshMaterial("Ceiling2");

        CreateGameObject();
        GameObject* houseWalls = GetGameObjectByIndex(GetGameObjectCount() - 1);
        houseWalls->SetPosition(houseOrigin);
        houseWalls->SetModel("House_Walls2");
        houseWalls->SetName("BlenderHouse");
        houseWalls->SetMeshMaterial("Ceiling2");

        CreateGameObject();
        GameObject* houseRoof = GetGameObjectByIndex(GetGameObjectCount() - 1);
        houseRoof->SetPosition(houseOrigin);
        houseRoof->SetModel("House_RoofA");
        houseRoof->SetName("BlenderHouse");
        houseRoof->SetMeshMaterial("Ceiling2");

        CreateGameObject();
        GameObject* houseRoofB = GetGameObjectByIndex(GetGameObjectCount() - 1);
        houseRoofB->SetPosition(houseOrigin);
        houseRoofB->SetModel("House_RoofB");
        houseRoofB->SetName("BlenderHouse");
        houseRoofB->SetMeshMaterial("Ceiling2");
    }
};
