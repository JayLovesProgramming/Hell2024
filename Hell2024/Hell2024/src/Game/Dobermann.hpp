#pragma once

#include "HellCommon.hpp"
#include "Game/AnimatedGameObject.hpp"
#include "Pathfinding/Pathfinding2.hpp"

#define DOG_MAX_HEALTH 45

struct DobermannCreateInfo
{
    glm::vec3 position;
    float rotation;
    DobermannState initalState;
};

struct Dobermann
{
    glm::vec3 m_initialPosition = glm::vec3(0);
    glm::vec3 m_currentPosition = glm::vec3(0);

    float m_initialRotation = 0;
    float m_currentRotation = 0;

    DobermannState m_initalState = {};
    DobermannState m_currentState = {};

    int m_animatedGameObjectIndex = -1;
    float m_footstepAudioTimer = 0;
    float m_health = DOG_MAX_HEALTH;

    Path m_pathToTarget;

    float m_walkSpeed = 1.0f;
    float m_runSpeed = 4.0f;
    float m_walkRotationSpeed = 1.0f;
    float m_runRotationSpeed = 2.5f;

    float m_currentSpeed = 0;
    float m_currentRotationSpeed = 0;

    void Init();
    void Update(float deltaTime);
    void GiveDamage(int amount, int targetPlayerIndex);
    void Kill();
    void Revive();
    void CleanUp();
    AnimatedGameObject* GetAnimatedGameObject();
    float GetDistanceToTarget();
    static void AddDobermann(DobermannCreateInfo& createInfo);

    PxController* m_characterController = nullptr;
    PxShape* m_shape = nullptr;
    int m_targetPlayerIndex = -1;
    glm::vec3 m_targetPosition;

private:
    void FindPath(glm::vec3 targetPosition);
    void UpdateDead(float deltaTime);
    void UpdateAudio(float deltaTime);
    void UpdateMovement(float deltaTime);
    void UpdateAnimation();
};