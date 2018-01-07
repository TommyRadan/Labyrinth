#include <AudioEngine/AudioMaster.hpp>
#include <AudioEngine/SoundSource.hpp>
#include <Infrastructure/GameModule.hpp>

#ifdef _DEBUG
#define WAV_MYSTERY "../Assets/sound/Mystery.wav"
#elif _RELEASE
#define WAV_MYSTERY "../Assets/sound/Mystery.wav"
#elif _DEPLOY
#define WAV_MYSTERY "Assets/sound/Mystery.wav"
#endif

AudioEngine::AudioMaster *audioMaster;
AudioEngine::SoundSource *backgroundMusic;

static void OnGameStart()
{
    audioMaster = AudioEngine::AudioMaster::GetInstance();
    backgroundMusic = new AudioEngine::SoundSource();

    const auto buffer = audioMaster->LoadSound(WAV_MYSTERY);

    backgroundMusic->SetLooping(true);
    backgroundMusic->SetGain(0.02F);
    backgroundMusic->Play(buffer);
}

static void OnGameEnd()
{
    delete audioMaster;
    delete backgroundMusic;
}

GAME_MODULE()
{
	REGISTER_CALLBACK(OnGameStart, OnGameStart);
	REGISTER_CALLBACK(OnGameEnd, OnGameEnd);
    return true;
}
