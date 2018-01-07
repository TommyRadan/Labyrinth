#include <al.h>
#include <alut.h>

#include "AudioEngine/AudioMaster.hpp"

AudioEngine::AudioMaster::AudioMaster()
{
    alutInit(nullptr, nullptr);
    alGetError();
}

AudioEngine::AudioMaster::~AudioMaster()
{
    for (auto& buffer : m_Buffers)
    {
        alDeleteBuffers(1, &buffer);
    }

    alutExit();
}

AudioEngine::AudioMaster* AudioEngine::AudioMaster::GetInstance()
{
    static AudioMaster* instance = nullptr;

    if (instance == nullptr)
    {
        instance = new AudioMaster();
    }

    return instance;
}

uint32_t AudioEngine::AudioMaster::LoadSound(const std::string &filePath)
{
    uint32_t buffer;

    alGenBuffers(1, &buffer);
    m_Buffers.push_back(buffer);

    buffer = alutCreateBufferFromFile(filePath.c_str());

    return buffer;
}

void AudioEngine::AudioMaster::SetListenerPosition(const float x, const float y, const float z)
{
    alListener3f(AL_POSITION, x, y, z);
}

void AudioEngine::AudioMaster::SetListenerVelocity(const float x, const float y, const float z)
{
    alListener3f(AL_VELOCITY, x, y, z);
}

void AudioEngine::AudioMaster::SetListenerOrientation(const float listenerOrientation[6])
{
    alListenerfv(AL_ORIENTATION, listenerOrientation);
}
