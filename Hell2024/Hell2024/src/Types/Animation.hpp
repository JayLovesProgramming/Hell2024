#pragma once

#include <map>
#include <string>
#include <iostream>
#include <vector>

#include "Defines.hpp"
#include "RendererCommon.hpp"

struct SQT 
{
    glm::quat rotation = glm::quat(1, 0, 0, 0);
    glm::vec3 positon = glm::vec3(0, 0, 0);
    float scale = 1.0f;
    float timeStamp = -1;
    const char* jointName = "";
};

struct AnimatedNode
{
    AnimatedNode(const char* name)
    {
        m_nodeName = name;
    }
    std::vector<SQT> m_nodeKeys;
    const char* m_nodeName;
};


class Animation
{
public:
    Animation() = default;
    Animation(std::string fulllPath);
    ~Animation();

    float GetTicksPerSecond() const;

    bool m_awaitingLoadingFromDisk = true;
    bool m_loadedFromDisk = false;
    std::string m_fullPath = "";

    float m_duration = 0;
    float m_ticksPerSecond = 0;
    float m_finalTimeStamp = 0;
    std::string _filename;

    std::vector<AnimatedNode> m_animatedNodes;
    std::map<const char*, unsigned int> m_NodeMapping; // maps a node name to its index
};
