#pragma once

#include "RendererCommon.hpp"
#include "Types/LightVolume.hpp"
#include <vector>

namespace GlobalIllumination
{
    void CreatePointCloud();
    void CreateLightVolume(float width, float height, float depth, float offsetX, float offsetY, float offsetZ);
    std::vector<CloudPoint>& GetPointCloud();
    LightVolume* GetLightVolumeByIndex(int index);
    void RecalculateGI();
    void DestroyAllLightVolumes();
    void ClearData();
    bool GPUDataAwaitingClear();
    void MarkGPUDataCleared();
    void IncrementFrameCounter();
    int GetFrameCounter();
}