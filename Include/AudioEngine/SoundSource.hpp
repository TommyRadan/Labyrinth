#pragma once

#include <cstdint>

namespace AudioEngine
{
	struct SoundSource
	{
		SoundSource();
		~SoundSource();

		void Play(uint32_t buffer) const;
		void Pause() const;
		void Continue() const;
		void Stop() const;

		bool IsPlaying() const;

		void SetLooping(bool loop) const;
		void SetPitch(float pitch) const;
		void SetPosition(float x, float y, float z) const;
		void SetVelocity(float x, float y, float z) const;
		void SetGain(float volume) const;

		void SetAttenuationRolloffFactor(float factor) const;
		void SetAttenuationReferenceDistance(float distance) const;
		void SetAttenuationMaxDistance(float distance) const;

	private:
		uint32_t m_SourceID;
	};
}
