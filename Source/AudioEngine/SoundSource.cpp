#include <al.h>

#include "AudioEngine/SoundSource.hpp"

AudioEngine::SoundSource::SoundSource()
{
	alGenSources(1, &m_SourceID);
}

AudioEngine::SoundSource::~SoundSource()
{
	Stop();
	alDeleteSources(1, &m_SourceID);
}

void AudioEngine::SoundSource::Play(const uint32_t buffer) const
{
	Stop();
	alSourcei(m_SourceID, AL_BUFFER, buffer);
	alSourcePlay(m_SourceID);
}

void AudioEngine::SoundSource::Pause() const
{
	alSourcePause(m_SourceID);
}

void AudioEngine::SoundSource::Continue() const
{
	alSourcePlay(m_SourceID);
}

void AudioEngine::SoundSource::Stop() const
{
	alSourceStop(m_SourceID);
}

bool AudioEngine::SoundSource::IsPlaying() const
{
	int32_t value;

	alGetSourcei(m_SourceID, AL_SOURCE_STATE, &value);

	return (value == AL_PLAYING);
}

void AudioEngine::SoundSource::SetLooping(const bool loop) const
{
	alSourcei(m_SourceID, AL_LOOPING, (loop) ? AL_TRUE : AL_FALSE);
}

void AudioEngine::SoundSource::SetPitch(const float pitch) const
{
	alSourcef(m_SourceID, AL_PITCH, pitch);
}

void AudioEngine::SoundSource::SetPosition(const float x, const float y, const float z) const
{
	alSource3f(m_SourceID, AL_POSITION, x, y, z);
}

void AudioEngine::SoundSource::SetVelocity(const float x, const float y, const float z) const
{
	alSource3f(m_SourceID, AL_VELOCITY, x, y, z);
}

void AudioEngine::SoundSource::SetGain(const float volume) const
{
	alSourcef(m_SourceID, AL_GAIN, volume);
}

void AudioEngine::SoundSource::SetAttenuationRolloffFactor(const float factor) const
{
	alSourcef(m_SourceID, AL_ROLLOFF_FACTOR, factor);
}

void AudioEngine::SoundSource::SetAttenuationReferenceDistance(const float distance) const
{
	alSourcef(m_SourceID, AL_REFERENCE_DISTANCE, distance);
}

void AudioEngine::SoundSource::SetAttenuationMaxDistance(const float distance) const
{
	alSourcef(m_SourceID, AL_MAX_DISTANCE, distance);
}
