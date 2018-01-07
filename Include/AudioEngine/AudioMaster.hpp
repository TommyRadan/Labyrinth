#pragma once

#include <cstdint>
#include <list>
#include <string>

namespace AudioEngine
{
	struct AudioMaster
	{
		AudioMaster();
		~AudioMaster();

		AudioMaster(AudioMaster&) = delete;
		AudioMaster(AudioMaster&&) = delete;
		AudioMaster& operator=(AudioMaster&) = delete;
		AudioMaster& operator=(AudioMaster&&) = delete;

		static AudioMaster* GetInstance();

		uint32_t LoadSound(const std::string& filePath);

		void SetListenerPosition(float x, float y, float z);
		void SetListenerVelocity(float x, float y, float z);
		void SetListenerOrientation(const float listenerOrientation[6]);

	private:
		std::list<uint32_t> m_Buffers;
	};
}
