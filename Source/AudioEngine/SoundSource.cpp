#include <al.h>

#include "AudioEngine/SoundSource.hpp"

SoundSource::SoundSource()
{
	alGenSources(1, &m_SourceID);
}

SoundSource::~SoundSource()
{
	Stop();
	alDeleteSources(1, &m_SourceID);
}

void SoundSource::Play(const uint32_t buffer) const
{
	Stop();
	alSourcei(m_SourceID, AL_BUFFER, buffer);
	alSourcePlay(m_SourceID);
}

void SoundSource::Pause() const
{
	alSourcePause(m_SourceID);
}

void SoundSource::Continue() const
{
	alSourcePlay(m_SourceID);
}

void SoundSource::Stop() const
{
	alSourceStop(m_SourceID);
}

bool SoundSource::IsPlaying() const
{
	int32_t value;

	alGetSourcei(m_SourceID, AL_SOURCE_STATE, &value);

	return (value == AL_PLAYING);
}

void SoundSource::SetLooping(const bool loop) const
{
	alSourcei(m_SourceID, AL_LOOPING, (loop) ? AL_TRUE : AL_FALSE);
}

void SoundSource::SetPitch(const float pitch) const
{
	alSourcef(m_SourceID, AL_PITCH, pitch);
}

void SoundSource::SetPosition(const float x, const float y, const float z) const
{
	alSource3f(m_SourceID, AL_POSITION, x, y, z);
}

void SoundSource::SetVelocity(const float x, const float y, const float z) const
{
	alSource3f(m_SourceID, AL_VELOCITY, x, y, z);
}

void SoundSource::SetGain(const float volume) const
{
	alSourcef(m_SourceID, AL_GAIN, volume);
}

void SoundSource::SetAttenuationRolloffFactor(const float factor) const
{
	alSourcef(m_SourceID, AL_ROLLOFF_FACTOR, factor);
}

void SoundSource::SetAttenuationReferenceDistance(const float distance) const
{
	alSourcef(m_SourceID, AL_REFERENCE_DISTANCE, distance);
}

void SoundSource::SetAttenuationMaxDistance(const float distance) const
{
	alSourcef(m_SourceID, AL_MAX_DISTANCE, distance);
}
