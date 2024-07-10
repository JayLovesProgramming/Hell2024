#pragma once
#include "../Common.h"
#include "GameObject.h"
#include "AnimatedGameObject.h"
#include "Light.h"
#include "../Physics/Physics.h"
#include "../Effects/BloodDecal.hpp"
#include "../Effects/BulletCasing.h"
#include "../Effects/BulletHoleDecal.hpp"
#include "../Core/VolumetricBloodSplatter.h"
#include "../Editor/CSG.h"
#include "../Game/Player.h"
#include "../Types/Modular/Door.h"
#include "../Types/Modular/Ceiling.h"
#include "../Types/Modular/Floor.h"
#include "../Types/Modular/Toilet.h"
#include "../Types/Modular/Wall.h"
#include "../Types/Modular/Window.h"
#include "../Util.hpp"

inline float RandFloat(float min, float max) {
    return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}

inline glm::vec3 NormalFromThreePoints(glm::vec3 pos0, glm::vec3 pos1, glm::vec3 pos2) {
    return glm::normalize(glm::cross(pos1 - pos0, pos2 - pos0));
}

inline void SetNormalsAndTangentsFromVertices(Vertex* vert0, Vertex* vert1, Vertex* vert2) {
    // Shortcuts for UVs
    glm::vec3& v0 = vert0->position;
    glm::vec3& v1 = vert1->position;
    glm::vec3& v2 = vert2->position;
    glm::vec2& uv0 = vert0->uv;
    glm::vec2& uv1 = vert1->uv;
    glm::vec2& uv2 = vert2->uv;
    // Edges of the triangle : position delta. UV delta
    glm::vec3 deltaPos1 = v1 - v0;
    glm::vec3 deltaPos2 = v2 - v0;
    glm::vec2 deltaUV1 = uv1 - uv0;
    glm::vec2 deltaUV2 = uv2 - uv0;
    float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
    glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
    glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;
    glm::vec3 normal = NormalFromThreePoints(vert0->position, vert1->position, vert2->position);
    vert0->normal = normal;
    vert1->normal = normal;
    vert2->normal = normal;
    vert0->tangent = tangent;
    vert1->tangent = tangent;
    vert2->tangent = tangent;
}

#define PROPOGATION_SPACING 1
#define PROPOGATION_WIDTH (MAP_WIDTH / PROPOGATION_SPACING)
#define PROPOGATION_HEIGHT (MAP_HEIGHT / PROPOGATION_SPACING)
#define PROPOGATION_DEPTH (MAP_DEPTH / PROPOGATION_SPACING)

struct CubeVolume {


private:
public:
    // MAKE PRIVATE, AND ADD CONST FOR THE RETURN TYPE OF GETTER
    // MAKE PRIVATE, AND ADD CONST FOR THE RETURN TYPE OF GETTER
    // MAKE PRIVATE, AND ADD CONST FOR THE RETURN TYPE OF GETTER
    // MAKE PRIVATE, AND ADD CONST FOR THE RETURN TYPE OF GETTER
    Transform m_transform;

public:
    uint32_t materialIndex = 0;
    float textureScale = 1.0f;
    glm::mat4 GetModelMatrix() {
        return  m_transform.to_mat4();
    }

    void SetTransform(Transform transform) {
        m_transform = transform;
        if (pxRigidStatic) {
            PxMat44 matrix = Util::GlmMat4ToPxMat44(GetModelMatrix());
            PxTransform transform2 = PxTransform(matrix);
            pxRigidStatic->setGlobalPose(transform2);
        }
    }

    Transform& GetTransform() {
        return m_transform;
    }

    PxRigidStatic* pxRigidStatic = nullptr;
    PxShape* pxShape = nullptr;

    void CleanUp() {
        if (pxRigidStatic) {
            if (pxRigidStatic->userData) {
                // MEMORY LEAK! FIX!!!
                // MEMORY LEAK! FIX!!!
                // MEMORY LEAK! FIX!!!
                // MEMORY LEAK! FIX!!!
                // MEMORY LEAK! FIX!!!
                // MEMORY LEAK! FIX!!!
                // MEMORY LEAK! FIX!!!
                // MEMORY LEAK! FIX!!!
            }
            pxRigidStatic->release();
        }
        if (pxShape) {
            pxShape->release();
        }
    }

    void CreateCubePhysicsObject() {

        PhysicsFilterData filterData2;
        filterData2.raycastGroup = RaycastGroup::RAYCAST_ENABLED;
        filterData2.collisionGroup = NO_COLLISION;
        filterData2.collidesWith = NO_COLLISION;
        PxShapeFlags shapeFlags(PxShapeFlag::eSCENE_QUERY_SHAPE); // Most importantly NOT eSIMULATION_SHAPE. PhysX does not allow for tri mesh.

        float width = m_transform.scale.x * 0.5f;
        float height = m_transform.scale.y * 0.5f;
        float depth = m_transform.scale.z * 0.5f;

        pxShape = Physics::CreateBoxShape(width, height, depth);
        pxRigidStatic = Physics::CreateRigidStatic(Transform(), filterData2, pxShape);

        PhysicsObjectData* physicsObjectData = new PhysicsObjectData(PhysicsObjectType::CSG_OBJECT_SUBTRACTIVE, this);
        pxRigidStatic->userData = physicsObjectData;

        PxMat44 m2 = Util::GlmMat4ToPxMat44(GetModelMatrix());
        PxTransform transform2 = PxTransform(m2);
        pxRigidStatic->setGlobalPose(transform2);

    }
};

struct SpawnPoint {
    glm::vec3 position = glm::vec3(0);
    glm::vec3 rotation = glm::vec3(0);
};

