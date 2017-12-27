#pragma once

#include <cstdint>
#include <list>
#include <string>

class AudioMaster
{
public:
	AudioMaster();
	~AudioMaster();

	uint32_t LoadSound(const std::string& filePath);

	void SetListenerPosition(float x, float y, float z);
	void SetListenerVelocity(float x, float y, float z);
	void SetListenerOrientation(const float listenerOrientation[6]);

private:
	std::list<uint32_t> m_Buffers;
};
