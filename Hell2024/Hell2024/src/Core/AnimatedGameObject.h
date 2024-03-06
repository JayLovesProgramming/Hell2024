#pragma once
#include "Animation/SkinnedModel.h"
#include "Ragdoll.h"

struct AnimatedGameObject {

    enum AnimationMode { BINDPOSE, ANIMATION, RAGDOLL };

	void Update(float deltaTime);
	void SetName(std::string name);
	void SetSkinnedModel(std::string skinnedModelName);
	void SetScale(float scale);
	void SetPosition(glm::vec3 position);
	void SetRotationX(float rotation);
	void SetRotationY(float rotation);
	void SetRotationZ(float rotation);
	void ToggleAnimationPause();
	void PlayAnimation(std::string animationName, float speed);
	void PlayAndLoopAnimation(std::string animationName, float speed);
    void PauseAnimation();
    void SetAnimationModeToBindPose();
	void SetMeshMaterial(std::string meshName, std::string materialName);
	void SetMeshMaterialByIndex(int meshIndex, std::string materialName);
	void SetMaterial(std::string materialName);
    void UpdateBoneTransformsFromBindPose();
    void UpdateBoneTransformsFromRagdoll();
	glm::mat4 GetBoneWorldMatrixFromBoneName(std::string name);

	std::string GetName();
	glm::mat4 GetModelMatrix();
	bool IsAnimationComplete(); 
	bool AnimationIsPastPercentage(float percent);
    glm::vec3 GetScale();

	SkinnedModel* _skinnedModel;
	Transform _transform;
	AnimatedTransforms _animatedTransforms;
	float _currentAnimationTime = 0;
	glm::mat4 _cameraMatrix = glm::mat4(1);
	std::vector<int> _materialIndices;
    AnimationMode _animationMode = BINDPOSE;
    Ragdoll _ragdoll;

	// Hacky shit
	glm::vec3 GetGlockBarrelPostion();
	glm::vec3 GetGlockCasingSpawnPostion();
	glm::vec3 GetAKS74UBarrelPostion();
	glm::vec3 GetShotgunBarrelPosition();
	glm::vec3 GetAK74USCasingSpawnPostion();

    void LoadRagdoll(std::string filename, PxU32 ragdollCollisionFlags);
    void SetRagdollToCurrentAniamtionState();
    void SetAnimatedModeToRagdoll();
    void DestroyRagdoll();
    void WipeAllSkippedMeshIndices();
    void AddSkippedMeshIndexByName(std::string meshName);
    void PrintMeshNames();

    std::vector<glm::mat4> _debugTransformsA;
    std::vector<glm::mat4> _debugTransformsB;
    bool _hasRagdoll = false;
    std::vector<unsigned int> _skippedMeshIndices;

private:

	void UpdateAnimation(float deltaTime);
	void CalculateBoneTransforms();	

	Animation* _currentAnimation = nullptr;
	bool _loopAnimation = false;
	bool _animationPaused = false;
	float _animationSpeed = 1.0f;
	std::string _name;
	bool _animationIsComplete = true;


};