struct RTMesh {
    GLuint baseVertex = 0;
    GLuint vertexCount = 0;
    GLuint padding0 = 0;
    GLuint padding1 = 0;
};

struct RTInstance {
    glm::mat4 modelMatrix = glm::mat4(1);
    glm::mat4 inverseModelMatrix = glm::mat4(1);
    GLuint meshIndex = 0;
    GLuint padding0 = 0;
    GLuint padding1 = 0;
    GLuint padding2 = 0;
};

struct Bullet {
    glm::vec3 spawnPosition;
    glm::vec3 direction;
    Weapon type;
    PxU32 raycastFlags;
    glm::vec3 parentPlayersViewRotation;
};

struct PickUp {

	enum class Type { GLOCK_AMMO = 0};

	Type type;
	glm::vec3 position;
	glm::vec3 rotation;
	std::string parentGameObjectName = "";
	bool pickedUp = false;
    float timeSincePickedUp = 0.0f;
	float respawnTime = 10.0f;

	glm::mat4 GetModelMatrix() {
		Transform transform;
		transform.position = position;
		transform.rotation = rotation;
		return transform.to_mat4();
	}

    void Update(float deltaTime) {

        if (pickedUp) {
            timeSincePickedUp += deltaTime;
        }
        if (timeSincePickedUp > respawnTime) {
            pickedUp = false;
            timeSincePickedUp = 0;
        }
    }
};

namespace Scene {

    void Update(float deltaTime);

    void LoadDefaultScene();

    // Bullet Hole Decals
    void CreateBulletDecal(glm::vec3 localPosition, glm::vec3 localNormal, PxRigidBody* parent, BulletHoleDecalType type);
    BulletHoleDecal* GetBulletHoleDecalByIndex(int32_t index);
    const size_t GetBulletHoleDecalCount();
    void CleanUpBulletHoleDecals();

    // Bullet Casings
    void CleanUpBulletCasings();

    // Game Objects
    int32_t CreateGameObject();
    GameObject* GetGameObjectByIndex(int32_t index);
    GameObject* GetGameObjectByName(std::string name);
    std::vector<GameObject>& GetGamesObjects();
    void UpdateGameObjects(float deltaTime);
    const size_t GetGameObjectCount();

    // Animated Game Objects
    int32_t CreateAnimatedGameObject();
    AnimatedGameObject* GetAnimatedGameObjectByIndex(int32_t index);
    std::vector<AnimatedGameObject>& GetAnimatedGamesObjects();
    std::vector<AnimatedGameObject*> GetAnimatedGamesObjectsToSkin();
    //void UpdateAnimatedGameObjects(float deltaTime);
    const size_t GetAnimatedGameObjectCount();

    // Map stuff
    CubeVolume* GetCubeVolumeAdditiveByIndex(int32_t index);
    CubeVolume* GetCubeVolumeSubtractiveByIndex(int32_t index);

    // Containers
    inline std::vector<Light> g_lights;
    inline std::vector<Door> g_doors;
    inline std::vector<Window> g_windows;
    inline std::vector<SpawnPoint> g_spawnPoints;
    inline std::vector<BulletCasing> g_bulletCasings;
    inline std::vector<CubeVolume> g_cubeVolumesAdditive;
    inline std::vector<CubeVolume> g_cubeVolumesSubtractive;

    // OLD SHIT BELOW
    inline PxTriangleMesh* _sceneTriangleMesh = NULL;
    inline PxRigidStatic* _sceneRigidDynamic = NULL;
    inline PxShape* _sceneShape = NULL;

    inline std::vector<Toilet> _toilets;
    inline std::vector<BloodDecal> _bloodDecals;
    inline std::vector<VolumetricBloodSplatter> _volumetricBloodSplatters;
    inline std::vector<PickUp> _pickUps;
    inline std::vector<Bullet> _bullets;

	inline std::vector<Wall> _walls;
    inline std::vector<Floor> _floors;
    inline std::vector<Ceiling> _ceilings;
    inline std::vector<CloudPointOld> _cloudPoints;
    //inline std::vector<GameObject> _gameObjects;
    inline std::vector<glm::vec3> _rtVertices;
    inline std::vector<RTMesh> _rtMesh;
    inline std::vector<RTInstance> _rtInstances;

    // New shit
    void LoadMapNEW(std::string mapPath);
    std::vector<RenderItem3D> GetAllRenderItems();
    std::vector<RenderItem3D> CreateDecalRenderItems();

    // Old shit
	void LoadHardCodedObjects();
	void LoadMap(std::string mapPath);
	void SaveMap(std::string mapPath);
    void CleanUp();
    void Update_OLD(float deltaTime);
    void LoadLightSetup(int index);
    //AnimatedGameObject* GetAnimatedGameObjectByName(std::string);
   // std::vector<AnimatedGameObject>& GetAnimatedGameObjects();
    void CreatePointCloud();
    void CreateMeshData();
    void AddLight(Light& light);
    void AddDoor(Door& door);
    void AddWall(Wall& wall);
    void AddFloor(Floor& floor);
    void UpdateRTInstanceData();
    void RecreateDataStructures();
    //void CreateScenePhysicsObjects();
    void ProcessPhysicsCollisions();
	void RecreateAllPhysicsObjects();
	void RemoveAllDecalsFromWindow(Window* window);
    void CalculateLightBoundingVolumes();
    void CheckForDirtyLights();
    void ResetGameObjectStates();

    void CreateVolumetricBlood(glm::vec3 position, glm::vec3 rotation, glm::vec3 front);


    //Player* GetPlayerFromCharacterControler(PxController* characterController);
}