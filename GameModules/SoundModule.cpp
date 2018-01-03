#include <AudioEngine/AudioMaster.hpp>
#include <AudioEngine/SoundSource.hpp>
#include <Infrastructure/GameModule.hpp>

#define WAV_MYSTERY "../Assets/sound/Mystery.wav"

AudioMaster *audioMaster;
SoundSource *backgroundMusic;

static void OnGameStart()
{
    audioMaster = AudioMaster::GetInstance();
    backgroundMusic = new SoundSource();

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

bool ModuleInit()
{
    EventProcessing::EventHandler::GetInstance()->RegisterOnGameStartCallback(OnGameStart);
    EventProcessing::EventHandler::GetInstance()->RegisterOnGameEndCallback(OnGameEnd);
    return true;
}
