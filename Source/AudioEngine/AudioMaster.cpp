#include <al.h>
#include <alut.h>

#include "AudioEngine/AudioMaster.hpp"

AudioMaster::AudioMaster()
{
    alutInit(nullptr, nullptr);
    alGetError();
}

AudioMaster::~AudioMaster()
{
    for (auto& buffer : m_Buffers)
    {
        alDeleteBuffers(1, &buffer);
    }

    alutExit();
}

AudioMaster* AudioMaster::GetInstance()
{
    static AudioMaster* instance = nullptr;

    if (instance == nullptr)
    {
        instance = new AudioMaster();
    }

    return instance;
}

uint32_t AudioMaster::LoadSound(const std::string &filePath)
{
    uint32_t buffer;

    alGenBuffers(1, &buffer);
    m_Buffers.push_back(buffer);

    buffer = alutCreateBufferFromFile(filePath.c_str());

    return buffer;
}

void AudioMaster::SetListenerPosition(const float x, const float y, const float z)
{
    alListener3f(AL_POSITION, x, y, z);
}

void AudioMaster::SetListenerVelocity(const float x, const float y, const float z)
{
    alListener3f(AL_VELOCITY, x, y, z);
}

void AudioMaster::SetListenerOrientation(const float listenerOrientation[6])
{
    alListenerfv(AL_ORIENTATION, listenerOrientation);
}
