#include "Animation.hpp"
#include "Utils/Util.hpp"

Animation::Animation(std::string fullPath)
{
    m_fullPath = fullPath;
    FileInfo info = Util::GetFileInfo(fullPath);
    _filename = info.filename;
}

Animation::~Animation()
{
}

float Animation::GetTicksPerSecond() const
{
    return m_ticksPerSecond != 0 ? m_ticksPerSecond : 25.0f;
}
